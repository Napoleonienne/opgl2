// Charge les fonctions OpenGL
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad.h>        // Toujours avant glfw3.h
#include <GLFW/glfw3.h>

#include <Shader.hpp>    // Classe shader personnalisée
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <printf.h>
#include <format>
#include "CameraController.hpp"
#include "Sphere.hpp"
#include "lampe.hpp"
#include <memory>

static GLFWcursorposfun s_previousCursorPosCallback = nullptr;
// Callback appelée lors du redimensionnement de la fenêtre
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Fonction pour gérer les entrées clavier
void processInput(GLFWwindow *window);
unsigned int chargerTexture(const char* chemin);
void interface(glm::vec3 *couleur);
void SetupImGuiModernStyle();
std::vector<glm::vec3> vecaleatoire(int n);
float random_float(float min, float max);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void APIENTRY glDebugOutput(GLenum source, GLenum type,GLuint id,GLenum severity, GLsizei length,const GLchar *message,const void *userParam);
// Paramètres de la fenêtre
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

struct LUMI {
 glm::vec3 position;
 glm::vec3 ambient;
 glm::vec3 diffuse;
 glm::vec3 specular;
};
float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;

CameraController camprincipale(cameraPos, cameraFront, cameraUp, yaw, pitch, deltaTime, SCR_WIDTH, SCR_HEIGHT);

struct Material {
   glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

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
   
    glEnable(GL_DEPTH_TEST);

    // Initialisation ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    SetupImGuiModernStyle();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");


    glm::vec3 couleur_sphere(1.0f,0.5f,0.31f);

    Sphere sphere(glm::vec3(0.0f,0.0f,0.0f),
    1.5f,glm::vec4(couleur_sphere,0.4f),
    Shader("../shader/sphere.vs","../shader/sphere.fs"));

 


    // Matrices
    const glm::mat4 projection = glm::perspective(
        glm::radians(80.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 
        0.1f, 
        10000.2f
                                        );

 
    Material mystere({1.0f, 0.5f, 0.31f},{1.0f, 0.5f, 0.31f},{0.5f, 0.5f, 0.5f},32.0f);

  
  glm::mat4 sp(1.0f);
  glm::mat4 modsoleil(1.0f);
  GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
    {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE,
                            GL_DONT_CARE,
                            GL_DONT_CARE,
                            0, nullptr, GL_TRUE);
    }
  
  
  sp = glm::translate(
    sp,
    glm::vec3(0.0f, 10.0f, 0.0f ) );
    int Nombre_object = 10;
    std::vector<glm::vec3> POS = vecaleatoire(Nombre_object);
    auto couleur_lumier = glm::vec3(1.0f) ;
    auto lightPos = glm::vec3(0.0f,0.0f,3.0f);

    LUMI soleillum(lightPos,{ 0.2f, 0.2f, 0.2f},{0.5f, 0.5f, 0.5f},{1.0f, 1.0f, 1.0f});
    lamp soleil(soleillum.position,5.0f, couleur_lumier  ,Shader("../shader/soleil.vs","../shader/soleil.fs"));

    auto a = &couleur_lumier;
    glm::mat4 mattrix[Nombre_object];
    for (int i =0; i <Nombre_object; i++)
    {

        glm::mat4 temp1 = glm::translate(glm::mat4(1.0f), POS.at(i)) ;
        mattrix[i] = temp1;

    }
    
    glm::mat4 pol = glm::translate(glm::mat4(1.0f),glm::vec3(-15.24,0.66,5.67));



    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        processInput(window);
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        interface(a);

        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 
        soleil.shader.set("lightColor",couleur_lumier);
        soleil.shader.set("utime",currentFrame);
        sphere.shade.set("light.couleur",couleur_lumier);
        sphere.shade.set("light.position",soleillum.position);
        sphere.shade.set("light.ambient",soleillum.ambient);
        sphere.shade.set("light.diffuse",soleillum.diffuse);
        sphere.shade.set("light.specular",soleillum.specular);

