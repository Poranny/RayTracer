#include <GL/glew.h>
#include "OpenGLRenderer.h"
#include "RayTracer.h"
#include <cstdlib>
#include <memory>
#include "Defaults.h"

OpenGLRenderer::OpenGLRenderer(wxWindow* parent) : wxGLCanvas(parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas")) {

    windowParent = parent;
    m_context = new wxGLContext(this);
    m_context->SetCurrent(*this);

    glewInit();

    textureWidth = Defaults::ResolutionWidth;
    textureHeight = Defaults::ResolutionHeight;
    textureData = new unsigned char[textureWidth * textureHeight * 3];


    Bind(wxEVT_PAINT, &OpenGLRenderer::onPaint, this);
    Bind(wxEVT_SIZE, &OpenGLRenderer::onResize, this);
}


void OpenGLRenderer::display(MyTexture& texToDisplay) {

    m_context->SetCurrent(*this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int width, height;
    GetClientSize(&width, &height);
    glViewport(0, 0, width, height);

    textureData = texToDisplay.getRawData();
    textureWidth = texToDisplay.getWidth();
    textureHeight = texToDisplay.getHeight();
    
    int maxTextureSize;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    SwapBuffers();
    
    Refresh();
}

void OpenGLRenderer::onResize(wxSizeEvent& event) {
    Refresh();
}

void OpenGLRenderer::onPaint(wxPaintEvent& event) {
  
    repaint();
}

void OpenGLRenderer::repaint() {

    m_context->SetCurrent(*this);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width, height;
    GetClientSize(&width, &height);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(width, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(width, height);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    SwapBuffers();
}

OpenGLRenderer::~OpenGLRenderer() {
    delete m_context;
  //  delete[] textureData; --- prowadzi do exception podczas wy³¹czania programu
}