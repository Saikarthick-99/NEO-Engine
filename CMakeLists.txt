cmake_minimum_required(VERSION 3.22)
project(NEO VERSION 0.1.0 LANGUAGES CXX C)

# Force modern C++20 standard rules
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tell the compiler where to drop the finished .exe application
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Strip out unnecessary parts of GLFW
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

# Dependencies
add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)

# 1. Auto-collect all Engine logic from src and include
file(GLOB_RECURSE ENGINE_SOURCES "src/*.cpp")
file(GLOB_RECURSE ENGINE_HEADERS "include/*.h")

# 2. Target-specific Windows Resource compilation for the .exe icon
if(WIN32)
    set(ENGINE_RESOURCES "src/resource.rc")
endif()

# 3. Define the executable
# This combines the main entry point, the engine src files, and the windows resource
add_executable(${PROJECT_NAME} "main.cpp" ${ENGINE_SOURCES} ${ENGINE_HEADERS} ${ENGINE_RESOURCES})

# Setting property for our exe startup
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Expose header folders
target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm 
)

# Bind graphics libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw
    glad
)

# MSVC specific fixes
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

# --- ASSET & SHADER DEPLOYMENT ---
# This copies everything the .exe needs into the 'bin' folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Deploying shaders and assets to build directory..."
)