cmake_minimum_required(VERSION 3.18)
project(render-core-wrapper VERSION 0.1.0 LANGUAGES C CXX)

# Scegli se static o shared
option(RENDER_CORE_BUILD_SHARED "Build render-core as shared library" ON)

# Forza alcune opzioni per i submodules
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# Submodules
add_subdirectory(vendor/glm)       # ✅ AGGIUNTO
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/SDL2)

# Subdirectory della libreria vera
add_subdirectory(render-core)

# (opzionale) Define globale per usare GLM extensions
target_compile_definitions(render-core PUBLIC GLM_ENABLE_EXPERIMENTAL)
