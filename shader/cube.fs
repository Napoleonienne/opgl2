#version 450 core

out vec4 FragColor;

uniform vec3 couleur;      // Couleur de l’objet
uniform vec3 camerapos;    // Position de la caméra

in vec3 normale;          
in vec3 FragPos;   
in vec2 aPosTEX;        

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 couleur;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform sampler2D tex;
uniform sampler2D texure_spec;



void main()
{
    // paramètres
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    // Composante ambiante
    vec3 ambient =  vec3(material.ambient * light.couleur);

    // Composante diffuse
    vec3 norm = (normale);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (material.diffuse*diff) * light.couleur;

    // Composante spéculaire
    vec3 viewDir = normalize(camerapos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),  material.shininess);
    vec3 specular = material.specular * spec * light.couleur;

    // Résultat final
    vec3 result = (ambient + diffuse + specular) * couleur;
    FragColor = vec4(result, 1.0);
}
