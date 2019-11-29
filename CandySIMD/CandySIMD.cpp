/*
	FAST-EDGE
	Copyright (c) 2009 Benjamin C. Haynor

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "imageio.h"
#include "fast-edge.h"
#include <fstream>

int main()
{
	std::ifstream inp{ "test.bmp", std::ios_base::binary };
	if (!inp.is_open()) {
		printf("ERROR: can't open 1212212test.bmg!");
	}
	char type[4];
	inp.read(type, 2);
	std::cout << _HEX << type << std::endl;
	inp.close();

	FILE* fp = NULL;
	errno_t err;
	err = fopen_s(&fp, "24_500.bmp", "rb");
	int w, h, i;
	if (err == 0) {
		printf("ERROR: can't open test.bmg!");
	}
	else {
		if (read_pgm_hdr(fp, &w, &h) != -1) {
			struct image img, img_gauss, img_out; //img_scratch, img_scratch2, 
			printf("*** PGM file recognized, reading data into image struct ***\n");
			//读取文件进img
			img.width = w;
			img.height = h;
			unsigned char* img_data = (unsigned char*)malloc(w * h * sizeof(char));
			for (i = 0; i < w * h; i++) {
				img_data[i] = fgetc(fp);
			}
			img.pixel_data = img_data;
			//申请空间
			img_out.width = img_gauss.width = w;
			img_out.height = img_gauss.height = h;
			unsigned char* img_gauss_data = (unsigned char*)malloc(w * h * sizeof(char));
			img_gauss.pixel_data = img_gauss_data;
			unsigned char* img_out_data = (unsigned char*)malloc(w * h * sizeof(char));
			img_out.pixel_data = img_out_data;

			printf("*** image struct initialized ***\n");
			printf("*** performing gaussian noise reduction ***\n");
			//经过高斯处理过的图片存储在img_gauss
			gaussian_noise_reduce(&img, &img_gauss);
			//printf("*** performing morphological closing ***\n");
			//morph_close(&img, &img_scratch, &img_scratch2, &img_gauss);
			canny_edge_detect(&img_gauss, &img_out);
			write_pgm_image(&img_out);
			free(img_data);
			free(img_gauss_data);
			free(img_out_data);
		}
		else {
			printf("ERROR:test.bgm is not a PGM file!");
		}
	}
	return(1);
}
