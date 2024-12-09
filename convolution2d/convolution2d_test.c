#include <stdio.h>
#include <stdlib.h>
#include "convolution2d.h"

void readI(int I[I_HEIGH][I_WIDTH], const char *fileName) {
    int temp;
    FILE *file = fopen(fileName, "r");
    for (int i=0;i<I_HEIGH;i++) {
        for (int j=0;j<I_WIDTH;j++) {
            fscanf(file, "%d,", &temp);
            I[i][j] = temp;
        }
    }
    fclose(file);
}
void readK(int K[K_HEIGH][K_WIDTH], const char *fileName) {
    int temp;
    FILE *file = fopen(fileName, "r");
    for (int i=0;i<K_HEIGH;i++) {
        for (int j=0;j<K_WIDTH;j++) {
            fscanf(file, "%d,", &temp);
            K[i][j] = temp;
        }
    }
    fclose(file);
}
void readJ(int J[J_HEIGH][J_WIDTH], const char *fileName) {
    int temp;
    FILE *file = fopen(fileName, "r");
    for (int i=0;i<J_HEIGH;i++) {
        for (int j=0;j<J_WIDTH;j++) {
            fscanf(file, "%d,", &temp);
            J[i][j] = temp;
        }
    }
    fclose(file);
}
void printI(int I[I_HEIGH][I_WIDTH]) {
    printf("Input\n");
    for (int i=0;i<I_HEIGH;i++) {
        for (int j=0;j<I_WIDTH;j++) {
            printf("%d ", I[i][j]);
        }
        printf("\n");
    }
}
void printK(int K[K_HEIGH][K_WIDTH]) {
    printf("Kernel\n");
    for (int i=0;i<K_HEIGH;i++) {
        for (int j=0;j<K_WIDTH;j++) {
            printf("%d ", K[i][j]);
        }
        printf("\n");
    }
}
void printJ(int matrix[J_HEIGH][J_WIDTH]) {
    for(int i=0;i<J_HEIGH;i++) {
        for(int j=0;j<J_WIDTH;j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main() {
    const char* fileNameI = "input.txt";
    const char* fileNameK = "kernel.txt";
    const char* fileNameJ = "output.txt";
    int I[I_HEIGH][I_WIDTH];
    int K[K_HEIGH][K_WIDTH];
    int J[J_HEIGH][J_WIDTH];
    int goldJ[J_HEIGH][J_WIDTH];
    readK(K, fileNameK);
    readI(I, fileNameI);
    readJ(goldJ, fileNameJ);
    // printI(I);
    // printK(K);
    convolution2d(I, K, J);
    // printJ(J);
    // printJ(goldJ);
    int isCorrect = 0;
    for (int i=0;i<J_HEIGH;i++) {
        for (int j=0;j<J_WIDTH;j++) {
            if (J[i][j] != goldJ[i][j]) {
                isCorrect = 1;
                break;
            }
        }
        if (isCorrect == 1) {
            break;
        }
    }
    if (isCorrect == 0) {
        printf("*** *** *** *** ***\n");
        printf("Result is correct\n");
        printf("*** *** *** *** ***\n");
    }
    else {
        printf("*** *** *** *** ***\n");
        printf("Result is wrong!\n");
        printf("*** *** *** *** ***\n");
        printf("Target\n");
        printJ(goldJ);
        printf("Result\n");
        printJ(J);
    }
    return 0;
}
// void convolution2d(int I[I_HEIGH][I_WIDTH], int K[K_HEIGH][K_WIDTH], int J[J_HEIGH][J_WIDTH]) {
// I_LOOP_ROW:
// 	for (int i=0; i<J_HEIGH;i++) {
// I_LOOP_COL:
//         for (int j=0; j<J_WIDTH;j++) {
//             int sum=0;
// K_LOOP_ROW:
//             for (int ik=0; ik < K_HEIGH; ik++) {
// K_LOOP_COL:
//                 for(int jk=0; jk < K_WIDTH; jk++) {
//                     sum += I[i+ik][j+jk] * K[ik][jk];
//                 }
//             }
//             J[i][j] = sum;
//         }
//     }
// }
