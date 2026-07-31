#include "CollisionUtils.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
namespace CollisionUtils
{
	bool	rectIntersect(
		const SDL_Rect	&a,
		const SDL_Rect	&b
	)
	{
		return (SDL_HasIntersection(&a, &b));
	}

	struct Vec2 { float x, y; };
	
	static Vec2	sub(SDL_Point a, SDL_Point b)
	{
		return {
			(float)(a.x-b.x),
			(float)(a.y-b.y)
		};
	}
	static float	dot(Vec2 a, Vec2 b)
	{
		return (a.x * b.x + a.y * b.y);
	}
	static Vec2	perp(Vec2 v)
	{
		return { -v.y, v.x };
	}
	static float	cross2D(Vec2 a, Vec2 b)
	{
		return (a.x * b.y - a.y * b.x);
	}
	static void	projectPolygon(
		const std::vector<SDL_Point> &poly,
		Vec2 axis,
		float &minP, float &maxP
	)
	{
		minP = maxP = dot(axis, {(float)poly[0].x, (float)poly[0].y});
		for (size_t i = 1; i < poly.size(); ++i)
		{
			float p = dot(axis, {(float)poly[i].x, (float)poly[i].y});
			if (p < minP) minP = p;
			if (p > maxP) maxP = p;
		}
	}

	bool	satConvex(
		const std::vector<SDL_Point> &polyA,
		const std::vector<SDL_Point> &polyB
	)
	{
		auto testAxes = [&](const std::vector<SDL_Point> &poly) -> bool
		{
			for (size_t i = 0; i < poly.size(); ++i)
			{
				SDL_Point a = poly[i];
				SDL_Point b = poly[(i + 1) % poly.size()];
				Vec2 edge = sub(b, a);
				Vec2 axis = perp(edge);
				float minA, maxA, minB, maxB;
				projectPolygon(polyA, axis, minA, maxA);
				projectPolygon(polyB, axis, minB, maxB);
				if (maxA < minB || maxB < minA)
					return (true); // pas de collisions
			}
			return false;
		};
		if (testAxes(polyA)) return (false);
		if (testAxes(polyB)) return (false);
		return (true);
	}

	std::vector<SDL_Point>	rectToPolygon(const SDL_Rect &r)
	{
		return {
			{r.x, r.y},
			{r.x + r.w, r.y},
			{r.x + r.w, r.y + r.h},
			{r.x, r.y + r.h}
		};
	}

	bool	isConvex(const std::vector<SDL_Point> &polygon)
	{
		int n = (int)polygon.size();
		if (n < 3) return (false);
		int sign = 0;
		for (int i = 0; i < n; ++i)
		{
			Vec2 a = sub(polygon[(i+1)%n], polygon[i]);
			Vec2 b = sub(polygon[(i+2)%n], polygon[(i+1)%n]);
			float c = cross2D(a, b);
			if (c != 0)
			{
				int s = (c > 0) ? 1 : -1;
				if (sign == 0) sign = s;
				else if (sign != s) return (false);
			}
		}
		return (true);
	}

	std::vector<std::vector<SDL_Point>>	triangulate(
		const std::vector<SDL_Point> &polygon
	)
	{
		std::vector<std::vector<SDL_Point>> triangles;
		std::vector<SDL_Point> verts = polygon;

		auto isEar = [&](int prev, int curr, int next) -> bool
		{
			Vec2 a = sub(verts[curr], verts[prev]);
			Vec2 b = sub(verts[next], verts[curr]);
			if (cross2D(a, b) <= 0) return (false);

			std::vector<SDL_Point> tri = {verts[prev], verts[curr], verts[next]};
			for (size_t i = 0; i < verts.size(); ++i)
			{
				if ((int)i == prev || (int)i == curr || (int)i == next)
					continue ;
				if (satConvex(tri, {verts[i]}))
					continue ;
				return (false);
			}
			return (true);
		};
		int maxIter = (int)verts.size() * (int)verts.size();
		while (verts.size() > 3 && maxIter-- > 0)
		{
			int n = (int)verts.size();
			for (int i = 0; i < n; ++i)
			{
				int prev = (i - 1 + n) % n;
				int next = (i + 1) % n;
				if (isEar(prev, i, next))
				{
					triangles.push_back({verts[prev], verts[i], verts[next]});
					verts.erase(verts.begin() + i);
					break ;
				}
			}
		}
		if (verts.size() == 3)
			triangles.push_back(verts);
		return (triangles);
	}
}