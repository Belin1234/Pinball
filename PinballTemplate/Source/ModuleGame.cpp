#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

class PhysicEntity
{
protected:

	PhysicEntity(PhysBody* _body, Module* _listener)
		: body(_body)
		, listener(_listener)
	{
		body->listener = listener;
	}

public:
	virtual ~PhysicEntity() = default;
	virtual void Update() = 0;

	virtual int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal)
	{
		return 0;
	}

	CollisionType GetCollisionType() const {
		return collisionType;
	}
	PhysBody* body;
protected:
	
	Module* listener;
	CollisionType collisionType;
};

class Perimeter : public PhysicEntity
{
	static constexpr int perimeter[134] = {
		
		192, 0,

		192, 280,
		105, 280,
		105, 278,
		139, 255,
		153, 245,
		153, 207,
		150, 200,
		144, 195,
		137, 193,
		137, 176,
		135, 170,
		131, 167,
		139, 154,
		143, 143,
		145, 133,
		147, 123,
		149, 111,
		151, 100,
		151, 77,
		148, 65,
		143, 51,
		136, 38,
		144, 46,
		152, 58,
		157, 70,
		160, 84,
		160, 278,
		174, 278,
		174, 87,
		171, 71,
		166, 58,
		157, 44,
		148, 33,
		138, 24,
		127, 17,
		113, 12,
		99, 9,
		73, 9,
		59, 12,
		46, 17,
		35, 24,
		26, 31,
		26, 16,
		22, 10,
		17, 8,
		12, 10,
		9, 15,
		9, 88,
		10, 101,
		11, 111,
		13, 126,
		16, 140,
		20, 153,
		28, 166,
		25, 169,
		23, 175,
		23, 194,
		16, 195,
		10, 200,
		7, 207,
		7, 246,
		21, 255,
		56, 278,
		56, 280,
		0, 280,
		0, 0,
	};

public:
	Perimeter(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, perimeter, 134), _listener)
	{

	}

	void Update() override {}


};

class UpperCollision : public PhysicEntity
{
	static constexpr int upper_collision[24] = {
		39, 42,
		49, 33,
		60, 27,
		75, 23,
		89, 23,
		105, 29,
		117, 39,
		105, 34,
		94, 30,
		79, 29,
		64, 31,
		52, 35
		

	};

public:
	UpperCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, upper_collision, 24), _listener)
	{

	}

	void Update() override {}


};

class LeftLittleCollision : public PhysicEntity
{
	static constexpr int left_little_collision[8] = {
		67, 63,
		67, 49,
		71, 47,
		71, 61
		

	};


public:
	LeftLittleCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, left_little_collision, 8), _listener)
	{

	}

	void Update() override {}


};

class RightLittleCollision : public PhysicEntity
{
	static constexpr int right_little_collision[8] = {
		88, 57,
		88, 43,
		94, 43,
		94, 57
		
		

	};



public:
	RightLittleCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, right_little_collision, 8), _listener)
	{

	}

	void Update() override {}

};

class StaryuCollision : public PhysicEntity
{
	static constexpr int staryu_collision[32] = {
	61, 129,
	55, 129,
	49, 125,
	45, 117,
	43, 108,
	43, 95,
	43, 83,
	45, 75,
	50, 65,
	50, 76,
	47, 83,
	48, 94,
	54, 102,
	61, 110,
	65, 116,
	66, 124
	};



public:
	StaryuCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, staryu_collision, 32), _listener)
	{

	}

	void Update() override {}

};

class UpperLeftCollision : public PhysicEntity
{
	static constexpr int upper_left_collision[26] = {
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


public:
	UpperLeftCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, upper_left_collision, 26), _listener)
	{

	}

	void Update() override {}

};

class UpperRightCollision : public PhysicEntity
{

	static constexpr int upper_right_collision[54] = {
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



public:
	UpperRightCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, upper_right_collision, 54), _listener)
	{

	}

	void Update() override {}

};

class DownLeftCollision : public PhysicEntity
{

	static constexpr int down_left_collision[12] = {
	
	24, 207,
	24, 232,
	56, 254,
	52, 261,
	20, 240,
	20, 207
	
	};



public:
	DownLeftCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, down_left_collision, 12), _listener)
	{

	}

	void Update() override {}

};

class DownRightCollision : public PhysicEntity
{

	static constexpr int down_right_collision[12] = {
	
	136, 207,
	140, 207,
	140, 239,
	108, 261,
	105, 254,
	136, 231,
	};



public:
	DownRightCollision(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain(_x, _y, down_right_collision, 12), _listener)
	{

	}

	void Update() override {}

};

class Pokeball : public PhysicEntity
{
public:
	Pokeball(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle(_x, _y, 5.4f * SCALE), _listener)
		, texture(_texture)
	{

	}

	void Update() override
	{

		// he pensado de hacer aqui lo de cuando se pase del limite que respawnee
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x, (float)y };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		
		/*if (y > 900) {
			
			delete body;
			
		}*/
	}

private:
	Texture2D texture;

};

