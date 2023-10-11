#include <memory>
#include "SceneManager.h"
#include "Engine/EventSystem/GameEvent.hpp"
#include <plog/Log.h>

SceneManager::SceneManager(Camera* camera)
{
	this->m_pMainCamera = camera;
}

void SceneManager::Render(double deltaTime)
{
	for(ISceneNode* node : this->m_pNodes)
	{
		node->VRender(m_pMainCamera, deltaTime);
	}
}

Camera* SceneManager::GetMainCamera()
{
	return this->m_pMainCamera;
}

void SceneManager::AddNode(ISceneNode* node)
{
	this->m_pNodes.push_back(node);
}

void SceneManager::OnNewRender(std::shared_ptr<IEvent> event)
{
	PLOG_DEBUG << "SceneManager::OnNewRender called!!";
	
	if (!event) {
		PLOG_WARNING << "scene manager: new render event is null";
		return;
	}
	
	std::shared_ptr<NewRenderEvent> newRender = std::dynamic_pointer_cast<NewRenderEvent>(event);

	if (!newRender && !newRender->GetData()) {
		PLOG_WARNING << "scene manager: new render event dont have a sceneNode";
		return;
	}

	this->AddNode(newRender->GetData());
}
