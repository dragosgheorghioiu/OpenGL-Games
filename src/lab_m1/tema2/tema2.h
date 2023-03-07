#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/lab_camera.h"
#include "lab_m1/tema2/meshes.h"
#include "lab_m1/tema2/car.h"
#include "lab_m1/tema2/enemy.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;
        meshes_t2 *m = new meshes_t2();
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                    : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderScene(int mode);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        timplemented::Camera *camera, *camera2;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        car car;
        enemy enemy1, enemy2;
        ViewportArea miniViewportArea;
        float orthoLeft = -25.0f, orthoRight = 25.0f, orthoBottom = -15.0f, orthoTop = 15.0f;
        bool isOrtho;
        float scaleFactor = 0.005f;
    };
}   // namespace m1
