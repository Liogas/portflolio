# include "resources/ResourceManager.hpp"

ResourceManager::ResourceManager(RendererSDL &r):
	_textures(),
	_renderer(r)
{
	std::cout << "Ressource Manager created" << std::endl;
}

ResourceManager::~ResourceManager()
{
	for (auto &pair : this->_fonts)
		TTF_CloseFont(pair.second);
	std::cout << "Ressource Manager destroyed" << std::endl;
}

std::shared_ptr<TextureSDL>	&ResourceManager::getTexture(const std::string &path)
{
	std::filesystem::path folder = this->getTexturesPath();
	std::filesystem::path fullPath = folder / path;
	std::string key = fullPath.string();
	if (!this->_textures.contains(key))
		this->_textures[key] = std::make_shared<TextureSDL>(this->_renderer, key);
	return (this->_textures[key]);
}

TTF_Font	*ResourceManager::getFont(const std::string &name, int size)
{
	std::string	key = name + "_" + std::to_string(size);
	auto it = this->_fonts.find(key);
	if (it != this->_fonts.end())
		return (it->second);
	std::filesystem::path path = getFontsPath();
	std::string	fullPath = (path / name).string();
	TTF_Font *font = TTF_OpenFont(fullPath.c_str(), size);
	if (!font)
		throw (std::runtime_error(TTF_GetError()));
	this->_fonts[key] = font;
	return (font);
}

std::string	ResourceManager::getAssetsPath()
{
	static std::string path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "assets"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error(
					"ERROR ResourceManager::getAssetsPath : assets folder not found"
				);
		}
		path = (exePath / "assets").string() + "/";
	}
	return (path);
}

std::string	ResourceManager::getFontsPath()
{
	static std::string path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "assets"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error(
					"ERROR ResourceManager::getFontsPath : assets folder not found"
				);
		}
		path = (exePath / "assets/fonts").string() + "/";
	}
	return (path);
}

std::string	ResourceManager::getTexturesPath()
{
	static std::string path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "assets"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error(
					"ERROR ResourceManager::getTexturesPath : textures folder not found"
				);
		}
		path = (exePath / "assets/textures").string() + "/";
	}
	return (path);
}
