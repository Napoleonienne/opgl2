#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>

#include <vector>


struct Material {
   glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
struct vertex
{
   std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normale;
    std::vector<GLuint> indices;
    std::vector<glm::vec2> uv;
};


class object{
    public:
    Shader shade;

    object(glm::vec3 origine,float rayon,glm::vec3 _couleur,Shader a);

    void dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision);
    void destroy();
    void init();

    private:
    Material materiel;
    vertex vertex;
    
    glm::vec3 rot;
    glm::vec3 scale;
 
    glm::mat4 modele;
    glm::vec3 couleur;
    unsigned int VBO, VAO, EBO;


};