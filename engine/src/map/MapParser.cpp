#include "MapParser.hpp"

// --- Utilitaires proprietes ---

static std::string getPropertyStr(const nlohmann::json &obj, const std::string &name)
{
    if (!obj.contains("properties"))
        return ("");
    for (const auto &prop : obj["properties"])
        if (prop["name"] == name)
            return (prop["value"].is_string()
                ? prop["value"].get<std::string>()
                : prop["value"].dump()); // fallback int/bool -> string
    return ("");
}

static int getPropertyInt(const nlohmann::json &obj, const std::string &name, int def = 0)
{
    if (!obj.contains("properties"))
        return (def);
    for (const auto &prop : obj["properties"])
        if (prop["name"] == name && prop["value"].is_number())
            return (prop["value"].get<int>());
    return (def);
}

static bool getPropertyBool(const nlohmann::json &obj, const std::string &name, bool def = false)
{
    if (!obj.contains("properties"))
        return (def);
    for (const auto &prop : obj["properties"])
        if (prop["name"] == name && prop["value"].is_boolean())
            return (prop["value"].get<bool>());
    return (def);
}

// --- Parsing des tilesets (inchange) ---

static void parseTilesets(TileMap &map, nlohmann::json &data, ResourceManager &ressources)
{
    try
    {
        for (auto &l : data["tilesets"])
        {
            t_tileset t;
            t.firstgid = l["firstgid"];
            std::string tsxRelative = l["source"].get<std::string>();
            std::filesystem::path mapPath = ressources.getMapsPath();
            std::filesystem::path tsxPath = mapPath / tsxRelative;
            tsxPath = tsxPath.lexically_normal();

            tinyxml2::XMLDocument doc;
            if (doc.LoadFile(tsxPath.c_str()) != tinyxml2::XML_SUCCESS)
                throw std::runtime_error("ERROR parseTilesets -> " + tsxPath.string());

            tinyxml2::XMLElement *tileset = doc.FirstChildElement("tileset");
            t.tileHeight = tileset->IntAttribute("tileheight");
            t.tileWidth  = tileset->IntAttribute("tilewidth");
            t.columns    = tileset->IntAttribute("columns");

            tinyxml2::XMLElement *image = tileset->FirstChildElement("image");
            std::filesystem::path tsxDir = std::filesystem::path(tsxPath).parent_path();
            t.pathfile = (tsxDir / image->Attribute("source")).string();
            t.sprite = std::make_shared<Sprite>(
                ressources.getTexture(t.pathfile, TextureFolder::WORLD),
                t.tileWidth, t.tileHeight, false
            );
            for (
                tinyxml2::XMLElement *tile = tileset->FirstChildElement("tile");
                tile != nullptr;
                tile = tile->NextSiblingElement("tile")
            )
            {
                int localId = tile->IntAttribute("id");
                tinyxml2::XMLElement *og = tile->FirstChildElement("objectgroup");
                if (!og) continue ;
                for (
                    tinyxml2::XMLElement *obj = og->FirstChildElement("object");
                    obj != nullptr;
                    obj = obj->NextSiblingElement("object")
                )
                {
                    CollisionShape  shape;
                    if (auto *poly = obj->FirstChildElement("polygon"))
                    {
                        shape.type = CollisionShapeType::Polygon;
                        float ox = obj->FloatAttribute("x");
                        float oy = obj->FloatAttribute("y");
                        std::string points = poly->Attribute("points");
                        if (points.empty())
                            continue ;
                        std::stringstream ss(points);
                        std::string pair;
                        while (std::getline(ss, pair, ' '))
                        {
                            float px, py;
                            if (sscanf(pair.c_str(), "%f,%f", &px, &py) == 2)
                            shape.polygon.push_back({
                                (int)(ox + px),
                                (int)(oy + py)
                            });
                        }
                    }
                    else
                    {
                        shape.type = CollisionShapeType::Rect;
                        shape.rect = {
                            (int)obj->FloatAttribute("x"),
                            (int)obj->FloatAttribute("y"),
                            (int)obj->FloatAttribute("width"),
                            (int)obj->FloatAttribute("height")
                        };
                    }
                    shape.convex = CollisionUtils::isConvex(shape.polygon);
                    if (!shape.convex)
                        shape.triangles = CollisionUtils::triangulate(shape.polygon);
                    t.collisions[localId].push_back(shape);
                }
            }
			map.addTileset(t);
        }
    } catch (const std::exception &e) {
        throw std::runtime_error(std::string("parseTilesets: ") + e.what());
    }
}

