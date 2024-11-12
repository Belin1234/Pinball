#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"

#include "p2Point.h"

#include <math.h>


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{

	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	//Puntos donde empieza el pinball

	int x = 5;
	int y = 30;


	/*CreateSpring(SCREEN_WIDTH - 30, SCREEN_HEIGHT - 100, 30, 50);*/
	// Crea el contorno del pinball



	// Crea la colision de arriba



	// Crea la colision pequeña de arriba a la izquierda



	// Crea la colision pequeña de arriba a la derecha



	// Crea la colision de Staryu




	// Crea la colision de arriba a la izquierda



	// Crea la colision de arriba a la derecha





	// Crea la colision de abajo a la izquierda






	// Crea la colision de abajo a la derecha
	//b2BodyDef bd;

	//b2Body* ground = world->CreateBody(&bd);
	/*rFlipper = nullptr;
	lFlipper = nullptr;*/
	/*lJoint = nullptr;
	rJoint = nullptr;*/
	/*leftFlipperTexture = LoadTexture("Assets/leftFlipper.png");
	rightFlipperTexture = LoadTexture("Assets/rightFlipper.png");*/

	/*Create2Flipper();*/

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	// Every update the physics world calculates positions and rotations
	world->Step(1.0f / 60.0f, 8, 3);

	for (b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if (c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			b2BodyUserData data1 = c->GetFixtureA()->GetBody()->GetUserData();
			b2BodyUserData data2 = c->GetFixtureA()->GetBody()->GetUserData();

			PhysBody* pb1 = (PhysBody*)data1.pointer;
			PhysBody* pb2 = (PhysBody*)data2.pointer;
			if (pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

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

	//if (IsKeyDown(KEY_S))
	//{
	//	// Cargas el muelle con la 'S'
	//	springJoint->SetMotorSpeed(10000.0f);
	//	springJoint->SetMaxMotorForce(10000.0f);
	//}
	//else if (IsKeyReleased(KEY_S))
	//{
	//	// Se activa el rebote cuando sueltas la 'S'
	//	springJoint->SetMotorSpeed(-10000.0f); // Velocidad de rebote hacia arriba
	//}
	//else
	//{
	//	// Desactivas el muelle si no aprietas la 'S'
	//	springJoint->SetMotorSpeed(0.0f);
	//}
	//if (IsKeyDown(KEY_A))
	//{
	//	lJoint->SetMotorSpeed(-10.0f); // Rotar a la izquierda
	//}
	//else {
	//	lJoint->SetMotorSpeed(5.0f); // Detener
	//}

	//if (IsKeyDown(KEY_D))
	//{
	//	rJoint->SetMotorSpeed(10.0f); // Rotar a la derecha
	//}
	//else
	//{
	//	rJoint->SetMotorSpeed(-5.0f); // Detener
	//}


	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch (f->GetType())
			{
				// Draw circles ------------------------------------------------
			case b2Shape::e_circle:
			{
				b2CircleShape* shape = (b2CircleShape*)f->GetShape();
				b2Vec2 pos = f->GetBody()->GetPosition();

				DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), (float)METERS_TO_PIXELS(shape->m_radius), Color{ 0, 0, 0, 128 });
			}
			break;

			// Draw polygons ------------------------------------------------
			case b2Shape::e_polygon:
			{
				b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
				int32 count = polygonShape->m_count;
				b2Vec2 prev, v;

				for (int32 i = 0; i < count; ++i)
				{
					v = b->GetWorldPoint(polygonShape->m_vertices[i]);
					if (i > 0)
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

				for (int32 i = 0; i < shape->m_count; ++i)
				{
					v = b->GetWorldPoint(shape->m_vertices[i]);
					if (i > 0)
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


			/*if (b == leftFlipper->body)
			{

				b2Vec2 pos = leftFlipper->body->GetPosition();
				Vector2 position { (float)pos.x + 168, (float)pos.y + 790 };
				Rectangle source = { 0.0f, 0.0f, (float)leftFlipperTexture.width, (float)leftFlipperTexture.height };
				Rectangle dest = { position.x, position.y, (float)leftFlipperTexture.width * SCALE, (float)leftFlipperTexture.height * SCALE };
				Vector2 origin = { 5*SCALE, leftFlipperTexture.height*SCALE*0.25};
				float rotation = b->GetAngle() * RAD2DEG - 120 * RAD2DEG;
				DrawTexturePro(leftFlipperTexture, source, dest, origin, rotation, WHITE);

			}
			else if (b == rightFlipper->body)
			{
				b2Vec2 pos = leftFlipper->body->GetPosition();
				Vector2 position { (float)pos.x + 315, (float)pos.y + 790 };
				Rectangle source = { 0.0f, 0.0f, (float)rightFlipperTexture.width, (float)rightFlipperTexture.height };
				Rectangle dest = { position.x, position.y, (float)rightFlipperTexture.width * SCALE, (float)rightFlipperTexture.height * SCALE };
				Vector2 origin = { rightFlipperTexture.width * SCALE - 5 * SCALE, rightFlipperTexture.height * SCALE * 0.25 };
				float rotation = b->GetAngle() * RAD2DEG + 120 * RAD2DEG;
				DrawTexturePro(rightFlipperTexture, source, dest, origin, rotation, WHITE);
			}*/

		}
	}


	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, float radius)
{
	PhysBody* pbody = new PhysBody();
	
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	
	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateCircle2(int x, int y, float radius)
{
	PhysBody* pbody = new PhysBody();
	
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = 2.0f;

	b->CreateFixture(&fixture);


	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	PhysBody* pbody = new PhysBody();
	
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	boxBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;

	b->CreateFixture(&boxFixture);

	
	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle2(int x, int y, int width, int height)
{
	PhysBody* pbody = new PhysBody();
	
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_staticBody;
	boxBodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	boxBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;

	b->CreateFixture(&boxFixture);

	
	pbody->body = b;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, const int* points, int size)
{
	PhysBody* pbody = new PhysBody();
	
	b2Vec2* vertices = new b2Vec2[size / 2];
	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2] * SCALE), PIXEL_TO_METERS(points[i * 2 + 1] * SCALE));
	}

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);
	
	b2Body* b = world->CreateBody(&bodyDef);

	b2ChainShape chainShape;
	chainShape.CreateLoop(vertices, size / 2);

	delete[] vertices;

	b2FixtureDef fixture;
	fixture.shape = &chainShape;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	
	pbody->body = b;



	return pbody;
}

