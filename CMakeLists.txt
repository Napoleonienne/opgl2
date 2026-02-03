cmake_minimum_required(VERSION 3.28)
project(OpenGL2 VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Configuration Modules C++ ---
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-stdlib=libc++>
        $<$<COMPILE_LANGUAGE:CXX>:-fmodules>
    )
    add_link_options(-stdlib=libc++ -lc++abi -fuse-ld=lld)
    
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fmodules-ts>)
endif()

if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    message(FATAL_ERROR "Ce projet C++26 exige Ninja.")
endif()

# --- Mold Linker ---
if(UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    execute_process(
        COMMAND mold --version 
        RESULT_VARIABLE MOLD_PRESENT 
        OUTPUT_QUIET ERROR_QUIET
    )
    if(MOLD_PRESENT EQUAL 0)
        message(STATUS "🔗 mold détecté et activé.")
        add_link_options(-fuse-ld=mold)
    endif()
endif()

# --- CPM ---
include(FetchContent)
include(CPM.cmake)
set(CPM_SOURCE_CACHE "$ENV{HOME}/.cache/CPM")

# --- Optimisations ---
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        add_compile_options(-O3 -march=native -flto=thin)
        add_link_options(-flto=thin)
    else()
        add_compile_options(-O3 -march=native)
    endif()
endif()

# --- Paquets ---
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)

CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp
    VERSION 5.3.1
    OPTIONS 
        "ASSIMP_BUILD_TESTS OFF" 
        "ASSIMP_INSTALL OFF" 
        "ASSIMP_BUILD_WERROR OFF"
        "ASSIMP_WARNINGS_AS_ERRORS OFF"
)

CPMAddPackage(NAME EnTT GITHUB_REPOSITORY skypjack/entt VERSION 3.13.2)
CPMAddPackage(NAME imgui GITHUB_REPOSITORY ocornut/imgui VERSION 1.91.5 DOWNLOAD_ONLY YES)
CPMAddPackage(NAME glfw GITHUB_REPOSITORY glfw/glfw VERSION 3.4)
CPMAddPackage(NAME glm GITHUB_REPOSITORY g-truc/glm GIT_TAG 1.0.1)
CPMAddPackage(NAME spdlog GITHUB_REPOSITORY gabime/spdlog VERSION 1.14.1)

find_package(OpenGL REQUIRED)

# Désactiver modules pour Assimp
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND TARGET assimp)
    target_compile_options(assimp PRIVATE -fno-modules)
endif()

# --- ImGui ---
if(imgui_ADDED)
    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )
    target_include_directories(imgui PUBLIC 
        ${imgui_SOURCE_DIR} 
        ${imgui_SOURCE_DIR}/backends
    )
    target_link_libraries(imgui PUBLIC glfw OpenGL::GL)
    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
endif()

# --- Module ECS ---
add_library(ecs_module)
target_sources(ecs_module
    PUBLIC FILE_SET CXX_MODULES FILES "${CMAKE_SOURCE_DIR}/src/ecs.cpp"
)
target_link_libraries(ecs_module PUBLIC EnTT::EnTT glm::glm)

# --- Exécutable ---
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)
list(REMOVE_ITEM PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/ecs.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# ⚠️ CRITIQUE : Désactiver modules pour fichiers utilisant GLAD
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Trouver automatiquement tous les .cpp qui incluent glad
    file(GLOB_RECURSE ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
    list(REMOVE_ITEM ALL_CPP_FILES "${CMAKE_SOURCE_DIR}/src/ecs.cpp")
    
    foreach(CPP_FILE ${ALL_CPP_FILES})
        file(READ ${CPP_FILE} FILE_CONTENT)
        if(FILE_CONTENT MATCHES "glad\\.h")
            set_source_files_properties(${CPP_FILE}
                PROPERTIES COMPILE_FLAGS "-fno-modules"
            )
            message(STATUS "Désactivation modules pour: ${CPP_FILE}")
        endif()
    endforeach()
    
    # Glad.c ne doit jamais avoir de modules
    set_source_files_properties("${CMAKE_SOURCE_DIR}/src/glad.c"
        PROPERTIES COMPILE_FLAGS "-fno-modules"
    )
endif()

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/dependance
)
target_link_libraries(${PROJECT_NAME} PUBLIC
    ecs_module
    imgui
    glfw
    assimp::assimp
    spdlog::spdlog
    OpenGL::GL
    $<$<PLATFORM_ID:Linux>:X11 Xrandr Xi Xxf86vm Xcursor pthread dl m>
)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)