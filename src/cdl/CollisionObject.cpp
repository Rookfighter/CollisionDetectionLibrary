#include <cmath>
#include "cdl/CollisionObject.hpp"

namespace cdl
{
	void CollisionObject::setDirection(float p_radian)
	{
		direction = p_radian;
		float tanVal;
		tanVal = tanf(direction);
		
		//rotate all circles
		for(int i = 0; i < circleVec.size(); ++i)
			rotatePoint(circleVec[i].mid, tanVal);
		
		//rotate all polygons
		for(int i = 0; i < polygonVec.size(); ++i) {
			for(int j = 0; j < polygonVec[i].corners.size(); ++j)
				rotatePoint(polygonVec[i].corners[j], tanVal);
		}
	}
	
	void CollisionObject::rotatePoint(Vec2 &p_point, float p_tanVal)
	{
		float x, y;
		x = p_point.y / p_tanVal;
		y = p_point.x * p_tanVal;
		p_point.set(x, y);
	}
	
	float CollisionObject::getDirection() const
	{
		return direction;
	}
	
	const std::vector<Polygon>& CollisionObject::polygons() const
	{
		return polygonVec;
	}
	
	const std::vector<Circle>& CollisionObject::circles() const
	{
		return circleVec;
	}
}