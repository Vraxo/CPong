#include "colored_rectangle.h"
#include <stdlib.h>
#include "stdio.h"

static void build(ColoredRectangle* self)
{
    //printf("[ColoredRectangle built]\n");

    self->base_build(self);
}

static void start(ColoredRectangle* self)
{
    printf("ColoredRectangle started.");

    self->base_start(self);
}

static void update(ColoredRectangle* self)
{
    Node2D* node2d = self;

    Rectangle rectangle =
    {
        .x = node2d_get_global_position(node2d).x - node2d_get_origin(node2d).x,
        .y = node2d_get_global_position(node2d).y - node2d_get_origin(node2d).y,
        .width = node2d_get_size(node2d).x,
        .height = node2d_get_size(node2d).y,
    };

    DrawRectangleRounded(
        rectangle,
        self->roundness,
        10,
        self->color
    );

    self->base_update(self);
}

ColoredRectangle* new_colored_rectangle()
{
    ColoredRectangle* self = malloc(sizeof(ColoredRectangle));

    self->node2d = *new_node2d();

    self->base_build = self->node2d.node.build;
    self->node2d.node.build = build;

    self->base_start = self->node2d.node.start;
    self->node2d.node.start = start;

    self->base_update = self->node2d.node.update;
    self->node2d.node.update = update;
    
    self->color = WHITE;
    self->roundness = 0;

    return self;
}