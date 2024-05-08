#include "BVHNode.h"

BVHNode::BVHNode() : leftChild(nullptr), rightChild(nullptr), isLeaf(false) {}

void BVHNode::setLeaf(const std::vector<Triangle>& tris) {
    isLeaf = true;
    leafTriangles = tris;
}

void BVHNode::setChildren(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right) {
    leftChild = std::move(left);
    rightChild = std::move(right);
    isLeaf = false;
}

void BVHNode::computeBoundingBox(const std::vector<Triangle>& triangles, int start, int end) {
    boundingBox = AABB(triangles[start].getBoundingBox());
    for (int i = start + 1; i < end; ++i) {
        boundingBox.expand(triangles[i].getBoundingBox());
    }
}bool BVHNode::intersect(const Ray& ray, float& t, glm::vec3& normal) const {

    if (!boundingBox.intersect(ray, t)) {
        return false;
    }


    if (isLeaf) {
        bool found = false;
        float closestDist = std::numeric_limits<float>::max();
        for (const auto& triangle : leafTriangles) {
            float currentDist;
            glm::vec3 currentNormal;
            if (triangle.intersects(ray, currentDist, currentNormal)) {
                if (currentDist < closestDist) {
                    closestDist = currentDist;
                    normal = currentNormal;
                    found = true;
                }
            }
        }
        if (found) {
            t = closestDist;
            return true;
        }
        return false;
    }


    float tLeft = std::numeric_limits<float>::max();
    float tRight = std::numeric_limits<float>::max();
    glm::vec3 normalLeft, normalRight;

    bool hitLeft = leftChild && leftChild->intersect(ray, tLeft, normalLeft);
    bool hitRight = rightChild && rightChild->intersect(ray, tRight, normalRight);

    if (hitLeft && hitRight) {
        if (tLeft < tRight) {
            t = tLeft;
            normal = normalLeft;
        }
        else {
            t = tRight;
            normal = normalRight;
        }
        return true;
    }
    else if (hitLeft) {
        t = tLeft;
        normal = normalLeft;
        return true;
    }
    else if (hitRight) {
        t = tRight;
        normal = normalRight;
        return true;
    }

    return false;
}
