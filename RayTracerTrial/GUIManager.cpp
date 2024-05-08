#include <GL/glew.h>
#include <string>
#include <iostream>
#include "GUIManager.h"
#include "OpenGLRenderer.h"
#include "RayTracer.h"
#include "RenderSettings.h"
#include "ApplicationManager.h"
#include "Defaults.h"
#include "StringUtils.h"
#include "ObjLoader.h"
using namespace std;
void GUIManager::setupGeneralControls(wxSizer* controlSizer, wxPanel* controlPanel) {

    wxStaticText* header = new wxStaticText(controlPanel, wxID_ANY, wxT("RayTracer by Poranny"));
    wxFont font = wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    header->SetFont(font);
    controlSizer->Add(header, 0, wxALL | wxCENTER, 0);

    wxStaticBoxSizer* mainSizer = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxT("Main settings"));

    // Pola rozdzielczoœci
    wxBoxSizer* mainFirstSizer = new wxBoxSizer(wxHORIZONTAL);
    wxString wxDefResX = wxString::FromUTF8(std::to_string(Defaults::ResolutionWidth).c_str());
    wxString wxDefResY = wxString::FromUTF8(std::to_string(Defaults::ResolutionHeight).c_str());

    mainFirstSizer->Add(createLabeledTextField(controlPanel, "Width", wxDefResX, txtResWidth), 1, wxEXPAND | wxALL, 2);
    mainFirstSizer->Add(createLabeledTextField(controlPanel, "Height", wxDefResY, txtResHeight), 1, wxEXPAND | wxALL, 2);
    mainFirstSizer->Add(createLabeledTextField(controlPanel, "Max Depth", wxString::FromUTF8(std::to_string(Defaults::MaxDepth).c_str()), txtMaxDepth), 1, wxEXPAND | wxALL, 2);

    mainSizer->Add(mainFirstSizer, 0, wxEXPAND | wxALL, 2);

    // Diffuse Layer Count i Diffuse Radial Count
    wxBoxSizer* diffuseSizer = new wxBoxSizer(wxHORIZONTAL);
    diffuseSizer->Add(createLabeledTextField(controlPanel, "D Indirect Factor", wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::IndirectDiffuse, 2).c_str()), txtIndirectDiffuse), 1, wxEXPAND | wxALL, 2);
    diffuseSizer->Add(createLabeledTextField(controlPanel, "D Layer Count", wxString::FromUTF8(std::to_string(Defaults::DiffuseLayerCount).c_str()), txtDiffuseLayerCount), 1, wxEXPAND | wxALL, 2);
    diffuseSizer->Add(createLabeledTextField(controlPanel, "D Radial Count", wxString::FromUTF8(std::to_string(Defaults::DiffuseRadialCount).c_str()), txtDiffuseRadialCount), 1, wxEXPAND | wxALL, 2);
    
    mainSizer->Add(diffuseSizer, 0, wxEXPAND | wxALL, 2);

    // Specular Layer Count i Specular Radial Count
    wxBoxSizer* specularSizer = new wxBoxSizer(wxHORIZONTAL); specularSizer->Add(createLabeledTextField(controlPanel, "S Indirect Factor", wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::IndirectSpecular, 2).c_str()), txtIndirectSpecular), 1, wxEXPAND | wxALL, 2);
    specularSizer->Add(createLabeledTextField(controlPanel, "S Layer Count", wxString::FromUTF8(std::to_string(Defaults::SpecularLayerCount).c_str()), txtSpecularLayerCount), 1, wxEXPAND | wxALL, 2);
    specularSizer->Add(createLabeledTextField(controlPanel, "S Radial Count", wxString::FromUTF8(std::to_string(Defaults::SpecularRadialCount).c_str()), txtSpecularRadialCount), 1, wxEXPAND | wxALL, 2);
    
    mainSizer->Add(specularSizer, 0, wxEXPAND | wxALL, 2);

    controlSizer->Add(mainSizer, 0, wxEXPAND | wxALL, 2);

    // Przyciski renderowania
    wxButton* renderButton = new wxButton(controlPanel, wxID_ANY, wxT("Render"));
    controlSizer->Add(renderButton, 0, wxALL | wxEXPAND, 2);
    renderButton->Bind(wxEVT_BUTTON, &GUIManager::onClickRender, this);
}


