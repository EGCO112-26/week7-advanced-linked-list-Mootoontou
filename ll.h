#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int id;
    char name[50];
    struct Node *next;
    struct Node *prev;
};

typedef struct Node node;
typedef node* NodePtr;

void insert(NodePtr *head, int id, char *name);
void deleteNode(NodePtr *head, int id);
void display(NodePtr head);
void freeAll(NodePtr *head);

#endif