
#include <iostream>
#include <map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <Engine/Graphics/OpenGlErrorHandler.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) glError->ClearError();\
    x;\
    ASSERT(glError->LogError(#x, __FILE__, __LINE__))

static unsigned int CompileShader(unsigned int type, std::string &shaderCode) {
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

void error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw callback error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void RunOpenGlApp() {
    if (!glfwInit()) {
        std::cout << "GLFW: Initialization failed" << std::endl;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW - Project", NULL, NULL);
    if (!window) {
        std::cout << "Window or OpenGL context creation failed" << std::endl;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glewInit();

    std::unique_ptr<OpenGlErrorHandler> glError = std::make_unique<OpenGlErrorHandler>();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();



    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    GLuint vao;
    glGenVertexArrays(1, &vao);

    GLuint ibo;
    glGenBuffers(1, &ibo);

    //std::cout << "buffer: " << vbo << std::endl;

    float vertices[12] = {
        -0.8f, 0.2f,
        -0.8f, 0.0f,
        -0.6f, 0.2f,

         //-0.6f, 0.2f,
         //-0.8f, 0.0f,
         -0.6f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    glBindVertexArray(vao);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

    unsigned int shaderProgram = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shaderProgram);

    GlCall(unsigned int fragColorUnId = glGetUniformLocation(shaderProgram, "u_Color"));
    GlCall(glUniform4f(fragColorUnId, 0.2, 0.8, 0.3, 1.0));

    GlCall(unsigned int vertexPosUnId = glGetUniformLocation(shaderProgram, "u_Position"));
   

    // draw in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw back in fill
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

    
    bool running = true;

    float right = 0;

    float time = 0;

    while (!glfwWindowShouldClose(window)) {
        time = glfwGetTime();

        glfwPollEvents();

        // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow(); // Show demo window! :)


        ImGui::SetNextWindowSize(ImVec2(100, 100));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        ImGui::Begin("window2");
        
        ImGui::End();

        GlCall(glUniform4f(vertexPosUnId, right, 0.5, 0.0, 1.0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GlCall(glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, (const void*)0));

        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)


        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}