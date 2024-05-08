#include "Light.h"

Light::Light() {

}

Light::Light(glm::vec3 _pos, float _intensity) {

    pos = _pos;
    intensity = _intensity;
}

Light::~Light() {
    
}

glm::vec3 Light::getPos() {
    return pos;
}

float Light::getIntensity() {
    return intensity;
}