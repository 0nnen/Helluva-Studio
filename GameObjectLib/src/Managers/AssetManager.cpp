#include "Managers/AssetManager.h"

std::map<std::string, sf::Texture*> AssetManager::assets;

 void AssetManager::AddAsset(std::string _key, std::string _fileName)
{
	 sf::Texture* texture = new sf::Texture();
	if (AssetManager::assets.find(_key) == AssetManager::assets.end()) 
	{
		AssetManager::assets.insert(std::make_pair(_key, texture));
		if (!AssetManager::assets.at(_key)->loadFromFile(_fileName)) 
		{
			std::cout << "asset introuvable" << std::endl;
		}
	}
}

 sf::Texture* AssetManager::GetAsset(std::string _key)
 {
	 if (AssetManager::assets.find(_key) != AssetManager::assets.end()) 
	 {
		 return AssetManager::assets.at(_key);
	 }
	 return nullptr;
 }


void AssetManager::DeleteAsset(std::string _key)
 {
	 if (AssetManager::assets.find(_key) != AssetManager::assets.end())
	 {
		 delete AssetManager::assets.at(_key);
		 AssetManager::assets.erase(_key);
	 }

 }