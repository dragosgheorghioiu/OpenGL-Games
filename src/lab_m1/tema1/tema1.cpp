#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/tema1_transform2D.h"
#include "lab_m1/tema1/tema1_object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1() {
}


Tema1::~Tema1() {
}

void Tema1::DrawHud(float translateX, float translateY, glm::mat3 visMatrix, int lives, int bullets, int max,
                    float symbolAngle) {
    // hearts
    for (int i = 0; i < lives; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + i * 30, translateY);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    // bullets
    for (int i = 0; i < bullets; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + i * 30 + 7, translateY - 40);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    // grass
    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    // pointBar
    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    modelMatrix *= tema1_transform2D::Translate(translateX + 900, translateY - 20);
    modelMatrix *= tema1_transform2D::Scale(h.points, 1.0f);
    RenderMesh2D(meshes["PointBar"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    modelMatrix *= tema1_transform2D::Translate(translateX + 900, translateY - 20);
    RenderMesh2D(meshes["maxPointBar"], shaders["VertexColor"], modelMatrix);

    if (h.isSpree) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + 865, translateY - 5);
        modelMatrix *= tema1_transform2D::Rotate(symbolAngle);
        RenderMesh2D(meshes["symbol"], shaders["VertexColor"], modelMatrix);
    }

}

void Tema1::DrawDuck(float translateX, float translateY, float angle, float wingAngle, glm::mat3 visMatrix) {

    if (!d.isDead) {
        // pupil
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + 100, translateY + 5);
        modelMatrix *= tema1_transform2D::Translate(-100, -5);
        modelMatrix *= tema1_transform2D::Rotate(angle);
        modelMatrix *= tema1_transform2D::Translate(100, 5);
        RenderMesh2D(meshes["circle2"], shaders["VertexColor"], modelMatrix);

        // eye
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + 95, translateY + 5);
        modelMatrix *= tema1_transform2D::Translate(-95, -5);
        modelMatrix *= tema1_transform2D::Rotate(angle);
        modelMatrix *= tema1_transform2D::Translate(+95, 5);
        RenderMesh2D(meshes["circle3"], shaders["VertexColor"], modelMatrix);

        // wing 1
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + 20, translateY + 40);
        modelMatrix *= tema1_transform2D::Translate(-20, -40);
        modelMatrix *= tema1_transform2D::Rotate(angle);
        modelMatrix *= tema1_transform2D::Rotate(-wingAngle);
        modelMatrix *= tema1_transform2D::Translate(+20, 40);
        modelMatrix *= tema1_transform2D::Rotate(M_PI / 2);
        RenderMesh2D(meshes["triangle3"], shaders["VertexColor"], modelMatrix);

        //wing 2
        modelMatrix = glm::mat3(1);
        modelMatrix *= visMatrix;
        modelMatrix *= tema1_transform2D::Translate(translateX + 20, translateY - 40);
        modelMatrix *= tema1_transform2D::Translate(-20, 40);
        modelMatrix *= tema1_transform2D::Rotate(angle);
        modelMatrix *= tema1_transform2D::Rotate(wingAngle);
        modelMatrix *= tema1_transform2D::Translate(+20, -40);
        modelMatrix *= tema1_transform2D::Rotate(-M_PI / 2);
        RenderMesh2D(meshes["triangle4"], shaders["VertexColor"], modelMatrix);

    }
    // head
    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    modelMatrix *= tema1_transform2D::Translate(translateX + 80, translateY);
    modelMatrix *= tema1_transform2D::Translate(-80, 0);
    modelMatrix *= tema1_transform2D::Rotate(angle);
    modelMatrix *= tema1_transform2D::Translate(+80, 0);
    RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);

    // beak
    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    modelMatrix *= tema1_transform2D::Translate(translateX + 110, translateY - 10);
    modelMatrix *= tema1_transform2D::Translate(-110, +10);
    modelMatrix *= tema1_transform2D::Rotate(angle);
    modelMatrix *= tema1_transform2D::Translate(+110, -10);
    modelMatrix *= tema1_transform2D::Rotate(-0.2f);
    RenderMesh2D(meshes["triangle1"], shaders["VertexColor"], modelMatrix);

    // body
    modelMatrix = glm::mat3(1);
    modelMatrix *= visMatrix;
    modelMatrix *= tema1_transform2D::Translate(translateX, translateY);
    modelMatrix *= tema1_transform2D::Rotate(angle);

    RenderMesh2D(meshes["triangle2"], shaders["VertexColor"], modelMatrix);

}

