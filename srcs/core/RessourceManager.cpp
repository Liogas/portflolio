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
	std::filesystem::path folder = this->getTexturesPath();
	std::filesystem::path fullPath = folder / path;
	std::string key = fullPath.string();
	if (!this->_textures.contains(key))
		this->_textures[key] = std::make_shared<TextureSDL>(this->_renderer, key);
	return (this->_textures[key]);
}

std::string	RessourceManager::getAssetsPath()
{
	static std::string path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "assets"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error("assets folder not found");
		}
		path = (exePath / "assets").string() + "/";
	}
	return (path);
}

std::string	RessourceManager::getTexturesPath()
{
	static std::string path;

	if (path.empty())
	{
		auto exePath = std::filesystem::current_path();
		while (!std::filesystem::exists(exePath / "assets"))
		{
			exePath = exePath.parent_path();
			if (exePath == exePath.root_path())
				throw std::runtime_error("textures folder not found");
		}
		path = (exePath / "assets/textures").string() + "/";
	}
	return (path);
}
