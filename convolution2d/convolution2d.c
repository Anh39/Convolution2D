#include "convolution2d.h"

void convolution2d(int I[I_HEIGH][I_WIDTH], int K[K_HEIGH][K_WIDTH], int J[J_HEIGH][J_WIDTH]) {
I_LOOP_ROW:
	for (int i=0; i<J_HEIGH;i++) {
I_LOOP_COL:
        for (int j=0; j<J_WIDTH;j++) {
            int sum=0;
K_LOOP_ROW:
            for (int ik=0; ik < K_HEIGH; ik++) {
K_LOOP_COL:
                for(int jk=0; jk < K_WIDTH; jk++) {
                    sum += I[i+ik][j+jk] * K[ik][jk];
                }
            }
            J[i][j] = sum;
        }
    }
}
