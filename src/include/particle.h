#ifndef PARTICLE_H
#define PARTICLE_H

#include <raylib.h>
#include <stdlib.h>

typedef struct {
	Vector2 pos;
	Vector2 dir;
	Color color;
	float speed;
	float side_len;
	float live_timer;
	float max_live_time;
	bool is_active;
} Particle;

void update_particles(Particle** particles);
void draw_particles(Particle** particles);
void create_particles(Particle** particles,
									 size_t size_p,
									 Vector2 pos,
									 Vector2 dir,
									 Color color,
									 float speed,
									 float side_len,
									 float max_live_time);
void deactivate_particle(Particle* p);
void deactivate_all_particles(Particle** particles);

#endif