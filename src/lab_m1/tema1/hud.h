//
// Created by drago on 07.11.2022.
//

#ifndef GFXFRAMEWORK_HUD_H
#define GFXFRAMEWORK_HUD_H


class hud {
public:
    hud();
    ~hud();
    int bullets = 3;
    int lives = 3;
    int max = 3;

    float mouseX, mouseY;
    float OutY;

    float points = 0;
    float maxPoints = 350;

    bool isSpree = false;

    float hudPosX = 15, hudPosY = 675;

};


#endif //GFXFRAMEWORK_HUD_H
