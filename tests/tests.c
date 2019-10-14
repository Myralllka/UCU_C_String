//#include "../main.c"
#include <hdf5_hl.h>
#include "test.h"
#include "../libb/src/library.c"

int tests(void) {
    if (!test_my_str_free()) return 1;
    if (!test_my_str_size()) return 2;
    if (!test_my_str_from_cstr()) return 3;
    if (!test_my_str_capacity()) return 4;
    return 0;
}

int test_my_str_free() {
    my_str_t mst;
    my_str_create(&mst, 7);
    my_str_free(&mst);
    return &mst ? 1 : 0;
}

int test_my_str_size() {
    my_str_t str1;
    my_str_create(&str1, 7);
    if (&str1 == NULL) return 1;
    if (str1.size_m != my_str_size(&str1)) return 1;
    return 0;
}

int test_my_str_from_cstr() {
    my_str_t str;
    char *ccc = "hello my dear";
    my_str_from_cstr(&str, ccc, 0);
    if (&str == NULL) return 1;
    for (int i = 0; i < str.size_m; i++) {
        if (str.data[i] != ccc[i]) return 1;
    }
    if (str.size_m != 13) return 1;
    if (str.capacity_m != 27) return 1;
    return 0;
}

int test_my_str_capacity () {
    my_str_t str;
    char *ccc = "hello";
    my_str_from_cstr(&str, ccc, 0);
    if (&str == NULL) return 1;
    if (str.capacity_m != 11) return 1;
}