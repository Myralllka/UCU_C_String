#include "test.h"
#include "../cstring/include/library.h"


int tests(void) {
    if (test_my_str_create()) printf("fail test 1\n");
    if (test_my_str_from_cstr()) printf("fail test 2\n");
    if (test_my_str_size()) printf("fail test 3\n");
    if (test_my_str_capacity()) printf("fail test 4\n");
    if (test_my_str_empty()) printf("fail test 5\n");
    return 0;
}

int test_my_str_create() {
    my_str_t str;
    my_str_create(&str, 1);
    if (!my_str_create(NULL, 0)) return -1;
    if (str.data == NULL) return -1;
    my_str_free(&str);
    return 0;
}


int test_my_str_from_cstr() {
    my_str_t str;
    my_str_create(&str, 0);
    char *ccc = "hello my dear";
    my_str_from_cstr(&str, ccc, 0);
    for (int i = 0; i < str.size_m; i++) {
        if (str.data[i] != ccc[i]) return 1;
    }
    if (str.size_m != 13) return 1;
    if (str.capacity_m != str.size_m + 1) return 1;
    my_str_free(&str);
    return 0;
}

int test_my_str_size() {
    my_str_t str1;
    my_str_create(&str1, 7);
    if (str1.size_m != my_str_size(&str1)) return 1;
    my_str_free(&str1);
    return 0;
}

int test_my_str_capacity() {
    my_str_t str;
    my_str_create(&str, 0);
    char *ccc = "hello";
    my_str_from_cstr(&str, ccc, 0);
    if (str.capacity_m != str.size_m + 1) return 1;
    my_str_free(&str);
    return 0;
}

int test_my_str_empty() {
        my_str_t str;
        my_str_create(&str, 1);
        my_str_from_cstr(&str, "hello", 0);

    return 0;
}

int test_my_str_getc() {
    return 0;
}

int test_my_str_putc() {
    return 0;
}

int test_my_str_get_cstr() {
    return 0;
}
