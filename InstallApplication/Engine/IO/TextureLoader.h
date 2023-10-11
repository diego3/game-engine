#pragma once

#include <string>

#include <Engine/Graphics/GlfwWindowSystem.h>
#include <Engine/Graphics/2d/Texture.h>

class TextureLoader
{
public:
	TextureLoader();

	~TextureLoader();

	Texture* Load(std::string path);

private:
};

