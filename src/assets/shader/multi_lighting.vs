#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;	

out vec3 Normal;
out vec3 Position;
out vec2 Uvs;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix *  modelMatrix * vec4(position, 1.0f);
    Position = vec3(modelMatrix * vec4(position, 1.0f));
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;//模型变换时（主要是缩放时会导致法线和切线不垂直）
    Uvs = texCoords;
}