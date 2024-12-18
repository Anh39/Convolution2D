#pragma once

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

typedef int NUMBER;
typedef int SNUMBER;

#define MAX_I_WIDTH 100
#define MAX_I_HEIGHT 100
#define K_WIDTH 5
#define K_HEIGHT 5
#define MAX_J_WIDTH 96
#define MAX_J_HEIGHT 96

 void convolution2d(
         const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
         SNUMBER width,
         SNUMBER height,
         const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
         NUMBER dst[MAX_J_WIDTH * MAX_J_HEIGHT]);
#endif
