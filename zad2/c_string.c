#include "c_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct c_string {
    char *data;
    size_t length;
    size_t capacity;    
} c_string;

struct c_string* cs_create() {
    c_string *new_cs = (c_string *) malloc(sizeof(c_string));
    if (new_cs == NULL) {
        fprintf(stderr, "Cannot create new c_string.\n");
        exit(1);
    }
    new_cs->length = 1;
    new_cs->capacity = 1;
    new_cs->data = (char *) malloc(sizeof(char));
    new_cs->data[0] = '\0';
    return new_cs;
}

const char* cs_to_str(const c_string *s) {
    return s->data;
}

void cs_push(c_string *s, char c) {
    assert(s != NULL);
    if (s->length == s->capacity) {
        s->capacity = s->capacity * 2 + 1;
        char *new_data = (char *) realloc(s->data, s->capacity * sizeof(char));
        if (new_data != NULL) {
            s->data = new_data;
        } else {
            free(s->data);
            fprintf(stderr, "Cannot (re)allocate more memory for c_string.\n");
            exit(1);
        }
    }
    s->data[s->length - 1] = c;
    s->data[s->length] = '\0';
    s->length++;
}

void cs_pop(c_string *s) {
    assert(s != NULL);
    if (s->length > 1) {
        s->length--;
        s->data[s->length - 1] = '\0';
    }
}

size_t cs_length(c_string *s) {
    assert(s != NULL);
    return s->length - 1;
}

int cs_cmp(const struct c_string *s1, const struct c_string *s2) {
    if (s1 == NULL) {
        return -1;
    }
    if (s2 == NULL) {
        return 1;
    }
    return strcmp(s1->data, s2->data);
}

void* cs_free(c_string *s) {
    if (s != NULL) {
        free(s->data);
        s->data = NULL;
        free(s);
    }
    return NULL;
}

