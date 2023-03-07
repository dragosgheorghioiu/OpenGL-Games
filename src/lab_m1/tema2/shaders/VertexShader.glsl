#version 330

// Input
layout(location = 0) in vec3 position;
layout(location = 3) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 1) in vec3 color;

// Uniform properties
uniform float scaleFactor;
uniform vec3 carPos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output
out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexcoord;


void main()
{
    vPosition = position;
    vNormal = normal;
    vColor = color;
    vTexcoord = texcoord;

    vec4 modelPosv4 = Model * vec4(position, 1.0);
    vec3 modelPosv3 = vec3(modelPosv4.x, modelPosv4.y, modelPosv4.z);
    modelPosv3.y = modelPosv3.y - length(carPos - modelPosv3) * length(carPos - modelPosv3) * scaleFactor;


    gl_Position = Projection * View * vec4(modelPosv3, 1.0);
}
