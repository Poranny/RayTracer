#ifndef EYE_H
#define EYE_H

#include <glm/vec3.hpp>

class Eye {
public:
    Eye();

    Eye(const glm::vec3& position, const glm::vec3& direction, float distance);

    const glm::vec3& getPosition() const;
    const glm::vec3& getDirection() const;
    float getDistance() const;

    void setPosition(const glm::vec3& position);
    void setDirection(const glm::vec3& direction);
    void setDistance(float distance);

private:
    glm::vec3 position;
    glm::vec3 direction;
    float distance;
};

#endif 
