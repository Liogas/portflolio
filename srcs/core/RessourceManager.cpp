#include "RessourceManager.hpp"

RessourceManager::RessourceManager(RendererSDL &r):
	_textures(),
	_renderer(r)
{
	std::cout << "Ressource Manager created" << std::endl;
}

RessourceManager::~RessourceManager()
{
	std::cout << "Ressource Manager destroyed" << std::endl;
}

std::shared_ptr<TextureSDL>	&RessourceManager::getTexture(const std::string &path)
{
	if (!this->_textures.contains(path))
		this->_textures[path] = std::make_shared<TextureSDL>(this->_renderer, path);
	return (this->_textures[path]);
}			
