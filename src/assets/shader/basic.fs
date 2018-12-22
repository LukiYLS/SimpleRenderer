#version 330

in vec2 uv;

uniform sampler2D texture1;
void main()
{		
	vec4 Color = texture(texture1, uv);	
	gl_FragColor = Color ;
}