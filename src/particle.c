#include "include/particle.h"
#include "include/game.h"
#include "include/vutils.h"
#include <stdio.h>

void update_particles(Particle** particles)
{
	for(int i = 0; i < PARTICLE_MAX_SIZE; i++) {
		Particle* p = particles[i];

		if (!p->is_active) continue;

		p->pos.x += p->dir.x * p->speed * GetFrameTime();
		p->pos.y += p->dir.y * p->speed * GetFrameTime();
		p->speed -= p->speed * GetFrameTime();

		p->live_timer += GetFrameTime();
		if (p->live_timer >= p->max_live_time) {
			deactivate_particle(p);
		}
	}
}

void draw_particles(Particle** particles)
{
	for(int i = 0; i < PARTICLE_MAX_SIZE; i++) {
		Particle* p = particles[i];

		if (!p->is_active) continue;
		DrawRectangle(p->pos.x, p->pos.y, p->side_len, p->side_len, p->color);
	}
}

void create_particles(Particle** particles,
									 size_t size_p,
									 Vector2 pos,
									 Vector2 dir,
									 Color color,
									 float speed,
									 float side_len,
									 float max_live_time)
{
	size_t activated = 0;
	for (int i = 0; i < PARTICLE_MAX_SIZE; i++) {
		Particle* p = particles[i];

		if (activated >= size_p) break;
		if (p->is_active) continue;
		
		p->pos = pos;
		float a = 0.5f;
		p->dir = xy(random_val(dir.x - a, dir.x + a), random_val(dir.y - a, dir.y + a));
		p->color = color;
		p->speed = random_val(speed/2, speed);
		p->side_len = random_val(side_len/2, side_len);
		p->max_live_time = random_val(max_live_time/2, max_live_time);
		p->is_active = true;

		activated++;
	}
}

void deactivate_particle(Particle* p)
{
	p->is_active = false;
	p->live_timer = 0;
}

void deactivate_all_particles(Particle** particles)
{
	for (int i = 0; i < PARTICLE_MAX_SIZE; i++) {
		deactivate_particle(particles[i]);
	}
}