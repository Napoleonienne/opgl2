#include <object.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <Shader.hpp>
#include <vector>
#include <glad.h>





void   object::setrotation(char axe,float angle){
    glm::vec3 rotation(0.);
    switch (axe)
    {
    case 'x' :
        rotation = {1.,0.0,0.};
        break;
    case 'y':
        rotation = {0.,1.0,0.};

        break;
    case 'z':
        rotation = {0.,0.0,1.};

        break;
    default:
        break;
    }

    glm::quat q(glm::radians(angle),rotation);
    
    auto nv_rotation= glm::mat4_cast(q);

    modele = nv_rotation*modele;
}
void    object::setscale(glm::vec3 taille){
    modele = glm::scale(glm::mat4(1.0f),taille) *modele;
}
void object::setposition(glm::vec3 position){
    modele = glm::translate(glm::mat4(1.0f),position)*modele;
}
glm::vec3 object::getrotation(){

    glm::mat3 rotationMatrix;
    rotationMatrix[0] = glm::normalize(glm::vec3(modele[0]));
    rotationMatrix[1] = glm::normalize(glm::vec3(modele[1]));
    rotationMatrix[2] = glm::normalize(glm::vec3(modele[2]));
    glm::quat rotation = glm::quat_cast(rotationMatrix);
    glm::vec3 euler = glm::eulerAngles(rotation);
    euler = glm::degrees(euler);
    return euler;
}
glm::vec3 object::gettaile(){
    glm::vec3 scale;
    scale.x = glm::length(glm::vec3(modele[0]));
    scale.y = glm::length(glm::vec3(modele[1]));
    scale.z = glm::length(glm::vec3(modele[2]));

    return scale;
}
glm::vec3 object::getposition(){

    return glm::vec3(modele[3]);
}

void object::setshader(Shader a){
        shade = a;
}


