#version 430

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;
layout(location=2) in vec2 VertexTexCoord;
layout(location=3) in mat4 InstanceModelMat;

layout(location=0) out vec3 Position;
layout(location=1) out vec3 Normal;
layout(location=2) out vec2 TexCoord;

uniform mat4 ProjectViewMatrix;

void main() {

	Position = vec3(InstanceModelMat * vec4(VertexPosition, 1.0f));
	Normal = mat3(transpose(inverse(InstanceModelMat))) * VertexNormal;

	TexCoord = VertexTexCoord;

	gl_Position = ProjectViewMatrix * InstanceModelMat * vec4(VertexPosition, 1.0f);

}