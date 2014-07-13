#include <UnitTest++.h>
#include <cdl/cdl.hpp>

SUITE(SimulationTests)
{
	TEST(Movement)
	{
		cdl::World world;
		std::vector<cdl::Circle> circles;
		std::vector<cdl::Polygon> polygons;
		circles.push_back(cdl::Circle(cdl::Vec2(0,0), 2));
		cdl::CollisionObject *obj = world.createObject(polygons, circles);
		
		obj->linearVelocity.set(1,1);
		
		world.step(1, 1);
		CHECK(obj->position == cdl::Vec2(1,1));
		
		world.step(1, 4);
		CHECK(obj->position == cdl::Vec2(2,2));
		
		world.destroyAllObjects();
	}
	
	class TestCollisionHandler : public cdl::CollisionHandler
	{
	public:
		cdl::CollisionObject *objA, *objB;
		bool hadCollision;
		
		TestCollisionHandler(): objA(NULL), objB(NULL), hadCollision(false) { }
		
		void collide(cdl::CollisionEvent &p_event)
		{
			hadCollision = true;
			CHECK(objA == p_event.getObjectA() || objA == p_event.getObjectB());
			CHECK(objB == p_event.getObjectA() || objB == p_event.getObjectB());
		}
	};
	
	TEST(Collision)
	{
		cdl::World world;
		std::vector<cdl::Circle> circles;
		std::vector<cdl::Polygon> polygons;
		cdl::Polygon polygon;
		TestCollisionHandler handler;
		
		circles.push_back(cdl::Circle(cdl::Vec2(0, 1), 1));
		circles.push_back(cdl::Circle(cdl::Vec2(0, -1), 1));
		
		polygon.corners.push_back(cdl::Vec2(-1, 1));
		polygon.corners.push_back(cdl::Vec2(1, 1));
		polygon.corners.push_back(cdl::Vec2(1, -1));
		polygon.corners.push_back(cdl::Vec2(-1, -1));
		
		polygons.push_back(polygon);
		
		cdl::CollisionObject *doubleCircle = world.createObject(std::vector<cdl::Polygon>(), circles);
		cdl::CollisionObject *box = world.createObject(polygons, std::vector<cdl::Circle>());
		box->position.set(-2, 0);
		doubleCircle->position.set(2, 0);
		
		world.setCollisionHandler(&handler);
		handler.objA = box;
		handler.objB = doubleCircle;
		
		handler.hadCollision = false;
		world.step(1, 1);
		CHECK(!handler.hadCollision);
		
		handler.hadCollision = false;
		doubleCircle->linearVelocity.set(-3, 0);
		world.step(1, 1);
		CHECK(handler.hadCollision);
		
		world.destroyAllObjects();
	}
}