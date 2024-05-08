#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/glew.h>
#include <wx/wx.h>
#include <wx/glcanvas.h>
#include "MyTexture.h"


class OpenGLRenderer : public wxGLCanvas {
public:
    OpenGLRenderer(wxWindow* parent);
    ~OpenGLRenderer();

    void display(MyTexture& texToDisplay);

private:
    wxWindow* windowParent;
    wxGLContext* m_context; 
    unsigned char* textureData; 
    int textureWidth, textureHeight; 

    GLuint textureID; 
    void onPaint(wxPaintEvent& event);
    void onResize(wxSizeEvent& event);
    void repaint();
};


#endif
