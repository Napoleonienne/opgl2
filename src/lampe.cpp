#include "lampe.hpp"
#include <glad.h>

lamp::lamp(glm::vec3 pos, float taille, glm::vec3 couleur, Shader shade)
    : position(pos), shader(shade),lightColor(couleur)
{
    float h = taille * 0.5f;

    vertices = {
        // Face avant
        pos + glm::vec3(-h, -h,  h),
        pos + glm::vec3( h, -h,  h),
        pos + glm::vec3( h,  h,  h),
        pos + glm::vec3(-h,  h,  h),
        // Face arri�re
        pos + glm::vec3(-h, -h, -h),
        pos + glm::vec3( h, -h, -h),
        pos + glm::vec3( h,  h, -h),
        pos + glm::vec3(-h,  h, -h)
    };

    indices = {
        0, 1, 2, 2, 3, 0, // avant
        4, 5, 6, 6, 7, 4, // arri�re
        4, 0, 3, 3, 7, 4, // gauche
        1, 5, 6, 6, 2, 1, // droite
        3, 2, 6, 6, 7, 3, // haut
        4, 5, 1, 1, 0, 4  // bas
    };
    
    init();
}

void lamp::init() {
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Attribut : position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void lamp::detruire() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &lightVAO);
}

void lamp::dessiner(const glm::mat4& projection, const glm::mat4& model, const glm::mat4& view) {
    shader.use();
    shader.set("lightColor",lightColor);
    shader.set("model", model);
    shader.set("projection", projection);
    shader.set("view", view);

    glBindVertexArray(lightVAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
