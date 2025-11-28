#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>
#include <object3d.hpp>

#include <vector>

struct Maeriel;


class Sphere:object{
    public:
    Shader shade;

    Sphere(glm::vec3 origine,float rayon,glm::vec3 _couleur,Shader a);

    void dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision);
    void destroy();
    void init();
    void materiel();
    void lumiere();
    private:
    int face =100;
    float pi =glm::pi<float>();
    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normale;
    std::vector<GLuint> indice;
    std::vector<glm::vec2> uv;
    glm::vec3 couleur;
    unsigned int VBO, VAO, EBO,VBO2;



    
};