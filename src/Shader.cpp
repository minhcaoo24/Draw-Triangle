#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>

std::string get_file_contents(std::string file) {
  std::ifstream ifs(file, std::ios::binary);
  if (ifs) {
    std::string contents;
    ifs.seekg(0, std::ios::end);
    contents.resize(ifs.tellg());
    ifs.seekg(0, std::ios::beg);
    ifs.read(&contents[0], contents.size());
    ifs.close();
    return contents;
  }
  std::cerr << "FAILED TO OPEN FILE: " << file << std::endl;
  throw std::runtime_error("Shader file not found");
}

Shader::Shader(std::string vertexFile, std::string fragmentFile) {
  auto vertexFileContent = get_file_contents(vertexFile);
  auto fragmentFileContent = get_file_contents(fragmentFile);

  auto vertexSource = vertexFileContent.c_str();
  auto fragmentSource = fragmentFileContent.c_str();

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, nullptr);
  glCompileShader(vertexShader);
  compileErrors(vertexShader, "VERTEX");

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
  glCompileShader(fragmentShader);
  compileErrors(fragmentShader, "FRAGMENT");

  ID = glCreateProgram();
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  glLinkProgram(ID);
  compileErrors(ID, "PROGRAM");

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::Active() { glUseProgram(ID); }

void Shader::Delete() { glDeleteProgram(ID); }

void Shader::compileErrors(GLuint shader, const char *type) {
  // Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}