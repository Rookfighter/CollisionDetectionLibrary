/* The CollisionDetection component of CDL provides functions to calculate collisions
 * between various 2 dimensional objects.
 * Every function returns true if a collision happened. In this case the intersection points
 * are stored in the vector given as last argument. */
 
#ifndef CDL_COLLISION_DETECTION_HPP
#define CDL_COLLISION_DETECTION_HPP

#include <vector>
#include "cdl/Polygon.hpp"
#include "cdl/Circle.hpp"
#include "cdl/Line.hpp"

namespace cdl
{
	bool collideCircles(const Circle &p_circle1, const Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLines(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineSegments(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineLineSegment(const Line &p_line, const Line &p_lineSegment, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineSegmentCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
	bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLinePolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineSegmentPolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);
	bool collideCirclePolygon(const Circle &p_circle, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);
}

#endif // CDL_COLLISION_DETECTION_HPP
