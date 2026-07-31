#ifndef COLLISIONUTILS_HPP
# define COLLISIONUTILS_HPP

# include <SDL2/SDL.h>
# include <vector>

namespace CollisionUtils
{
	// AABB
	bool	rectIntersect(const SDL_Rect &a, const SDL_Rect &b);
	// SAT
	bool	satConvex(
		const std::vector<SDL_Point> &polyA,
		const std::vector<SDL_Point> &polyB
	);
	// Polygon -> triangles
	std::vector<std::vector<SDL_Point>> triangulate(
		const std::vector<SDL_Point> &polygon
	);
	// SDL_Rect -> polygon
	std::vector<SDL_Point>	rectToPolygon(const SDL_Rect &r);
	bool isConvex(
		const std::vector<SDL_Point> &polygon
	);
}

#endif