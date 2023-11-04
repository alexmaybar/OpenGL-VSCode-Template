#include <iostream>
#include <math.h>
#include <vector>

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <GLM/common.hpp>
#include <GLM/vec3.hpp>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

using namespace glm;

// Vertices coordinates
vec3 buffer_data[] = {
    vec3(-.1f, 0.0f, 0.0f),
    vec3(-.6f, 0.0f, 0.0f),
    vec3(-.35f, -.25f, 0.0f),
    vec3(-.35f, .25f, 0.0f),
    vec3(.1f, 0.0f, 0.0f),
    vec3(.6f, 0.0f, 0.0f),
    vec3(.35f, -.25f, 0.0f),
    vec3(.35f, .25f, 0.0f),
    vec3(0.0f, .1f, 0.0f),
    vec3(0.0f, .6f, 0.0f),
    vec3(-.25f, .35f, 0.0f),
    vec3(.25f, .35f, 0.0f),
    vec3(0.0f, -.1f, 0.0f),
    vec3(0.0f, -.6f, 0.0f),
    vec3(-.25f, -.35f, 0.0f),
    vec3(.25f, -.35f, 0.0f)};

// Indices for vertices order
GLuint indices[] =
    {0, 1, 2,
     0, 1, 3,
     4, 5, 6,
     4, 5, 7,
     8, 9, 10,
     8, 9, 11,
     12, 13, 14,
     12, 13, 15};

const int WIDTH = 1280;
const int HEIGHT = 720;

void log(std::string message)
{
    std::cout << message << std::endl;
}

// Lock the view port into the specified aspect ratio
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    float ratio = (float)HEIGHT / (float)WIDTH;
    int scaledHeight = (int)(ratio * width);

    if (scaledHeight >= height)
    {
        int scaledWidth = (int)((1 / ratio) * height);
        glViewport(0, 0, scaledWidth, height);
    }
    else
    {
        glViewport(0, 0, width, scaledHeight);
    }
}

int main()
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "My Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    log("Begin Loading Shaders...");
    // Generates Shader object using shaders defualt.vert and default.frag
    Shader shaderProgram("default.vert", "default.frag");
    log("Shaders Loaded!");

    // Generates Vertex Array Object and binds it
    VAO VAO1;
    VAO1.Bind();

    // Generates Vertex Buffer Object and links it to vertices
    VBO VBO1(buffer_data, sizeof(buffer_data));
    // Generates Element Buffer Object and links it to indices
    EBO EBO1(indices, sizeof(indices));

    // Links VBO to VAO
    VAO1.LinkVBO(VBO1, 0);
    // Unbind all to prevent accidentally modifying them
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        shaderProgram.Activate();
        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        // Draw primitives, number of indices, datatype of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}