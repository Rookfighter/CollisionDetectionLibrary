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
	
	void World::collideObjects(CollisionObject *p_objectA, CollisionObject *p_objectB) {
		bool collided = false;
		std::vector<Vec2> intersectionPoints;
		
		std::vector<Circle> circlesA(p_objectA->circles());
		std::vector<Circle> circlesB(p_objectB->circles());
		std::vector<Polygon> polygonsA(p_objectA->polygons());
		std::vector<Polygon> polygonsB(p_objectB->polygons());
		
		// positions of circles and polygons are only reltaive, calculate abs positions
		for(int i = 0; i < circlesA.size(); ++i)
			circlesA[i].mid += p_objectA->position;
		for(int i = 0; i < circlesB.size(); ++i)
			circlesB[i].mid += p_objectB->position;
		for(int i = 0; i < polygonsA.size(); ++i) {
			for(int j = 0; j < polygonsA[i].corners.size(); ++j)
				polygonsA[i].corners[j] += p_objectA->position;
		}
		for(int i = 0; i < polygonsB.size(); ++i) {
			for(int j = 0; j < polygonsB[i].corners.size(); ++j)
				polygonsB[i].corners[j] += p_objectB->position;
		}
		
		// check for all circles of A
		for(int i = 0; i < circlesA.size(); ++i) {
			// check for all circles of B
			for(int j = 0; j < circlesB.size(); ++j) {
				if(collideCircles(circlesA[i], circlesB[j], intersectionPoints))
					collided = true;
			}
			
			// check for all polygons of B
			for(int j = 0; j < polygonsB.size(); ++j) {
				if(collideCirclePolygon(circlesA[i], polygonsB[j], intersectionPoints))
					collided = true;
			}
		}
		
		// check for all polygons of A
		for(int i = 0; i < polygonsA.size(); ++i) {
			// check for all circles of B
			for(int j = 0; j < circlesB.size(); ++j) {
				if(collideCirclePolygon(circlesB[j], polygonsA[i], intersectionPoints))
					collided = true;
			}
			
			// check for all polygons of B
			for(int j = 0; j < polygonsB.size(); ++j) {
				if(collidePolygons(polygonsA[i], polygonsB[j], intersectionPoints))
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