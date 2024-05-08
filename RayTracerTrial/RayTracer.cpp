#include <GL/glew.h>
#include "RayTracer.h"
#include "RenderSettings.h"
#include "Scene.h"
#include "MyTexture.h"
#include <omp.h>
#include <iostream>


RayTracer::RayTracer() {
   
    scene = Scene();
    renderSettings = RenderSettings();

    camera = Camera();
    eye = camera.getEye();
    screenPlane = camera.getScreenPlane();

    meshes = scene.getMeshes();
    lights = scene.getLights();
}

RayTracer::~RayTracer() {

}

MyTexture RayTracer::render(Scene& _scene, RenderSettings& _renderSettings) {
    workTex = MyTexture(_renderSettings.getResolutionWidth(), _renderSettings.getResolutionHeight());


    scene = _scene;
    renderSettings = _renderSettings;

    indirectDiffuseMultiplier = renderSettings.getIndirectDiffuse();
    indirectSpecularMultiplier = renderSettings.getIndirectSpecular();

    diffuseLayerCount = renderSettings.getDiffuseLayerCount();
    specularLayerCount = renderSettings.getSpecularLayerCount();
    diffuseRadialCount = renderSettings.getDiffuseRadialCount();
    specularRadialCount = renderSettings.getSpecularRadialCount();

    camera = scene.getCamera();

    eye = camera.getEye();
    const glm::vec3& eyePos = eye.getPosition();


    screenPlane = camera.getScreenPlane();

    meshes = scene.getMeshes();
    lights = scene.getLights();


    int width = workTex.getWidth();
    int height = workTex.getHeight();

    #pragma omp parallel for collapse(2)
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            glm::vec3 direction = screenPlane.calculateRayDirection(x, y, eye.getDistance(), eye.getDirection(), width, height);

            Ray ray(eye.getPosition(), direction);

            float lightVal = bounceRay(ray, renderSettings.getMaxDepth());

            if (lightVal < 0) {
                lightVal = 0;
            }

            float pixelVal = 255 * (1.0f - exp(-1* lightVal));

            workTex.setPixel(x, y, pixelVal, pixelVal, pixelVal);
        }
    }

    return workTex;
}

