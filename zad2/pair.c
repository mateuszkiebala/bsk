#include "pair.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct pair {
    struct c_string *cs;
    int quantity;
} pair;

pair* pair_create(struct c_string *cs, int quantity) {
    pair *p = (pair *) malloc(sizeof(pair));
    if (p == NULL) {
        fprintf(stderr, "Cannot allocate memory for pair.\n");
        exit(1);
    }
    p->cs = cs;
    p->quantity = quantity;
    return p;
}

void pair_increase(struct pair *p) {
    assert(p != NULL);
    p->quantity++;
}

int pair_quantity(const pair *p) {
    assert(p != NULL);
    return p->quantity;
}

const struct c_string* pair_c_string(const pair *p) {
    assert(p != NULL);
    return p->cs;
}

int pair_cmp(const struct pair *p1, const struct pair *p2) {
    if (p1 == NULL) {
        return -1;
    }
    if (p2 == NULL) {
        return 1;
    }

    if (p1->quantity > p2->quantity) {
        return 1;
    } else if (p1->quantity < p2->quantity) {
        return -1;
    } else {
        return (-1) * cs_cmp(p1->cs, p2->cs);
    }
}

void* pair_free(pair *p) {
    if (p != NULL) {
        cs_free(p->cs);
        p->cs = NULL;
        free(p);
    }
    return NULL;
}