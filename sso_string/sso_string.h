#ifndef C_STRING_SSO_STRING_H
#define C_STRING_SSO_STRING_H

#include "../lib/include/c_string.h"

union sso_str_t {
    bool small_flag;
    size_t capacity_m;
    size_t size_m;
    char *data;
    my_str_t long_str;
};

void so_str_create(sso_str* str, size_t buf_size);
void so_str_free(sso_str* str);
int sso_str_from_cstr(sso_str_t *str, const char *cstr, size_t buf_size);

size_t sso_str_size(const sso_str_t *str);
size_t sso_str_capacity(const sso_str_t *str);
int sso_str_empty(const sso_str_t *str);

int sso_str_getc(const sso_str_t *str, size_t index);
int sso_str_putc(sso_str_t *str, size_t index, char c);
const char *sso_str_get_cstr(sso_str_t *str);

int sso_str_pushback(sso_str_t *str, char c);
int sso_str_popback(sso_str_t *str);
int sso_str_copy(const sso_str_t *from, sso_str_t *to, int reserve);
void sso_str_clear(sso_str_t *str);
int sso_str_insert_c(sso_str_t *str, char c, size_t pos);
int sso_str_insert(sso_str_t *str, const sso_str_t *from, size_t pos);
int sso_str_insert_cstr(sso_str_t *str, const char *from, size_t pos);
int sso_str_append(sso_str_t *str, const sso_str_t *from);
int sso_str_append_cstr(sso_str_t *str, const char *from);
int sso_str_substr(const sso_str_t *from, sso_str_t *to, size_t beg, size_t end);
int sso_str_substr_cstr(const sso_str_t *from, char *to, size_t beg, size_t end);

int sso_str_reserve(sso_str_t *str, size_t buf_size);
int sso_str_shrink_to_fit(sso_str_t *str);
int sso_str_resize(sso_str_t *str, size_t new_size, char sym);

size_t sso_str_find(const sso_str_t *str, const sso_str_t *tofind, size_t from);
int sso_str_cmp(const sso_str_t *str1, const sso_str_t *str2);
int sso_str_cmp_cstr(const sso_str_t *str1, const char *cstr2);
size_t sso_str_find_c(const sso_str_t *str, char tofind, size_t from);
size_t sso_str_find_if(const sso_str_t *str, int (*predicat)(int));

int sso_str_read_file(sso_str_t *str, FILE *file);
int sso_str_read(sso_str_t *str);
int sso_str_write_file(const sso_str_t *str, FILE *file);
int sso_str_write(const sso_str_t *str);
int sso_str_read_file_delim(sso_str_t *str, FILE *file, char delimiter);

#endif //C_STRING_SSO_STRING_H
