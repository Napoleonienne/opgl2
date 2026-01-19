#pragma once
#include <glm/glm.hpp>





struct vertex
{
   glm::vec2 uv; 
   glm::vec3 vertice;
   uint pos;

};

class mesh {
public:
    mesh() ;
    ~mesh() ;
    void load_obj(const char* path);

    private: 
    int *verte;






};