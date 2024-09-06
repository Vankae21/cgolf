#ifndef BUTTON_H
#define BUTTON_H
#include "raylib.h"
#include "game.h"
#include "soundmanager.h"

typedef struct Button
{
    enum
    {
        STILL,
        OVER,
        HOLD
    } state;
    Vector2 size;
    Vector2 pos;
    char* text;
    unsigned font_size;
} Button;

Button* init_button(Vector2 size, Vector2 pos, char* text, float font_size);
bool is_button_pressed(Button* button, SoundManager* sman);
void draw_button(Button* button, Font font);

#endif