#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#define I_WIDTH 5
#define I_HEIGH 10
#define K_WIDTH 2
#define K_HEIGH 3
#define J_WIDTH I_WIDTH-K_WIDTH+1
#define J_HEIGH I_HEIGH-K_HEIGH+1

void convolution2d(int I[I_HEIGH][I_WIDTH], int K[K_HEIGH][K_WIDTH], int J[J_HEIGH][J_WIDTH]);
#endif