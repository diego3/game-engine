#pragma once
#include <vector>

#include <Engine/Graphics/OpenGlErrorHandler.h>

class Mesh {
public:
	Mesh(float velocity);
	~Mesh();

	void SetUp();

	void Render(double deltaTime);

	void setUniform();
private:
	std::vector<float> vertices;
	std::vector<GLuint> indices;
	OpenGlErrorHandler* glError;

	unsigned int shaderProgram;
	unsigned int vertexPosUnId;
	unsigned int fragColorUnId;

	float right;
	float velocity;
	float timePass;
};