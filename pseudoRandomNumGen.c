#include <stdio.h>
#include <math.h>

int rand(long long int seed)
{
    long long int multiplier = 1103515245;
    long long int increment = 12345;
    long long int modulus = pow(2, 31) - 1;
    return (multiplier * seed + increment) % modulus;
}

int main()
{

    long long int seed = 828;
    for (int i = 0; i < 1000; i++)
    {
        seed = rand(seed);
        printf("%lli\n", seed);
    }

    return 0;
}
