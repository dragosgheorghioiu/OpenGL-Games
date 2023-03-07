//
// Created by drago on 02.12.2022.
//

#include <iostream>
#include "meshes.h"

//constructor
meshes_t2::meshes_t2() {
}

//destructor
meshes_t2::~meshes_t2() {
}

Mesh *meshes_t2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices,
                            const std::vector<unsigned int> &indices, std::unordered_map<std::string, Mesh *> meshes) {
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void *) (sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void *) (2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat),
                          (void *) (2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void meshes_t2::addMoreTriangles(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, std::vector<VertexFormat> *vertices) {
    glm::vec3 direction = glm::normalize(b - a);
    glm::vec3 direction2 = glm::normalize(c - d);
    float i = 0.0f;
    glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);

    while (glm::length(a + (i + 0.001f) * direction - a) < glm::length(a - b) && glm::length(d + (i + 0.001f) * direction2 - d) < glm::length(d - c)) {
        vertices->push_back(VertexFormat(a + direction * i, glm::vec3(0, 1, 0), color));
        vertices->push_back(VertexFormat(d + direction2 * i, glm::vec3(0, 1, 0), color));
        vertices->push_back(VertexFormat(a + direction * (i + 0.001f), glm::vec3(0, 1, 0), color));
        vertices->push_back(VertexFormat(d + direction2 * (i + 0.001f), glm::vec3(0, 1, 0), color));
        i += 0.001f;
    }
}

