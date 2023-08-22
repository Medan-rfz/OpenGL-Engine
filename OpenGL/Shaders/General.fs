#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform sampler2D selfTexture;

in vec2 fragmentTexture;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

float specularStrength = 0.5f;
int reflectPower = 35;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), reflectPower);
    vec3 specular = specularStrength * spec * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = (ambient + diffuse + specular);
    color = vec4(result, 1.0f) * texture(selfTexture, fragmentTexture);
}
