//
// Created by drago on 02.12.2022.
//

#ifndef GFXFRAMEWORK_MESHES_H
#define GFXFRAMEWORK_MESHES_H


#include "core/gpu/mesh.h"
#include <unordered_map>
#include "lab_m1/tema2/car.h"
#include "lab_m1/tema2/enemy.h"

class meshes_t2 {
public:
    meshes_t2();
    ~meshes_t2();

    Mesh *CreateMesh(const char *name, const std::vector <VertexFormat> &vertices, const std::vector<unsigned int> &indices, std::unordered_map<std::string, Mesh *> meshes);

    Mesh *CreatePlane(std::unordered_map<std::string, Mesh *> meshes);

    Mesh *CreateCourse(std::unordered_map<std::string, Mesh *> meshes, enemy *enemy1, enemy *enemy2);

    Mesh *CreateTree(std::unordered_map<std::string, Mesh *> meshes);

    Mesh *CreateCar(std::unordered_map<std::string, Mesh *> meshes, glm::vec3 frontColor, glm::vec3 backColor, int carNumber);

    int CheckIfPointIsInsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c);

    int CheckIfPointIsOnTheRoad(glm::vec3 p);

    void addMoreTriangles(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, std::vector <VertexFormat> *vertices);

    std::vector <glm::vec3> treePositions;
    std::vector <glm::vec3> roadPoints;
};


#endif //GFXFRAMEWORK_MESHES_H