void GUIManager::setupCameraControls(wxSizer* controlSizer, wxPanel* controlPanel) {
    wxStaticBoxSizer* cameraSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxT("Camera settings"));

    wxString wxDefPosX = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosCamX, 2).c_str());
    wxString wxDefPosY = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosCamY, 2).c_str());
    wxString wxDefPosZ = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosCamZ, 2).c_str());
    wxBoxSizer* positionSizer = new wxBoxSizer(wxHORIZONTAL);

    // Pozycje
    positionSizer->Add(createLabeledTextField(controlPanel, "Pos X", wxDefPosX, txtCamPosX), 1, wxEXPAND | wxALL, 0);
    positionSizer->Add(createLabeledTextField(controlPanel, "Pos Y", wxDefPosY, txtCamPosY), 1, wxEXPAND | wxALL, 0);
    positionSizer->Add(createLabeledTextField(controlPanel, "Pos Z", wxDefPosZ, txtCamPosZ), 1, wxEXPAND | wxALL, 0);
    cameraSettingsSizer->Add(positionSizer, 0, wxEXPAND | wxALL, 0);

    // Rotacja i FOV
    wxString wxDefFov = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Fov, 2).c_str());
    wxString wxDefRotX = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::RotCamX, 2).c_str());
    wxString wxDefRotY = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::RotCamY, 2).c_str());

    wxBoxSizer* rotationSizer = new wxBoxSizer(wxHORIZONTAL);
    rotationSizer->Add(createLabeledTextField(controlPanel, "FOV", wxDefFov, txtCamFov), 1, wxEXPAND | wxALL, 0);
    rotationSizer->Add(createLabeledTextField(controlPanel, "Rot X", wxDefRotX, txtCamRotX), 1, wxEXPAND | wxALL,0);
    rotationSizer->Add(createLabeledTextField(controlPanel, "Rot Y", wxDefRotY, txtCamRotY), 1, wxEXPAND | wxALL, 0);
    cameraSettingsSizer->Add(rotationSizer, 0, wxEXPAND | wxALL, 0);


    controlSizer->Add(cameraSettingsSizer, 0, wxEXPAND | wxALL, 0);
}


// Funkcja tworz¹ca ustawienia dla dwóch œwiate³
void GUIManager::setupLightControls(wxSizer* controlSizer, wxPanel* controlPanel) {
    wxStaticBoxSizer* lightSettingsSizer1 = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxString::Format("Light 1 settings"));


    wxString wxDefPos1X = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightX, 2).c_str());
    wxString wxDefPos1Y = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightY, 2).c_str());
    wxString wxDefPos1Z = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightZ, 2).c_str());

    // Pozycje
    wxBoxSizer* positionSizer1 = new wxBoxSizer(wxHORIZONTAL);
    positionSizer1->Add(createLabeledTextField(controlPanel, "Pos X", wxDefPos1X, txtLight1PosX), 1, wxEXPAND | wxALL, 0);
    positionSizer1->Add(createLabeledTextField(controlPanel, "Pos Y", wxDefPos1Y, txtLight1PosY), 1, wxEXPAND | wxALL, 0);
    positionSizer1->Add(createLabeledTextField(controlPanel, "Pos Z", wxDefPos1Z, txtLight1PosZ), 1, wxEXPAND | wxALL, 0);
    lightSettingsSizer1->Add(positionSizer1, 0, wxEXPAND | wxALL, 0);


    wxString wxDef1Intensity = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::IntensityLight, 2).c_str());

    // Intensywnoœæ
    lightSettingsSizer1->Add(createLabeledTextField(controlPanel, "Light Intensity", wxDef1Intensity, txtLight1Int), 1, wxEXPAND | wxALL, 0);

    controlSizer->Add(lightSettingsSizer1, 0, wxEXPAND | wxALL, 0);

    wxStaticBoxSizer* lightSettingsSizer2 = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxString::Format("Light 2 settings"));


    wxString wxDefPos2X = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightX, 2).c_str());
    wxString wxDefPos2Y = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightY, 2).c_str());
    wxString wxDefPos2Z = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::PosLightZ, 2).c_str());

    // Pozycje
    wxBoxSizer* positionSizer2 = new wxBoxSizer(wxHORIZONTAL);
    positionSizer2->Add(createLabeledTextField(controlPanel, "Pos X", wxDefPos2X, txtLight2PosX), 1, wxEXPAND | wxALL, 0);
    positionSizer2->Add(createLabeledTextField(controlPanel, "Pos Y", wxDefPos2Y, txtLight2PosY), 1, wxEXPAND | wxALL, 0);
    positionSizer2->Add(createLabeledTextField(controlPanel, "Pos Z", wxDefPos2Z, txtLight2PosZ), 1, wxEXPAND | wxALL, 0);
    lightSettingsSizer2->Add(positionSizer2, 0, wxEXPAND | wxALL, 0);


    wxString wxDef2Intensity = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::IntensityLight, 2).c_str());

    // Intensywnoœæ
    lightSettingsSizer2->Add(createLabeledTextField(controlPanel, "Light Intensity", wxDef2Intensity, txtLight2Int), 1, wxEXPAND | wxALL, 0);

    controlSizer->Add(lightSettingsSizer2, 0, wxEXPAND | wxALL, 0);
}

