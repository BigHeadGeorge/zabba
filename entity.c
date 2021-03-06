#include "entity.h"

void entity_init(entity_t *e, const SDL_Rect *pos, const SDL_Rect *hitbox) {
	e->pos = *pos;
	e->hitbox = *hitbox;
	e->move_x = e->pos.x;
	e->move_y = e->pos.y;
}

void move_dir(float move_speed, Uint32 delta, float *step, float *move_axis, int *pos_axis) {
	*step = move_speed * delta;
	*move_axis += *step;
	*pos_axis = (int)*move_axis;
}

void move_x(entity_t *e, float move_speed, Uint32 delta) {
	move_dir(move_speed, delta, &(e->_x_step), &(e->move_x), &(e->pos.x));
}

void move_y(entity_t *e, float move_speed, Uint32 delta) {
	move_dir(move_speed, delta, &(e->_y_step), &(e->move_y), &(e->pos.y));
}

void entity_move(entity_t *e, Uint32 delta, int dir) {
	e->_x_step = e->_y_step = 0;
	if (dir & UP)
		move_y(e, e->move_speed * -1, delta);
	if (dir & DOWN)
		move_y(e, e->move_speed, delta);
	if (dir & LEFT)
		move_x(e, e->move_speed * -1, delta);
	if (dir & RIGHT)
		move_x(e, e->move_speed, delta);
}

void entity_set_pos(entity_t *e, int x, int y) {
	e->pos.x = x;
	e->pos.y = y;
	e->move_x = x;
	e->move_y = y;
}

void entity_hitbox(entity_t *e, SDL_Rect *r) {
	*r = e->hitbox;
	r->x += e->pos.x;
	r->y += e->pos.y;
}

SDL_bool entity_intersects(entity_t *e, entity_t *other) {
	SDL_Rect other_hitbox;
	entity_hitbox(other, &other_hitbox);
	return entity_intersects_rect(e, &other_hitbox);
}

SDL_bool entity_intersects_rect(entity_t *e, SDL_Rect *r) {
	SDL_Rect hitbox;
	entity_hitbox(e, &hitbox);
	return SDL_HasIntersection(&hitbox, r);
}

void entity_uncollide(entity_t *e) {
	e->move_x += e->_x_step * -1;
	e->pos.x = (int) e->move_x;
	e->move_y += e->_y_step * -1;
	e->pos.y = (int) e->move_y;
}

void entity_disable(entity_t *e) {
	e->pos.w = e->pos.h = -1;
	e->hitbox.w = e->hitbox.h = -1;
	e->move_speed = 0.0f;
	entity_set_pos(e, -1, -1);
}

int entity_disabled(entity_t *e) {
	return e->pos.w == -1;
}
