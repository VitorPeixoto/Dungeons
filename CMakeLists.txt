cmake_minimum_required(VERSION 3.10)
project(Dungeons)

set(CMAKE_CXX_STANDARD 11)

FIND_PATH( SOIL_INCLUDE_DIRS SOIL.h PATH_SUFFIXES SOIL )
FIND_LIBRARY( SOIL_LIBRARIES SOIL)

include_directories(include ${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)
find_package (GLEW REQUIRED)

add_executable(Dungeons
        include/Vector3.h
        main.cpp Cell.cpp Cell.h Level.cpp Level.h)

target_link_libraries (Dungeons ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES})