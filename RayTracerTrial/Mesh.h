#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/vec3.hpp>
#include "Triangle.h"
#include "Ray.h"
#include "Material.h"
#include "BVH.h"

class Mesh {
public:

    Mesh();


    Mesh(const Material& material);



    Mesh(const Mesh& other);


    Mesh& operator=(const Mesh& other);


    void setMaterial(const Material& material);


    const Material& getMaterial() const;


    void addTriangle(const Triangle& triangle);


    const std::vector<Triangle>& getTriangles() const;


    static Mesh createCube(const glm::vec3& position, float size);


    static Mesh createPlane(const glm::vec3& position, float width, float length);


    bool intersects(const Ray& ray, float& dist, glm::vec3& norm) const;
    void buildBVH();

private:
    std::vector<Triangle> triangles;    
    Material material;
    BVH bvh;
};

#endif 
