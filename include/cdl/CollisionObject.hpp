/* The CollisionObject is the common representation of a 2 dimensional
 * object in CDL. It consists of a list of polygons and a list of circles.
 * The positions of the circles and polygons are relative to the position
 * of the object.
 * The userData field can be used to store any additional data in the
 * CollisionObject. */

#ifndef CDL_COLLISION_OBJECT_HPP
#define CDL_COLLISION_OBJECT_HPP

#include <vector>
#include "cdl/Polygon.hpp"
#include "cdl/Circle.hpp"

namespace cdl
{
	class CollisionObject
	{
	private:
		std::vector<Polygon> polygonVec;
		std::vector<Circle> circleVec;
		float direction;
		
		void rotatePoint(Vec2 &p_point, float p_tanVal);
	public:
		void *userData;
		Vec2 position;
		Vec2 linearVelocity;
		
		CollisionObject(const std::vector<Polygon> &p_polygons)
		:polygonVec(p_polygons), circleVec() { }
		CollisionObject(const std::vector<Circle> &p_circles)
		:polygonVec(), circleVec(p_circles) { }
		CollisionObject(const std::vector<Polygon> &p_polygons, const std::vector<Circle> &p_circles)
		:polygonVec(p_polygons), circleVec(p_circles) { }
		~CollisionObject() { }
		
		void setDirection(float p_radian);
		float getDirection() const;
		const std::vector<Polygon>& polygons() const;
		const std::vector<Circle>& circles() const;
	};
}

#endif