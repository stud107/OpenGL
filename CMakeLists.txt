cmake_minimum_required(VERSION 3.7)
project(OpenGLProva)

set(CMAKE_CXX_STANDARD 11)



find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLU)

set(SOURCE_FILES main.cpp Includes/shader.cpp Includes/shader.h Includes/utils.h)
add_executable(OpenGLProva ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} ${GLUT_LIBRARY} ${GLU_LIBRARY})