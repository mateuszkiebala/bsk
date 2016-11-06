#include "unit_tests.h"
#include <stdio.h>
#include <string.h>

void test_c_string() {
    {
        struct c_string *cs = cs_create();
        assert(cs_length(cs) == 0);
        assert(strcmp(cs_to_str(cs), "") == 0);

        cs_push(cs, 'a');
        assert(cs_length(cs) == 1);

        cs_push(cs, 'b');
        cs_push(cs, 'c');
        assert(strcmp(cs_to_str(cs), "abc") == 0);
        assert(cs_length(cs) == 3);
        
        cs_pop(cs);
        assert(strcmp(cs_to_str(cs), "ab") == 0);
        assert(cs_length(cs) == 2);

        cs_pop(cs);
        cs_pop(cs);
        assert(strcmp(cs_to_str(cs), "") == 0);

        cs_push(cs, 'a');
        assert(strcmp(cs_to_str(cs), "a") == 0);
        assert(cs_length(cs) == 1);

        int i = 0;
        for (i = 0; i < 10; ++i) {
            cs_push(cs, 'a');
        }
        assert(strcmp(cs_to_str(cs), "aaaaaaaaaaa") == 0);
        assert(cs_length(cs) == 11);

        cs_pop(cs);
        assert(strcmp(cs_to_str(cs), "aaaaaaaaaa") == 0);
        assert(cs_length(cs) == 10);

        for (i = 0; i < 10; ++i) {
            cs_pop(cs);
        }
        assert(strcmp(cs_to_str(cs), "") == 0);

        struct c_string *cs2 = cs_create();
        cs_push(cs2, 'a');
        cs_push(cs2, 'b');
        cs_push(cs2, 'c');
        assert(strcmp(cs_to_str(cs2), "abc") == 0);

        cs_push(cs, 'a');
        cs_push(cs, 'b');
        cs_push(cs, 'c');
        assert(strcmp(cs_to_str(cs), "abc") == 0);
        assert(cs_cmp(cs, cs2) == 0);

        cs_pop(cs2);
        assert(strcmp(cs_to_str(cs2), "ab") == 0);
        assert(cs_cmp(cs, cs2) > 0);

        cs = cs_free(cs);
        assert(cs == NULL);

        cs2 = cs_free(cs2);
        assert(cs2 == NULL);
    }
}

void test_pair() {
    {
        struct c_string *cs = cs_create();
        struct pair *p = pair_create(cs, 0);
        assert(pair_quantity(p) == 0);
        assert(strcmp(cs_to_str(pair_c_string(p)), "") == 0);

        pair_increase(p);
        assert(pair_quantity(p) == 1);
        p = pair_free(p);
    }

    {
        struct c_string *cs = cs_create();
        cs_push(cs, 'a');
        struct pair *p = pair_create(cs, 1);
        assert(pair_quantity(p) == 1);
        assert(strcmp(cs_to_str(pair_c_string(p)), "a") == 0);
        pair_increase(p);
        assert(pair_quantity(p) == 2);
        p = pair_free(p);
    }
}

void test_quantity_array() {
    {
        struct quantity_array *qa = qa_create();
        assert(qa_length(qa) == 0);

        {
            struct c_string *cs = cs_create();
            cs_push(cs, 'a');
            qa_insert(qa, cs);
            assert(qa_length(qa) == 1);
            assert(strcmp(cs_to_str(pair_c_string(qa_get(qa, 0))), "a") == 0);
            assert(pair_quantity(qa_get(qa, 0)) == 1);
        }
        {
            struct c_string *cs = cs_create();
            cs_push(cs, 'a');
            qa_insert(qa, cs);
            assert(qa_length(qa) == 1);
            assert(strcmp(cs_to_str(pair_c_string(qa_get(qa, 0))), "a") == 0);
            assert(pair_quantity(qa_get(qa, 0)) == 2);
        }
        {
            struct c_string *cs = cs_create();
            cs_push(cs, 'b');
            qa_insert(qa, cs);
            assert(qa_length(qa) == 2);
            assert(strcmp(cs_to_str(pair_c_string(qa_get(qa, 1))), "b") == 0);
            assert(pair_quantity(qa_get(qa, 1)) == 1);
        }

        qa = qa_free(qa);
    }
}

void test_text() {
    {
        struct text *t = text_create();
        {
            struct c_string *row = cs_create();
            cs_push(row, 'a');
            cs_push(row, 'b');
            cs_push(row, 'c');
            text_insert_first_row(t, row);
        }
        int i = 0;
        for (; i < 7; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            cs_push(s, 'b');
            cs_push(s, 'c');
            text_insert_word(t, s);
        }

        for (i = 0; i < 4; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            cs_push(s, 'c');
            text_insert_word(t, s);
        }

        for (i = 0; i < 4; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            cs_push(s, 'b');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 1; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            cs_push(s, 'b');
            cs_push(s, 'c');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 10; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            cs_push(s, 'b');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 1; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'd');
            text_insert_word(t, s);
        }

        for (i = 0; i < 1; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'c');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 1; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 16; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'a');
            text_insert_word(t, s);
        }
        text_display_top(t);

        for (i = 0; i < 20; ++i) {
            struct c_string *s = cs_create();
            cs_push(s, 'd');
            text_insert_word(t, s);
        }
        text_display_top(t);

        t = text_free(t);
    }
}

void test() {
    test_c_string();
    test_pair();
    test_quantity_array();
    test_text();
}