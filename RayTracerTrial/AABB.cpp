#include "AABB.h"

AABB::AABB() : min(glm::vec3(0)), max(glm::vec3(0)) {}

AABB::AABB(const glm::vec3& _min, const glm::vec3& _max) : min(_min), max(_max) {}

void AABB::expand(const AABB& other) {

    min = glm::vec3(std::min(min.x, other.min.x),
        std::min(min.y, other.min.y),
        std::min(min.z, other.min.z));

    max = glm::vec3(std::max(max.x, other.max.x),
        std::max(max.y, other.max.y),
        std::max(max.z, other.max.z));
}
bool AABB::intersect(const Ray& ray, float& t) const {
    float tMin = (min.x - ray.getOrigin().x) / ray.getDirection().x;
    float tMax = (max.x - ray.getOrigin().x) / ray.getDirection().x;
    if (tMin > tMax) std::swap(tMin, tMax);

    float tMinY = (min.y - ray.getOrigin().y) / ray.getDirection().y;
    float tMaxY = (max.y - ray.getOrigin().y) / ray.getDirection().y;
    if (tMinY > tMaxY) std::swap(tMinY, tMaxY);

    if ((tMin > tMaxY) || (tMinY > tMax)) return false;
    if (tMinY > tMin) tMin = tMinY;
    if (tMaxY < tMax) tMax = tMaxY;

    float tMinZ = (min.z - ray.getOrigin().z) / ray.getDirection().z;
    float tMaxZ = (max.z - ray.getOrigin().z) / ray.getDirection().z;
    if (tMinZ > tMaxZ) std::swap(tMinZ, tMaxZ);

    if ((tMin > tMaxZ) || (tMinZ > tMax)) return false;
    if (tMinZ > tMin) tMin = tMinZ;
    if (tMaxZ < tMax) tMax = tMaxZ;
    /*
    glm::vec3 origin = ray.getOrigin();
    if (origin.x >= min.x && origin.x <= max.x &&
        origin.y >= min.y && origin.y <= max.y &&
        origin.z >= min.z && origin.z <= max.z) {
        t = 0.0f;
        return true;
    }
    */
    t = tMin;

    return true;
}

