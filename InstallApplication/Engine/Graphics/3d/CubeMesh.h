#pragma once

#include <vector>
#include <string>

#include <Engine/Graphics/OpenGlErrorHandler.h>
#include <Engine/Graphics/ISceneNode.h>
#include <Engine/Graphics/3d/Camera.hpp>

class CubeMesh : public ISceneNode
{
public:
	CubeMesh();
	~CubeMesh();

	std::vector<float> GetVertices() const;

	void SetUp();

	void VRender(Camera* camera, double deltaTime);

	void SetPosition(glm::vec3 pos);
	void SetScale(glm::vec3 pos);
	void SetRotation(glm::vec3 pos);

private:
	std::vector<float> vertices;
	
	std::string vertexShaderPath;
	std::string fragmentShaderPath;

	unsigned int shaderProgram;

	OpenGlErrorHandler* glError;

	Camera* m_pCamera;


	// TODO transform component !!!!
	float rotationAngle;
	glm::vec3 rotation;
	glm::vec3 scaling;
	glm::vec3 position;
};

