#include "ShaderCompiler.h"

#include <GL/glew.h>


unsigned int ShaderCompiler::Compile(unsigned int type, std::string& shaderCode)
{
    unsigned int shader = glCreateShader(type);
    const char* code = shaderCode.c_str();

    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint compileStatus;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (compileStatus != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        // Write the error to a log
        std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragmet") << " shader compile error: " << message << std::endl;
    }

    return shader;
}


unsigned int ShaderCompiler::Create(std::string& vertex, std::string& fragment) {
    unsigned int program = glCreateProgram();
    unsigned int vs = ShaderCompiler::Compile(GL_VERTEX_SHADER, vertex);
    unsigned int fs = ShaderCompiler::Compile(GL_FRAGMENT_SHADER, fragment);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    GLint linkerStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &linkerStatus);
    if (linkerStatus != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(program, 1024, &log_length, message);
        // Write the error to a log
        std::cout << "shader linker error: " << message << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}