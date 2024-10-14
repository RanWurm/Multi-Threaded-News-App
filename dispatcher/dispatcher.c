//
// Created by ran on 10/10/24.
//

#include "dispatcher.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void* dispatch(void* args) {
    dispatcherArgs *d_a = (dispatcherArgs *) args;
    int done_cnt = 0;
    int curr = 0;
    int idle_count = 0;
    while (done_cnt < d_a->bounded_array_size) {
        int work_done = 0;
        if (pthread_mutex_trylock(d_a->mutex[curr]) == 0) {
            if (d_a->bounded_array[curr]->queue->size > 0) {
                char *news = bounded_buffer_pop((d_a->bounded_array[curr]));
                if (strcmp("DONE", news) == 0) {
                    ++done_cnt;
                } else {
                    sort_news(news, d_a);
                    //printf("%s\n", news);
                }
                pthread_cond_signal(d_a->not_full[curr]);
                work_done = 1;
                idle_count = 0;
            }
            pthread_mutex_unlock(d_a->mutex[curr]);
        }
        if (!work_done) {
            idle_count++;
            if (idle_count > d_a->bounded_array_size * 2) {
                usleep(1000);
                idle_count = 0;
            }
        }
        ++curr;
        curr = curr % (d_a->bounded_array_size);
    }
    //printf("DONE\n");
    sort_news("DONE",d_a);
    return NULL;
}


void sort_news(char* news, dispatcherArgs *d_a){
   // printf("%s\n",news);
    // Determine the topic and pass the message to the appropriate unbounded array
    if (strstr(news, "News")) {
        pthread_mutex_lock(d_a->co_editor_mutex[0]);
        add_to_queue(d_a->unbounded_Array[0], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[0]);
        pthread_mutex_unlock(d_a->co_editor_mutex[0]);
    } else if (strstr(news, "Sports")) {
        pthread_mutex_lock(d_a->co_editor_mutex[1]);
        add_to_queue(d_a->unbounded_Array[1], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[1]);
        pthread_mutex_unlock(d_a->co_editor_mutex[1]);
    } else if (strstr(news, "Weather")) {
        pthread_mutex_lock(d_a->co_editor_mutex[2]);
        add_to_queue(d_a->unbounded_Array[2], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[2]);
        pthread_mutex_unlock(d_a->co_editor_mutex[2]);
    }else if (strstr(news, "DONE")) {
        pthread_mutex_lock(d_a->co_editor_mutex[0]);
        add_to_queue(d_a->unbounded_Array[0], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[0]);
        pthread_mutex_unlock(d_a->co_editor_mutex[0]);

        pthread_mutex_lock(d_a->co_editor_mutex[1]);
        add_to_queue(d_a->unbounded_Array[1], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[1]);
        pthread_mutex_unlock(d_a->co_editor_mutex[1]);

        pthread_mutex_lock(d_a->co_editor_mutex[2]);
        add_to_queue(d_a->unbounded_Array[2], news);  // Push to News queue
        pthread_cond_signal(d_a->co_editor_not_empty[2]);
        pthread_mutex_unlock(d_a->co_editor_mutex[2]);

    }
}