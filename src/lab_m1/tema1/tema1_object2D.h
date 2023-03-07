#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace tema1_object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill = false);
    Mesh* CreateTriangle(const std::string &name, glm::vec3 point, float height, float base, glm::vec3 color, bool fill = false);
    Mesh* CreateCircle(const std::string &name, glm::vec3 center, float radius, int numberOfPoints, glm::vec3 color, bool fill = false);
    Mesh* CreatePointBar(const std::string &name, glm::vec3 leftBottomCorner, float length, float height, glm::vec3 color, bool fill);
    Mesh* CreateSpreeSymbol(const std::string &name, glm::vec3 center, float width, float height, glm::vec3 color, bool fill);
}
