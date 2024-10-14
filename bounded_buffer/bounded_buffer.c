//
// Created by ran on 9/26/24.
//
#include "bounded_buffer.h"

bounded_buffer* bounded_init(int size){
    bounded_buffer* b = (bounded_buffer*) malloc(sizeof(bounded_buffer));
    if( b ==NULL){
        exit(1);
    }
    queue_list* bq = queue_init();
    b->capacity = size;
    b->queue = bq;
    return b;
}

int add(bounded_buffer* b,char* type){
    if(b->queue->size == b->capacity){
        printf(" buff capacity is %d\n" ,b->capacity);
        return -1;
    }
    add_to_queue(b->queue,type);
    return b->queue->size;
}

node* bounded_buffer_pop(bounded_buffer* b){
    if( b == 0 || b->capacity == 0){
        printf("pop return NULL\n");
        return NULL;
    }
    node* ret = pop(b->queue);
    return ret;
}

int is_full(bounded_buffer* b){
    if(b->capacity - b->queue->size == 0){
        return 1;
    }
    return 0;
}