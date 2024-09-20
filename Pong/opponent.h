#pragma once

#include "colored_rectangle.h"

typedef struct Opponent
{
	ColoredRectangle colored_rectangle;

	void (*base_build)(ColoredRectangle* node);
	void (*base_start)(ColoredRectangle* node);
	void (*base_update)(ColoredRectangle* node);

	float speed;
}
Opponent;

Opponent* new_opponent();