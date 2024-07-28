#include <stdio.h>
#include <lib/func_a/func_a.h>
#include <lib/func_b/func_b.h>

int main(int argc, char *argv[])
{
    func_a();
    func_b();

    printf("main.\n");

    return 0;
}