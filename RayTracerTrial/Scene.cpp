#include "Scene.h"
#include "Camera.h"
#include <stdexcept>

Scene::Scene() {
    
    bgColor = Defaults::BgColor;
}

void Scene::addMesh(const Mesh& mesh) {


    meshes.push_back(mesh);
}

void Scene::setCamera(const Camera& _camera) {
    
    camera = _camera;
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

void Scene::setBgColor(const float _bgCol) {

    bgColor = _bgCol;
}

float Scene::getBgColor() {
    return bgColor;
}


void Scene::clearLights() {
    lights.clear();
}

void Scene::clearMeshes() {
    meshes.clear();  
}


const Light& Scene::getLight(size_t index) const {
    if (index < lights.size()) {
        return lights[index];
    }
    else {
        throw std::out_of_range("Invalid light index");
    }
}


const Mesh& Scene::getMesh(size_t index) const {
    if (index < meshes.size()) {
        return meshes[index];
    }
    else {
        throw std::out_of_range("Invalid mesh index");
    }
}

const std::vector<Mesh>& Scene::getMeshes() const {
    return meshes;
}

const Camera& Scene::getCamera() const {
    return camera;
}

const std::vector<Light>& Scene::getLights() const {
    return lights;
}
