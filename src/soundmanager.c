#include "include/soundmanager.h"
#include <stdio.h>
#include <stdlib.h>

SoundManager* init_sound_manager()
{
	SoundManager* sman = calloc(1, sizeof(SoundManager));

	sman->ball_hit_sounds = calloc(BALL_HIT_SOUND_SIZE, sizeof(Sound));
	for (int i = 0; i < BALL_HIT_SOUND_SIZE; i++) {
		char sound_path[40];
		sprintf(sound_path, "assets/ball_hit_%d.ogg", i);
		sman->ball_hit_sounds[i] = LoadSound(sound_path);
	}
	sman->ball_in_hole_sound = LoadSound("assets/ball_in_hole.ogg");
	sman->button_sound = LoadSound("assets/blipSelect.wav");

	return sman;
}

void play_ball_hit_sound(SoundManager* sman)
{
	unsigned r = rand() % BALL_HIT_SOUND_SIZE;
	PlaySound(sman->ball_hit_sounds[r]);
}

void play_ball_coll_sound(SoundManager* sman)
{
	/*
	for s in ball_hit_sounds [
		if is playing(s) [
			skip.
		]
		play(s). stop.
	]
	*/
}

void play_ball_in_hole_sound(SoundManager* sman)
{
	if (IsSoundPlaying(sman->ball_in_hole_sound)) return;
	PlaySound(sman->ball_in_hole_sound);
}