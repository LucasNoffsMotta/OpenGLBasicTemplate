#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include "Snake.h"
#include "Object2D.h"

#ifndef GAME_MANAGER_CLASS_H
#define GAME_MANAGER_CLASS_H

class GameManager
{
public:

	bool IsPlaying = false;
	void Update(GLFWwindow* window, int invalidInputKey, Object2D& apple, Snake& snake);
	bool CheckCollision(Object2D& obj1, Object2D& obj2);

private:
	int GetPressedInputKey(GLFWwindow* window);
	void CheckInput(GLFWwindow* window, int invalidInputKey);
	void RestartFood(Object2D& apple);

};


#endif