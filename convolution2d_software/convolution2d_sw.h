#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#define I_WIDTH 5
#define I_HEIGH 10
#define K_WIDTH 2
#define K_HEIGH 3
#define J_WIDTH I_WIDTH-K_WIDTH+1
#define J_HEIGH I_HEIGH-K_HEIGH+1
#define NUMBER long
#define SIZE_NUMBER int

void convolution2d(NUMBER I[I_HEIGH][I_WIDTH], NUMBER K[K_HEIGH][K_WIDTH], NUMBER J[J_HEIGH][J_WIDTH]);
#endif