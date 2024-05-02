#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// NOTE :
// OUTPUT OF CCA2 IN THIS PROGRAM IS NOT CORRECT
// BUT RSA ENCRYPTION AND DECRYPTION IS WORKING FINE

int inverse(int q, int a, int b, int r, int t1, int t2, int t)
{

    if (b == 0)
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

    // if remainder is 0, then return t1

    inverse(q, a, b, r, t1, t2, t);
}

int gcd(int a, int b)
{
    if (a == 0)
    {
        return b;
    }
    return gcd(b % a, a);
}

int multiplicativeInverse(int a, int b)
{

    int ans;
    if (a < b)
    {
        ans = inverse(-1, b, a, -1, 0, 1, -1);
    }

    if (a % b == 0)
    {
        printf("Multiplicative Inverse of %d mod %d does not exist\n", b, a);
        return 0;
    }

    ans = inverse(-1, a, b, -1, 0, 1, -1);

    if (ans == 0)
    {
        printf("Multiplicative Inverse of %d mod %d does not exist\n", b, a);
        return 0;
    }

    while (ans < 0)
    {
        ans = ans + a;
    }

    printf("Multiplicative Inverse of %d mod %d is %d\n", b, a, ans);
    return ans;
}

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

    // cheking if rsa is working or not
    int p = 47;
    int q = 71;
    int N = p * q;

    int *keys = rsaKeyGeneration(p, q);
    int e = keys[0];
    int d = keys[1];

    int m = 78;
    int c = encryption(p, q, e, m);
    int mDecrypted = decryption(p, q, d, c);

    printf("Original message: %d\n", m);
    printf("Encrypted message: %d\n", c);
    printf("Decrypted message: %d\n", mDecrypted);

    printf("now choosing random value r for cca2 attack\n");
    int r = 44;
    int cDash = (c * ((r ^ e) % N)) % N;
    printf("cDash: %d\n", cDash);

    int mDash = decryption(p, q, d, cDash);
    printf("mDash: %d\n", mDash);

    int orignalMessage = (mDash * multiplicativeInverse(r, N)) % N;
    printf("Original message: %d\n", orignalMessage);

    return 0;
}