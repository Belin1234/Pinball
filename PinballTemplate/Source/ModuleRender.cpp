#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = BLACK;
    score = 0; // controlar el valor desde update de game desde score de game, hay que arreglarlo
    lives = 3; // igual con lives
    camera.x = camera.y = 0;
    camera.width = SCREEN_WIDTH;
    camera.height = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
    LOG("Creating Renderer context");
    bool ret = true;

    return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{
    return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    ClearBackground(background);

    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    BeginDrawing();

    return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    DrawFPS(10, 7);

    /*DrawText(TextFormat("Score: %08i", score), 400, 10, GetFontDefault(), 1, YELLOW);*/ // Cuando tengamos la fuente se puede incorporar de momento, DrawTextEx

    EndDrawing();

    if (lives == 0)
    {
        DrawTextEx(GetFontDefault(), TextFormat("GAME OVER PRESS R TO RESTART"), Vector2{ 100, 3 }, 22, 4, YELLOW);
    }
    else {
        // Draw Score
        DrawTextEx(GetFontDefault(), TextFormat("Score: %08i", score), Vector2{ 300, 1 }, 30, 4, YELLOW);
        // Draw Lives
        DrawTextEx(GetFontDefault(), TextFormat("Lives: %i", lives), Vector2{ 140, 1 }, 30, 4, RED);
    }
    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
    return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
    background = color;
}

// Draw to screen
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, double angle, int pivot_x, int pivot_y) const
{
    bool ret = true;

    float scale = SCALE;
    Vector2 position = { (float)x, (float)y };
    Rectangle rect = { 0.f, 0.f, (float)texture.width, (float)texture.height };

    if (section != NULL) rect = *section;

    position.x = (float)(x - pivot_x) * scale + camera.x;
    position.y = (float)(y - pivot_y) * scale + camera.y;

    rect.width *= scale;
    rect.height *= scale;

    DrawTextureRec(texture, rect, position, WHITE);

    return ret;
}

bool ModuleRender::DrawText(const char* text, int x, int y, Font font, int spacing, Color tint) const
{
    bool ret = true;

    Vector2 position = { (float)x, (float)y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);

    return ret;
}
