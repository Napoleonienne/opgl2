#include <gui.hpp>


namespace gui
{
    
    void init(GLFWwindow *window){

            
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        SetupImGuiModernStyle();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 450");


    }

    void nvframes(){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

    }


    void interface(glm::vec3 *couleur){
        ImGui::Begin("Contrôle");



 

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

    void endframes(){
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    }

    void liberer(){
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }


} // namespace name
