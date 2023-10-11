#include <iostream>
#include <thread>

#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

UIManager::UIManager()
{
    this->colors[0] = 0;
    this->colors[1] = 0;
    this->colors[2] = 0;
    this->colors[3] = 0;
    this->my_tool_active = true;
    this->active = true;
}

void UIManager::Initialize(GlfwWindowSystem* windowSystem)
{
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
        this->active = false;
    }
}

void UIManager::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::Render(float deltaMilis)
{
    if (!this->active)
    {
        return;
    }
    // (Your code calls glfwPollEvents())
        // ...
        // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    // ImGui::ShowDemoWindow(); // Show demo window! :)

    ImGui::Begin("Scene Tree", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..Sleep", "Ctrl+O")) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
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

   // char buf[80];
   // sprintf_s(buf, "frame elapsed time: %.4f", elapsedFrameTime);
    //ImGui::Text(buf);

    ImGui::Begin("window-3");
    ImGui::ColorEdit4("color-edit-2", colors);
    ImGui::End();

    ImGui::End();


    // Rendering
    // (Your code clears your framebuffer, renders your other stuff etc.)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // (Your code calls glfwSwapBuffers() etc.)
}

void UIManager::SetActive(bool active)
{
    this->active = active;
}
