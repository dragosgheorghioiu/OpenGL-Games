#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 position;
layout(location = 3) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 1) in vec3 color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;

// Output
// TODO(student): Output values to fragment shader
out vec3 vPosition;
out vec3 vNormal;
out vec3 vColor;
out vec2 vTexcoord;


void main()
{
    // TODO(student): Send output to fragment shader

    vPosition = position;
    vNormal = normal;
    vColor = color;
    vTexcoord = texcoord;

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(vPosition, 1.0);

}
