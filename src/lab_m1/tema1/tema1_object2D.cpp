#include "tema1_object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

# define M_PI           3.14159265358979323846  /* pi */

Mesh* tema1_object2D::CreateRectangle(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        float height,
        float width,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner + glm::vec3(4 * width / 6, height / 2, 0), color),
                    VertexFormat(corner + glm::vec3(2 * -width / 6, height / 2, 0), color),
                    VertexFormat(corner + glm::vec3(2 * -width / 6, -height / 2, 0), color),
                    VertexFormat(corner + glm::vec3(4 * width / 6, -height / 2, 0), color),
            };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* tema1_object2D::CreateSquare(
        const std::string &name,
        glm::vec3 leftBottomCorner,
        float length,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner, color),
                    VertexFormat(corner + glm::vec3(length, 0, 0), color),
                    VertexFormat(corner + glm::vec3(length, length, 0), color),
                    VertexFormat(corner + glm::vec3(0, length, 0), color)
            };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* tema1_object2D::CreateTriangle(
        const std::string &name,
        glm::vec3 point,
        float height,
        float base,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 corner = point;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner + glm::vec3(height / 2, 0, 0) , color),
                    VertexFormat(corner + glm::vec3(-height/2, base/2, 0), color),
                    VertexFormat(corner + glm::vec3(-height/2, -base/2, 0), color),
            };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2 };

    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
    }

    triangle->InitFromData(vertices, indices);
    return triangle;
}

Mesh* tema1_object2D::CreateCircle(
        const std::string &name,
        glm::vec3 point,
        float radius,
        int numberOfPoints,
        glm::vec3 color,
        bool fill)
{
    glm::vec3 center = point;

    std::vector<VertexFormat> vertices;
    vertices.push_back(VertexFormat(center, color));

    std::vector<unsigned int> indices;
    indices.push_back(0);
    int count = 0;

    for(int i = 0; i <= numberOfPoints; i++) {;
        vertices.push_back(VertexFormat(center + glm::vec3((radius * cos(i *  2 * M_PI / numberOfPoints)), (radius * sin(i * 2 * M_PI / numberOfPoints)), 0) , color));
        indices.push_back(i);
        indices.push_back(i + 1);
        indices.push_back(0);

    }

    Mesh* circle = new Mesh(name);


    if (!fill) {
        circle->SetDrawMode(GL_LINE_LOOP);
    }

    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* tema1_object2D::CreatePointBar(const std::string &name, glm::vec3 leftBottomCorner, float width, float height,
                                     glm::vec3 color, bool fill) {

    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner, color),
                    VertexFormat(corner + glm::vec3(width, 0, 0), color),
                    VertexFormat(corner + glm::vec3(width, height, 0), color),
                    VertexFormat(corner + glm::vec3(0, height, 0), color),
            };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* tema1_object2D::CreateSpreeSymbol(const std::string &name, glm::vec3 center, float width, float height,
                                         glm::vec3 color, bool fill) {

    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
            {
                    VertexFormat(corner + glm::vec3(0, height / 2, 0), color),
                    VertexFormat(corner + glm::vec3(width / 2, 0, 0), color),
                    VertexFormat(corner + glm::vec3(0, -height / 2, 0), color),
                    VertexFormat(corner + glm::vec3(-width / 2, 0, 0), color),
            };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;

}
