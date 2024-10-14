//
// Created by ran on 10/10/24.
//

#ifndef NEWSAPP_NEWS_RUNNER_H
#define NEWSAPP_NEWS_RUNNER_H
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>    // For O_* constants
#include <sys/stat.h> // For mode constants
#include "../bounded_buffer/bounded_buffer.h"
#include "../producer/producer.h"
#include "../dispatcher/dispatcher.h"
#include "../co_editor/co_editor.h"
#include "../screen_manager/screen_manager.h"
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

int run(int* products_num, int* queue_sizes,int size);
#endif //NEWSAPP_NEWS_RUNNER_H
