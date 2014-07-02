#include <cmath>
#include <algorithm>
#include "cdl/CollisionDetection.hpp"
#include "cdl/Utils.hpp"

/* Formula of line intersection:
 * u1 = LINE1_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u2 = LINE2_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u1 and u2 are used as factors to calculate intersection point */
#define LINE_INTERSECT_DENOM(l1, l2) (((l2.point2.y - l2.point1.y) * (l1.point2.x - l1.point1.x)) - \
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
	static void unique(std::vector<Vec2> p_points)
	{
		for(int i = 0; i < p_points.size(); ++i) {
			for(int j = i; j < p_points.size(); ++j) {
				if(p_points[i] == p_points[j]) {
					p_points.erase(p_points.begin() + j);
					--j;
				}
			}
		}
	}
	
/*************************************************
 * Collide Circles
 *************************************************/
	
	typedef struct {
		Vec2 M1M2;
		float sqDist;
		float sqRadSum;
		bool collide;
	} circleIntersection_t;
	
	static circleIntersection_t circlesIntersect(const Circle &p_circle1, const Circle &p_circle2)
	{
		circleIntersection_t result;
		
		// vector from mid1 to mid2
		result.M1M2 = p_circle2.mid - p_circle1.mid;
		result.sqDist = result.M1M2.lengthSQ();
		result.sqRadSum = (p_circle1.radius + p_circle2.radius) * (p_circle1.radius + p_circle2.radius);
		// distance is lower / euqal than radius sum
		result.collide = result.sqDist <= result.sqRadSum;
		
		return result;
	}
	
	bool collideCircles(const Circle &p_circle1, const Circle &p_circle2)
	{
		return circlesIntersect(p_circle1, p_circle2).collide;
	}
	
	bool collideCircles(const Circle &p_circle1, const Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints)
	{
		circleIntersection_t intersection = circlesIntersect(p_circle1, p_circle2);
		if(!intersection.collide)
			return false;
			
		float circleDist = sqrt(intersection.sqDist);
		
		// tangent each other
		if(intersection.sqRadSum == intersection.sqDist) {
			p_intersectionPoints.push_back(p_circle1.mid + ((intersection.M1M2 / circleDist) * p_circle1.radius));
			return true;
		}
		
		// distance from circle1 to radicalLine
		float distance1 = (intersection.sqDist + p_circle1.radius * p_circle1.radius - p_circle2.radius * p_circle2.radius) / (2 * circleDist);
		// points of radical line, have to normalize direction vec
		Vec2 radicalPoint1 = p_circle1.mid + ((intersection.M1M2 / circleDist) * distance1);
		Vec2 radicalPoint2 = radicalPoint1 + intersection.M1M2.perpendicular();
		return collideLineCircle(Line(radicalPoint1, radicalPoint2), p_circle1, p_intersectionPoints);
	}
	
