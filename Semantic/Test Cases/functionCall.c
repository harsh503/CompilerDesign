#include<stdio.h>

int sum(int a,int b)
{
    int c;
    c = a + b;
    return c;
}

int main()
{
    int q;
    q = 10;
    int d = sum(5,q);

    int e = sum(5,q,d);

    int f = sum(5.5,q);

    return 0;
}