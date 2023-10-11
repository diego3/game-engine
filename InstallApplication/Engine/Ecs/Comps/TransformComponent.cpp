#include "TransformComponent.h"

#include <glm/glm.hpp>

bool TransformComponent::VInit(tinyxml2::XMLNode* node)
{
    tinyxml2::XMLElement* position = node->FirstChildElement("Position");
    if (position) {
        float px = position->FindAttribute("x")->FloatValue();
        float py = position->FindAttribute("y")->FloatValue();
        float pz = position->FindAttribute("z")->FloatValue();
        m_position = glm::vec3(px, py, pz);
    }

    tinyxml2::XMLElement* rotation = node->FirstChildElement("Rotation");
    if (rotation) {
        float rx = rotation->FindAttribute("x")->FloatValue();
        float ry = rotation->FindAttribute("y")->FloatValue();
        float rz = rotation->FindAttribute("z")->FloatValue();
        m_rotation = glm::vec3(rx, ry, rz);
    }

    tinyxml2::XMLElement* scale = node->FirstChildElement("Scale");
    m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (scale) {
        float sx = scale->FindAttribute("x")->FloatValue();
        float sy = scale->FindAttribute("y")->FloatValue();
        float sz = scale->FindAttribute("z")->FloatValue();
        m_scale = glm::vec3(sx, sy, sz);
    }


    return true;
}

std::string TransformComponent::VGetComponentName()
{
    return "TransformComponent";
}

void TransformComponent::VUpdate(float deltaTime)
{
}

void TransformComponent::PosInit()
{
}

glm::vec3 TransformComponent::GetPosition()
{
    return this->m_position;
}

glm::vec3 TransformComponent::GetRotation()
{
    return this->m_rotation;
}

glm::vec3 TransformComponent::GetScale()
{
    return this->m_scale;
}

glm::mat4 TransformComponent::GetTransform()
{
    // TODO make R * S * T
    return this->m_transform;
}
