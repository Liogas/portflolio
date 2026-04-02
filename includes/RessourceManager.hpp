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
		[[nodiscard]] std::shared_ptr<TextureSDL>	&getTexture(const std::string &);
	private:
		std::unordered_map<std::string, std::shared_ptr<TextureSDL>> _textures;
		RendererSDL									&_renderer;
};

#endif