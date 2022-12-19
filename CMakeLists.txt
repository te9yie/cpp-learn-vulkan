cmake_minimum_required(VERSION 3.14)
project(learn-vulkan)

find_package(Vulkan REQUIRED)

include(FetchContent)

# imgui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.89.1
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(imgui)

file(GLOB imgui_sources
    ${imgui_SOURCE_DIR}/*.h
    ${imgui_SOURCE_DIR}/*.cpp)
file(GLOB imgui_backends
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl.*
    ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.*)

add_library(imgui STATIC ${imgui_sources} ${imgui_backends})
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends)
target_include_directories(imgui PUBLIC ${Vulkan_INCLUDE_DIR})
target_link_libraries(imgui PRIVATE SDL2::SDL2 ${Vulkan_LIBRARIES})

# SDL
FetchContent_Declare(
    SDL
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.1
    GIT_SHALLOW TRUE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL)

file(GLOB_RECURSE sources src/*.cpp)

add_executable(${PROJECT_NAME} WIN32 ${sources})
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /utf-8>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W -Wall>)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:DEBUG>>:_CRTDBG_MAP_ALLOC>)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    SDL2::SDL2 SDL2::SDL2main
    ${Vulkan_LIBRARIES})