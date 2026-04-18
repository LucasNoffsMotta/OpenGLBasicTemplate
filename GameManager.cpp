#include "GameManager.h"
#include <glm/fwd.hpp>
#include <random>
#include "Snake.h"


void GameManager::CheckInput(GLFWwindow* window, int invalidInputKey)
{
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        IsPlaying = false;

	if (IsPlaying == true) return;

	//Only called if game is paused, aka IsPLaying == false:
	int pressedKey = GetPressedInputKey(window);

    if (pressedKey != invalidInputKey && pressedKey != 0)
        IsPlaying = true;
}

void GameManager::RestartFood(Object2D& apple)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	float min = -0.9f;
	float max = 0.9f;
	std::uniform_real_distribution<float> dis(min, max);

	float newX = dis(gen);
	float newY = dis(gen);

	glm::vec3 newLocation = glm::vec3(newX, newY, 0.f);
	apple.SetTranslation(newLocation);
}

bool GameManager::CheckCollision(Object2D& obj1, Object2D& obj2)
{
	bool collisionX = obj1.GetTranslation().x + 0.05f >= obj2.GetTranslation().x &&
		obj2.GetTranslation().x + 0.05f >= obj1.GetTranslation().x;

	bool collisionY = obj1.GetTranslation().y + 0.05f >= obj2.GetTranslation().y &&
		obj2.GetTranslation().y + 0.05f >= obj1.GetTranslation().y;

	return collisionX && collisionY;
}

void GameManager::Update(GLFWwindow* window, int invalidInputKey, Object2D& apple, Snake& snake)
{
    CheckInput(window, invalidInputKey);

	if (!IsPlaying) return;

	if (CheckCollision(apple, *snake.pointerBody.front()))
	{
		RestartFood(apple);
		snake.EatFood();
	}
}

int GameManager::GetPressedInputKey(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		return GLFW_KEY_UP;
	}

	else if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		return GLFW_KEY_DOWN;
	}

	else if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		return GLFW_KEY_LEFT;
	}

	else if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		return GLFW_KEY_RIGHT;
	}

	return 0;
}
