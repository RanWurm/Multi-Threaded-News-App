//
// Created by ran on 10/10/24.
//

#ifndef NEWSAPP_SCREEN_MANAGER_H
#define NEWSAPP_SCREEN_MANAGER_H
#include "../queue/queue_list.h"
#include <pthread.h>
#include <semaphore.h>
typedef struct screenManArgs{
    pthread_mutex_t* shared_q_mutex;
    queue_list* shared;
    pthread_cond_t* shared_q_not_empty;
}screenManArgs;
void* broadcast(void* args);

#endif //NEWSAPP_SCREEN_MANAGER_H
