cmake_minimum_required(VERSION 3.18)
project(render-core VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Percorsi sorgenti/header ===
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# === Trova i file sorgenti ===
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

# === Crea libreria dinamica ===
add_library(render-core SHARED ${SOURCES})

# === Macro export simboli ===
target_compile_definitions(render-core PRIVATE RENDER_CORE_BUILD_DLL RENDER_CORE_SHARED)

# === Includi solo i tuoi header pubblici ===
target_include_directories(render-core
    PUBLIC
        ${INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/vendor/glm  # Aggiunta include path per GLM
)

# === Aggiungi glad ===
add_library(glad STATIC ${SOURCE_DIR}/glad.c)
target_include_directories(glad PUBLIC ${INCLUDE_DIR})

# === Linka dipendenze staticamente ===
target_link_libraries(render-core
    PRIVATE
    glad
    SDL3::SDL3
    spdlog::spdlog
)

# === Linka opengl32 su Windows ===
if (WIN32)
    target_link_libraries(render-core PRIVATE opengl32)
endif()

# === Installazione per distribuzione ===
install(TARGETS render-core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY ${INCLUDE_DIR}/ DESTINATION include FILES_MATCHING PATTERN "*.h")