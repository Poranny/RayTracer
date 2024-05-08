#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "Mesh.h"
#include <string>

class ObjLoader {
public:

    static Mesh loadObj(const std::string& filePath);
};

#endif 
