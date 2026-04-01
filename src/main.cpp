// Charge les fonctions OpenGL


#include <glad.h>        
#include <GLFW/glfw3.h>
#include <gm.hpp>
#include <gui.hpp>
#include <buffer.hpp>
#include <printf.h>
#include "CameraController.hpp"
#include "spdlog/spdlog.h"
#include <f_util.hpp>
#include "cube.hpp"



const GLFWcursorposfun s_previousCursorPosCallback = nullptr;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void APIENTRY glDebugOutput(GLenum source, GLenum type,GLuint id,GLenum severity, GLsizei length,const GLchar *message,const void *userParam);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float deltaTime = 1.0f; 
float lastFrame = 1.0f;
float fov = 45.0f;


CameraController camprincipale(SCR_WIDTH, SCR_HEIGHT,deltaTime);

struct Light {
    glm::vec3 couleur;
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


void mon_callback_pre(const char *name, GLADapiproc apiproc, int len_args, ...) {
    //spdlog::info("Appel de {}:  {}\n", name, len_args);

}

// Ce callback vérifie les erreurs après chaque appel
void mon_callback_post(void *ret, const char *name, GLADapiproc apiproc, int len_args, ...) {
GLenum error = glad_glGetError();
if (error != GL_NO_ERROR) {
    //spdlog::error("ERREUR GL dans {} : Code {}\n", name, error);
}
}


int main()
{
    spdlog::set_level(spdlog::level::err);

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
        spdlog::error("Échec de la création de la fenêtre GLFW");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);



    // Initialisation GLAD
    int version = gladLoadGL(glfwGetProcAddress);
    spdlog::info("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

     if (GLAD_VERSION_MAJOR(version) < 4 || (GLAD_VERSION_MAJOR(version) == 4 && GLAD_VERSION_MINOR(version) < 6))
     
    {
        spdlog::error("OpenGL 4.6 n'est pas supporté" );
        return -1;
    }

    
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    gladSetGLPreCallback(mon_callback_pre);
    gladSetGLPostCallback(mon_callback_post);
   
    
    GLuint ssbo;
    GLuint ubo;
    glCreateBuffers(1, &ssbo);
    glCreateBuffers(1, &ubo);

    glNamedBufferStorage(ssbo, 1024*1024, nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferStorage(ubo, 1024*16, nullptr, GL_DYNAMIC_STORAGE_BIT);

    glEnable(GL_DEPTH_TEST);


    gui::init(window);
    


    // Matrices
    const glm::mat4 projection = glm::perspective(
        glm::radians(80.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 
        10000.0f, 
        0.1f
    );
    
    cube cube1({0,0,0},{1,1,1},Shader("shader/cube.vs","shader/cube.fs") );
    
    

 
    Light light = {
        .couleur = glm::vec3(1.0f, 1.0f, 1.0f),
        .position = glm::vec3(2.0f, 2.0f, 2.0f),
        .ambient = glm::vec3(0.2f, 0.2f, 0.2f), 
        .diffuse = glm::vec3(0.5f, 0.5f, 0.5f),
        .specular = glm::vec3(1.0f, 1.0f, 1.0f)
    };
  


  
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        processInput(window);
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gui::nvframes();
        gui::interface(camprincipale.getCameraPos());

        cube1.set_projection(projection);
        cube1.set_view(camprincipale.getViewMatrix());
        cube1.our.set("light.position", light.position);
        cube1.our.set("light.couleur", light.couleur);
        cube1.our.set("light.ambient", light.ambient);
        cube1.our.set("light.diffuse", light.diffuse);
        cube1.our.set("light.specular", light.specular);
        cube1.afficher();



     


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
                

                   
        
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


    
    static double lastToggle = 0.0;
    if (qPressed && qWasPressed && (now - lastToggle) > 1.0f )
    {
        lastToggle = now;
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






const char* getDebugSource(GLenum source) {
    switch (source) {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION: return "Application";
        case GL_DEBUG_SOURCE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* getDebugType(GLenum type) {
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behaviour";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behaviour";
        case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
        case GL_DEBUG_TYPE_MARKER: return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
        case GL_DEBUG_TYPE_OTHER: return "Other";
        default: return "Unknown";
    }
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
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: 
            spdlog::error("GL DEBUG HIGH: {} (Source: {}, Type: {})\n", message, getDebugSource(source), getDebugType(type));
            break;
        case GL_DEBUG_SEVERITY_MEDIUM: 
            spdlog::warn("GL DEBUG MEDIUM: {} (Source: {}, Type: {})\n", message, getDebugSource(source), getDebugType(type));
            break;
        case GL_DEBUG_SEVERITY_LOW: 
            spdlog::info("GL DEBUG LOW: {} (Source: {}, Type: {})\n", message, getDebugSource(source), getDebugType(type));
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: 
            spdlog::debug("GL DEBUG NOTIFICATION: {} (Source: {}, Type: {})\n", message, getDebugSource(source), getDebugType(type));
            break;
        default: 
            spdlog::error("GL DEBUG UNKNOWN: {} (Source: {}, Type: {})\n", message, getDebugSource(source), getDebugType(type));
            break;
    }

}

 