// --- Parsing des objets par layer ---

static void parseEntities(const nlohmann::json &layer, entt::registry &registry)
{
    for (const auto &obj : layer["objects"])
    {
        std::string listen = getPropertyStr(obj, "listen");
        if (listen.empty())
            continue;

        PylonFactories::create(
            registry,
            listen,
            obj["x"].get<float>(),
            obj["y"].get<float>(),
            obj["width"].get<int>(),
            obj["height"].get<int>()
        );
    }
}

static void parseTriggers(const nlohmann::json &layer, entt::registry &registry)
{
    // Proprietes du layer -> valeurs par defaut pour tous les objets du layer
    std::string defaultEmit = getPropertyStr(layer, "emit");
    bool        defaultOnce = getPropertyBool(layer, "once", false);
    int         defaultDur  = getPropertyInt(layer, "duration", 0);

    for (const auto &obj : layer["objects"])
    {
        std::string id        = getPropertyStr(obj, "id");
        std::string animation = getPropertyStr(obj, "animation");
        int         timer     = getPropertyInt(obj, "timer", defaultDur);

        // Un objet sans id est ignore (pas un trigger valide)
        if (id.empty())
            continue;

        TriggerFactories::create(
            registry,
            defaultEmit,    // l'event a emettre vient du layer
            id,             // le payload vient de l'objet
            animation,
            obj["x"].get<float>(),
            obj["y"].get<float>(),
            obj["width"].get<int>(),
            obj["height"].get<int>(),
            (float)timer,
            defaultOnce
        );
    }
}

static void parseObjectLayer(const nlohmann::json &layer, entt::registry &registry)
{
    std::string name = layer["name"].get<std::string>();

    if (name == "Entities")
        parseEntities(layer, registry);
    else if (name == "Triggers")
        parseTriggers(layer, registry);
    // Ajoute d'autres layers d'objets ici selon les besoins
}

// --- Parsing des layers (recursif pour les groupes) ---

static void parseLayersRecursive(TileMap &map, const nlohmann::json &layers, entt::registry &registry)
{
    for (const auto &l : layers)
    {
        std::string type = l["type"].get<std::string>();

        if (type == "group")
        {
            // Descend dans le groupe recursivement
            parseLayersRecursive(map, l["layers"], registry);
        }
        else if (type == "objectgroup")
        {
            parseObjectLayer(l, registry);
        }
        else if (type == "tilelayer")
        {
            t_layer t;
            t.data    = l["data"].get<std::vector<int>>();
            t.name    = l["name"].get<std::string>();
            t.visible = l["visible"].get<bool>();

            // renderPass depuis les proprietes du layer
            std::string renderPass = getPropertyStr(l, "renderPass");
            if (!renderPass.empty())
                t.renderPass = renderPass; // assure-toi que t_layer a ce champ

            if (t.name == "Passages")
                map.setCollisionLayer(t);
            else
                map.addLayer(t);
        }
    }
}

// --- Point d'entree ---

std::unique_ptr<TileMap> MapParser::start(
	const std::string 	&path,
	entt::registry 		&registry,
	ResourceManager	    &rm
)
{
    auto map = std::make_unique<TileMap>();
    try
    {
        std::filesystem::path p(path);
        if (p.extension() != ".json" && p.extension() != ".tmj")
            throw std::runtime_error("Bad extension: " + path);
        if (!std::filesystem::exists(p))
            throw std::runtime_error("File not found: " + path);

        std::ifstream file(path);
        if (!file)
            throw std::runtime_error("Failed opening: " + path);

        nlohmann::json data;
        file >> data;

        map->setWidth(data["width"]);
        map->setHeight(data["height"]);
        map->setTileSize(data["tileheight"]);
        parseTilesets(*map, data, rm);
        parseLayersRecursive(*map, data["layers"], registry);
    }
    catch (const std::exception &e) {
        throw std::runtime_error(std::string("MapParser::start: ") + e.what());
    }
    return (map);
}