#ifndef VECTOR_UTILS_H
#define VECTOR_UTILS_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <vector>

class VectorUtils {
public:
    static std::vector<glm::vec3> generateRadialOffsets(int count, float angleOffset, const glm::vec3& up);
    static std::vector<float> generateLinearRange(float start, float end, int numElements);
};

#endif