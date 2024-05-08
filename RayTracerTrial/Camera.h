#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Eye.h"
#include "ScreenPlane.h"

class Camera {
public:
    Camera(); 
    Camera(const glm::vec3& position, const glm::vec3& rotation, float fov, int screenWidth, int screenHeight);

    const glm::vec3& getPosition() const;
    const glm::vec3& getRotation() const;
    float getFov() const;
    const Eye& getEye() const;
    const ScreenPlane& getScreenPlane() const;

    void setPosition(const glm::vec3& position);
    void setRotation(const glm::vec3& rotation);
    void setFov(float fov);

private:
    glm::vec3 position;
    glm::vec3 rotation;
    float fov;

    Eye eye;
    ScreenPlane screenPlane;

    void initialize();
    glm::vec3 computeDirectionFromEuler(const glm::vec3& eulerAngles);
};

#endif 
