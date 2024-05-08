#ifndef SCREENPLANE_H
#define SCREENPLANE_H

#include <glm/vec3.hpp>

class ScreenPlane {
public:
    ScreenPlane();
    
    ScreenPlane(const glm::vec3& up, const glm::vec3& right, int resolutionWidth, int resolutionHeight);

    const glm::vec3& getUp() const;
    const glm::vec3& getRight() const;
    int getResolutionWidth() const;
    int getResolutionHeight() const;

    void setUp(const glm::vec3& up);
    void setRight(const glm::vec3& right);
    void setResolutionWidth(int resolutionWidth);
    void setResolutionHeight(int resolutionHeight);


    glm::vec3 calculateRayDirection(int x, int y, float distance, glm::vec3 dir, int screenWidth, int screenHeight) const;


private:
    glm::vec3 up;
    glm::vec3 right;
    int resolutionWidth;
    int resolutionHeight;
};

#endif 
