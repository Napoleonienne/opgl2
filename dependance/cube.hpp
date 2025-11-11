#pragma once
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>

#include <vector>



class cube{
    public:
    Shader shade;

    cube(glm::vec3 origine,float rayon,glm::vec3 _couleur,Shader a);

    void dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision);
    void destroy();
    void init();
    private:
    int face =100;
    float pi =glm::pi<float>();
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normale;
    std::vector<GLuint> indices;
    std::vector<glm::vec2> uv;
    glm::vec3 couleur;
    unsigned int VBO, VAO, EBO,VBO2;



    
};