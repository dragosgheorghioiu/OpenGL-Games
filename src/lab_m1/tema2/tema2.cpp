#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2() {
}


Tema2::~Tema2() {
}

void Tema2::Init() {
    glViewport(10, 10, 810, 460);
    car.acceleration = 0;
    car.maxSpeed = 10;
    renderCameraTarget = true;

    car.position = glm::vec3(-27.05, 0.2, 28.31);
    car.color = glm::vec3(1, 0.5, 0.5);

    camera = new timplemented::Camera();
    camera->SetTarget(car);

    camera2 = new timplemented::Camera();
    camera2->Set(camera2->GetPositionUp(car), car.position, glm::vec3(0, 0, 1));

    // Create a simple plane
    {
        AddMeshToList(m->CreatePlane(this->meshes));
    }

    // Create a simple course
    {
        AddMeshToList(m->CreateCourse(this->meshes, &enemy1, &enemy2));
    }

    // Create a simple tree
    {
        AddMeshToList(m->CreateTree(this->meshes));
    }

    // Create a simple car
    {
        AddMeshToList(m->CreateCar(this->meshes, glm::vec3(0.75, 0.1, 0.75), glm::vec3(0.5, 0.5, 1.0), 0));
    }

    srand(time(NULL));
    // Create a simple enemy1
    {
        // generte random color
        enemy1.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy1.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy1.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy1.position = enemy1.path[3];
//        for (int i = 0; i < 16; i++) {
//            enemy1.lastAngle = enemy1.getCurrentAngle(enemy1.path, i);
//        }
        enemy1.angle = enemy1.getCurrentAngle(enemy1.path, 3);
        enemy1.lastPoint = 3;

        AddMeshToList(m->CreateCar(this->meshes, enemy1.color, enemy1.color, 1));
    }

    // Create a simple enemy2
    {
        // generte random color
        enemy2.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy2.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy2.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        enemy2.position = enemy2.path[10];
        enemy2.angle = enemy2.getCurrentAngle(enemy2.path, 10);
        enemy2.lastPoint = 10;

        AddMeshToList(m->CreateCar(this->meshes, enemy2.color, enemy2.color, 2));
    }

    // Shader for rendering to texture
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"),
                          GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"),
                          GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }


    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

}


void Tema2::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0.8, 0.9, 1);
}

void Tema2::RenderScene(int mode) {
    string shaderName;
    if (mode == 1) {
        shaderName = "LabShader";
    } else {
        shaderName = "VertexNormal";
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-100, 0.1, -100));
        RenderMesh(meshes["plane"], shaders[shaderName], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        RenderMesh(meshes["course"], shaders[shaderName], modelMatrix);
    }

    for (int i = 0; i < m->treePositions.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, m->treePositions[i]);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));
        RenderMesh(meshes["tree"], shaders[shaderName], modelMatrix);
    }

    {

        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy1.position);
        modelMatrix = glm::rotate(modelMatrix, -enemy1.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
        RenderMesh(meshes["enemy1"], shaders[shaderName], modelMatrix);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, enemy2.position);
        modelMatrix = glm::rotate(modelMatrix, -enemy2.angle, glm::vec3(0, 1, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
        RenderMesh(meshes["enemy2"], shaders[shaderName], modelMatrix);
    }

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, car.position);;
    modelMatrix = glm::rotate(modelMatrix, car.angle, car.up);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7, 0.7, 0.7));
    RenderMesh(meshes["car"], shaders[shaderName], modelMatrix);

}

