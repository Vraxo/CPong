#pragma once

#include "colored_rectangle.h"

typedef struct Ball
{
	ColoredRectangle colored_rectangle;

	void (*base_build)(ColoredRectangle* node);
	void (*base_start)(ColoredRectangle* node);
	void (*base_update)(ColoredRectangle* node);

	float speed;
	float horizontal_speed;
	float vertical_speed;
}
Ball;

Ball* new_ball();