Mesh *meshes_t2::CreateCourse(std::unordered_map<std::string, Mesh *> meshes, enemy *enemy1, enemy *enemy2) {
    float dist = 0.25;
    glm::vec3 color = glm::vec3(0.5, 0.5, 0.5);
    glm::vec3 normal = glm::vec3(1, 0, 0);
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    std::vector<int> nrTriangles;

    std::vector<glm::vec3> points{
            glm::vec3(-27.05, 0.2, 28.31), // A
            glm::vec3(-11.97562, 0.2, 32.17718), // B
            glm::vec3(-0.76, 0.2, 27.15), // C
            glm::vec3(5.36819, 0.2, 30.80495), // D
            glm::vec3(15.15389, 0.2, 25.12906), // E
            glm::vec3(13.19943, 0.2, 16.65853), // F
            glm::vec3(4.26862, 0.2, 15.54617), // G
            glm::vec3(2.72155, 0.2, 8.58436), // P
            glm::vec3(9.10321, 0.2, 3.363), // H
            glm::vec3(19.9327, 0.2, 3.16962), // I
            glm::vec3(22.64007, 0.2, -10.05175), // Q
            glm::vec3(14.97961, 0.2, -20.01999), // J
            glm::vec3(7.74952, 0.2, -11.33417), // K
            glm::vec3(-5.21003, 0.2, 0 - 20.13226), // L
            glm::vec3(-11.20931, 0.2, -11.79), // M
            glm::vec3(-21.80143, 0.2, -8.7530), // N
            glm::vec3(-34.90678, 0.2, -7.634), // R
            glm::vec3(-37.46392, 0.2, 3.713014), // S
            glm::vec3(-39.62949, 0.2, 18.25), // O
            glm::vec3(-25.62949, 0.2, 29.25), // T
    };

    glm::vec3 p;

    for (int i = 0; i < points.size() - 1; i++) {
        p = glm::cross(points[i + 1] - points[i], glm::vec3(0, 1, 0));
        vertices.push_back(VertexFormat(points[i] + dist * p, normal, color));
        vertices.push_back(VertexFormat(points[i] - dist * p, normal, color));
        vertices.push_back(VertexFormat(points[i + 1] + dist * p, normal, color));
        vertices.push_back(VertexFormat(points[i + 1] - dist * p, normal, color));
        enemy1->path.push_back(points[i] + dist * p * 3.0f / 6.0f);
        enemy2->path.push_back(points[i] - dist * p * 4.0f / 6.0f);
    }

    p = glm::cross(points[points.size() - 1] - points[0], glm::vec3(0, 1, 0));
    vertices.push_back(VertexFormat(points[points.size() - 1] + dist * p, normal, color));
    vertices.push_back(VertexFormat(points[points.size() - 1] - dist * p, normal, color));
    vertices.push_back(VertexFormat(points[0] + dist * p, normal, color));
    vertices.push_back(VertexFormat(points[0] - dist * p, normal, color));

    float sum = 0;
    for (int i = 0; i < vertices.size() - 3; i += 4) {
         addMoreTriangles(vertices[i].position, vertices[(i + 2)].position,
                                vertices[(i + 3)].position,
                                vertices[(i + 1)].position, &vertices);
    }

    for (int i = 0; i < points.size() - 1; i++) {
        p = glm::cross(points[i + 1] - points[i ], glm::vec3(0, 1, 0));
        int n;
        n = 3;
        if (glm::length(vertices[4 * i + 1].position - vertices[4 * i + 3].position) < 12) {
            n = 2;
        }
        for (float j = 1; j < n; j++) {
            glm::vec3 treePos =
                    vertices[i * 4].position +
                    j * (vertices[i * 4 + 2].position - vertices[i * 4].position) / 3.0f +
                    (dist * p) / 2.0f;
            if (i != 2) {
                treePositions.push_back(treePos);
            }

            if (j == 1 && (i != 11)) {
                treePos = vertices[i * 4 + 1].position +
                          (j + 0.5f) * (vertices[i * 4 + 3].position - vertices[i * 4 + 1].position) / 3.0f -
                          (dist * p) / 3.0f;
                treePositions.push_back(treePos);
            }

        }

        {
            roadPoints.push_back(vertices[i * 4].position);
            roadPoints.push_back(vertices[i * 4 + 1].position);
            roadPoints.push_back(vertices[i * 4 + 3].position);

            roadPoints.push_back(vertices[i * 4].position);
            roadPoints.push_back(vertices[i * 4 + 3].position);
            roadPoints.push_back(vertices[i * 4 + 2].position);
        }

//        // first rectangle
//        {
//            indices.push_back(4 * i);
//            indices.push_back(4 * i + 3);
//            indices.push_back(4 * i + 1);
//
//            indices.push_back(4 * i);
//            indices.push_back(4 * i + 2);
//            indices.push_back(4 * i + 3);
//        }

        {
            roadPoints.push_back(vertices[i * 4 + 4].position);
            roadPoints.push_back(vertices[i * 4 + 2].position);
            roadPoints.push_back(vertices[i * 4 + 3].position);

            roadPoints.push_back(vertices[i * 4 + 4].position);
            roadPoints.push_back(vertices[i * 4 + 5].position);
            roadPoints.push_back(vertices[i * 4 + 3].position);
        }

        // second rectangle
        {
            indices.push_back(4 * i + 4);
            indices.push_back(4 * i + 3);
            indices.push_back(4 * i + 2);

            indices.push_back(4 * i + 4);
            indices.push_back(4 * i + 5);
            indices.push_back(4 * i + 3);
        }

//        {
//            roadPoints.push_back(vertices[i * 4 + 4].position);
//            roadPoints.push_back(vertices[i * 4 + 5].position);
//            roadPoints.push_back(vertices[i * 4 + 1].position);
//
//            roadPoints.push_back(vertices[i * 4 + 4].position);
//            roadPoints.push_back(vertices[i * 4 + 0].position);
//            roadPoints.push_back(vertices[i * 4 + 1].position);
//        }
//        // bridge between rectangles
//        {
//            indices.push_back(4 * i + 4);
//            indices.push_back(4 * i + 1);
//            indices.push_back(4 * i + 5);
//
//            indices.push_back(4 * i + 4);
//            indices.push_back(4 * i + 0);
//            indices.push_back(4 * i + 1);
//        }

    }

    {
        roadPoints.push_back(vertices[4 * (points.size() - 1)].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 3].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 1].position);

        roadPoints.push_back(vertices[4 * (points.size() - 1)].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 3].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 2].position);

        roadPoints.push_back(vertices[4 * (points.size() - 1) + 3].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 2].position);
        roadPoints.push_back(vertices[1].position);

        roadPoints.push_back(vertices[4 * (points.size() - 1) + 3].position);
        roadPoints.push_back(vertices[1].position);
        roadPoints.push_back(vertices[0].position);

        roadPoints.push_back(vertices[1].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 1].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 0].position);

        roadPoints.push_back(vertices[1].position);
        roadPoints.push_back(vertices[0].position);
        roadPoints.push_back(vertices[4 * (points.size() - 1) + 1].position);
    }

    indices.push_back(4 * (points.size() - 1));
    indices.push_back(4 * (points.size() - 1) + 3);
    indices.push_back(4 * (points.size() - 1) + 1);

    indices.push_back(4 * (points.size() - 1));
    indices.push_back(4 * (points.size() - 1) + 3);
    indices.push_back(4 * (points.size() - 1) + 2);

    indices.push_back(1);
    indices.push_back(4 * (points.size() - 1) + 3);
    indices.push_back(4 * (points.size() - 1) + 2);

    indices.push_back(1);
    indices.push_back(0);
    indices.push_back(4 * (points.size() - 1) + 3);

    indices.push_back(1);
    indices.push_back(4 * (points.size() - 1) + 1);
    indices.push_back(4 * (points.size() - 1) + 0);

    indices.push_back(1);
    indices.push_back(0);
    indices.push_back(4 * (points.size() - 1) + 1);

    // additional trees
    treePositions.push_back(glm::vec3(8, 0, -7));

    for (int i = 4 * points.size(); i < vertices.size() - 3; i += 4) {
        indices.push_back(i + 1);
        indices.push_back(i + 2);
        indices.push_back(i + 3);

        indices.push_back(i);
        indices.push_back(i + 2);
        indices.push_back(i + 1);
    }



    Mesh *mesh = CreateMesh("course", vertices, indices, meshes);
    return mesh;
}