void Tema2::Update(float deltaTimeSeconds) {
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);


    car.Update();
    car.position += car.forward * deltaTimeSeconds * car.acceleration;

    if (renderCameraTarget) {
        camera->SetTarget(car);
    }

    enemy1.keepOnTheRoad();
    enemy1.angle = enemy1.getCurrentAngle(enemy1.path, enemy1.lastPoint);
    enemy1.position.x += enemy1.speed * cos(enemy1.angle) * deltaTimeSeconds * 3 / 2;
    enemy1.position.z += enemy1.speed * sin(enemy1.angle) * deltaTimeSeconds * 3 / 2;

    enemy2.keepOnTheRoad();
    enemy2.angle = enemy2.getCurrentAngle(enemy2.path, enemy2.lastPoint);
    enemy2.position.x += enemy2.speed * cos(enemy2.angle) * deltaTimeSeconds;
    enemy2.position.z += enemy2.speed * sin(enemy2.angle) * deltaTimeSeconds;

    if (sqrt((car.position.x - enemy1.position.x) * (car.position.x - enemy1.position.x) +
             (car.position.z - enemy1.position.z) * (car.position.z - enemy1.position.z)) <
        car.radius + enemy1.radius) {
        car.acceleration = 0;
    }
    if (sqrt((car.position.x - enemy2.position.x) * (car.position.x - enemy2.position.x) +
             (car.position.z - enemy2.position.z) * (car.position.z - enemy2.position.z)) <
        car.radius + enemy2.radius) {
        car.acceleration = 0;
    }
    if (car.acceleration > 0) {
        if (m->CheckIfPointIsOnTheRoad(car.position + car.forward * 1.5f / 1.4f + car.right * 0.5f / 1.4f) == 0 ||
            m->CheckIfPointIsOnTheRoad(car.position + car.forward * 1.5f / 1.4f - car.right * 0.5f / 1.4f) == 0) {
            car.acceleration = -car.acceleration / 3;
        }
    } else if (car.acceleration < 0) {
        if (m->CheckIfPointIsOnTheRoad(car.position - car.forward * 1.5f / 1.4f + car.right * 0.5f / 1.4f) == 0 ||
            m->CheckIfPointIsOnTheRoad(car.position - car.forward * 1.5f / 1.4f - car.right * 0.5f / 1.4f) == 0) {
            car.acceleration = -car.acceleration / 3;
        }
    }
    isOrtho = false;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
    RenderScene(1);

    isOrtho = true;
    glClear(GL_DEPTH_BUFFER_BIT);

    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    camera2->Set(camera2->GetPositionUp(car), car.position, glm::vec3(1, 0, 1));
    projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, 0.01f, 200.0f);
    RenderScene(2);

}


void Tema2::FrameEnd() {
    // DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) {
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    if (!isOrtho) {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    } else {
        glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera2->GetViewMatrix()));
    }

    GLint loc_car = glGetUniformLocation(shader->program, "carPos");
    glUniform3fv(loc_car, 1, glm::value_ptr(car.position));

    GLint scaleFactorGL = glGetUniformLocation(shader->program, "scaleFactor");
    glUniform1f(scaleFactorGL, scaleFactor);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind projection matrix
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods) {
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        float cameraSpeed = 8.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            camera->TranslateForward(cameraSpeed * deltaTime);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            camera->TranslateRight(-cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_S)) {
            camera->TranslateForward(-cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_D)) {
            camera->TranslateRight(cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            camera->TranslateUpword(-cameraSpeed * deltaTime);

        }

        if (window->KeyHold(GLFW_KEY_E)) {
            camera->TranslateUpword(cameraSpeed * deltaTime);

        }
    } else {
        if (window->KeyHold(GLFW_KEY_A)) {
            if (m->CheckIfPointIsOnTheRoad(car.position + car.forward * 1.5f / 1.4f - car.right * 0.5f / 1.4f) == 1 &&
                m->CheckIfPointIsOnTheRoad(car.position - car.forward * 1.5f / 1.4f + car.right * 0.5f / 1.4f) == 1) {
                car.angle += deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            if (m->CheckIfPointIsOnTheRoad(car.position + car.forward * 1.5f / 1.4f + car.right * 0.5f / 1.4f) == 1 &&
                m->CheckIfPointIsOnTheRoad(car.position - car.forward * 1.5f / 1.4f - car.right * 0.5f / 1.4f) == 1) {
                car.angle -= deltaTime;
            }
        }

        if (window->KeyHold(GLFW_KEY_W)) {
            if (car.acceleration < car.maxSpeed)
                car.acceleration += deltaTime * 2;
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            if (abs(car.acceleration) < car.maxSpeed)
                car.acceleration -= deltaTime * 2;
        }

        if (!window->KeyHold(GLFW_KEY_W) && !window->KeyHold(GLFW_KEY_S)) {
            if (car.acceleration > 0) {
                car.acceleration -= deltaTime;
            } else if (car.acceleration < 0) {
                car.acceleration += deltaTime;
            }
        }
    }

    if (window->KeyHold(GLFW_KEY_K)) {
        scaleFactor += 0.01f * deltaTime;
    }
    if (window->KeyHold(GLFW_KEY_L)) {
        scaleFactor -= 0.01f * deltaTime;
    }
}


void Tema2::OnKeyPress(int key, int mods) {

    // Add key press event
    if (key == GLFW_KEY_T) {
        renderCameraTarget = !renderCameraTarget;
        cout << car.angle << endl;
        cout << scaleFactor << endl;
    }

    if (key == GLFW_KEY_R) {
        cout << "car position: " << car.position.x << " " << car.position.y << " " << car.position.z << endl;
    }

    if (key == GLFW_KEY_F) {
        camera->SetTarget(car);
    }
}


void Tema2::OnKeyRelease(int key, int mods) {
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        if (!renderCameraTarget) {
            renderCameraTarget = false;
            camera->RotateFirstPerson_OX(-deltaY * sensivityOX);
            camera->RotateFirstPerson_OY(-deltaX * sensivityOY);
            camera->RotateFirstPerson_OZ(0);
        }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema2::OnWindowResize(int width, int height) {
}
