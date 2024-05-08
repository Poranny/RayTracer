#ifndef AABB_H
#define AABB_H

#include <glm/vec3.hpp>
#include <algorithm> 
#include "Ray.h"

class AABB {
public:
    AABB();
    AABB(const glm::vec3& _min, const glm::vec3& _max);

    void expand(const AABB& other);


    bool intersect(const Ray& ray, float& t) const;

private:
    glm::vec3 min;
    glm::vec3 max;
};

#endif 
