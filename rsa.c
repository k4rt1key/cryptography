#include <stdlib.h>
#include <stdio.h>

int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
};

// returns array of strings
// 0th element is public key
// 1st element is private key
int *rsaKeyGeneration(int p, int q)
{
    int *keys = (int *)malloc(2 * sizeof(int));
    // TODO: implement RSA key generation
    int n = p * q;
    int phiOfN = (p - 1) * (q - 1);

    for (int e = 2; e < phiOfN; e++)
    {
        if (gcd(e, phiOfN) == 1)
        {
            // e is public key
            keys[0] = e;
            break;
        }
    }

    for (int d = 2; d < phiOfN; d++)
    {
        if (gcd((d * keys[0]), phiOfN) == 1)
        {
            // d is private key
            keys[1] = d;
            break;
        }
    }

    return keys;
}

int encryption(int p, int q, int e, int m)
{
    // encrypting the message m
    int n = p * q;
    int c = (m ^ e) % n;
    return c;
}

int decryption(int p, int q, int d, int c)
{
    // decrypting the cipher c
    int n = p * q;
    int m = (c ^ d) % n;
    return m;
}

int main()
{

    int p[] = {
        97,
        98,
        99,
        100,
    };
    printf("Original message: ");

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        char ch = (char)p[i];
        printf("%c", ch);
    }

    int *keys = rsaKeyGeneration(5, 11);
    int c[sizeof(p) / sizeof(p[0])];

    for (int i = 0; i < sizeof(p) / sizeof(p[0]); i++)
    {
        c[i] = encryption(211, 223, keys[0], p[i]);
    }

    printf("\n");
    printf("Encrypted message: ");
    for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++)
    {
        char ch = (char)c[i];
        printf("%c", ch);
    }

    // now decrypting the message
    int m[sizeof(p) / sizeof(p[0])];

    for (int i = 0; i < sizeof(c) / sizeof(c[0]); i++)
    {
        m[i] = decryption(211, 223, keys[1], c[i]);
    }
    printf("\n");
    printf("Decrypted message: ");
    for (int i = 0; i < sizeof(m) / sizeof(m[0]); i++)
    {
        char ch = (char)m[i];
        printf("%c", ch);
    }

    return 0;
}