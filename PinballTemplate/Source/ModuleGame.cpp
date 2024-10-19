#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	fondo = LoadTexture("Assets/Fondo.png");
	pokeball = LoadTexture("Assets/pokeball.png");
	

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
	App->renderer->Draw(fondo, 5, 28);

	// TODO 4: Move all creation of bodies on 1,2,3 key press here in the scene
	if (IsKeyPressed(KEY_ONE))
	{
		bodies.push_back(App->physics->CreateCircle(GetMouseX(), GetMouseY(), 5));

	}

	

	for each (PhysBody * body in bodies)
	{
		int x, y;
		body->GetPosition(x, y);
		float degrees = body->GetRotation() * RAD2DEG;
		/*Blit(pokeball, x, y, nullptr, degrees);*/

		App->renderer->Draw(pokeball, x - pokeball.width * 0.5f, y - pokeball.height * 0.5f);
	}

	return UPDATE_CONTINUE;
}
