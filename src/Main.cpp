#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.hpp"
#include "VAO.hpp"

void processWindow(GLFWwindow *window);

GLfloat vertices[] = {-.5f, -.5f * float(sqrt(3)) / 3,     0.0f,        0.498, 0.988, 0.984,
                      .5f,  -.5f * float(sqrt(3)) / 3,     0.0f,        0.133, 0.612, 1,
                      0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    0.71, 0.059, 0.78};

int main(int, char **) {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize glfw" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  constexpr float SCR_WIDTH = 800;
  constexpr float SCR_HEIGHT = 800;

  GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Draw Triangle",
                                        nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize glad" << std::endl;
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  Shader shaderProgram("shaders/triangle.vert", "shaders/triangle.frag");

  VAO vao;
  vao.Bind();

  VBO vbo(vertices, sizeof(vertices));

  vao.LinkAttrib(vbo, 0, 3, 6 * sizeof(float), (void*) 0);
  vao.LinkAttrib(vbo, 1, 3, 6 * sizeof(float), (void*) (3 * sizeof(float)));

  vao.Unbind();
  vbo.Unbind();

  constexpr float SCALE = 1.7f;
  auto uniID = glGetUniformLocation(shaderProgram.ID, "scale");
  std::cout << uniID << '\n';

  while (!glfwWindowShouldClose(window)) {
    processWindow(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.Active();
    glUniform1f(uniID, SCALE);
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  vao.Delete();
  vbo.Delete();
  shaderProgram.Delete();

  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}

void processWindow(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}