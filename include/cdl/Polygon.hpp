#ifndef CDL_POLYGON_HPP
#define CDL_POLYGON_HPP

#include <vector>
#include "cdl/Vec2.hpp"

namespace cdl
{
	class Polygon
	{
	public:
		std::vector<Vec2> corners;
		Polygon() { }
		Polygon(const std::vector<Vec2> &p_corners): corners(p_corners) { }
		~Polygon() { }

	};

}

#endif // CDL_POLYGON_HPP
