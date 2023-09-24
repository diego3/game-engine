#include "CubeMesh.h"

#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/OpenGlErrorHandler.h>
#include <Engine/Graphics/ShaderCompiler.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>  // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection
#include <glm/gtc/type_ptr.hpp> 

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) glError->ClearError();\
    x;\
    ASSERT(glError->LogError(#x, __FILE__, __LINE__))

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-4-a-colored-cube/

CubeMesh::CubeMesh()
{
    
}

CubeMesh::~CubeMesh()
{

}

std::vector<float> CubeMesh::GetVertices() const
{
	return this->vertices;
}

void CubeMesh::SetUp()
{
    this->glError = new OpenGlErrorHandler();

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertices_tutorial1[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    float vertices[] = {
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,

     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f
    };

    GLuint vertexArrayBuffer;
    GlCall(glGenBuffers(1, &vertexArrayBuffer));
    GlCall(glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffer));
    GlCall(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    GLuint vertexArrays;
    GlCall(glGenVertexArrays(1, &vertexArrays));
    GlCall(glBindVertexArray(vertexArrays));

    GlCall(glVertexAttribPointer(
        0,                                // attribute. No particular reason for 0, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
    ));
    GlCall(glEnableVertexAttribArray(0));

    // learned: gl_position sempre é um vec4, por que? o que seria a ultima posicao do vetor?
    std::string vertexShader = R"glsl(
        #version 330 core
        
        layout(location = 0) in vec3 position;
        
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        
        out vec4 myColor;

        void main() {
            
            gl_Position = projection * view * model * vec4(position, 1.0);
            myColor = vec4(1, 0, 0, 1);
        } 
    )glsl";

    std::string fragmentShader = R"dem(
        #version 330 core
        
        out vec4 FragColor;
        in vec4 myColor;

        void main() {
            FragColor = myColor; 
        }
    )dem";

    this->shaderProgram = ShaderCompiler::Create(vertexShader, fragmentShader);
    
}

void CubeMesh::Render(double deltaTime)
{
    GlCall(glUseProgram(shaderProgram));

    glm::mat4 model = glm::mat4(1.0f);
   // model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    model = glm::rotate(model, (float)deltaTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 1200.f / 640.0f, 0.1f, 100.0f);

    GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
    GLint viewlLoc = glGetUniformLocation(this->shaderProgram, "view");
    GLint projectionlLoc = glGetUniformLocation(this->shaderProgram, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewlLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionlLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GlCall(glDrawArrays(GL_TRIANGLES, 0, 12 * 3)); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
}
