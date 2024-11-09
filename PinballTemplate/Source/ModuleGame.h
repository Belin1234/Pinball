#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;

enum CollisionType
{
	DEFAULT,
	VOLTORB
};
class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	std::vector<PhysicEntity*> entities;

	PhysBody* sensor;
	bool sensed;

	Texture2D fondo;
	Texture2D pokeball;
	Texture2D leftFlipperTexture;
	Texture2D rightFlipperTexture;
	Texture2D voltorb;
	Texture2D voltorbChocado;

	int score;

	//uint32 bonus_fx;

	vec2<int> ray;
	bool ray_on;

	std::vector<PhysBody*> bodies;

};
