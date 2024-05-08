#include "ObjLoader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <stdexcept>

Mesh ObjLoader::loadObj(const std::string& filePath) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;


    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filePath.c_str());

    if (!success) {
        throw std::runtime_error("Failed to load .obj file: " + warn + err);
    }

    Mesh mesh;


    for (const auto& shape : shapes) {
        size_t indexOffset = 0;
        for (size_t faceIdx = 0; faceIdx < shape.mesh.num_face_vertices.size(); ++faceIdx) {
            int numVerts = shape.mesh.num_face_vertices[faceIdx];


            glm::vec3 vertices[3];
            glm::vec3 normals[3];
            for (int v = 0; v < numVerts; ++v) {
                tinyobj::index_t idx = shape.mesh.indices[indexOffset + v];

                vertices[v] = {
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]
                };

                if (idx.normal_index >= 0) {
                    normals[v] = {
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]
                    };
                }
                else {
                    normals[v] = glm::vec3(0.0f); 
                }
            }


            mesh.addTriangle(Triangle(vertices[0], vertices[1], vertices[2], normals[0], normals[1], normals[2]));

            indexOffset += numVerts;
        }
    }

    return mesh;
}