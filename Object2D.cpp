#include "Object2D.h"



Object2D::Object2D(GLfloat* square, GLsizeiptr size)
{
    _renderShit = RenderShit(square, size);
}

void Object2D::Update(glm::vec3 scale)
{
    CalculateMatrixPosition(scale);
    _renderShit.vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    _renderShit.vao.Unbind();
}

void Object2D::SetTranslation(glm::vec3& translation)
{
    Tranlation = translation;
}

glm::vec3 Object2D::GetTranslation()
{
    return Tranlation;
}

glm::vec3 Object2D::GetRotation()
{
    return Rotation;
}

void Object2D::SetRotation(glm::vec3 rotation)
{
    Rotation = rotation;
}

glm::vec3 Object2D::GetScale()
{
    return Scale;
}

void Object2D::SetScale(glm::vec3 scale)
{
    Scale = scale;
}

void Object2D::CalculateMatrixPosition(glm::vec3 scale)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Tranlation);
    model = glm::rotate(model, 0.f, glm::vec3(Rotation.x, Rotation.y, Rotation.z));
    model = glm::scale(model, scale);

    _renderShit.shader.Activate();
    _renderShit.shader.SetUniformMatrix4fv("model", model);
}
