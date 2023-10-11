#pragma once

#include <vector>
#include <memory>
#include <Engine/Graphics/ISceneNode.h>
#include <Engine/Graphics/3d/Camera.hpp>
#include <Engine/EventSystem/GameEvent.hpp>

class SceneManager
{
public:
	SceneManager(Camera* camera);

	void Render(double deltaTime);

	Camera* GetMainCamera();

	void AddNode(ISceneNode* node);

	void OnNewRender(std::shared_ptr<IEvent> event);

private:
	std::vector<ISceneNode*> m_pNodes;

	Camera* m_pMainCamera;
};

