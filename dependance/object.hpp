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
    float irégularité;
    float transparence;
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
    void component();

    glm::vec3 get_position();
    glm::vec3 get_rotation();
    glm::vec3 get_taille(); 
    void set_rotation(float angle,char axe='x');
    void set_taille(glm::vec3);
    void set_position(glm::vec3 nv_position);

    private:
    
    Material materiel;
    vertex vertex;
    
    glm::vec3 rot;
    glm::vec3 scale;
 
    glm::mat4 modele;
    glm::vec3 couleur;
    unsigned int VBO, VAO, EBO;


};