#include "Eye.h"

Eye::Eye() {

    position = glm::vec3(0, 0, 0);
    direction = glm::vec3(0, 0, 0);
    distance = 1;
}

Eye::Eye(const glm::vec3& _position, const glm::vec3& _direction, float _distance) {

    position = _position;
    direction = _direction;
    distance = _distance;
}

const glm::vec3& Eye::getPosition() const {
    return position;
}

const glm::vec3& Eye::getDirection() const {
    return direction;
}

float Eye::getDistance() const {
    return distance;
}

void Eye::setPosition(const glm::vec3& position) {

    this->position = position;
}

void Eye::setDirection(const glm::vec3& direction) {
    this->direction = direction;
}

void Eye::setDistance(float distance) {
    this->distance = distance;
}
