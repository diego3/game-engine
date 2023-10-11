#include <memory>
#include "BaseRenderComponent.h"
#include <glm/glm.hpp>
#include <plog/Log.h>

#include <Engine/Graphics/3d/CubeMesh.h>
#include <Engine/EventSystem/EventManager.hpp>
#include <Engine/EventSystem/GameEvent.hpp>

bool BaseRenderComponent::VInit(tinyxml2::XMLNode* node)
{
	tinyxml2::XMLElement* renderEl = node->FirstChildElement(this->VGetComponentName().c_str());
	if (!renderEl) {
		PLOG_WARNING << "BaseRenderComponent Init failure. Render xml node not found for actorId: " << m_owner->GetId();
		return false;
	}

	tinyxml2::XMLElement* colorEl = renderEl->FirstChildElement("Color");
	if (colorEl) {
		float r = colorEl->FindAttribute("r")->FloatValue();
		float g = colorEl->FindAttribute("g")->FloatValue();
		float b = colorEl->FindAttribute("b")->FloatValue();
		float a = colorEl->FindAttribute("a")->FloatValue();
		m_color = glm::vec4(r, g, b, a);
	}

	// decidir se existira uma classe render para cada geometria

	CubeMesh* cube = new CubeMesh();
	std::shared_ptr<NewRenderEvent> event = std::make_shared<NewRenderEvent>(cube);
	EventManager::Get()->TriggerEvent(event);
	
	return true;
}

std::string BaseRenderComponent::VGetComponentName()
{
	return "BaseRenderComponent";
};

void BaseRenderComponent::VUpdate(float deltaTime)
{

};

void BaseRenderComponent::PosInit() {
	// chama um metodo virtual para criar um SceneNode
	// e dispara um evento (NEW_RENDER_COMPONENT) com o actorId e o sceneNode

	// Carrega o arquivo do level
	// ActorFactory criar o ator e os comps
	// ActorFactory cria o render component
	// O render component cria o scene node para o ator
	// O render dispara o evento de New_Render_Component passando o SceneNode
	// 
	// SceneManager consome esse evento adicionando o novo node como um filho 
	// 
	// HumanView
	//   Scene 
	//     SceneNodes
	//
	//

};