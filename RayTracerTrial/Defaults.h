
#ifndef DEFAULTS_H
#define DEFAULTS_H

class Defaults {
public:
    static const int WindowResolutionWidth;
    static const int WindowResolutionHeight;

    static const int ResolutionWidth;
    static const int ResolutionHeight;
    static const int MaxDepth;

    static const float PosCamX;
    static const float PosCamY;
    static const float PosCamZ;
    static const float RotCamX;
    static const float RotCamY;

    static const float PosLightX;
    static const float PosLightY;
    static const float PosLightZ;

    static const float IntensityLight;

    static const float Fov;

    static const float Diffuse;
    static const float Specular;
    static const float Roughness;
    static const float IndirectDiffuse;
    static const float IndirectSpecular;

    static const int DiffuseLayerCount;
    static const int DiffuseRadialCount;

    static const int SpecularLayerCount;
    static const int SpecularRadialCount;

    static const float BgColor;
};
#endif