//
// Created by ran on 10/10/24.
//
#include "screen_manager.h"

void* broadcast(void* args) {
    screenManArgs *s_a = (screenManArgs *) args;
    int done_cnt = 0;
    int x = 0;
    while (done_cnt < 3) {
        pthread_mutex_lock(s_a->shared_q_mutex);
        while (s_a->shared->size == 0) {
            pthread_cond_wait(s_a->shared_q_not_empty, s_a->shared_q_mutex);
        }
        char *news = pop(s_a->shared)->message;
        pthread_mutex_unlock(s_a->shared_q_mutex);
        if (news == NULL) {
            continue;
        }
        if (strcmp(news, "DONE") == 0) {
            ++done_cnt;
        } else {
            printf("%s\n", news);
        }
        free(news);
        news =NULL;
    }
    printf("%d DONE\n", x);
    return NULL;
}