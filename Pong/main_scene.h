#pragma once

#include "node.h"
#include "raylib.h"
#include "paddle.h"
#include "opponent.h"
#include "ball.h"

typedef struct MainScene
{
	Node node;

	void (*base_build)(Node* node);
	void (*base_start)(Node* node);
	void (*base_update)(Node* node);

	Paddle* paddle;
	Opponent* opponent;
	Ball* ball;

}
MainScene;

MainScene* new_main_scene();