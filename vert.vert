#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform mat4 model;
uniform vec3 color;
uniform float size;

void main()
{
	gl_Position = model * vec4(aPos, 1.0f);
	float sizeAdd = (size * 0.01f) + 0.1f;
	ourColor = aColor + vec3(color.x + sizeAdd, color.y +  sizeAdd, color.z + sizeAdd);
}

