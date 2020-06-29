#include "entity.h"

void move_dir(float move_speed, Uint32 delta, float *step, float *move_axis, int *pos_axis) {
	*step = move_speed * delta;
	*move_axis += *step;
	*pos_axis = (int)*move_axis;
}

void move_x(entity_t *e, float move_speed, Uint32 delta) {
	move_dir(move_speed, delta, &(e->_x_step), &(e->move_x), &(e->pos->x));
}

void move_y(entity_t *e, float move_speed, Uint32 delta) {
	move_dir(move_speed, delta, &(e->_y_step), &(e->move_y), &(e->pos->y));
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

SDL_bool entity_intersects(entity_t *e, entity_t *other) {
	return SDL_HasIntersection(e->hitbox, other->hitbox);
}

SDL_bool entity_intersects_rect(entity_t *e, SDL_Rect *r) {
	return SDL_HasIntersection(e->hitbox, r);
}

void entity_uncollide(entity_t *e) {
	e->move_x += e->_x_step * -1;
	e->pos->x = (int) e->move_x;
	e->move_y += e->_y_step * -1;
	e->pos->y = (int) e->move_y;
}