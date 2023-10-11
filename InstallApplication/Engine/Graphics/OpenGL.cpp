
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <stdio.h>

#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Initializers/ConsoleInitializer.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> // translate, rotate, scale
#include <glm/ext/matrix_clip_space.hpp> // projection

#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/ui/UIManager.h>
#include <Engine/Graphics/3d/Mesh.hpp>
#include <Engine/Graphics/3d/CubeMesh.h>
#include <Engine/Graphics/3d/Camera.hpp>

#include <Engine/EventSystem/EventManager.hpp>
#include <Engine/Graphics/SceneManager.h>
#include <Engine/Scripting/ScriptSystem.h>
#include <Engine/Ecs/ActorFactory.h>


// TODO make this an Application class
// TODO handle windows events like user minimize, user tab to other apps: might Glew handles this events
void RunOpenGlApp() {
    // Logger initialization: tail game-engine-log.txt -f
    //plog::init(plog::verbose, "game-engine-log.txt", 10000, 1); FileInitializer
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
    PLOG_DEBUG << "Log initialization success";

    GlfwWindowSystem* windowSystem = new GlfwWindowSystem();
    
    EventManager::Get();

    UIManager* uiManager = new UIManager();
    uiManager->Initialize(windowSystem);

    Camera* mainCamera = new Camera();
    SceneManager* sceneManager = new SceneManager(mainCamera);

    ScriptSystem* scriptSystem = new ScriptSystem();
    scriptSystem->Initialize();

    ActorFactory* actorFactory = new ActorFactory();
    
   
    // TODO load compos from xml !!!
    CubeMesh* cube1 = new CubeMesh();
    cube1->SetUp();
    cube1->SetRotation(glm::vec3(0.5, 1.f, 0));
    cube1->SetPosition(glm::vec3(2.4f, 0, 0));
    cube1->SetScale(glm::vec3(0.2, 0.5, 0.2));
    sceneManager->AddNode(cube1);


    CubeMesh* cube2 = new CubeMesh();
    cube2->SetUp();
    cube2->SetRotation(glm::vec3(0, 1.f, 2.4f));
    cube2->SetPosition(glm::vec3(0, 0, 0));
    cube2->SetScale(glm::vec3(0.5, 0.5, 0.5));
    sceneManager->AddNode(cube2);

    // TODO add event manager !!!
    EventListener sceneListener = std::bind(&SceneManager::OnNewRender, sceneManager, std::placeholders::_1);
    EventManager::Get()->AddListener(sceneListener, NewRenderEvent::EventName);

    // draw in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // draw back in fill
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 

    double deltaTime = 0;
    double elapsedFrameTime = 0;

    while (!glfwWindowShouldClose(windowSystem->GetWindow())) {
        deltaTime = glfwGetTime();

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        uiManager->Render(deltaTime);
        sceneManager->Render(deltaTime);

        
        glfwSwapBuffers(windowSystem->GetWindow());

        elapsedFrameTime = glfwGetTime() - deltaTime;
    }

    
    delete actorFactory;
    delete scriptSystem;
    delete sceneManager;
    delete mainCamera;

    uiManager->Destroy();

    delete windowSystem;
}