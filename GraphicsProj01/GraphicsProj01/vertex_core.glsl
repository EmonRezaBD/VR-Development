#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec3 vertex_textcoord;

out vec3 vs_position;
out vec3 vs_color;
out vec3 vs_texcoord;

void main()
{
	vs_position = vertex_position;
	vs_color = vertex_color;
	vs_textcoord = vec2(vertex_texcoord.x, vertex_texcoord.y * -1.f);

	gl_position = vec4(vertex_position, 1.f);
}

