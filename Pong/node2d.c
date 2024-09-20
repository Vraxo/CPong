#include "node2d.h"
#include <stdlib.h>
#include "stdio.h"

static void build(Node2D* self)
{
    //printf("[Node2D built]\n");

    self->base_build(self);
}

static void start(Node2D* self)
{
    printf("Node2D started.");

    self->base_start(self);
}

static void update_origin(Node2D* self) 
{
    Vector2 size = node2d_get_size(self);

    switch (node2d_get_origin_preset(self))
    {
        case ORIGIN_PRESET_CENTER:
            node2d_set_origin(self, (Vector2){ .x = size.x / 2, .y = size.y / 2 });
            break;

        case ORIGIN_PRESET_LEFT_CENTER:
            node2d_set_origin(self, (Vector2){ .x = 0, .y = size.y / 2 });
            break;
    }
}

static void update(Node2D* self)
{
    update_origin(self);

    self->base_update(self);
}

Vector2 node2d_get_position(Node2D* self)
{
    return self->position;
}

void node2d_set_position(Node2D* self, Vector2 value)
{
    self->position = value;
}

Vector2 node2d_get_global_position(Node2D* self)
{
    return self->position;
}

void node2d_set_global_position(Node2D* self, Vector2 value)
{
    self->global_position = value;
}

Vector2 node2d_get_size(Node2D* self)
{
    return self->size;
}

void node2d_set_size(Node2D* self, Vector2 value)
{
    self->size = value;
}

Vector2 node2d_get_origin(Node2D* self)
{
    return self->origin;
}

void node2d_set_origin(Node2D* self, Vector2 value)
{
    self->origin = value;
}

OriginPreset node2d_get_origin_preset(Node2D* self)
{
    return self->origin_preset;
}

void node2d_set_origin_preset(Node2D* self, OriginPreset value)
{
    self->origin_preset = value;
}

Node2D* new_node2d()
{
    Node2D* self = malloc(sizeof(Node));

    self->node = *new_node();

    self->base_build = self->node.build;
    self->node.build = build;
    
    self->base_start = self->node.start;
    self->node.start = start;

    self->base_update = self->node.update;
    self->node.update = update;

    self->global_position = (Vector2){ .x = 0, .y = 0 };
    self->position = (Vector2){ .x = 0, .y = 0 };
    self->size = (Vector2){ .x = 32, .y = 32 };
    self->origin_preset = ORIGIN_PRESET_CENTER;

    return self;
}