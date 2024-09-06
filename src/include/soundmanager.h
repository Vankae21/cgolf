#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <raylib.h>

#define BALL_HIT_SOUND_SIZE 7

typedef struct {
	Sound ball_in_hole_sound;
	Sound button_sound;
	Sound* ball_hit_sounds;
} SoundManager;

SoundManager* init_sound_manager();
void play_ball_hit_sound(SoundManager* sman);
void play_ball_coll_sound(SoundManager* sman);
void play_ball_in_hole_sound(SoundManager* sman);

#endif