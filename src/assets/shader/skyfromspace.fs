// Atmospheric scattering fragment shader
// Author: Sean O'Neil
// Copyright (c) 2004 Sean O'Neil

#version 330

uniform vec3 v3LightDirection;
uniform float g;
uniform float g2;

varying vec3 v3Direction;
varying vec3 rayleiColor;
varying vec3 mieColor;
void main (void)
{
	float fCos = dot(v3LightDirection, v3Direction) / length(v3Direction);
	float fRayleighPhase = 0.75*(1.0 + fCos * fCos);
	float fMiePhase = (1.0 - g2) / (2.0 + g2) * (1.0 + fCos * fCos) / pow(1.0 + g2 - 2.0 * g * fCos, 1.5);
	gl_FragColor = vec4(1.0 - exp(-1.5 * (fRayleighPhase * rayleiColor + fMiePhase * mieColor)), 1.0);
	//gl_FragColor = vec4(1.0 - exp(-1.5 * (fRayleighPhase * rayleiColor)), 1.0);

	//gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}

