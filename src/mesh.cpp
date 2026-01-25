#include <mesh.hpp>
#include <glad.h>


Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){

}
Mesh::setupMesh(){
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glCreateVertexArrays(1,&VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
}