//
// Created by drago on 06.12.2022.
//

#ifndef GFXFRAMEWORK_ENEMY_H
#define GFXFRAMEWORK_ENEMY_H

#include "core/gpu/mesh.h"

class enemy {
public:
    glm::vec3 position;
    float angle = 0, lastAngle = 0, speed = 4, radius = 0.5f;
    glm::vec3 color;
    std::vector<glm::vec3> path;
    int lastPoint = 0;

    float getCurrentAngle(std::vector<glm::vec3> path, int index) {
        if (index == path.size() - 1) {
            return atan2(path[0].z - path[index].z, path[0].x - path[index].x);
        }
        return atan2(path[index + 1].z - path[index].z, path[index + 1].x - path[index].x);
    }

    void keepOnTheRoad() {
        if (lastPoint < 18) {
            if (abs(position.x - path[lastPoint + 1].x) <= 0.1 &&
                abs(position.z - path[lastPoint + 1].z) <= 0.1) {
                lastPoint++;
                position = path[lastPoint];
            }
        } else if (abs(position.x - path[0].x) <= 0.1 &&
                   abs(position.z - path[0].z) <= 0.1) {
            lastPoint = 0;
            position = path[0];
        }
    }
};


#endif //GFXFRAMEWORK_ENEMY_H