PhysBody* ModulePhysics::CreateChain2(int x, int y, const int* points, int size)
{
	PhysBody* pbody = new PhysBody();

	b2Vec2* vertices = new b2Vec2[size / 2];
	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2] * SCALE), PIXEL_TO_METERS(points[i * 2 + 1] * SCALE));
	}

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&bodyDef);

	b2ChainShape chainShape;
	chainShape.CreateLoop(vertices, size / 2);

	delete[] vertices;

	b2FixtureDef fixture;
	fixture.shape = &chainShape;
	fixture.density = 1.0f;
	fixture.restitution = 3.0f;

	b->CreateFixture(&fixture);


	pbody->body = b;



	return pbody;
}


//PhysBody* ModulePhysics::CreateEdge(int x, int y, const int* points, int size)
//{
//	b2Vec2* vertices = new b2Vec2[size / 2];
//	for (int i = 0; i < size / 2; ++i) {
//		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2] * SCALE), PIXEL_TO_METERS(points[i * 2 + 1] * SCALE));
//	}
//
//	b2BodyDef bodyDef;
//	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
//	b2Body* b = world->CreateBody(&bodyDef);
//
//	b2EdgeShape edgeShape;
//
//	b2FixtureDef fixture;
//	fixture.shape = &edgeShape;
//	fixture.density = 1.0f;
//
//
//	for (int i = 0; i < (134 / 2) - 1; ++i) {
//
//		edgeShape.SetTwoSided(vertices[i], vertices[i + 1]);
//		b->CreateFixture(&fixture);
//	}
//
//	delete[] vertices;
//
//	PhysBody* pbody = new PhysBody();
//	pbody->body = b;
//
//	return pbody;
//}

