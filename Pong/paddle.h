#pragma once

#include "colored_rectangle.h"

typedef struct Paddle
{
	ColoredRectangle colored_rectangle;

	void (*base_build)(ColoredRectangle* node);
	void (*base_start)(ColoredRectangle* node);
	void (*base_update)(ColoredRectangle* node);

	float speed;
}
Paddle;

Paddle* new_paddle();