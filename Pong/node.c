#include "node.h"
#include <stdlib.h>
#include "stdio.h"

void node_process(Node* self)
{
    self->update(self);

    for (size_t i = 0; i < self->child_count; i++)
    {
        node_process(self->children[i]);
    }
}

void node_add_child(Node* self, Node* child)
{
    self->children = (Node**)realloc(self->children, (self->child_count + 1) * sizeof(Node*));
    self->children[self->child_count] = child;

    child->program = self->program;

    child->start(child);
    //child->start();
    //child->build(child);
    //child->start(child);
    //child->program = node_self->program;
    //node_self->children[node_self->child_count]->parent = node_self;
    self->child_count++;
}

void node_change_scene(Node* self, Node* new_scene)
{
    self->program->root_node = new_scene;
    new_scene->program = self->program;
    new_scene->build(new_scene);
    new_scene->start(new_scene);

    //new_node->program = self->program;
    //new_node->node_build(new_node);
    //new_node->node_start(new_node);
}

static void build(Node* self)
{
    //printf("[Node built]\n");
}

static void start(Node* self)
{
    printf("Node started.");
}

static void update(Node* self)
{

}

Node* new_node()
{
    Node* self = malloc(sizeof(Node));

    self->build = build;
    self->start = start;
    self->update = update;

    self->name = "Node";
    self->children = NULL;
    self->child_count = 0;
    self->program = NULL;
    //self->program = NULL;
    //self->active = true;
    //self->children = NULL;
    //self->child_count = 0;
    //
    //self->node_build = node_build;
    //self->node_update = node_update;
    //self->node_process = node_process;
    //self->node_add_child = node_add_child;
    //self->node_remove_child = node_remove_child;

    return self;
}