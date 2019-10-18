#include "test.h"
#include "../lib/include/c_string.h"
#include <ctype.h>

typedef struct {
    char* name;
    int (*func)(void);
} function;

int tests(void) {
    function names[] = {"test_my_str_create", test_my_str_create,
                     "test_my_str_from_cstr", test_my_str_from_cstr,
                     "test_my_str_size", test_my_str_size,
                     "test_my_str_capacity", test_my_str_capacity,
                     "test_my_str_empty", test_my_str_empty,
                     "test_my_str_getc", test_my_str_getc,
                     "test_my_str_putc", test_my_str_putc,
                     "test_my_str_get_cstr", test_my_str_get_cstr,
                     "test_my_str_pushback", test_my_str_pushback,
                     "test_my_str_popback", test_my_str_popback,
                     "test_my_str_copy", test_my_str_copy,
                     "test_my_str_insert_c", test_my_str_insert_c,
                     "test_my_str_insert", test_my_str_insert,
                     "test_my_str_insert_cstr", test_my_str_insert_cstr,
                     "test_my_str_append", test_my_str_append,
                     "test_my_str_append_cstr", test_my_str_append_cstr,
                     "test_my_str_substr", test_my_str_substr,
                     "test_my_str_substr_cstr", test_my_str_substr_cstr,
                     "test_my_str_reserve", test_my_str_reserve,
                     "test_my_str_shrink_to_fit", test_my_str_shrink_to_fit,
                     "test_my_str_resize", test_my_str_resize,
                     "test_my_str_find", test_my_str_find,
                     "test_my_str_cmp", test_my_str_cmp,
                     "test_my_str_cmp_cstr", test_my_str_cmp_cstr,
                     "test_my_str_find_c", test_my_str_find_c,
                     "test_my_str_find_if", test_my_str_find_if,
                     "test_my_str_read_file", test_my_str_read_file,
                     "test_my_str_write_file", test_my_str_write_file,
                     "test_my_str_read_file_delim", test_my_str_read_file_delim};

    for (int i = 0; i < 18; ++i) {
        int res;
        res = names[i].func();
        if (res)
            printf("Test %i '%s':\t\tFail %i\n", i + 1, names[i].name, res);
    }
    test_my_str_reserve();
    test_my_str_shrink_to_fit();
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
    for (size_t i = 0; i < str.size_m; i++) {
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
    if (str.capacity_m != my_str_capacity(&str)) return 1;
    my_str_free(&str);
    return 0;
}

int test_my_str_empty() {
    my_str_t str;
    my_str_t empty_str;
    my_str_create(&str, 1);
    my_str_create(&empty_str, 1);
    my_str_from_cstr(&str, "hello", 0);
    if (!my_str_empty(&empty_str)) return -1;
    if (my_str_empty(&str)) return -1;
    my_str_free(&str);
    my_str_free(&empty_str);
    return 0;
}

int test_my_str_getc() {
    my_str_t str;
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello world", 0);
    if (my_str_getc(&str, 0) != 'h') return 1;
    if (my_str_getc(&str, 6) != 'w') return 1;
    if (my_str_getc(&str, 10) != 'd') return 1;
    if (!my_str_getc(&str, -45)) return 1;
    if (!my_str_getc(&str, 12)) return 1;
    my_str_free(&str);
    return 0;
}

int test_my_str_putc() {
    my_str_t str;
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello my dear friend", 0);
    my_str_putc(&str, 0, 'p');
    my_str_putc(&str, str.size_m - 1, 'a');
    if (str.data[0] != 'p') return 1;
    if (str.data[str.size_m - 1] != 'a') return 1;
    if (!my_str_putc(&str, -1, 'a')) return 1;
    if (!my_str_putc(&str, str.size_m, 'a')) return 1;
    my_str_free(&str);
    return 0;
}

int test_my_str_get_cstr() {
    char* sample = "hello world";
    my_str_t str;
    my_str_create(&str, 1);
    my_str_from_cstr(&str, sample, 0);
    const char* res =  my_str_get_cstr(&str);

    if (char_arr_len(res) != char_arr_len(sample)) return -1;

    for (size_t i = 0; i < char_arr_len(res); ++i)
        if (res[i] != sample[i]) return -1;
    return 0;
}

int test_my_str_pushback() {
    my_str_t str;
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello world", 0);
    my_str_pushback(&str, ' ');
    my_str_pushback(&str, 'n');
    my_str_pushback(&str, 'o');
    if (str.data[str.size_m - 1] != 'o') return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_popback() {
    my_str_t str;
    my_str_create(&str, 1);
    if (!my_str_popback(&str)) return -1;
    my_str_from_cstr(&str, "hello world", 0);
    int c = my_str_popback(&str);
    if (str.data[str.size_m - 1] != 'l') return -1;
    if (c != 'd') return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_copy() {
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 1);
    my_str_create(&str2, 1);
    my_str_from_cstr(&str1, "hello world", 0);
    my_str_copy(&str1, &str2, 1);
    if (str2.data[str2.size_m - 1] != 'd') return -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return 0;
}

int test_my_str_insert_c() {
    my_str_t str;
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello world", 0);
    my_str_insert_c(&str, 'A', 0);
    if (str.data[0] != 'A') return -1;
    my_str_insert_c(&str, 'A', str.size_m);
    if (str.data[str.size_m - 1] != 'A') return -1;
    my_str_insert_c(&str, 'A', 4);
    if (str.data[4] != 'A') return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_insert() {
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 1);
    my_str_create(&str2, 1);
    my_str_from_cstr(&str1, "hello", 0);
    my_str_from_cstr(&str2, " world", 0);
    my_str_insert(&str1, &str2, str1.size_m);
    if (str2.data[str2.size_m - 1] != 'd') return -1;
    my_str_insert(&str1, &str2, 0);
    if (!isspace(str2.data[0])) return -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return 0;
}

int test_my_str_insert_cstr() {
    my_str_t str;
    my_str_create(&str, 0);
    char *c = " world";
    my_str_from_cstr(&str, "hello", 0);
    my_str_insert_cstr(&str, c, str.size_m);
    if (str.data[str.size_m - 1] != 'd') return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_append() {
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 1);
    my_str_create(&str2, 1);
    my_str_from_cstr(&str1, "hello", 0);
    my_str_from_cstr(&str2, " world", 0);
    my_str_append(&str1, &str2);
    if (str2.data[str2.size_m - 1] != 'd') return -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return 0;
}

int test_my_str_append_cstr() {
    my_str_t str;
    my_str_create(&str, 0);
    char *c = " world";
    my_str_from_cstr(&str, "hello", 0);
    my_str_append_cstr(&str, c);
    if (str.data[str.size_m - 1] != 'd') return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_substr() {
    my_str_t str1;
    my_str_t str2;
    my_str_create(&str1, 0);
    my_str_create(&str2, 0);
    my_str_from_cstr(&str1, "hello world", 0);
    my_str_substr(&str1, &str2, 0, 5);
    if (str2.data[str2.size_m-1] != 'o') return -1;
    my_str_free(&str1);
    my_str_free(&str2);
    return 0;
}

int test_my_str_substr_cstr() {
    my_str_t str;
    char c[10];
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello world", 0);
    my_str_substr_cstr(&str, c, 0, 5);
    if (c[4] != 'o') return -1;
    if (!my_str_substr_cstr(&str, c, -3, 5)) return -1;
    if (my_str_substr_cstr(&str, c, 3, 45)) return -1;
    my_str_free(&str);
    return 0;
}

int test_my_str_reserve() {
    my_str_t str;
    char c[10];
    my_str_create(&str, 1);
    my_str_from_cstr(&str, "hello world", 0);
    size_t old_buf_size = str.capacity_m;
    my_str_reserve(&str, 100);
    if (str.capacity_m == old_buf_size) return -1;
    my_str_free(&str);
    return 0;
}


int test_my_str_shrink_to_fit() {
    my_str_t str;
    my_str_create(&str, 0);
    my_str_from_cstr(&str, "hello wonderful world, hello my dear people, hello everybody", 0);
    my_str_append_cstr(&str, "hello");
    my_str_shrink_to_fit(&str);
    if (str.size_m + 1 != str.capacity_m) return -1;
    my_str_free(&str);
    return -1;
}

int test_my_str_resize() {
    return -1;
}

int test_my_str_find() {
    return -1;
}

int test_my_str_cmp() {
    my_str_t str;
    my_str_t tmp;
    if (my_str_create(&str, 1) != 0) return -12;
    if (my_str_create(&tmp, 1) != 0) return -12;
    if (my_str_from_cstr(&str, "abcd", 0) != 0) return -13;

    if (my_str_from_cstr(&tmp, "a", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 1) return -1;

    if (my_str_from_cstr(&tmp, "bcscas", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != -1) return -2;

    if (my_str_from_cstr(&tmp, "c", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != -1) return -3;

    if (my_str_from_cstr(&str, "klmnop", 0) != 0) return -13;
    if (my_str_from_cstr(&tmp, "asdasd", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 1) return -4;

    if (my_str_from_cstr(&tmp, "b", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 1) return -5;

    if (my_str_from_cstr(&str, "gfg", 0) != 0) return -13;
    if (my_str_from_cstr(&tmp, "gbasd", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 1) return -6;

    if (my_str_from_cstr(&tmp, "gfg", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 0) return -7;

    if (my_str_from_cstr(&str, "v", 0) != 0) return -13;
    if (my_str_from_cstr(&tmp, "v", 0) != 0) return -13;
    if (my_str_cmp(&str, &tmp) != 0) return -8;

    my_str_free(&str);
    return 0;
}

int test_my_str_cmp_cstr() {
    my_str_t str;

    if (my_str_create(&str, 1) != 0) return -12;
    if (my_str_from_cstr(&str, "abcd", 0) != 0) return -13;

    if (my_str_cmp_cstr(&str, "a") != 1) return -1;

    if (my_str_cmp_cstr(&str, "bcscas") != -1) return -2;

    if (my_str_cmp_cstr(&str, "c") != -1) return -3;

    if (my_str_from_cstr(&str, "klmnop", 0) != 0) return -13;
    if (my_str_cmp_cstr(&str, "asdasd") != 1) return -4;

    if (my_str_cmp_cstr(&str, "b") != 1) return -5;

    if (my_str_from_cstr(&str, "gfg", 0) != 0) return -13;
    if (my_str_cmp_cstr(&str, "gbasd") != 1) return -6;

    if (my_str_cmp_cstr(&str, "gfg") != 0) return -7;

    if (my_str_from_cstr(&str, "v", 0) != 0) return -13;
    if (my_str_cmp_cstr(&str, "v") != 0) return -8;

    my_str_free(&str);
    return 0;
}

int test_my_str_find_c() {
    my_str_t str;
    if (my_str_create(&str, 1) != 0) return -12;
    if (my_str_from_cstr(&str, "the best test Ever, for your good mood! :)\n", 0) != 0) return -13;

    if (my_str_find_c(&str, 't', 0) != 0) return -2;
    if (my_str_find_c(&str, 't', 1) != 7) return -3;
    if (my_str_find_c(&str, 't', 9) != 9) return -4;
    if (my_str_find_c(&str, 't', 10) != 12) return -5;
    if (my_str_find_c(&str, 't', 13) != -1) return -6;
    if (my_str_find_c(&str, 't', 100) != -1) return -7;

    if (my_str_find_c(&str, 'e', 0) != 2) return -8;
    if (my_str_find_c(&str, 'e', 14) != 16) return -9;
    if (my_str_find_c(&str, 'e', 15) != 16) return -10;
    if (my_str_find_c(&str, '\n', 15) != 42) return -11;

    my_str_free(&str);
    return 0;
}

int false_pred(int c) {
    return 0;
}

int five_mod_pred(int c) {
    switch ((char) c) {
        case 'a':
            return 1;
        case 'b':
            return 1;
        case 'c':
            return 1;
    }
    return 0;
}

int test_my_str_find_if() {
    my_str_t str;
    if (my_str_create(&str, 1) != 0) return -12;
    if (my_str_from_cstr(&str, "the best test Ever, for your good mood! :)\n", 0) != 0) return -13;

    if (my_str_find_if(&str, five_mod_pred) != (size_t) (4)) return -1;
    if (my_str_find_if(&str, false_pred) != (size_t) (-1)) return -2;

    my_str_free(&str);
    return 0;
}

int test_my_str_read_file() {
    // read the file docs/alice29.txt and checks the number of characters that should be 152089
    my_str_t str;
    FILE* alice_p = fopen("../docs/alice29.txt", "r");

    if (alice_p == NULL) return -11;
    if (my_str_create(&str, 1) != 0) return -12;

//    delimiter is not in file
    if (my_str_read_file(&str, alice_p) != 0) return -1;
    if (str.size_m != 152089) return -2;

    my_str_free(&str);
    fclose(alice_p);
    return 0;
}

int test_my_str_write_file() {
    // create file "docs/test_out.txt" with content "test_my_str_write_file\n"
    my_str_t str;
    FILE* output_p = fopen("../docs/test_out.txt", "w");

    if (output_p == NULL) return -11;
    if (my_str_create(&str, 1) != 0) return -12;
    if (my_str_from_cstr(&str, "test_my_str_write_file\n", 0) != 0) return -13;
    if (my_str_write_file(&str, output_p) != 0) return -1;

    my_str_free(&str);
    fclose(output_p);
    return 0;
}

int test_my_str_read_file_delim() {
    my_str_t str;
    FILE* alice_p = fopen("../docs/alice29.txt", "r");
    if (alice_p == NULL) return -11;
//    char c = (char) fgetc(alice_p);
//    fseek(alice_p, 26, SEEK_CUR);
//    char c2_res = (char) fgetc(alice_p);
//    char c2 = (char) fgetc(alice_p);
//    rewind(alice_p);
    my_str_create(&str, 1);
//    delimiter on the very beginning
    if (my_str_read_file_delim(&str, alice_p, '\r') != 0) return -1;
    if (str.size_m) return -2;
    rewind(alice_p);  // reset the cursor of the file

//    delimiter on the firs page
    if (my_str_read_file_delim(&str, alice_p, 'E') != 0) return -3;
    if (str.size_m != 28 && str.data[27] == 'S') return -4;
    rewind(alice_p);

//    delimiter is not in file
    if (my_str_read_file_delim(&str, alice_p, '{') != 0) return -5;
    if (str.size_m != 152089) return -6;
    rewind(alice_p);

    my_str_free(&str);
    fclose(alice_p);
    return 0;
}
