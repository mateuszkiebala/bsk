#ifndef QUANTITY_ARRAY_H
#define QUANTITY_ARRAY_H

#include "c_string.h"
#include <stddef.h>

/* Array of pairs. */
struct quantity_array;

/* Create new instance of array. */
struct quantity_array* qa_create();

/* Insert new pair. 
   If pair already exists increase quantity and free memory of s else
   create new instance of pair.
   IMPORTANT: c_string s always becomes NULL after insert. 
   Return pair inserted. */
struct pair* qa_insert(struct quantity_array *qa, struct c_string *s);

/* Return element at position pos. */
struct pair* qa_get(const struct quantity_array *qa, int pos);

/* Return length of array. */
size_t qa_length(const struct quantity_array *qa);

/* Free memory of array. */
void* qa_free(struct quantity_array *qa);

#endif /* QUANTITY_ARRAY_H */