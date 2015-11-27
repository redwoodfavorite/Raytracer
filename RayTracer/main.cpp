#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

//
//  main.cpp
//  RayTracer
//
//  Created by Joseph Sample on 11/25/15.
//  Copyright © 2015 Joseph Sample. All rights reserved.
//

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <iostream>
#include "./loadShader.hpp"

//static const GLfloat g_vertex_buffer_data[] = {
//    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
//    -1.0f,-1.0f, 1.0f,
//    -1.0f, 1.0f, 1.0f, // triangle 1 : end
//    1.0f, 1.0f,-1.0f, // triangle 2 : begin
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f,-1.0f, // triangle 2 : end
//    1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f, 1.0f,
//    -1.0f,-1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    -1.0f,-1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f,-1.0f,
//    1.0f,-1.0f,-1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f,-1.0f,
//    -1.0f, 1.0f,-1.0f,
//     1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f,-1.0f,
//    -1.0f, 1.0f, 1.0f,
//    1.0f, 1.0f, 1.0f,
//    -1.0f, 1.0f, 1.0f,
//    1.0f,-1.0f, 1.0f
//};

static float points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};

static float colors[] = {
    0.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 0.0f
};

void display (GLuint &vao) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint initialize() {
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    GLuint vertexBuffer, colorBuffer;
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
    
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);
    
    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(programID);
    
    glEnable (GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc (GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    return vao;
}

int main(void)
{
    GLFWwindow* window;
    
    /* Initialize the library */
    if (!glfwInit())
        return -1;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit ();

    GLuint vao = initialize();
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        display(vao);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        
        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
