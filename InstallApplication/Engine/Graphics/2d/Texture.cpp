#include "Texture.h"

Texture::Texture(unsigned int id, unsigned char* data, int width, int height)
{
	this->data = data;
	this->width = width;
	this->height = height;
	this->id = id;
}

Texture::~Texture()
{
}

unsigned char* Texture::GetData()
{
	return this->data;
}

unsigned int Texture::GetId()
{
	return this->id;
}

