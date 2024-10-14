#include "data_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* read_product_numbers(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    int* products = NULL;
    int index = 0;
    char line[128];
    int temp_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "PRODUCER")) {
            // Read the next line for number of products
            if (fgets(line, sizeof(line), file)) {
                temp_count++;
                products = realloc(products, temp_count * sizeof(int));
                products[index++] = atoi(line);
            }
        }
    }

    *count = temp_count;
    fclose(file);
    return products;
}

int* read_queue_sizes(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    int* sizes = NULL;
    int index = 0;
    char line[128];
    int temp_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "queue size = ")) {  // Changed this line
            temp_count++;
            sizes = realloc(sizes, temp_count * sizeof(int));
            // Extract the integer after 'queue size = '
            char* start = strstr(line, "=") + 1;
            sizes[index++] = atoi(start) + 1;
        }
    }

    *count = temp_count;
    fclose(file);
    return sizes;
}