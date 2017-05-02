cmake_minimum_required(VERSION 3.7)
project(OpenGLProva)

set(CMAKE_CXX_STANDARD 11)


# WINDOWS LIBRARIES PATHS
# SET ------
set(GLUT_INCLUDE_DIR C:/Documents/freeglut/include)
set(GLUT_glut_LIBRARY C:/Documents/freeglut_MinGW/lib/x64)
set(GLEW_INCLUDE_DIR C:/Documents/GLEW/glew-2.0.0-win32/glew-2.0.0/include)
set(GLEW_LIBRARY C:/Documents/GLEW/glew-2.0.0-win32/glew-2.0.0/lib/Release/x64)

#    # INCLUDES    -----------------------------------------------------
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLUT_INCLUDE_DIR})

#    # LINKER      -----------------------------------------------------
link_directories("${GLEW_LIBRARY}")
link_directories("${GLUT_glut_LIBRARY}")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU REQUIRED)

set(EXT_LIBS ${OPENGL_gl_LIBRARY} CACHE STRING "I want to be sure this is the first time use." FORCE)
set(EXT_LIBS ${EXT_LIBS} ${GLEW_LIBRARY}/glew32s.lib ${GLEW_LIBRARY}/glew32.lib)
set(EXT_LIBS ${EXT_LIBS} ${GLUT_glut_LIBRARY}/libfreeglut.a)
set(EXT_LIBS ${EXT_LIBS} ${GLU_LIBRARY})


set(SOURCE_FILES main.cpp Includes/shader.cpp Includes/shader.h Includes/utils.h)
add_executable(OpenGLProva ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${EXT_LIBS})