#pragma once
#include <map>
#include <string>
#include <vector>
#include "resources.h"
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"
#include "xml_file.h"

class ResourceManager
{
private:
	static ResourceManager* instance;
	ResourceManager ();
public:
	void Init () {};
	static ResourceManager* getInstance ();
	void setReadDocument (const char*);
	void loadResources (const xml_node<>*);
	void freeResources ();
	~ResourceManager ();
	enum
	{
		_models,
		_textures,
		_shaders,
		_materials,

	}filetype;
	std::map<unsigned int, ShaderResource*> shadersRes;
	std::map<unsigned int, TextureResource*> texturesRes;
	std::map<unsigned int, ModelResource*> modelsRes;
	std::map<unsigned int, MaterialResource*> materialsRes;
	std::vector<Shader*> shaders;
	std::vector<Model*> models;
	std::vector<Texture*> textures;
	std::vector<Material*> materials;
	Texture* loadTexture (const unsigned int);
	Shader* loadShader (const unsigned int,const unsigned int);
	Model* loadModel (const unsigned int);
	Material* loadMaterial (const unsigned int);
	xml_file doc;	
};

