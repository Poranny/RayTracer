#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Light.h"
#include "MyTexture.h"
#include "RenderSettings.h"
#include "VectorUtils.h"
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>                
#include <glm/gtc/matrix_transform.hpp>   
#include <glm/gtc/type_ptr.hpp>           
#include <glm/gtx/norm.hpp>              
#include <cmath> 

class RayTracer {
public:
    RayTracer();
    ~RayTracer();
    MyTexture render(Scene& scene, RenderSettings& renderSettings);

private:

    Scene scene;
    RenderSettings renderSettings;

    Camera camera;
    Eye eye;
    ScreenPlane screenPlane;

    std::vector<Mesh> meshes;
    std::vector<Light> lights;

    MyTexture workTex;

    float indirectDiffuseMultiplier;
    float indirectSpecularMultiplier;

    int diffuseLayerCount;
    int diffuseRadialCount;
    int specularLayerCount;
    int specularRadialCount;

    float bounceRay(Ray ray, int depthLeft);
};

#endif
