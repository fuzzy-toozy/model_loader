#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};

struct Light {
    vec4 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float linear;
    float constant;
    float quadratic;
};

in vec2 TexCoords;

out vec4 color;

uniform vec3 viewPos;
uniform mat4 view;

in vec3 Normal;
in vec3 FragPos;

uniform Material material;
uniform Light light;

void main()
{
    vec4 camLightPos = view * light.position;
    vec4 camTargetPos = view * vec4(light.direction, 1.f);
    vec4 lightDir = normalize(vec4(FragPos, 1.0f) - camLightPos);
    vec4 lightSpotDir = normalize(camTargetPos - camLightPos); 

    float cutOff = 0.997;
    float outCutOff = 0.993;
    float epsilon = cutOff - outCutOff;
    float calcCutOff = dot(lightSpotDir, lightDir);
    float intensity = clamp((calcCutOff - outCutOff) / epsilon, 0.0, 1.0);

        float distance = length(vec4(FragPos, 1.0f) - light.position);
        float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords)) * attenuation;
        // Diffuse
        vec4 norm = vec4(normalize(Normal), 0.f);
        float diff = max(dot(norm, -lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff *  vec3(texture(material.diffuse, TexCoords)) * attenuation * intensity;

        // Specular
        vec3 viewDir = normalize(-FragPos);
        vec3 reflectDir = vec3(normalize(reflect(lightDir, norm)));
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords)) * attenuation * intensity;

        vec3 emission = vec3(texture(material.emission, TexCoords)) * 0;
    
        vec3 result = ambient + diffuse + specular + emission;
        color = vec4(result, 1.0f); 
}