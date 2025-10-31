#pragma once
#include <glm/gtc/type_ptr.hpp>

template<typename T>
void Shader::set(const std::string& name, const T& value) const {
    GLint loc = glGetUniformLocation(ID, name.c_str());

    if constexpr (std::is_same_v<T, bool>) {
        glUniform1i(loc, static_cast<int>(value));
    } else if constexpr (std::is_same_v<T, int>) {
        glUniform1i(loc, value);
    } else if constexpr (std::is_same_v<T, float>) {
        glUniform1f(loc, value);
    } else if constexpr (std::is_same_v<T, glm::vec2>) {
        glUniform2fv(loc, 1, glm::value_ptr(value));
    } else if constexpr (std::is_same_v<T, glm::vec3>) {
        glUniform3fv(loc, 1, glm::value_ptr(value));
    } else if constexpr (std::is_same_v<T, glm::vec4>) {
        glUniform4fv(loc, 1, glm::value_ptr(value));
    } else if constexpr (std::is_same_v<T, glm::mat3>) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    } else if constexpr (std::is_same_v<T, glm::mat4>) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
    
    } else {
        static_assert(!sizeof(T*), "Shader::set() type non supporté");
    }
}