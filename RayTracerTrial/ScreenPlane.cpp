#include "ScreenPlane.h"
#include <glm/geometric.hpp>
#include <algorithm>

ScreenPlane::ScreenPlane() {
    
    up = glm::vec3(0, -1, 0);
    right = glm::vec3(1, 0, 0);
    resolutionWidth = 128;
    resolutionHeight = 128;
}

ScreenPlane::ScreenPlane(const glm::vec3& _up, const glm::vec3& _right, int _resolutionWidth, int _resolutionHeight) {
    
    up = _up;
    right = _right;
    resolutionWidth = _resolutionWidth;
    resolutionHeight = _resolutionHeight;
}

const glm::vec3& ScreenPlane::getUp() const {
    return up;
}

const glm::vec3& ScreenPlane::getRight() const {
    return right;
}

int ScreenPlane::getResolutionWidth() const {
    return resolutionWidth;
}

int ScreenPlane::getResolutionHeight() const {
    return resolutionHeight;
}

void ScreenPlane::setUp(const glm::vec3& _up) {
    up = _up;
}

void ScreenPlane::setRight(const glm::vec3& _right) {
    right = _right;
}

void ScreenPlane::setResolutionWidth(int _resolutionWidth) {
    resolutionWidth = _resolutionWidth;
}

void ScreenPlane::setResolutionHeight(int _resolutionHeight) {
    resolutionHeight = _resolutionHeight;
}
glm::vec3 ScreenPlane::calculateRayDirection(int x, int y, float distance, glm::vec3 dir, int screenWidth, int screenHeight) const {
   
    float u = (2.0f * (float)x / screenWidth - 1.0f);
    float v = (2.0f * (float)y / screenHeight - 1.0f);

    glm::vec3 direction = u * right + v * up + distance * dir;

    return glm::normalize(direction);
}
