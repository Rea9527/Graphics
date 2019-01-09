#version 430

in vec3 Position;
in vec3 Normal;

layout(location=0) out vec4 FragColor;

layout(binding=0) uniform samplerCube cubemap;

void main() {

	FragColor = texture(cubemap, Position);
}