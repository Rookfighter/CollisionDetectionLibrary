#include <UnitTest++.h>
#include <cdl/cdl.hpp>
#include <cdl/Utils.hpp>
#include <vector>

SUITE(CollisionDetection)
{
	TEST(CircleCollision)
	{
		cdl::Circle c1, c2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c1.mid.x = 0;
		c1.mid.y = 0;
		c1.radius = 2;
		
		c2.mid.x = 5;
		c2.mid.y = 0;
		c2.radius = 1;
		
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2,intersectionPoints);
		
		//circles should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		c2.radius = 4;
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2, intersectionPoints);
		//circles should intersect in 2 points
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		
		c1.mid.x = 2;
		c1.mid.y = 4;
		c1.radius = 2;
		
		c2.mid.x = 2;
		c2.mid.y = 0;
		c2.radius = 2;
		
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2, intersectionPoints);
		//circles should intersect in 1 point (tangent)
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
	}
	
	TEST(LineCollision)
	{
		cdl::Line l1, l2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		//increasing
		l1.point1.x = 1;
		l1.point1.y = -3;
		l1.point2.x = 5;
		l1.point2.y = 10;
		
		//parallel
		l2.point1.x = 1;
		l2.point1.y = -1;
		l2.point2.x = 5;
		l2.point2.y = 12;
		
		intersectionPoints.clear();
		ret = cdl::collideLines(l1, l2, intersectionPoints);
		// lines should be parallel, no intersection
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//decreasing
		l2.point1.x = 2;
		l2.point1.y = 7;
		l2.point2.x = 4;
		l2.point2.y = 3;
		
		intersectionPoints.clear();
		ret = cdl::collideLines(l1, l2, intersectionPoints);
		// lines should intersect
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		
		//decreasing
		l1.point1.x = 0;
		l1.point1.y = 2;
		l1.point2.x = 3;
		l1.point2.y = -1;
		
		//lines would cross, line segments should not
		l2.point1.x = 0;
		l2.point1.y = -4;
		l2.point2.x = 9;
		l2.point2.y = 1;
		
		intersectionPoints.clear();
		ret = cdl::collideLines(l1, l2, intersectionPoints);
		// lines intersect
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
	}
	
	TEST(LineSegmentCollision)
	{
		cdl::Line l1, l2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		//decreasing
		l1.point1.x = 0;
		l1.point1.y = 2;
		l1.point2.x = 3;
		l1.point2.y = -1;
		
		//parallel
		l2.point1.x = 3;
		l2.point1.y = 2;
		l2.point2.x = 6;
		l2.point2.y = -1;
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lineSegments should be parallel, no intersection
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//decreasing
		l1.point1.x = 0;
		l1.point1.y = 2;
		l1.point2.x = 3;
		l1.point2.y = -1;
		
		//changed x values -> should be perpendicular
		l2.point1.x = 3;
		l2.point1.y = 2;
		l2.point2.x = 0;
		l2.point2.y = -1;
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lineSegments intersect
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		
		//decreasing
		l1.point1.x = 0;
		l1.point1.y = 2;
		l1.point2.x = 3;
		l1.point2.y = -1;
		
		//lines would cross, line segments should not
		l2.point1.x = 0;
		l2.point1.y = -4;
		l2.point2.x = 9;
		l2.point2.y = 1;
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lineSegments dont intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//this is a line
		l1.point1.x = 2;
		l1.point1.y = 1;
		l1.point2.x = 6;
		l1.point2.y = -1;
		
		//this is a line segment
		l2.point1.x = -2;
		l2.point1.y = 1;
		l2.point2.x = 2;
		l2.point2.y = 4;
		
		intersectionPoints.clear();
		ret = cdl::collideLineLineSegment(l1, l2, intersectionPoints);
		// line and lineSegment should collide
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
	}
	
	TEST(lineCircleCollision)
	{
		cdl::Line l;
		cdl::Circle c;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c.mid.x = 0;
		c.mid.y = 0;
		c.radius = 2;
		
		l.point1.set(-6, -5);
		l.point2.set(-2,-2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// lineSegments dont intersect, but lines should
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		
		l.point1.set(-1, -4);
		l.point2.set(4,-2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// line should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(-2, 2);
		l.point2.set(4, 2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// line should tangent circle
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
	}
	
	TEST(lineSegmentCircleCollision)
	{
		cdl::Line l;
		cdl::Circle c;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c.mid.x = 0;
		c.mid.y = 0;
		c.radius = 2;
		
		l.point1.set(-6, -5);
		l.point2.set(-2,-2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments dont intersect, but lines should
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(-2, -2);
		l.point2.set(2, 1);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments should intersect 2 times
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		
		l.point1.set(-2, -2);
		l.point2.set(0, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments should intersect only 1 time
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		
		l.point1.set(-1, -4);
		l.point2.set(4,-2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(-2, 2);
		l.point2.set(4, 2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// lineSegment should tangent circle
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
	}
	
	TEST(PolygonCollision)
	{
		cdl::Polygon p1, p2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		p1.corners.push_back(cdl::Vec2(-3, 1));
		p1.corners.push_back(cdl::Vec2(-1, 1));
		p1.corners.push_back(cdl::Vec2(-1, -1));
		p1.corners.push_back(cdl::Vec2(-3, -1));
		
		p2.corners.push_back(cdl::Vec2(1, 0));
		p2.corners.push_back(cdl::Vec2(2, 1));
		p2.corners.push_back(cdl::Vec2(3, 1));
		p2.corners.push_back(cdl::Vec2(3, -1));
		p2.corners.push_back(cdl::Vec2(2, -1));
		
		intersectionPoints.clear();
		ret = cdl::collidePolygons(p1, p2, intersectionPoints);
		//polygons should not collide
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		for(int i = 0; i < p2.corners.size(); ++i)
			p2.corners[i] += cdl::Vec2(-3, 1);
			
		intersectionPoints.clear();
		ret = cdl::collidePolygons(p1, p2, intersectionPoints);
		//polygons should collide in 2 points
		CHECK(ret);
		//CHECK(intersectionPoints.size() == 2);
	}
}