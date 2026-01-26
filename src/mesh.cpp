#include <mesh.hpp>
#include <glad.h>


Mesh::Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){

}
void Mesh::setupMesh(){
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);
    glCreateVertexArrays(1,&VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    
}