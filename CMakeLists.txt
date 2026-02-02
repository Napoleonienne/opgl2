cmake_minimum_required(VERSION 3.28)
project(OpenGL2 VERSION 0.1 LANGUAGES CXX C)

include(FetchContent)
include(CPM.cmake)
    # On utilise la variable d'environnement pour éviter le chemin en dur
set(CPM_SOURCE_CACHE "$ENV{HOME}/.cache/CPM")
message(STATUS "L'archive des sources est scellée dans : ${CPM_SOURCE_CACHE}")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT MSVC)
    add_compile_options(-O3 -march=native)
endif()


CPMAddPackage(
    NAME assimp
    GITHUB_REPOSITORY assimp/assimp
    VERSION 6.0.3
    OPTIONS
        "ASSIMP_BUILD_TESTS OFF"
        "ASSIMP_INSTALL OFF"
        "ASSIMP_BUILD_ASSIMP_TOOLS OFF"
        "ASSIMP_BUILD_WERROR OFF"
)


CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    VERSION 1.91.5 
    DOWNLOAD_ONLY YES
)

CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw
    VERSION 3.4
    OPTIONS
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_DOCS OFF"
)

CPMAddPackage(
    name glm 
    GITHUB_REPOSITORY g-truc/glm
    GIT_TAG 1.0.3
    OPTIONS

)
cpmaddpackage(
    name spd
    GITHUB_REPOSITORY gabime/spdlog
    VERSION 1.17.0

)
find_package(OpenGL REQUIRED)




if(assimp_ADDED)
    if(NOT MSVC)
        target_compile_options(assimp PUBLIC -Wno-maybe-uninitialized -Wno-unused-parameter)
    endif()
endif()

if(imgui_ADDED)
    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )
    target_include_directories(imgui PUBLIC 
        ${imgui_SOURCE_DIR} 
        ${imgui_SOURCE_DIR}/backends
    )
    # ImGui a besoin de savoir comment charger OpenGL
    target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
endif()


file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-D_LARGEFILE_SOURCE)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/dependance
    ${CMAKE_SOURCE_DIR}/externe
    ${GLFW_INCLUDE_DIRS}
    ${PHYSX_DIR}/physx/include
    ${PHYSX_DIR}/pxshared/include
)


set(PHYSX_LIBS
    ${PHYSX_SOURCE}/libPhysX_static_64.a
    ${PHYSX_SOURCE}/libPhysXCommon_static_64.a
    ${PHYSX_SOURCE}/libPhysXFoundation_static_64.a
    ${PHYSX_SOURCE}/libPhysXCooking_static_64.a
    ${PHYSX_SOURCE}/libPhysXExtensions_static_64.a
    ${PHYSX_SOURCE}/libPhysXPvdSDK_static_64.a
    ${PHYSX_SOURCE}/libPhysXCharacterKinematic_static_64.a
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    imgui 
    glfw          
    assimp::assimp 
    glm::glm
    OpenGL::GL
)

if(WIN32)
    #target_link_libraries(${PROJECT_NAME} PRIVATE ${PHYSX_LIBS})
elseif(APPLE)
    find_library(COCOA Cocoa)
    find_library(IOKIT IOKit)
    find_library(COREVIDEO CoreVideo)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${COCOA} ${IOKIT} ${COREVIDEO} ${PHYSX_LIBS})
else() # Linux
    target_link_libraries(${PROJECT_NAME} PUBLIC
        #${PHYSX_LIBS}
        X11 Xrandr Xi Xxf86vm Xcursor
        pthread dl m
    )
endif()