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

	

	PhysBody* body;
protected:
	
	Module* listener;
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
		
		if (y > 800) {
			printf("ghuaapsd");
			x = 300;
			y = 300;
		}
	}

private:
	Texture2D texture;

};

class Left_Flipper: public PhysicEntity
{
public:
	static constexpr int left_flipper[12] = {
	51, 260,
	51, 254,
	56, 253,
	73, 266,
	73, 268,
	71, 269
	};

	Left_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain(_x, _y, left_flipper, 12), _listener)
		, texture(_texture)
	{

	}

	void Update() override
	{
		// he pensado de hacer aqui que cuando le des a la A se rote 
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { 188, 812, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

	}

private:
	Texture2D texture;

};

class Right_Flipper : public PhysicEntity
{
public:
	static constexpr int right_flipper[12] = {
	87, 268,
	103, 253,	
	109, 254,
	109, 260,
	89, 269,
	87, 265,
	};

	Right_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain(_x, _y, right_flipper, 12), _listener)
		, texture(_texture)
	{

	}

	void Update() override
	{
		// he pensado de hacer aqui que cuando le des a la D se rote 
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { 299, 812, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

	}

private:
	Texture2D texture;

};


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
	left_flip = LoadTexture("Assets/leftFlipper.png");
	right_flip = LoadTexture("Assets/rightFlipper.png");

	/*bonus_fx = App->audio->LoadFx("Assets/bonus.wav");*/


	// Sensor rectangular que me ralla
	/*sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);*/


	entities.emplace_back(new Left_Flipper(App->physics, 5, 30, this, left_flip));

	// no va la colision del right flipper cuando la bola va por arriba pero por el lateral si, es como que se atrapa dentro de la chain y en el left flipper no pasa y es lo mismo
	entities.emplace_back(new Right_Flipper(App->physics, 5, 30, this, right_flip));

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
	//Rectangle source = { 0, 0, (float)fondo.width, (float)fondo.height }; // - Porque las coordenadas de OpenGL est�n invertidas
	//Rectangle dest = { 0, 0, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT };
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
	/*App->audio->PlayFx(bonus_fx);*/
}
