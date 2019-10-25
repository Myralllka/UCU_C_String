#include "lib/include/c_string.h"
#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        FILE *read_file = fopen(argv[1], "r");
        if (read_file == NULL) return 1;
        FILE *write_file = fopen(argv[2], "w");
        if (write_file == NULL) {
            fclose(read_file);
            return 1;
        }

        my_str_t line;
        my_str_create(&line, 360000);
        my_str_read_file(&line, read_file);

        my_str_sort_words(&line);

        my_str_write_file(&line, write_file);

        my_str_free(&line);
        fclose(read_file);
        fclose(write_file);
    } else {
        printf("! please enter file names in the command row\n");
    }
    return 0;
}

char to_lower(char c) {
    char letters[52] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e',
                        'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j',
                        'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o',
                        'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't',
                        'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'};
    for (size_t i = 0; i < 52; i++)
        if (c == letters[i]) {
            if (i % 2 == 0)
                return letters[++i];
            else
                return letters[i];
        }
}

int is_alpha(char c) {
    char letters[52] = {'A', 'a', 'B', 'b', 'C', 'c', 'D', 'd', 'E', 'e',
                        'F', 'f', 'G', 'g', 'H', 'h', 'I', 'i', 'J', 'j',
                        'K', 'k', 'L', 'l', 'M', 'm', 'N', 'n', 'O', 'o',
                        'P', 'p', 'Q', 'q', 'R', 'r', 'S', 's', 'T', 't',
                        'U', 'u', 'V', 'v', 'W', 'w', 'X', 'x', 'Y', 'y', 'Z', 'z'};
    for (size_t i = 0; i < 52; i++)
        if (c == letters[i])
            return 0;
    return -1;
}

void insertionSort(char* elements, size_t a, size_t b) {
    for (size_t i = a + 1; i < b + 1; i++) {
        char x = elements[i];
        size_t j = i - 1;
        while (to_lower(elements[j]) > to_lower(x) && j >= a) {
            elements[j + 1] = elements[j];
            j--;
        }
        elements[j + 1] = x;
    }
}

void my_str_sort_words(my_str_t *str) {
    size_t n = my_str_size(str);
    size_t word_start = 0;
    int word_end = -1; // no int since we need negative value
    for (size_t i = 0; i < n; i++) {
        if (is_alpha(str -> data[i]) == 0) {
            word_end++;
        } else {
            insertionSort(str -> data, word_start, word_end);
            if (i + 1 < n)
                word_start = i + 1;
            word_end = i;
        }
    }
}
