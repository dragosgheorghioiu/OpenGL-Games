#pragma once

#include "components/simple_scene.h"
#include "duck.h"
#include "hud.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                    : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            float x;
            float y;
            float width;
            float height;
        };

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void InitDuck();
        void InitHud();
        void DrawDuck(float translateX, float translateY, float angle, float wingAngle, glm::mat3 visMatrix);
        void DrawHud(float translateX, float translateY, glm::mat3 visMatrix, int lives, int bullets, int max, float symbolAngle);
        void getCorners(float translateX, float translateY, float angle);
        void getMinMaxCoordonates();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        float length;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        duck d;
        hud h;
        bool skipFirstFrame = false;
        glm::vec3 corner1, corner2, corner3, corner4;
        float posX = 0, posY = 0;
        float triangleHeight = 40;
        float triangleBase = 25;
        float bodyHeight = 130;
        float bodyBase = 66;
        float wingHeight = 80;
        float wingBase = 50;
        float hitboxHeight = 160;
        float hitboxWidth = 210;
        float minX = 0;
        float minY = 0;
        float maxX = 0;
        float maxY = 0;

        glm::vec3 color = glm::vec3(0.45, 0.85, 1);
        float symbolAngle = 0;

        int numberOfTriangles = 500;

    };
}   // namespace m1
