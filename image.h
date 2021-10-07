
#ifndef IMAGE_h
#define IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

// Copy of stbi_load
// params:
// 1: filename
// 2: pointer to int to put image width into
// 3: pointer to int to put image height into
// 4: pointer to int to put image channels into
// 5: just set to 0, dk what it does
// stbi_uc *(*image_load)(char const *, int *, int *, int *, int) = stbi_load;

// Copy of stbi_free_image
// void (*image_free)(void *) = stbi_image_free;

// Writes image the 'data' to the file 'filename'
// Paramters that are not needed for a certain file type should be 0 or null
// 'ext' is extracted from filename if null
// extern int image_write(const char *filename, int w, int h, int chans, const void *data, int stride_in_bytes, int quality, const char *ext);

// Add sepia filter to image 'data' and write to buffer of size 'size'
// if buffer is null, 'data' is modified
// extern int image_to_sepia(void *data, int channels, void *buffer, size_t size);

// Invert image colors, same rules as image_to_sepia
// extern int image_color_invert(void *data, int channels, void *buffer, size_t size);


#define STB_IMAGE_IMPLEMENTATION
#include "src/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "src/stb_write.h"

// Macros to compute Sepia filter value for each channel
#define SEP_R(p) ((uint8_t)fmin(0.393 * *(p) + 0.769 * *((p) + 1) + 0.189 * *((p) + 2), 255.0))
#define SEP_G(p) ((uint8_t)fmin(0.349 * *(p) + 0.686 * *((p) + 1) + 0.168 * *((p) + 2), 255.0))
#define SEP_B(p) ((uint8_t)fmin(0.272 * *(p) + 0.534 * *((p) + 1) + 0.131 * *((p) + 2), 255.0))

// Copy of stbi_load
// stbi_uc	*(*image_load)(char const *, int *, int *, int *, int) = stbi_load;

// Copy of stbi_free_image
// void (*image_free)(void *) = stbi_image_free;

// int image_write(const char *filename, int w, int h, int chans, const void *data, int stride_in_bytes, int quality, const char *ext);
// int image_to_sepia(void *data, int channels, void *buffer, size_t size);
// int image_color_invert(void *data, int channels, void *buffer, size_t size);


/* wrapper for stbi_write_<format>. For formats that do not require
 all paramters, they should be set to 0 or NULL
 NULL in ext to extract extension from filename

 Example: image_write("out.jpg", 500, 500, channels, image, 0, 100, NULL)
                                 ^     ^					  ^	
                                 |     |					  |
                      Image width    Image length  only pngs require strides */
int image_write(const char *filename, int w, int h, int chans, const void *data, int stride_in_bytes, int quality, const char *ext)
{
	ext = ext == NULL ? strrchr(filename, '.') + 1 : ext;
	if (ext == NULL)
		return 0;

	if (!strncmp(ext, "png", 3))
		return stbi_write_png(filename, w, h, chans, data, stride_in_bytes);
	else if (!strncmp(ext, "jpg", 3) || !strncmp(ext, "jpeg", 4))
		return stbi_write_jpg(filename, w, h, chans, data, quality);
	else if (!strncmp(ext, "bmp", 3))
		return stbi_write_bmp(filename, w, h, chans, data);
	else
		return 0;
}

// Add sepia filter to an image, NULL in buffer to modify the given data
// or pointer to buffer of size 'size' to copy the image in
int image_to_sepia(void *data, int channels, void *buffer, size_t size)
{
	uint8_t pixel[channels];
	uint8_t *end = (uint8_t *)data + size;

	if (buffer == NULL)
	{
		for (uint8_t *p = (uint8_t *)data; p != end; p += channels)
		{
			memcpy(&pixel, p, sizeof(uint8_t) * (channels));

			*p       = SEP_R(&pixel[0]);
			*(p + 1) = SEP_G(&pixel[0]);
			*(p + 2) = SEP_B(&pixel[0]);

			if (channels == 4){
				*(p + 3) = pixel[3];
			}
		}
		return 1;
	}
	else
	{
		for (uint8_t *p = (uint8_t *)data, *pg = (uint8_t *)buffer; p != end; p += channels, pg += channels)
        {
			//puts("ee");
            *pg       = SEP_R(p);
            *(pg + 1) = SEP_G(p);
            *(pg + 2) = SEP_B(p);

			if(channels == 4) {
             *(pg + 3) = *(p + 3);
         	}
		}
		return 1;
	}
}

// Invert colors of image NULL in buffer to modify the given data
// or pointer to buffer of size 'size' to copy the image in
int image_color_invert(void *data, int channels, void *buffer, size_t size)
{
    uint8_t *end = (uint8_t *)data + size;

    if (buffer == NULL)
    {
        for (uint8_t *p = (uint8_t *)data; p != end; p += channels)
        {
            *p       = 0xff - *p;
            *(p + 1) = 0xff - *(p + 1);
            *(p + 2) = 0xff - *(p + 2);

            if (channels == 4){
                *(p + 3) = *(p + 3);
            }
        }
        return 1;
    }
    else
    {
        for (uint8_t *p = (uint8_t *)data, *pg = (uint8_t *)buffer; p != end; p += channels, pg += channels)
        {
			*pg       = 0xff - *p;
            *(pg + 1) = 0xff - *(p + 1);
            *(pg + 2) = 0xff - *(p + 2);

            if(channels == 4) {
             *(pg + 3) = *(p + 3);
            }
        }
        return 1;
    }
}
#endif // IMAGE_H
