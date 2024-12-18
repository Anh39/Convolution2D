#include "convolution2d.h"
#include "hls_stream.h"
#include <stdio.h>


typedef struct {
    NUMBER data[K_HEIGHT][K_WIDTH];
} WINDOW;

void readFromMemory(
        SNUMBER width,
        SNUMBER height,
        const NUMBER *kernelSrc,
        NUMBER kernel[K_HEIGHT][K_WIDTH],
        const NUMBER *src,
        hls::stream<NUMBER> &image)
{
	printf("Start read memory\n");
READ_KERNEL_OUTER:
    for(SNUMBER ik=0; ik<K_HEIGHT; ik++) {
READ_KERNEL_INNER:
        for(SNUMBER jk=0; jk<K_WIDTH; jk++) {
        	NUMBER value = kernelSrc[ik*K_WIDTH + jk];
        	kernel[ik][jk] = value;
        }
    }
    const SNUMBER max_iterations = MAX_I_HEIGHT * MAX_I_WIDTH;
    SNUMBER image_size = height * width;
    SNUMBER baseIndex = -width;
READ_IMAGE_LOOP:
	for (SNUMBER i=0;i<image_size;i++) {
#pragma HLS LOOP_TRIPCOUNT max=max_iterations
		NUMBER value = src[i];
		image.write(value);
	}
}
void writeToMemmory(
        SNUMBER width,
        SNUMBER height,
        hls::stream<NUMBER> &out_image,
        NUMBER dst[MAX_J_HEIGHT*MAX_J_WIDTH])
{
	SNUMBER size=(height-K_HEIGHT+1) * (width-K_WIDTH+1);
WRITE_IMAGE_OUTPUT_LOOP:
	for (SNUMBER i=0; i<MAX_J_HEIGHT*MAX_J_WIDTH;i++) {
		if (i<size) {
			NUMBER value = out_image.read();
			dst[i] = value;
		} else {
			dst[i] = 0;
		}
	}
}
void readWindow(
        SNUMBER width,
        SNUMBER height,
        hls::stream<NUMBER> &image,
		hls::stream<WINDOW> &windows)
{
	SNUMBER num_iterations = width * height;
	const int max_iteration = MAX_J_WIDTH * MAX_J_HEIGHT;
	SNUMBER bufferSize = (K_HEIGHT-1) * width;
	SNUMBER bufferMaxSize = (K_HEIGHT-1) * MAX_I_WIDTH;
	NUMBER LineBuffer[K_HEIGHT-1][MAX_I_WIDTH];
	WINDOW window;
READ_WINDOW_LOOP:
	for (SNUMBER it=0;it<num_iterations;it++) {
#pragma HLS LOOP_TRIPCOUNT max=max_iteration
		NUMBER new_pixel = image.read();
		SNUMBER x = it % width;
		SNUMBER y = (it / width) % (K_HEIGHT-1);
WINDOW_KERNEL_OUTER_LOOP:
		for (SNUMBER i=0;i<K_HEIGHT;i++) {
WINDOW_KERNEL_INNER_LOOP:
			for (SNUMBER j=0;j<K_WIDTH-1;j++) {
				window.data[i][j] = window.data[i][j+1];
			}
			if (i == K_HEIGHT - 1) {
				window.data[K_HEIGHT-1][K_WIDTH-1] = new_pixel;
			} else {
				window.data[i][K_WIDTH-1] = LineBuffer[(i+y)%(K_HEIGHT-1)][x];
			}
		}
		LineBuffer[y][x] = new_pixel;
		if (it >= bufferSize + K_WIDTH - 1 && x>=K_WIDTH-1) {
			windows.write(window);
		}
	}
}

void processConvolution2d(
        SNUMBER width,
        SNUMBER height,
        NUMBER kernel[K_HEIGHT][K_WIDTH],
		hls::stream<WINDOW> &windows,
        hls::stream<NUMBER> &out_image)
{
	const SNUMBER max_height = MAX_J_HEIGHT;
	const SNUMBER max_width = MAX_J_WIDTH;
CONVOLUTION_OUTER_LOOP:
	for(SNUMBER i=0;i<height-K_HEIGHT+1;i++) {
#pragma HLS LOOP_TRIPCOUNT max=max_height
CONVOLUTION_INNER_LOOP:
		for(SNUMBER j=0;j<width-K_WIDTH+1;j++) {
#pragma HLS LOOP_TRIPCOUNT max=max_width
			WINDOW w = windows.read();
			NUMBER sum=0;
CONVOLUTION_KERNEL_OUTER_LOOP:
			for (int ik=0; ik<K_HEIGHT; ik++) {
CONVOLUTION_KERNEL_INNER_LOOP:
				for(int jk=0; jk<K_WIDTH; jk++) {
					sum += w.data[ik][jk]*kernel[ik][jk];
				}
			}
			out_image.write(sum);
		}
	}

}
void convolution2d(
        const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
        SNUMBER width,
        SNUMBER height,
        const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
        NUMBER dst[MAX_J_HEIGHT*MAX_J_WIDTH])
{
    NUMBER kernel[K_HEIGHT][K_WIDTH];
    hls::stream<NUMBER> image;
    hls::stream<WINDOW> windows;
    hls::stream<NUMBER> out_image;
    readFromMemory(width, height, kernalSrc, kernel, src, image);
    readWindow(width, height, image, windows);
    processConvolution2d(width, height, kernel, windows, out_image);
    writeToMemmory(width, height, out_image, dst);
}
