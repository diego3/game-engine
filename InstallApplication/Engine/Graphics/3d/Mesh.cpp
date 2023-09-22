#include <string>
#include <iostream>


#include "Mesh.hpp"
#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/OpenGlErrorHandler.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) glError->ClearError();\
    x;\
    ASSERT(glError->LogError(#x, __FILE__, __LINE__))

static unsigned int CompileShader(unsigned int type, std::string& shaderCode) {
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

static unsigned int CreateShader(std::string& vertex, std::string& fragment) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);

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


Mesh::Mesh(float velocity)
{
    right = 0;
    this->velocity = velocity;
}

Mesh::~Mesh()
{
    GlCall(glDeleteProgram(this->shaderProgram));
}

void Mesh::SetUp()
{
    this->glError = new OpenGlErrorHandler();

    GLuint vbo;
    GlCall(glGenBuffers(1, &vbo));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    GLuint vao;
    GlCall(glGenVertexArrays(1, &vao));

    GLuint ibo;
    GlCall(glGenBuffers(1, &ibo));

    //std::cout << "buffer: " << vbo << std::endl;

    float vertices[8] = {
        -0.5f, 0.2f,
        -0.5f, 0.0f,
        -0.6f, 0.2f,

        //-0.6f, 0.2f,
        //-0.8f, 0.0f,
        -0.6f, 0.0f
    };

    indices = {
        0, 1, 2,
        1, 2, 3
    };

    GlCall(glBindVertexArray(vao));
    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GlCall(glEnableVertexAttribArray(0));

    GLuint indicesData[6];
    for (int i = 0; i < std::size(indices); i++) {
        indicesData[i] = indices[i];
    }

    GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW));

    std::string vertexShader = R"glsl(
        #version 330 core
        
        layout(location = 0) in vec4 position;
        
        uniform vec4 u_Position;

        void main() {
            
            gl_Position = position + u_Position;
        } 
    )glsl";

    std::string fragmentShader = R"dem(
        #version 330 core
        
        out vec4 color;
        
        uniform vec4 u_Color;

        void main() {
            vec4 ambientColor = vec4(1, 1, 1, 1.0) * 0.5;
            color = u_Color * ambientColor;
        }
    )dem";

    this->shaderProgram = CreateShader(vertexShader, fragmentShader);
    GlCall(glUseProgram(shaderProgram));

    GlCall(this->fragColorUnId = glGetUniformLocation(shaderProgram, "u_Color"));
    GlCall(glUniform4f(fragColorUnId, 0.2, 0.8, 0.3, 1.0));

    GlCall(this->vertexPosUnId = glGetUniformLocation(shaderProgram, "u_Position"));
}

void Mesh::Render(double deltaTime)
{
    timePass += deltaTime;
    if (timePass >= 1000.f) {
        right += velocity;
        timePass = 0;
    }

    
    GlCall(glUniform4f(this->vertexPosUnId, right, 0.5, 0.0, 1.0));
    GlCall(glDrawElements(GL_TRIANGLES, std::size(this->indices), GL_UNSIGNED_INT, (const void*)0));
}

void Mesh::setUniform()
{

}
