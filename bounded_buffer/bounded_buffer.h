//
// Created by ran on 9/26/24.
//

#ifndef NEWSAPP_BOUNDED_BUFFER_H
#define NEWSAPP_BOUNDED_BUFFER_H
#include "../queue/queue_list.h"


typedef struct bounded_buffer{
    int capacity;
    queue_list* queue;
}bounded_buffer;


bounded_buffer* bounded_init(int size);

//return -1 if failed else the current capacity
int add(bounded_buffer* b,char* type);
node* bounded_buffer_pop(bounded_buffer* b);
int is_full(bounded_buffer* b);


#endif //NEWSAPP_BOUNDED_BUFFER_H
