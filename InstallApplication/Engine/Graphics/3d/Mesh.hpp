#pragma once
#include <vector>

#include <Engine/Graphics/OpenGlErrorHandler.h>

// https://free3d.com/3d-model/intergalactic-spaceship-in-blender-28-eevee-394046.html
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/

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