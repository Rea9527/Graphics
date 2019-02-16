#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;

uniform struct LightInfo {
	vec4 Direction;
	vec3 Intensity;

} Light;

uniform struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;
} Material;

subroutine void RenderPassType();
subroutine uniform RenderPassType renderPass;

layout(binding = 0) uniform sampler2D posTex;
layout(binding = 1) uniform sampler2D normTex;
layout(binding = 2) uniform sampler2D colorTex;


layout( location = 0 ) out vec4 FragColor;
layout( location = 1 ) out vec3 PosData;
layout( location = 2 ) out vec3 NormData;
layout( location = 3 ) out vec3 ColorData;

vec3 ads(in vec3 pos, in vec3 norm, in vec3 color) {
    vec3 s = normalize( vec3(-Light.Direction));
    vec3 v = normalize(vec3(-pos));
    vec3 h = normalize( v + s );

    return
        Light.Intensity * (Material.Ka +
						  Material.Kd * max( dot(s, norm), 0.0 ) +
						 Material. Ks * pow( max( dot(h, norm), 0.0 ), Material.Shininess ) );
}

layout(index = 0) subroutine (RenderPassType)
void geometryPass() {
	PosData = Position;
	NormData = Normal;
	ColorData = Material.Kd;
}

layout(index = 1) subroutine (RenderPassType)
void lightingPass() {
	vec3 pos = vec3(texture(posTex, TexCoord));
	vec3 norm = vec3(texture(normTex, TexCoord));
	vec3 color = vec3(texture(colorTex, TexCoord));

	FragColor = vec4(ads(pos, norm, color), 1.0f);

}

void main() {

	renderPass();
}
