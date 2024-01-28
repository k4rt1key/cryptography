#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


// function to print an array
// input --> Array
void printArray(int arr[], int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// input --> int number ( example: 2 )
// output --> Array of binary number ( example: [1,0] )
int *decimalToBinary(int number)
{

    int* ans = (int*)malloc(sizeof(int)* 2);

    // We have only 0,1,2,3 as input
    // so returning binary number's array manually

    if (number == 0)
    {
        ans[0] = 0;
        ans[1] = 0;
        return ans;
    }

    if (number == 1)
    {
        ans[0] = 0;
        ans[1] = 1;
        return ans;
    }

    if (number == 2)
    {
        ans[0] = 1;
        ans[1] = 0;
        return ans;
    }

    if (number == 3)
    {
        ans[0] = 1;
        ans[1] = 1;
        return ans;
    }

    else
    {
    }
}

// input --> Array of 8 bits
// output --> Permuted array 8 bits
int *ip(int arr[8])
{

    int* ans = (int*) malloc(sizeof(int)*8);

    ans[0] = arr[1];
    ans[1] = arr[5];
    ans[2] = arr[2];
    ans[3] = arr[0];

    ans[4] = arr[3];
    ans[5] = arr[7];
    ans[6] = arr[4];
    ans[7] = arr[6];

    return ans;
}

// input --> Array of 8 bits
// output --> Permuted array of 8 bits
int *ipInverse(int arr[8])
{

    int* ans = (int*) malloc(sizeof(int)*8);

    ans[0] = arr[3];
    ans[1] = arr[0];
    ans[2] = arr[2];
    ans[3] = arr[4];
    ans[4] = arr[6];
    ans[5] = arr[1];
    ans[6] = arr[7];
    ans[7] = arr[5];

    return ans;
}

// input --> Array of 4 bits
// output --> Expanded Array of 8 bits
int *ep(int arr[4], int ans[8])
{

    ans[0] = arr[3];
    ans[1] = arr[0];
    ans[2] = arr[1];
    ans[3] = arr[2];

    ans[4] = arr[1];
    ans[5] = arr[2];
    ans[6] = arr[3];
    ans[7] = arr[0];

    return ans;
}

// output --> S-box Matrix
int **s0Box()
{
    int **twoDArray = (int **)malloc(sizeof(int *) * 4);

    for (int i = 0; i < 4; i++)
    {
        twoDArray[i] = (int *)malloc(sizeof(int) * 4);
    }

    twoDArray[0][0] = 1;
    twoDArray[0][1] = 0;
    twoDArray[0][2] = 3;
    twoDArray[0][3] = 2;
    twoDArray[1][0] = 3;
    twoDArray[1][1] = 2;
    twoDArray[1][2] = 1;
    twoDArray[1][3] = 0;
    twoDArray[2][0] = 0;
    twoDArray[2][1] = 2;
    twoDArray[2][2] = 1;
    twoDArray[2][3] = 3;
    twoDArray[3][0] = 3;
    twoDArray[3][1] = 1;
    twoDArray[3][2] = 3;
    twoDArray[3][3] = 2;

    return twoDArray;
}

// output --> S-box Matrix
int **s1Box()
{
    int **twoDArray = (int **)malloc(sizeof(int *) * 4);

    for (int i = 0; i < 4; i++)
    {
        twoDArray[i] = (int *)malloc(sizeof(int) * 4);
    }

    twoDArray[0][0] = 0;
    twoDArray[0][1] = 1;
    twoDArray[0][2] = 2;
    twoDArray[0][3] = 3;
    twoDArray[1][0] = 2;
    twoDArray[1][1] = 0;
    twoDArray[1][2] = 1;
    twoDArray[1][3] = 3;
    twoDArray[2][0] = 3;
    twoDArray[2][1] = 0;
    twoDArray[2][2] = 1;
    twoDArray[2][3] = 0;
    twoDArray[3][0] = 2;
    twoDArray[3][1] = 1;
    twoDArray[3][2] = 0;
    twoDArray[3][3] = 3;

    return twoDArray;
}

// input --> Array of 4 bits
// output --> Permuted Array of 4 bits
int *p4(int arr[4])
{

    int* ans = (int*)malloc(sizeof(int)*4);

    ans[0] = arr[1];
    ans[1] = arr[3];
    ans[2] = arr[2];
    ans[3] = arr[0];

    return ans;
}

// input --> Array of 8 bits
// output --> Swapped Array of 8 bits
int *sw(int arr[8])
{
    int* ans = (int*)malloc(sizeof(int)*8);

    ans[0] = arr[4];
    ans[1] = arr[5];
    ans[2] = arr[6];
    ans[3] = arr[7];

    ans[4] = arr[0];
    ans[5] = arr[1];
    ans[6] = arr[2];
    ans[7] = arr[3];

    return ans;
}

// input --> Array of 8 bits, Array of 8 bits ( key )
// output --> Array of 8 bits
int *fk(int arr[8], int key[8])
{

    // dividing array into 2 parts
    int leftPart[4];
    int rightPart[4];

    for (int i = 0; i < 4; i++)
    {
        leftPart[i] = arr[i];
        rightPart[i] = arr[i + 4];
    }

    // right part --> expansion permutation
    int epAns[8];
    ep(rightPart, epAns); // 8 bits

    // now xor epAns with key
    int xorAns[8];

    for (int i = 0; i < 8; i++)
    {
        xorAns[i] = epAns[i] ^ key[i];
    }


    // dividing array into 2 parts
    int leftXorAns[4];
    int rightXorAns[4];

    for ( int i = 0; i < 4; i++){
        leftXorAns[i] = xorAns[i];
        rightXorAns[i] = xorAns[i+4];
    }

    // sending both parts to s-box
    int **leftSbox = s0Box();
    int **rightSbox = s1Box();

    // Finding row & col value in left s-box
    int rowValueforLeftSBox = 2 * leftXorAns[0] + 1 * leftXorAns[3];
    int colValueforLeftSBox = 2 * leftXorAns[1] + 1 * leftXorAns[2];

    // value in s-box according to row & col value
    int leftSboxAns = leftSbox[rowValueforLeftSBox][colValueforLeftSBox];
    int *leftSboxAnsInBinary = decimalToBinary(leftSboxAns);

    // Finding row & col value in right s-box
    int rowValueforRightSBox = 2 * rightXorAns[0] + 1 * rightXorAns[3];
    int colValueforRightSBox = 2 * rightXorAns[1] + 1 * rightXorAns[2];

    // value in s-box according to row & col value
    int rightSboxAns = rightSbox[rowValueforRightSBox][colValueforRightSBox];
    int *rightSboxAnsInBinary = decimalToBinary(rightSboxAns);

    // joining both answer --> fourBitArray[4]
    int fourBitArray[4];
    for (int i = 0; i < 2; i++)
    {
        fourBitArray[i] = leftSboxAnsInBinary[i];
        fourBitArray[i + 2] = rightSboxAnsInBinary[i];
    }

    // sending fourBitArray into p4 box
    int *p4Ans = p4(fourBitArray);

    // xoring --> leftpart ^ p4Ans
    int xorAns2[4];
    for (int i = 0; i < 4; i++)
    {
        xorAns2[i] = p4Ans[i] ^ leftPart[i];
    }

    // merging xorAns2 with rightPart
    int* finalArray = (int*)malloc(sizeof(int)*8);
    for (int i = 0; i < 4; i++)
    {
        finalArray[i] = xorAns2[i];
        finalArray[i + 4] = rightPart[i];
    }

    return finalArray;

}

void encryption(char filename[20])
{

    int plaintext[8];
    FILE* fp;
    fp = fopen(filename, "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &plaintext[i]);
    }


    printf("plaintext: ");
    printArray(plaintext, 8);

    printf("\n");

    printf("Inputed plaintext: ");
    printArray(plaintext, 8);

    // ip of input
    int *ipAns = ip(plaintext);

    printf("Result of initial permutation: ");
    printArray(ipAns, 8);

    // reading value of key1 from key1.txt
    int key1[8];

    fp = fopen("key1.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &key1[i]);
    }
    fclose(fp);

    printf("Value of key1: ");
    printArray(key1, 8);

    // inside fk ( 1st time )
    int *fkAns = fk(ipAns, key1);

    printf("after undergoing into function fk: ");
    printArray(fkAns, 8);

    // swapping
    int *swAns = sw(fkAns);

    printf("after undergoing into swapping function: ");
    printArray(swAns, 8);

    // reading value of key2 from key2.txt
    int *key2 = (int *)malloc(sizeof(int) * 8);
    fp = fopen("key2.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &key2[i]);
    }
    fclose(fp);

    printf("Value of key2: ");
    printArray(key2, 8);

    // inside fk ( 2nd time )
    int *fkAns2 = fk(swAns, key2);

    printf("after undergoing into function fk second time: ");
    printArray(fkAns2, 8);

    // ip inverse
    int *ipInverseAns = ipInverse(fkAns2);

    // ipInverseAns is our CIPHERTEXT
    printf("Result of inverse initial permutation ( CIPHERTEXT ): ");
    printArray(ipInverseAns, 8);

    // wrtiting to ciphertext.txt

    fp = fopen("ciphertext.txt", "w");
    for (int i = 0; i < 8; i++)
    {
        fprintf(fp, "%d", ipInverseAns[i]);
    }

    fclose(fp);
}

void decryption(char filename[20])
{

    int ciphertext[8];
    // reading value of ciphertext frok ciphertext.txt
    FILE* fp;
    fp = fopen(filename, "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &ciphertext[i]);
    }

    printf("\n");
    printf("Ciphertext: ");
    printArray(ciphertext, 8);

    // ip of input
    int *ipAns = ip(ciphertext);

    printf("Result of initial permutation: ");
    printArray(ipAns, 8);

    // reading value of key2 from key2.txt
    int key2[8];
 
    fp = fopen("key2.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &key2[i]);
    }
    fclose(fp);

    printf("Value of key2: ");
    printArray(key2, 8);

    // inside fk ( 1st time )
    int *fkAns = fk(ipAns, key2);

    printf("after undergoing into function fk: ");
    printArray(fkAns, 8);

    // swapping
    int *swAns = sw(fkAns);

    printf("after undergoing into swapping function: ");
    printArray(swAns, 8);

    // reading value of key1 from key1.txt
    int *key1 = (int *)malloc(sizeof(int) * 8);
    fp = fopen("key1.txt", "r");
    for (int i = 0; i < 8; i++)
    {
        fscanf(fp, "%1d", &key1[i]);
    }
    fclose(fp);

    printf("Value of key1: ");
    printArray(key1, 8);

    // inside fk ( 2nd time )
    int *fkAns2 = fk(swAns, key1);

    printf("after undergoing into function fk second time: ");
    printArray(fkAns2, 8);

    // ip inverse
    int *ipInverseAns = ipInverse(fkAns2);

    // ipInverseAns is our CIPHERTEXT
    printf("Result of inverse initial permutation ( PLAINTEXT ): ");
    printArray(ipInverseAns, 8);

    // wrtiting to ciphertext.txt

    fp = fopen("plaintext.txt", "w");
    for (int i = 0; i < 8; i++)
    {
        fprintf(fp, "%d", ipInverseAns[i]);
    }

    fclose(fp);
}

int main(){

    encryption("plaintext.txt");
    decryption("ciphertext.txt");

    return 0;
}