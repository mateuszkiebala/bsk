#ifndef TEXT_H
#define TEXT_H

#include "c_string.h"
#include "pair.h"
#include "quantity_array.h"

#define TOP_SIZE 5

struct text;

/* Create new instance of text. */
struct text* text_create();

/* Insert first row of text.
   Row becomes NULL. */
void text_insert_first_row(struct text *t, struct c_string *row);

/* Add new word to text.
   s becomes NULL. */
void text_insert_word(struct text *t, struct c_string* s);

/* Shows top 5 words with most occurence in text. */
void text_display_top(const struct text *t);

/* Free memory of text. */
void* text_free(struct text *t);

#endif /* TEXT_H */