#include <GLFW/glfw3.h>
#include <glad/glad.h> 

#include <iostream>
#include "Window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window);


float vertices[] = {
    // positions          // colors          
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // top left 
};

unsigned int indices[] = {
   0, 1, 3, // first triangle
   1, 2, 3  // second triangle
};

int main()
{
    glfwInit();
    Window window = Window(SCR_WIDTH, SCR_HEIGHT, "OpenGL");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    if (!window.CheckIfWindowWasCreated())
    {
        glfwTerminate();
        return -1;
    }

    window.SetViewPort(window.SCREEN_WIDTH, window.SCREEN_HEIGHT);
    window.framebuffer_size_callback();

    VAO vao = VAO();
    vao.Bind();
    VBO vbo = VBO(vertices, sizeof(vertices));
    EBO ebo = EBO(indices, sizeof(indices));
    ebo.Bind();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));

    Shader shader("vert.vert", "frag.frag");
    shader.Activate();

    while (!glfwWindowShouldClose(window.window))
    {
        window.ChangeBackgroundColor(0.5f, 0.5f, 0.5f, 1.0f);
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.Unbind();
        processInput(window.window);
        window.Update();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

