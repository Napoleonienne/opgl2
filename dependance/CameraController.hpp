#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class CameraController {
public:
    glm::vec3& cameraPos;
    glm::vec3& cameraFront;
    glm::vec3& cameraUp;
    float& yaw;
    float& pitch;
    float &deltaTime;

    float lastX, lastY;
    bool firstMouse;

    CameraController(glm::vec3& pos,
                     glm::vec3& front,
                     glm::vec3& up,
                     float& y,
                     float& p,
                     float& dt,
                     int SCR_WIDTH,
                     int SCR_HEIGHT);
        

    void mouseCallback(double xpos, double ypos);
    void scrollCallback(double yoffset, float& fov);
    void processInput(GLFWwindow* window);
};
//glfwSetScrollCallback(window, scroll_callback);
//glfwSetCursorPosCallback(window, mouse_callback);