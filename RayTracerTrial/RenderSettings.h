
#ifndef RENDER_SETTINGS_H
#define RENDER_SETTINGS_H

class RenderSettings {
public:
    RenderSettings();

    int getResolutionWidth() const;
    int getResolutionHeight() const;
    void setResolution(int _width, int _height);

    int getMaxDepth() const;
    void setMaxDepth(int _count);

    float getIndirectDiffuse() const;
    void setIndirectDiffuse(float _indirect);

    float getIndirectSpecular() const;
    void setIndirectSpecular(float _indirect);

    int getDiffuseLayerCount() const;
    void setDiffuseLayerCount(int _layer);

    int getDiffuseRadialCount() const;
    void setDiffuseRadialCount(int _radial);

    int getSpecularLayerCount() const;
    void setSpecularLayerCount(int _layer);

    int getSpecularRadialCount() const;
    void setSpecularRadialCount(int _radial);


private:
    int resolutionWidth;
    int resolutionHeight;
    int maxDepth; 

    float indirectDiffuse;
    int diffuseLayerCount;
    int diffuseRadialCount;

    float indirectSpecular;
    int specularLayerCount;
    int specularRadialCount;
};

#endif
