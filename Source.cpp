#include <GLFW/glfw3.h>
#include <glad/glad.h> 

#include <iostream>
#include "Window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object2D.h"
#include "Snake.h"
#include "GameManager.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow* window);

//TODO: gm -> Cuida da logica da apple
//vector factory->cuida da logica das direcoes x enum
//content manager->cuida da logica dos shaders, textures e etc

float snakeVertices[] = {
    // positions          // colors          
      0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,  
      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f, 
     -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,  
      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,  
     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f
};

float appleVertices[] = {
    // positions          // colors          
      0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 0.0f
};



float square[] = {
    // positions          // colors          
     0.1f,  0.1f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
     0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
    -0.1f, -0.1f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
    -0.1f,  0.1f, 0.0f,   1.0f, 1.0f, 0.0f,  // top left 
};


unsigned int indices[] = {
   0, 1, 3, // first triangle
   1, 2, 3  // second triangle
};



int main()
{
    GLfloat lastFrame = 0.f;
    GLfloat deltaTime = 0.f;

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

    Snake snake = Snake(snakeVertices, sizeof(snakeVertices));
    Object2D apple = Object2D(appleVertices, sizeof(appleVertices));
    apple.SetColor(glm::vec3(1.0f, 0.f, 0.f));
    GameManager gm = GameManager();

    glm::vec3 applePos = glm::vec3(-0.3f, 0.1f, 0.f);
    apple.SetTranslation(applePos);


    while (!glfwWindowShouldClose(window.window))
    {
        float currentFrame = glfwGetTime(); 
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.ChangeBackgroundColor(0.f, 0.f, 0.f, 1.0f);

        if (gm.IsPlaying)
        {
            snake.Update(window.window, deltaTime, gm.IsPlaying);
        }

        snake.Draw();
        apple.Update(glm::vec3(0.04f));

        gm.Update(window.window, snake.invalidInputKey, apple, snake);
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

