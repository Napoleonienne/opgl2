#include <glm/glm.hpp>
struct texture
{
   const char* name;
   glm::vec3 DIFFUSE= {0,0,0};
   glm::vec3 specular = {0,0,0};
   glm::vec3 SPECULAR = {0,0,0};
   glm::vec3 AMBIENT = {0,0,0};
   glm::vec3 EMISSIVE = {0,0,0};
   glm::vec3 TRANSPARENT = {0,0,0};
   glm::vec3 REFLECTIVE = {0,0,0};
    float REFLECTIVITY = 0.0;
    bool wireframe= true;


    void get(){}
   
};
