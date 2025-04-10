cmake_minimum_required(VERSION 3.10)
project(files-engine)

# flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# src
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)
file(GLOB_RECURSE HEADERS fe-headers/* include/*)

# compile
add_executable(main ${SRCS})


# include packages

## openGL
find_package(OpenGL REQUIRED)
target_link_libraries(main ${OPENGL_LIBRARIES})

## GLFW3
find_package(glfw3 REQUIRED)
target_link_libraries(main glfw)

## glm
find_package(glm REQUIRED)
#target_link_libraries(main glm)

## ImGui
find_package(imgui REQUIRED)
target_link_libraries(main imgui)

## FreeType
find_package(Freetype REQUIRED)
target_link_libraries(main Freetype::Freetype)

# headers
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/fe-headers
)



file(COPY "${CMAKE_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

