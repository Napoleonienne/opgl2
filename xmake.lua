-- Définition de l'horizon du projet
set_project("OpenGL2")
set_version("0.1")
set_version()
set_xmakever("3.0.6")

-- Vers un futur standardisé
set_languages("cxx26", "c23")
set_policy("check.auto_ignore_flags", false)

-- Gestion des dépendances : le jardin des paquets
add_requires("assimp 6.0.3", {configs = {tests = false, build_tools = false}})
add_requires("imgui 1.91.5", {configs = {glfw = true, opengl3 = true}})
add_requires("glfw 3.4")
add_requires("glm 1.0.3")
add_requires("spdlog 1.17.0")
add_requires("joltphysics", {configs = {double_precision = false}})

if not is_plat("windows") then
    add_cxflags("-O3", "-march=native")
end

-- Définition de la cible principale
target("OpenGL2")
    set_kind("binary")
    
    -- Sources : le murmure des fichiers
    add_files("src/**.cpp", "src/**.c")
    
    -- Définitions globales
    add_defines("_FILE_OFFSET_BITS=64", "_LARGEFILE_SOURCE", "GLM_ENABLE_EXPERIMENTAL")
    add_defines("IMGUI_IMPL_OPENGL_LOADER_GLAD")

    -- Inclusion des chemins ancestraux
    add_includedirs("include")
    
    -- Intégration des paquets déclarés
    add_packages("assimp", "imgui", "glfw", "glm", "spdlog")
    
    -- La quête de l'OpenGL
    add_rules("utils.bin2c") 
    if is_plat("linux") then
        add_syslinks("GL", "X11", "Xrandr", "Xi", "Xxf86vm", "Xcursor", "pthread", "dl", "m")
    elseif is_plat("macosx") then
        add_frameworks("Cocoa", "IOKit", "CoreVideo", "OpenGL")
    elseif is_plat("windows") then
        add_syslinks("opengl32")
    end