//void ModulePhysics::Create2Flipper()
//{
//
//
//	PhysBody* Box1;
//	PhysBody* Box2;
//
//	Box1 = CreateRectangle2(176, 810, 5, 5);
//	leftFlipper = CreateRectangle(198, 810, 30, 10);
//	Box2 = CreateRectangle2(315, 810, 5, 5);
//	rightFlipper = CreateRectangle(293, 810, 30, 10);
//
//	b2RevoluteJointDef jointDef;
//	jointDef.Initialize(Box1->body, leftFlipper->body, b2Vec2(PIXEL_TO_METERS(175), PIXEL_TO_METERS(810)));
//	jointDef.enableMotor = true;
//	jointDef.motorSpeed = 0.0f;
//	jointDef.maxMotorTorque = 200.0f;
//	jointDef.enableLimit = true;
//	jointDef.lowerAngle = -25 * b2_pi / 180.0f;  // Limite inferior en radianes (-20 grados)
//	jointDef.upperAngle = 25 * b2_pi / 180.0f;   // Limite superior en radianes (20 grados)
//
//	// Crear la unión en el mundo de Box2D
//	lJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
//
//	b2RevoluteJointDef jointDefRight;
//	jointDefRight.Initialize(Box2->body, rightFlipper->body, b2Vec2(PIXEL_TO_METERS(315), PIXEL_TO_METERS(810)));
//	jointDefRight.enableMotor = true;
//	jointDefRight.motorSpeed = 0.0f;
//	jointDefRight.maxMotorTorque = 200.0f;
//	jointDefRight.enableLimit = true;
//	jointDefRight.lowerAngle = -25 * b2_pi / 180.0f;  // Limite inferior en radianes (-20 grados)
//	jointDefRight.upperAngle = 25 * b2_pi / 180.0f;   // Limite superior en radianes (20 grados)
//
//	// Crear la unión en el mundo de Box2D
//	rJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDefRight);
//
//
	//// Posiciones de los anclajes de las palas
	//b2Vec2 anchorLeft(PIXEL_TO_METERS(178), PIXEL_TO_METERS(810));
	//b2Vec2 anchorRight(PIXEL_TO_METERS(313), PIXEL_TO_METERS(810));

	//// Definir y crear los cuerpos estáticos de los anclajes
	//b2BodyDef anchorDef;
	//anchorDef.type = b2_staticBody;
	//b2Body* leftAnchor = world->CreateBody(&anchorDef);
	//b2Body* rightAnchor = world->CreateBody(&anchorDef);

	//leftAnchor->SetTransform(anchorLeft, 0);
	//rightAnchor->SetTransform(anchorRight, 0);

	//// Crear las palas con el tamaño adecuado
	//leftFlipper = CreateRectangle(METERS_TO_PIXELS(anchorLeft.x), METERS_TO_PIXELS(anchorLeft.y), 30, 10);
	//rightFlipper = CreateRectangle(METERS_TO_PIXELS(anchorRight.x), METERS_TO_PIXELS(anchorRight.y), 30, 10);

	//// Configurar los parámetros de las revolute joints para mejorar el rendimiento
	//b2RevoluteJointDef jointDef;
	//jointDef.enableMotor = true;                    // Activar el motor
	//jointDef.motorSpeed = 0.0f;                     // Velocidad inicial del motor (puedes ajustarla dinámicamente)
	//jointDef.maxMotorTorque = 200.0f;               // Ajusta el torque a un valor razonable
	//jointDef.enableLimit = true;                    // Habilitar límites para evitar giros infinitos
	//jointDef.lowerAngle = -20 * b2_pi / 180.0f;     // Limite inferior en radianes (-20 grados)
	//jointDef.upperAngle = 20 * b2_pi / 180.0f;      // Limite superior en radianes (20 grados)

	//// Conectar la pala izquierda
	//jointDef.bodyA = leftAnchor;
	//jointDef.bodyB = leftFlipper->body;
	//jointDef.localAnchorA.SetZero();
	//jointDef.localAnchorB.Set(PIXEL_TO_METERS(-30), 0);
	//lJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	//// Conectar la pala derecha
	//jointDef.bodyA = rightAnchor;
	//jointDef.bodyB = rightFlipper->body;
	//jointDef.localAnchorA.SetZero();
	//jointDef.localAnchorB.Set(PIXEL_TO_METERS(30), 0);
	//rJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	//b2BodyDef anchor
	//anchor.type = static.body

	//b2Vec2* vertices = new b2Vec2[size / 2];
	//for (int i = 0; i < size / 2; ++i) {
	//	vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2] * SCALE), PIXEL_TO_METERS(points[i * 2 + 1] * SCALE));
	//}

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	//b2Body* flipperBody = world->CreateBody(&bodyDef);


	//b2ChainShape chainShape;
	//chainShape.CreateLoop(vertices, size / 2);
	//delete[] vertices;


	//b2FixtureDef fixture;
	//fixture.shape = &chainShape;
	//fixture.density = 1.0f;
	//flipperBody->CreateFixture(&fixture);


	//b2BodyDef groundDef;
	//groundDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	//b2Body* groundBody = world->CreateBody(&groundDef);


	//b2RevoluteJointDef jointDef;
	//jointDef.bodyA = groundBody;                    
	//jointDef.bodyB = flipperBody;                     
	//jointDef.localAnchorA.Set(0, 0);                
	//jointDef.localAnchorB.Set(0, 0);                  
	//jointDef.enableMotor = true;                       
	//jointDef.motorSpeed = 0.0f;                       
	//jointDef.maxMotorTorque = 1000.0f;                
	//jointDef.enableLimit = true;                       
	//jointDef.lowerAngle = -30.0f * b2_pi / 180.0f;     
	//jointDef.upperAngle = 5.0f * b2_pi / 180.0f;       


	//b2RevoluteJoint* flipperJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);


	//PhysBody* pbody = new PhysBody();
	//pbody->body = flipperBody;
	//pbody->joint = flipperJoint;  

	/*return pbody;*/
