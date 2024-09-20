#pragma once

#include "node.h"
#include "raylib.h"
#include "origin_preset.h"

typedef struct Node2D Node2D;

typedef struct Node2D
{
	Node node;

	Vector2 position;
	Vector2 global_position;
	Vector2 size;
	Vector2 origin;
	OriginPreset origin_preset;

	void (*base_build)(Node* node);
	void (*base_start)(Node* node);
	void (*base_update)(Node* node);
}
Node2D;

Node2D* new_node2d();
Vector2 node2d_get_position(Node2D* self);
void node2d_set_position(Node2D* self, Vector2 value);

Vector2 node2d_get_global_position(Node2D* self);
void node2d_set_global_position(Node2D* self, Vector2 value);

Vector2 node2d_get_size(Node2D* self);
void node2d_set_size(Node2D* self, Vector2 value);

Vector2 node2d_get_origin(Node2D* self);
void node2d_set_origin(Node2D* self, Vector2 value);

OriginPreset node2d_get_origin_preset(Node2D* self);
void node2d_set_origin_preset(Node2D* self, OriginPreset value);