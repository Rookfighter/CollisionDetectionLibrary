/* The CollisionHandler Interface is used to change the way how CDL
 * reacts to a collision of two objects.
 * The Interface has to be implemented and set as collision handler
 * in the World class.
 * If a collision happens the function 'collide(CollisionEvent &p_event)'
 * is triggered. The given CollisionEvent contains the two objects that
 * are part of the collision and the intersection points. */
 
#ifndef CDL_COLLISION_HANDLER_HPP
#define CDL_COLLISION_HANDLER_HPP

#include <vector>
#include "cdl/CollisionObject.hpp"

namespace cdl
{
	class CollisionEvent
	{
	private:
		const std::vector<Vec2> &intersectionPoints;
		CollisionObject *objectA;
		CollisionObject *objectB;
		
	public:
		CollisionEvent(const std::vector<Vec2> &p_intersectionPoints, CollisionObject *p_objectA, CollisionObject *p_objectB)
		:intersectionPoints(p_intersectionPoints), objectA(p_objectA), objectB(p_objectB) { }
		~CollisionEvent() { }
		
		CollisionObject* getObjectA()
		{return objectA;}
		CollisionObject* getObjectB()
		{return objectB;}
		
		const std::vector<Vec2>& getIntersectionPoints()
		{return intersectionPoints;}
	};
	
	class CollisionHandler
	{
	public:
		CollisionHandler() { }
		virtual ~CollisionHandler() { }
		virtual void collide(CollisionEvent &p_event) = 0;
	};
}

#endif