void Tema1::InitHud() {
    // hud
    float posX = 0, posY = 0;
    glm::vec3 corner = glm::vec3{posX, posY, 0};
    Mesh *heart = tema1_object2D::CreateSquare("heart", corner, 30, glm::vec3(0.9, 0, 0), true);
    AddMeshToList(heart);

    Mesh *bullet = tema1_object2D::CreateSquare("bullet", corner, 15, glm::vec3(0.95, 0.95, 0), true);
    AddMeshToList(bullet);

    Mesh *grass = tema1_object2D::CreateRectangle("grass", corner + glm::vec3{426.66f, 0, 0}, 400, 1500,
                                                  glm::vec3(0, 0.8, 0), true);
    AddMeshToList(grass);

    Mesh *symbol = tema1_object2D::CreateSpreeSymbol("symbol", corner, 30, 50, glm::vec3(0.9, 0, 0), true);
    AddMeshToList(symbol);
}

void Tema1::InitDuck() {

    glm::vec3 corner = glm::vec3{posX, posY, 0};
    Mesh *triangle1 = tema1_object2D::CreateTriangle("triangle1", corner, triangleHeight, triangleBase,
                                                     glm::vec3(0.90588235294, 0.8, 0.22352941176), true);
    AddMeshToList(triangle1);

    Mesh *triangle2 = tema1_object2D::CreateTriangle("triangle2", corner, bodyHeight, bodyBase,
                                                     glm::vec3(0.34509803921, 0.22745098039, 0.14901960784), true);
    AddMeshToList(triangle2);

    Mesh *triangle3 = tema1_object2D::CreateTriangle("triangle3", corner, wingHeight, wingBase,
                                                     glm::vec3(0.34509803921, 0.22745098039, 0.14901960784), true);
    AddMeshToList(triangle3);

    Mesh *triangle4 = tema1_object2D::CreateTriangle("triangle4", corner, wingHeight, wingBase,
                                                     glm::vec3(0.34509803921, 0.22745098039, 0.14901960784), true);
    AddMeshToList(triangle4);

    Mesh *circle1 = tema1_object2D::CreateCircle("circle1", corner, 30, 500,
                                                 glm::vec3(0.18823529411, 0.34117647058, 0.21568627451), true);
    AddMeshToList(circle1);

    Mesh *circle2 = tema1_object2D::CreateCircle("circle2", corner, 5, numberOfTriangles, glm::vec3(0, 0, 0), true);
    AddMeshToList(circle2);

    Mesh *circle3 = tema1_object2D::CreateCircle("circle3", corner, 10, numberOfTriangles, glm::vec3(1, 1, 1), true);
    AddMeshToList(circle3);

    Mesh *square1 = tema1_object2D::CreateRectangle("square1", corner, hitboxHeight, hitboxWidth, glm::vec3(1, 0, 0),
                                                    false);
    AddMeshToList(square1);

    Mesh *maxPointBar = tema1_object2D::CreatePointBar("maxPointBar", corner, 350, 30, glm::vec3(0.5, 0, 0.5), false);
    AddMeshToList(maxPointBar);

    Mesh *PointBar = tema1_object2D::CreatePointBar("PointBar", corner, 1, 30, glm::vec3(0.5, 0, 0.5), true);
    AddMeshToList(PointBar);
}

void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float) resolution.x, 0, (float) resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 1280;   // logic width
    logicSpace.height = 720;  // logic height

    d.SetRandomSpawnPoint();
    InitDuck();
    InitHud();
//
}


void Tema1::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear) {
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float) viewSpace.x, (float) (viewSpace.x + viewSpace.width), (float) viewSpace.y,
                                      (float) (viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace) {
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
            smin, 0.0f, tx,
            0.0f, smin, ty,
            0.0f, 0.0f, 1.0f));
}

