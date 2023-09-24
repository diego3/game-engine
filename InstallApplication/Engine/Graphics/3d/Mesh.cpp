#include <string>
#include <iostream>

#include "Mesh.hpp"
#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/OpenGlErrorHandler.h>
#include <Engine/Graphics/ShaderCompiler.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) glError->ClearError();\
    x;\
    ASSERT(glError->LogError(#x, __FILE__, __LINE__))

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

    GLuint vbo;
    GlCall(glGenBuffers(1, &vbo));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));

    GLuint vao;
    GlCall(glGenVertexArrays(1, &vao));
    GlCall(glBindVertexArray(vao));

    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));
    //GlCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
    GlCall(glVertexAttribPointer(
        0,                                // attribute. No particular reason for 0, but must match the layout in the shader.
        2,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        2 * sizeof(float),                // stride
        (void*)0                          // array buffer offset
    ));
    GlCall(glEnableVertexAttribArray(0));

    GLuint indicesData[6];
    for (int i = 0; i < std::size(indices); i++) {
        indicesData[i] = indices[i];
    }

    GLuint ibo;
    GlCall(glGenBuffers(1, &ibo));
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

    this->shaderProgram = ShaderCompiler::Create(vertexShader, fragmentShader);
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
