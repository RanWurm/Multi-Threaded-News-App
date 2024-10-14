//
// Created by ran on 9/26/24.
//
#include "queue_list.h"

//inits empty queue_list
queue_list* queue_init(){
    queue_list* q =(queue_list*)malloc(sizeof(queue_list));
    if(q == 0){
        exit(1);
    }
    q->head =NULL;
    q->size = 0;
    return q;
}


node* new_node(char* message){
    node* n = (node*)malloc(sizeof(node));
    if( n == 0){
        exit(1);
    }
    if(message == NULL){
        return NULL;
    }
    strcpy(n->message, message);
    n->next = NULL;
    n->prev = NULL;
    return n;
}
// returns -1 if failed 0 else
int add_to_queue(queue_list* q, char* message) {
    if (q == NULL) {
        printf("queue_list pointer is: %p\n", q);
        return -1;
    }
    node *to_add = new_node(message);
    if(to_add == NULL){
        return -1;
    }
    if (q->size == 0) {
        q->head = to_add;
        q->last = to_add;
        q->size++;
        return 0;
    }
    to_add->prev = q->last;
    q->last->next = to_add;
    q->last = to_add;
    q->size++;
    return 0;
}
//pop the head of the queue_list
node* pop(queue_list* q){
    if(q == NULL || q->head == NULL){
        printf("queue pop return null because: ");
        if(q == NULL){
            printf("q == NULL\n");
        }else if(q->head  == NULL){
            printf("q->head == NULL\n");
        }
        return NULL;
    }
    node* ret = q->head;  // We'll return the actual head node instead of creating a new one
    q->head = q->head->next;
    if(q->head == NULL){
        q->last = NULL;  // If the queue is now empty, update last pointer as well
    } else {
        q->head->prev = NULL;
    }

    ret->next = NULL;  // Isolate the returned node
    q->size--;
    return ret;
}

// Function to reverse the queue
void reverse_queue(queue_list* q) {
    if (q == NULL || q->size <= 1) {
        return; // No need to reverse if the queue is empty or has one element
    }

    node* current = q->head;
    node* temp = NULL;

    // Swap next and prev for each node in the queue
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node (which was the previous one before swap)
    }

    // Swap the head and last pointers of the queue
    temp = q->head;
    q->head = q->last;
    q->last = temp;
}