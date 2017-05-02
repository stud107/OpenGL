

#if ( (defined(__MACH__)) && (defined(__APPLE__)) )
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glext.h>
#else
//#include <stdlib.h>
//#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glut.h>
//#include <GL/glext.h>
#include <iostream>
#endif

#include "Includes/shader.h"

Shader* shader;

GLuint texture;

GLfloat angle = 0.0; //set the angle of rotation


GLuint LoadTexture(const char* filename, int width, int heigth) {
    GLuint texture;
    unsigned char* data;
    FILE* file;

    // The following code will read in our RAW file.
    file = fopen(filename, "rb");

    if (file == NULL) {
        std::cerr << "Texture not found!" << std::endl;
        return 0;
    }

    data = (unsigned char *)malloc(width * heigth * 3);
    fread(data, width * heigth * 3, 1, file);
    fclose(file);

    // generate the texture when loaded data.
    glGenTextures(1, &texture);
    // Bind the texture to it's array.
    glBindTexture(GL_TEXTURE_2D, texture);
    // Set texture environment parameters.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // And if you go and use extensions, you can use Anisotropic filtering textures
    // which are of an even better quality, but this will do for now.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Here we are setting the parameter to repeat the texture instead of clamping the texture
    // to the edge of our shape.
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Generate the texture.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, heigth, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    // Free the texture.
    free(data);

    // Return whether it was successfull.
    return texture;
}

void FreeTexture(GLuint texture) {
    glDeleteTextures(1, &texture);
}

void init(void) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //shader.init("shader.vert", "shader.frag");
    shader = new Shader("../shader.vert", "../shader.frag");
    // "/home/cloud/CLionProjects/OpenGLProva/OpenGLProva/Resources/Texture/Ball-256x256.bmp"
    texture = LoadTexture("../Resources/Texture/Ball-256x256.bmp", 256, 256);
}

void my_object(void) {
    glRotatef(angle, 1.0, 0.0, 0.0); //rotate on the x axis
    glRotatef(angle, 0.0, 1.0, 0.0); //rotate on the y axis
    glRotatef(angle, 0.0, 0.0, 1.0); //rotate on the z axis

    glActiveTexture(GL_TEXTURE0);
    int texture_location = glGetUniformLocation(shader->id(), "texture_color");
    glUniform1i(texture_location, 0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //glutWireCube(2);
    //glutSolidCube(3);
    glutSolidTeapot(4.0);
}

void display(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    shader->bind();
    my_object();
    shader->unbind();

    glutSwapBuffers();
    angle += 0.1f;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    std::cout << "This is a test!";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); //set up the double buffering
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("A basic OpenGL Window");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    /// Extremely important.
    glewInit();

    glutReshapeFunc(reshape);

    init();

    glutMainLoop();

    return 0;
}
