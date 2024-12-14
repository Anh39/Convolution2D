//#include <stdio.h>
//#include <stdlib.h>
//#include "convolution2d.h"
//
//
//
//void readI(NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH], SNUMBER width, SNUMBER height, const char *fileName) {
//    NUMBER temp;
//    FILE *file = fopen(fileName, "r");
//    for (SNUMBER i=0;i<height*width;i++) {
//        fscanf(file, "%d,", &temp);
//        I[i] = temp;
//    }
//    fclose(file);
//}
//
//void printK(NUMBER* K) {
//	printf("**************K***********\n");
//    for (SNUMBER i=0;i<K_HEIGHT;i++) {
//        for (SNUMBER j=0;j<K_WIDTH;j++) {
//            printf("%d ", K[i*K_WIDTH+j]);
//        }
//        printf("\n");
//    }
//}
//void readK(NUMBER* K, const char *fileName) {
//    NUMBER temp;
//    FILE *file = fopen(fileName, "r");
//    for (SNUMBER i=0;i<K_WIDTH*K_HEIGHT;i++) {
//    	fscanf(file, "%d,", &temp);
//    	K[i] = temp;
//    }
//    fclose(file);
//
//}
//void readJ(NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH], SNUMBER width, SNUMBER height, const char *fileName) {
//    NUMBER temp;
//    FILE *file = fopen(fileName, "r");
//    for (SNUMBER i=0;i<height*width;i++) {
//        fscanf(file, "%d,", &temp);
//        J[i] = temp;
//    }
//    fclose(file);
//}
//void printI(NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH], SNUMBER width, SNUMBER height) {
//	printf("**************I***********\n");
//    for (SNUMBER i=0;i<height;i++) {
//        for (SNUMBER j=0;j<width;j++) {
//            printf("%d ", I[i*width+j]);
//        }
//        printf("\n");
//    }
//}
//
//void printJ(NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH], SNUMBER width, SNUMBER height) {
//	printf("**************J***********\n");
//    for (SNUMBER i=0;i<height;i++) {
//        for (SNUMBER j=0;j<width;j++) {
//            printf("%d ", J[i*width+j]);
//        }
//        printf("\n");
//    }
//}
//void convolution2dTest(NUMBER K[K_HEIGHT*K_WIDTH], SNUMBER width, SNUMBER height, NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH], NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH]) {
//	for (SNUMBER i=0; i<height-K_HEIGHT+1;i++) {
//       for (SNUMBER j=0; j<width-K_WIDTH+1;j++) {
//           NUMBER sum=0;
//           for (SNUMBER ik=0; ik < K_HEIGHT; ik++) {
//               for(SNUMBER jk=0; jk < K_WIDTH; jk++) {
//                   sum += I[(i+ik)*MAX_I_WIDTH + (j + jk)] * K[ik*K_WIDTH+jk];
//               }
//           }
//           J[i*MAX_J_WIDTH+j] = sum;
//       }
//   }
//}
//
//int main() {
//	printf("---------------------\n");
//	printf("--------START--------\n");
//	printf("---------------------\n");
//	SNUMBER width = 5;
//	SNUMBER height = 10;
//    const char* fileNameI = "input.txt";
//    const char* fileNameK = "kernel.txt";
//    const char* fileNameJ = "output.	txt";
//    NUMBER I[MAX_I_HEIGHT*MAX_I_WIDTH];
//    NUMBER K[K_HEIGHT*K_WIDTH];
//    NUMBER J[MAX_J_HEIGHT*MAX_J_WIDTH];
//    NUMBER goldJ[MAX_J_HEIGHT*MAX_J_WIDTH];
//    readK(K, fileNameK);
//    readI(I, width, height, fileNameI);
//    readJ(goldJ,width-K_WIDTH+1, height-K_HEIGHT+1, fileNameJ);
//	printf("---------------------\n");
//	printf("-----FINISH READ-----\n");
//	printf("---------------------\n");
//
//	printI(I, width, height);
//	printK(K);
////	printf("********START*TEST*******\n");
////	convolution2dTest(K, width, height, I, goldJ);
////	printf("*********END*TEST*******\n");
//	printf("********START************\n");
//	convolution2d(K, width, height, I, J);
//	printf("********END**************\n");
////	printJ(J, width-K_WIDTH+1, height-K_HEIGHT+1);
////	printJ(goldJ, width-K_WIDTH+1, height-K_HEIGHT+1);
//	int isCorrect = 0;
//    for (SNUMBER i=0;i<MAX_J_HEIGHT;i++) {
//        for (SNUMBER j=0;j<MAX_J_WIDTH;j++) {
//            if (J[i*MAX_J_WIDTH+j] != goldJ[i*MAX_J_WIDTH+j]) {
//                isCorrect = 1;
//                break;
//            }
//        }
//        if (isCorrect == 1) {
//            break;
//        }
//    }
//    if (isCorrect == 0) {
//        printf("*** *** *** *** ***\n");
//        printf("Result is correct\n");
//        printf("*** *** *** *** ***\n");
//    }
//    else {
//        printf("*** *** *** *** ***\n");
//        printf("Result is wrong!\n");
//        printf("*** *** *** *** ***\n");
//        printf("Target\n");
//    	printJ(J, width-K_WIDTH+1, height-K_HEIGHT+1);
//        printf("Result\n");
//    	printJ(goldJ, width-K_WIDTH+1, height-K_HEIGHT+1);
//    }
//    return 0;
//}
//
//
