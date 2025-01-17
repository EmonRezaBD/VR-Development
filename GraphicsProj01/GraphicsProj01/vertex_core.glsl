#version 450

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_texcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord; // Corrected this variable name

uniform mat4 ModelMatrix;


void main()
{
    //vs_position = vertex_position;
    vs_position = vec4(ModelMatrix * vec4(vertex_position, 1.f)).xyz;
    vs_color = vertex_color;
    vs_texcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f); // Make sure to use vs_texcoord

    gl_Position = ModelMatrix * vec4(vertex_position, 1.f);
    //gl_Position = vec4(vertex_position, 1.f);
    //gl_Position = vec4(vertex_position + 0.2f, 1.f); //it'll move the drawing
}
