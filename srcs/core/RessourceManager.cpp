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

TextureSDL	&RessourceManager::getTexture(const std::string &path)
{
	if (!this->_textures.contains(path))
		this->_textures[path] = std::make_unique<TextureSDL>(this->_renderer, path);
	return (*this->_textures[path]);
}			
