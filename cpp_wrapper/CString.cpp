//
// Created by kumquat on 10/15/19.
//

#include "CString.h"



CString::CString(size_t buf_size) {
    my_str_create(&str, buf_size);
}

void CString::clear() {
    my_str_clear(&str);
}

CString::~CString() {
    my_str_free(&str);
}

int CString::from_cstr(const char *cstr, size_t buf_size) {
    return my_str_from_cstr(&str, cstr, buf_size);
}

size_t CString::size() {
    return my_str_size(&str);
}

size_t CString::capacity() {
    return my_str_capacity(&str);
}

int CString::empty() {
    return my_str_empty(&str);
}

int CString::getc(size_t index) {
    return my_str_getc(&str, index);
}

int CString::putc(size_t index, char c) {
    return my_str_putc(&str, index, c);
}

int CString::pushback(char c) {
    return my_str_pushback(&str, c);
}

int CString::popback() {
    return my_str_popback(&str);
}

int CString::copy(CString *to, int reserve) {
    CString new_str(0);
    return my_str_copy(&str, &((*to).str), reserve);
}

int CString::insert_c(char c, size_t pos) {
    return my_str_insert_c(&str, c, pos);
}

int CString::insert(CString *from, size_t pos) {
    return my_str_insert(&str, &(*from).str, pos);
}

int CString::insert_cstr(const char *from, size_t pos) {
    return my_str_insert_cstr(&str, from, pos);
}

int CString::append(CString *from) {
    return my_str_append(&str, &(*from).str);
}

int CString::append_cstr(const char *from) {
    return my_str_append_cstr(&str, from);
}

int CString::substr(CString *to, size_t beg, size_t end) {
    return my_str_substr(&str, &(*to).str, beg, end);
}

int CString::substr_cstr(char *to, size_t beg, size_t end) {
    return my_str_substr_cstr(&str, to, beg, end);
}

int CString::reserve(size_t buf_size) {
    return my_str_reserve(&str, buf_size);
}

int CString::resize(size_t new_size, char sym) {
    return my_str_resize(&str, new_size, sym);
}

int CString::shrink_to_fit() {
    return my_str_shrink_to_fit(&str);
}

size_t CString::find(CString *tofind, size_t from) {
    return my_str_find(&str, &(*tofind).str, from);
}

int CString::cmp(CString *str2) {
    return my_str_cmp(&str, &(*str2).str);
}

int CString::cmp_cstr(const char *cstr2) {
    return my_str_cmp_cstr(&str, cstr2);
}

size_t CString::find_c(char tofind, size_t from) {
    return my_str_find_c(&str, tofind, from);
}

size_t CString::find_if(int (*predicat)(int)) {
    return my_str_find_if(&str, (*predicat));
}

int CString::read_file(FILE *file) {
    return my_str_read_file(&str, file);
}

int CString::read() {
    return my_str_read(&str);
}

int CString::write_file(FILE *file) {
    return my_str_write_file(&str, file);
}

int CString::write() {
    return my_str_write(&str);
}

int CString::read_file_delim(FILE *file, char delimiter) {
    return my_str_read_file_delim(&str, file, delimiter);
}