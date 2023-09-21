#include "Testbed/InstallApp.hpp"
//#include "Testbed/Experiment2.hpp"
//#include "Games/Bomberman.hpp"
//#include "Testbed/Fadeout.hpp"

int main()
{
    //Fadeout();
    //Bomberman();
    //Box2dIntegration();
    //RunInstallApp();
    RunOpenGlApp();
    return 0;
}

/*
Ideia for a main game loop structure
while (true)
{
    PollJoypad();
    float dt = g_gameClock.CalculateDeltaTime();
    for (each gameObject) {
        gameObject.Update(dt);
    }

    g_eventSystem.DispatchEvents(dt);
    g_animationEngine.Update(dt);
    g_physicsEngine.Simulate(dt);
    g_collisionEngine.DetectAndResolveCollisions(dt);
    g_audioEngine.Update(dt);
    g_renderingEngine.RenderFrameAndSwapBuffers();
}
*/