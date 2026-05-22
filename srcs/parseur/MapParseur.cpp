#include "MapParseur.hpp"

static void	parseTilesets(TileMap &map, nlohmann::json &data, RessourceManager &ressources)
{
	for (auto &l : data["tilesets"])
	{
		t_tileset t;
		t.firstgid = l["firstgid"];
		std::string tsxRelative = l["source"].get<std::string>();
		std::string tsxFullPath = ressources.getAssetsPath() + tsxRelative;
		std::cout << "file xml -> " << tsxFullPath << std::endl;
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(tsxFullPath.c_str()) != tinyxml2::XML_SUCCESS)
			throw std::runtime_error("ERROR TileMap::parseTilesets -> Opening of XML File filed");
		tinyxml2::XMLElement *tileset = doc.FirstChildElement("tileset");
		t.tileHeight = tileset->IntAttribute("tileheight");
		t.tileWidth = tileset->IntAttribute("tilewidth");
		t.columns = tileset->IntAttribute("columns");
		tinyxml2::XMLElement *image = tileset->FirstChildElement("image");
		std::filesystem::path tsxPath(tsxFullPath);
		std::filesystem::path tsxDir = tsxPath.parent_path();
		std::filesystem::path fullPath = tsxDir / image->Attribute("source");
		t.pathfile = fullPath.string();
		t.sprite = std::make_shared<Sprite>(
			ressources.getTexture(t.pathfile),
			t.tileWidth,
			t.tileHeight,
			false
		);
		map.addTileset(t);
	}
}

static void	parseObjects(nlohmann::json &layer, entt::registry &registry)
{
	for (auto &obj : layer["objects"])
	{
		if (obj["type"] == "computer")
			ComputerFactories::create(
				registry,
				obj["x"],
				obj["y"],
				obj["width"],
				obj["height"],
				obj["properties"][0]["value"]
			);
	}
}

static void	parseLayers(TileMap &map, nlohmann::json &data, entt::registry &registry)
{
	for (auto &l : data["layers"])
	{
		if (l["type"] == "objectgroup")
		{
			parseObjects(l, registry);
			continue ;
		}
		t_layer	t;
		t.data = l["data"].get<std::vector<int>>();
		t.name = l["name"];
		t.visible = l["visible"];
		if (t.name == "Passages")
			map.setCollisionLayer(t);
		else
			map.addLayer(t);
	}
	map.printLayers();
}

std::unique_ptr<TileMap> MapParseur::start(
	const std::string &path,
	World &world
)
{
	std::unique_ptr<TileMap> map = std::make_unique<TileMap>();
	try 
	{
		std::filesystem::path p(path);
		if (p.extension() != ".json" && p.extension() != ".tmj")
			throw std::runtime_error("ERROR MapParseur::start -> Bad extension for " + path);
		if (!std::filesystem::exists(p))
			throw std::runtime_error("ERROR MapParseur::start -> File not found : " + path);
		std::ifstream file(path);
		if (!file)
			throw std::runtime_error("ERROR MapParseur::start -> failed opening : " + path);
		nlohmann::json	data;
		file >> data;

		map->setWidth(data["width"]);
		map->setHeight(data["height"]);
		map->setTileSize(data["tileheight"]);

		parseTilesets(*map, data, world.getRm());
		parseLayers(*map, data, world.getRegistry());
	} catch (const std::exception &e)
	{
		throw (std::runtime_error(e.what()));
	}
	return (map);
}

