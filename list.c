#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node
{
    void *data;
    Node *next;
    Node *prev;
};

struct List
{
    Node *head;
    Node *tail;
    Node *current;
};

typedef List List;

Node *createNode(void *data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List *createList()
{
    List *new = (List *)malloc(sizeof(List));
    if (new->head == NULL)
        return NULL;
    new->head = NULL;
    new->tail = NULL;
    new->current = NULL;
    return new;
}

void *firstList(List *list)
{
    if (list->head == NULL)
        return NULL;
    list->current = list->head;
    return list->current->data;
}

void *nextList(List *list)
{
    if (list->current == NULL)
        return NULL;
    if (list->current->next == NULL)
        return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void *lastList(List *list)
{
    if (list->tail == NULL)
        return NULL;
    list->current = list->tail;
    return list->current->data;
}

void *prevList(List *list)
{
    if (list->current == NULL)
        return NULL;
    if (list->current->prev == NULL)
        return NULL;

    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List *list, void *data)
{
    Node *nuevo = createNode(data);
    if (list->head == NULL)
    {
        list->head = nuevo;
        list->tail = nuevo;
    }
    else
    {
        nuevo->next = list->head;
        list->head->prev = nuevo;
        list->head = nuevo;
    }
}

void pushBack(List *list, void *data)
{
    list->current = list->tail;
    pushCurrent(list, data);
}

void pushCurrent(List *list, void *data)
{
    Node *new = createNode(data);
    if (list->head == NULL)
    {
        list->head = new;
        list->tail = new;
    }
    else
    {
        new->next = list->current->next;
        new->prev = list->current;
        if (list->current->next != NULL)
        {
            list->current->next->prev = new;
        }
        list->current->next = new;
        if (list->current == list->tail)
        {
            list->tail = new;
        }
    }
}

void *popFront(List *list)
{
    list->current = list->head;
    return popCurrent(list);
}

void *popBack(List *list)
{
    list->current = list->tail;
    return popCurrent(list);
}

void *popCurrent(List *list)
{
    if (list->current == NULL)
        return;

    Node *toDelete = list->current;

    if (list->head == list->tail)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    else if (list->current == list->head)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
    }
    else if (list->current == list->tail)
    {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }
    else
    {
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
    }

    list->current = toDelete->next;

    free(toDelete);
}

void cleanList(List *list)
{
    while (list->head != NULL)
    {
        popFront(list);
    }
}