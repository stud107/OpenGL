#include <cstring>
#include "shader.h"
#include "utils.h"


//
static void validateShader(GLuint shader, const char* file = 0) {
    // The sisze of the ouput buffer.
    const unsigned int BUFFER_SIZE = 512;
    // It will contain the output from our validation.
    char buffer[512];
    memset(buffer, 0, BUFFER_SIZE);
    // It will contain the length of the buffer we get back from OpenGL.
    GLsizei length = 0;

    // Read back the shader log from opengl and store it in our buffer.
    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    // Just output the error, if there is any.
    if (length > 0) {
        std::cerr << "Shader" << shader << " (" << (file ? file : "") << ") compile error: " << buffer << std::endl;
    }
}

static void validateProgram(GLuint program) {
    const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    GLsizei length = 0;

    glGetShaderInfoLog(program, BUFFER_SIZE, &length, buffer);

    if (length > 0) {
        std::cerr << "Program " << program << " link error:" << buffer << std::endl;
    }

    glValidateProgram(program);

    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE) {
        std::cerr << "Error validating shader " << program << std::endl;
    }
}


Shader::Shader() {

}

Shader::Shader(const char *vsFile, const char *fsFile) {
    init(vsFile, fsFile);
}

void Shader::init(const char *vsFile, const char *fsFile) {
    // We're going to tell OpenGL to create a vertex shader and  a fragment shader,
    //  and assign the id's of these to our shader_vp and shader_fp variables.
    shader_vp = glCreateShader(GL_VERTEX_SHADER);
    shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

    // The content of our shader files.
    const char* vsText = textFileRead(vsFile);
    const char* fsText = textFileRead(fsFile);

    // Check if vertex and fragment shader files have been read properly.
    if (vsText == NULL || fsText == NULL) {
        std::cerr << "Either vertex shader or fragment shader file not found" << std::endl;
        return;
    }

    // The following two lines pass our shader file contens to OpenGL to attach it tou our shaders.
    glShaderSource(shader_vp, 1, &vsText, 0);
    glShaderSource(shader_fp, 1, &fsText, 0);

    // These next two lines, tells OpenGL to compile our shaders, which we have already bound
    //  the source code to.
    glCompileShader(shader_vp);
    validateShader(shader_vp, vsFile);
    glCompileShader(shader_fp);
    validateShader(shader_fp, fsFile);

    // We create our shader_id as a shader program.
    shader_id = glCreateProgram();
    //  and then attach the vertex shader and the fragment shader to the shader program,
    glAttachShader(shader_id, shader_fp);
    glAttachShader(shader_id, shader_vp);
    //  and finally, link the program.
    glLinkProgram(shader_id);

    validateProgram(shader_id);
}

// This method will return the shader_id program.
//  This is used for when we bind our shader, or for when we want to pass variables through
//  to our shader.
unsigned int Shader::id() {
    return shader_id;
}

// This method will simply attach our shader, and anything drawn afterwards will use this shader,
//  either until this shader is unbound or another shader is enabled.
void Shader::bind() {
    glUseProgram(shader_id);
}


// This method simply binds the shader 0, which is reserved for OpenGL, and will disable
//  our current shader.
void Shader::unbind() {
    glUseProgram(0);
}


Shader::~Shader() {
    glDetachShader(shader_id, shader_fp);
    glDetachShader(shader_id, shader_vp);

    glDeleteShader(shader_fp);
    glDeleteShader(shader_vp);
    glDeleteProgram(shader_id);
}