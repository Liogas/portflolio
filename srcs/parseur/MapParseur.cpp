#include "MapParseur.hpp"

MapParseur::MapParseur(const std::string &path):
	_path(path),
	_map(std::make_unique<TileMap>())
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

std::unique_ptr<TileMap> MapParseur::start(
	RessourceManager &ressources,
	Scene *scene
)
{
	std::ifstream file(this->_path);
	if (!file)
		throw std::runtime_error("Can't open file");

	nlohmann::json	data;
	file >> data;
		
	this->_map->setWidth(data["width"]);
	this->_map->setHeight(data["height"]);
	this->_map->setTileSize(data["tileheight"]);

	this->parseTilesets(data, ressources);
	this->parseLayers(data, scene);
	
	// throw std::runtime_error("WIP");
	return (std::move(this->_map));
}

void	MapParseur::parseTilesets(nlohmann::json &data, RessourceManager &ressources)
{
	for (auto &l : data["tilesets"])
	{
		t_tileset t;
		t.firstgid = l["firstgid"];
		std::cout << "file xml -> " << l["source"].get<std::string>().c_str() << std::endl;
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(l["source"].get<std::string>().c_str()) != tinyxml2::XML_SUCCESS)
			throw std::runtime_error("Can't open XML File");
		tinyxml2::XMLElement *tileset = doc.FirstChildElement("tileset");
		t.tileHeight = tileset->IntAttribute("tileheight");
		t.tileWidth = tileset->IntAttribute("tilewidth");
		t.columns = tileset->IntAttribute("columns");

		tinyxml2::XMLElement *image = tileset->FirstChildElement("image");

		std::filesystem::path tsxPath(l["source"].get<std::string>().c_str());
		std::filesystem::path tsxDir = tsxPath.parent_path();
		std::filesystem::path fullPath = tsxDir / image->Attribute("source");
		t.pathfile = fullPath.string();

		std::cout << "Tentative d'ouverture de -> " << t.pathfile << std::endl;
		t.sprite = std::make_shared<Sprite>(ressources.getTexture(t.pathfile), t.tileWidth, t.tileHeight, false);
		this->_map->addTileset(t);
	}
}

void	MapParseur::parseLayers(nlohmann::json &data, Scene *scene)
{
	for (auto &l : data["layers"])
	{
		if (l["type"] == "objectgroup")
		{
			this->parseObjects(l, scene);
			continue ;
		}
		t_layer	t;
		t.data = l["data"].get<std::vector<int>>();
		t.name = l["name"];
		t.visible = l["visible"];
		if (t.name == "Passages")
			this->_map->setCollisionLayer(t);
		else
			this->_map->addLayer(t);
	}
	this->_map->printLayers();
}

void	MapParseur::parseObjects(nlohmann::json &layer, Scene *scene)
{
	for (auto &obj : layer["objects"])
	{
		if (obj["type"] == "computer")
		{
			auto e = std::make_unique<Computer>(
				obj["x"],
				obj["y"],
				obj["width"],
				obj["height"],
				obj["properties"][0]["value"]
			);
			scene->addEntity(std::move(e));
		}
	}
}