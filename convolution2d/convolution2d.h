#pragma once

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

typedef int NUMBER;
typedef int SNUMBER;

#define MAX_I_WIDTH 192
#define MAX_I_HEIGHT 108
#define K_WIDTH 2
#define K_HEIGHT 3
#define MAX_J_WIDTH 192
#define MAX_J_HEIGHT 108

 void convolution2d(
         const NUMBER kernalSrc[K_HEIGHT*K_WIDTH],
         SNUMBER width,
         SNUMBER height,
         const NUMBER src[MAX_I_HEIGHT*MAX_I_WIDTH],
         NUMBER dst[MAX_J_WIDTH * MAX_J_HEIGHT]);
#endif
