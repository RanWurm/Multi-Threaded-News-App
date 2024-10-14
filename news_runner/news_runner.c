//
// Created by Ran on 10/10/24.
//
#include "news_runner.h"
queue_list** topicsArray;
bounded_buffer** producers_buffers;
queue_list* shared_q;

pthread_t* prod_threads;
pthread_t* co_editor_threads;
pthread_t dispatch_thread;
pthread_t screen_manager_thread;

pthread_mutex_t** buffers_mutex;
pthread_cond_t** buffers_not_full;
pthread_cond_t** buffers_not_empty;

pthread_mutex_t** co_editors_mutex;
pthread_cond_t** co_editors_not_empty;

pthread_mutex_t* shared_q_mutex;
pthread_cond_t* shared_q_not_empty;

void init_topics_array();
void init_producers_arrays(int buffer_nums,int* buffer_sizes);
void init_shared_q();
void init_prod_threads_array(int producer_num);
void init_news(int producers_num, int* queue_sizes);
void init_locks(int buffer_num);
void join_all_threads(int num_producers);
int call_producers(int size,int* products_num);
int call_dispatcher(int size);
int call_co_editors();
int call_screen_manager();
void init_co_editor_array();
void free_memory(int size);

int run(int* products_num, int* queue_sizes,int size) {
    printf("Initialize Buffers...\n");
    sleep(1);
    printf("creating the Producers...\n");
    sleep(1);
    printf("creating the Dispatcher...\n");
    sleep(1);
    printf("creating Co-editors...\n");
    sleep(1);
    printf("Initialize Screen-Manager...\n");
    sleep(1);
    printf("Starting the News!...\n");
    sleep(1);
    init_news(size, queue_sizes);
    call_producers(size, products_num);
    call_dispatcher(size);
    call_co_editors();
    call_screen_manager();
    join_all_threads(size);
    free_memory(size);
    return 0;
}
void init_news(int producers_num, int* queue_sizes){
    init_topics_array();
    init_producers_arrays(producers_num,queue_sizes);
    init_shared_q();
    init_co_editor_array();
    buffers_mutex = (pthread_mutex_t**) malloc(sizeof(pthread_mutex_t*) * producers_num);
    buffers_not_empty = (pthread_cond_t**) malloc(sizeof(pthread_cond_t*) * producers_num);
    buffers_not_full = (pthread_cond_t**) malloc(sizeof(pthread_cond_t*) * producers_num);
    co_editors_mutex = (pthread_mutex_t**) malloc(sizeof(pthread_mutex_t*) * 3);
    co_editors_not_empty = (pthread_cond_t**) malloc(sizeof(pthread_cond_t**) * 3);
    if(!buffers_mutex || !buffers_not_empty || !buffers_not_full || !co_editors_mutex){
        free(buffers_not_empty);
        free(buffers_not_full);
        free(buffers_mutex);
        free(co_editors_mutex);
        printf("mutex allocation fail\n");
        exit(1);
    }
    init_locks(producers_num);
    init_prod_threads_array(producers_num);
}
void init_topics_array(){
    queue_list* news = queue_init();
    queue_list* sports = queue_init();
    queue_list* weather = queue_init();
    topicsArray =(queue_list**)malloc(sizeof(queue_list*) * 3);
    topicsArray[0] = news;
    topicsArray[1] = sports;
    topicsArray[2] = weather;
}
void init_producers_arrays(int buffer_nums,int* buffer_sizes){
    producers_buffers = (bounded_buffer**)malloc(sizeof (bounded_buffer*)*(buffer_nums));
    for(int i = 0; i < buffer_nums; i++){
        producers_buffers[i] = bounded_init(buffer_sizes[i]);
    }
}
void init_shared_q(){
    shared_q =(queue_list*)malloc(sizeof(queue_list*));
}
void init_prod_threads_array(int producer_num){
    prod_threads = (pthread_t*)malloc(producer_num * sizeof(sem_t));
}
void init_co_editor_array(){
    co_editor_threads=(pthread_t*) malloc(sizeof(pthread_t) * 3);
}
void init_locks(int buffer_nums){
    for (int i = 0; i < buffer_nums; i++) {
        buffers_mutex[i] = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
        buffers_not_empty[i] = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
        buffers_not_full[i] = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));

        if (!buffers_mutex[i] || !buffers_not_empty[i] || !buffers_not_full[i]) {
            printf("Failed to allocate memory for mutex or condition variables\n");
            exit(1);
        }
    }
    for(int i = 0; i < buffer_nums; i ++){
        pthread_mutex_init(buffers_mutex[i],NULL);
        pthread_cond_init(buffers_not_empty[i],NULL);
        pthread_cond_init(buffers_not_full[i],NULL);
    }

    for(int i = 0; i < 3; i++){
        co_editors_mutex[i] = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
        co_editors_not_empty[i] = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
        pthread_mutex_init(co_editors_mutex[i],NULL);
        pthread_cond_init(co_editors_not_empty[i], NULL);
    }
    shared_q_mutex = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(shared_q_mutex,NULL);
    shared_q_not_empty = (pthread_cond_t*) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(shared_q_not_empty, NULL);
}
int call_producers(int size,int* products_num){
    for(int i = 0; i < size; i++){
        producerArgs* p_a =(producerArgs*)malloc(sizeof(producerArgs));
        if(p_a == NULL){
            printf("p_a failed!\n");
            exit(1);
        }
        p_a->id = i;
        p_a->buff= producers_buffers[i];
        p_a->prods_num= products_num[i];
        p_a->mutex = buffers_mutex[i];
        p_a->not_empty = buffers_not_empty[i];
        p_a->not_full = buffers_not_full[i];
        if(pthread_create(&prod_threads[i],NULL,createNews,(void*)p_a) !=0){
            fprintf(stderr,"error creating news thread\n");
            return 1;
        }
    }
    return 0;
}
int call_dispatcher(int size){
    dispatcherArgs* d_a = (dispatcherArgs*)malloc(sizeof (dispatcherArgs));
    if(d_a == NULL){
        free(d_a);
        exit(1);
    }
    d_a->bounded_array = producers_buffers;
    d_a->bounded_array_size = size;
    d_a->unbounded_Array= topicsArray;
    d_a->mutex = buffers_mutex;
    d_a->not_empty = buffers_not_empty;
    d_a->not_full = buffers_not_full;
    d_a->co_editor_mutex =co_editors_mutex;
    d_a->co_editor_not_empty = co_editors_not_empty;
    if(pthread_create(&dispatch_thread,NULL,dispatch,(void*)d_a) !=0){
        fprintf(stderr,"error creating news thread\n");
        return 1;
    }
    return 0;
}
int call_co_editors(){
    for(int i = 0; i < 3; i++) {
        coArgs *c_a = (coArgs *) malloc(sizeof(coArgs));
        if (!c_a) {
            free(c_a);
            printf("co_editors malloc failed!\n");
            return -1;
        }
        c_a->topic_q = topicsArray[i];
        c_a->shared_q = shared_q;
        c_a->co_editor_mutex = co_editors_mutex[i];
        c_a->co_editor_not_empty = co_editors_not_empty[i];
        c_a->shared_q_mutex = shared_q_mutex;
        c_a->shared_q_not_empty = shared_q_not_empty;
        c_a->id = i;
        if(pthread_create(&co_editor_threads[i],NULL,pass_to_queue,(void*)c_a) !=0){
            fprintf(stderr,"error creating news thread\n");
            return -1;
        }
    }
    return 0;
}
int call_screen_manager() {
    screenManArgs *s_a = (screenManArgs *) malloc(sizeof(screenManArgs));
    if (!s_a) {
        free(s_a);
        exit(1);
    }
    s_a->shared_q_mutex= shared_q_mutex;
    s_a->shared= shared_q;
    s_a->shared_q_not_empty = shared_q_not_empty;
    if(pthread_create(&screen_manager_thread,NULL,broadcast,(void*)s_a) !=0){
        fprintf(stderr,"error screen manager thread\n");
        return 1;
    }
    return 0;
}
void join_all_threads(int num_producers) {
    // Wait for all producer threads
    for (int i = 0; i < num_producers; i++) {
        if (pthread_join(prod_threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining producer thread %d\n", i);
        }
    }

    // Wait for the dispatcher thread
    if (pthread_join(dispatch_thread, NULL) != 0) {
        fprintf(stderr, "Error joining dispatcher thread\n");
    }

    // Wait for all co-editor threads
    for (int i = 0; i < 3; i++) {
        if (pthread_join(co_editor_threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining co-editor thread %d\n", i);
        }
    }
    if(pthread_join(screen_manager_thread,NULL) != 0) {
        fprintf(stderr, "Error joining screen manager thread\n");
    }

    printf("All threads have completed their work.\n");
}
void free_memory(int size) {
    // Free topicsArray
    for (int i = 0; i < 3; i++) {
        free(topicsArray[i]);
    }
    free(topicsArray);

    // Free producers_buffers
    for (int i = 0; i < size; i++) {
        free(producers_buffers[i]);
    }
    free(producers_buffers);

    // Free shared_q
    free(shared_q);

    // Free threads arrays
    free(prod_threads);
    free(co_editor_threads);

    // Free mutex and condition variable arrays
    for (int i = 0; i < size; i++) {
        pthread_mutex_destroy(buffers_mutex[i]);
        pthread_cond_destroy(buffers_not_empty[i]);
        pthread_cond_destroy(buffers_not_full[i]);
        free(buffers_mutex[i]);
        free(buffers_not_empty[i]);
        free(buffers_not_full[i]);
    }
    free(buffers_mutex);
    free(buffers_not_empty);
    free(buffers_not_full);

    // Free co-editor mutex and condition variables
    for (int i = 0; i < 3; i++) {
        pthread_mutex_destroy(co_editors_mutex[i]);
        pthread_cond_destroy(co_editors_not_empty[i]);
        free(co_editors_mutex[i]);
        free(co_editors_not_empty[i]);
    }
    free(co_editors_mutex);
    free(co_editors_not_empty);

    // Free shared queue mutex and condition variable
    pthread_mutex_destroy(shared_q_mutex);
    pthread_cond_destroy(shared_q_not_empty);
    free(shared_q_mutex);
    free(shared_q_not_empty);
}