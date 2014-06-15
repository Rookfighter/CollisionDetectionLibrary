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
		CHECK(intersectionPoints.size() == 1)
	}
	
	TEST(LineSegmentCollision)
	{
		
	}
	
	TEST(lineCircleCollision)
	{
		
	}
	
	TEST(lineSegmentCircleCollision)
	{
		
	}
}