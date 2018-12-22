#version 330

in vec2 uvs;
uniform sampler2D depthMap;

void main()
{
	vec4 Color = texture(depthMap, uvs);	
	gl_FragColor = vec4(1.0,0.0,0.0,1.0) ;
}