#version 430 core

in GS_OUT
{
	in vec2 outTexCoords;
	in vec3 outNormals;
	in vec4 lightSpaceFragPos;
	in vec3 outFragPos;
} fs_in;

out vec4 finalColor;

struct light
{
	vec3 pos;
	vec3 target;
	float aConstant;
	float aLinear;
	float aQuadratic;
	float cutOff;
};

uniform vec3 camPos;
uniform vec3 color;
uniform light dirLight;

uniform sampler2D shadowMap;

float getAttenuation(light source, float distance)
{
	float attenuation = 1 / (source.aConstant + source.aLinear * distance + source.aQuadratic * (distance * distance));
	return attenuation;
}

float calculateShadowFactor(vec4 lightSpaceFragPos)
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


vec3 calculatePointLight(light point_light, vec3 objectColor)
{
	vec3 lightDir = normalize(point_light.pos -fs_in.outFragPos);
	vec3 normal = normalize(fs_in.outNormals);
	vec3 viewPos = normalize(camPos - fs_in.outFragPos);
	vec3 halfWayDir = normalize(lightDir + viewPos);			//used for blinn-phong lighting

	vec3 finalVec;

	float distance = length(camPos - fs_in.outFragPos);

	float attenuation = getAttenuation(point_light, distance);
	
	float diffuseFactor = max(dot(normal, lightDir), 0.2f);
	vec3 diffuseVec = diffuseFactor * objectColor;

	//vec3 reflected = reflect(-lightDir, normal);
	float specularFactor = pow(max(dot(normal, halfWayDir),0.0),64);
	
	vec3 specularVec = specularFactor * vec3(1.0f); 

	diffuseVec *= attenuation;
	specularVec *= attenuation;


	finalVec = diffuseVec + specularVec;

	return finalVec;
}

vec3 calculateFlashLight(light flashLight)
{
	vec3 spotDir = flashLight.target;
	vec3 lightDir = normalize(fs_in.outFragPos - flashLight.pos);

	vec3 finalVec = vec3(1.0f);

	float angle = dot(lightDir, spotDir);
	if(angle > flashLight.cutOff)
	{
		finalVec = vec3(1.0f) * ((1 - (1-angle)) / (1 - flashLight.cutOff));
	}
	else
	{
		finalVec = vec3(0.2f);
	}	

	return finalVec;
}

vec3 calculateDirLight(light dir_light, vec3 objectColor)
{
	vec3 directional = normalize(-dir_light.target);
	vec3 normal = normalize(fs_in.outNormals);
	vec3 viewPos = normalize(camPos - fs_in.outFragPos);

	vec3 halfWayDir = normalize(directional + viewPos);			//used for blinn-phong lighting
	
	vec3 finalVec;


	float distance = length(camPos - fs_in.outFragPos);

	float attenuation = getAttenuation(dir_light, distance);
	
	float diffuseFactor = max(dot(normal, directional), 0.2f);
	vec3 diffuseVec = diffuseFactor * objectColor;

	//vec3 reflected = reflect(-directional, normal);
	float specularFactor = pow(max(dot(normal, halfWayDir),0.0),64);
	
	vec3 specularVec = specularFactor * vec3(1.0f); 

	diffuseVec *= attenuation;
	specularVec *= attenuation;

	float shadowFactor = calculateShadowFactor(fs_in.lightSpaceFragPos);

	finalVec = shadowFactor * (diffuseVec + specularVec);

	return finalVec;
}

void main()
{
	vec3 dirLightVec = calculateDirLight(dirLight, color);
	finalColor = vec4(dirLightVec, 1.0f);	
}
