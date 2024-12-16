#include "convolution2d.h"
#include "hls_stream.h"
#include <stdio.h>


typedef struct {
    NUMBER pix[K_HEIGHT][K_WIDTH];
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
    const SNUMBER max_height = MAX_I_HEIGHT;
    const SNUMBER max_width = MAX_I_WIDTH;
READ_IMAGE_OUTER:
    for (SNUMBER i=0; i<height; i++) {
#pragma HLS LOOP_TRIPCOUNT max=max_height
READ_IMAGE_INNER:
        for (SNUMBER j=0; j<width; j++) {
#pragma HLS LOOP_TRIPCOUNT max=max_width
            NUMBER value = src[i*width + j];
            image.write(value);
        }
    }
}
void writeToMemmory(
        SNUMBER width,
        SNUMBER height,
        hls::stream<NUMBER> &out_image,
        NUMBER dst[MAX_J_HEIGHT*MAX_J_WIDTH])
{
	printf("Start write memory\n");

	SNUMBER size=(height-K_HEIGHT+1) * (width-K_WIDTH+1);
WRITE_IMAGE_OUTPUT_LOOP:
	for (SNUMBER i=0; i<MAX_J_HEIGHT*MAX_J_WIDTH;i++) {
		if (i<size) {
			NUMBER value = out_image.read();
			printf("%d ", value);
			dst[i] = value;
		} else {
			dst[i] = 0;
		}
	}
	printf("\n");
//    SNUMBER count = (height-K_HEIGHT+1) * (width-K_WIDTH+1);
//    for (SNUMBER i=count;i<MAX_J_WIDTH*MAX_J_HEIGHT;i++) {
//    	dst[i] = 0;
//    }
}
void readWindow(
        SNUMBER width,
        SNUMBER height,
        hls::stream<NUMBER> &image,
		hls::stream<WINDOW> &windows)
{
	printf("Start read window\n");

	SNUMBER num_pixels = width*height;
	SNUMBER num_iterations = width * height;
	const SNUMBER max_iteration = MAX_J_WIDTH * MAX_J_HEIGHT;
	SNUMBER bufferSize = (K_HEIGHT-1) * width + K_WIDTH;
	SNUMBER bufferMaxSize = (K_HEIGHT-1) * MAX_I_WIDTH + K_WIDTH;
	NUMBER LineBuffer[bufferMaxSize];
	SNUMBER ptr = 0;
	WINDOW window;
READ_WINDOW_LOOP:
	for (SNUMBER it=0;it<num_iterations;it++) {
#pragma HLS LOOP_TRIPCOUNT max=max_iteration
		NUMBER new_pixel = image.read();
//		for(SNUMBER z=0;z<bufferSize;z++) {
//			printf("%d ", LineBuffer[z]);
//		}
		ptr = it%bufferSize;
		LineBuffer[ptr] = new_pixel;
WINDOW_KERNEL_OUTER_LOOP:
		for (SNUMBER i=0;i<K_HEIGHT;i++) {
WINDOW_KERNEL_INNER_LOOP:
			for (SNUMBER j=0;j<K_WIDTH-1;j++) {
				window.pix[i][j] = window.pix[i][j+1];
//				SNUMBER index = ((ptr + 1 + (i*width + j)) % bufferSize);
//				window.pix[i][j] = LineBuffer[index];
			}
			SNUMBER index = ((ptr + 1 + (i*width + K_WIDTH-1)) % bufferSize);
			window.pix[i][K_WIDTH-1] = LineBuffer[index]; // Make last element use new_pixel
		}
		if (it >= bufferSize - 1 && it%width>=K_WIDTH-1) {
//			printf("***********\n");
//			for (SNUMBER i=0;i<K_HEIGHT;i++) {
//				for (SNUMBER j=0;j<K_WIDTH;j++) {
//					printf("%d ", window.pix[i][j]);
//				}
//				printf("\n");
//			}
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
	printf("Start convolution\n");
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
					sum += w.pix[ik][jk]*kernel[ik][jk];
				}
			}
//			printf("**********\n");
//			for (int ik=0; ik<K_HEIGHT; ik++) {
//				for(int jk=0; jk<K_WIDTH; jk++) {
//					printf("%d ", w.pix[ik][jk]);
//				}
//				printf("|");
//				for(int jk=0; jk<K_WIDTH; jk++) {
//					printf("%d ", kernel[ik][jk]);
//				}
//				printf("\n");
//			}
			out_image.write(sum);
			printf("%d ", sum);
		}
		printf("\n");
	}

}


void convolution2d(
        const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
        SNUMBER width,
        SNUMBER height,
        const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
        NUMBER dst[MAX_J_HEIGHT*MAX_J_WIDTH])
{
//	if (width > MAX_I_WIDTH) {
//		width = MAX_I_WIDTH;
//	}
//	if (height > MAX_I_HEIGHT) {
//		height = MAX_I_HEIGHT;
//	}
	printf("Start function\n");

    NUMBER kernel[K_HEIGHT][K_WIDTH];
    hls::stream<NUMBER> image;
    hls::stream<WINDOW> windows; // window buffer (implement as FIFO)
    hls::stream<NUMBER> out_image;

    // Read image, kernel
    // TO: kernel, image
    readFromMemory(width, height, kernalSrc, kernel, src, image);
#ifndef __SYNTHESIS__
    printf("Pixel input count %d \n", image.size());
#endif
    // Read image window
    // Use line buffer to speed up
    // TO: windowFIFO
    readWindow(width, height, image, windows);
#ifndef __SYNTHESIS__
    printf("Pixel input left %d \n", image.size());
    printf("Windows count %d \n", windows.size());
#endif
    // Perform convolution
    // FROM: kernel, windowFIFO
    // TO: outputStream
    processConvolution2d(width, height, kernel, windows, out_image);
#ifndef __SYNTHESIS__
    printf("Windows left %d \n", windows.size());
    printf("Pixel output count %d \n", out_image.size());
#endif
    // Write output
    // FROM: outputStream
    // TO: dst
    writeToMemmory(width, height, out_image, dst);
#ifndef __SYNTHESIS__
    printf("Pixel input left %d \n", image.size());
    while(image.size() > 0) {
    	image.read();
    }

    printf("Pixel output left %d \n", out_image.size());
    while(out_image.size() > 0) {
    	out_image.read();
    }
    printf("Windows left %d \n", windows.size());
#endif
}
//void convolution2d(
//        const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
//        SNUMBER width,
//        SNUMBER height,
//        const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
//        NUMBER dst[MAX_J_WIDTH * MAX_J_HEIGHT])
//{
//    printf("\n");
////    printf("Output size : %d %d %d\n",MAX_J_WIDTH, MAX_J_HEIGHT, MAX_J_WIDTH * MAX_J_HEIGHT);
//    for (SNUMBER i=0; i<height-K_HEIGHT+1; i++) {
//        for (SNUMBER j=0; j<width-K_WIDTH+1; j++) {
//            NUMBER sum=0;
//            for (SNUMBER ic=0; ic<K_HEIGHT;ic++) {
//                for (SNUMBER jc=0; jc<K_WIDTH;jc++) {
//                    sum+=src[(i+ic)*MAX_I_WIDTH+(j+jc)] * kernalSrc[ic*K_WIDTH+jc];
//                }
//            }
//            SNUMBER index = i*MAX_J_WIDTH+j;
//            dst[index] = sum;
//        }
//
//    }
//    printf("\n");
//
//}
