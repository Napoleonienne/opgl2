#include <glm/glm.hpp>
#include <cube.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>

#include <vector>


struct Material;
struct light;

cube::cube(glm::vec3 origine,float taille,glm::vec3 _couleur,Shader a,GLuint VBOP):shade(a){
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
    normale.assign(36,glm::vec3(0.0));

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

    for (size_t i = 0; i < indices.size(); i += 3)
    {
        glm::vec3 A = vertices[indices[i]];
        glm::vec3 B = vertices[indices[i + 1]];
        glm::vec3 C = vertices[indices[i + 2]];

        glm::vec3 normalFace = glm::normalize(glm::cross(B - A, C - A));

        // Ajouter cette normale aux 3 vertices pour un lissage
        normale[indices[i]]     += normalFace;
        normale[indices[i + 1]] += normalFace;
        normale[indices[i + 2]] += normalFace;
    }

    // Normaliser toutes les normales des vertices
    for (size_t i = 0; i < normale.size(); i++)
    {
        normale[i] = glm::normalize(normale[i]);
    }


init();
};

void cube::init(){

   glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glGenBuffers(1,&EBO);

    GLsizeiptr posSize = vertices.size() * sizeof(glm::vec3);
    GLsizeiptr uvSize  = uv.size()       * sizeof(glm::vec2);
    GLsizeiptr normalsize = normale.size() * sizeof(glm::vec3);

    GLsizeiptr totalSize = posSize + uvSize +normalsize;

    // allocation
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, totalSize, nullptr, GL_STATIC_DRAW);

    // remplissage
    glBufferSubData(GL_ARRAY_BUFFER, 0, posSize, vertices.data());
    glBufferSubData(GL_ARRAY_BUFFER, posSize,  uvSize,  uv.data());
    glBufferSubData(GL_ARRAY_BUFFER,uvSize,normalsize,normale.data());
    // indices en EBO, toujours leur royaume s�par�
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // attributs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)posSize);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)posSize);
    glEnableVertexAttribArray(2);




    glBindVertexArray(0);

};


void cube::dessiner(glm::mat4 procj, glm::mat4 model,glm::mat4 vision){

    shade.use();
    shade.set("model",model);
    shade.set("projection",procj);
    shade.set("view", vision);
    shade.set("couleur",couleur);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
}
void cube::materiel(type::Material rFlum){
    shade.set("material.ambient",rFlum.ambient);
    shade.set("material.diffuse",rFlum.diffuse);
    shade.set("material.shininess",rFlum.shininess);
    shade.set("material.specular",rFlum.specular);
}

void cube::lumiere(type::LUMI sourceLumineuse){
    

    shade.set("light.ambient",sourceLumineuse.ambient);
    shade.set("light.diffuse",sourceLumineuse.diffuse);
    shade.set("light.position",sourceLumineuse.position);
    shade.set("light.specular",sourceLumineuse.specular);

}
void cube::destroy(){
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);
    glDeleteVertexArrays(1,&VAO);

}