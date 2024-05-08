#include <vector>
#include <memory>
#include "BVHNode.h"
#include "Triangle.h"
#include "Ray.h"

class BVH {
public:
    BVH();
    void build(const std::vector<Triangle>& triangles);
    bool intersect(const Ray& ray, float& t, glm::vec3& normal) const;

private:
    std::unique_ptr<BVHNode> root;

    std::unique_ptr<BVHNode> buildRecursive(std::vector<Triangle>& triangles, int start, int end);
};
