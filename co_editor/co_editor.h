//
// Created by ran on 10/10/24.
//

#ifndef NEWSAPP_CO_EDITOR_H
#define NEWSAPP_CO_EDITOR_H
#include "../queue/queue_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <fcntl.h>    // For O_* constants
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
typedef struct coArgs{
    queue_list* shared_q;
    queue_list* topic_q;
    pthread_mutex_t* shared_q_mutex;
    pthread_mutex_t* co_editor_mutex;
    pthread_cond_t* co_editor_not_empty;
    pthread_cond_t* shared_q_not_empty;
    int id;
}coArgs;
void* pass_to_queue(void* args);
#endif //NEWSAPP_CO_EDITOR_H
