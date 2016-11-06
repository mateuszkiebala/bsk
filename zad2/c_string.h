#ifndef C_STRING_H
#define C_STRING_H

#include <stddef.h>

/* Type of string. Terminated with '\0' */
struct c_string;

/* Creates new instance of c_string. */
struct c_string* cs_create();

/* Convert string to c-string. */
const char* cs_to_str(const struct c_string *s);

/* Add new letter at the end of string. */
void cs_push(struct c_string *s, char c);

/* Remove last letter from string. */
void cs_pop(struct c_string *s);

/* Return length of string. '\0' doesn't count. */
size_t cs_length(struct c_string *s);

/* Return 0 if s1 == s2, 1 when s1 > s2, -1 otherwise. */
int cs_cmp(const struct c_string *s1, const struct c_string *s2);

/* Free memory allocated by c-string and returns NULL */
void* cs_free(struct c_string *s);

#endif /* C_STRING_H */