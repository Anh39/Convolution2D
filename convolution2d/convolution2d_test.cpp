#include <stdio.h>
#include <stdlib.h>
#include "convolution2d.h"


void readI(NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH], SNUMBER width, SNUMBER height, const char *fileName) {
    NUMBER temp;
    FILE *file = fopen(fileName, "r");
    for (SNUMBER i=0;i<height*width;i++) {
        fscanf(file, "%d,", &temp);
        I[i] = temp;
    }
    fclose(file);
}

void printK(NUMBER* K) {
	printf("**************K***********\n");
    for (SNUMBER i=0;i<K_HEIGHT;i++) {
        for (SNUMBER j=0;j<K_WIDTH;j++) {
            printf("%d ", K[i*K_WIDTH+j]);
        }
        printf("\n");
    }
}
void readK(NUMBER* K, const char *fileName) {
    NUMBER temp;
    FILE *file = fopen(fileName, "r");
    for (SNUMBER i=0;i<K_WIDTH*K_HEIGHT;i++) {
    	fscanf(file, "%d,", &temp);
    	K[i] = temp;
    }
    fclose(file);

}
void readJ(NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH], SNUMBER width, SNUMBER height, const char *fileName) {
    NUMBER temp;
    FILE *file = fopen(fileName, "r");
    for (SNUMBER i=0;i<height*width;i++) {
        fscanf(file, "%d,", &temp);
        J[i] = temp;
    }
    fclose(file);
}
void printI(NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH], SNUMBER width, SNUMBER height) {
	printf("**************I***********\n");
    for (SNUMBER i=0;i<height;i++) {
        for (SNUMBER j=0;j<width;j++) {
            printf("%d ", I[i*width+j]);
        }
        printf("\n");
    }
}

void printJ(NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH], SNUMBER width, SNUMBER height) {
	printf("**************J***********\n");
    for (SNUMBER i=0;i<height;i++) {
        for (SNUMBER j=0;j<width;j++) {
            printf("%d ", J[i*width+j]);
        }
        printf("\n");
    }
}
int main() {
	printf("---------------------\n");
	printf("--------START--------\n");
	printf("---------------------\n");
	SNUMBER width = 5;
	SNUMBER height = 10;
    const char* fileNameI = "input.txt";
    const char* fileNameK = "kernel.txt";
    const char* fileNameJ = "output.txt";
    NUMBER imgSrc[MAX_I_HEIGHT*MAX_I_WIDTH];
    NUMBER kernelSrc[K_HEIGHT*K_WIDTH];
    NUMBER imgDst[MAX_J_HEIGHT*MAX_J_WIDTH];
    NUMBER imgRef[MAX_J_HEIGHT*MAX_J_WIDTH];
    SNUMBER out_size = (height-K_HEIGHT+1) * (width-K_WIDTH+1);
    printf("Out size: %d \n", out_size);
    for (int i=0; i< MAX_J_WIDTH*MAX_J_HEIGHT;i++) {
        imgDst[i] = 0;
        imgRef[i] = 0;
    }
    readK(kernelSrc, fileNameK);
    readI(imgSrc, width, height, fileNameI);
    readJ(imgRef,width-K_WIDTH+1, height-K_HEIGHT+1, fileNameJ);
	printf("---------------------\n");
	printf("-----FINISH READ-----\n");
	printf("---------------------\n");

	printI(imgSrc, width, height);
	printK(kernelSrc);

    convolution2d(kernelSrc, width, height, imgSrc, imgDst);
    int correct = 1;
    for (SNUMBER i=0;i<out_size;i++) {
        if (imgDst[i] != imgRef[i]) {
            correct = 0;
            break;
        }
    }
        if (correct == 1) {
        printf("*** *** *** *** ***\n");
        printf("Result is correct\n");
        printf("*** *** *** *** ***\n");
    }
    else {
        printf("*** *** *** *** ***\n");
        printf("Result is wrong!\n");
        printf("*** *** *** *** ***\n");
        printf("Target\n");
//    	for (SNUMBER i=0;i<height-K_HEIGHT+1;i++) {
//            for (SNUMBER j=0;j<width-K_WIDTH+1;j++) {
//                printf("%d ", imgRef[i*width+j]);
//            }
//            printf("\n");
//        }
        for (SNUMBER i=0;i<out_size;i++) {
        	printf("%d ", imgRef[i]);
        }
        printf("******************\n");
        printf("Result\n");
//    	for (SNUMBER i=0;i<height-K_HEIGHT+1;i++) {
//            for (SNUMBER j=0;j<width-K_WIDTH+1;j++) {
//                printf("%d ", imgDst[i*width+j]);
//            }
//            printf("\n");
//        }
        for (SNUMBER i=0;i<out_size;i++) {
        	printf("%d ", imgDst[i]);
        }
        printf("******************\n");
    }
    return 0;
}


