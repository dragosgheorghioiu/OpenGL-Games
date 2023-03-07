#include "duck.h"
#include "iostream"
#include "hud.h"

duck::duck() = default;

duck::~duck() = default;

void duck::Fly(float deltaTimeSeconds, float speed) {
    posX += deltaTimeSeconds * 100 * speed * cos(flightAngle);
    posY += deltaTimeSeconds * 100 * speed * sin(flightAngle);
}

void duck::FlapWings(float deltaTimeSeconds) {
    //check
    if (upWing) {
        wingAngle += 10 * deltaTimeSeconds;
    } else {
        wingAngle -= 10 * deltaTimeSeconds;
    }

    if (wingAngle >= M_PI / 4) {
        wingAngle = M_PI / 4;
        upWing = false;
    }

    if (wingAngle <= -M_PI / 4) {
        wingAngle = -M_PI / 4;
        upWing = true;
    }
}

void duck::KeepDuckInLogicSpace() {
    // quadrant 1
    if (sin(flightAngle) > 0 && cos(flightAngle) > 0) {
        if (posX > outX) {
            flightAngle = -flightAngle + M_PI;
        }
        if (posY > outY) {
            flightAngle = -flightAngle;
        }
    }

    // quadrant 2
    if (sin(flightAngle) > 0 && cos(flightAngle) < 0) {
        if (posX < 0) {
            flightAngle = -flightAngle + M_PI;
        }
        if (posY > outY) {
            flightAngle = -flightAngle;
        }
    }

    // quadrant 3
    if (sin(flightAngle) < 0 && cos(flightAngle) < 0) {
        if (posX < 0) {
            flightAngle = M_PI - flightAngle;
        }
        if (posY < 0) {
            flightAngle = -flightAngle;
        }
    }

    // quadrant 4
    if (sin(flightAngle) < 0 && cos(flightAngle) > 0) {
        if (posX > outX) {
            flightAngle = -flightAngle + M_PI;
        }

        if (posY < 0) {
            flightAngle = -flightAngle;
        }
    }
}

void duck::SetRandomSpawnPoint() {
    srand(unsigned(time(0)));

    for (int i = 0; i < 5; i++) {
        posX = (rand() % 1278) + 1;
        posY = (rand() % 100) + 1;
        flightAngle = M_PI + 0.3 + static_cast <float> (rand()) /
                                   (static_cast <float> (RAND_MAX / ((2 * M_PI - 0.4) - (M_PI + 0.3))));
    }

    while (flightAngle > M_PI * 3 / 2 - 0.3 && flightAngle < M_PI * 3 / 2 + 0.3) {
        flightAngle = M_PI + 0.3 + static_cast <float> (rand()) /
                                   (static_cast <float> (RAND_MAX / ((2 * M_PI - 0.3) - (M_PI + 0.3))));
    }
}

void duck::FlyAway(float deltaTimeSeconds, hud *h) {
    if ((timeToFly <= airTime || h->bullets == 0) && !isFlyingAway && !isDead) {
        previousSpeed = currentSpeed;
        killedDucks = 1;
        h->isSpree = false;
        isFlyingAway = true;
        flightAngle = M_PI / 2;
        currentSpeed = flyAwaySpeed;
    }
    if (posY > outY + 100 && isFlyingAway) {
        isFlyingAway = false;
        airTime = 0;
        SetRandomSpawnPoint();
        duckNumber++;
        if (duckNumber % 5 == 0) {
            currentSpeed = previousSpeed + 3;
        } else {
            currentSpeed = previousSpeed;
        }
        h->lives--;
        h->bullets = h->max;
    }
    if (!isFlyingAway && !isDead) {
        airTime += deltaTimeSeconds;
    }
}

void duck::Die(hud *h) {
    if (posY < -100) {
        isDead = false;
        airTime = 0;
        if (killedDucks >= 4) {
            h->isSpree = true;
            h->points += killedDucks / 4 * currentSpeed;
        } else {
            h->points += currentSpeed / 4;
        }
        SetRandomSpawnPoint();
        duckNumber++;
        killedDucks++;
        if (duckNumber % 5 == 0) {
            currentSpeed = previousSpeed + 3;
        } else {
            currentSpeed = previousSpeed;
        }
        h->bullets = h->max;
    }
    if (!isDead && !isFlyingAway) {
        previousSpeed = currentSpeed;
    }
}