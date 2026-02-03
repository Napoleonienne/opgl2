module;  // Global module fragment
#include <glm/glm.hpp>
#include <entt/entt.hpp>

export module ecs;  // Déclaration du module
#import std;

// La régie reste ici : elle est privée au module.
// Personne à l'extérieur ne peut la corrompre.
entt::registry registry;

export namespace ecs {
    // Fonctions d'entités
    entt::entity create_entity() {
        return registry.create();
    }
    
    void destroy_ent(entt::entity entity) {
        registry.destroy(entity);
    }
    
    // Composants
    struct Physique {
        float masse;
    };
    
    struct Texture {
        unsigned int id;
        std::string type;
    };
    
    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
    };
    
    struct Mesh {
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
    };
}