//}

//PhysBody* ModulePhysics::CreateSpring(int posX, int posY, int springWidth, int springHeight)
//{
//	// Posicion en X del muelle
//	int adjustedX = posX - 35;
//	int adjustedY = posY + 95;
//
//	// Crear base del muelle
//	b2BodyDef baseBodyDef;
//	baseBodyDef.type = b2_staticBody;
//	baseBodyDef.position.Set(PIXEL_TO_METERS(adjustedX), PIXEL_TO_METERS(adjustedY));
//	springBase = world->CreateBody(&baseBodyDef);
//
//	// Reducir el tamaño del muelle
//	int reducedWidth = springWidth * 0.8;    // Reducir el ancho a un 80%
//	int reducedHeight = springHeight * 0.05;  // Reducir el alto a un 80%
//
//	// Crear cuerpo móvil del muelle
//	springPiston = CreateRectangle(adjustedX, adjustedY + reducedHeight / 2, reducedWidth, reducedHeight);
//
//	// Definir el prismatic joint
//	b2PrismaticJointDef prismaticJointConfig;
//	prismaticJointConfig.bodyA = springBase;
//	prismaticJointConfig.bodyB = springPiston->body;
//	prismaticJointConfig.collideConnected = false;
//	prismaticJointConfig.localAnchorA.Set(0, 0);
//	prismaticJointConfig.localAnchorB.Set(0, -PIXEL_TO_METERS(reducedHeight) / 2);
//
//	// Configurar el eje de movimiento en el eje Y
//	prismaticJointConfig.localAxisA.Set(0, 1);
//
//	// Límites de movimiento
//	prismaticJointConfig.enableLimit = true;
//	prismaticJointConfig.lowerTranslation = -PIXEL_TO_METERS(200 * 0.3f);// Límite abajo
//	prismaticJointConfig.upperTranslation = -PIXEL_TO_METERS(200 * 0.3f);// Límite arriba
//
//	// Configurar fuerza del muelle
//	prismaticJointConfig.enableMotor = true;
//	prismaticJointConfig.maxMotorForce = 10000.0f; //Fuerza del muelle
//	prismaticJointConfig.motorSpeed = 0.0f; //Velocidad inicial del muelle
//
//	// Crear el prismatic joint
//	springJoint = (b2PrismaticJoint*)world->CreateJoint(&prismaticJointConfig);
//
//	return springPiston;
//}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	PhysBody* pbody = new PhysBody();

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x) * SCALE, PIXEL_TO_METERS(y) * SCALE);
	body.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	pbody->body = b;
	pbody->width = width;
	pbody->height = height;

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

void PhysBody::GetPhysicPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x);
	y = METERS_TO_PIXELS(pos.y);
}

float PhysBody::GetRotation() const
{
	return body->GetAngle();
}

void PhysBody::SetRotation(float r)
{
	rotation = r;
}

//void PhysBody::Rotate(float angle) {
//
//	if (body) {
//		
//		b2Vec2 position = body->GetPosition();
//		float currentAngle = body->GetAngle();
//		body->SetTransform(position, currentAngle + angle);
//	}
//}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while (fixture != NULL)
	{
		if (fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = (float)(x2 - x1);
			float fy = (float)(y2 - y1);
			float dist = sqrtf((fx * fx) + (fy * fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return (int)(output.fraction * dist);
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	b2BodyUserData dataA = contact->GetFixtureA()->GetBody()->GetUserData();
	b2BodyUserData dataB = contact->GetFixtureB()->GetBody()->GetUserData();

	PhysBody* physA = (PhysBody*)dataA.pointer;
	PhysBody* physB = (PhysBody*)dataB.pointer;

	if (physA && physA->listener != NULL) {
		physA->listener->OnCollision(physA, physB);
	}


	if (physB && physB->listener != NULL) {
		physB->listener->OnCollision(physB, physA);
	}
		
}
