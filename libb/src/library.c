#include "../include/library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
    str->capacity_m = real_cstring_size * 2 + 1;
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
    // return if str is empty or not, -1 for NULL pointer
    if (str == NULL) return -1;
    return !str->size_m;
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

int my_str_pushback(my_str_t *str, char c) {
    if (str == NULL)
        return -1;
    if (my_str_reserve(str, str->size_m + 1) == -1)
        return -2;
    str->data[str->size_m] = c;
    str->size_m++;
    return 0;
}

int my_str_popback(my_str_t *str) {
    if (str == NULL)
        return -1;
    if (str->size_m == 0) {
        return -2;
    }
    str->size_m--;
    return str->data[str->size_m];
}

int my_str_copy(const my_str_t *from, my_str_t *to, int reserve) {
    int new_buffer;
    if (reserve)
        new_buffer = from->capacity_m;
    else
        new_buffer = from->size_m;
    if (my_str_reserve(to, new_buffer) != 0)
        return -1;
    memmove(to->data, from->data, from->size_m);
    to->capacity_m = new_buffer;
    to->size_m = from->size_m;
    return 0;
}

void my_str_clear(my_str_t *str) {
    str->size_m = 0;
}

int my_str_insert_c(my_str_t *str, char c, size_t pos) {
    if (str == NULL)
        return -1;
    if (pos > str->size_m)
        return -2;
    if (my_str_reserve(str, str->size_m + 1) != 0)
        return -3;
    memmove(str->data + pos + 1, str->data + pos, str->size_m - pos);
    str->size_m++;
    str->data[pos] = c;
    return 0;
}

int my_str_insert(my_str_t *str, const my_str_t *from, size_t pos) {
    if (str == NULL || from == NULL)
        return -1;
    if (pos > str->size_m)
        return -2;
    if (my_str_reserve(str, str->size_m + from->size_m) != 0)
        return -3;
    memmove(str->data + pos + from->size_m, str->data + pos, str->size_m - pos);
    memcpy(str->data + pos, from->data, from->size_m);
    str->size_m += from->size_m;
    return 0;
}

int my_str_insert_cstr(my_str_t *str, const char *from, size_t pos) {
    my_str_t temp;
    my_str_create(&temp, 0);
    my_str_from_cstr(&temp, from, 0);
    int res = my_str_insert(str, &temp, pos);
    my_str_free(&temp);
    return res;
}

int my_str_append(my_str_t *str, const my_str_t *from) {
    return my_str_insert(str, from, str->size_m);
}

int my_str_append_cstr(my_str_t *str, const char *from) {
    return my_str_insert_cstr(str, from, str->size_m);
}

static int check_borders(const my_str_t *str, size_t beg, size_t *end) {
    if (!(beg >= 0 && beg < str->size_m) || *end < beg)
        return 0;
    if (*end > str->size_m)
        *end = str->size_m;
    return 1;
}

int my_str_substr(const my_str_t *from, my_str_t *to, size_t beg, size_t end) {
    if (!check_borders(from, beg, &end))
        return -1;
    if (my_str_reserve(to, end - beg) != 0)
        return -2;
    memmove(to->data, from->data + beg, end - beg);
    to->size_m = end - beg;
    return 0;
}

int my_str_substr_cstr(const my_str_t *from, char *to, size_t beg, size_t end) {
    if (!check_borders(from, beg, &end))
        return -1;
    printf("%i\n", sizeof(to));
    memmove(to, from->data + beg, end - beg);
    to[end - beg] = '\0';
    return 0;
}

