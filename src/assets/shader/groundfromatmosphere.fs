#version 330 core

uniform sampler2D earthmap;
uniform sampler2D cloud;
uniform sampler2D light;

varying vec3 rayleiColor;
varying vec3 meiColor;
varying vec2 uvs;

void main (void)
{
	vec3 Clouds = texture2D(cloud, uvs).rgb;
	vec3 Lights = texture2D(light, uvs).rgb;
	vec3 mixColor = mix(Clouds, Lights, 0.5);
	gl_FragColor = vec4(rayleiColor.rgb + mix(texture2D(earthmap, uvs).rgb, mixColor, dot(vec3(0.33), mixColor)) * meiColor.rgb, 1.0);
}
