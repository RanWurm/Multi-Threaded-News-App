//
// Created by ran on 10/10/24.
//

#ifndef NEWSAPP_PRODUCER_H
#define NEWSAPP_PRODUCER_H
#include "../bounded_buffer/bounded_buffer.h"
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
#include <semaphore.h>

typedef struct producerArgs{
    int id;
    int prods_num;
    bounded_buffer* buff;
    pthread_mutex_t* mutex;
    pthread_cond_t* not_full;
    pthread_cond_t* not_empty;
}producerArgs;

void* createNews(void* args);

#endif //NEWSAPP_PRODUCER_H
