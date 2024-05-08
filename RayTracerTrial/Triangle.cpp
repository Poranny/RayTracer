#include "Triangle.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>

Triangle::Triangle() {

    v0 = glm::vec3(0, 0, 0);
    v1 = glm::vec3(0, 1, 0);
    v2 = glm::vec3(0, 0, 1);

    normalV0 = glm::vec3(1, 0, 0);
    normalV1 = glm::vec3(0, 1, 0);
    normalV2 = glm::vec3(0, 0, 1);

    normal = glm::normalize(normalV0 + normalV1 + normalV2);
}

Triangle::Triangle(const glm::vec3& _v0, const glm::vec3& _v1, const glm::vec3& _v2, const glm::vec3& _normalV0, const glm::vec3& _normalV1, const glm::vec3& _normalV2) {

    v0 = _v0;
    v1 = _v1;
    v2 = _v2;

    normalV0 = _normalV0;
    normalV1 = _normalV1;
    normalV2 = _normalV2;

    normal = glm::normalize(normalV0 + normalV1 + normalV2);
}

AABB Triangle::getBoundingBox() const {
    glm::vec3 minCoord = glm::min(glm::min(v0, v1), v2);
    glm::vec3 maxCoord = glm::max(glm::max(v0, v1), v2);
    return AABB(minCoord, maxCoord);
}

glm::vec3 Triangle::getCentroid() const {
    return (v0 + v1 + v2) / 3.0f;
}

bool Triangle::intersects(const Ray& ray, float& dist, glm::vec3& norm) const {

    const float EPSILON = 0.0000001;


    glm::vec3 edge1 = v1 - v0;
    glm::vec3 edge2 = v2 - v0;


    glm::vec3 h = glm::cross(ray.getDirection(), edge2);
    float a = glm::dot(edge1, h);


    if (a > -EPSILON && a < EPSILON) {
        return false;
    }

    float f = 1.0f / a;
    glm::vec3 s = ray.getOrigin() - v0;
    float u = f * glm::dot(s, h);


    if (u < 0.0f || u > 1.0f) {
        return false;
    }

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(ray.getDirection(), q);

    if (v < 0.0f || u + v > 1.0f) {
        return false;
    }


    dist = f * glm::dot(edge2, q);

    norm = normal;
    return dist > EPSILON;
}
