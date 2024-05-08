#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/vec3.hpp>

class Material {
public:
    Material();  
    Material(float _diffuse, float _specular, float _roughness);

    float getDiffuse() const;
    float getSpecular() const;
    float getRoughness() const;

    void setDiffuse(float _diffuse);
    void setSpecular(float _specular);
    void setRoughness(float _roughness);

private:
    float diffuse;   
    float specular;  
    float roughness;  
};

#endif 
