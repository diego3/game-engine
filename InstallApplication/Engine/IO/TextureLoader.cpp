#include "TextureLoader.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <Engine/Graphics/GlfwWindowSystem.h>

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{

}

Texture* TextureLoader::Load(std::string path)
{
	int numberOfChannels;
	int width;
	int height;
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &numberOfChannels, 0);
	const char *failure = stbi_failure_reason();
	if (failure) {
		std::cout << "Fail to load texture file [ " << path << "] error:" << failure << std::endl;
		return nullptr;
	}

	stbi_set_flip_vertically_on_load(true);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture* text = new Texture(texture, data, width, height);

	// free only after send texture data to GPU
	stbi_image_free(data);
	
	return text;
}
