//
// Created by ran on 10/10/24.
//
#include "producer.h"

void* createNews(void* args) {
    producerArgs *prodArgs = (producerArgs *) args;
    char *topics[] = {"News", "Sports", "Weather"};
    int sports_cnt = 0;
    int news_cnt = 0;
    int weather_cnt = 0;
    for (int i = 0; i < prodArgs->prods_num; i++) {
        pthread_mutex_lock(prodArgs->mutex);
        while (is_full(prodArgs->buff)) {
            pthread_cond_wait(prodArgs->not_full, prodArgs->mutex);
        }
        int topic_index = i % 3;
        char news_string[100];

        // Depending on the random topic, increment the corresponding counter
        if (strcmp(topics[topic_index], "Sports") == 0) {
            sports_cnt++;
            sprintf(news_string, "producer %d %s %d", prodArgs->id, topics[topic_index], sports_cnt);
        } else if (strcmp(topics[topic_index], "Weather") == 0) {
            weather_cnt++;
            sprintf(news_string, "producer %d %s %d", prodArgs->id, topics[topic_index], weather_cnt);
        } else if (strcmp(topics[topic_index], "News") == 0) {
            news_cnt++;
            sprintf(news_string, "producer %d %s %d", prodArgs->id, topics[topic_index], news_cnt);
        }
        //printf("%s\n",news_string);
        add(prodArgs->buff, news_string);
        pthread_cond_signal(prodArgs->not_empty);
        pthread_mutex_unlock(prodArgs->mutex);
    }
    pthread_mutex_lock(prodArgs->mutex);

    while(is_full(prodArgs->buff)){
        pthread_cond_wait(prodArgs->not_full,prodArgs->mutex);
    }
    char news_string[100];
    sprintf(news_string, "DONE");
    add(prodArgs->buff, news_string);
    pthread_cond_signal(prodArgs->not_empty);
    pthread_mutex_unlock(prodArgs->mutex);
    return NULL;
}



