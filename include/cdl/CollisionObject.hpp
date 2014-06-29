#ifndef CDL_COLLISION_OBJECT_HPP
#define CDL_COLLISION_OBJECT_HPP

#include <vector>
#include "cdl/Polygon.hpp"
#include "cdl/Circle.hpp"

namespace cdl
{
	class CollisionObject
	{
	public:
		void *userData;
		std::vector<Polygon> polygons;
		std::vector<Circle> circles;
		Vec2 position;
		Vec2 linearVelocity;
		float directionRadian;
		
		CollisionObject() { }
		CollisionObject(const std::vector<Polygon> &p_polygons)
		:polygons(p_polygons), circles() { }
		CollisionObject(const std::vector<Circle> &p_circles)
		:polygons(), circles(p_circles) { }
		CollisionObject(const std::vector<Polygon> &p_polygons, const std::vector<Circle> &p_circles)
		:polygons(p_polygons), circles(p_circles) { }
		~CollisionObject() { }
	};
}

#endif