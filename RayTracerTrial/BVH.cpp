#include "BVH.h"
#include <algorithm>

BVH::BVH() : root(nullptr) {}

void BVH::build(const std::vector<Triangle>& triangles) {
    std::vector<Triangle> sortedTriangles = triangles;
    root = buildRecursive(sortedTriangles, 0, sortedTriangles.size());
}

std::unique_ptr<BVHNode> BVH::buildRecursive(std::vector<Triangle>& triangles, int start, int end) {
    auto node = std::make_unique<BVHNode>();


    if (end - start <= 2) {
        std::vector<Triangle> leafTriangles(triangles.begin() + start, triangles.begin() + end);
        node->setLeaf(leafTriangles);
    }
    else {

        int axis = 0; 
        std::sort(triangles.begin() + start, triangles.begin() + end, [axis](const Triangle& a, const Triangle& b) {
            return a.getCentroid()[axis] < b.getCentroid()[axis];
            });


        int mid = start + (end - start) / 2;
        node->setChildren(buildRecursive(triangles, start, mid), buildRecursive(triangles, mid, end));
    }


    node->computeBoundingBox(triangles, start, end);

    return node;
}

bool BVH::intersect(const Ray& ray, float& t, glm::vec3& normal) const {
    if (!root) {
        return false;
    }

    return root->intersect(ray, t, normal);
}
