#include "main_scene.h"
#include <stdlib.h>
#include "stdio.h"
#include "paddle.h"
#include "ball.h"

static void build(MainScene* self)
{
    self->paddle = new_paddle();
    self->opponent = new_opponent();
    self->ball = new_ball();

    node_add_child(self, self->paddle);
    node_add_child(self, self->ball);
    node_add_child(self, self->opponent);

    self->base_build(self);
}

static void start(MainScene* self)
{
    self->base_start(self);
}

static void update(MainScene* self)
{
    self->base_update(self);
}

MainScene* new_main_scene()
{
    MainScene* self = malloc(sizeof(MainScene));

    self->node = *new_node();

    self->base_build = self->node.build;
    self->node.build = build;

    self->base_start = self->node.start;
    self->node.start = start;

    self->base_update = self->node.update;
    self->node.update = update;

    return self;
}