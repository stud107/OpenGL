cmake_minimum_required(VERSION 3.7)
project(OpenGLProva)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Includes/shader.cpp Includes/shader.h Includes/utils.h)
add_executable(OpenGLProva ${SOURCE_FILES})

#Davide 2017/04/28 -----------------------------------------------------

#    # INCLUDES    -----------------------------------------------------
set(GLEW_INCLUDE_DIRECTORY C:/Documents/GLEW/glew-2.0.0-win32/glew-2.0.0/include)
include_directories(${GLEW_INCLUDE_DIRECTORY})

#set(GLM_INCLUDE_DIRECTORY C:/Documents/GLM/glm-0.9.8.4)
#include_directories(${GLM_INCLUDE_DIRECTORY})

#set(GLFW_INCLUDE_DIRECTORY C:/Documents/GLFW/glfw-3.2.1/include/GLFW)
#include_directories(${GLFW_INCLUDE_DIRECTORY})

set(GLUT_INCLUDE_DIRECTORY C:/Documents/OpenGL\ Drivers/compiler\ needs/include)
include_directories(${GLUT_INCLUDE_DIRECTORY})


#    # LIBRARIES   -----------------------------------------------------
set(GLEW_LIB_DIRECTORY C:/Documents/GLEW/glew-2.0.0-win32/glew-2.0.0/lib/Release/Win32)

#add_library(glew32.lib SHARED IMPORTED)
#set_property(TARGET glew32.lib PROPERTY IMPORTED_LOCATION "C:/Documents/GLEW/glew-2.0.0-win32/glew-2.0.0/lib/Release/x64")


#target_link_libraries(OpenGLProva "C:/Documents/GLFW/glfw-3.2.1_build/lib-mingw-w64/glfw3.dll")
#target_link_libraries(OpenGLProva "C:/Documents/GLFW/glfw-3.2.1_build/lib-mingw-w64/libglfw3.a")