//
// Created by ran on 9/26/24.
//

#ifndef NEWSAPP_QUEUE_LIST_H
#define NEWSAPP_QUEUE_LIST_H
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

typedef struct node{
    char message[100];
    struct node* next;
    struct node* prev;
}node;

typedef struct queue_list{
    node* head;
    node* last;
    int size;
}queue_list;

//inits empty queue_list
queue_list* queue_init();


node* new_node(char* message);

// returns -1 if failed 0 else
int add_to_queue(queue_list* q, char* message);
//pop the head of the queue_list
node* pop(queue_list* q);
void reverse_queue(queue_list* q);

#endif //NEWSAPP_QUEUE_LIST_H
