#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    while (1)
    {
        sleep(1);
        system("leaks -q so_long");
    }
}