#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "src/perlin.h"
#include "image.h"

#define R0 58650
#define R1 52275
#define R2 45645
#define R3 39270
#define R4 32896
#define R5 26265
#define R6 19890
#define R7 13260
#define R8 6885
#define R9 511

#define GET_R(p) ((p) >> 8)
#define GET_G(p) ((p) & 0x0ff)

// #define FREQ  0.0025
// #define DEPTH 11

struct pixel
{
	uint8_t red, green, blue;
};

// perlin noise outputs a number from 0 to 9 inclusive, although 0 and 9 are rare
uint16_t colors[] = {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9};
char map[] = ".,:;ox%#@";

int main(int argc, char *argv[])
{
    int x = argc >= 2 ? atoi(argv[1]) : 1920;
	int y = argc >= 3 ? atoi(argv[2]) : 1080;

	float FREQ = getenv("freq") == NULL ? 0.0025 : atof(getenv("freq"));
	float DEPTH = getenv("depth") == NULL ? 11 : atof(getenv("depth"));

	srand(time(NULL));
	int x_scale = rand() % 10000;
	int y_scale = rand() % 10000;

	size_t size = x * y * (sizeof(struct pixel));

	struct pixel *image = (struct pixel *)malloc(size);
	if (!image){
		printf("could not allocate %ld bytes\n", size);
		return 1;
	}

	//struct pixel *end = (struct pixel *)image + x * y;
	
	int perl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			perl = (int)((perlin2d(i + x_scale, j + y_scale, FREQ, DEPTH) * 10));

			image[x*j + i].red   = GET_R(colors[perl]);
			image[x*j + i].green = GET_G(colors[perl]);
			image[x*j + i].blue  =                   0;
		}
	}
	image_write("map.jpg", x, y, 3, (void *)image, 0, 100, NULL);
	free(image);
}
