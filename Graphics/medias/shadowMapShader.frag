#version 430

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec4 ShadowCoord;

uniform struct LightInfo {
	vec4 Position;
	vec3 Intensity;

} Light;

uniform struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shininess;

} Material;

uniform sampler2DShadow shadowMap;

layout(location=0) out vec4 FragColor;

subroutine void RenderPassType();
subroutine uniform RenderPassType renderPass;


vec3 diffuseAndSpecPhongShading() {
	vec3 n = Normal;
	vec3 v = normalize(-Position);
	vec3 s = normalize(vec3(Light.Position) - Position);
	vec3 h = v + s;

	float sDotN = max(dot(s, n), 0.0f);
	vec3 diffuse = Material.Kd * sDotN;

	vec3 spec = vec3(0.0f);
	if (sDotN > 0.0) {
		spec = Material.Ks * pow(max(dot(h, n), 0.0f), Material.Shininess);
	}

	return Light.Intensity * (diffuse + spec);
}

layout(index=0) subroutine (RenderPassType)
void recordPass() {
	// depth is recorded to the depth map automatically
}

layout(index=1) subroutine (RenderPassType)
void shadowPass() {
	vec3 ambient = Light.Intensity * Material.Ka;
	vec3 diffAndSpec = diffuseAndSpecPhongShading();

	float shadow = 1.0f;
	if (ShadowCoord.z >= 0.0) {
		shadow = textureProj(shadowMap, ShadowCoord);
	}

	// shadow == 0, then shadowCoord.z > shadowMap value, and not pass the depth test(GL_LESS), that is the fragment is under the shadow(further and behind)
	FragColor = vec4(diffAndSpec * shadow + ambient, 1.0f);
	//FragColor = Color;

	// Gamma correct
    FragColor = pow( FragColor, vec4(1.0 / 2.2) );

	//FragColor = texture(shadowMap, TexCoord) + vec4(1.0f, 0.0f, 0.0f, 1.0f);

}


void main() {
	renderPass();
}