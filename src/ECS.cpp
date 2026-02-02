#include <ecs.hpp>


namespace ecs{

    entt::entity create_entity(){
        entt::entity entity = registry.create();
        return entity;
    }


    void destroy_ent(entt::entity entity){
        registry.destroy(entity);
    }


}