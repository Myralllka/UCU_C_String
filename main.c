#include <stdio.h>
#include "main.h"
//#include "libb/library.c"
#include "libb/library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "tests.c"

int main(void) {
    my_str_t x;
    my_str_create(&x, 7);
    char *cst = "aaaa";
    my_str_from_cstr(&x, cst, 0);
//    puts("asdasd");
//    printf("%s", my_str_get_cstr(&x));
    puts(my_str_get_cstr(&x));
    printf("%d", my_str_size(&x));
}

int my_str_create(my_str_t *str, size_t buf_size) {
    // constructor of my_str_t object
    //return -1 if null pointer given, 0 otherwise
    str->capacity_m = buf_size + 1;
    str->size_m = 0;
    str->data = (char *) calloc(str->capacity_m, sizeof(char));
    if (str->data == NULL) {
        return -1;
    }
    return 0;
};

void my_str_free(my_str_t *str) {
    // delete memory of my_str_t
    free(str->data);
}

int my_str_from_cstr(my_str_t *str, const char *cstr, size_t buf_size) {
    // make my_str from cstring.
    // if buf_size == 0 then buf_size will be equal to real size
    // return -1 if buf size is less then real size then it is a mistake
    // return -2 if it is impossible to give enough memory
    //return 0 if everything is Ok
    size_t real_cstring_size = 0;
    while (*(cstr + real_cstring_size) != '\0') {
        real_cstring_size += 1;
    }
    if (buf_size == 0) {
        buf_size = real_cstring_size + 1;
    } else if (buf_size < real_cstring_size) {
        return -1;
    }
    int checker = my_str_reserve(str, real_cstring_size * 2 + 1);
    if (checker) {
        return -2;
    }
    memcpy(str->data, cstr, real_cstring_size);
    str->size_m = real_cstring_size;
    str->capacity_m = real_cstring_size*2+1;
    return 0;
}

size_t my_str_size(const my_str_t *str) {
    // Return size of your string.
    // 0 for NULL pointer
    if (str == NULL) return 0;
    return str->size_m;
}

size_t my_str_capacity(const my_str_t *str) {
    //Return buffer size (capacity) of the str
    //0 for NULL pointer
    if (str == NULL) return 0;
    return str->capacity_m;
}

int my_str_empty(const my_str_t *str) {
    // return if str is empty or not
    if (str == NULL) return 0;
    return str->size_m;
}

int my_str_getc(const my_str_t *str, size_t index) {
    //return -1 if index is incorrect, otherwise the char on needed position
    if (str == NULL) return -1;
    if ((index > str->size_m - 1) || (index < 0)) return -1;
    return str->data[index];
}

int my_str_putc(my_str_t *str, size_t index, char c) {
    // return -1 if index is incorrect, otherwise 0
    // and put char c on the index place
    if (str == NULL) return -1;
    if ((index > str->size_m - 1) || (index < 0)) return -1;
    str->data[index] = c;
    return 0;
}

const char *my_str_get_cstr(my_str_t *str) {
    //return pointer on the C_string
    str->data[str->size_m + 1] = '\0';
    return str->data;
}

int my_str_pushback(my_str_t *str, char c) {}

int my_str_popback(my_str_t *str) {}

int my_str_copy(const my_str_t *from, my_str_t *to, int reserve) {}

void my_str_clear(my_str_t *str) {}

int my_str_insert_c(my_str_t *str, char c, size_t pos) {}

int my_str_insert(my_str_t *str, const my_str_t *from, size_t pos) {}

int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos) {}

int my_str_append(my_str_t *str, const my_str_t *from) {}

int my_str_append_cstr(my_str_t *str, const char *from) {}

int my_str_substr(const my_str_t *from, my_str_t *to, size_t beg, size_t end) {}

int my_str_substr_cstr(const my_str_t *from, char *to, size_t beg, size_t end) {}

int my_str_reserve(my_str_t *str, size_t buf_size) {
    // increase buff size of my_str if new_size is bigger then previous one
    // if new_size is equal or less - nothing.
    // for increasing size - make new buffer and copy my_str into it and make it empty.
    // return negative numbers if something get wrong, 0 otherwise.
    if (str == NULL) {
        return -1;
    }
    if (str->size_m > buf_size) {
        return 0;
    }
    char *new_str = (char *) calloc(buf_size, sizeof(char));
    if (new_str == NULL) {
        return -2;
    }
    memmove(new_str, str->data, str->size_m);
    my_str_free(str);
    str->data = new_str;
    str->capacity_m = buf_size;
    return 0;
}

int my_str_shrink_to_fit(my_str_t *str) {}

int my_str_resize(my_str_t *str, size_t new_size, char sym) {}

size_t my_str_find(const my_str_t *str, const my_str_t *tofind, size_t from) {}

int my_str_cmp(const my_str_t *str1, const my_str_t *str2) {}

int my_str_cmp_cstr(const my_str_t *str1, const char *cstr2) {}

size_t my_str_find_c(const my_str_t *str, char tofind, size_t from) {}

size_t my_str_find_if(const my_str_t *str, int (*predicat)(int)) {}

int my_str_read_file(my_str_t *str, FILE *file) {}

int my_str_read(my_str_t *str) {}

int my_str_write_file(const my_str_t *str, FILE *file) {}

int my_str_write(const my_str_t *str, FILE *file) {}

int my_str_read_file_delim(my_str_t *str, FILE *file, char delimiter) {}
