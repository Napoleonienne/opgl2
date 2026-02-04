#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <Shader.hpp>
#include <string>

struct Texture {
    unsigned int id;
    std::string type;
};  

struct vertex
{
   glm::vec2 uv; 
   glm::vec3 vertice;
   uint pos;

};

class Mesh {
    public:
        // mesh data
        std::vector<vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        ~Mesh();
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();
};  