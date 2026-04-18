#include "Snake.h"
#include <random>

Snake::Snake(GLfloat* _square, GLsizeiptr _size)
{
	vertexArray = _square;
	verticesSize = _size;
	float bodySize = 3;
	SnakeHeadPositon = glm::vec3(0.0f, -0.5f, 0.f);
	ConstructBody(glm::vec3(0.05f, 0.f, 0.f), bodySize);
	pointerBody.front()->SetColor(glm::vec3(0.f, 1.f, 0.f));
	invalidInputKey = GetInvalidInputKey();
}

void Snake::Update(GLFWwindow* window, GLfloat& deltaTime, bool& isPlaying)
{
	glm::vec3 rotation = glm::vec3(1.0f);
	isPlaying = isAlive;
	GLfloat rotationAngle = 0.0f;
	MoveSnake(deltaTime);
	HandleInput(window, deltaTime);
	invalidInputKey = GetInvalidInputKey();
}

void Snake::Draw()
{
	glm::vec3 scale = glm::vec3(0.05f);

	for (auto& segment : pointerBody)
	{
		segment->ColorMultiplier = pointerBody.size();
		segment->Update(scale);
	}
}

void Snake::HandleInput(GLFWwindow* window, float dt)
{
	inputTimer += 1.1 * dt;

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && (GLFW_KEY_UP != invalidInputKey) && inputTimer >= 0.005)
	{
		direction = glm::vec3(0.0f, moveOffset, 0.f);
		inputTimer = 0;
	}

	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && (GLFW_KEY_DOWN != invalidInputKey) && inputTimer >= 0.005)
	{
		direction = glm::vec3(0.0f, -moveOffset, 0.f);
		inputTimer = 0;
	}

	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && (GLFW_KEY_LEFT != invalidInputKey) && inputTimer >= 0.005)
	{
		direction = glm::vec3(-moveOffset, 0.f, 0.f);
		inputTimer = 0;
	}

	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && (GLFW_KEY_RIGHT != invalidInputKey) && inputTimer >= 0.005)
	{
		direction = glm::vec3(moveOffset, 0.f, 0.f);
		inputTimer = 0;
	}
}

int Snake::GetInvalidInputKey()
{
	if (direction == glm::vec3(0.0f, moveOffset, 0.0f))
	{
		return GLFW_KEY_DOWN;
	}

	else if (direction == glm::vec3(0.0f, -moveOffset, 0.0f))
	{
		return GLFW_KEY_UP;
	}

	else if (direction == glm::vec3(moveOffset, 0.f, 0.0f))
	{
		return GLFW_KEY_LEFT;
	}

	else if (direction == glm::vec3(-moveOffset, 0.f, 0.0f))
	{
		return GLFW_KEY_RIGHT;
	}
}

void Snake::RearrangeBody(glm::vec3 value)
{
	pointerBody.front()->SetColor(glm::vec3(0.f, 1.f, 0.f));
	glm::vec3 newHeadPos = pointerBody.front()->GetTranslation();
	newHeadPos += value;
	
	for (int i = 0; i < pointerBody.size(); i++)
	{
		if (newHeadPos == pointerBody[i]->GetTranslation())
		{
			isAlive = false;
		}
	}
	pointerBody.back()->SetTranslation(newHeadPos);
	auto back = pointerBody.back();
	pointerBody.pop_back();
	pointerBody.push_front(back);
	back->SetColor(glm::vec3(0.0f, 0.5f, 0.0f));
}

void Snake::MoveSnake(GLfloat& deltaTime)
{
	moveTimer += 2 * (deltaTime);

	if (moveTimer >= moveSpeed)
	{
		RearrangeBody(direction);
		moveTimer = 1;
	}

	if (moveTimer >= moveSpeed)
	{
		RearrangeBody(direction);
		moveTimer = 1;
	}

	if (moveTimer >= moveSpeed)
	{
		RearrangeBody(direction);
		moveTimer = 1;
	}

	if (moveTimer >= moveSpeed)
	{
		RearrangeBody(direction);
		moveTimer = 1;
	}
}

void Snake::AddSegment()
{
	Object2D newSegment = Object2D(vertexArray, verticesSize);
	pointerBody.push_back(std::make_shared<Object2D>(newSegment));
}

void Snake::EatFood()
{
	AddSegment();
	if (moveSpeed >= 1.2f) moveSpeed -= 0.01f;
}

void Snake::ConstructBody(glm::vec3 offset, int bodySize)
{
	for (int i = 0; i < bodySize; i++)
	{
		Object2D segment = Object2D(vertexArray, verticesSize);
		segment.ID = i;
		segment.SetTranslation(SnakeHeadPositon);
		segment.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
		pointerBody.push_back(std::make_shared<Object2D>(segment));
		SnakeHeadPositon += offset;
	}
}



