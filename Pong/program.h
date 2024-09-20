#pragma once

#include "raylib.h"
#include "node.h"
#include "window_data.h"

typedef struct Node Node;

typedef struct Program
{
    WindowData window_data;
    Node* root_node;

    void (*run)(struct Program* self);
}
Program;

Program* new_program(WindowData window_data, Node* root_node);