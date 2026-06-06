/**
 * @file hello_test.c
 * @author tinysec
 * @brief
 * @version 0.0.1
 * 2023-09-02   init
 */

#include <hello/hello.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    return foobar(1, 2) == 3 ? 0 : 1;
}
