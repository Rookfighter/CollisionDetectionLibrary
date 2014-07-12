#include "cdl/World.hpp"
#include "cdl/CollisionDetection.hpp"

namespace cdl
{
	CollisionObject* World::createObject(const std::vector<Polygon> &p_polygons, const std::vector<Circle> &p_circles)
	{
		CollisionObject *result = new CollisionObject(p_polygons, p_circles);
		objects.push_back(result);
		return result;
	}
	
	void World::destroyObject(CollisionObject* p_object)
	{
		int before = objects.size();
		objects.remove(p_object);
		if(before > objects.size())
			delete p_object;
	}
	
	void World::step(const float p_sec, const int p_iterations)
	{
		float iterationSec = p_sec / ((float) p_iterations);
		
		for(int i = 0; i < p_iterations; ++i) {
			moveObjects(iterationSec);
			collideObjects();
		}
	}
	
	void World::moveObjects(const float p_sec)
	{
		std::list<CollisionObject*>::iterator it;
		for(it = objects.begin(); it != objects.end(); ++it)
			(*it)->position += ((*it)->linearVelocity * p_sec);
	}
	
	void World::collideObjects() 
	{
		std::list<CollisionObject*>::iterator it1, it2;
		// check each object with each other
		for(it1 = objects.begin(); it1 != objects.end(); ++it1) {
			for(++(it2 = it1); it2 != objects.end(); ++it2)
				collideObjects(*it1, *it2);
		}
	}
	
	// TODO shapes of objects use relative positions!
	void World::collideObjects(CollisionObject *p_objectA, CollisionObject *p_objectB) {
		bool collided = false;
		std::vector<Vec2> intersectionPoints;
		
		// check for all circles of A
		for(int i = 0; i < p_objectA->circles.size(); ++i) {
			// check for all circles of B
			for(int j = 0; j < p_objectB->circles.size(); ++j) {
				if(collideCircles(p_objectA->circles[i], p_objectB->circles[j], intersectionPoints))
					collided = true;
			}
			
			// check for all polygons of B
			for(int j = 0; j < p_objectB->polygons.size(); ++j) {
				if(collideCirclePolygon(p_objectA->circles[i], p_objectB->polygons[j], intersectionPoints))
					collided = true;
			}
		}
		
		// check for all polygons of A
		for(int i = 0; i < p_objectA->polygons.size(); ++i) {
			// check for all circles of B
			for(int j = 0; j < p_objectB->circles.size(); ++j) {
				if(collideCirclePolygon(p_objectB->circles[j], p_objectA->polygons[i], intersectionPoints))
					collided = true;
			}
			
			// check for all polygons of B
			for(int j = 0; j < p_objectB->polygons.size(); ++j) {
				if(collidePolygons(p_objectA->polygons[i], p_objectB->polygons[j], intersectionPoints))
					collided = true;
			}
		}
		
		if(collided) {
			CollisionEvent event(intersectionPoints, *p_objectA, *p_objectB);
			collisionHandler->collide(event);
		}
		
	}
	
	void World::setCollisionHandler(CollisionHandler *p_collisionHandler)
	{
		collisionHandler = p_collisionHandler;
	}
	
	void World::setDefaultHandler()
	{
		collisionHandler = &defaultHandler;
	}
}