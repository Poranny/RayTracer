#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H
#include <GL/glew.h>
#include <wx/wx.h>
#include "OpenGLRenderer.h"
#include "SceneManager.h"
#include "RenderSettings.h"
class ApplicationManager;
#include "RayTracer.h"
#include "Scene.h"
#include <glm/vec3.hpp> 

class GUIManager : public wxFrame {
public:
    GUIManager(const wxString& title, ApplicationManager* _appManager, SceneManager* _sceneManager, RayTracer* _rayTracer);

    void updateSceneData(Scene& scene, RenderSettings& renderSettings);
    void onClickRender(wxCommandEvent& event);
    void onClickLoadObjMesh(wxCommandEvent& event);
    void onClickLoadObjMesh2(wxCommandEvent& event);

private:

    void setupGeneralControls(wxSizer* controlSizer, wxPanel* controlPanel);
    void setupCameraControls(wxSizer* controlSizer, wxPanel* controlPanel);
    void setupLightControls(wxSizer* controlSizer, wxPanel* controlPanel);
    void setupGeometryControls(wxSizer* controlSizer, wxPanel* controlPanel);
    void setupGeometry2Controls(wxSizer* controlSizer, wxPanel* controlPanel);
    wxBoxSizer* createLabeledTextField(wxPanel* parent, const wxString& label, const wxString& defaultValue, wxTextCtrl*& outField);

    ApplicationManager* appManager;
    SceneManager* sceneManager;
    OpenGLRenderer* glPanel;
    RayTracer* rayTracer;


    wxTextCtrl* txtResWidth;
    wxTextCtrl* txtResHeight;
    wxTextCtrl* txtMaxDepth;

    wxTextCtrl* txtCamPosX, * txtCamPosY, * txtCamPosZ;
    wxTextCtrl* txtCamRotX, * txtCamRotY;
    wxTextCtrl* txtCamFov;

    wxTextCtrl* txtLight1PosX, * txtLight1PosY, * txtLight1PosZ, * txtLight1Int;
    wxTextCtrl* txtLight2PosX, * txtLight2PosY, * txtLight2PosZ, * txtLight2Int;

    wxTextCtrl* txtDiffuse1, * txtSpecular1, * txtRoughness1;
    wxTextCtrl* txtDiffuse2, * txtSpecular2, * txtRoughness2;
    wxTextCtrl* txtIndirectDiffuse, * txtIndirectSpecular;
    wxTextCtrl* txtDiffuseLayerCount, * txtDiffuseRadialCount;
    wxTextCtrl* txtSpecularLayerCount, * txtSpecularRadialCount;

    wxString objFilePath1;
    wxString objFilePath2;
};

#endif
