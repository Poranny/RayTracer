#include "SceneManager.h"
#include <string>

SceneManager::SceneManager() { 
    
    currentScene = Scene();
    renderSettings = RenderSettings();
}

SceneManager::~SceneManager() {

}

void SceneManager::setCurrentScene(const Scene& scene) {
    currentScene = scene;
}

Scene& SceneManager::getCurrentScene() {
    return currentScene;
}


void SceneManager::setRenderSettings(const RenderSettings& _renderSettings) {
    renderSettings = _renderSettings;
}

RenderSettings& SceneManager::getRenderSettings() {
    return renderSettings;
}
