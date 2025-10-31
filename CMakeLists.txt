cmake_minimum_required(VERSION 3.28)
project(OpenGL2 VERSION 0.1 LANGUAGES CXX C)

# Utiliser C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Détection des dépendances
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if(NOT GLFW_FOUND)
    message(FATAL_ERROR "GLFW not found. Installez libglfw3-dev et réessayez.")
endif()

# Chemin ImGui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)

# Sources du projet
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"

)

# Sources ImGui
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Création de l’exécutable
add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${IMGUI_SOURCES}
)

# Définitions pour ImGui
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

# Dossiers d’inclusion
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependance
        ${CMAKE_SOURCE_DIR}/externe
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${GLFW_INCLUDE_DIRS}
)

# Liens des bibliothèques
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glm::glm)
elseif(APPLE)
    find_library(COCOA Cocoa)
    find_library(IOKIT IOKit)
    find_library(COREVIDEO CoreVideo)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glm::glm ${COCOA} ${IOKIT} ${COREVIDEO})
else() # Linux
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw glm::glm X11 Xrandr Xi Xxf86vm Xcursor pthread dl m)
endif()
