#pragma once

#include "program.h"

typedef struct Program Program;

typedef struct Node
{
	void (*build)(struct Node* self);
	void (*start)(struct Node* self);
	void (*update)(struct Node* self);

	char* name;
	struct Node** children;
	size_t child_count;
	Program* program;
}
Node;

Node* new_node();
void node_process(Node* node);
void node_add_child(Node* self, Node* child);
void node_change_scene(Node* self, Node* new_scene);