#include "convolution2d.h"

void convolution2d(NUMBER I[I_HEIGH][I_WIDTH], NUMBER K[K_HEIGH][K_WIDTH], NUMBER J[J_HEIGH][J_WIDTH]) {
I_LOOP_ROW:
	for (SIZE_NUMBER i=0; i<J_HEIGH;i++) {
I_LOOP_COL:
        for (SIZE_NUMBER j=0; j<J_WIDTH;j++) {
            NUMBER sum=0;
K_LOOP_ROW:
            for (SIZE_NUMBER ik=0; ik < K_HEIGH; ik++) {
K_LOOP_COL:
                for(SIZE_NUMBER jk=0; jk < K_WIDTH; jk++) {
                    sum += I[i+ik][j+jk] * K[ik][jk];
                }
            }
            J[i][j] = sum;
        }
    }
}
