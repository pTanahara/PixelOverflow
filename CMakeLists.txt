cmake_minimum_required(VERSION 3.16)
project(3DEngine LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(third_party/SDL3-3.2.24 EXCLUDE_FROM_ALL)
add_subdirectory(third_party/imgui-1.92.4)
add_subdirectory(third_party/mimalloc-3.0.10)
add_subdirectory(third_party/tinygltf-2.9.7)

# Adiciona os diretórios de include
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)


# Cria o executável
add_executable(${PROJECT_NAME}
    main.cpp
    src/engine.cpp
    src/render/renderer.cpp
    src/render/post.cpp
    src/render/raster.cpp
)

target_link_libraries(imgui PUBLIC SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE mimalloc-static)

target_compile_definitions(${PROJECT_NAME} PRIVATE MI_MALLOC_OVERRIDE)
target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=1)
# target_compile_definitions(${PROJECT_NAME} PRIVATE MI_TRACK_VALGRIND=0 MI_SECURE=0 MI_PADDING=0)

