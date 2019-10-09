#include "main.c"
#include "test.h"

int tests(void) {
    my_str_t mst;
    my_str_create(&mst, 7);
    if (test_my_str_free(&mst)) return 1;
    my_str_t string;
    my_str_create(&string, 7);
    if (test_my_str_size(&string)) return 2;
    if (test_my_str_from_cstr(&string)) return 3;
    return 0;
}

int test_my_str_free(my_str_t *str) {
    my_str_free(str);
    if (str == NULL) return 1;
    return 0;
}
