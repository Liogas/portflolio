#ifndef TILEMAP_HPP
# define TILEMAP_HPP

# include <iostream>
# include <vector>

class TileMap
{
	public:
		TileMap(int width, int height);
		~TileMap();
		// SETTERS
		void	setWidth(int w);
		void	setHeight(int h);
		void	setTileSize(int s);
		// GETTERS
		[[nodiscard]] int	getWidth() const;
		[[nodiscard]] int	getHeight() const;
		[[nodiscard]] int	getTileSize() const;
	private:
		int					_width;
		int					_height;
		int					_tileSize;
		std::vector<int>	_tiles;
		std::vector<int>	_passages;
};

#endif