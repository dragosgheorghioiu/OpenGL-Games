#ifndef GFXFRAMEWORK_DUCK_H
#define GFXFRAMEWORK_DUCK_H

#include "components/simple_scene.h"
#include "hud.h"

class duck {
    public:
        duck();
        ~duck();

        void Fly(float deltaTimeSeconds, float speed);
        void FlapWings(float deltaTimeSeconds);
        void KeepDuckInLogicSpace();
        void SetRandomSpawnPoint();
        void FlyAway(float deltaTimeSeconds, hud *h);
        void Die(hud *h);

        float posX = 360.0f, posY = 270.0f;
        float flightAngle = 3 * M_PI / 2, wingAngle = 0;
        bool upWing = false;
        float outX = 1280, outY = 720;

        bool isDead = false;
        bool isFlyingAway = false;

        float timeToFly = 7;
        float airTime = 0;
        int currentSpeed = 2;
        int flyAwaySpeed = 10;
        int previousSpeed = 2;
        int duckNumber = 1;
        int killedDucks = 1;
};


#endif //GFXFRAMEWORK_DUCK_H
