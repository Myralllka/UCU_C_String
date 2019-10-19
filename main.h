#ifndef MAIN_H
#define MAIN_H

char to_lower(char c);
void swap(char *elements, size_t k, size_t t);
int is_alpha(char c);
size_t partition(char *elements, size_t a, size_t b);
void quickSort(char *elements, size_t a, size_t b);
void my_str_sort_words(my_str_t *str);
#endif // MAIN_H