#include "raylib.h"
#include "window_data.h"
#include "program.h"
#include "node2d.h"
#include "colored_rectangle.h"
#include "paddle.h"
#include "main_scene.h"

int main()
{
	WindowData window_data =
	{
		.title = "Pong",
		.resolution = (Vector2){.x = 640, .y = 480},
		.clear_color = (Color){.r = 32, .g = 32, .b = 32, .a = 255}
	};

	//Node* root_node = new_node();
	//Node2D* root_node = new_node2d();
	//ColoredRectangle* root_node = new_colored_rectangle();
	//Paddle* root_node = new_paddle();

	//Node* root_node = new_node();
	//node_add_child(root_node, new_paddle());

	MainScene* root_node = new_main_scene();

	Program* program = new_program(window_data, root_node);
	program->run(program);

	return 0;
}