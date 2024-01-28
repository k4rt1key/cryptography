#include <stdio.h>
#include <stdlib.h>  
#include<time.h>

// input --> array of 10 bit 
// output --> permuted array of 10 bit
int* p10( int key[10] ){
    int* pArr = (int *)malloc(10 * sizeof(int));
    
    pArr[0] = key[2];
    pArr[1] = key[4];
    pArr[2] = key[1];
    pArr[3] = key[6];
    pArr[4] = key[3];
    pArr[5] = key[9];
    pArr[6] = key[0];
    pArr[7] = key[8];
    pArr[8] = key[7];
    pArr[9] = key[5];
    
    return pArr;
}

// input --> array of 10 bit 
// output --> permuted array of 8 bit
int* p8( int key[10] ){
    int* pArr = (int *)malloc(8 * sizeof(int));
    
    pArr[0] = key[5];
    pArr[1] = key[2];
    pArr[2] = key[6];
    pArr[3] = key[3];
    pArr[4] = key[7];
    pArr[5] = key[4];
    pArr[6] = key[9];
    pArr[7] = key[8];
    
    return pArr;
}

// input --> array of 5 bit ( key )
// output --> left shifted array of 5 bit 
int* ls(int key[5]){
    int* newArr = (int *)malloc(5 * sizeof(int));
    
    for(int i = 0; i<5; i++){
        if( i == 4 ) {
            newArr[i] = key[0];
        }
        newArr[i] = key[i+1];
    }
    
    return newArr;
}

// input --> Nothing 
// output --> random 10 bits
int* key_gen() {
   int* key = (int *)malloc(10 * sizeof(int));
   for (int i = 0 ; i < 10; i++){
       key[i] = rand() % 2;
   }
   
   return key;
}

int main() {
       
    srand(time(0));
    
    // random 10 bit of key
    int* randomKey = key_gen();

    // permuted key
    int* permutedKey = p10(randomKey);
    
    // dividing permuted key into 2 parts
    int* leftPermutedKey = (int *)malloc(5 * sizeof(int));
    int* rightPermutedKey = (int *)malloc(5 * sizeof(int));

    for(int i = 0 ; i < 5; i++) {
        leftPermutedKey[i] = permutedKey[i];
        rightPermutedKey[i] = permutedKey[i+5];
    }
    
    // left shifting both key parts 
    int* leftShiftedKey = ls(leftPermutedKey);
    int* leftShiftedKey2 = ls(rightPermutedKey);
    
    // mergin both 5 bit array
    int* mergedKeyAfterLeftShift = (int*) malloc ( sizeof(int) * 10);
    for(int i = 0; i < 5; i++){
        mergedKeyAfterLeftShift[i] = leftShiftedKey[i];
        mergedKeyAfterLeftShift[i+5] = leftShiftedKey2[i];
    }
    
    // getting value of "key1"
    int* key1 = p8(mergedKeyAfterLeftShift);
    
    // for second key ... 
    // apply left shift second time 
    int* secondLeftShiftedKey = ls(leftShiftedKey);
    int* secondLeftShiftedKey2 = ls(leftShiftedKey2);
    
    
    // merge two secondLeftShiftedKey arrays 
    int* mergedKeyAfterSecondLeftShift = (int*) malloc( sizeof(int) * 10);
    for(int i = 0; i < 5; i++){
        mergedKeyAfterSecondLeftShift[i] = secondLeftShiftedKey[i];
        mergedKeyAfterSecondLeftShift[i+5] = secondLeftShiftedKey2[i];
    }
    
    // getting value of "key2"
    int* key2 = p8(mergedKeyAfterSecondLeftShift);
    

    // printing and storing keys in .txt files

    // -------------------------
    for(int i = 0; i < 8; i++){
        printf("%d", key1[i]);
    }
    
    printf("\n");

    for(int i = 0; i < 8; i++){
        printf("%d", key2[i]);
    }

    // -------------------------
    
    FILE *file;
    file = fopen("key1.txt", "w");
    if (file == NULL) {
        printf("Error.\n");
        return 1;
    }
    
    for(int i = 0; i < 8; i++){
        fprintf(file, "%d", key1[i]);
    }
    
    file = fopen("key2.txt", "w");
    if (file == NULL) {
        printf("Error.\n");
        return 1;
    }

    for(int i = 0; i < 8; i++){
        fprintf(file, "%d", key2[i]);
    }
    
    return 0;
}