/*************************************************
 * Collide Lines
 *************************************************/
	
	typedef struct {
		float denominator;
		float u1;
		float u2;
		
		bool collide;
	} lineIntersection_t;
	
	static void linesIntersect(const Line &p_line1, const Line &p_line2, lineIntersection_t &p_result)
	{
		// denominator of formula for line intersection
		p_result.denominator = LINE_INTERSECT_DENOM(p_line1, p_line2);
		p_result.collide = p_result.denominator != 0;
	}
	
	static void calculateLineIntersectionFactor(const Line &p_line1, const Line &p_line2, lineIntersection_t &p_result)
	{
		// factor to calculate resulting point with line 1
		p_result.u1 = LINE1_INTERSECT_FAC(p_line1, p_line2) / p_result.denominator;
	}
	
	bool collideLines(const Line &p_line1, const Line &p_line2)
	{
		lineIntersection_t intersect;
		linesIntersect(p_line1, p_line2, intersect);
		return intersect.collide;
	}
	
	bool collideLines(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		lineIntersection_t intersect;
		linesIntersect(p_line1, p_line2, intersect);
		if(!intersect.collide)
			return false;
			
		calculateLineIntersectionFactor(p_line1, p_line2, intersect);
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (intersect.u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
/*************************************************
 * Collide Linesegments
 *************************************************/
	
	static void calculateLineSegmentIntersectionFactors(const Line &p_line1, const Line &p_line2, lineIntersection_t &p_result)
	{
		calculateLineIntersectionFactor(p_line1, p_line2, p_result);
		// factor to calculate resulting point with line 2
		p_result.u2 = LINE2_INTERSECT_FAC(p_line1, p_line2) / p_result.denominator;
					   
		// intersection point is in between points of lines
		p_result.collide = p_result.u1 >= 0 && p_result.u1 <= 1 && p_result.u2 >= 0 && p_result.u2 <= 1;
	}
	
	bool collideLineSegments(const Line &p_line1, const Line &p_line2)
	{
		std::vector<Vec2> tmp;
		return collideLineSegments(p_line1, p_line2, tmp);
	}
	
	bool collideLineSegments(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		lineIntersection_t intersect;
		linesIntersect(p_line1, p_line2, intersect);
		if(!intersect.collide)
			return false;
			
		calculateLineSegmentIntersectionFactors(p_line1, p_line2, intersect);
		if (!intersect.collide)
			return false;
			
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (intersect.u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
/*************************************************
 * Collide Line Linesegment
 *************************************************/
	
	static void calculateLineLineSegmentIntersectionFactor(const Line &p_line, const Line &p_lineSegment, lineIntersection_t &p_result)
	{
		calculateLineSegmentIntersectionFactors(p_line, p_lineSegment, p_result);
		//check if point is on the line
		p_result.collide = p_result.u2 >= 0 && p_result.u2 <= 1;
	}
	
	bool collideLineLineSegment(const Line &p_line, const Line &p_lineSegment, std::vector<Vec2> &p_intersectionPoints)
	{
		lineIntersection_t intersect;
		linesIntersect(p_line, p_lineSegment, intersect);
		if(!intersect.collide)
			return false;
		
		calculateLineLineSegmentIntersectionFactor(p_line, p_lineSegment, intersect);
		
		// intersection point is not in between points of lineSegment
		if (!intersect.collide)
			return false;
			
		// add intersection point
		p_intersectionPoints.push_back(p_lineSegment.point1 + (intersect.u2 * (p_lineSegment.point2 - p_lineSegment.point1)));
		return true;
	}
	
/*************************************************
 * Collide Line Circle
 *************************************************/
	
	typedef struct {
		Vec2 P1P2;
		float a;
		float b;
		float c;
		float delta;
		float u1;
		float u2;
		
		bool collide;
	} lineCircleIntersection_t;
	
	static void lineCircleIntersect(const Line &p_line, const Circle &p_circle, lineCircleIntersection_t &p_result)
	{
		Vec2 localPoint1 = p_line.point1 - p_circle.mid;
		Vec2 localPoint2 = p_line.point2 - p_circle.mid;
		// direction vector of the line
		p_result.P1P2 = localPoint2 - localPoint1;
		
		p_result.a = LINE_CIRCLE_INTERSECT_FAC_A(p_result.P1P2);
		p_result.b = LINE_CIRCLE_INTERSECT_FAC_B(p_result.P1P2, localPoint1);
		p_result.c = LINE_CIRCLE_INTERSECT_FAC_C(localPoint1, p_circle.radius);
		p_result.delta = LINE_CIRCLE_INTERSECT_DELTA(p_result.a, p_result.b, p_result.c);
		p_result .collide = p_result.delta >= 0;
	}
	
	static void calculateLineCircleIntersectionFactors(const Line &p_line, const Circle &p_circle, lineCircleIntersection_t &p_result)
	{
		if(!p_result.collide)
			return;
		else if(p_result.delta == 0)
			 p_result.u1 = -p_result.b / (2 * p_result.a);
		else {
			float sqrtDelta = sqrt(p_result.delta);
			p_result.u1 = (-p_result.b + sqrtDelta) / (2 * p_result.a);
			p_result.u2 = (-p_result.b - sqrtDelta) / (2 * p_result.a);
		}
	}
	
	bool collideLineCircle(const Line &p_line, const Circle &p_circle)
	{
		lineCircleIntersection_t intersect;
		lineCircleIntersect(p_line, p_circle, intersect);
		return intersect.collide;
	}
	
	bool collideLineCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		lineCircleIntersection_t intersect;
		lineCircleIntersect(p_line, p_circle, intersect);
	
		//no intersection
		if (!intersect.collide)
			return false;
			
		calculateLineCircleIntersectionFactors(p_line, p_circle, intersect);
		// one intersection, tangent
		if (intersect.delta == 0) {
			p_intersectionPoints.push_back(p_line.point1 + (intersect.u1 * intersect.P1P2));
		//two intersections
		} else {
			p_intersectionPoints.push_back(p_line.point1 + (intersect.u1 * intersect.P1P2));
			p_intersectionPoints.push_back(p_line.point1 + (intersect.u2 * intersect.P1P2));
		}
		
		return true;
	}
	
/*************************************************
 * Collide Line Circle
 *************************************************/	
	
	static void calculateLineSegmentCircleIntersectionFactors(const Line &p_lineSegment, const Circle &p_circle,  lineCircleIntersection_t &p_result)
	{
		
		calculateLineCircleIntersectionFactors(p_lineSegment, p_circle, p_result);
		if(!p_result.collide)
			return;
		else if(p_result.delta == 0)
			p_result.collide = p_result.u1 >= 0 && p_result.u2 <= 1;
		else
			p_result.collide = (p_result.u1 >= 0  && p_result.u1 <= 1) || (p_result.u2 >= 0 && p_result.u2 <= 1);
	}
	
	bool collideLineSegmentCircle(const Line &p_line, const Circle &p_circle)
	{
		return collideLineSegmentCircle(p_line, p_circle);
	}
	
	bool collideLineSegmentCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		lineCircleIntersection_t intersect;
		lineCircleIntersect(p_line, p_circle, intersect);
	
		//no intersection
		if (!intersect.collide)
			return false;
			
		calculateLineSegmentCircleIntersectionFactors(p_line, p_circle, intersect);
		//is not on line segment
		if (!intersect.collide)
			return false;
		
		// one intersection, tangent
		else if (intersect.delta == 0) {
			p_intersectionPoints.push_back(p_line.point1 + (intersect.u1 * intersect.P1P2));
		//two intersections
		} else {
			if(intersect.u1 >= 0  && intersect.u1 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (intersect.u1 * intersect.P1P2));
			if(intersect.u2 >= 0  && intersect.u2 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (intersect.u2 * intersect.P1P2));
		}
		
		return true;
	}
	
	bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
		std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon1.corners.size(); ++i) {
			next = (i + 1) % p_polygon1.corners.size();
			//collide all line segments of polygon1 with polygon 2
			if(collideLineSegmentPolygon(Line(p_polygon1.corners[i], p_polygon1.corners[next]), p_polygon2, resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
	bool collideLinePolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
		std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			//collide all line segments of the polygon with the line
			if(collideLineLineSegment(p_line, Line(p_polygon.corners[i], p_polygon.corners[next]), resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
	bool collideLineSegmentPolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
		std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			// collide all line segments of polygon with line segment
			if(collideLineSegments(p_line, Line(p_polygon.corners[i], p_polygon.corners[next]), resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
	bool collideCirclePolygon(const Circle &p_circle, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
		std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			//collide all line segments of polygon with circle
			if(collideLineSegmentCircle(Line(p_polygon.corners[i], p_polygon.corners[next]), p_circle, resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
}

