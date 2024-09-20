#include "program.h"
#include <stdlib.h>
#include "stdio.h"

static void run(Program* self);
static void _initialize(Program* self);
static void _run_loop(Program* self);
static void _set_current_directory(Program* self);
static void _set_window_flags();

Program* new_program(WindowData window_data, Node* root_node)
{
    Program* program = malloc(sizeof(Program));

    program->window_data = window_data;
    program->root_node = root_node;

    program->run = run;

    return program;
}

static void run(Program* self)
{
    _initialize(self);
    _run_loop(self);
}

static void _initialize(Program* self)
{
    _set_current_directory(self);
    _set_window_flags();

    int width = (int)self->window_data.resolution.x;
    int height = (int)self->window_data.resolution.y;
    char* title = self->window_data.title;

    InitWindow(width, height, title);
    //SetWindowMinSize(width, height);
    InitAudioDevice();
    SetTargetFPS(60);

    self->root_node->program = self;

    self->root_node->build(self->root_node);
    self->root_node->start(self->root_node);
    //node->program = self;
    //node->node_build(node);
    //node->node_start(node);
}

static void _run_loop(Program* self)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(self->window_data.clear_color);
        //self->root_node->update(self->root_node);

        if (self->root_node)
        {
            node_process(self->root_node);
        }
        else
        {
            printf("\nLOST FUCKING LOST");
        }
        EndDrawing();
    }
}

static void _set_current_directory(Program* self)
{
    // Implementation here if needed
}

static void _set_window_flags()
{
    SetConfigFlags(
        FLAG_VSYNC_HINT |
        FLAG_MSAA_4X_HINT |
        FLAG_WINDOW_HIGHDPI |
        FLAG_WINDOW_RESIZABLE |
        FLAG_WINDOW_ALWAYS_RUN);
}