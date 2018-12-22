#version 330 core

#define NUMBER_OF_POINT_LIGHTS 4

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
    
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

in vec3 Position;
in vec3 Normal;
in vec2 Uvs;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLight;//[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;
//uniform Material material;
uniform sampler2D texture1;
// Function prototypes
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir );
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 Position, vec3 viewDir );
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 Position, vec3 viewDir );

void main( )
{
    // Properties
    vec3 norm = normalize( Normal );
    vec3 viewDir = normalize( viewPos - Position );
    
    // Directional lighting
    vec3 result = CalcDirLight( dirLight, norm, viewDir );
    
    // Point lights
    //for ( int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++ )
    //{
       result += CalcPointLight( pointLight, norm, Position, viewDir );
    //}
    
    // Spot light
    result += CalcSpotLight( spotLight, norm, Position, viewDir );
    
    color = vec4( result, 1.0 );
}

// Calculates the color when using a directional light.
vec3 CalcDirLight( DirLight light, vec3 normal, vec3 viewDir )
{
    vec3 lightDir = normalize( -light.direction );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 256 );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( texture1, Uvs ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( texture1, Uvs ) );
    vec3 specular = light.specular * spec * vec3( texture( texture1, Uvs ) );
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a point light.
vec3 CalcPointLight( PointLight light, vec3 normal, vec3 Position, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - Position );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 256 );
    
    // Attenuation
    float distance = length( light.position - Position );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( texture1, Uvs ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( texture1, Uvs ) );
    vec3 specular = light.specular * spec * vec3( texture( texture1, Uvs ) );
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return ( ambient + diffuse + specular );
}

// Calculates the color when using a spot light.
vec3 CalcSpotLight( SpotLight light, vec3 normal, vec3 Position, vec3 viewDir )
{
    vec3 lightDir = normalize( light.position - Position );
    
    // Diffuse shading
    float diff = max( dot( normal, lightDir ), 0.0 );
    
    // Specular shading
    vec3 reflectDir = reflect( -lightDir, normal );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), 256 );
    
    // Attenuation
    float distance = length( light.position - Position );
    float attenuation = 1.0f / ( light.constant + light.linear * distance + light.quadratic * ( distance * distance ) );
    
    // Spotlight intensity
    float theta = dot( lightDir, normalize( -light.direction ) );
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp( ( theta - light.outerCutOff ) / epsilon, 0.0, 1.0 );
    
    // Combine results
    vec3 ambient = light.ambient * vec3( texture( texture1, Uvs ) );
    vec3 diffuse = light.diffuse * diff * vec3( texture( texture1, Uvs ) );
    vec3 specular = light.specular * spec * vec3( texture( texture1, Uvs ) );
    
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return ( ambient + diffuse + specular );
}