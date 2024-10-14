//
// Created by ran on 10/10/24.
//

#include "co_editor.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void* pass_to_queue(void* args) {
    //wait
    coArgs* c_a =(coArgs*)args;
    node* curr;
    char* msg = "";
    int flag = 1;

    //printf("Co-editor started\n");
    while( flag ){
        pthread_mutex_lock(c_a->co_editor_mutex);
        while(c_a->topic_q->size == 0) {
      //      printf("Co-editor waiting for items...\n");
            pthread_cond_wait(c_a->co_editor_not_empty,c_a->co_editor_mutex);
        }
        curr = pop(c_a->topic_q);
        if (curr == NULL) {
            printf("Error: Popped NULL from topic queue\n");
            pthread_mutex_unlock(c_a->co_editor_mutex);
            continue;
        }
        msg = curr->message;
        pthread_mutex_unlock(c_a->co_editor_mutex);
        //printf("Co-editor %d popped: %s\n",c_a->id, msg);
        usleep(1000);
        //printf("co editor %d tries to lock the shared_q\n",c_a->id);
        pthread_mutex_lock(c_a->shared_q_mutex);
       // printf("co editor %d aquired lock the shared_q\n",c_a->id);
        add_to_queue(c_a->shared_q,msg);
        pthread_cond_signal(c_a->shared_q_not_empty);
        pthread_mutex_unlock(c_a->shared_q_mutex);
        //printf("co editor %d add its message to sharedq\n",c_a->id);
        if(strcmp(msg,"DONE") == 0){
            flag = 0;
            free(curr);
            curr = NULL;
        }
        free(curr);
        curr = NULL;
    }
    //printf("Co-editor finished\n");

    return NULL;
}