Mesh *meshes_t2::CreatePlane(std::unordered_map<std::string, Mesh *> meshes) {
    std::vector<VertexFormat> vertices;

    for (float i = 0; i < 200; i = i + 2) {
        for (float j = 0; j < 200; j = j + 2) {
            glm::vec3 normal = glm::vec3(0, 1, 0);
            glm::vec3 color = glm::vec3(0.31, 0.75, 0.30);

            glm::vec3 position = glm::vec3(i - 1, 0, j + 1);
            vertices.push_back(VertexFormat(position, normal, color));

            position = glm::vec3(i + 1, 0, j + 1);
            vertices.push_back(VertexFormat(position, normal, color));

            position = glm::vec3(i - 1, 0, j - 1);
            vertices.push_back(VertexFormat(position, normal, color));

            position = glm::vec3(i + 1, 0, j - 1);
            vertices.push_back(VertexFormat(position, normal, color));
        }
    }

    std::vector<unsigned int> indices;

    for (int i = 0; i < 40000; i++) {
        indices.push_back(i * 4);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 3);
        indices.push_back(i * 4 + 2);
    }

    return CreateMesh("plane", vertices, indices, meshes);
}

Mesh *meshes_t2::CreateTree(std::unordered_map<std::string, Mesh *> meshes) {
    glm::vec3 trunkColor = glm::vec3(0.38, 0.23, 0.08);
    glm::vec3 leafColor = glm::vec3(0.04, 0.58, 0.25);
    std::vector<VertexFormat> vertices
            {
                    // trunk vertices
                    VertexFormat(glm::vec3(-0.9, -1, 0.9), glm::vec3(0, 1, 1), trunkColor),
                    VertexFormat(glm::vec3(0.9, -1, 0.9), glm::vec3(1, 0, 1), trunkColor),
                    VertexFormat(glm::vec3(-0.9, 4, 0.9), glm::vec3(1, 0, 0), trunkColor),
                    VertexFormat(glm::vec3(0.9, 4, 0.9), glm::vec3(0, 1, 0), trunkColor),
                    VertexFormat(glm::vec3(-0.9, -1, -0.9), glm::vec3(1, 1, 1), trunkColor),
                    VertexFormat(glm::vec3(0.9, -1, -0.9), glm::vec3(0, 1, 1), trunkColor),
                    VertexFormat(glm::vec3(-0.9, 4, -0.9), glm::vec3(1, 1, 0), trunkColor),
                    VertexFormat(glm::vec3(0.9, 4, -0.9), glm::vec3(0, 0, 1), trunkColor),

                    // leaf vertices
                    VertexFormat(glm::vec3(-2, 4, 2), glm::vec3(0, 1, 1), leafColor),
                    VertexFormat(glm::vec3(2, 4, 2), glm::vec3(1, 0, 1), leafColor),
                    VertexFormat(glm::vec3(-2, 8, 2), glm::vec3(1, 0, 0), leafColor),
                    VertexFormat(glm::vec3(2, 8, 2), glm::vec3(0, 1, 0), leafColor),
                    VertexFormat(glm::vec3(-2, 4, -2), glm::vec3(1, 1, 1), leafColor),
                    VertexFormat(glm::vec3(2, 4, -2), glm::vec3(0, 1, 1), leafColor),
                    VertexFormat(glm::vec3(-2, 8, -2), glm::vec3(1, 1, 0), leafColor),
                    VertexFormat(glm::vec3(2, 8, -2), glm::vec3(0, 0, 1), leafColor),
            };

    std::vector<unsigned int> indices =
            {
                    0, 1, 2, 1, 3, 2,
                    2, 3, 7, 2, 7, 6,
                    1, 7, 3, 1, 5, 7,
                    6, 7, 4, 7, 5, 4,
                    0, 4, 1, 1, 4, 5,
                    2, 6, 4, 0, 2, 4,

                    8, 9, 10, 9, 11, 10,
                    10, 11, 15, 10, 15, 14,
                    9, 15, 11, 9, 13, 15,
                    14, 15, 12, 15, 13, 12,
                    8, 12, 9, 9, 12, 13,
                    10, 14, 12, 8, 10, 12
            };

    return CreateMesh("tree", vertices, indices, meshes);
}

