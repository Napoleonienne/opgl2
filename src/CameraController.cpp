#include "CameraController.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include <cmath>

CameraController::CameraController(
    glm::vec3& pos,
    glm::vec3& front,
    glm::vec3& up,
    float& y,
    float& p,
    float& dt,
    int SCR_WIDTH,
    int SCR_HEIGHT
) : cameraPos(pos),
    cameraFront(front),
    cameraUp(up),
    yaw(y),
    pitch(p),
    deltaTime(dt),
    firstMouse(true),
    lastX(SCR_WIDTH / 2.0f),
    lastY(SCR_HEIGHT / 2.0f)
{}

// Gestion de la souris pour la rotation
void CameraController::mouseCallback(double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = static_cast<float>(xpos - lastX) * 0.05f;
    float yoffset = static_cast<float>(lastY - ypos) * 0.05f;
    lastX = xpos;
    lastY = ypos;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// Gestion du scroll pour le FOV
void CameraController::scrollCallback(double yoffset, float& fov) {
    fov -= static_cast<float>(yoffset);
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

// Gestion des touches WASD + espace/shift
void CameraController::processInput(GLFWwindow* window) {
    
    float speed = 60.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= speed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) cameraPos += glm::vec3(0, 1, 0) * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) cameraPos -= glm::vec3(0, 1, 0) * speed;
    
}
