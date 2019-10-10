#include <stdio.h>

//#include "libb/library.c"
#include "libb/src/library.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    my_str_t x;
    my_str_create(&x, 7);
    char *cst = "aaaa";
    my_str_from_cstr(&x, cst, 0);
//    puts("asdasd");
//    printf("%s", my_str_get_cstr(&x));
    puts(my_str_get_cstr(&x));
    printf("%zu", my_str_size(&x));
    my_str_free(&x);
}
