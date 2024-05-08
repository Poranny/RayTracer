#include "Mesh.h"
#include "tiny_obj_loader.h"

Mesh::Mesh() {

    material = Material();
}


Mesh::Mesh(const Material& _material) {

    material = _material;
}


void Mesh::setMaterial(const Material& material) {
    this->material = material;
}


const Material& Mesh::getMaterial() const {
    return material;
}


void Mesh::addTriangle(const Triangle& triangle) {
    triangles.push_back(triangle);
}


const std::vector<Triangle>& Mesh::getTriangles() const {
    return triangles;
}


bool Mesh::intersects(const Ray& ray, float& t, glm::vec3& normal) const {
    return bvh.intersect(ray, t, normal);

}


Mesh::Mesh(const Mesh& other) : material(other.material), triangles(other.triangles) {
    bvh.build(triangles); 
}


Mesh& Mesh::operator=(const Mesh& other) {
    if (this != &other) {
        material = other.material;
        triangles = other.triangles;
        bvh.build(triangles); 
    }
    return *this;
}

void Mesh::buildBVH() {
    bvh.build(triangles);
}

/*
* 
bool Mesh::intersects(const Ray& ray, float& dist, glm::vec3& normal) const {

    float closestDist = -1;
    float currentDist = 0;

    glm::vec3 currentNormal;
    glm::vec3 closestNormal;

    bool foundIntersection = false;

    for (const auto& triangle : triangles) {
        if (triangle.intersects(ray, currentDist, currentNormal)) {
            if (closestDist == -1 || currentDist < closestDist) {
                closestDist = currentDist;
                closestNormal = currentNormal;
            }

            dist = closestDist;
            normal = closestNormal;

            foundIntersection = true;
        }
    }


    return foundIntersection;
}
*/