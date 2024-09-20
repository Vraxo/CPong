#include "opponent.h"
#include <stdlib.h>
#include "stdio.h"
#include "raymath.h"
#include "main_scene.h"
#include "node2d.h"

static void build(Opponent* self)
{
    self->base_build(self);
}

static void start(Opponent* self)
{
    node2d_set_position(self, (Vector2) { .x = GetScreenWidth() - node2d_get_size(self).x, .y = GetScreenHeight() / 2 });

    self->base_start(self);
}

static void update(Opponent* self)
{
    Node2D* node2d = self;

    float movement = self->speed * GetFrameTime();

    MainScene* main_scene = self->colored_rectangle.node2d.node.program->root_node;
    Node2D* ball = main_scene->ball;

    if (node2d_get_position(ball).y > node2d_get_position(self).y)
    {
        if (node2d_get_position(self).y + node2d_get_size(self).y / 2 < GetScreenHeight())
        {
            Vector2 current_position = node2d_get_position(node2d);
            Vector2 movement_vector = (Vector2){ .x = 0, .y = movement };
            Vector2 new_position = Vector2Add(current_position, movement_vector);

            node2d_set_position(self, new_position);
        }
    }

    if (node2d_get_position(ball).y < node2d_get_position(self).y)
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

Opponent* new_opponent()
{
    Opponent* self = malloc(sizeof(Opponent));

    self->colored_rectangle = *new_colored_rectangle();

    self->base_build = self->colored_rectangle.node2d.node.build;
    self->colored_rectangle.node2d.node.build = build;

    self->base_start = self->colored_rectangle.node2d.node.start;
    self->colored_rectangle.node2d.node.start = start;

    self->base_update = self->colored_rectangle.node2d.node.update;
    self->colored_rectangle.node2d.node.update = update;

    node2d_set_size(&self->colored_rectangle.node2d, (Vector2) { .x = 32, .y = 96 });
    node2d_set_origin_preset(&self->colored_rectangle.node2d, ORIGIN_PRESET_LEFT_CENTER);

    self->speed = 250;

    return self;
}