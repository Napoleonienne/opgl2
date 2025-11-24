#pragma once

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>
#include <vector>
#include <vector>


namespace type{
struct LUMI {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


struct Material {
    glm::vec3 clu;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};
};

struct Vertex
{
   std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normale;
    std::vector<GLuint> indices;
    std::vector<glm::vec2> uv;
};

class object{
    public:
    Shader shade;

    object(GLuint vbo);

    void dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision);
    void destroy();
    void init();



    void material(type::Material mat);
    void texture(unsigned int tex);
    
    void    translate(glm::vec3 nv_position);
    void    setposition(glm::vec3 nv_position) ;
    void   setrotation(char axe,float angle) ;
    void    setscale(glm::vec3 taille)  ;

    glm::vec3  getposition()  ;
    glm::vec3  getrotation() ;
    glm::vec3  gettaile() ;



    private:
    int espace_pris;
    std::vector<unsigned int> textures;
    type::Material materiel;
    Vertex vertex;
    
    glm::vec3 rot;
    glm::vec3 scale;
 
    glm::mat4 modele;
    glm::vec3 couleur;
    GLuint VBO;
    unsigned int  VAO, EBO;


};
