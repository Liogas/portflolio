#ifndef RESSOURCEMANAGER_HPP
# define RESSOURCEMANAGER_HPP

# include <iostream>
# include <unordered_map>
# include <memory>

# include "TextureSDL.hpp"

class RessourceManager
{
	public:
		RessourceManager(RendererSDL &);
		~RessourceManager();
		TextureSDL	&getTexture(const std::string &);
	private:
		std::unordered_map<std::string, std::unique_ptr<TextureSDL>> _textures;
		RendererSDL									&_renderer;
};

#endif