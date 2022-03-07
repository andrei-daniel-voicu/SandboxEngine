#pragma once
struct ShaderResource
{
	char* path;
	char* name;
};
struct TextureResource
{
	int id;
	char* path;
	char* name;
	char* type;
	char* min_filter;
	char* mag_filter;
	char* wrap_s;
	char* wrap_t;


};
struct ModelResource
{
	char* name;
	char* path;
};
struct MaterialResource
{
	int id;
	int shaderId;
	int textureId;
};