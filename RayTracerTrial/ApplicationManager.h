#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <wx/wx.h>
#include "GUIManager.h"
#include "RayTracer.h"
#include "SceneManager.h"

class ApplicationManager {
public:
    ApplicationManager();
    ~ApplicationManager();
    void renderAndDisplay(SceneManager& sceneManager, RayTracer& rayTracer, OpenGLRenderer& renderer);

    void run(); 

private:
    wxApp* app;
    GUIManager* guiManager; 
    RayTracer* rayTracer;
    SceneManager* sceneManager;
};

#endif 
