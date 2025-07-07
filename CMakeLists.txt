cmake_minimum_required(VERSION 3.10)
project(files-engine)

# flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fPIE")
# -L${CMAKE_CURRENT_BINARY_DIR} -Wl,-rpath=${CMAKE_CURRENT_BINARY_DIR} -lfelogic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# src
file(GLOB_RECURSE SRCS src/*.cpp src/*.c "cfe-*/src/*")
file(GLOB SCRIPT_INCS "cfe-*/include")

# compile fe-logic (in zig)
execute_process(
  COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/zig/fe-logic/build.sh
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# compile
add_executable(main ${SRCS} build/fe-logic.o)


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

## BulletPhysics
find_package(Bullet REQUIRED)
target_link_libraries(main BulletDynamics BulletCollision LinearMath)

# headers
include_directories(
  ${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/include/bullet
  ${CMAKE_SOURCE_DIR}/fe-headers
  ${SCRIPT_INCS}
)
message(STATUS "INCS:::::: ${SCRIPT_INCS}")


file(COPY "${CMAKE_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_BINARY_DIR}")
file(COPY "${CMAKE_SOURCE_DIR}/assets" DESTINATION "${CMAKE_BINARY_DIR}")

