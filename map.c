#include <stdlib.h>
#include <stdio.h>

typedef struct map_Node
{
    char *key;
    char *value;
    struct map_Node *next;
} map_Node;

typedef struct Map
{
    struct map_Node *head;
    void (*display)(struct Map *);
    void (*append)(struct Map *, char *, char *);
    void (*find)(struct Map *, char *);
    struct Map *(*new_Map);
    struct Map *(*delete_Map);
} Map;

map_Node *init()
{
    map_Node *head = (map_Node *)malloc(sizeof(map_Node));
    if (head == NULL)
    {
        perror("[malloc]");
        exit(EXIT_FAILURE);
    }
    head->next = NULL;
    return head;
}

void append(Map *self, char *key, char *value)
{
    if ((self->head)->key == NULL)
    {
        (self->head)->key = key;
        (self->head)->value = value;
        return;
    }

    map_Node *Node = (self->head);

    while (Node->next != NULL)
    {
        Node = Node->next;
    }

    map_Node *new = init();
    new->key = key;
    new->value = value;

    Node->next = new;
    return;
}

void display(Map *self)
{
    map_Node *Node = (self->head);
    while (Node != NULL)
    {
        printf("%s:%s\n", Node->key, Node->value);
        Node = Node->next;
    }
}

void find(Map *self, char *key){
    map_Node ->

}

Map *new_Map()
{
    Map *map = (Map *)malloc(sizeof(Map));
    if (map == NULL)
    {
        perror("[Malloc]");
        exit(EXIT_FAILURE);
    }

    map->head = init();
    map->display = &display;
    map->append = &append;
    return map;
};

void delete_Map(Map *self)
{
    free(self->head);
    free(self);
};
