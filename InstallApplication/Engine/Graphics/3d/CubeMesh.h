#pragma once

#include <vector>
#include <string>

#include <Engine/Graphics/OpenGlErrorHandler.h>


class CubeMesh
{
public:
	CubeMesh();
	~CubeMesh();

	std::vector<float> GetVertices() const;

	void SetUp();

	void Render(double deltaTime);

private:
	std::vector<float> vertices;
	
	std::string vertexShaderPath;
	std::string fragmentShaderPath;

	unsigned int shaderProgram;

	OpenGlErrorHandler* glError;
};

