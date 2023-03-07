#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform int lightType;
uniform float spotAngle;

uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    vec3 L = normalize( light_position - world_position );
    vec3 V = normalize( eye_position - world_position );
    vec3 H = normalize( L + V );
    vec3 R = reflect (-L, world_normal);

    float ambient_light = 0.3;

    float diffuse_light = max( dot( L, world_normal ), 0.0 );

    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);
    }

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.
    vec3 light;
    float cutOff = spotAngle;
    float attenuation = 1 / pow(length(light_position - world_position), 2);
    float spotLight = dot(-L, light_direction);
    float spotLightLimit = cos(cutOff);
    float linearAttenuation = (spotLight - spotLightLimit) / (1 - spotLightLimit);
    float lightAttenuationFactor = pow(linearAttenuation, 2);

    if (lightType == 1) {
        if (spotLight > cos(cutOff)) {
            light = object_color * (ambient_light + (lightAttenuationFactor + attenuation) * (diffuse_light + specular_light));
        } else {
            light = ambient_light * object_color;
        }
    } else {
        light = object_color * (ambient_light + attenuation * (diffuse_light + specular_light));
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.
    // TODO(student): Write pixel out color
    out_color = vec4(light, 1.0);

}