void GUIManager::setupGeometryControls(wxSizer* controlSizer, wxPanel* controlPanel) {
    wxStaticBoxSizer* meshSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxT("Material1"));


    wxString wxDiffuse1 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Diffuse, 2).c_str());
    wxString wxSpecular1 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Specular, 2).c_str());
    wxString wxRoughness1 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Roughness, 2).c_str());


    wxBoxSizer* materialSizer = new wxBoxSizer(wxHORIZONTAL);
    materialSizer->Add(createLabeledTextField(controlPanel, "Diffuse", wxDiffuse1, txtDiffuse1), 1, wxEXPAND | wxALL, 0);
    materialSizer->Add(createLabeledTextField(controlPanel, "Specular", wxSpecular1, txtSpecular1), 1, wxEXPAND | wxALL, 0);
    materialSizer->Add(createLabeledTextField(controlPanel, "Roughness", wxRoughness1, txtRoughness1), 1, wxEXPAND | wxALL, 0);
    meshSettingsSizer->Add(materialSizer, 0, wxEXPAND | wxALL, 0);


    controlSizer->Add(meshSettingsSizer, 0, wxEXPAND | wxALL, 0);


    wxButton* loadObjButton = new wxButton(controlPanel, wxID_ANY, wxT("Load .obj mesh 1"));
    controlSizer->Add(loadObjButton, 0, wxALL | wxEXPAND, 0);
    loadObjButton->Bind(wxEVT_BUTTON, &GUIManager::onClickLoadObjMesh, this);
}


void GUIManager::setupGeometry2Controls(wxSizer* controlSizer, wxPanel* controlPanel) {
    wxStaticBoxSizer* meshSettingsSizer = new wxStaticBoxSizer(wxVERTICAL, controlPanel, wxT("Material 2"));


    wxString wxDiffuse2 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Diffuse, 2).c_str());
    wxString wxSpecular2 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Specular, 2).c_str());
    wxString wxRoughness2 = wxString::FromUTF8(StringUtils::to_string_with_precision(Defaults::Roughness, 2).c_str());


    wxBoxSizer* materialSizer = new wxBoxSizer(wxHORIZONTAL);
    materialSizer->Add(createLabeledTextField(controlPanel, "Diffuse", wxDiffuse2, txtDiffuse2), 1, wxEXPAND | wxALL, 0);
    materialSizer->Add(createLabeledTextField(controlPanel, "Specular", wxSpecular2, txtSpecular2), 1, wxEXPAND | wxALL, 0);
    materialSizer->Add(createLabeledTextField(controlPanel, "Roughness", wxRoughness2, txtRoughness2), 1, wxEXPAND | wxALL, 0);
    meshSettingsSizer->Add(materialSizer, 0, wxEXPAND | wxALL, 0);


    controlSizer->Add(meshSettingsSizer, 0, wxEXPAND | wxALL, 0);


    wxButton* loadObjButton = new wxButton(controlPanel, wxID_ANY, wxT("Load .obj mesh 2"));
    controlSizer->Add(loadObjButton, 0, wxALL | wxEXPAND, 0);
    loadObjButton->Bind(wxEVT_BUTTON, &GUIManager::onClickLoadObjMesh2, this);
}

