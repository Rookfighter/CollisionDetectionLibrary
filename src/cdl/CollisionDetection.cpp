#include <cmath>
#include "CollisionDetection.hpp"

/* Formula of line intersection:
 * u1 = LINE1_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u2 = LINE2_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u1 and u2 are used as factors to calculate intersection point */
#define LINE_INTERSECT_DENOM(l1,l2) (((l2.point2.y - l2.point1.y) * (l1.point2.x - l1.point1.x)) - \
									 ((l2.point2.x - l2.point1.x) * (l1.point2.y - l1.point1.y)))
#define LINE1_INTERSECT_FAC(l1, l2) (((l2.point2.x - l2.point1.x) * (l1.point1.y - l2.point1.y)) - \
									 ((l2.point2.y - l2.point1.y) * (l1.point1.x - l2.point1.x)))
#define LINE2_INTERSECT_FAC(l1, l2) (((l1.point2.x - l1.point1.x) * (l1.point1.y - l2.point1.y)) - \
								     ((l1.point2.y - l1.point1.y) * (l1.point1.x - l2.point1.x)))
									 
/* Formulas for line circle intersection */
#define LINE_CIRCLE_INTERSECT_FAC_A(diffp1p2) ((diffp1p2.x) * (diffp1p2.x) + (diffp1p2.y) * (diffp1p2.y))
#define LINE_CIRCLE_INTERSECT_FAC_B(diffp1p2, p1) (2 * ((diffp1p2.x * p1.x) + (diffp1p2.y * p1.y)))
#define LINE_CIRCLE_INTERSECT_FAC_C(p1, rad) ((p1.x * p1.x) + (p1.y * p1.y) - (rad * rad))
#define LINE_CIRCLE_INTERSECT_DELTA(a, b, c) (b * b - (4 * a * c))

namespace cdl
{
	
	bool collideCircles(Circle &p_circle1, Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints)
	{
		p_intersectionPoints.clear();
		// vector from mid1 to mid2
		Vec2 directionVec = p_circle2.mid - p_circle1.mid;
		float sqDistance = directionVec.lengthSQ();
		// square of radius sum is higher than square distance between mids
		if((p_circle1.radius + p_circle2.radius) * (p_circle1.radius + p_circle2.radius) > sqDistance)
			return false;
		
		// distance from circle1 to radicalLine
		float distance1 = (sqDistance + p_circle1.radius * p_circle1.radius - p_circle2.radius * p_circle2.radius) / sqrt(sqDistance);
		// points of radical line
		Vec2 radicalPoint1 = p_circle1.mid + (directionVec * distance1);
		Vec2 radicalPoint2 = radicalPoint1 + directionVec.perpendicular();
		Line radicalLine(radicalPoint1, radicalPoint2);
		return collideLineCircle(radicalLine, p_circle1, p_intersectionPoints);
	}
	
	bool collideLines(Line &p_line1, Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		p_intersectionPoints.clear();
		// denominator of formula for line intersection
		float denominator = LINE_INTERSECT_DENOM(p_line1, p_line2);
		if(denominator == 0)
			return false;
		// factor to calculate resulting point
		float u1 = LINE1_INTERSECT_FAC(p_line1, p_line2) / denominator;
		
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
	bool collideLineSegments(Line &p_line1, Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		p_intersectionPoints.clear();
		// denominator of formula for line intersection
		float denominator = LINE_INTERSECT_DENOM(p_line1, p_line2);
		if(denominator == 0)
			return false;
		// factor to calculate resulting point
		float u1 = LINE1_INTERSECT_FAC(p_line1, p_line2) / denominator;
		float u2 = LINE2_INTERSECT_FAC(p_line1, p_line2) / denominator;
		
		// intersection point is not in between points of lines
		if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1)
			return false;
			
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
	bool collideLineCircle(Line &p_line, Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		p_intersectionPoints.clear();
		
		Vec2 localPoint1 = p_line.point1 - p_circle.mid;
		Vec2 localPoint2 = p_line.point2 - p_circle.mid;
		// direction vector of the line
		Vec2 diffP2P1 = localPoint2 - localPoint1;
		
		float a = LINE_CIRCLE_INTERSECT_FAC_A(diffP2P1);
		float b = LINE_CIRCLE_INTERSECT_FAC_B(diffP2P1, localPoint1);
		float c = LINE_CIRCLE_INTERSECT_FAC_C(localPoint1, p_circle.radius);
		float delta = LINE_CIRCLE_INTERSECT_DELTA(a, b, c);
		//no intersection
		if (delta < 0)
			return false;
		// one intersection
		else if (delta == 0) {
			float u = -b / (2 * a);
			p_intersectionPoints.push_back(p_line.point1 + (u * diffP2P1));
		//two intersections
		} else {
			float sqrtDelta = sqrt(delta);
			float u1 = (-b + sqrtDelta) / (2 * a);
			float u2 = (-b - sqrtDelta) / (2 * a);
			
			p_intersectionPoints.push_back(p_line.point1 + (u1 * diffP2P1));
			p_intersectionPoints.push_back(p_line.point1 + (u2 * diffP2P1));
		}
		
		return true;
	}
	
	bool collideLineSegmentCircle(Line &p_line, Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		p_intersectionPoints.clear();
		
		Vec2 localPoint1 = p_line.point1 - p_circle.mid;
		Vec2 localPoint2 = p_line.point2 - p_circle.mid;
		// direction vector of the line
		Vec2 diffP2P1 = localPoint2 - localPoint1;
		
		float a = LINE_CIRCLE_INTERSECT_FAC_A(diffP2P1);
		float b = LINE_CIRCLE_INTERSECT_FAC_B(diffP2P1, localPoint1);
		float c = LINE_CIRCLE_INTERSECT_FAC_C(localPoint1, p_circle.radius);
		float delta = LINE_CIRCLE_INTERSECT_DELTA(a, b, c);
		//no intersection
		if (delta < 0)
			return false;
		// one intersection
		else if (delta == 0) {
			float u = -b / (2 * a);
			// is not on the line segment
			if(u < 0 || u > 1)
				return false;
			else {
				p_intersectionPoints.push_back(p_line.point1 + (u * diffP2P1));
				return true;
			}
		//two intersections
		} else {
			float sqrtDelta = sqrt(delta);
			float u1 = (-b + sqrtDelta) / (2 * a);
			float u2 = (-b - sqrtDelta) / (2 * a);
			
			if(u1 < 0  || u1 > 1 || u2 < 0 || u2 > 1)
				return false;
			
			if(u1 >= 0  && u1 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (u1 * diffP2P1));
			if(u2 >= 0  && u2 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (u2 * diffP2P1));
			return true;
		}
		
		return true;
	}
}

