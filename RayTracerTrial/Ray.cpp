#include "Ray.h"
#include <glm/geometric.hpp>

Ray::Ray() {

    origin = glm::vec3 (0, 0, 0);
    direction = glm::vec3(0, 0, 1);
}

Ray::Ray(const glm::vec3& _origin, const glm::vec3& _dir) {

    origin = _origin;
    direction = _dir;
}

const glm::vec3& Ray::getOrigin() const {
    return origin;
}

const glm::vec3& Ray::getDirection() const {
    return direction;
}

void Ray::setOrigin(const glm::vec3& _origin) {
    origin = origin;
}

void Ray::setDirection(const glm::vec3& _direction) {
    direction = direction;
}
