#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include "RenderSettings.h"

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void setCurrentScene(const Scene& scene);  
    Scene& getCurrentScene();   

    void setRenderSettings(const RenderSettings& renderSettings);
    RenderSettings& getRenderSettings();

private:
    Scene currentScene;
    RenderSettings renderSettings;
};

#endif 
