#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <iostream>
# include <vector>
# include <memory>

# include "graphics/Sprite.hpp"
# include "graphics/Camera.hpp"

enum class CollisionShapeType
{
	Rect,
	Polygon
};

struct CollisionShape
{
	CollisionShapeType					type;
	SDL_Rect							rect;
	std::vector<SDL_Point>				polygon;
	bool								convex;
	std::vector<std::vector<SDL_Point>> triangles;
};

typedef struct s_tileset
{
	int														firstgid;
	int														tileWidth;
	int														tileHeight;
	int														columns;
	std::string 											pathfile;
	std::shared_ptr<Sprite>									sprite;
	std::unordered_map<int, std::vector<CollisionShape>>	collisions;
}	t_tileset;

typedef struct	s_layer
{
	std::vector<int>	data;
	bool				visible;
	std::string			name;
	std::string			renderPass;
}	t_layer;

class TileMap
{
	public:
		TileMap();
		~TileMap();
		// METHODS
		void	addTileset(t_tileset);
		void	addLayer(t_layer);
		void	printLayers();
		void	render(Camera &camera);
		void	renderForeground(Camera &camera);
		void    debugPrint() const;
		// SETTERS
		void	setWidth(int w);
		void	setHeight(int h);
		void	setTileSize(int s);
		void	setCollisionLayer(t_layer l);
		// GETTERS
		[[nodiscard]] int							getWidth() const;
		[[nodiscard]] int							getHeight() const;
		[[nodiscard]] int							getTileSize() const;
		[[nodiscard]] t_layer						getCollisionLayer() const;
		[[nodiscard]] std::vector<SDL_Rect>			getCollisionRects(int gid, int tileX, int tileY) const;
		[[nodiscard]] std::vector<CollisionShape>	getWorldCollisionShapes(const SDL_Rect &area) const;
		const t_tileset								*getTilesetByPath(const std::string path);

	private:
		// PROPS
		int						_width;
		int						_height;
		int						_tileSize;
		std::vector<t_tileset>	_tilesets;
		std::vector<t_layer>	_layers;
		t_layer					_collisionLayer;
		// METHODS
		const t_tileset	*getTilesetForTile(int gid) const;
		bool			isForegroundLayer(std::string name);
		void			renderLayer(const t_layer &layer, Camera &camera);
};

#endif