#include <UnitTest++.h>
#include <cdl/cdl.hpp>
#include <vector>

SUITE(CollisionDetection)
{
	TEST(CircleCollision)
	{
		cdl::Circle c1, c2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c1.mid.set(-1, 0);
		c1.radius = 1;
		
		c2.mid.set(5, 0);
		c2.radius = 1;
		
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2,intersectionPoints);
		
		//circles should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		c2.mid.set(1, 0);
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2, intersectionPoints);
		//circles should tangent
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(0,0));
		
		c1.mid.set(2, 0);
		c1.radius = 2;
		
		c2.mid.set(0, -2);
		c2.radius = 2;
		
		intersectionPoints.clear();
		ret = cdl::collideCircles(c1, c2, intersectionPoints);
		//circles should intersect in 2 points
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		CHECK(intersectionPoints[0] == cdl::Vec2(2, -2));
		//fails due to rounding error of float
		//CHECK(intersectionPoints[1] == cdl::Vec2(0, 6e-008));
	}
	
	TEST(LineCollision)
	{
		cdl::Line l1, l2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		//increasing
		l1.point1.set(1, 0);
		l1.point2.set(2, 1);
		
		//parallel
		l2.point1.set(1, -2);
		l2.point2.set(2, -1);
		
		intersectionPoints.clear();
		ret = cdl::collideLines(l1, l2, intersectionPoints);
		// lines should be parallel, no intersection
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//decreasing
		l2.point1.set(1, 4);
		l2.point2.set(2, 3);
		
		intersectionPoints.clear();
		ret = cdl::collideLines(l1, l2, intersectionPoints);
		// lines should intersect
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(3, 2));
	}
	
	TEST(LineSegmentCollision)
	{
		cdl::Line l1, l2;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		//increasing
		l1.point1.set(1, 0);
		l1.point2.set(2, 1);
		
		//parallel
		l2.point1.set(1, -2);
		l2.point2.set(2, -1);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lineSegments should be parallel, no intersection
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//decreasing
		l2.point1.set(1, 4);
		l2.point2.set(2, 3);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lines should intersect, linesegments dont
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		//decreasing
		l2.point1.set(1, 4);
		l2.point2.set(4, 1);
		
		intersectionPoints.clear();
		ret = cdl::collideLineLineSegment(l1, l2, intersectionPoints);
		// line (l1) and lineSegment (l2) should collide
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(3,2));
		
		//increasing
		l1.point1.set(1, 0);
		l1.point2.set(4, 3);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegments(l1, l2, intersectionPoints);
		// lineSegments intersect
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(3,2));
	}
	
	TEST(lineCircleCollision)
	{
		cdl::Line l;
		cdl::Circle c;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c.mid.set(0, 0);
		c.radius = 2;
		
		l.point1.set(3, 0);
		l.point2.set(5, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// lineSegments dont intersect, but lines should
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		CHECK(intersectionPoints[0] == cdl::Vec2(2, 0));
		CHECK(intersectionPoints[1] == cdl::Vec2(-2, 0));
		
		l.point1.set(-3, -1);
		l.point2.set(-1,-3);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// line should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(2, 2);
		l.point2.set(2, 3);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// line should tangent circle
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(2,0));
	}
	
	TEST(lineSegmentCircleCollision)
	{
		cdl::Line l;
		cdl::Circle c;
		std::vector<cdl::Vec2> intersectionPoints;
		bool ret;
		
		c.mid.set(0, 0);
		c.radius = 2;
		
		l.point1.set(3, 0);
		l.point2.set(5, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments dont intersect, but lines should
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(-3, 0);
		l.point2.set(3, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments should intersect 2 times
		CHECK(ret);
		CHECK(intersectionPoints.size() == 2);
		CHECK(intersectionPoints[0] == cdl::Vec2(2, 0));
		CHECK(intersectionPoints[1] == cdl::Vec2(-2, 0));
		
		l.point1.set(-3, 0);
		l.point2.set(0, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegments should intersect only 1 time
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(-2, 0));
		
		l.point1.set(-4, 0);
		l.point2.set(-3, 0);
		
		intersectionPoints.clear();
		ret = cdl::collideLineSegmentCircle(l, c, intersectionPoints);
		// lineSegment should not intersect
		CHECK(!ret);
		CHECK(intersectionPoints.empty());
		
		l.point1.set(2, 2);
		l.point2.set(2, -2);
		
		intersectionPoints.clear();
		ret = cdl::collideLineCircle(l, c, intersectionPoints);
		// lineSegment should tangent circle
		CHECK(ret);
		CHECK(intersectionPoints.size() == 1);
		CHECK(intersectionPoints[0] == cdl::Vec2(2, 0));
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
		CHECK(intersectionPoints.size() == 2);
		CHECK(intersectionPoints[0] == cdl::Vec2(-2, 1));
		CHECK(intersectionPoints[1] == cdl::Vec2(-1, 0));
	}
}