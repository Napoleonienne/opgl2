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
void interface(float* rX,float* rY,float* rZ,glm::vec4 *couleur,float* fov);
void SetupImGuiModernStyle();
std::vector<glm::vec3> vecaleatoire(int n);
float random_float(float min, float max);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// Paramètres de la fenêtre
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float deltaTime = 1.0f; // Time between current frame and last frame
float lastFrame = 1.0f; // Time of last frame
float yaw;
float pitch;
static double lastToggle = 0.0;
float fov = 45.0f;


float lastX = SCR_WIDTH/2, lastY = SCR_HEIGHT/2;

CameraController camprincipale(cameraPos, cameraFront, cameraUp, yaw, pitch, deltaTime, SCR_WIDTH, SCR_HEIGHT);

struct material
{
    /* data */
};


int main()
{
    // Initialisation GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    5.6f,glm::vec4(couleur_sphere,1.0f),
    Shader("../shader/sphere.vs","../shader/sphere.fs"));

 


    // Matrices
    const glm::mat4 projection = glm::perspective(
        glm::radians(80.0f), 
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 
        0.1f, 
        10000.2f
                                        );

    float rotX = 0.0f;
    float rotY = 0.0f;
    float rotZ = 0.0f;                             
    glm::vec4 couleur = glm::vec4(0.5f,0.6f,0.3f,1.0f);
    glm::vec4* c = &couleur;
    
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    


    GLuint tex = chargerTexture("../wall.jpg");
    // Boucle principale
  
  glm::mat4 sp(1.0f);
  glm::mat4 modsoleil(1.0f);
  modsoleil =
   glm::rotate(
    modsoleil,
    glm::radians(45.0f),
  glm::vec3(1.0f, 0.2f, 0.0f ) );
  
#include <memory>
  sp = glm::translate(
    sp,
    glm::vec3(0.0f, 10.0f, 0.0f ) );

    std::vector<glm::vec3> POS = vecaleatoire(1000);
    lamp soleil(glm::vec3(1.5,1.0,0.5),6,Shader("../shader/soleil.vs","../shader/soleil.fs"));
    glm::vec3 lightColor(0.33f, 0.42f, 0.18f);
    soleil.shader.set("lightColor",lightColor);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        glm::mat4 view;
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp); 

        sphere.shade.set("light",glm::vec3(0.33f, 0.42f, 0.18f));


        soleil.dessiner(projection, modsoleil , view);

        float utime=glfwGetTime();
        
                     

        for (auto pos :POS)
        {
            sp = glm::translate(glm::mat4(1.0f),pos) ;
            sp = glm::rotate(sp,sin(45.0f)*utime,glm::vec3(0.0,0.7,0.0));
            sphere.dessiner(projection,sp,view);
        }
         

                                             
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        float currentFrame = glfwGetTime();
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
void interface(float* rX,float* rY,float* rZ,glm::vec4 *couleur, float* fov)
{
        ImGui::Begin("control");
        ImGui::Button("rotation");
        ImGui::SliderAngle("rotation x",rX,-180.0f,180.0f);
        ImGui::SliderAngle("rotation y",rY,-180.0f,180.0f);
        ImGui::SliderAngle("rotation z",rZ,-180.0f,180.0f);
        ImGui::SliderAngle("fov",fov,0.0f,180.0f);
        ImGui::ColorEdit4("couleeur",glm::value_ptr(*couleur));
        ImGui::TextColored(ImVec4(0.3f, 0.8f, 1.0f, 1.0f),
                   "CameraPos: (%.2f, %.2f, %.2f)",
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


