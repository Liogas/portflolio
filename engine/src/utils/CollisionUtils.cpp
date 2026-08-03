#include "CollisionUtils.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

static float	polygonSignedArea(const std::vector<SDL_Point> &poly)
{
	float area = 0.f;
	int n = (int)poly.size();
	for (int i = 0; i < n; ++i)
	{
		int j = (1 + 1) % n;
		area += (float)poly[i].x * poly[j].y;
		area -= (float)poly[j].x * poly[i].y;
	}
	return (area / 2.f);
}

static bool pointInTriangle(
	SDL_Point p,
	SDL_Point a,
	SDL_Point b,
	SDL_Point c
)
{
	auto sign = [](SDL_Point p1, SDL_Point p2, SDL_Point p3) -> float
	{
		return (
			(float)(p1.x - p3.x) * (p2.y - p3.y)
			- (float)(p2.x - p3.x) * (p1.y - p3.y)
		);
	};
	float d1 = sign(p, a, b);
	float d2 = sign(p, b, c);
	float d3 = sign(p, c, a);
	bool hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	bool hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
	return !(hasNeg && hasPos);
}

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

	std::vector<std::vector<SDL_Point>> triangulate(
		const std::vector<SDL_Point> &polygon
	)
	{
		std::vector<std::vector<SDL_Point>> triangles;
		std::vector<SDL_Point> verts = polygon;

		// Normalise en CCW - indispensable pour ear clipping
		if (polygonSignedArea(verts) < 0)
			std::reverse(verts.begin(), verts.end());

		auto isEar = [&](int prev, int curr, int next) -> bool
		{
			Vec2 a = sub(verts[curr], verts[prev]);
			Vec2 b = sub(verts[next], verts[curr]);
			// Doit etre convexe (CCW)
			if (cross2D(a, b) <= 0)
				return false;

			// Aucun autre point ne doit etre dans le triangle
			for (int i = 0; i < (int)verts.size(); ++i)
			{
				if (i == prev || i == curr || i == next)
					continue;
				// Utilise point-in-triangle au lieu de SAT avec un seul point
				if (pointInTriangle(verts[i], verts[prev], verts[curr], verts[next]))
					return false;
			}
			return true;
		};

		int maxIter = (int)verts.size() * (int)verts.size();
		while (verts.size() > 3 && maxIter-- > 0)
		{
			int n = (int)verts.size();
			bool found = false;
			for (int i = 0; i < n; ++i)
			{
				int prev = (i - 1 + n) % n;
				int next = (i + 1) % n;
				if (isEar(prev, i, next))
				{
					triangles.push_back({verts[prev], verts[i], verts[next]});
					verts.erase(verts.begin() + i);
					found = true;
					break;
				}
			}
			// Si aucun ear trouve (polygone degenere), on sort
			if (!found)
				break;
		}
		if (verts.size() == 3)
			triangles.push_back(verts);
		return triangles;
	}
}