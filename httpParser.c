#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    struct Node *next;
    char *key;
    char *value;
} Node;

typedef struct HttpContext
{
    struct Node *head;
} HttpContext;

Node *init()
{
    Node *head = (Node *)malloc(sizeof(head));
    if (head == NULL)
    {
        perror("[init malloc]");
        exit(EXIT_FAILURE);
    }
    head->next = NULL;
    return head;
}

void append(Node **head_ref, char *key, char *value)
{
    Node *node = (*head_ref);

    while (node->next != NULL)
    {
        node = node->next;
    }

    Node *new = init();
    new->key = key;
    new->value = value;

    node->next = new;
}

void display(Node **head_ref)
{
    Node *node = (*head_ref);
    while (node != NULL)
    {
        printf("%s : %s\n", node->key, node->value);
        node = node->next;
    }
}

Node *find(Node **head_ref, char *key)
{
    Node *node = (*head_ref);
    while (node->next != NULL)
    {
        node = node->next;
        if (strcmp(key, node->key) == 0)
        {
            printf("%s : %s\n", key, node->value);
            exit(EXIT_SUCCESS);
        }
    }
    printf("%s not found\n", key);
    exit(EXIT_FAILURE);
}

int main(void)
{

    char DummyData[4096] = "test: test\ntest2: test\n";
    int i = 0;
    char *p = strtok(DummyData, "\n");
    char *array[2];

    while (p != NULL)
    {
        printf("%s\n", p);
        array[i++] = p;
        p = strtok(NULL, "\n");
    }

    HttpContext httpContext;
    httpContext.head = init();
    httpContext.head->key = "key";
    httpContext.head->value = "value";

    display(&httpContext.head);
    find(&httpContext.head, "key6");
    return 0;
}