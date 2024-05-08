#include "Camera.h"

Camera::Camera() {
    
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    fov = 50;

    eye = Eye();
    screenPlane = ScreenPlane();

}

Camera::Camera(const glm::vec3& _position, const glm::vec3& _rotation, float _fov, int _screenWidth, int _screenHeight) {
    position = _position;
    rotation = _rotation;
    fov = _fov;

    glm::vec3 direction = computeDirectionFromEuler(rotation);
    eye = Eye(position, direction, 100.0f / fov);

    int minRes = glm::min(_screenWidth, _screenHeight);
    float aspectRatio = (float)_screenWidth / (float)_screenHeight;

    glm::vec3 up = glm::vec3(0, -1, 0);
    glm::vec3 right = glm::normalize(glm::cross(direction, up));

    up = glm::cross(right, direction);

    screenPlane = ScreenPlane(up, right * aspectRatio, _screenWidth, _screenHeight);
}

glm::vec3 Camera::computeDirectionFromEuler(const glm::vec3& eulerAngles) {
    float pitch = glm::radians(eulerAngles.x);
    float yaw = glm::radians(eulerAngles.y);

    glm::vec3 direction;
    direction.x = cos(pitch) * cos(yaw);
    direction.y = sin(pitch);
    direction.z = cos(pitch) * sin(yaw);

    return glm::normalize(direction);
}


const glm::vec3& Camera::getPosition() const {
    return position;
}

const glm::vec3& Camera::getRotation() const {
    return rotation;
}

float Camera::getFov() const {
    return fov;
}

const Eye& Camera::getEye() const {
    return eye;
}

const ScreenPlane& Camera::getScreenPlane() const {
    return screenPlane;
}

void Camera::setPosition(const glm::vec3& position) {
    this->position = position;
    eye.setPosition(position);
}

void Camera::setRotation(const glm::vec3& rotation) {
    this->rotation = rotation;
    eye.setDirection(rotation);
}

void Camera::setFov(float fov) {
    this->fov = fov;
}
