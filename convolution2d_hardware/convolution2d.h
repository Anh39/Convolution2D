#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#define MAX_I_WIDTH 5
#define MAX_I_HEIGHT 10
#define K_WIDTH 2
#define K_HEIGHT 3
#define MAX_J_WIDTH MAX_I_WIDTH-K_WIDTH+1
#define MAX_J_HEIGHT MAX_I_HEIGHT-K_HEIGHT+1
#define NUM_BUFFER 4
typedef long NUMBER;
typedef unsigned int SNUMBER;

// void convolution2d(NUMBER I[MAX_I_HEIGHT][MAX_I_WIDTH], NUMBER K[K_HEIGHT][K_WIDTH], NUMBER J[MAX_J_HEIGHT][MAX_J_WIDTH]);
#endif