#include "quantity_array.h"
#include "pair.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct quantity_array {
    struct pair **array;
    size_t length;
    size_t capacity;
} quantity_array;

/* If c_string exists in array then return position, else -1. */
static int find(const quantity_array *qa, const struct c_string *s1) {
    int i = 0;
    for (; i < qa->length; ++i) {
        if (cs_cmp(s1, pair_c_string(qa->array[i])) == 0) {
            return i;
        }
    }
    return -1;
}

struct quantity_array* qa_create() {
    quantity_array *qa = (quantity_array *) malloc(sizeof(quantity_array));
    if (qa == NULL) {
        fprintf(stderr, "Cannot create new quantity array.\n");
        exit(1);
    }
    qa->length = 0;
    qa->capacity = 0;
    qa->array = NULL;
    return qa;
}

struct pair* qa_insert(struct quantity_array *qa, struct c_string *s) {
    assert(qa != NULL);
    int pos = -1;
    struct pair *ret = NULL;
    if ((pos = find(qa, s)) != -1) {
        pair_increase(qa->array[pos]);
        ret = qa->array[pos];
        cs_free(s);
    } else {
        if (qa->length == qa->capacity) {
            qa->capacity = qa->capacity * 2 + 1;
            struct pair **new_arr = (struct pair **) 
                                     realloc(qa->array, 
                                             qa->capacity * sizeof(struct pair *));
            if (new_arr != NULL) {
                qa->array = new_arr;
            } else {
                qa = qa_free(qa);
                fprintf(stderr, "Cannot (re)allocate more memory for quantity_array.\n");
                exit(1);
            }
        }
        struct pair *p = pair_create(s, 1);
        qa->array[qa->length] = p;
        qa->length++;
        ret = p;
    }
    s = NULL;
    return ret;
}

struct pair* qa_get(const quantity_array *qa, int pos) {
    assert(qa != NULL);
    if (pos < qa->length) {
        return qa->array[pos];
    }
    return NULL;
}

size_t qa_length(const struct quantity_array *qa) {
    assert(qa != NULL);
    return qa->length;
}

void* qa_free(struct quantity_array *qa) {
    if (qa != NULL) {
        int i = 0;
        for (; i < qa->length; ++i) {
            pair_free(qa->array[i]);
        }
        free(qa->array);
        qa->array = NULL;
        free(qa);
    }
    return NULL;
}