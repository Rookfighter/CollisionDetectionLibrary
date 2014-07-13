/* The World component of CDL manages CollisionObjects, moves them
 * and calculates collisions between them. If a collision happened the
 * current CollisionHandler is triggered. the CollisionHandler can be
 * set to any own implementation with 'setCollisionHandler(CollisionHandler *p_collisionHandler)'
 * The 'step(const float p_sec, const int p_iterations)' function steps the
 * whole simulation one timestep ahead. The length of one timestep in seconds
 * is determined by the first argument. The second argument determines how many
 * iterations are done to calculate this timestep. More iterations lead to
 * higher precision but longer execution time. */

#ifndef CDL_WORLD_HPP
#define CDL_WORLD_HPP

#include <list>
#include "cdl/CollisionObject.hpp"
#include "cdl/CollisionHandler.hpp"
#include "cdl/DefaultCollisionHandler.hpp"

namespace cdl
{
	class World
	{
	private:
		std::list<CollisionObject*> objects;
		CollisionHandler *collisionHandler;
		DefaultCollisionHandler defaultHandler;
		
		void moveObjects(const float p_sec);
		void collideObjects();
		void collideObjects(CollisionObject *p_objectA, CollisionObject *p_objectB);
	public:
		World() { setDefaultHandler(); }
		~World() { }
	
		CollisionObject* createObject(const std::vector<Polygon> &p_polygons, const std::vector<Circle> &p_circles);
		void destroyObject(CollisionObject* p_object);
		void destroyAllObjects();
		void step(const float p_sec, const int p_iterations);
		
		void setCollisionHandler(CollisionHandler *p_collisionHandler);
		void setDefaultHandler();
	};
}

#endif