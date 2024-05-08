
#include "VectorUtils.h"
#include <stdexcept>

std::vector<glm::vec3> VectorUtils::generateRadialOffsets(int count, float angleOffset, const glm::vec3& up) {
    std::vector<glm::vec3> offsets;

    if (angleOffset < 0 || angleOffset >(glm::pi<float>() / 2.0)) {
        throw std::runtime_error("Angle offset has to be a value between 0 and 90 degrees.");
    }

    angleOffset = (glm::pi<float>() / 2.0) - angleOffset;

    glm::vec3 normalizedUp = glm::normalize(up);

    glm::vec3 baseVec;
    if (normalizedUp == glm::vec3(0, 1, 0) || normalizedUp == glm::vec3(0, -1, 0)) {
        baseVec = glm::vec3(1, 0, 0);
    }
    else {
        baseVec = glm::normalize(glm::cross(normalizedUp, glm::vec3(0, 1, 0)));
    }

    float angleIncrement = glm::two_pi<float>() / count;

    for (int i = 0; i < count; ++i) {
        float angleAroundUp = angleIncrement * i;
        glm::vec3 rotatedVec = glm::rotate(baseVec, angleAroundUp, normalizedUp);
        glm::vec3 finalVec = glm::rotate(rotatedVec, angleOffset, glm::cross(rotatedVec, normalizedUp));

        offsets.push_back(glm::normalize(finalVec));
    }

    return offsets;
}

std::vector<float> VectorUtils::generateLinearRange(float start, float end, int numElements) {
    std::vector<float> values(numElements);
    float step = (end - start) / (numElements - 1);

    for (int i = 0; i < numElements; ++i) {
        values[i] = start + step * i;
    }

    return values;
}
