#include "run.h"
#include "c_string.h"
#include "text.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int run(FILE *in, FILE *out) {
    struct c_string *end = cs_create();
    cs_push(end, '=');
    cs_push(end, '=');
    int dot = 0;

    while (!feof(in) && !dot) {                     // read file
        struct text *t = text_create();
        int row_cnt = 0;
        while (!dot) {                              // read text
            struct c_string *row = cs_create();
            while (!dot) {                          // read line
                struct c_string *cs = cs_create();
                char c;
                int word = 0;
                while (isalpha((c = getc(in)))) {   // read word
                    cs_push(cs, c);
                    if (row_cnt == 0) {
                        cs_push(row, c);
                    }
                    word = 1;
                }

                if (word) {
                    text_insert_word(t, cs);
                } else {
                    cs = cs_free(cs);
                }

                if (c != '\n') {
                    cs_push(row, c); 
                } else {
                    if (row_cnt == 0) {
                        text_insert_first_row(t, row);
                    }
                    ++row_cnt;
                    break;
                }

                if (c == '.') {
                    cs = cs_free(cs);
                    row = cs_free(row);
                    dot = 1;
                    break;
                }
            }

            if (cs_cmp(row, end) == 0) {
                text_display_top(t);
                t = text_free(t);
                row = cs_free(row);
                break;
            } else if (row_cnt > 1) {
                row = cs_free(row);
            }
        }

        if (t != NULL) {
            t = text_free(t);
        }
    }
    cs_free(end);
}