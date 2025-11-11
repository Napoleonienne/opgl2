#include <glm/glm.hpp>
#include <cube.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>

#include <vector>



cube::cube(glm::vec3 origine,float taille,glm::vec3 _couleur,Shader a){
        float h = taille * 0.5f;

    vertices = {
        // Face avant
        origine + glm::vec3(-h, -h,  h),
        origine + glm::vec3( h, -h,  h),
        origine + glm::vec3( h,  h,  h),
        origine + glm::vec3(-h,  h,  h),
        // Face arri�re
        origine + glm::vec3(-h, -h, -h),
        origine + glm::vec3( h, -h, -h),
        origine + glm::vec3( h,  h, -h),
        origine + glm::vec3(-h,  h, -h)
    };

    indices = {
        0, 1, 2, 2, 3, 0, // avant
        4, 5, 6, 6, 7, 4, // arri�re
        4, 0, 3, 3, 7, 4, // gauche
        1, 5, 6, 6, 2, 1, // droite
        3, 2, 6, 6, 7, 3, // haut
        4, 5, 1, 1, 0, 4  // bas
    };
     uv = {
    // Face avant
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    // Face arrière
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    // Face gauche
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    // Face droite
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    // Face haut
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    // Face bas
    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
};
init();
};

void cube::init(){

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1,&VBO2);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, uv.size()* sizeof(glm::vec3), uv.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(1);




    glBindVertexArray(0);

}


