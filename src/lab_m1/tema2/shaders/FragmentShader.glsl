#version 330

// Input
in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vColor;

// Output
layout(location = 0) out vec4 out_color;


void main()
{

    out_color = vec4(vColor, 1.0);

}
