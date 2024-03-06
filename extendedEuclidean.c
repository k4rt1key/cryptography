#include <stdio.h>
#include <math.h>

int inverse(int q, int a, int b, int r, int t1, int t2, int t)
{

    // if remainder is 0, then return t1
    if (r == 0)
    {
        return t1;
    }

    // quotient = floor(a / b)
    // remainder = a % b
    // t = (t1 - t2) * q
    q = floor(a / b);
    r = a % b;
    t = (t1 - t2) * q;

    // now moving to next step
    a = b;
    b = r;
    t1 = t2;
    t2 = t;

    // printf("q: %d, a: %d, b: %d, r: %d, t1: %d, t2: %d, t: %d\n", q, a, b, r, t1, t2, t);
    inverse(q, a, b, r, t1, t2, t);
}

void solution()
{
    int a, b;
    printf("Enter the value of a and b: ");
    scanf("%d %d", &a, &b);

    if (a < b)
    {
        printf("Inverse of %d mod %d does not exist\n", b, a);
        return;
    }

    if (a % b == 0)
    {
        printf("Inverse of %d mod %d does not exist\n", b, a);
        return;
    }

    int ans = inverse(-1, a, b, -1, 0, 1, -1);

    if (ans == 0)
    {
        printf("Inverse of %d mod %d does not exist\n", b, a);
        return;
    }

    while (ans < 0)
    {
        ans = ans + a;
    }

    printf("Inverse of %d mod %d is %d\n", b, a, ans);
}

int main()
{
    solution();
    return 0;
}