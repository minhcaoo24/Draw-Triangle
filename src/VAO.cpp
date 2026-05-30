#include <glad/glad.h>

#include "VAO.hpp"

VAO::VAO() {
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLint numComponents, GLsizei stride, const void* offset){
    vbo.Bind();
    glVertexAttribPointer(layout, numComponents, GL_FLOAT, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    vbo.Unbind();
}

void VAO::Bind(){
    glBindVertexArray(ID);
}

void VAO::Unbind(){
    glBindVertexArray(0);
}

void VAO::Delete(){
    glDeleteVertexArrays(1, &ID);
}