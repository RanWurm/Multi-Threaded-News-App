//
// Created by ran on 10/10/24.
//

#ifndef NEWSAPP_DISPATCHER_H
#define NEWSAPP_DISPATCHER_H
#include "../bounded_buffer/bounded_buffer.h"
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

typedef struct dispatcherArgs{
    bounded_buffer** bounded_array;
    int bounded_array_size;
    queue_list** unbounded_Array;
    pthread_mutex_t** mutex;
    pthread_cond_t** not_full;
    pthread_cond_t** not_empty;
    pthread_mutex_t** co_editor_mutex;
    pthread_cond_t** co_editor_not_empty;
}dispatcherArgs;

void* dispatch(void* args);

void sort_news(char* news,dispatcherArgs *d_a);


#endif //NEWSAPP_DISPATCHER_H
