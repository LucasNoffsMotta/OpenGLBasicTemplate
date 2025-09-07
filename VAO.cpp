#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &Id);
}


void VAO::Bind()
{
	glBindVertexArray(Id);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}