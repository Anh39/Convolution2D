//#include <stdio.h>
//#include <stdlib.h>
//#include "convolution2d.h"
//
//
//void convolution2dSoftware(
//        const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
//        SNUMBER width,
//        SNUMBER height,
//        const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
//        NUMBER dst[MAX_J_WIDTH * MAX_J_HEIGHT])
//{
//    printf("\n");
////  printf("Output size : %d %d %d\n",MAX_J_WIDTH, MAX_J_HEIGHT, MAX_J_WIDTH * MAX_J_HEIGHT);
//    for (SNUMBER i=0; i<height-K_HEIGHT+1; i++) {
//        for (SNUMBER j=0; j<width-K_WIDTH+1; j++) {
//            NUMBER sum=0;
//            for (SNUMBER ic=0; ic<K_HEIGHT;ic++) {
//                for (SNUMBER jc=0; jc<K_WIDTH;jc++) {
//                    sum+=src[(i+ic)*width+(j+jc)] * kernalSrc[ic*K_WIDTH+jc];
//                }
//            }
//            SNUMBER index = i*(width-K_WIDTH+1)+j;
//            dst[index] = sum;
//        }
//
//    }
//    printf("\n");
//}
//int main() {
//    SNUMBER width = 5;
//    SNUMBER height = 10;
//    NUMBER imgSrc[MAX_I_WIDTH * MAX_I_HEIGHT] = {
//    		3,7,9,7,4,
//    		8,0,9,9,0,
//    		4,9,6,3,4,
//    		9,2,4,3,4,
//    		0,7,8,9,10,
//    		0,2,0,8,4,
//    		8,3,2,1,0,
//    		5,4,7,9,6,
//    		9,8,4,4,3,
//    		0,4,9,9,10
//    };
//    NUMBER imgDst[MAX_J_WIDTH * MAX_J_HEIGHT];
//    NUMBER imgRef[MAX_J_WIDTH * MAX_J_HEIGHT];
//    SNUMBER out_size = (height-K_HEIGHT+1) * (width-K_WIDTH+1);
//    printf("Out size: %d \n", out_size);
//    for (int i=0; i< MAX_J_WIDTH*MAX_J_HEIGHT;i++) {
//        imgDst[i] = 0;
//        imgRef[i] = 0;
//    }
//    NUMBER kernelSrc[K_HEIGHT * K_WIDTH] = {
//    		6,5,
//    		5,9,
//    		5,6
//    };
//    convolution2d(kernelSrc, width, height, imgSrc, imgDst);
//    convolution2dSoftware(kernelSrc, width, height, imgSrc, imgRef);
//    int correct = 1;
//    for (SNUMBER i=0;i<out_size;i++) {
//        if (imgDst[i] != imgRef[i]) {
//            correct = 0;
//            break;
//        }
//    }
//        if (correct == 1) {
//        printf("*** *** *** *** ***\n");
//        printf("Result is correct\n");
//        printf("*** *** *** *** ***\n");
//    }
//    else {
//        printf("*** *** *** *** ***\n");
//        printf("Result is wrong!\n");
//        printf("*** *** *** *** ***\n");
//        printf("Target\n");
////    	for (SNUMBER i=0;i<height-K_HEIGHT+1;i++) {
////            for (SNUMBER j=0;j<width-K_WIDTH+1;j++) {
////                printf("%d ", imgRef[i*width+j]);
////            }
////            printf("\n");
////        }
//        for (SNUMBER i=0;i<out_size;i++) {
//        	printf("%d ", imgRef[i]);
//        }
//        printf("******************\n");
//        printf("Result\n");
////    	for (SNUMBER i=0;i<height-K_HEIGHT+1;i++) {
////            for (SNUMBER j=0;j<width-K_WIDTH+1;j++) {
////                printf("%d ", imgDst[i*width+j]);
////            }
////            printf("\n");
////        }
//        for (SNUMBER i=0;i<out_size;i++) {
//        	printf("%d ", imgDst[i]);
//        }
//        printf("******************\n");
//    }
//    return 0;
//}
