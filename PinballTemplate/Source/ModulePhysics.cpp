#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"

#include "p2Point.h"

#include <math.h>


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{

	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	
	//Puntos donde empieza el pinball

	int x = 5;
	int y = 30;

	// Crea el contorno del pinball

	int points[134] = {
			0, 0,
			0, 280,
			56, 280,
			56, 278,
			21, 255,
			7, 246,
			7, 207,
			10, 200,
			16, 195,
			23, 194,
			23, 175,
			25, 169,
			28, 166,
			20, 153,
			16, 140,
			13, 126,
			11, 111,
			10, 101,
			9, 88,
			9, 15,
			12, 10,
			17, 8,
			22, 10,
			26, 16,
			26, 31,
			35, 24,
			46, 17,
			59, 12,
			73, 9,
			99, 9,
			113, 12,
			127, 17,
			138, 24,
			148, 33,
			157, 44,
			166, 58,
			171, 71,
			174, 87,
			174, 278,
			160, 278,
			160, 84,
			157, 70,
			152, 58,
			144, 46,
			136, 38,
			143, 51,
			148, 65,
			151, 77,
			151, 100,
			149, 111,
			147, 123,
			145, 133,
			143, 143,
			139, 154,
			131, 167,
			135, 170,
			137, 176,
			137, 193,
			144, 195,
			150, 200,
			153, 207,
			153, 245,
			139, 255,
			105, 278,
			105, 280,
			192, 280,
			192, 0,
	};

	CreateEdge(x, y, points, 134);


	// Crea la colision de arriba

	int upper_collision[24] = {
	39, 42,
	52, 35,
	64, 31,
	79, 29,
	94, 30,
	105, 34,
	117, 39,
	105, 29,
	89, 23,
	75, 23,
	60, 27,
	49, 33,
	
	};

	CreateEdge(x, y, upper_collision, 24);


	// Crea la colision pequeña de arriba a la izquierda

	int left_little_collision[8] = {
	67, 63,
	71, 61,
	71, 47,
	67, 49
	};

	CreateEdge(x, y, left_little_collision, 8);


	// Crea la colision pequeña de arriba a la derecha

	int right_little_collision[8] = {
		88, 57,
		94, 57,
		94, 43,
		88, 43
	};

	CreateEdge(x, y, right_little_collision, 8);


	// Crea la colision de Staryu

	int staryu_collision[32] = {
	66, 124,
	65, 116,
	61, 110,
	54, 102,
	48, 94,
	47, 83,
	50, 76,
	50, 65,
	45, 75,
	43, 83,
	43, 95,
	43, 108,
	45, 117,
	49, 125,
	55, 129,
	61, 129
	};

	CreateEdge(x, y, staryu_collision, 32);


	// Crea la colision de arriba a la izquierda

	int upper_left_collision[26] = {
	40, 150,
	34, 143,
	28, 130,
	25, 116,
	24, 104,
	25, 95,
	29, 85,
	31, 86,
	29, 97,
	29, 106,
	32, 121,
	36, 132,
	46, 145
	};

	CreateEdge(x, y, upper_left_collision, 26);


	// Crea la colision de arriba a la derecha

	int upper_right_collision[54] = {
	105, 117,
	107, 104,
	109, 91,
	110, 81,
	110, 48,
	121, 56,
	127, 63,
	132, 72,
	135, 82,
	135, 113,
	133, 126,
	129, 137,
	125, 146,
	121, 150,
	115, 144,
	121, 136,
	127, 124,
	129, 117,
	131, 105,
	131, 87,
	127, 82,
	121, 82,
	117, 88,
	116, 95,
	116, 106,
	113, 114,
	110, 121
	};

	CreateEdge(x, y, upper_right_collision, 54);


	// Crea la colision de abajo a la izquierda

	int down_left_collision[12] = {
	52, 261,
	57, 254,
	24, 232,
	24, 207,
	20, 207,
	20, 240
	};

	CreateEdge(x, y, down_left_collision, 12);


	// Crea la colision de abajo a la derecha

	int down_right_collision[12] = {
	140, 239,
	140, 207,
	136, 207,
	136, 231,
	104, 254,
	107, 261
	};

	CreateEdge(x, y, down_right_collision, 12);


	return true;
}

update_status ModulePhysics::PreUpdate()
{
	// Every update the physics world calculates positions and rotations
	world->Step(1.0f / 60.0f, 8, 3);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	

	if (IsKeyPressed(KEY_F1))
	{
		debug = !debug;
	}

	if (!debug)
	{
		return UPDATE_CONTINUE;
	}



	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					
					DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), (float)METERS_TO_PIXELS(shape->m_radius), Color{0, 0, 0, 128});
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->m_count;
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->m_vertices[i]);
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				/*case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), BLUE);
				}
				break;*/
			}

			
		}
	}

	
	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, float radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;

	b->CreateFixture(&boxFixture);
 
    PhysBody* pbody = new PhysBody();
    pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, const int* points, int size)
{
	b2Vec2* vertices = new b2Vec2[size / 2];
	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2]), PIXEL_TO_METERS(points[i * 2 + 1]));
	}

	b2BodyDef bodyDef;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&bodyDef);

	b2ChainShape chainShape;
	chainShape.CreateLoop(vertices, size / 2);

	delete[] vertices;

	b2FixtureDef fixture;
	fixture.shape = &chainShape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);
	
	PhysBody* pbody = new PhysBody();
	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateEdge(int x, int y, const int* points, int size)
{
	b2Vec2* vertices = new b2Vec2[size / 2];
	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2]), PIXEL_TO_METERS(points[i * 2 + 1]));
	}

	b2BodyDef bodyDef;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	b2Body* b = world->CreateBody(&bodyDef);

	b2EdgeShape edgeShape;

	b2FixtureDef fixture;
	fixture.shape = &edgeShape;
	fixture.density = 1.0f;


	for (int i = 0; i < (134 / 2) - 1; ++i) {

		edgeShape.SetTwoSided(vertices[i], vertices[i + 1]);
		b->CreateFixture(&fixture);
	}

	delete[] vertices;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;

	return pbody;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x);
	y = METERS_TO_PIXELS(pos.y);
}

float PhysBody::GetRotation()
{
	return body->GetAngle();
	
}