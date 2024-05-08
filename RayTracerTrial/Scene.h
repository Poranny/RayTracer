#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Camera.h"
#include "Light.h"
#include "Defaults.h"
#include "Mesh.h"

class Scene {
public:

    Scene();

    void setCamera(const Camera& camera);
    const Camera& getCamera() const;

    void addLight(const Light& light);
    const std::vector<Light>& getLights() const;
    const Light& getLight(size_t index) const;
    void clearLights();

    void addMesh(const Mesh& mesh);
    const std::vector<Mesh>& getMeshes() const;
    const Mesh& getMesh(size_t index) const;
    void clearMeshes();

    void setBgColor(float _bgCol);
    float getBgColor();


private:
    std::vector<Mesh> meshes;  
    Camera camera;             
    std::vector<Light> lights; 
    float bgColor;
};

#endif 
