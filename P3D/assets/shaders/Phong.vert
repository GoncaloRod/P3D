#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextCoord;

out V2F
{
    vec3 normal;
    vec2 textCoord;
    vec3 fragPos;
} v2f;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

uniform float u_Inflation;

void main()
{
    v2f.normal = mat3(transpose(inverse(u_Model))) *  aNormal;
    v2f.textCoord = aTextCoord;
    v2f.fragPos = vec3(u_Model * vec4(aPos, 1.0f));
    
    gl_Position = u_Projection * u_View * u_Model * (vec4(aPos + (v2f.normal * u_Inflation), 1.0f));
}
