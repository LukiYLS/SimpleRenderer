#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 lightPV;

out vec3 Position;
out vec3 Normal;
out vec2 Uv;
out vec4 LightSpacePos;

void main()
{
	Position = vec3(modelMatrix * vec4(position, 1.0));
	Normal = transpose(inverse(mat3(modelMatrix))) * normal;
	Uv = tex;
	LightSpacePos = lightPV * vec4(Position, 1.0);
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
}
