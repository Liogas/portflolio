#include "MapParseur.hpp"

MapParseur::MapParseur(const std::string &path):
	_path(path),
	_tilesets(),
	_layers()
{
	std::filesystem::path p(path);
	if (p.extension() != ".json" && p.extension() != ".tmj")
		throw std::runtime_error("Bad extension");
	if (!std::filesystem::exists(p))
		throw std::runtime_error("File not find");
	std::cout << "MapParseur created" << std::endl;
}

MapParseur::~MapParseur()
{
	std::cout << "MapParseur destroyed" << std::endl;
}

TileMap	*MapParseur::start()
{
	std::ifstream file(this->_path);
	if (!file.is_open())
		throw std::runtime_error("Can't open file");

	nlohmann::json	data;
	file >> data;
		
	std::unique_ptr<TileMap> map = std::make_unique<TileMap>(data["width"], data["height"]);
	map->setTileSize(data["tileheight"]);

	this->loadTilesets(data);
	this->loadLayers(data);
	
	file.close();
	throw std::runtime_error("WIP");
}

void	MapParseur::loadTilesets(nlohmann::json &data)
{
	for (auto l : data["tilesets"])
	{
		t_tileset t;
		t.firstgid = l["firstgid"];
		t.pathfile = l["source"];
		this->_tilesets.push_back(t);
	}
}

void	MapParseur::loadLayers(nlohmann::json &data)
{
	for (auto l : data["layers"])
	{
		t_layer	t;
		t.data = l["data"].get<std::vector<int>>();
		t.name = l["name"];
		t.visible = l["visible"];
		this->_layers.push_back(t);
	}
}