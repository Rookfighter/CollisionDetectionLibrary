#ifndef CDL_WORLD_HPP
#define CDL_WORLD_HPP

#include <list>
#include "cdl/CollisionObject.hpp"

namespace cdl
{
	class World
	{
	private:
		std::list<CollisionObject*> objects;
		
		void moveObjects(const float p_sec);
		void collideObjects();
	public:
		World() { }
		~World() { }
	
		CollisionObject* createObject(const std::vector<Polygon> &p_polygons, const std::vector<Circle> &p_circles);
		void destroyObject(CollisionObject* p_object);
		void step(const float p_sec, const int p_iterations);
	};
}

#endif