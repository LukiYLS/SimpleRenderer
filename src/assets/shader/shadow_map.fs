#version 330 core

in vec3 Position;
in vec3 Normal;
in vec2 Uv;
in vec4 LightSpacePos;
struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    
    float constant;
    float linear;
    float quadratic;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D shadowMap;
uniform sampler2D texture;
uniform SpotLight spotLight;
//uniform DirLight dirLight;
uniform vec3 viewPos;

float CalcShadowFactor(vec4 lightspacePos)
{
	vec3 projectCoords = lightspacePos.xyz / lightspacePos.w;
	projectCoords *= 0.5 +0.5;
	
	float nearDepth = texture(shadowMap, projectCoords.xy).r;
	float currentDepth = projectCoords.z;
	
	return nearDepth;//currentDepth > nearDepth ? 1.0 : 0.0; //1.0 means in the shadow
}
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir, float shadowFactor )
{
    vec3 lightDir = normalize( -light.direction );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 256 );
    
    // Combine results
    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;
    
    return ( ambient + shadowFactor * (diffuse + specular ));
}
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 Position, vec3 viewDir, float shadowFactor)
{
    vec3 lightDir = normalize( light.position - Position );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow( max( dot( normal, halfwayDir), 0.0), 256);
    //float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 256 );
    
    // Attenuation
    float distance = length( light.position - Position );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Spotlight intensity
    float theta = dot( lightDir, normalize( -light.direction ) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );
    
    // Combine results
    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff ;
    vec3 specular = light.specular * spec;
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ( ambient + shadowFactor * (diffuse + specular) );
}

void main()
{
	float shadowFactor = CalcShadowFactor(LightSpacePos); 
	vec3 norm = normalize( Normal );
    vec3 viewDir = normalize( viewPos - Position );
    vec3 light = CalcSpotLight( spotLight, norm, Position, viewDir, shadowFactor );
	vec3 color = texture(texture, Uv).rgb;
    gl_FragColor = vec4(vec3(shadowFactor), 1.0);   
}