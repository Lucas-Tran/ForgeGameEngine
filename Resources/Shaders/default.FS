#version 330 core



uniform vec3 viewPos;

out vec4 outColor;

in vec2 textureCoordinates;
in vec3 normalCoordinates;
in vec3 fragPos;

struct Material {
    sampler2D diffuseTexture;
    sampler2D specularTexture;
    float shininess;
};

uniform Material material;

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_DIR_LIGHTS 0
#if NR_DIR_LIGHTS > 0
uniform DirLight dirLights[NR_DIR_LIGHTS];
#endif


struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 1
#if NR_POINT_LIGHTS > 0
uniform PointLight pointLights[NR_POINT_LIGHTS];
#endif

struct SpotLight {
    vec3 position;     // Light source coordinates
    vec3 direction;    // Target direction vector (normalized)
    
    float cutOff;      // Cosine of the inner cone angle
    float outerCutOff; // Cosine of the outer cone angle (for smooth edges)
    
    // Attenuation coefficients (how light dims over distance)
    float constant;
    float linear;
    float quadratic;
    
    // Color properties
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_SPOT_LIGHTS 0
#if NR_DIR_LIGHTS > 0
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
#endif

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main() {
    vec3 norm = normalize(normalCoordinates);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result = vec3(0.0f);

    #if NR_DIR_LIGHTS > 0
    for(int i = 0; i < NR_DIR_LIGHTS; i++)
        result += CalcDirLight(dirLights[i], norm, viewDir);
    #endif
    #if NR_POINT_LIGHTS > 0
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, viewDir);
    #endif
    #if NR_SPOT_LIGHTS > 0
    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
        result += CalcSpotLight(spotLights[i], norm, viewDir);
    #endif
   outColor = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 specular = light.specular * spec * vec3(texture(material.specularTexture, textureCoordinates));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 specular = light.specular * spec * vec3(texture(material.specularTexture, textureCoordinates));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    
    // 1. Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
    // 2. Specular shading (using Blinn-Phong for better accuracy)
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    
    // 3. Attenuation (distance fade)
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // 4. Spotlight intensity (cone restriction)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    // 5. Combine results
    vec3 ambient  = light.ambient * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuseTexture, textureCoordinates));
    vec3 specular = light.specular * spec * vec3(texture(material.specularTexture, textureCoordinates));
    
    // Note: If you use textures, multiply them here: (e.g., diffuse * texture(texture_diffuse1, TexCoords).rgb)
    
    ambient  *= attenuation;
    diffuse  *= attenuation * intensity;
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}