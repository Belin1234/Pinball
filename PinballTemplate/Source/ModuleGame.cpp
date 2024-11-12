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
		117, 38,
		105, 33,
		94, 30,
		79, 29,
		64, 30,
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
	StaryuCollision(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain(_x, _y, staryu_collision, 32), _listener)
		, texture(_texture)
	{
		timer = 0.0f;
		toggle = false;

	}

	void Update() override {

		int x, y;
		body->GetPhysicPosition(x, y);
		Rectangle source;
		Vector2 position{ (float)x + 199, (float)y + 349 };
		Rectangle dest;
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;

		// Actualizar temporizador y alternar source cada 0,4 segundos
		timer += GetFrameTime();
		if (timer >= 1.2f) {
			timer = 0.0f; // Reiniciar el temporizador
			toggle = !toggle;  // Alternar entre true y false
		}

		
		if (toggle) {
			dest = { position.x, position.y, (float)texture.width * SCALE / 2, (float)texture.height * SCALE };
			source = { 0.0f, 0.0f, 21.0f, (float)texture.height - 1 };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else {
			dest = { position.x, position.y - 3, (float)texture.width * SCALE / 2, (float)texture.height * SCALE };
			source = { 21.0f, 0.0f, 21.0f, (float)texture.height - 1 };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		

	}

private:

	Texture2D texture;
	float timer;
	bool toggle;

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
	UpperRightCollision(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangleSensor(_x + 140, _y + 70, 42, 20), _listener)
		, texture(_texture)
	{
		Box = physics->CreateChain(_x, _y, upper_right_collision, 54);
		body->collisionType = PALET;
		hitTimer = 0.0f;
		timer = 0.0f;
		frameIndex = 0;
		hitOn = false;
		frameCounter = 0;
		frameTotal = 0;
		body->bonus = false;


	}

	void Update() override {
		int x = 435;
		int y = 300;
		Rectangle source;
		Vector2 position{ (float)x, (float)y };

		Rectangle dest = { position.x, position.y, 16.0f * SCALE - 3 , 16.0f * SCALE };
		Vector2 origin = { 16.0f * SCALE / 2.0f, 16.0f * SCALE / 2.0f };
		static float rotation = body->GetRotation() * RAD2DEG;

		// Detecta colisión y empieza el temporizador solo si no está en colisión y no se ha ejecutado la animación
		if (body->hit && !hitOn) {
			hitOn = true;  // Iniciamos la animación en la colisión
			hitTimer = 0.0f;  // Reiniciamos el temporizador
			frameCounter = 0;  // Reseteamos el contador de frames
		}

		// Si estamos en colisión, incrementamos la animación
		if (hitOn) {
			hitTimer += GetFrameTime();  // Incrementa el temporizador de colisión

			if (hitTimer >= 0.2f) {  // Si ha pasado suficiente tiempo (0.2 segundos)
				hitTimer = 0.0f;  // Reiniciamos el temporizador

				// Avanzamos los frames hasta alcanzar 4 frames en total
				if (frameCounter < 4) {
					frameIndex++;  // Avanzamos al siguiente frame
					frameCounter++;  // Aumentamos el contador de frames
					if (frameTotal < 16) {
						frameTotal++;
					}
				}
			}

			// Cuando hemos llegado al cuarto frame, detenemos la animación y desactivamos la colisión
			if (frameCounter >= 4) {
				body->hit = false;  // Desactivamos el estado de colisión
				hitOn = false;  // Detenemos la animación
			}

			// Si el frameIndex supera el máximo de 5 (por la cantidad de frames en la animación), lo reseteamos a 0
			if (frameIndex > 5) {
				frameIndex = 0;
			}
		}

		// Configuramos la selección del cuadro de la textura basado en frameIndex
		source = { frameIndex * 16.0f, 32.0f, 16.0f, 16.0f };

		// Dibujamos la textura en pantalla
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

		// TEXTURA RAYO: actualizamos el estado de bonus y controlamos frameTotal
		if (frameTotal == 16) {
			body->bonus = true;
		}

		// Reinicia frameTotal cuando el bonus se desactiva y la bola ha salido de la colisión
		if (!body->bonus && frameTotal >= 17) {
			frameTotal = 0;
		}

		dest = { position.x - 70, position.y - 78, 24.0f * SCALE, 32.0f * SCALE };
		source = { frameTotal * 24.0f, 0.0f, 24.0f, 32.0f };

		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}

private:

	Texture2D texture;
	PhysBody* Box;
	float hitTimer;
	float timer;
	int  frameIndex;
	bool toggle;
	bool hitOn;	
	int frameCounter;
	int frameTotal;

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

class OffCollision : public PhysicEntity
{
	static constexpr int offCollsion[22] = {
		96, 25,
		110, 27,
		124, 32,
		134, 40,
		144, 54,
		148, 70,
		149, 80,
		144, 69,
		135, 54,
		121, 40,
		107, 30
	};

public:
	OffCollision(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain(_x, _y, offCollsion, 22), _listener)
		, texture(_texture)
	{

	}

	void Update() override {
	
		int x, y;
		body->GetPhysicPosition(x, y);

		Vector2 position{ (float)x + 370, (float)y + 155 };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

	}

private:

	Texture2D texture;

};

class Pokeball : public PhysicEntity
{
public:
	Pokeball(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle(_x, _y, 5.4f * SCALE), _listener)
		, texture(_texture)
	{
		body->collisionType = POKEBALL;
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

class Left_Flipper : public PhysicEntity
{
public:
	//static constexpr int left_flipper[12] = {
	//51, 260,
	//51, 254,
	//56, 253,
	//73, 266,
	//73, 268,
	//71, 269
	//};

	Left_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangle(_x, _y, 30, 12), _listener)
		, texture(_texture)
	{

		Box1 = physics->CreateRectangle2(176, 810, 5, 5);

		b2RevoluteJointDef jointDef;
		jointDef.Initialize(Box1->body, body->body, b2Vec2(PIXEL_TO_METERS(175), PIXEL_TO_METERS(810)));
		jointDef.enableMotor = true;
		jointDef.motorSpeed = 0.0f;
		jointDef.maxMotorTorque = 200.0f;
		jointDef.enableLimit = true;
		jointDef.lowerAngle = -25 * DEG2RAD;  // Limite inferior en radianes (-20 grados)
		jointDef.upperAngle = 25 * DEG2RAD;   // Limite superior en radianes (20 grados)

		// Crear la unión en el mundo de Box2D
		leftJoint = (b2RevoluteJoint*)body->body->GetWorld()->CreateJoint(&jointDef);

	}

	void Update() override
	{
		b2Vec2 pos = body->body->GetPosition();
		Vector2 position{ (float)pos.x + 168, (float)pos.y + 790 };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { 5 * SCALE, texture.height * SCALE * 0.25 };
		float rotation = body->body->GetAngle() * RAD2DEG - 120 * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

		if (IsKeyDown(KEY_LEFT))
		{
			leftJoint->SetMotorSpeed(-10.0f); // Rotar a la izquierda
		}
		else {
			leftJoint->SetMotorSpeed(5.0f); // Detener
		}


	}

private:

	Texture2D texture;
	PhysBody* Box1;
	b2RevoluteJoint* leftJoint;

};

class Right_Flipper : public PhysicEntity
{
public:
	//static constexpr int right_flipper[12] = {
	//87, 265,
	//103, 253,	
	//109, 254,
	//109, 260,
	//89, 269,
	//87, 268,
	//};

	Right_Flipper(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangle(_x, _y, 30, 12), _listener)
		, texture(_texture)
	{
		Box2 = physics->CreateRectangle2(315, 810, 5, 5);


		b2RevoluteJointDef jointDef;
		jointDef.Initialize(Box2->body, body->body, b2Vec2(PIXEL_TO_METERS(315), PIXEL_TO_METERS(810)));
		jointDef.enableMotor = true;
		jointDef.motorSpeed = 0.0f;
		jointDef.maxMotorTorque = 200.0f;
		jointDef.enableLimit = true;
		jointDef.lowerAngle = -25 * DEG2RAD;
		jointDef.upperAngle = 25 * DEG2RAD;

		// Crear la unión en el mundo de Box2D
		rightJoint = (b2RevoluteJoint*)body->body->GetWorld()->CreateJoint(&jointDef);
	}

	void Update() override
	{
		b2Vec2 pos = body->body->GetPosition();
		Vector2 position{ (float)pos.x + 315, (float)pos.y + 789 };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { texture.width * SCALE - 5 * SCALE, texture.height * SCALE * 0.25 };
		float rotation = body->body->GetAngle() * RAD2DEG + 120 * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

		if (IsKeyDown(KEY_RIGHT))
		{
			rightJoint->SetMotorSpeed(12.5f); // Rotar a la izquierda
		}
		else {
			rightJoint->SetMotorSpeed(-5.0f); // Detener
		}


	}

private:

	Texture2D texture;
	PhysBody* Box2;
	b2RevoluteJoint* rightJoint;

};

class InvisibleSpring : public PhysicEntity
{
public:

	InvisibleSpring(ModulePhysics* physics, int _x, int _y, float _w, float _h, Module* _listener)
		: PhysicEntity(springPiston = physics->CreateRectangle(_x, _y - 3, _w, _h), _listener)
	{

		// Crear base del muelle
		springBase = physics->CreateRectangle2(_x, _y, _w, _h);

		// Definir el prismatic joint
		b2PrismaticJointDef prismaticJointConfig;
		prismaticJointConfig.bodyA = springBase->body;
		prismaticJointConfig.bodyB = springPiston->body;
		prismaticJointConfig.collideConnected = false;
		prismaticJointConfig.localAnchorA.Set(0, 0);
		prismaticJointConfig.localAnchorB.Set(0, -PIXEL_TO_METERS(_h * 0.05) / 2);

		// Configurar el eje de movimiento en el eje Y
		prismaticJointConfig.localAxisA.Set(0, 1);

		// Límites de movimiento
		prismaticJointConfig.enableLimit = true;
		prismaticJointConfig.lowerTranslation = -PIXEL_TO_METERS(200 * 0.3f);// Límite abajo
		prismaticJointConfig.upperTranslation = -PIXEL_TO_METERS(200 * 0.3f);// Límite arriba

		// Configurar fuerza del muelle
		prismaticJointConfig.enableMotor = true;
		prismaticJointConfig.maxMotorForce = 10000.0f; //Fuerza del muelle
		prismaticJointConfig.motorSpeed = 0.0f; //Velocidad inicial del muelle

		// Crear el prismatic joint
		springJoint = (b2PrismaticJoint*)physics->world->CreateJoint(&prismaticJointConfig);
	}

	void Update() override
	{
		if (IsKeyDown(KEY_DOWN))
		{
			// Cargas el muelle con la 'S'
			springJoint->SetMotorSpeed(10000.0f);
			springJoint->SetMaxMotorForce(10000.0f);
		}
		else if (IsKeyReleased(KEY_DOWN))
		{
			// Se activa el rebote cuando sueltas la 'S'
			springJoint->SetMotorSpeed(-10000.0f); // Velocidad de rebote hacia arriba
		}
		else
		{
			// Desactivas el muelle si no aprietas la 'S'
			springJoint->SetMotorSpeed(0.0f);
		}

	}

private:

	PhysBody* springPiston;
	PhysBody* springBase;
	b2PrismaticJoint* springJoint;

};

class Voltorb : public PhysicEntity
{
public:
	Voltorb(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle2(_x, _y, 6.5f * SCALE), _listener)
		, texture(_texture)
	{
		body->collisionType = VOLTORB;
		hitOn = false;
		hitTimer = 0.0f;
	}

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);

		Vector2 position{ (float)x + 24, (float)y };
		Rectangle source;
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE / 2, (float)texture.height * SCALE};
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		
		// Detecta colisión y empieza el temporizador
		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {
			hitTimer += GetFrameTime();
			if (hitTimer >= 0.3f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones
			}
		}

		// Dibuja la textura según el estado
		if (hitOn) {
			source = { 16.0f, 16.0f, 16.0f, (float)texture.height };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else {
			source = { 0.0f, 0.0f, 16.0f, (float)texture.height };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}

	}

private:
	Texture2D texture;
	bool hitOn;
	float hitTimer;

};

class LeftTriangle : public PhysicEntity
{
public:

	static constexpr int leftTriangle[6] = {
	37, 227,
	37, 209,
	50, 235
	};

	LeftTriangle(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain2(_x, _y, leftTriangle, 6), _listener)
		, texture(_texture)
	{
		body->collisionType = TRIANGLE;
		hitOn = false;
		hitTimer = 0.0f;
	}

	void Update() override
	{
		int x, y;
		x = 44 * SCALE;
		y = 233 * SCALE;
		
		Vector2 position{ (float)x, (float)y };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		Rectangle source;
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		float rotation = body->GetRotation() * RAD2DEG;

		// Detecta colisión y empieza el temporizador
		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {
			hitTimer += GetFrameTime();
			if (hitTimer >= 0.3f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones
			}
		}

		// Dibuja la textura según el estado
		if (hitOn) {
			source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else {
			source = { 0.0f, 0.0f, 0.0f, 0.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}

	}

private:
	Texture2D texture;
	bool hitOn;
	float hitTimer;

};

class RightTriangle : public PhysicEntity
{
public:

	static constexpr int rightTriangle[6] = {
	110, 235,
	123, 208,
	123, 226
	};

	RightTriangle(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain2(_x, _y, rightTriangle, 6), _listener)
		, texture(_texture)
	{
		body->collisionType = TRIANGLE;
		hitOn = false;
		hitTimer = 0.0f;
	}

	void Update() override
	{
		int x, y;
		x = 119 * SCALE;
		y = 233 * SCALE;
		
		Vector2 position{ (float)x, (float)y };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		Rectangle source;
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		float rotation = body->GetRotation() * RAD2DEG;

		// Detecta colisión y empieza el temporizador
		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {
			hitTimer += GetFrameTime();
			if (hitTimer >= 0.3f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones
			}
		}

		// Dibuja la textura según el estado
		if (hitOn) {
			source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else {
			source = { 0.0f, 0.0f, 0.0f, 0.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
	}

private:
	Texture2D texture;
	bool hitOn;
	float hitTimer;

};

class LeftDiglett : public PhysicEntity
{
public:
	LeftDiglett(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 15, 35), _listener)
		, texture(_texture)
	{
		body->collisionType = DIGLETT;
		timer = 0.0f;
		toggle = false;
		hitOn = false;
		hitTimer = 0.0f;
		body->shouldAddScore = true;
		ditrio = 0;
		body->bonus = false;
	}

	void Update() override {

		int x, y;
		body->GetPhysicPosition(x, y);
		Rectangle source;
		Vector2 position{ (float)x + 137, (float)y + 48};
		Rectangle dest;
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;

		// Actualizar temporizador y alternar source cada 0,4 segundos
		timer += GetFrameTime();
		if (timer >= 0.8f) {
			timer = 0.0f; // Reiniciar el temporizador
			toggle = !toggle;  // Alternar entre true y false
			
		}

		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
			if (ditrio < 3) {
				ditrio += 1;
			}
			else {
				ditrio = 0;
			}
			body->shouldAddScore = false;
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {
			
			hitTimer += GetFrameTime();
			if (hitTimer < 3.0f) body->shouldAddScore = false;

			if (hitTimer >= 3.0f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones
				body->shouldAddScore = true;
				if (ditrio == 3) ditrio = 0;
			}
		}

		// Diglett texture
		if (toggle && !hitOn) {
			dest = { position.x, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 0.0f, 32.0f, 16.0f, 16.0f};
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (hitOn) {
			dest = { position.x, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 32.0f, 32.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (!toggle && !hitOn){
			dest = { position.x, position.y, 16.0f * SCALE, 16.0f * SCALE};
			source = { 16.0f, 32.0f, 16.0f, 16.0f};
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}


		// Ditrio texture
		if (ditrio == 0) {
			dest = { position.x - 72, position.y-24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 0.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 1) {
			dest = { position.x - 72, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 24.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 2) {
			body->bonus = true;
			dest = { position.x - 72, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 48.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 3) {

			dest = { position.x - 72, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 72.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}


	}

private:

	Texture2D texture;
	float timer;
	float hitTimer;
	int ditrio;
	bool bonus;
	bool toggle;
	bool hitOn;

};

class RightDiglett : public PhysicEntity
{
public:
	RightDiglett(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 15, 35), _listener)
		, texture(_texture)
	{
		body->collisionType = DIGLETT;
		timer = 0.0f;
		toggle = false;
		hitOn = false;
		hitTimer = 0.0f;
		body->shouldAddScore = true;
		ditrio = 0;
		body->bonus = false;
	}

	void Update() override {

		int x, y;
		body->GetPhysicPosition(x, y);
		Rectangle source;
		Vector2 position{ (float)x + 137, (float)y + 48 };
		Rectangle dest;
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;

		// Actualizar temporizador y alternar source cada 0,4 segundos
		timer += GetFrameTime();
		if (timer >= 0.8f) {
			timer = 0.0f; // Reiniciar el temporizador
			toggle = !toggle;  // Alternar entre true y false

		}

		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
			if (ditrio < 3) {
				ditrio += 1;
			}
			else {
				ditrio = 0;
			}
			body->shouldAddScore = false;
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {

			hitTimer += GetFrameTime();
			if (hitTimer < 3.0f) body->shouldAddScore = false;

			if (hitTimer >= 3.0f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones
				body->shouldAddScore = true;
				if (ditrio == 3) ditrio = 0;
			}
		}

		// Diglett texture
		if (toggle && !hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 0.0f, 32.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 32.0f, 32.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (!toggle && !hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 16.0f, 32.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}


		// Ditrio texture
		if (ditrio == 0) {
			dest = { position.x + 12, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 0.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 1) {
			dest = { position.x + 12, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 24.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 2) {
			body->bonus = true;
			dest = { position.x + 12, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 48.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (ditrio == 3) {

			dest = { position.x + 12, position.y - 24, 24.0f * SCALE, 32.0f * SCALE };
			source = { 72.0f, 0.0f, 24.0f, 32.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}

	}

private:

	Texture2D texture;
	float timer;
	float hitTimer;
	int ditrio;
	bool bonus;
	bool toggle;
	bool hitOn;

};

class Bellsprout : public PhysicEntity
{

	static constexpr int mouthCollision[8] = {
	117, 87,
	120, 83,
	127, 83,
	130, 87
	};

public:
	Bellsprout(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 40, 10), _listener)
		, texture(_texture)
	{
		body->collisionType = BELLSPROUT;
		timer = 0.0f;
		toggle = false;
		hitOn = false;
		hitTimer = 0.0f;
		body->bonus = false;
		
	}

	void Update() override {

		int x = 435;
		int y = 300;
		Rectangle source;
		Vector2 position{ (float)x, (float)y };
		Rectangle dest = { position.x, position.y, 16.0f * SCALE - 3 , 16.0f * SCALE };
		Vector2 origin = { 16.0f * SCALE / 2.0f, 16.0f * SCALE / 2.0f };
		static float rotation = body->GetRotation() * RAD2DEG;

		// Actualizar temporizador y alternar source cada 0,4 segundos
		timer += GetFrameTime();
		if (timer >= 1.0f) {
			timer = 0.0f; // Reiniciar el temporizador
			toggle = !toggle;  // Alternar entre true y false

		}

		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {

			hitTimer += GetFrameTime();

			if (hitTimer >= 1.5f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones

			}
		}

		if (toggle && !body->bonus) { 
			dest = { position.x - 94, position.y - 4, 27.0f * SCALE, 35.0f * SCALE };
			source = { 0.0f, 48.0f, 27.0f, 35.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (body->bonus) {
			dest = { position.x - 94, position.y - 4, 27.0f * SCALE, 35.0f * SCALE };
			source = { 54.0f, 48.0f, 27.0f, 35.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (!toggle && !body->bonus) { 
			dest = { position.x - 94, position.y - 4, 27.0f * SCALE, 35.0f * SCALE };
			source = { 27.0f, 48.0f, 27.0f, 35.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}

		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);


	}

private:

	Texture2D texture;
	float timer;
	float hitTimer;
	bool toggle;
	bool hitOn;

};

class BellsproutMouth : public PhysicEntity
{

	static constexpr int mouthCollision[8] = {
	117, 87,
	120, 83,
	127, 83,
	130, 87
	};

public:
	BellsproutMouth(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateChain2(_x, _y, mouthCollision, 8), _listener)
	{
		body->collisionType = BELLSPROUT_MOUTH;
		body->hit = false;

	}

	void Update() override {}

};


class Pikachu : public PhysicEntity
{

	static constexpr int pikachuCollision[8] = {
		7, 240,
		20, 240,
		20, 260,
		7, 260
	};

public:
	Pikachu(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D _texture)
		: PhysicEntity(physics->CreateChain2(_x, _y, pikachuCollision, 8), _listener)
		, texture(_texture)
	{
		body->collisionType = PIKACHU;
		timer = 0.0f;
		toggle = false;
		hitOn = false;
		hitTimer = 0.0f;
		currentFrame = 0;
		hitFrameTimer = 0.0f;
		body->bonus = false;
	}

	void Update() override {

		int x, y;
		body->GetPhysicPosition(x, y);
		Rectangle source;
		Vector2 position{ (float)x + 156, (float)y + 770 };
		Rectangle dest;
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;

		// Actualizar temporizador y alternar source cada 0,4 segundos
		timer += GetFrameTime();
		if (timer >= 0.8f) {
			timer = 0.0f; // Reiniciar el temporizador
			toggle = !toggle;  // Alternar entre true y false

		}

		if (body->hit && !hitOn) {
			hitOn = true;
			hitTimer = 0.0f; // Reinicia el temporizador en la colisión
			
		}

		// Incrementa el temporizador si está en estado "hit"
		if (hitOn) {

			hitTimer += GetFrameTime();
			hitFrameTimer += GetFrameTime();

			if (hitFrameTimer >= 0.5f) {
				hitFrameTimer = 0.0f;
				currentFrame++; // Alterna entre 4 frames
			}

			if (hitTimer >= 2.0f) { // Después de 0.3 segundos, vuelve a la textura normal
				hitOn = false;
				body->hit = false; // Reinicia `body->hit` para futuras colisiones

			}
		}

		// Diglett texture
		if (toggle && !hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 0.0f, 0.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}
		else if (hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 32.0f, 0.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
			
			dest = { position.x - 40, position.y - 30, 16.0f * SCALE, 16.0f * SCALE };
			source = { currentFrame * 16.0f, 16.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);

		}
		else if (!toggle && !hitOn) {
			dest = { position.x - 36, position.y, 16.0f * SCALE, 16.0f * SCALE };
			source = { 16.0f, 0.0f, 16.0f, 16.0f };
			DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
		}

	}

private:

	Texture2D texture;
	float timer;
	float hitTimer;
	int ditrio;
	bool bonus;
	bool toggle;
	bool hitOn;
	int currentFrame;
	float hitFrameTimer;

};

class LittlePoints : public PhysicEntity
{
public:
	LittlePoints(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 15, 15), _listener)
		
	{
		body->collisionType = LITTLES;

	}

	void Update() override {}

};

class EntrySensor : public PhysicEntity
{
public:
	EntrySensor(ModulePhysics* physics, int _x, int _y, Module* _listener)
		: PhysicEntity(physics->CreateRectangleSensor(_x, _y, 15, 15), _listener)

	{
		body->collisionType = ENTRY;

	}

	void Update() override {}

};

class DittoOpen : public PhysicEntity
{
	static constexpr int ditto1[12] = {
	9, 73,
	2, 19,
	29, 30,
	21, 39,
	14, 52,
	10, 64
	};

public:
	DittoOpen(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D texture)
		: PhysicEntity(physics->CreateChain(_x, _y, ditto1, 12), _listener)
		, texture(texture)

	{
		

	}

	void Update() override {
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x + 45, (float)y + 140 };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height-0.5};
		Rectangle dest = { position.x, position.y, (float)texture.width * SCALE, (float)texture.height * SCALE };
		Vector2 origin = { ((float)texture.width * SCALE) / 2.0f, ((float)texture.height * SCALE) / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;

		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	

	}
private:
	Texture2D texture;
};

class DittoClosed : public PhysicEntity
{
	static constexpr int ditto2[14] = {
	9, 94,
	4, 25,
	40, 42,
	31, 49,
	23, 58,
	16, 69,
	11, 82
	};

public:
	DittoClosed(ModulePhysics* physics, int _x, int _y, Module* _listener, Texture2D texture)
		: PhysicEntity(physics->CreateChain(_x, _y, ditto2, 14), _listener)
		, texture(texture)

	{


	}

	void Update() override {
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x + 65, (float)y + 185 };
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height - 0.5 };
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
	leftFlipperTexture = LoadTexture("Assets/leftFlipper.png");
	rightFlipperTexture = LoadTexture("Assets/rightFlipper.png");
	voltorb = LoadTexture("Assets/Voltorb.png");
	leftTriangleOn = LoadTexture("Assets/LeftTriangleOn.png");
	rightTriangleOn = LoadTexture("Assets/RightTriangleOn.png");
	offCollisionT = LoadTexture("Assets/OffCollision.png");
	staryu = LoadTexture("Assets/Staryu.png");
	leftDiglettT = LoadTexture("Assets/LeftDiglett.png");
	rightDiglettT = LoadTexture("Assets/RightDiglett.png");
	upperRight = LoadTexture("Assets/UpperRight.png");
	pikachu = LoadTexture("Assets/Pikachu.png");
	ditto1 = LoadTexture("Assets/Ditto1.png");
	ditto2 = LoadTexture("Assets/Ditto2.png");

	bonus_fx = App->audio->LoadFx("Assets/bonus.wav");
	if (App != nullptr && App->audio != nullptr) {
		bonus_fx = App->audio->LoadFx("path_to_sound_file.wav");
		if (bonus_fx != 0) {
			if (!App->audio->PlayFx(bonus_fx)) {
				printf("Error: No se pudo reproducir el sonido.");
			}
		}
		else {
			printf("Error: El sonido no se cargó correctamente.");
		}
	}
	else {
		printf("Error: App o App->audio no están inicializados.");
	}

	musica = LoadMusicStream("Assets/music.ogg");
	PlayMusicStream(musica);

	// Sensor rectangular que me ralla
	/*sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);*/

	entities.emplace_back(new Perimeter(App->physics, 5, 30, this));
	entities.emplace_back(new UpperCollision(App->physics, 5, 30, this));
	entities.emplace_back(new LeftLittleCollision(App->physics, 5, 30, this));
	entities.emplace_back(new RightLittleCollision(App->physics, 5, 30, this));
	entities.emplace_back(new StaryuCollision(App->physics, 5, 30, this, staryu));
	entities.emplace_back(new UpperLeftCollision(App->physics, 5, 30, this));
	entities.emplace_back(new UpperRightCollision(App->physics, 5, 30, this, upperRight));
	entities.emplace_back(new Bellsprout(App->physics, 125, 97, this, upperRight));
	
	entities.emplace_back(new DownLeftCollision(App->physics, 5, 30, this));
	entities.emplace_back(new DownRightCollision(App->physics, 5, 30, this));

	entities.emplace_back(new InvisibleSpring(App->physics, 506, 862, 20, 2, this));

	entities.emplace_back(new Left_Flipper(App->physics, 198, 810, this, leftFlipperTexture));
	entities.emplace_back(new Right_Flipper(App->physics, 293, 810, this, rightFlipperTexture));

	entities.emplace_back(new Voltorb(App->physics, 280, 260, this, voltorb));
	entities.emplace_back(new Voltorb(App->physics, 210, 297, this, voltorb));
	entities.emplace_back(new Voltorb(App->physics, 265, 350, this, voltorb));

	entities.emplace_back(new LeftTriangle(App->physics, 5, 30, this, leftTriangleOn));
	entities.emplace_back(new RightTriangle(App->physics, 5, 30, this, rightTriangleOn));

	entities.emplace_back(new LeftDiglett(App->physics, 28, 192, this, leftDiglettT));
	entities.emplace_back(new RightDiglett(App->physics, 136, 192, this, rightDiglettT));

	entities.emplace_back(new EntrySensor(App->physics, 9, 96, this));

	// Littles
	entities.emplace_back(new LittlePoints(App->physics, 39, 93, this));
	entities.emplace_back(new LittlePoints(App->physics, 40, 127, this));
	entities.emplace_back(new LittlePoints(App->physics, 20, 117, this));
	entities.emplace_back(new LittlePoints(App->physics, 144, 117, this));
	entities.emplace_back(new LittlePoints(App->physics, 148, 229, this));
	entities.emplace_back(new LittlePoints(App->physics, 132, 229, this));
	entities.emplace_back(new LittlePoints(App->physics, 16, 229, this));
	entities.emplace_back(new LittlePoints(App->physics, 32, 229, this));
	entities.emplace_back(new LittlePoints(App->physics, 30, 55, this));
	entities.emplace_back(new LittlePoints(App->physics, 43, 63, this));
	entities.emplace_back(new LittlePoints(App->physics, 135, 55, this));
	entities.emplace_back(new LittlePoints(App->physics, 126, 63, this));
	entities.emplace_back(new LittlePoints(App->physics, 104, 68, this));
	entities.emplace_back(new LittlePoints(App->physics, 82, 67, this));
	entities.emplace_back(new LittlePoints(App->physics, 60, 78, this));

	/*entities.emplace_back(new OffCollision(App->physics, 5, 30, this, offCollisionT));*/

	score = 0;
	lives = 3;
	offCollision = false;
	left = true;
	timer = 0.0f;
	hitPika = false;
	inside = false;
	inMouth = false;
	power = false;
	
	
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
	UpdateMusicStream(musica);   // Se reproduce la música

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

	//for (auto entity : entities) {
	//	// Intentar hacer cast a Bellsprout y UpperRightCollision
	//	auto bellsprout = dynamic_cast<Bellsprout*>(entity);
	//	auto upperRightCollision = dynamic_cast<UpperRightCollision*>(entity);
	//	

	//	if (bellsprout && upperRightCollision) {
	//		// Verificar las condiciones para crear BellsproutMouth
	//		if (bellsprout->body->hit && upperRightCollision->body->bonus) {
	//			// Crear la entidad BellsproutMouth si aún no existe
	//			if (!bellsproutMouth) {
	//				bellsproutMouth = new BellsproutMouth(App->physics, 5, 30, this);
	//				entities.push_back(bellsproutMouth);
	//			}
	//		}

	//		// Verificar las condiciones para eliminar BellsproutMouth
	//		if (bellsproutMouth && bellsproutMouth->body->hit) {
	//			// Eliminar BellsproutMouth y reiniciar los estados de hit y bonus
	//			auto it = std::find(entities.begin(), entities.end(), bellsproutMouth);
	//			if (it != entities.end()) {
	//				entities.erase(it);
	//				delete bellsproutMouth;
	//				bellsproutMouth = nullptr;
	//			}
	//			bellsprout->body->hit = false;
	//			upperRightCollision->body->bonus = false;
	//		}
	//	}
	//}


	// Ditto movement
	// Eliminar la entidad previa si existe
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		// Si la entidad es de tipo DittoOpen o DittoClosed, se elimina
		if (dynamic_cast<DittoOpen*>(*it) || dynamic_cast<DittoClosed*>(*it)) {
			// Asegúrate de que 'body' es un puntero al cuerpo de Box2D
			if ((*it)->body != nullptr) {
				// Destruir el cuerpo físico asociado
				App->physics->world->DestroyBody((*it)->body->body);  // 'body->body' es el cuerpo físico de Box2D
			}

			// Eliminar la entidad y sus recursos
			delete* it;  // Eliminar la entidad
			entities.erase(it);  // Eliminarla del vector
			break;  // Salir del ciclo, ya que solo hay una instancia
		}
	}

	// Agregar la nueva entidad según el estado de "inside"
	if (!inside) {
		entities.emplace_back(new DittoOpen(App->physics, 5, 30, this, ditto1));
	}
	else {
		entities.emplace_back(new DittoClosed(App->physics, 5, 30, this, ditto2));
	}



	// Pikachu movement
    // Actualiza el temporizador
	timer += GetFrameTime();

	// Verifica si han pasado los 2 segundos
	if (timer >= 2.0f) {
		// Reinicia el temporizador
		timer = 0.0f;

		// Busca y elimina la entidad Pikachu actual en entities
		for (auto it = entities.begin(); it != entities.end(); ++it) {
			if (Pikachu* pikachuEntity = dynamic_cast<Pikachu*>(*it)) {  // Verifica si es un objeto Pikachu
				// Elimina el cuerpo físico de Box2D
				App->physics->world->DestroyBody(pikachuEntity->body->body);

				// Libera la memoria de la entidad completa
				delete* it;
				entities.erase(it);  // Elimina el puntero del vector
				break;  // Sale del bucle tras encontrar y borrar el último Pikachu
			}
		}

		// Alterna la posición de Pikachu y crea un nuevo objeto
		if (left) {
			entities.emplace_back(new Pikachu(App->physics, 5, 30, this, pikachu));
		}
		else {
			entities.emplace_back(new Pikachu(App->physics, 397, 30, this, pikachu));
		}
		left = !left;  // Cambia el estado de la variable left
	}

	if (inMouth && power) {
		entities.emplace_back(new BellsproutMouth(App->physics, 5, 30, this));
		inMouth = false;
		power = false;
	}
	for (auto it = entities.begin(); it != entities.end(); ++it) {
		if (BellsproutMouth* bellsproutMouth = dynamic_cast<BellsproutMouth*>(*it)) {  // Verifica si es un objeto Pikachu
			if (bellsproutMouth->body->hit) {
				App->physics->world->DestroyBody(bellsproutMouth->body->body);

				// Libera la memoria de la entidad completa
				delete* it;
				entities.erase(it);  // Elimina el puntero del vector
				break;  
			}
			
		}
	}
	


	// Pokeball and offCollision behaviour
for (int i = 0; i < entities.size(); ++i)
{
    int x, y;
    entities[i]->body->GetPhysicPosition(x, y);

    // Si la entidad es una Pokeball
    if (entities[i]->body->collisionType == POKEBALL)
    {
        if (x < 450 && !offCollision) {
            entities.emplace_back(new OffCollision(App->physics, 5, 30, this, offCollisionT));
            offCollision = true;
        }

        if (y > 900) {
            // Eliminar la Pokeball
            delete entities[i];
            entities[i] = nullptr;
            inside = false;

            if (lives > 0)
            {
                entities.emplace_back(new Pokeball(App->physics, 505, 850, this, pokeball));
                printf("ANTES: %i", lives);
                lives -= 1;
                App->renderer->lives = lives;
                printf("LUEGO: %i", lives);
            }
            else
            {
                lives = 0;
            }
        }

    }

}

	// Limpia los nullptr después del bucle
	entities.erase(remove(entities.begin(), entities.end(), nullptr), entities.end());

	return UPDATE_CONTINUE;
}
void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB) {
	
	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == VOLTORB)) {
		bodyB->hit = true;
		App->renderer->score += 300;
		App->audio->PlayFx(bonus_fx);
	}

	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == TRIANGLE)) {
		bodyB->hit = true;
		App->renderer->score += 200;
		App->audio->PlayFx(bonus_fx);
	}

	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == DIGLETT)) {
		if (bodyB->shouldAddScore) {  // Verifica si se deben sumar puntos
			bodyB->hit = true;
			App->renderer->score += 1000;
			App->audio->PlayFx(bonus_fx);
			if (bodyB->bonus) {
				App->renderer->score += 6000;
				bodyB->bonus = false;
			}
		}
		
	}

	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == PALET)) {
		bodyB->hit = true;
		App->renderer->score += 400;
		if (bodyB->bonus) {
			power = true;
			if (!power) {
				bodyB->bonus = false;
			}
			
		}
	}
	
	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == PIKACHU)) {
		bodyB->hit = true;
		App->renderer->score += 1500;

	}
	
	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == LITTLES)) {
		bodyB->hit = true;
		App->renderer->score += 100;

	}

	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == ENTRY)) {
		inside = true;
	

	}

	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == BELLSPROUT)) {
		bodyB->hit = true;
		inMouth = bodyB->hit;

	}
	
	if ((bodyA->collisionType == POKEBALL && bodyB->collisionType == BELLSPROUT_MOUTH)) {
		bodyB->hit = true;
		


	}

	


}
