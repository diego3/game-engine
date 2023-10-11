#pragma once



class Texture
{
public:
	Texture(unsigned int id, unsigned char* data, int width, int height);
	
	~Texture();

	unsigned char* GetData();

	unsigned int GetId();
private:
	unsigned int id;

	unsigned char* data;
	
	int width;

	int height;
};

