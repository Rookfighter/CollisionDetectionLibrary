#include <UnitTest++.h>
#include <cdl/cdl.hpp>
#include <cdl/Utils.hpp>
#include <cmath>

SUITE(BasicTests)
{
	TEST(Vec2)
	{
		cdl::Vec2 v1(2,1);
		cdl::Vec2 v2;
		cdl::Vec2 v3;
		
		CHECK(v1.x == 2 && v1.y == 1);
		CHECK(v2.x == 0 && v2.y == 0);
		CHECK(v1 != v2);
		v2.x = 2;
		v2.y = 1;
		CHECK(v2 == v1);
		
		v3 = v1 * 3;
		CHECK(v3.x == 6 && v3.y == 3);
		v3 *= 4;
		CHECK(v3.x == 24 && v3.y == 12);
		v3 /= 2;
		CHECK(v3.x == 12 && v3.y == 6);
		v2 = v3 / 2;
		CHECK(v2.x == 6 && v2.y == 3);
		
		v3 = v1 + v2;
		CHECK(v3.x == 8 && v3.y == 4);
		v3 += v1;
		CHECK(v3.x == 10 && v3.y == 5);
		
		v1 = v2 - v3;
		CHECK(v1.x == -4 && v1.y == -2);
		v1-= v2;
		CHECK(v1.x == -10 && v1.y == -5);
	}
}