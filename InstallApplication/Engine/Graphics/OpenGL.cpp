
#include <iostream>
#include <map>
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection

#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/OpenGlErrorHandler.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) glError->ClearError();\
    x;\
    ASSERT(glError->LogError(#x, __FILE__, __LINE__))

class Layer {};

/*
int RunApp() {
    std::vector<Layer> layers;

    layers.push_back(new WindowLayer());
    layers.push_back(new GUILayer());
    layers.push_back(new OpenGLLessonsLayer());
    layers.push_back(new EntityComponentLayer());

    for (Layer layer : layers) {
        if (!layer->Initialize()) {
            std::cout << "Layer fail to initialize: " << layer->GetName() << std::endl;
            return 1;
        }
    }

    for (Layer layer : layers) {
        layer->Run();
    }

    for (Layer layer : layers) {
        layer->Finish();
    }

    return 0;
}*/

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


void RunOpenGlApp() {
    GlfwWindowSystem* windowSystem = new GlfwWindowSystem();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(windowSystem->GetWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    if (!ImGui_ImplOpenGL3_Init()) {
        std::cout << "ImGui OpenGL Backend initialization failed!" << std::endl;
    }

    OpenGlErrorHandler* glError = new OpenGlErrorHandler();

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

    //ImVec4 colors = ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
    float colors[4] = { 0,0,0,0 };

    while (!glfwWindowShouldClose(windowSystem->GetWindow())) {
        time = glfwGetTime();

        glfwPollEvents();

        // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
       // ImGui::ShowDemoWindow(); // Show demo window! :)

        bool my_tool_active = true;
        ImGui::Begin("Scene Tree", &my_tool_active, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) {  }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {  }
                if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::End();

        bool my_tool_active2 = true;
        ImGui::Begin("Game", &my_tool_active2, ImGuiWindowFlags_MenuBar);
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O")) {}
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active2 = false; }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();

        ImGui::Begin("Components");
        ImGui::ColorEdit4("color-edit-1", colors);
            
            ImGui::Begin("window-3");
            ImGui::ColorEdit4("color-edit-2", colors);
            ImGui::End();

        ImGui::End();

        GlCall(glUniform4f(vertexPosUnId, right, 0.5, 0.0, 1.0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GlCall(glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, (const void*)0));

        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)


        glfwSwapBuffers(windowSystem->GetWindow());
    }

    glDeleteProgram(shaderProgram);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete windowSystem;
}