GUIManager::GUIManager(const wxString& title, ApplicationManager* _appManager, SceneManager* _sceneManager, RayTracer* _rayTracer)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(Defaults::WindowResolutionWidth, Defaults::WindowResolutionHeight)) {

    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    glPanel = new OpenGLRenderer(this);

    auto* controlPanel = new wxPanel(this);
    controlPanel->SetBackgroundColour(*wxWHITE);

    appManager = _appManager;
    sceneManager = _sceneManager;
    rayTracer = _rayTracer;

    sizer->Add(glPanel, 3, wxEXPAND);
    sizer->Add(controlPanel, 1, wxEXPAND);


    
    controlPanel->SetMinSize(wxSize(300, Defaults::WindowResolutionHeight)); 
    controlPanel->SetMaxSize(wxSize(300, Defaults::WindowResolutionHeight));

    wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);

    setupGeneralControls(controlSizer, controlPanel);
    setupCameraControls(controlSizer, controlPanel);
    setupLightControls(controlSizer, controlPanel);
    setupGeometryControls(controlSizer, controlPanel);
    setupGeometry2Controls(controlSizer, controlPanel);

    controlPanel->SetSizer(controlSizer);
    controlPanel->Layout();

    SetSizer(sizer);
    Layout();
}


 void GUIManager::onClickRender(wxCommandEvent& event) {

     Scene& scene = sceneManager->getCurrentScene();

     RenderSettings& renderSettings = sceneManager->getRenderSettings();

     updateSceneData(scene, renderSettings);

     appManager->renderAndDisplay(*sceneManager, *rayTracer, *glPanel);
 }

 wxBoxSizer* GUIManager::createLabeledTextField(wxPanel* parent, const wxString& label, const wxString& defaultValue, wxTextCtrl*& outField) {
     wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
     wxStaticText* staticLabel = new wxStaticText(parent, wxID_ANY, label);
     outField = new wxTextCtrl(parent, wxID_ANY, defaultValue);
     outField->SetMinSize(wxSize(-1, 20));
     outField->SetMaxSize(wxSize(65, -1));

     sizer->Add(staticLabel, 0, wxBOTTOM, 0);
     sizer->Add(outField, 1, wxEXPAND | wxALL, 0);

     return sizer;
 }