        sphere.shade.set("material.ambient",  mystere.ambient);
        sphere.shade.set("material.diffuse",  mystere.diffuse);
        sphere.shade.set("material.specular", mystere.specular);
        sphere.shade.set("material.shininess", mystere.shininess);
                
                
        sphere.shade.set("camerapos",cameraPos);

        soleil.dessiner(projection, modsoleil , view);

        modsoleil = glm::translate(glm::mat4(1.0f) , glm::vec3(35.0f*cos(currentFrame),0.5f, 50*sin(currentFrame) ) );

        soleillum.position = glm::vec3(modsoleil[3]);
        for (auto mat :mattrix)
        {
            
            sphere.dessiner(projection,mat,view);
        }


        sphere.dessiner(projection, pol ,view);

                                             
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();
    }
    
    // Cleanup
    soleil.detruire();
    sphere.destroy();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    
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

unsigned int chargerTexture(const char* chemin)
{
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(chemin,&width,&height,&nrChannels,0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cerr << "Échec du chargement de la texture : " << chemin << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

void interface(glm::vec3 *couleur)
{
    ImGui::Begin("Contrôle");

    // Slider pour l'angle de champ de vision
    ImGui::SliderAngle("FOV", &fov, 0.0f, 180.0f);

    // Éditeur de couleur pour la lumière
    ImGui::ColorEdit3("Couleur", glm::value_ptr(*couleur));

    // Affichage de la position de la caméra
    ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f),
                       "Position Caméra: (%.2f, %.2f, %.2f)",
                       cameraPos.x, cameraPos.y, cameraPos.z);

    ImGui::End();
}

void SetupImGuiModernStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    // Param�tres de base
    style.WindowRounding = 10.0f;   // bords arrondis
    style.FrameRounding = 6.0f;     // boutons et sliders arrondis
    style.WindowPadding = ImVec2(10, 10);
    style.FramePadding = ImVec2(6, 4);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 4);

    // Couleurs semi-transparentes (alpha < 1.0)
    ImVec4 transparentBg = ImVec4(0.12f, 0.12f, 0.14f, 0.6f); // fen�tre
    ImVec4 accentColor    = ImVec4(0.35f, 0.65f, 0.95f, 0.8f); // boutons, sliders
    ImVec4 hoverColor     = ImVec4(0.45f, 0.75f, 1.0f, 0.8f);
    ImVec4 activeColor    = ImVec4(0.25f, 0.55f, 0.85f, 0.9f);
    ImVec4 textColor      = ImVec4(0.95f, 0.95f, 0.95f, 1.0f);

    style.Colors[ImGuiCol_WindowBg]       = transparentBg;
    style.Colors[ImGuiCol_FrameBg]        = ImVec4(0.18f, 0.18f, 0.2f, 0.5f);
    style.Colors[ImGuiCol_FrameBgHovered] = hoverColor;
    style.Colors[ImGuiCol_FrameBgActive]  = activeColor;
    style.Colors[ImGuiCol_TitleBg]        = transparentBg;
    style.Colors[ImGuiCol_TitleBgActive]  = accentColor;
    style.Colors[ImGuiCol_Button]         = accentColor;
    style.Colors[ImGuiCol_ButtonHovered]  = hoverColor;
    style.Colors[ImGuiCol_ButtonActive]   = activeColor;
    style.Colors[ImGuiCol_Header]         = accentColor;
    style.Colors[ImGuiCol_HeaderHovered]  = hoverColor;
    style.Colors[ImGuiCol_HeaderActive]   = activeColor;
    style.Colors[ImGuiCol_SliderGrab]     = accentColor;
    style.Colors[ImGuiCol_SliderGrabActive] = activeColor;
}


std::vector<glm::vec3> vecaleatoire(int n){
    std::vector<glm::vec3> pos;
    for (int i = 0; i < n; i++)
    {
        pos.push_back(glm::vec3(random_float(-1000,1000),random_float(-1000,1000),random_float(-1000,1000)));

    };
    return pos;
}


float random_float(float min, float max) {
    static std::random_device rd;  // Générateur de graine aléatoire
    static std::mt19937 gen(rd()); // Moteur de génération (Mersenne Twister)
    std::uniform_real_distribution<float> dis(min, max); // Distribution uniforme
    return dis(gen);
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
