#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <memory>
#include <vector>
#include "Triangle.h"
#include "Ray.h"
#include "AABB.h"

class BVHNode {
public:
    BVHNode();


    void setLeaf(const std::vector<Triangle>& tris);


    void setChildren(std::unique_ptr<BVHNode> left, std::unique_ptr<BVHNode> right);


    void computeBoundingBox(const std::vector<Triangle>& triangles, int start, int end);


    bool intersect(const Ray& ray, float& t, glm::vec3& normal) const;

private:
    std::unique_ptr<BVHNode> leftChild, rightChild;
    AABB boundingBox;
    std::vector<Triangle> leafTriangles;
    bool isLeaf;
};

#endif 
