#pragma once


#ifndef CALLBACK
#if defined(_ARM_)
#define CALLBACK
#else
#define CALLBACK __stdcall
#endif
#endif

#if (defined(__MACH__)) && (defined(__APPLE__))
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#else
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#endif

#include <string>

class Shader
{
public:
    Shader();
    Shader(const char *vsFile, const char *fsFile);	// Constructor with parameters.
    ~Shader();

    void init(const char *vsFile, const char *fsFile);	// Another way to create a shader.
    void bind();	// To enable the shader.
    void unbind();	// To disable the shader.
    unsigned int id();	// To get the number associated with our shader.

private:
    unsigned int shader_id;
    unsigned int shader_vp;
    unsigned int shader_fp;
};