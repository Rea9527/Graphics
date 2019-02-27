#version 430

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 TexCoord;


uniform struct LightInfo {
	vec3 Position;
	vec3 Color;

	float Constant;
	float Linear;
	float Quadratic;

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
layout( location = 1 ) out vec3 gPos;
layout( location = 2 ) out vec3 gNormal;
layout( location = 3 ) out vec3 gColor;

vec3 ads(in vec3 pos, in vec3 norm, in vec3 color) {
    vec3 s = normalize( Light.Position - pos);
    vec3 v = normalize(vec3(-pos));
    vec3 h = normalize( v + s );

	vec3 diff = color * max( dot(s, norm), 0.0 );
	vec3 spec = Material.Ks == vec3(0.0f) ? vec3(0.0f) : Material.Ks * pow( max( dot(h, norm), 0.0 ), Material.Shininess);

	// compute attenuation for point light
	float dist = length(Light.Position - pos);
	float attenuation = 1.0f / (Light.Constant + Light.Linear * dist + Light.Quadratic * dist * dist);

	vec3 diffSpec = attenuation * (diff + spec);

    return
        Light.Color * (Material.Ka + diffSpec);
}


layout(index = 0) subroutine (RenderPassType)
void geometryPass() {
	gPos = Position;
	gNormal = Normal;
	gColor = Material.Kd;

	//FragColor = vec4(ads(Position, Normal, Material.Kd), 1.0f);
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