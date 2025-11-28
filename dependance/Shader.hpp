#pragma once
#include <string>
#include <glad.h> // include glad BEFORE any GLFW includes that might follow
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad.h>
#include <Shader.hpp>



class Shader {
public:
    GLuint ID;
    Shader();
    Shader(const char* vertexPath, const char* fragmentPath);
    Shader(const char* vertexPath, const char* fragmentPath, const char* computePath);







    void use() const;

    template<typename T>
    void set(const std::string& name, const T& value) const;

    void settex(const std::string& name, const unsigned int value) const;

private:
    void checkCompileErrors(GLuint shader, const std::string &type) const;
};

#include <Shader.inl>