//class Left_Flipper: public PhysicEntity
//{
//public:
//	static constexpr int left_flipper[12] = {
//	51, 260,
//	51, 254,
//	56, 253,
//	73, 266,
//	73, 268,
//	71, 269
//	};
//
//	Left_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
//		: PhysicEntity(physics->CreateRectangle(_x, _y, 30, 12), _listener)
//		, texture(_texture)
//	{
//		
//
//		PhysBody* Box1 = ModulePhysics::CreateRectangle2(176, 610, 5, 5); //-200
//		
//
//		b2RevoluteJointDef jointDef;
//		jointDef.Initialize(Box1->body, body->body, b2Vec2(PIXEL_TO_METERS(175), PIXEL_TO_METERS(610)));
//		jointDef.enableMotor = true;
//		jointDef.motorSpeed = 0.0f;
//		jointDef.maxMotorTorque = 200.0f;
//		jointDef.enableLimit = true;
//		jointDef.lowerAngle = -25 * b2_pi / 180.0f;  // Limite inferior en radianes (-20 grados)
//		jointDef.upperAngle = 25 * b2_pi / 180.0f;   // Limite superior en radianes (20 grados)
//
//		// Crear la unión en el mundo de Box2D
//	    gJoint = (b2RevoluteJoint*)body->body->GetWorld()->CreateJoint(&jointDef);
//
//	}
//
//	void Update() override
//	{
//		// he pensado de hacer aqui que cuando le des a la A se rote 
//		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
//		Rectangle dest = { 188, 812, (float)texture.width * SCALE, (float)texture.height * SCALE };
//		Vector2 origin = { ((float)texture.width * SCALE) / 2.0, ((float)texture.height * SCALE) / 2.0f };
//		float rotation = body->GetRotation() * RAD2DEG;
//
//		if (IsKeyDown(KEY_A))
//		{
//			gJoint->SetMotorSpeed(-10.0f); // Rotar a la izquierda
//		}
//		else {
//			gJoint->SetMotorSpeed(5.0f); // Detener
//		}
//		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
//
//	}
//
//private:
//	Texture2D texture;
//
//};

//class Right_Flipper : public PhysicEntity
//{
//public:
//	static constexpr int right_flipper[12] = {
//	87, 265,
//	103, 253,	
//	109, 254,
//	109, 260,
//	89, 269,
//	87, 268,
//	};
//
//	Right_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
//		: PhysicEntity(physics->CreateRectangle(_x, _y, 30, 12), _listener)
//		, texture(_texture)
//	{
//
//	}
//
//	void Update() override
//	{
//		// he pensado de hacer aqui que cuando le des a la D se rote 
//		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
//		Rectangle dest = { 299, 812, (float)texture.width * SCALE, (float)texture.height * SCALE };
//		Vector2 origin = { ((float)texture.width * SCALE) / 2.0, ((float)texture.height * SCALE) / 2.0f };
//		float rotation = body->GetRotation() * RAD2DEG;
//
//		if (IsKeyDown(KEY_D)) {
//			body->Rotate(-5.0f * DEG2RAD);
//		}
//		else {
//			/*body->Rotate(5.0f * DEG2RAD);*/
//		}
//		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
//
//	}
//
//private:
//	Texture2D texture;
//
//};


//class Box : public PhysicEntity
//{
//public:
//	Box(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
//		: PhysicEntity(physics->CreateRectangle(_x, _y, 100, 50), _listener)
//		, texture(_texture)
//	{
//
//	}
//
//	void Update() override
//	{
//		int x, y;
//		body->GetPhysicPosition(x, y);
//		DrawTexturePro(texture, Rectangle{ 0, 0, (float)texture.width, (float)texture.height },
//		Rectangle{ (float)x, (float)y, (float)texture.width, (float)texture.height },
//		Vector2{ (float)texture.width / 2.0f, (float)texture.height / 2.0f }, body->GetRotation() * RAD2DEG, WHITE);
//	}
//
//	int RayHit(vec2<int> ray, vec2<int> mouse, vec2<float>& normal) override
//	{
//		return body->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);;
//	}
//
//private:
//	Texture2D texture;
//
//};

//class Rick : public PhysicEntity
//{
//public:
//	// Pivot 0, 0
//	static constexpr int rick_head[64] = {
//			14, 36,
//			42, 40,
//			40, 0,
//			75, 30,
//			88, 4,
//			94, 39,
//			111, 36,
//			104, 58,
//			107, 62,
//			117, 67,
//			109, 73,
//			110, 85,
//			106, 91,
//			109, 99,
//			103, 104,
//			100, 115,
//			106, 121,
//			103, 125,
//			98, 126,
//			95, 137,
//			83, 147,
//			67, 147,
//			53, 140,
//			46, 132,
//			34, 136,
//			38, 126,
//			23, 123,
//			30, 114,
//			10, 102,
//			29, 90,
//			0, 75,
//			30, 62
//	};
//
//	Rick(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
//		: PhysicEntity(physics->CreateChain(GetMouseX() - 50, GetMouseY() - 100, rick_head, 64), _listener)
//		, texture(_texture)
//	{
//
//	}
//
//	void Update() override
//	{
//		int x, y;
//		body->GetPhysicPosition(x, y);
//		DrawTextureEx(texture, Vector2{ (float)x, (float)y }, body->GetRotation() * RAD2DEG, 1.0f, WHITE);
//	}
//
//private:
//	Texture2D texture;
//};