void Tema1::getCorners(float translateX, float translateY, float angle) {
    corner1 = glm::vec3(translateX + 5 * hitboxHeight / 6 * cos(angle), translateY + 5 * hitboxWidth / 6 * sin(angle),
                        0);
    corner2 = glm::vec3(translateX + 5 * hitboxHeight / 6 * cos(angle), translateY - 5 * hitboxWidth / 6 * sin(angle),
                        0);
    corner3 = glm::vec3(translateX - 5 * hitboxHeight / 6 * cos(angle), translateY + 5 * hitboxWidth / 6 * sin(angle),
                        0);
    corner4 = glm::vec3(translateX - 5 * hitboxHeight / 6 * cos(angle), translateY - 5 * hitboxWidth / 6 * sin(angle),
                        0);
}

void Tema1::Update(float deltaTimeSeconds) {
    glm::ivec2 resolution = window->GetResolution();
    h.OutY = resolution.y;

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, color, true);

    // Compute uniform 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    if (h.lives != 0 && h.points < h.maxPoints) {
        DrawHud(h.hudPosX, h.hudPosY, visMatrix, h.lives, h.bullets, h.max, symbolAngle);
        DrawDuck(d.posX, d.posY, d.flightAngle, d.wingAngle, visMatrix);

        d.FlyAway(deltaTimeSeconds, &h);
        d.Die(&h);
        getCorners(d.posX, d.posY, d.flightAngle);

        if (!d.isDead && !d.isFlyingAway) {
            d.KeepDuckInLogicSpace();
        }

        if (skipFirstFrame) {
            d.Fly(deltaTimeSeconds, d.currentSpeed);
        }
        skipFirstFrame = true;

        d.FlapWings(deltaTimeSeconds);
        symbolAngle += deltaTimeSeconds * 10;
    } else if (h.points >= h.maxPoints) {
        color = glm::vec3(0, 0.5, 0);
    } else {
        color = glm::vec3(0.5, 0, 0);
    }


//    cout << d.isFlyingAway << " " << d.previousSpeed << endl;
}


void Tema1::FrameEnd() {
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods) {
}


void Tema1::OnKeyPress(int key, int mods) {
}

void Tema1::getMinMaxCoordonates() {
    minX = corner1.x;
    minY = corner1.y;
    if (corner2.x < minX) {
        minX = corner2.x;
    }
    if (corner3.x < minX) {
        minX = corner3.x;
    }
    if (corner4.x < minX) {
        minX = corner4.x;
    }
    if (corner2.y < minY) {
        minY = corner2.y;
    }
    if (corner3.y < minY) {
        minY = corner3.y;
    }
    if (corner4.y < minY) {
        minY = corner4.y;
    }

    maxX = corner1.x;
    maxY = corner1.y;
    if (corner2.x > maxX) {
        maxX = corner2.x;
    }
    if (corner3.x > maxX) {
        maxX = corner3.x;
    }
    if (corner4.x > maxX) {
        maxX = corner4.x;
    }
    if (corner2.y > maxY) {
        maxY = corner2.y;
    }
    if (corner3.y > maxY) {
        maxY = corner3.y;
    }
    if (corner4.y > maxY) {
        maxY = corner4.y;
    }
}

void Tema1::OnKeyRelease(int key, int mods) {
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2) {
        if (!d.isDead && !d.isFlyingAway) {
            if (h.bullets > 0) {
                h.bullets--;
                h.mouseX = mouseX;
                h.mouseY = h.OutY - mouseY;
            }

            glm::vec3 mousePos = glm::vec3(h.mouseX, h.mouseY, 1);
            glm::vec3 realPos = glm::inverse(visMatrix) * mousePos;
            getMinMaxCoordonates();
            if (realPos.x < maxX && realPos.y < maxY && realPos.x > minX && realPos.y > minY) {
                d.isDead = true;
                d.flightAngle = 3 * M_PI / 2;
                d.currentSpeed = d.flyAwaySpeed;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema1::OnWindowResize(int width, int height) {
}
