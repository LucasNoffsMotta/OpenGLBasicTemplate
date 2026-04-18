#include "Shader.h"
#include "VAO.h"


#ifndef OBJECT_2D_CLASS_H
#define OBJECT_2D_CLASS_H


struct RenderShit
{
	Shader shader;
	VAO vao;
	VBO vbo;

	RenderShit() {}

	RenderShit(GLfloat* square, GLsizeiptr size)
	{
		vao = VAO();
		vbo = VBO(square, size);
		vao.Bind();
		vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(float) * 6, (void*)0);
		vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(float) * 6, (void*)(3 * sizeof(float)));
		shader = Shader("vert.vert", "frag.frag");
		shader.Activate();
	}
};


class Object2D
{
private:
	glm::vec3  Tranlation;
	glm::vec3  Rotation;
	glm::vec3  Scale;


public:
	Object2D(GLfloat* square, GLsizeiptr size);
	RenderShit _renderShit;
	void Update(glm::vec3 scale);
	int ID = 0;

	void SetTranslation(glm::vec3& translation);
	glm::vec3 GetTranslation();

	glm::vec3 GetRotation();
	void SetRotation(glm::vec3 rotation);

	glm::vec3 GetScale();
	void SetScale(glm::vec3 scale);

	void CalculateMatrixPosition(glm::vec3 scale);
};


#endif // !OBJECT_2D_H
