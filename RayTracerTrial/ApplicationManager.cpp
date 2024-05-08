#include "ApplicationManager.h"

ApplicationManager::ApplicationManager() {

    app = new wxApp();
    wxApp::SetInstance(app);
    wxEntryStart(0, NULL);

    rayTracer = new RayTracer();
    sceneManager = new SceneManager();


    guiManager = new GUIManager(wxT("RayTracer"), this, sceneManager, rayTracer);
    
}

ApplicationManager::~ApplicationManager() {
    wxEntryCleanup();
}

void ApplicationManager::run() {

    guiManager->Show(true);
    app->MainLoop();
}


void ApplicationManager::renderAndDisplay(SceneManager& sceneManager, RayTracer& rayTracer, OpenGLRenderer& renderer) {
    
    Scene& scene = sceneManager.getCurrentScene();
    RenderSettings& renderSettings = sceneManager.getRenderSettings();

    MyTexture someTex = rayTracer.render(scene, renderSettings);


    renderer.display(someTex);
}