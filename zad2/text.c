#include "text.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct text {
    struct quantity_array *words;
    struct pair *top[TOP_SIZE]; // ascending order
    struct c_string *first_row;
} text;

static void update_top_five(text *t, struct pair *p) {
    int i = 0;
    int pos = -1;
    for (; i < TOP_SIZE; ++i) {
        if (pair_cmp(p, t->top[i]) == 0) {
            pos = i;
            break;
        }
    }

    for (i = pos + 1; i < TOP_SIZE; ++i) {
        if (pair_cmp(p, t->top[i]) > 0) {
            if (i > 0) {
                t->top[i - 1] = t->top[i];
            }
            t->top[i] = p;
        } else {
            break;
        }
    }
}

struct text* text_create() {
    text* t = (text *) malloc(sizeof(text));
    if (t == NULL) {
        fprintf(stderr, "Cannot create new text.\n");
        exit(1);
    }

    int i = 0;
    for (; i < 5; ++i) {
        t->top[i] = NULL;
    }
    t->words = qa_create();
    t->first_row = NULL;
    return t;
}

void text_insert_first_row(struct text *t, struct c_string *row) {
    t->first_row = row;
}

void text_insert_word(struct text *t, struct c_string* s) {
    struct pair *p = qa_insert(t->words, s);
    update_top_five(t, p);
}

void text_display_top(const struct text *t) {
    int i = 0;
    printf("First row: %s\n", cs_to_str(t->first_row));
    for (; i < TOP_SIZE; ++i) {
        if (t->top[i] != NULL) {
            printf("%s %d\n", cs_to_str(pair_c_string(t->top[i])),
                                        pair_quantity(t->top[i]));
        }
    }
}

void* text_free(struct text *t) {
    if (t != NULL) {
        qa_free(t->words);
        cs_free(t->first_row);
        free(t);
    }
    return NULL;
}
