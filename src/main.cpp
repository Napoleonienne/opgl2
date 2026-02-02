// Charge les fonctions OpenGL


#include <glad.h>        // Toujours avant glfw3.h
#include <GLFW/glfw3.h>
#include <gm.hpp>
#include <Shader.hpp>    // Classe shader personnalisée
#include "gui.hpp"
#include <buffer.hpp>
#include <iostream>
#include <vector>
#include <printf.h>
#include <ecs.hpp>
#include <format>
#include "CameraController.hpp"
#include <memory>



static GLFWcursorposfun s_previousCursorPosCallback = nullptr;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int chargerTexture(const char* chemin);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void APIENTRY glDebugOutput(GLenum source, GLenum type,GLuint id,GLenum severity, GLsizei length,const GLchar *message,const void *userParam);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float deltaTime = 1.0f; 
float lastFrame = 1.0f;
float yaw;
float pitch;
static double lastToggle = 0.0;
float fov = 45.0f;
CameraController camprincipale(cameraPos, cameraFront, cameraUp, yaw, pitch, deltaTime, SCR_WIDTH, SCR_HEIGHT);


int main()
{
    // Initialisation GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);

    // Création de la fenêtre
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube Texturé", NULL, NULL);
    if (!window)
    {
        std::cerr << "Échec de la création de la fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);


    // Initialisation GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Échec de l'initialisation de GLAD" << std::endl;
        return -1;
    }
    
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
   
    
    GLuint ssbo;
    GLuint ubo;
    glNamedBufferStorage(ssbo, 1e9, nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(ubo, 1024, nullptr, GL_DYNAMIC_STORAGE_BIT);

    glEnable(GL_DEPTH_TEST);


    gui::init(window);


    // Matrices
    const glm::mat4 projection = glm::perspective(
        glm::radians(80.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 
        0.1f, 
        10000.2f);

 

  


  
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        processInput(window);
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gui::nvframes();




     


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
                

                   
        
        gui::endframes();
        glfwSwapBuffers(window);

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
    }
    
    // Cleanup

    gui::liberer();
    glfwTerminate();
    glDeleteBuffers(1,&ssbo);
    glDeleteBuffers(1,&ubo);
    return 0;

    
}
bool firstMouse = true;


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    camprincipale.mouseCallback(xpos,ypos);

}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camprincipale.scrollCallback(yoffset, fov);
}



bool qWasPressed = false; 
bool souris = true;
void processInput(GLFWwindow *window)
{

    bool qPressed = (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS);
    
    double now = glfwGetTime();

    camprincipale.processInput(window);


    
    if (qPressed && qWasPressed && (now - lastToggle) >1.0f )
    {
        static double lastToggle = now;
        if (souris == true){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }else
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        souris = !souris;
        
        
    }



    qWasPressed = qPressed;
      
   
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}





void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar *message,
                            const void *userParam)
{
    // on ignore les codes ou avertissements non significatifs
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;
    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other"; break;
    }
    std::cout << std::endl;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:
       std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other"; break;
    }
    std::cout << std::endl;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification"; break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

