#include <glad/glad.h>
#include <string>

std::string get_file_contents(std::string file);

class Shader {
public:
    GLuint ID;

    Shader(std::string vertexFile, std::string fragmentFile);
    void Active();
    void Delete();
    private:
    void compileErrors(GLuint shader, const char* type);
};