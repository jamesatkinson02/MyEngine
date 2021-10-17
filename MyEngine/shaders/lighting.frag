#version 430 core

in GS_OUT
{
	in vec2 outTexCoords;
    in vec3 outNormals;
	in vec4 outLightSpaceFragPos;
	in vec3 outFragPos;
	//in mat3 outTBN;
} fs_in;

out vec4 finalColor;

struct dirLight
{
	vec3 target;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct pointLight
{
	vec3 pos;
	vec3 target;
	float aConstant;
	float aLinear;
	float aQuadratic;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct material
{
	sampler2D diffuseMap;
	sampler2D normalMap;
	sampler2D specularMap;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;				//has to be 2^n
	bool hasDiffuse;
	bool hasSpecular;
	bool hasNormalMap;
};

uniform vec3 camPos;
uniform vec3 color;
uniform dirLight sun;
uniform material mat;
uniform sampler2D shadowMap;

#define NUM_LIGHTS 4
uniform pointLight pointLights[NUM_LIGHTS];

float getAttenuation(pointLight source, float distance)
{
	float attenuation = 1 / (source.aConstant + source.aLinear * distance + source.aQuadratic * (distance * distance));
	return attenuation;
}

float calculateShadowFactor(vec4 lightSpaceFragPos, sampler2D shadowMap)
{
	vec3 perspectiveDivision = lightSpaceFragPos.xyz / lightSpaceFragPos.w;
	vec2 uvCoords;
	uvCoords.x = 0.5f * perspectiveDivision.x + 0.5f;
	uvCoords.y = 0.5f * perspectiveDivision.y + 0.5f;
	float z = 0.5 * perspectiveDivision.z + 0.5f;
	float depth = texture(shadowMap, uvCoords).x;
	float shadow = (depth < (z + 0.00001)) ? 0.2 : 1.0;
	return shadow;
}

vec3 calculateDirLight(dirLight dir_light, material m)
{
	vec3 directional = normalize(-dir_light.target);
	vec3 normal = normalize(fs_in.outNormals);
	vec3 viewPos = normalize(camPos - fs_in.outFragPos);

	vec3 halfWayDir = normalize(directional + viewPos);			//used for blinn-phong lighting
	
	vec3 finalVec;
	
	if(m.hasNormalMap)
	{
		normal = texture(m.normalMap, fs_in.outTexCoords).rgb;
		normal = normalize(normal * 2.0 - 1.0);
	}

	//normal = normalize(fs_in.outTBN * normal);
	
	float distance = length(camPos - fs_in.outFragPos);

	//float attenuation = getAttenuation(dir_light, distance);
	
	float diffuseFactor = max(dot(normal, directional), 0.2f);

	vec3 diffuseVec;

	if(m.hasDiffuse)
	{
		diffuseVec = diffuseFactor * m.ambient * dir_light.ambient * vec3(texture(m.diffuseMap,fs_in.outTexCoords)) * m.diffuse * dir_light.diffuse;
	}
	else
		diffuseVec = diffuseFactor * m.ambient * m.diffuse;

	//vec3 reflected = reflect(-directional, normal);
	float specularFactor = pow(max(dot(normal, halfWayDir),0.0),m.shininess);
	
	vec3 specularVec;
	if(m.hasSpecular)
		specularVec =  specularFactor * m.specular * dir_light.specular * vec3(texture(m.specularMap,fs_in.outTexCoords));
	else
		specularVec = specularFactor * m.specular;

	//diffuseVec *= attenuation;
	//specularVec *= attenuation;

	float shadowFactor = calculateShadowFactor(fs_in.outLightSpaceFragPos, shadowMap);

	finalVec = shadowFactor * (diffuseVec + specularVec);

	return finalVec;
}

vec3 calculatePointLight(pointLight point_light, material m)
{
	vec3 lightDir = normalize(point_light.pos -fs_in.outFragPos);
	vec3 normal = normalize(fs_in.outNormals);
	vec3 viewPos = normalize(camPos - fs_in.outFragPos);
	vec3 halfWayDir = normalize(lightDir + viewPos);			//used for blinn-phong lighting

	vec3 finalVec;

	float distance = length(camPos - fs_in.outFragPos);

	float attenuation = getAttenuation(point_light, distance);
		
	float diffuseFactor = max(dot(normal, lightDir), 0.2f);

	vec3 diffuseVec;

	if(m.hasDiffuse)
		diffuseVec = diffuseFactor * m.ambient * vec3(texture(m.diffuseMap,fs_in.outTexCoords)) * m.diffuse;
	else
		diffuseVec = diffuseFactor * m.ambient * m.diffuse;

	//vec3 reflected = reflect(-lightDir, normal);
	float specularFactor = pow(max(dot(normal, halfWayDir),0.0),m.shininess);

	vec3 specularColor = vec3(1.0f);

	vec3 specularVec; 
	
	if(m.hasSpecular)
		specularVec = specularFactor * m.specular * vec3(texture(m.specularMap,fs_in.outTexCoords));
	else
		specularVec = specularFactor * m.specular;

	finalVec = diffuseVec + specularVec;

	return finalVec;
}


void main()
{
	vec3 dirLightVec = calculateDirLight(sun, mat);

	finalColor = vec4(dirLightVec, 1.0f);	
}
