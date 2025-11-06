#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Shader.hpp"

struct lightpoint{

};

class lamp {
public:
    lamp(glm::vec3 pos, float taille, Shader shade);

    void init();
    void detruire();
    void dessiner(const glm::mat4& projection, const glm::mat4& model, const glm::mat4& view);

    glm::vec3 position;
    Shader shader;

private:
    unsigned int lightVAO = 0;
    unsigned int VBO = 0;
    unsigned int EBO = 0;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
};
