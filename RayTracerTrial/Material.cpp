#include "Material.h"


Material::Material() {

    diffuse = 1.0f;
    specular = 1.0f;
    roughness = 0.5f;
}


Material::Material(float _diffuse, float _specular, float _roughness)  {

    diffuse = _diffuse;
    specular = _specular;
    roughness = _roughness;
}
float Material::getDiffuse() const {
    return diffuse;
}

float Material::getSpecular() const {
    return specular;
}

float Material::getRoughness() const {
    return roughness;
}


void Material::setDiffuse(float _diffuse) {
    diffuse = _diffuse;
}

void Material::setSpecular(float _specular) {
    specular = _specular;
}

void Material::setRoughness(float _roughness) {
    roughness = _roughness;
}