class Voltorb : public PhysicEntity
{
public:
	Voltorb(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle2(_x, _y, 6.5f * SCALE), _listener)
		, texture(_texture)
	{
		collisionType = VOLTORB;
	}

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);

		Vector2 position{ (float)x, (float)y };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

	}

private:
	Texture2D texture;

};

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	ray_on = false;
	sensed = false;
}

ModuleGame::~ModuleGame()
{}


// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	fondo = LoadTexture("Assets/Fondo.png");
	pokeball = LoadTexture("Assets/pokeball.png");
	//left_flip = LoadTexture("Assets/leftFlipper.png");
	//right_flip = LoadTexture("Assets/rightFlipper.png");
	voltorb = LoadTexture("Assets/voltorb.png");
	voltorbChocado = LoadTexture("Assets/voltorbChocado.png");

	/*bonus_fx = App->audio->LoadFx("Assets/bonus.wav");*/


	// Sensor rectangular que me ralla
	/*sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);*/

	entities.emplace_back(new Perimeter(App->physics, 5, 30, this));
	entities.emplace_back(new UpperCollision(App->physics, 5, 30, this));
	entities.emplace_back(new LeftLittleCollision(App->physics, 5, 30, this));
	entities.emplace_back(new RightLittleCollision(App->physics, 5, 30, this));
	entities.emplace_back(new StaryuCollision(App->physics, 5, 30, this));
	entities.emplace_back(new UpperLeftCollision(App->physics, 5, 30, this));
	entities.emplace_back(new UpperRightCollision(App->physics, 5, 30, this));
	entities.emplace_back(new DownLeftCollision(App->physics, 5, 30, this));
	entities.emplace_back(new DownRightCollision(App->physics, 5, 30, this));


	/*entities.emplace_back(new Left_Flipper(App->physics, 188, 812, this, left_flip));
	entities.emplace_back(new Right_Flipper(App->physics, 299, 812, this, right_flip));*/

	entities.emplace_back(new Voltorb(App->physics, 280, 260, this, voltorb));
	entities.emplace_back(new Voltorb(App->physics, 210, 297, this, voltorb));
	entities.emplace_back(new Voltorb(App->physics, 265, 350, this, voltorb));

	return ret;
}


// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	
	
	if (IsKeyPressed(KEY_ONE)) {

		entities.emplace_back(new Pokeball(App->physics, 505, 850, this, pokeball));

	}

	DrawTexturePro(fondo, Rectangle{ 0, 0, (float)fondo.width, (float)fondo.height }, Rectangle{ 5, 30, (float)fondo.width * 3, (float)fondo.height * 3 }, Vector2{ (float)0, (float)0 }, 0, WHITE);

	// TODO 4: Move all creation of bodies on 1,2,3 key press here in the scene
	if (IsKeyPressed(KEY_TWO))
	{
		entities.emplace_back(new Pokeball(App->physics, GetMouseX(), GetMouseY(), this, pokeball));


	}

	// Prepare for raycast ------------------------------------------------------

	vec2i mouse;
	mouse.x = GetMouseX();
	mouse.y = GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	vec2f normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------


	for (PhysicEntity* entity : entities)
	{
		entity->Update();
		if (ray_on)
		{
			int hit = entity->RayHit(ray, mouse, normal);
			if (hit >= 0)
			{
				ray_hit = hit;
			}
		}
	}


	// ray -----------------
	if (ray_on == true)
	{
		vec2f destination((float)(mouse.x - ray.x), (float)(mouse.y - ray.y));
		destination.Normalize();
		destination *= (float)ray_hit;

		DrawLine(ray.x, ray.y, (int)(ray.x + destination.x), (int)(ray.y + destination.y), RED);

		if (normal.x != 0.0f)
		{
			DrawLine((int)(ray.x + destination.x), (int)(ray.y + destination.y), (int)(ray.x + destination.x + normal.x * 25.0f), (int)(ray.y + destination.y + normal.y * 25.0f), Color{ 100, 255, 100, 255 });
		}
	}

	// Carga la textura y la rota pero no
	for each (PhysBody * body in bodies)
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		float degrees = body->GetRotation() * RAD2DEG;
		/*Blit(pokeball, x, y, nullptr, degrees);*/

		App->renderer->Draw(pokeball, x - pokeball.width * 0.5f, y - pokeball.height * 0.5f);

	}

	return UPDATE_CONTINUE;
}
void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	bool hascollisionwithvoltorb = false;

	int length = entities.size();
	for (int i = 0; i < length; i++)
	{
		if (bodyA == entities[i]->body && entities[i]->GetCollisionType() == VOLTORB ){
			hascollisionwithvoltorb = true;
			printf("Collision detected:       %i", score);
			break;
		}
	}
	if (hascollisionwithvoltorb) { 
		score += 500;
		
	}
	

	/*App->audio->PlayFx(bonus_fx);*/
}
