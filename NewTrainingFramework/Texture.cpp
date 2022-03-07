#include "Texture.h"
#include <iostream>
#include "ResourceManager.h"
Texture::Texture ()
{

}
void Texture::Load ()
{
	if (!strcmp (textureResource->type, "2d"))
	{
		type = GL_TEXTURE_2D;
		int width, height, bpp;
		char* image = LoadTGA (textureResource->path, &width, &height, &bpp);
		int color_mode;
		if (bpp == 24)
			color_mode = GL_RGB;
		else color_mode = GL_RGBA;

		glGenTextures (1, &textureBuffer);
		glBindTexture (type, textureBuffer);
		glTexImage2D (type, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);
	}
	else
	{
		type = GL_TEXTURE_CUBE_MAP;
		int width, height, bpp;
		char* image = LoadTGA (textureResource->path, &width, &height, &bpp);
		int color_mode;
		if (bpp == 24)
			color_mode = GL_RGB;
		else color_mode = GL_RGBA;

		glGenTextures (1, &textureBuffer);
		glBindTexture (type, textureBuffer);

		glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);

		image = LoadTGA (ResourceManager::getInstance ()->texturesRes[textureResource->id + 1]->path, &width, &height, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);

		image = LoadTGA (ResourceManager::getInstance ()->texturesRes[textureResource->id + 2]->path, &width, &height, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);

		image = LoadTGA (ResourceManager::getInstance ()->texturesRes[textureResource->id + 2]->path, &width, &height, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);

		image = LoadTGA (ResourceManager::getInstance ()->texturesRes[textureResource->id + 4]->path, &width, &height, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);

		image = LoadTGA (ResourceManager::getInstance ()->texturesRes[textureResource->id + 5]->path, &width, &height, &bpp);
		glTexImage2D (GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, color_mode, width, height, 0, color_mode, GL_UNSIGNED_BYTE, image);
	}
	if (!strcmp (textureResource->min_filter, "LINEAR"))
		glTexParameteri (type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (!strcmp (textureResource->mag_filter, "LINEAR"))
		glTexParameteri (type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (!strcmp (textureResource->wrap_s, "CLAMP_TO_EDGE"))
		glTexParameteri (type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	else if (!strcmp (textureResource->wrap_s, "REPEAT"))
		glTexParameteri (type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	if (!strcmp (textureResource->wrap_t, "CLAMP_TO_EDGE"))
		glTexParameteri (type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	else if (!strcmp (textureResource->wrap_t, "REPEAT"))
		glTexParameteri (type, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture (type, 0);
}
Texture::~Texture ()
{

}