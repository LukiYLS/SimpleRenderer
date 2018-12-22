
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal ;

uniform mat3 viewRotation;
uniform mat4 projection;
uniform float farPlane;
varying vec3 tex_coords;
void main()
{
	vec3 viewPosition = viewRotation * position;
	gl_Position = projection * vec4(viewPosition,1.0);
	gl_Position = gl_Position.xyww;
	tex_coords = position.xyz;
}