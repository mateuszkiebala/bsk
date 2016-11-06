#ifndef PAIR_H
#define PAIR_H

#include "c_string.h"

/* Pair of c_string and quantity of occurances. */
struct pair;

/* Create pair. */
struct pair* pair_create(struct c_string *cs, int quantity);

/* Increase quantity. */
void pair_increase(struct pair *p);

/* Return quantity. */
int pair_quantity(const struct pair *p);

/* Return c_string. */
const struct c_string* pair_c_string(const struct pair *p);

/* Compare two pairs.
   Return 0 if equal, 1 if first i greater and -1 if second is greater. */
int pair_cmp(const struct pair *p1, const struct pair *p2);
	
/* Free allocated memory for pair and returns NULL */
void* pair_free(struct pair *p);

#endif /* PAIR_H */