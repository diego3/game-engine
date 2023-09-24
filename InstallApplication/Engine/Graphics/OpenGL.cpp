
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <stdio.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection

#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/3d/Mesh.hpp>
#include <Engine/Graphics/3d/CubeMesh.h>


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

    //Mesh* rectangle = new Mesh(0.1f);
    //rectangle->SetUp();

    CubeMesh* cube = new CubeMesh();
    cube->SetUp();

    // draw in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw back in fill
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

    double deltaTime = 0;
    double elapsedFrameTime = 0;

    //ImVec4 colors = ImVec4(0.1f, 0.1f, 0.1f, 0.1f);
    float colors[4] = { 0,0,0,0 };

    while (!glfwWindowShouldClose(windowSystem->GetWindow())) {
        deltaTime = glfwGetTime();

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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
                if (ImGui::MenuItem("Open..Sleep", "Ctrl+O")) { 
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
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
        
        char buf[80];
        sprintf_s(buf, "frame elapsed time: %.4f", elapsedFrameTime);
        ImGui::Text(buf);
            
            ImGui::Begin("window-3");
            ImGui::ColorEdit4("color-edit-2", colors);
            ImGui::End();

        ImGui::End();

       
        // Rendering
        // (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)

        //rectangle->Render(deltaTime);
        cube->Render(deltaTime);

        glfwSwapBuffers(windowSystem->GetWindow());

        elapsedFrameTime = glfwGetTime() - deltaTime;
    }

    //delete rectangle;
    delete cube;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    delete windowSystem;
}