#pragma once
#include <Shader.hpp>
#include <gm.hpp>
#include "Shader.hpp"
#include "f_util.hpp"
#include <string>
#include <glad.h>
#include <vector>
using std::vector;






class cube{
public:
cube(glm::vec3 origine,glm::vec3 dimension,const Shader &our,Materiaux mat):origine(origine),dimension(dimension),our(our),materiaux(mat)
{





    construre();

    model = glm::translate(model, origine);
    model = glm::scale(model, dimension);
}


void rotatex(float x){
    model =glm::rotate(model,x,{1.,0,0});
}
void rotatey(float x){
        model =glm::rotate(model,x,{0.,1,0});
}
void rotatez(float x){
        model =glm::rotate(model,x,{0.,0,1});
}

void set_view(glm::mat4 view){
    our.set("view",view);
}
void set_projection(glm::mat4 projection){
    our.set("projection",projection);
}

void afficher(){


    glm::mat3 matrixnormale = glm::transpose(glm::inverse(glm::mat3(model)));
    
    our.set("Material.ambiante",materiaux.ambiante);
    our.set("Material.diffuse",materiaux.diffuse);
    our.set("Material.speculaire",materiaux.speculaire);
    our.set("Material.shininess",materiaux.shininess);
    our.set("modelnormale",matrixnormale);
    our.set("model", model);
    our.use();
}


void texture(const std::string name,uint texture){
    our.settex(name,texture);
}
Shader our;
Materiaux materiaux = {
    .ambiante = glm::vec3(0.2f, 0.2f, 0.2f),
    .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
    .speculaire = glm::vec3(1.0f, 1.0f, 1.0f),
    .shininess = 32.0f
};

~cube(){
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
}

private:
glm::vec3 origine;
glm::vec3 dimension;
glm::mat4 model = glm::mat4(1.0f);
GLuint ebo,vao,vbo;
vector<vertex> cube_vert={
    // FACE AVANT (Z = 0.5f) - Normale : (0, 0, 1)
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},

    // FACE GAUCHE (X = -0.5f) - Normale : (-1, 0, 0)
    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

    // FACE DROITE (X = 0.5f) - Normale : (1, 0, 0)
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},

    // FACE BASSE (Y = -0.5f) - Normale : (0, -1, 0)
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},

    // FACE HAUTE (Y = 0.5f) - Normale : (0, 1, 0)
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}
};

void construre(){
    glCreateBuffers(1,&vbo);
    glCreateVertexArrays(1,&vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * cube_vert.size(), cube_vert.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, vertice));
    glEnableVertexAttribArray(0);  

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normale));
    glEnableVertexAttribArray(2);

  
}







};