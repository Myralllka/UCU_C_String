#include <ctime>
#include <iostream>
#include "../cpp_wrapper/CString.h"
#include <string>

CString test(0);
CString another_test(0);
std::string str;
std::string another_str;
char buffer[20];

void set_up() {
    another_test.clear();
    test.clear();
    test.from_cstr("abcdeaaa", 0);
    another_test.from_cstr("aaa", 0);
    str = "abcdeaaa";
    another_str = "aaa";
}

void print_res(std::pair<double, double> res) {
    std::cout << "     OWN: " << res.first << "\n";
    std::cout << "BUILT-IN: " << res.second << "\n";
    std::cout << "Difference is " << res.first / res.second << " times\n";
    std::cout << "-----------------------------------------------------------------\n";
}

std::pair<double, double> check_pushback() {
    std::cout << "ADD CHAR\n";
    set_up();
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 200000; i++)
        test.pushback('c');
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < 200000; i++)
        str.push_back('c');
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_append_cstr() {
    std::cout << "APPEND_CSTR\n";
    set_up();
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 200000; i++)
        test.append_cstr("aa");
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 200000; i++)
        str.append("aa");
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_empty() {
    std::cout << "EMPTY\n";

    set_up();
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.empty();
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str.empty();
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_getc() {
    std::cout << "GETC\n";

    set_up();
    test.from_cstr("aaa", 0);
    str = "aaa";
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.getc(1);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str[1];
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_putc() {
    std::cout << "PUTC\n";

    set_up();
    test.from_cstr("aaa", 0);
    str = "aaa";
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.putc(1, 'd');
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str[1] = 'd';
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_popback() {
    std::cout << "POPBACK\n";

    set_up();
    for (int i = 0; i < 20000; i++) {
        str.push_back('a');
        test.pushback('a');
    }

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 20000; i++)
        test.popback();
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 20000; i++)
        str.pop_back();
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_copy() {
    std::cout << "COPY\n";

    set_up();
    str = "abcdefg";
    test.from_cstr("abcdefg", 0);

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.copy(&another_test, 0);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str.copy(buffer, 7, 0);
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_insert() {
    std::cout << "INSERT\n";

    set_up();

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 80000; i++)
        test.insert(&another_test, 2);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 80000; i++)
        str.insert(0, another_str);
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_substr() {
    std::cout << "SUBSTR\n";

    set_up();

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.substr(&another_test, 0, 4);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str.substr(0, 4);
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_find() {
    std::cout << "FIND\n";

    set_up();

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.find(&another_test, 0);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str.find(another_str, 0);
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}

std::pair<double, double> check_cmp() {
    std::cout << "CMP\n";

    set_up();

    clock_t start, end;
    start = clock();
    for (int i = 0; i < 2000000; i++)
        test.cmp(&another_test);
    end = clock();
    double own_lib_time = double(end - start) / double(CLOCKS_PER_SEC);
    start = clock();
    for (int i = 0; i < 2000000; i++)
        str.compare(another_str);
    end = clock();
    double builtin_lib_time = double(end - start) / double(CLOCKS_PER_SEC);

    return std::make_pair(own_lib_time, builtin_lib_time);
}


int main() {
    print_res(check_pushback());
    print_res(check_popback());
    print_res(check_append_cstr());
    print_res(check_empty());
    print_res(check_getc());
    print_res(check_putc());
    print_res(check_copy());
    print_res(check_insert());
    print_res(check_substr());
    print_res(check_find());
    print_res(check_cmp());
}

