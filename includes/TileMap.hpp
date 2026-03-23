#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <iostream>
# include <vector>

class TileMap
{
	public:
		TileMap(const std::string &file_path);
		~TileMap();
	private:
		int					width;
		int					height;
		int					tileSize;
		std::vector<int>	tiles;
};

#endif