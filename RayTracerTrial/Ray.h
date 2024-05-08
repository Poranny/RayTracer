#ifndef RAY_H
#define RAY_H

#include <glm/vec3.hpp>

class Ray {
public:
    Ray();
    Ray(const glm::vec3& origin, const glm::vec3& dir);

    const glm::vec3& getOrigin() const;
    const glm::vec3& getDirection() const;
    void setOrigin(const glm::vec3& origin);
    void setDirection(const glm::vec3& direction);

private:
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif 
