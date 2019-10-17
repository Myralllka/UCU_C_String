#include "test.h"
#include "../lib/include/c_string.h"


int tests(void) {
    char* names[] = {"test_my_str_create",         // 1
                     "test_my_str_from_cstr",      // 2
                     "test_my_str_size",           // 3
                     "test_my_str_capacity",       // 4
                     "test_my_str_empty",          // 5
                     "test_my_str_getc",           // 6
                     "test_my_str_putc",           // 7
                     "test_my_str_get_cstr",       // 8
                     "test_my_str_pushback",       // 9
                     "test_my_str_popback",        // 10
                     "test_my_str_copy",           // 11

//                     "test_my_str_insert_c",       // 12
//                     "test_my_str_insert",         // 13
//                     "test_my_str_insert_cstr",    // 14
//                     "test_my_str_append",         // 15
//                     "test_my_str_append_cstr",    // 16
//                     "test_my_str_substr",         // 17
//                     "test_my_str_substr_cstr",    // 18
//                     "test_my_str_reserve",        // 19
//                     "test_my_str_shrink_to_fit",  // 20
//                     "test_my_str_resize",         // 21
//                     "test_my_str_find",           // 22

                     "test_my_str_cmp",            // 15
                     "test_my_str_cmp_cstr",       // 16
                     "test_my_str_find_c",         // 17
                     "test_my_str_find_if",
                     "test_my_str_read_file",      // 18
                     "test_my_str_write_file",     // 19
                     "test_my_str_read_file_delim"};// 20

    int (*functions[])(void) = {test_my_str_create,         // 1
                                test_my_str_from_cstr,      // 2
                                test_my_str_size,           // 3
                                test_my_str_capacity,       // 4
                                test_my_str_empty,          // 5
                                test_my_str_getc,           // 6
                                test_my_str_putc,           // 7
                                test_my_str_get_cstr,       // 8
                                test_my_str_pushback,       // 9
                                test_my_str_popback,        // 10
                                test_my_str_copy,           // 11

//                                test_my_str_insert_c,       // 12
//                                test_my_str_insert,         // 13
//                                test_my_str_insert_cstr,    // 14
//                                test_my_str_append,         // 15
//                                test_my_str_append_cstr,    // 16
//                                test_my_str_substr,         // 17
//                                test_my_str_substr_cstr,    // 18
//                                test_my_str_reserve,        // 19
//                                test_my_str_shrink_to_fit,  // 20
//                                test_my_str_resize,         // 21
//                                test_my_str_find,           // 22

                                test_my_str_cmp,            // 15
                                test_my_str_cmp_cstr,       // 16
                                test_my_str_find_c,         // 17
                                test_my_str_find_if,
                                test_my_str_read_file,      // 18
                                test_my_str_write_file,     // 19
                                test_my_str_read_file_delim};// 20
    for (int i = 0; i < 18; ++i) {
        int res = (functions[i])();
        if (res)
            printf("Test %i '%s':\t\tFail %i\n", i + 1, names[i], res);
//        else
//            printf("Test %i: OK\n", i + 1);
    }

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
    return -1;
}

int test_my_str_insert() {
    return -1;
}

int test_my_str_insert_cstr() {
    return -1;
}

int test_my_str_append() {
    return -1;
}

int test_my_str_append_cstr() {
    return -1;
}

int test_my_str_substr() {
    return -1;
}

int test_my_str_substr_cstr() {
    return -1;
}

int test_my_str_reserve() {
    return -1;
}

int test_my_str_shrink_to_fit() {
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
    if (my_str_create(&str, 1) != 0) return -12;

//    delimiter on the very beginning
    if (my_str_read_file_delim(&str, alice_p, '\n') != 0) return -1;
    if (str.size_m != 0) return -2; // !!! somehow  str.size_m = 1
    rewind(alice_p);  // reset the cursor of the file

    // debug lines
//    printf("res: %i\n", my_str_read_file_delim(&str, alice_p, 'E'));
//    printf("res: %zu\n", str.size_m);
//    printf("%c", str.data[0]);
//    for (size_t i = 0; i <= str.size_m; ++i) {
//        printf("%zu%c", i, str.data[i]);
//    }
//    printf("\n");
//    rewind(alice_p);

//    delimiter on the firs page
    if (my_str_read_file_delim(&str, alice_p, 'E') != 0) return -3;
    if (str.size_m != 24) return -4;
    rewind(alice_p);
//    delimiter is not in file
    if (my_str_read_file_delim(&str, alice_p, '{') != 0) return -5;
    if (str.size_m != 152089) return -6;
    rewind(alice_p);

    my_str_free(&str);
    fclose(alice_p);
    return 0;
}
