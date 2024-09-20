#pragma once

#include "node2d.h"

typedef struct ColoredRectangle
{
	Node2D node2d;

	void (*base_build)(Node2D* node);
	void (*base_start)(Node2D* node);
	void (*base_update)(Node2D* node);

	Color color;
	float roundness;
}
ColoredRectangle;

ColoredRectangle* new_colored_rectangle();