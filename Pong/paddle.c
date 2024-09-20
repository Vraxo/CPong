#include "paddle.h"
#include <stdlib.h>
#include "stdio.h"
#include "raymath.h"

static void build(Paddle* self)
{
    //printf("[Paddle built]\n");


    self->base_build(self);
}

static void start(Paddle* self)
{
    printf("Paddle started.");

    node2d_set_position(self, (Vector2) { .x = 0, .y = GetScreenHeight() / 2 });

    self->base_start(self);
}

static void update(Paddle* self)
{
    Node2D* node2d = self;

    float movement = self->speed * GetFrameTime();

    if (IsKeyDown(KEY_S))
    {
        if (node2d_get_position(self).y + node2d_get_size(self).y / 2 < GetScreenHeight())
        {
            Vector2 current_position = node2d_get_position(node2d);
            Vector2 movement_vector = (Vector2){ .x = 0, .y = movement };
            Vector2 new_position = Vector2Add(current_position, movement_vector);

            node2d_set_position(self, new_position);
        }
    }
    
    if (IsKeyDown(KEY_W))
    {
        if (node2d_get_position(self).y - node2d_get_size(self).y / 2 > 0)
        {
            Vector2 current_position = node2d_get_position(node2d);
            Vector2 movement_vector = (Vector2){ .x = 0, .y = -movement };
            Vector2 new_position = Vector2Add(current_position, movement_vector);

            node2d_set_position(self, new_position);
        }
    }

    self->base_update(self);
}

Paddle* new_paddle()
{
    Paddle* self = malloc(sizeof(Paddle));

    self->colored_rectangle = *new_colored_rectangle();

    self->base_build = self->colored_rectangle.node2d.node.build;
    self->colored_rectangle.node2d.node.build = build;

    self->base_start = self->colored_rectangle.node2d.node.start;
    self->colored_rectangle.node2d.node.start = start;

    self->base_update = self->colored_rectangle.node2d.node.update;
    self->colored_rectangle.node2d.node.update = update;

    node2d_set_size(&self->colored_rectangle.node2d, (Vector2) { .x = 32, .y = 96 });
    node2d_set_origin_preset(&self->colored_rectangle.node2d, ORIGIN_PRESET_LEFT_CENTER);

    self->speed = 500;

    return self;
}