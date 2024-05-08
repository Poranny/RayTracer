#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/vec3.hpp>
#include "Ray.h"
#include "AABB.h"

class Triangle {
public:
    Triangle();
    Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& _normalV0, const glm::vec3& _normalV1, const glm::vec3& _normalV2);

    AABB getBoundingBox() const;


    glm::vec3 getCentroid() const;

    bool intersects(const Ray& ray, float& t, glm::vec3& norm) const;
    

private:
    glm::vec3 v0, v1, v2;
    glm::vec3 normal;
    glm::vec3 normalV0, normalV1, normalV2; // Normalne wierzcho³ków
};

#endif
