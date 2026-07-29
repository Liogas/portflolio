#ifndef ResourceManager_HPP
# define ResourceManager_HPP

# include <iostream>
# include <unordered_map>
# include <memory>
# include <filesystem>
# include <SDL2/SDL_ttf.h>

# include "TextureSDL.hpp"

enum class TextureFolder
{
	CHARACTER,
	TECHNOLOGIE,
	UI,
	WORLD
};

class ResourceManager
{
	public:
		ResourceManager(RendererSDL &);
		~ResourceManager();
		// GETTER
		[[nodiscard]] std::shared_ptr<TextureSDL>	&getTexture(
			const std::string &,
			TextureFolder
		);
		[[nodiscard]] TTF_Font						*getFont(const std::string &name, int size);
		// METHODS
		std::string	getAssetsPath();
		std::string	getTexturesPath(TextureFolder);
		std::string getFontsPath();
		std::string	getMapsPath();
	private:
		std::unordered_map<std::string, std::shared_ptr<TextureSDL>>	_textures;
		std::unordered_map<std::string, TTF_Font *>						_fonts;
		RendererSDL														&_renderer;
};

#endif