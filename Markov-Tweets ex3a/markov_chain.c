#include "markov_chain.h"
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number) {
    return rand() % max_number;
}

Node *get_node_from_database(MarkovChain *markov_chain, char *data_ptr) {
    Node *cur = markov_chain->database->first;
    while (cur) {
        if (!strcmp(cur->data->data, data_ptr)) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Node *add_to_database(MarkovChain *markov_chain, char *data_ptr) {
    if (get_node_from_database(markov_chain, data_ptr)) {
        return get_node_from_database(markov_chain, data_ptr);
    }
    MarkovNode *new_node = malloc(sizeof(Node));
    if (!new_node) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return NULL;
    }
    char *size = malloc(sizeof(strlen(data_ptr) + 1));
    if (!size) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return NULL;
    }
    new_node->num_of_words=0;
    strcpy(size, data_ptr); // strcpy(new_node->data, data_ptr);
    new_node->data=size;
    new_node->frequency_list=NULL;
    add(markov_chain->database, new_node);
    return markov_chain->database->last;
}

int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode *second_node) {
    for (int i = 0; i < first_node->num_of_words; i++) {
        if (!strcmp(first_node->frequency_list[i].markov_node->data, second_node->data)) {
            first_node->frequency_list[i].frequency += 1;
        }
    }
    unsigned long size=sizeof(MarkovNodeFrequency) * (first_node->num_of_words + 1);
    MarkovNodeFrequency *new_freq = realloc(first_node->frequency_list,size);
    if (!new_freq) {
        printf(ALLOCATION_ERROR_MASSAGE);
        return EXIT_FAILURE;
    }
    new_freq[first_node->num_of_words].markov_node = second_node;
    new_freq[first_node->num_of_words].frequency = 1;
    first_node->frequency_list=new_freq;
    first_node->num_of_words += 1;

    return EXIT_SUCCESS;
}

void free_database(MarkovChain **ptr_chain) {
    Node *cur = (*ptr_chain)->database->first;
    Node *next = NULL;
    while (cur) {
        next = cur->next;
        // for (int i = 0; i < cur->data->num_of_words; i++) {
        //     free(cur->data->frequency_list[i].markov_node);
        // }
        free(cur->data->data);
        free(cur->data->frequency_list);
        free(cur->data);
        cur->data = NULL;
        free(cur);
        cur = next;
    }
    free((*ptr_chain)->database);
    free(*ptr_chain);
    *ptr_chain = NULL;
}


MarkovNode *get_first_random_node(MarkovChain *markov_chain) {
    int i = 0;
    int random = get_random_number(markov_chain->database->size);
    Node *cur = markov_chain->database->first;
    while (i < random) {
        cur = cur->next;
        i++;
    }
    if (cur->data->data[strlen(cur->data->data) - 1] == '.') {
        get_first_random_node(markov_chain);
    }
    return cur->data;
}

MarkovNode *get_next_random_node(MarkovNode *cur_markov_node) {
    int words_iterates = 0;
    for (int i = 0; i < cur_markov_node->num_of_words; i++) {
        words_iterates += cur_markov_node->frequency_list[i].frequency;
    }
    int rand2 = get_random_number(words_iterates);
    int m = 0;
    while (rand2 >= 0) {
        if (cur_markov_node->frequency_list[m].frequency < rand2) {
            rand2 -= cur_markov_node->frequency_list[m].frequency;
        } else {
            return cur_markov_node->frequency_list[m].markov_node;
        }
        m++;
    }
}

void generate_tweet(MarkovNode *first_node, int max_length) {
    int i = 1;
    printf("%s ",first_node->data);
    MarkovNode *cur = get_next_random_node(first_node);
    while (i <= max_length) {
        printf("%s ", cur->data);
        if (cur->data[strlen(cur->data) - 1] == '.') {
            break;
        }
        cur = get_next_random_node(cur);
        i++;
    }
}