int my_str_reserve(my_str_t *str, size_t buf_size) {
    // increase buff size of my_str if new_size is bigger then previous one
    // if new_size is equal or less - nothing.
    // for increasing size - make new buffer and copy my_str into it and make it empty.
    // return negative numbers if something get wrong, 0 otherwise.
    if (str == NULL) {
        return -1;
    }
    if (str->capacity_m >= buf_size) {
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

int my_str_resize(my_str_t *str, size_t new_size, char sym) {
    if (new_size < 0)
        return -1;
    if (new_size <= str->size_m) {
        str->size_m = new_size;
        return 0;
    }
    if (!my_str_reserve(str, new_size))
        return -1;
    for (size_t i = str->size_m; i < new_size; i++) {
        str->data[i] = sym;
    }
    str->size_m = new_size;
    return 0;
}

// not tested
int my_str_shrink_to_fit(my_str_t *str) {
    if (str == NULL) return -1;

    if (str->size_m + 1 != str->capacity_m) {
        if (my_str_realloc(str, str->size_m) == -1)
            return -2;
    }
    return 0;
}


// TODO: test my_str_find AND possibly delete input checks
size_t my_str_find(const my_str_t *str, const my_str_t *tofind, size_t from) {
    if (NULL == str || tofind == NULL || str->size_m < tofind->size_m || from >= str->size_m || from < 0 ||
        tofind->size_m == 0)
        return (size_t) (-2);
//    if (tofind->size_m == 0)
//        return (size_t)(-1);

    size_t i = from, match = 0;
    while (i < str->size_m && match < tofind->size_m) {
        if (str->data[i] == tofind->data[match])
            match++;
        else
            match = 0;
        i++;
    }
    if (match == tofind->size_m)
        return i - match;
    else
        return (size_t) (-1);
}

int my_str_cmp(const my_str_t *str1, const my_str_t *str2) {
    size_t i = 0;
    while (i < (*str1).size_m && i < (*str2).size_m) {
        if ((*str1).data[i] > (*str2).data[i])
            return 1;
        else if ((*str1).data[i] < (*str2).data[i])
            return -1;
        i++;
    }
    if ((*str1).size_m > (*str2).size_m)
        return 1;
    else if ((*str1).size_m < (*str2).size_m)
        return -1;
    return 0;
}

// TODO: test my_str_cmp_cstr
int my_str_cmp_cstr(const my_str_t *str1, const char *cstr2) {
    size_t str2_len = char_arr_len(cstr2);
    if (str1->size_m > str2_len)
        return 1;
    else if (str1->size_m < str2_len)
        return -1;
    else {
        for (int j = 0; j < str1->size_m; ++j) {
            if (str1->data[j] != cstr2[j])
                return -1;
        }
        return 0;
    }
}

// TODO: test my_str_find_c
size_t my_str_find_c(const my_str_t *str, char tofind, size_t from) {
    if (from > str->size_m)
        return -1;
    if (from < 0)
        from = 0;
//        exit(1);

    for (size_t j = from; j < str->size_m; ++j) {
        if (str->data[j] == tofind)
            return j;
    }
    return (size_t) (-1);
}

// TODO: test my_str_find_if
size_t my_str_find_if(const my_str_t *str, int (*predicat)(int)) {
    for (int j = 0; j < str->size_m; ++j) {
        if (predicat(str->data[j]))
            return j;
    }
    return (size_t) (-1);
}

int my_str_read_file(my_str_t *str, FILE *file) {
    return 1;
}

int my_str_read(my_str_t *str) {
    return 1;
}

int my_str_write_file(const my_str_t *str, FILE *file) {
    return 1;
}

int my_str_write(const my_str_t *str, FILE *file) {
    return 1;
}

int my_str_read_file_delim(my_str_t *str, FILE *file, char delimiter) {
    return 1;
}


/*********************************************************************/
// TODO: TEST this helper function (used in "my_str_shrink_to_fit")
// TODO: REWRITE with memcpy or memmove
int my_str_realloc(my_str_t *str, size_t buffer) {
    char *data_p = (char *) malloc(buffer + 1);

    if (data_p == NULL) return -1;

    if (str->size_m > buffer)
        str->size_m = buffer;

    memmove(data_p, str->data, str->size_m);
    data_p[buffer] = '\0';
    free(str->data);
    str->data = data_p;
    str->capacity_m = buffer + 1;
    return 0;
}

// TODO: DELETE after use of "memcpy" or "memmove"
size_t char_arr_len(const char *s) {
    size_t i = 0;
    while (*(s + i) != '\0') {
        i++;
    }
    return i;
}
