#ifndef LIGHT_H
#define LIGHT_H
#include <glm/vec3.hpp> 

class Light {
public:
    Light();
    Light(glm::vec3 _pos, float _intensity);
    ~Light();

    glm::vec3 getPos();
    float getIntensity();


private:
    glm::vec3 pos;

    float intensity;
};

#endif 
