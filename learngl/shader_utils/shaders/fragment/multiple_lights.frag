#version 330 core

struct DirLight
{
    vec4 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoords;

out vec4 color;

uniform mat4 view;

in vec3 Normal;
in vec4 FragPos;

uniform DirLight dirLight;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_ambient1;
uniform sampler2D texture_specular1;

vec3 CalcDirLight(DirLight light, vec4 normal, vec4 viewDir);

void main()
{
    // Calculation in camera space so view is always start of coords
    vec4 viewPos = vec4(0.f, 0.f, 0.f, 1.f);
    vec4 norm = normalize(vec4(Normal, 0.f));
    vec4 viewDir = normalize(viewPos - FragPos);

    color = vec4(CalcDirLight(dirLight, norm, viewDir), 1.0);
}

vec3 CalcDirLight(DirLight light, vec4 normal, vec4 viewDir)
{
    vec4 lightDir = normalize(light.direction);
    // Diffuse shading
    float diff = max(dot(normal, -lightDir), 0.0);
    // Specular shading
    vec4 reflectDir = reflect(lightDir, normal);
    // Combine results
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 specular = light.specular * vec3(texture(texture_specular1, TexCoords));
    return (ambient + diffuse + specular);
}

