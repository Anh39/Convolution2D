#include "convolution2d.h"
//#include <ap_cint.h>

typedef struct {
    NUMBER pix[K_HEIGHT][K_WIDTH];
} WINDOW;
typedef struct {
	WINDOW data[NUM_BUFFER];
	int head;
	int tail;
	short empty;
	short full;
} WINDOW_FIFO;
WINDOW readFIFO(WINDOW_FIFO *ff) {
	while (ff->empty == 0) {

	}
	ff->tail = (ff->tail+1) % NUM_BUFFER;
	if (ff->tail == ff->head) {
		ff->empty = 1;
	}
	ff->full = 0;
	return ff->data[ff->tail];
}
void writeFIFO(WINDOW_FIFO *ff, WINDOW window) {
	while (ff->full == 1) {

	}
	ff->head = (ff->head+1) % NUM_BUFFER;
	if (ff->head == ff->tail) {
		ff->full = 1;
	}
	ff->empty = 0;
}

void readFromMemory(
        SNUMBER width,
        SNUMBER height,
        const NUMBER *kernelSrc,
        NUMBER kernel[K_HEIGHT][K_WIDTH],
        const NUMBER *src,
        NUMBER image[MAX_I_HEIGHT][MAX_I_WIDTH])
{
    // Need line buffer
    for(SNUMBER ik=0; ik<K_HEIGHT; ik++) {
        for(SNUMBER jk=0; jk<K_WIDTH; jk++) {
            kernel[ik][jk] = kernelSrc[ik*K_WIDTH + jk];
        }
    }

    for (SNUMBER i=0; i<height-K_WIDTH+1; i++) {
        for (SNUMBER j=0; j<width-K_HEIGHT+1; j++) {
            image[i][j] = src[i*width + j];
        }
    }
}
void writeToMemmory(
        SNUMBER width,
        SNUMBER height,
        const NUMBER out_image[MAX_J_HEIGHT][MAX_J_WIDTH],
        NUMBER *dst)
{
    for (SNUMBER i=0; i<height; i++) {
        for (SNUMBER j=0; j<width; j++) {
            dst[i*width + j] = out_image[i][j];
        }
    }
}
void readWindow(
        SNUMBER width,
        SNUMBER height,
        const NUMBER image[MAX_I_HEIGHT][MAX_I_WIDTH],
		WINDOW_FIFO windows)
{
    for (SNUMBER i=0; i<height-K_WIDTH+1; i++) {
        for (SNUMBER j=0; j<width-K_HEIGHT+1; j++) {
            WINDOW window;
            for (SNUMBER iw=0; iw<K_HEIGHT; iw++) {
                for (SNUMBER jw=0; jw<K_WIDTH; jw++) {
                    window.pix[iw][jw] = image[i+iw][j+jw];
                }
            }
            writeFIFO(&windows, window);
        }
    }
}

void convolution2d(
        SNUMBER width,
        SNUMBER height,
        const NUMBER kernel[K_HEIGHT][K_WIDTH],
        WINDOW_FIFO windows,
        NUMBER out_image[MAX_J_HEIGHT][MAX_J_WIDTH])
{
    for (SNUMBER i=0; i<height-K_HEIGHT+1; i++) {
        for (SNUMBER j=0; j<width-K_WIDTH+1; j++) {
            WINDOW window = readFIFO(&windows);
            NUMBER sum = 0;
            for (SNUMBER ic=0; ic<K_HEIGHT; ic++) {
                for (SNUMBER jc; jc<K_WIDTH; jc++) {
                    sum += window.pix[ic][jc] * kernel[ic][jc];
                }
            }
            out_image[i][j] = sum;
        }
    }
}

void convolution2dTop(
        const NUMBER *kernalSrc,
        float factor,
        short bias,
        SNUMBER width,
        SNUMBER height,
        const NUMBER *src,
        NUMBER *dst)
{
    NUMBER kernel[K_HEIGHT][K_WIDTH];
    NUMBER image[MAX_I_HEIGHT][MAX_I_WIDTH];
    WINDOW_FIFO windows; // window buffer (implement as FIFO)
    NUMBER out_image[MAX_J_HEIGHT][MAX_J_WIDTH];

    // Read image, kernel
    // TO: kernel, image
    readFromMemory(width, height, kernalSrc, kernel, src, image);

    // Read image window
    // Use line buffer to speed up
    // TO: windowFIFO
    readWindow(width, height, image, windows);

    // Perform convolution
    // FROM: kernel, windowFIFO
    // TO: outputStream
    convolution2d(width, height, kernel, windows, out_image);

    // Write output
    // FROM: outputStream
    // TO: dst
    writeToMemmory(width, height, out_image, dst);
}
