#include "ResourceManager.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager* ResourceManager::getInstance ()
{
	if (instance == nullptr)
		instance = new ResourceManager ();
	return instance;
}
ResourceManager::ResourceManager ()
{

}
void ResourceManager::setReadDocument (const char* path)
{
	doc.xmlLoad (path);
}
void ResourceManager::loadResources (const xml_node<>* node)
{
	xml_attribute<>* pAttr;
	std::string sir;
	for (pAttr = node->first_attribute (); pAttr; pAttr = pAttr->next_attribute ())
	{
		sir = pAttr->name ();
		switch (filetype)
		{
		case _models:
			if (sir == "id")
			{
				modelsRes[std::stoi (pAttr->value ())] = new ModelResource;

			}
			else if (sir == "name")
			{
				modelsRes[modelsRes.rbegin ()->first]->name = pAttr->value ();

			}
			else if (sir == "path")
			{
				modelsRes[modelsRes.rbegin ()->first]->path = pAttr->value ();

			}
			break;
		case _textures:
			if (sir == "id")
			{
				texturesRes[std::stoi (pAttr->value ())] = new TextureResource;
				texturesRes[texturesRes.rbegin ()->first]->id = std::stoi (pAttr->value ());
			}
			else if (sir == "type")
			{
				texturesRes[texturesRes.rbegin ()->first]->type = pAttr->value ();
			}
			else if (sir == "name")
			{
				texturesRes[texturesRes.rbegin ()->first]->name = pAttr->value ();

			}
			else if (sir == "path")
			{
				texturesRes[texturesRes.rbegin ()->first]->path = pAttr->value ();

			}
			else if (sir == "min_filter")
			{
				texturesRes[texturesRes.rbegin ()->first]->min_filter = pAttr->value ();
			}
			else if (sir == "mag_filter")
			{
				texturesRes[texturesRes.rbegin ()->first]->mag_filter = pAttr->value ();
			}
			else if (sir == "wrap_s")
			{
				texturesRes[texturesRes.rbegin ()->first]->wrap_s = pAttr->value ();
			}
			else if (sir == "wrap_t")
			{
				texturesRes[texturesRes.rbegin ()->first]->wrap_t = pAttr->value ();
			}
			break;
		case _shaders:
			if (sir == "id")
			{
				shadersRes[std::stoi (pAttr->value ())] = new ShaderResource;
			}
			else if (sir == "name")
			{
				shadersRes[shadersRes.rbegin ()->first]->name = pAttr->value ();

			}
			else if (sir == "path")
			{
				shadersRes[shadersRes.rbegin ()->first]->path = pAttr->value ();

			}
			break;
		case _materials:
			if (sir == "id")
			{
				materialsRes[std::stoi (pAttr->value ())] = new MaterialResource;
			}
			else if (sir == "shaderId")
			{
				materialsRes[materialsRes.rbegin ()->first]->shaderId = std::stoi (pAttr->value ());
			}
			break;
		}


	}
	for (xml_node<>* n = node->first_node (); n; n = n->next_sibling ())
	{

		if (!strcmp (n->name (), "models"))
		{
			filetype = _models;
		}
		else if (!strcmp (n->name (), "textures"))
		{
			filetype = _textures;
		}
		else if (!strcmp (n->name (), "shaders"))
		{
			filetype = _shaders;
		}
		else if (!strcmp (n->name (), "materials"))
		{
			filetype = _materials;
		}
		loadResources (n);
	}

}
Model* ResourceManager::loadModel (const unsigned int modelId)
{
	std::vector<Model*>::iterator ptr;
	for (ptr = models.begin (); ptr != models.end (); ptr++)
	{
		if ((*ptr)->modelResource == modelsRes[modelId])
			return (*ptr);
	}
	models.push_back (new Model);
	models.back ()->modelResource = modelsRes[modelId];
	models.back ()->Load ();
	return models.back ();
}
Material* ResourceManager::loadMaterial (const unsigned int materialId)
{
	std::vector<Material*>::iterator ptr;
	for (ptr = materials.begin (); ptr != materials.end (); ptr++)
	{
		if ((*ptr)->materialResource == materialsRes[materialId])
			return (*ptr);
	}
	materials.push_back (new Material);
	materials.back ()->materialResource = materialsRes[materialId];
	return materials.back ();
}
Texture* ResourceManager::loadTexture (const unsigned int textureId)
{
	std::vector<Texture*>::iterator ptr;
	for (ptr = textures.begin (); ptr < textures.end (); ptr++)
	{
		if ((*ptr)->textureResource == texturesRes[textureId])
			return (*ptr);
	}
	textures.push_back (new Texture);
	textures.back ()->textureResource = texturesRes[textureId];
	textures.back ()->Load ();
	return textures.back ();
}
Shader* ResourceManager::loadShader (const unsigned int shaderIdVS, const unsigned int shaderIdFS)
{
	std::vector<Shader*>::iterator ptr;
	for (ptr = shaders.begin (); ptr < shaders.end (); ptr++)
	{
		if ((*ptr)->shaderResourceVS == shadersRes[shaderIdVS] && (*ptr)->shaderResourceFS == shadersRes[shaderIdFS])
			return (*ptr);
	}
	shaders.push_back (new Shader);
	shaders.back ()->shaderResourceVS = shadersRes[shaderIdVS];
	shaders.back ()->shaderResourceFS = shadersRes[shaderIdFS];
	shaders.back ()->Load ();
	return shaders.back ();
}
void ResourceManager::freeResources ()
{


}
ResourceManager::~ResourceManager ()
{

}