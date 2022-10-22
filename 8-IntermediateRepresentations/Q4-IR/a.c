#include <stdio.h>

int fact(int n)
{
    int i, j = 1;
    for (i = 1; i <= n; i++)
    {
        j = j * i;
    }
    return j;
}

int main(int argc, char **argv)
{
    int n, res;
    scanf("%d", &n);
    res = fact(n);

    printf("Value of fact(%d): %d\n", n, res);
    return 0;
}