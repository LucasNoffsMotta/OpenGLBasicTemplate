#include <list>
#include "Object2D.h"
#include <vector>
#include <deque>
#ifndef SNAKE_CLASS_H
#define SNAKE_CLASS_H

class Snake
{

	glm::vec3 direction = glm::vec3(-0.05f, 0.f, 0.f);
	GLfloat* vertexArray; 
	GLsizeiptr verticesSize;
	float moveOffset = 0.05f;
	float moveSpeed = 1.3f;
	float inputTimer = 0.f;
	bool isAlive = true;



public:
	std::deque<std::shared_ptr<Object2D>> pointerBody;
	int invalidInputKey = 0;
	Snake(GLfloat* square, GLsizeiptr size);
	void Update(GLFWwindow* window, GLfloat& deltaTime, bool& isPlaying);
	void Draw();
	void HandleInput(GLFWwindow* window, float dt);
	glm::vec3 SnakeHeadPositon = glm::vec3(1.0f);
	float moveTimer = 1.f;
	void RearrangeBody(glm::vec3 value);
	void MoveSnake(GLfloat& deltaTime);
	void AddSegment();
	void EatFood();
	void ConstructBody(glm::vec3 offset, int size);
	int GetInvalidInputKey();
};

#endif // !SNAKE_CLASS_H