Mesh *meshes_t2::CreateCar(std::unordered_map<std::string, Mesh *> meshes, glm::vec3 frontColor, glm::vec3 backColor,
                           int carNumber) {

    std::vector<VertexFormat> vertices
            {
                    // trunk vertices
                    VertexFormat(glm::vec3(-1.5, 0, 0.5), glm::vec3(0, 1, 1), frontColor),
                    VertexFormat(glm::vec3(1.5, 0, 0.5), glm::vec3(1, 0, 1), backColor),
                    VertexFormat(glm::vec3(-1.5, 1, 0.5), glm::vec3(1, 0, 0), frontColor),
                    VertexFormat(glm::vec3(1.5, 1, 0.5), glm::vec3(0, 1, 0), backColor),
                    VertexFormat(glm::vec3(-1.5, 0, -0.5), glm::vec3(1, 1, 1), frontColor),
                    VertexFormat(glm::vec3(1.5, 0, -0.5), glm::vec3(0, 1, 1), backColor),
                    VertexFormat(glm::vec3(-1.5, 1, -0.5), glm::vec3(1, 1, 0), frontColor),
                    VertexFormat(glm::vec3(1.5, 1, -0.5), glm::vec3(0, 0, 1), backColor),

            };

    std::vector<unsigned int> indices =
            {
                    0, 1, 2, 1, 3, 2,
                    2, 3, 7, 2, 7, 6,
                    1, 7, 3, 1, 5, 7,
                    6, 7, 4, 7, 5, 4,
                    0, 4, 1, 1, 4, 5,
                    2, 6, 4, 0, 2, 4,

            };

    if (carNumber == 1) {
        return CreateMesh("enemy1", vertices, indices, meshes);
    } else if (carNumber == 2) {
        return CreateMesh("enemy2", vertices, indices, meshes);
    }
    return CreateMesh("car", vertices, indices, meshes);
}

int meshes_t2::CheckIfPointIsInsideTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    float triangleArea = glm::length(glm::cross(b - a, c - a)) / 2;
    float area1 = glm::length(glm::cross(p - a, b - a)) / 2;
    float area2 = glm::length(glm::cross(p - b, c - b)) / 2;
    float area3 = glm::length(glm::cross(p - c, a - c)) / 2;
    if (area1 + area2 + area3 <= triangleArea + 0.0001) {
        return 1;
    }
    return 0;
}

int meshes_t2::CheckIfPointIsOnTheRoad(glm::vec3 p) {
    for (int i = 0; i < roadPoints.size() - 2; i = i + 3) {
        if (CheckIfPointIsInsideTriangle(p, roadPoints[i], roadPoints[i + 1], roadPoints[i + 2]) == 1) {
            return 1;
        }
    }
    return 0;
}


