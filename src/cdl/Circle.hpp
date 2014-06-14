#ifndef CDL_CIRCLE_HPP
#define CDL_CIRCLE_HPP

#include "Vec2.hpp"

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
