#ifndef RESSOURCEMANAGER_HPP
# define RESSOURCEMANAGER_HPP

# include <iostream>
# include <unordered_map>
# include <memory>
# include <filesystem>

# include "TextureSDL.hpp"

class RessourceManager
{
	public:
		RessourceManager(RendererSDL &);
		~RessourceManager();
		// GETTER
		[[nodiscard]] std::shared_ptr<TextureSDL>	&getTexture(const std::string &);
		// METHODS
		std::string	getAssetsPath();
		std::string	getTexturesPath();
	private:
		std::unordered_map<std::string, std::shared_ptr<TextureSDL>>	_textures;
		RendererSDL														&_renderer;
};

#endif