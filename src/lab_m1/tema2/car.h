//
// Created by drago on 04.12.2022.
//

#ifndef GFXFRAMEWORK_CAR_H
#define GFXFRAMEWORK_CAR_H

#include "core/gpu/mesh.h"

class car {
public:
    float angle = 2.42f, acceleration, maxSpeed, radius = 0.5f;
    glm::vec3 position, color;
    glm::vec3 forward = glm::vec3(0, 0, 1);
    glm::vec3 up		= glm::vec3(0, 1, 0);
    glm::vec3 right	= glm::vec3(1, 0, 0);

    // function to extract forward and right from angle
    void Update()
    {
        forward = glm::vec3(cos(angle), 0, -sin(angle));
        right = glm::normalize(glm::cross(forward, up));
    }
};


#endif //GFXFRAMEWORK_CAR_H
