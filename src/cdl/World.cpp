#include "cdl/World.hpp"

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
		
	}
}