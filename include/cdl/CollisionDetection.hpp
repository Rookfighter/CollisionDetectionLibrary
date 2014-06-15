#ifndef CDL_COLLISION_DETECTION_HPP
#define CDL_COLLISION_DETECTION_HPP

#include <vector>
#include "cdl/Circle.hpp"
#include "cdl/Line.hpp"

namespace cdl
{
	bool collideCircles(Circle &p_circle1, Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLines(Line &p_line1, Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineSegments(Line &p_line1, Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineCircle(Line &p_line, Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
	bool collideLineSegmentCircle(Line &p_line, Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
}

#endif // CDL_COLLISION_DETECTION_HPP
