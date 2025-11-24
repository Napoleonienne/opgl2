#include <object.hpp>
#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Shader.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>



glm::vec3 object::get_position(){
    return glm::vec3( modele[3]);
}
glm::vec3 object::get_rotation(){

    glm::vec3 rotx = glm::normalize(modele[0]);
    glm::vec3 roty  = glm::normalize(modele[1]);
    glm::vec3 rotz = glm::normalize(modele[2]);
    glm::mat3 matrix_rotation = {rotx,roty,rotz};
    auto rotation = glm::quat_cast(matrix_rotation);
    auto angle = glm::eulerAngles(rotation);


    return glm::degrees(angle);
}
glm::vec3 object::get_taille(){
    glm::vec3 scale;
    scale.x = glm::length( modele[0]);
    scale.y = glm::length( modele[1]);
    scale.z = glm::length( modele[2]);


    return scale;
}


void object::set_position(glm::vec3 nv_position){
    modele *= glm::translate(glm::mat4(1.0F), nv_position);
}
void object::set_taille(glm::vec3 nv_taille){
    modele *= glm::scale(glm::mat4(1.0F), nv_taille);
}
void object::set_rotation(float angle,char axe){

    glm::vec3 axe_r;
  


    switch (axe)
    {
    case 'x':
        axe_r = {1.,0.,0.};
        break;
    case 'y':
        axe_r = {0.,1.,0.};
    break;
    case 'z':
        axe_r = {0.,0.,1.};    
    break;
    default:
        break;
    }
    glm::quat q(glm::radians(angle),glm::normalize(axe_r));
   

    
    modele *= glm::mat4_cast(q);

}

void object::init(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindBuffer(VBO);
    glBufferData(GL_ARRAY_BUFFER,vertex.vertices.size(), (void)vertex.vertices.size()*sizeof(glm::vec3),)

}


