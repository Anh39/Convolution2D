#include <stdio.h>
#include <stdlib.h>
#include "convolution2d.h"


 void convolution2dSoftware(
        const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
        SNUMBER width,
        SNUMBER height,
        const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
        NUMBER dst[MAX_J_HEIGHT*MAX_J_WIDTH])
{
    for (SNUMBER i=0; i<height-K_HEIGHT+1; i++) {
        for (SNUMBER j=0; j<width-K_WIDTH+1; j++) {
            NUMBER sum=0;
            for (SNUMBER ic=0; ic<K_HEIGHT;ic++) {
                for (SNUMBER jc=0; jc<K_WIDTH;jc++) {
                    sum+=src[(i+ic)*width+(j+jc)] * kernalSrc[ic*K_WIDTH+jc];
                }
            }
            dst[i*width+j] = sum;
        }
    }
}
int main() {
    SNUMBER width = 10;
    SNUMBER height = 10;
    NUMBER imgSrc[MAX_I_WIDTH * MAX_I_HEIGHT];
    NUMBER imgDst[MAX_J_WIDTH * MAX_J_HEIGHT];
    NUMBER imgRef[MAX_J_WIDTH * MAX_J_HEIGHT];
    SNUMBER out_size = (height-K_HEIGHT+1) * (width-K_WIDTH+1);
    printf("Out size: %d \n", out_size);
    for (int i=0; i< MAX_I_HEIGHT*MAX_I_WIDTH;i++) {
        imgSrc[i] = 1;
    }
    for (int i=0; i< MAX_J_WIDTH*MAX_J_HEIGHT;i++) {
        imgDst[i] = 0;
        imgRef[i] = 0;
    }
    NUMBER kernelSrc[K_HEIGHT * K_WIDTH];
    for (int i=0; i< K_HEIGHT*K_WIDTH;i++) {
        kernelSrc[i] = 1;
    }
    convolution2d(kernelSrc, width, height, imgSrc, imgDst);

    convolution2dSoftware(
        kernelSrc,
        width,
        height,
        imgSrc,
        imgRef
    );
    int correct = 1;
//    out_size = (height-K_HEIGHT+1) * (width-K_WIDTH+1);
    printf("Out size: %d \n", out_size);
    for (SNUMBER i=0;i<MAX_J_WIDTH*MAX_J_HEIGHT;i++) {
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
