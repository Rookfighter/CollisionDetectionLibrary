/* The Circle class represents a cricle shape in CDL. It provides a Vec2 as Mid
 * and a radius. */
 
#ifndef CDL_CIRCLE_HPP
#define CDL_CIRCLE_HPP

#include "cdl/Vec2.hpp"

namespace cdl
{
	class Circle
	{
	public:
		Vec2 mid;
		float radius;
		Circle() { }
		Circle(const Vec2 &p_mid, const float p_radius): mid(p_mid), radius(p_radius) { }
		~Circle() { }

	};

}

#endif
