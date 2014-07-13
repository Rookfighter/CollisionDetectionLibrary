/* The DefaultCollisionHandler is the standard Handler for World
 * objects in CDL. If a collision happens it sets the linearVelocity
 * of the two objects that take part in it to 0. */

#ifndef CDL_DEFAULT_COLLISION_HANDLER_HPP
#define CDL_DEFAULT_COLLISION_HANDLER_HPP

#include "cdl/CollisionHandler.hpp"

namespace cdl
{
	class DefaultCollisionHandler : public CollisionHandler
	{
	public:
		void collide(CollisionEvent &p_event)
		{ p_event.getObjectA()->linearVelocity.set(0,0); p_event.getObjectB()->linearVelocity.set(0,0); }
	};
}

#endif