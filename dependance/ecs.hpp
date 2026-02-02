#pragma once
#include <entt.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace ecs{
entt::registry registry;
entt::entity create_entity();
void destroy_ent(entt::entity entity);

namespace component{
struct physique
{
    float masse;
};

struct Texture {
    unsigned int id;
    std::string type;
};  


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

struct pbr{
    float metal;
    float b;
    float c;
}

struct vertex
{
   glm::vec2 uv; 
   glm::vec3 vertice;
   uint pos;

};
struct mesh{
    std::vector<int> indice;
    std::vector<vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
};

struct transform{
    glm::vec3 pos;
    glm::vec3 orientation;
}
};







}