#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <glm/glm.hpp>

namespace ecs{
entt::registry registry;
entt::entity create_entity();
void destroy_ent(entt::entity entity);


struct physique
{
    float masse;
};

struct Texture {
    unsigned int id;
    std::string type;
};  

struct Material
{
    /* data */
};


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
    
}









}