#version 330 core

layout(location = 0)in vec3 position;
layout(location = 1)in vec3 normal;
layout(location = 2)in vec2 tex;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uv;
void main(){
	gl_Position = projectionMatrix * viewMatrix * modelMatrix *vec4(position.xyz,1.0);
	uv = tex;
}
