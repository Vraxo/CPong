#include "ball.h"
#include <stdlib.h>
#include "stdio.h"
#include "raymath.h"
#include "main_scene.h"
#include "paddle.h"
#include <stdlib.h>
#include <stdlib.h>

static void build(Ball* self)
{
    //printf("[Paddle built]\n");

    self->base_build(self);
}

static void start(Ball* self)
{
    printf("Ball started.\n");

    node2d_set_position(self, (Vector2) { .x = GetScreenWidth() / 2, .y = GetScreenHeight() / 2 });

    self->base_start(self);
}

static void move(Ball* self)
{
    float delta = GetFrameTime();

    float horizontal_movement = self->horizontal_speed * self->speed * delta;
    float vertical_movement = self->vertical_speed * self->speed * delta;

    Vector2 current_position = node2d_get_position(self);
    Vector2 movement_vector = (Vector2){ .x = horizontal_movement, .y = vertical_movement };
    Vector2 new_position = Vector2Add(current_position, movement_vector);

    node2d_set_position(self, new_position);
}

static void check_for_collisions_vertical(Ball* self)
{
    Vector2 global_position = node2d_get_global_position(self);

    if (global_position.y > GetScreenHeight() - node2d_get_size(self).y / 2)
    {
        self->vertical_speed = -self->vertical_speed;
    }
    else if (global_position.y < node2d_get_size(self).y / 2)
    {
        self->vertical_speed = -self->vertical_speed;
    }
}

static void check_for_collisions_horizontal(Ball* self)
{
    Vector2 global_position = Vector2Subtract(node2d_get_position(self), node2d_get_origin(self));

    if (global_position.x < 0 || global_position.x > GetScreenWidth())
    {
        node_change_scene(self, new_main_scene());
    }
}

static void check_for_collisions_paddles(Ball* self)
{
    // Get ball rectangle
    Rectangle ball_rectangle =
    {
        .x = node2d_get_position(self).x,
        .y = node2d_get_position(self).y,
        .width = node2d_get_size(self).x,
        .height = node2d_get_size(self).y,
    };

    // Get main scene and paddles
    MainScene* main_scene = self->colored_rectangle.node2d.node.program->root_node;
    Paddle* paddle = main_scene->paddle;
    Opponent* opponent = main_scene->opponent;

    // Get paddle rectangles
    Rectangle paddle_rectangle =
    {
        .x = node2d_get_position(paddle).x - node2d_get_origin(paddle).x,
        .y = node2d_get_position(paddle).y - node2d_get_origin(paddle).y,
        .width = node2d_get_size(paddle).x,
        .height = node2d_get_size(paddle).y,
    };

    Rectangle opponent_rectangle =
    {
        .x = node2d_get_position(opponent).x - node2d_get_origin(opponent).x,
        .y = node2d_get_position(opponent).y - node2d_get_origin(opponent).y,
        .width = node2d_get_size(opponent).x,
        .height = node2d_get_size(opponent).y,
    };

    // Handle collisions with paddle
    if (CheckCollisionRecs(ball_rectangle, paddle_rectangle))
    {
        self->horizontal_speed = -self->horizontal_speed;

        Vector2 movement = (Vector2){ .x = node2d_get_size(self).x / 2, 0 };
        Vector2 new_position = Vector2Add(node2d_get_position(self), movement);
        node2d_set_position(self, new_position);
    }
    
    // Handle collisions with opponent
    if (CheckCollisionRecs(ball_rectangle, opponent_rectangle))
    {
        self->horizontal_speed = -self->horizontal_speed;

        Vector2 movement = (Vector2){ .x = node2d_get_size(self).x / 2, 0 };
        Vector2 new_position = Vector2Subtract(node2d_get_position(self), movement);
        node2d_set_position(self, new_position);
    }
}

static void update(Ball* self)
{
    move(self);
    check_for_collisions_vertical(self);
    check_for_collisions_horizontal(self);
    check_for_collisions_paddles(self);

    self->base_update(self);
}


Ball* new_ball()
{
    Ball* self = malloc(sizeof(Ball));

    self->colored_rectangle = *new_colored_rectangle();

    self->base_build = self->colored_rectangle.node2d.node.build;
    self->colored_rectangle.node2d.node.build = build;

    self->base_start = self->colored_rectangle.node2d.node.start;
    self->colored_rectangle.node2d.node.start = start;

    self->base_update = self->colored_rectangle.node2d.node.update;
    self->colored_rectangle.node2d.node.update = update;

    node2d_set_size(&self->colored_rectangle.node2d, (Vector2) { .x = 32, .y = 32 });
    node2d_set_origin_preset(&self->colored_rectangle.node2d, ORIGIN_PRESET_LEFT_CENTER);

    self->colored_rectangle.roundness = 1;

    self->speed = 350;
    self->horizontal_speed = (rand() % 2 == 0) ? -1 : 1;
    self->vertical_speed = (rand() % 2 == 0) ? -1 : 1;

    return self;
}