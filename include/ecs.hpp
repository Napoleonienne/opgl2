#pragma once
#include <entt.hpp>
#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
namespace ecs{
entt::registry registry;
entt::entity create_entity();
void destroy_ent(entt::entity entity);



namespace component{

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
struct shader{
    std::map<std::string,std::string> chtype;
    int ID;
    shader(){
        /*
        
        initier de shadr
        
        
        */
        for(auto tb:chtype ){
        std::string shadecode, tb.second;
        std::ifstream shadefile
        shadefile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            shadefile.open(fragmentPath);
            std::stringstream shadestream;
            shadestream << shadefile.rdbuf();
            shadefile.close();
            shadecode = shadestream.str();
        } catch (const std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << '\n';
        }

        const char* codef = shadecode.c_str();

        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
        ID = glCreateProgram();
        glAttachShader(ID, fragment);

   


            }
        ID = glCreateProgram();
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }
    
    void Shader::checkCompileErrors(GLuint shader, const std::string &type) const {
    GLint success = 0;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                      << infoLog << "\n-- --------------------------------------------------- --\n";
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
                      << infoLog << "\n-- --------------------------------------------------- --\n";
        }
    }
}



};

struct transform{
    glm::vec3 pos;
    glm::vec3 orientation;
};
};







}