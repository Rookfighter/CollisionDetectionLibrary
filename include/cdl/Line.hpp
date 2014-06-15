#ifndef CDL_LINE_HPP
#define CDL_LINE_HPP

#include "cdl/Vec2.hpp"

namespace cdl
{
	class Line
	{
	public:
		Vec2 point1;
		Vec2 point2;
		
		Line(): point1(), point2() { }
		Line(const Vec2 &p_point1, const Vec2 &p_point2): point1(p_point1), point2(p_point2) { }
		~Line() { }

	};
}

#endif // CDL_LINE_HPP