void GUIManager::updateSceneData(Scene& scene, RenderSettings& renderSettings) {
    
    // Przypisanie zebranych danych do obiektów

    glm::vec3 cameraPos;
    glm::vec3 cameraRot;
    
    double cameraFov;

    glm::vec3 light1Pos;
    glm::vec3 light1Rot;
    double light1Int;

    glm::vec3 light2Pos;
    glm::vec3 light2Rot;
    double light2Int;

    double tempDouble;

    txtMaxDepth->GetValue().ToDouble(&tempDouble);
    int maxDepth = static_cast<float>(tempDouble);

    txtCamPosX->GetValue().ToDouble(&tempDouble);
    cameraPos.x = static_cast<float>(tempDouble);

    txtCamPosY->GetValue().ToDouble(&tempDouble);
    cameraPos.y = static_cast<float>(tempDouble);

    txtCamPosZ->GetValue().ToDouble(&tempDouble);
    cameraPos.z = static_cast<float>(tempDouble);

    txtCamRotX->GetValue().ToDouble(&tempDouble);
    cameraRot.x = static_cast<float>(tempDouble);

    txtCamRotY->GetValue().ToDouble(&tempDouble);
    cameraRot.y = static_cast<float>(tempDouble);

    txtCamFov->GetValue().ToDouble(&cameraFov);


    txtLight1PosX->GetValue().ToDouble(&tempDouble);
    light1Pos.x = static_cast<float>(tempDouble);

    txtLight1PosY->GetValue().ToDouble(&tempDouble);
    light1Pos.y = static_cast<float>(tempDouble);

    txtLight1PosZ->GetValue().ToDouble(&tempDouble);
    light1Pos.z = static_cast<float>(tempDouble);


    txtLight2PosX->GetValue().ToDouble(&tempDouble);
    light2Pos.x = static_cast<float>(tempDouble);

    txtLight2PosY->GetValue().ToDouble(&tempDouble);
    light2Pos.y = static_cast<float>(tempDouble);

    txtLight2PosZ->GetValue().ToDouble(&tempDouble);
    light2Pos.z = static_cast<float>(tempDouble);

    txtLight1Int->GetValue().ToDouble(&tempDouble);
    light1Int = static_cast<float>(tempDouble);
    txtLight2Int->GetValue().ToDouble(&tempDouble);
    light2Int = static_cast<float>(tempDouble);


    txtDiffuse1->GetValue().ToDouble(&tempDouble);
    float matDiffuse = static_cast<float>(tempDouble);
    txtSpecular1->GetValue().ToDouble(&tempDouble);
    float matSpecular = static_cast<float>(tempDouble);
    txtRoughness1->GetValue().ToDouble(&tempDouble);
    float matRoughness = static_cast<float>(tempDouble);


    txtDiffuse2->GetValue().ToDouble(&tempDouble);
    float matDiffuse2 = static_cast<float>(tempDouble);
    txtSpecular2->GetValue().ToDouble(&tempDouble);
    float matSpecular2 = static_cast<float>(tempDouble);
    txtRoughness2->GetValue().ToDouble(&tempDouble);
    float matRoughness2 = static_cast<float>(tempDouble);

    txtIndirectDiffuse->GetValue().ToDouble(&tempDouble);
    float indirectDiffuse = static_cast<float>(tempDouble);

    txtIndirectSpecular->GetValue().ToDouble(&tempDouble);
    float indirectSpecular = static_cast<float>(tempDouble);

    int tempInt = 0;
    txtResWidth->GetValue().ToInt(&tempInt);
    int resWidth = static_cast<int>(tempInt);
    txtResHeight->GetValue().ToInt(&tempInt);
    int resHeight = static_cast<int>(tempInt);

    txtDiffuseLayerCount->GetValue().ToInt(&tempInt);
    int diffuseLayerCount = static_cast<int>(tempInt);
    txtDiffuseRadialCount->GetValue().ToInt(&tempInt);
    int diffuseRadialCount = static_cast<int>(tempInt);
    txtSpecularLayerCount->GetValue().ToInt(&tempInt);
    int specularLayerCount = static_cast<int>(tempInt);
    txtSpecularRadialCount->GetValue().ToInt(&tempInt);
    int specularRadialCount = static_cast<int>(tempInt);


    scene.clearMeshes();


    if (objFilePath1 != "") {
        string objFilePathS(objFilePath1.ToUTF8());

        Mesh newMesh = ObjLoader::loadObj(objFilePathS);

        Material mat = Material(matDiffuse, matSpecular, matRoughness);

        newMesh.setMaterial(mat);

        scene.addMesh(newMesh);
    }

    if (objFilePath2 != "") {
        string objFilePathS2(objFilePath2.ToUTF8());

        Mesh newMesh2 = ObjLoader::loadObj(objFilePathS2);

        Material mat2 = Material(matDiffuse2, matSpecular2, matRoughness2);

        newMesh2.setMaterial(mat2);

        scene.addMesh(newMesh2);
    }


    Camera newCam = Camera(cameraPos, cameraRot, cameraFov, resWidth, resHeight);

    scene.setCamera(newCam);

    Light newLight1 = Light(light1Pos, light1Int);
    Light newLight2 = Light(light2Pos, light2Int);

    scene.clearLights();
    scene.addLight(newLight1);
    scene.addLight(newLight2);


    renderSettings.setResolution(resWidth, resHeight);
    renderSettings.setMaxDepth(maxDepth);
    renderSettings.setIndirectDiffuse(indirectDiffuse);
    renderSettings.setIndirectSpecular(indirectSpecular);
    renderSettings.setDiffuseLayerCount(diffuseLayerCount);
    renderSettings.setDiffuseRadialCount(diffuseRadialCount);
    renderSettings.setSpecularLayerCount(specularLayerCount);
    renderSettings.setSpecularRadialCount(specularRadialCount);
}


void GUIManager::onClickLoadObjMesh(wxCommandEvent& event) {
    wxFileDialog openFileDialog(
        this, _("Wybierz plik .obj"), "", "",
        "OBJ Files (*.obj)|*.obj",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK) {

        objFilePath1 = openFileDialog.GetPath();
        wxLogMessage("Wybrano plik: %s", objFilePath1);
    }
}

void GUIManager::onClickLoadObjMesh2(wxCommandEvent& event) {

    wxFileDialog openFileDialog(
        this, _("Wybierz plik .obj"), "", "",
        "OBJ Files (*.obj)|*.obj",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);


    if (openFileDialog.ShowModal() == wxID_OK) {
        objFilePath2 = openFileDialog.GetPath();
           wxLogMessage("Wybrano plik: %s", objFilePath2);
    }
}