#pragma once

#include "Module.h"
#include "Globals.h"

#include "box2d\box2d.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -5.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;

enum CollisionType
{
	DEFAULT,
	POKEBALL,
	VOLTORB,
	TRIANGLE,
	DIGLETT,
	PALET,
	LITTLES,
	PIKACHU,
	ENTRY
};
class PhysBody
{
public:
	PhysBody() : listener(NULL), body(NULL)
	{}

	//void GetPosition(int& x, int& y) const;
	void GetPhysicPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;
	void SetRotation(float r);
	/*void Rotate(float angle);*/
	/*CollisionType GetCollisionType() const;*/


public:

	CollisionType collisionType;
	bool hit;
	bool shouldAddScore;
	bool bonus;

	int width, height;
	float rotation;

	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	PhysBody* CreateCircle(int x, int y, float radius);
	PhysBody* CreateCircle2(int x, int y, float radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangle2(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, const int* points, int size);
	PhysBody* CreateChain2(int x, int y, const int* points, int size);
	/*PhysBody* CreateEdge(int x, int y, const int* points, int size);*/

	//void Create2Flipper();
	/*PhysBody* CreateSpring(int x, int y, int width, int height);*/
	/*PhysBody* springPiston;*/
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);

	// b2ContactListener ---
	void BeginContact(b2Contact* contact);

	/*PhysBody* leftFlipper;
	PhysBody* rightFlipper;
	b2RevoluteJoint* lJoint;
	b2RevoluteJoint* rJoint;*/

	b2World* world;
private:

	bool debug;
	//b2Body* springBase;
	//b2PrismaticJoint* springJoint;
	/*Texture2D leftFlipperTexture;
	Texture2D rightFlipperTexture;*/

};