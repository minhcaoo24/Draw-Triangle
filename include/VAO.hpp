#include <glad/glad.h>

#include "VBO.hpp"

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& vbo, GLuint layout, GLint numComponents, GLsizei stride, const void* offset);
    void Bind();
    void Unbind();
    void Delete();
};