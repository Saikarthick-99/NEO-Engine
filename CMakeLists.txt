cmake_minimum_required(VERSION 3.22)
project(NEO VERSION 0.1.0 LANGUAGES CXX C)

# Force modern C++20 standard rules
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tell the compiler where to drop the finished .exe application
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Strip out unnecessary parts of GLFW we don't need to build
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

# Introduce our third-party code modules
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)

# Tell CMake where our custom engine code is located
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "include/*.h")

# Define our final executable target game engine
add_executable(${PROJECT_NAME} ${ENGINE_SOURCES} ${ENGINE_HEADERS} "include/Window.h" "src/Window.cpp")

# Expose header folders so our files can find each other via #include
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
)

# Bind the graphics libraries tightly to NEO
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    glad
)

# Enable strict warning checks to prevent messy code bugs
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()