float RayTracer::bounceRay(Ray ray, int depthLeft) {

    if (depthLeft == 0) {
        return 0;
    }

    Mesh* hitMesh = nullptr;
    float hitDistTemp;
    glm::vec3 faceNormalTemp;
    float hitDist;
    glm::vec3 faceNormal;
    glm::vec3 hitPoint;

    float incidentAngle;

    bool wasHit = false;

    float smallestHitDist = -1.0;

    for (Mesh& mesh : meshes) {
        if (mesh.intersects(ray, hitDistTemp, faceNormalTemp)) {
            if (hitDistTemp < smallestHitDist || smallestHitDist == -1.0) {
                faceNormal = -faceNormalTemp;
                hitDist = hitDistTemp;

                hitPoint = ray.getOrigin() + ray.getDirection() * (hitDist - 0.001f);
                
                incidentAngle = glm::angle(ray.getDirection(), faceNormal);
                hitMesh = &mesh;

                smallestHitDist = hitDist;

                wasHit = true;
            }
        }
    }

    if (!wasHit) {
        return scene.getBgColor();
    }

    float materialRoughness = hitMesh->getMaterial().getRoughness();

    float totalLight = 0;
    float indirectDiffuse = 0;
    float indirectSpecular = 0;

    for (Light& light : lights) {
        if (light.getIntensity() == 0) {
            continue;
        }

        glm::vec3 lightDir = glm::normalize(light.getPos() - hitPoint);

        Ray shadowRay(hitPoint, lightDir);
        bool isShadow = false;

        float lightDist = 0;

        lightDist = glm::distance(light.getPos(), hitPoint);

        float shadowHitDist;
        glm::vec3 dummyNormal;

        float smallestHitDist = -1.0;

        for (Mesh& shadowMesh : meshes) {
            if (shadowMesh.intersects(shadowRay, shadowHitDist, dummyNormal) && shadowHitDist < lightDist) {
                isShadow = true;

                break;
            }
        }

        glm::vec3 lightReflectionDir = glm::reflect(-lightDir, faceNormal);
        glm::vec3 rayReflectionDir = glm::reflect(ray.getDirection(), faceNormal);

        if (!isShadow) {
            float diffuseFactor = 1;
            diffuseFactor = glm::max(glm::dot(-faceNormal, lightDir), 0.0f);
            diffuseFactor = pow(diffuseFactor, 1.0);

            totalLight += diffuseFactor * light.getIntensity() * hitMesh->getMaterial().getDiffuse() / pow(lightDist, 2.0);


            float specularFactor = glm::max(glm::dot(-ray.getDirection(), lightReflectionDir), 0.0f);

            specularFactor = glm::pow(specularFactor, (1 / materialRoughness));

            specularFactor /= log1p(materialRoughness + 10);

            totalLight += specularFactor * light.getIntensity() * hitMesh->getMaterial().getSpecular();
        }
        
        if (depthLeft - 1 <= 0) {
            continue;
        }

        if (hitMesh->getMaterial().getDiffuse() > 0) {
            float diffuseLayersStart = 5.0f;
            float diffuseLayersEnd = 89.0f;

            std::vector<float> diffuseLayers = VectorUtils::generateLinearRange(diffuseLayersStart, diffuseLayersEnd, diffuseLayerCount);

            std::vector<glm::vec3> diffuseDirections;

            for (float dLayer : diffuseLayers) {
                std::vector<glm::vec3> diffuseDirectionsTemp = VectorUtils::generateRadialOffsets(diffuseRadialCount, glm::radians(dLayer), -faceNormal);

                for (glm::vec3 diffuseDir : diffuseDirectionsTemp) {
                    diffuseDirections.push_back(diffuseDir);
                }
            }

            float localIndirectDiffuse = 0;

            #pragma omp parallel for reduction(+:localIndirectDiffuse)
            for (int i = 0; i < diffuseDirections.size(); ++i) {
                glm::vec3 diffuseDirection = glm::normalize(diffuseDirections[i]);

                Ray newDiffuseRay = Ray(hitPoint, diffuseDirection);

                localIndirectDiffuse += bounceRay(newDiffuseRay, depthLeft - 1);
            }

            indirectDiffuse = localIndirectDiffuse / diffuseDirections.size();
        }


        if (hitMesh->getMaterial().getSpecular() > 0) {
            float roughnessAngle = 1.0f - exp(-materialRoughness);

            float specularLayersStart = 0.1f;
            float specularLayersEnd = materialRoughness;
            std::vector<float> specularLayers = VectorUtils::generateLinearRange(specularLayersStart, specularLayersEnd, specularLayerCount);

            std::vector<glm::vec3> specularDirections;

            for (float sLayer : specularLayers) {
                std::vector<glm::vec3> specularDirectionsTemp = VectorUtils::generateRadialOffsets(specularRadialCount, glm::radians(sLayer), rayReflectionDir);

                for (glm::vec3 specularDir : specularDirectionsTemp) {
                    specularDirections.push_back(specularDir);
                }
            }

            float localIndirectSpecular = 0;

            #pragma omp parallel for reduction(+:localIndirectSpecular)
            for (int i = 0; i < specularDirections.size(); ++i) {
                glm::vec3 specularDirection = glm::normalize(specularDirections[i]);

                Ray newSpecularRay = Ray(hitPoint, specularDirection);

                localIndirectSpecular += bounceRay(newSpecularRay, depthLeft - 1);
            }

            indirectSpecular = localIndirectSpecular / specularDirections.size();
        }
    }

    indirectDiffuse = indirectDiffuseMultiplier * indirectDiffuse / (pow(totalLight, 0.5) + 1);

    indirectSpecular = indirectSpecularMultiplier * indirectSpecular / (pow(totalLight, 0.5) + 1);

    return totalLight + indirectDiffuse + indirectSpecular;
}
