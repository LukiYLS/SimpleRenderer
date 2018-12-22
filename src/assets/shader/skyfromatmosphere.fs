#version 330 core

uniform vec3 v3LightDirection;
uniform float g;
uniform float g2;

varying vec3 v3Direction;
varying vec3 rayleiColor;
varying vec3 meiColor;
void main (void)
{
	float fCos = dot(v3LightDirection, v3Direction) / length(v3Direction);
	float fRayleighPhase = 1.0 + fCos * fCos;
	float fMiePhase = (1.0 - g2) / (2.0 + g2) * (1.0 + fCos * fCos) / pow(1.0 + g2 - 2.0 * g * fCos, 1.5);
	gl_FragColor = vec4(1.0 - exp(-1.5 * (fRayleighPhase * rayleiColor + fMiePhase * meiColor)), 1.0);
}

