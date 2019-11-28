#include <iostream>

#include <cstring>
#include <cmath>
#include <ctime>
#include "BMPIMage.h"
#include "fast-edge.h"

void gaussian_noise_reduce(BMPImage* img_in, BMPImage* img_out) {
#ifdef CLOCK
	clock_t start = clock();
#endif
	int w, h, x, y, max_x, max_y;
	w = img_in->width();
	h = img_in->height();
	max_x = w - 2;
	max_y = w * (h - 2);
	uchar* data = new uchar[w*h]();
	for (y = w * 2; y < max_y; y += w) {
		for (x = 2; x < max_x; x++) {
			data[x + y] = (2 * img_in->m_data[x + y - 2 - w - w] +
				4 * img_in->m_data[x + y - 1 - w - w] +
				5 * img_in->m_data[x + y - w - w] +
				4 * img_in->m_data[x + y + 1 - w - w] +
				2 * img_in->m_data[x + y + 2 - w - w] +
				4 * img_in->m_data[x + y - 2 - w] +
				9 * img_in->m_data[x + y - 1 - w] +
				12 * img_in->m_data[x + y - w] +
				9 * img_in->m_data[x + y + 1 - w] +
				4 * img_in->m_data[x + y + 2 - w] +
				5 * img_in->m_data[x + y - 2] +
				12 * img_in->m_data[x + y - 1] +
				15 * img_in->m_data[x + y] +
				12 * img_in->m_data[x + y + 1] +
				5 * img_in->m_data[x + y + 2] +
				4 * img_in->m_data[x + y - 2 + w] +
				9 * img_in->m_data[x + y - 1 + w] +
				12 * img_in->m_data[x + y + w] +
				9 * img_in->m_data[x + y + 1 + w] +
				4 * img_in->m_data[x + y + 2 + w] +
				2 * img_in->m_data[x + y - 2 + w + w] +
				4 * img_in->m_data[x + y - 1 + w + w] +
				5 * img_in->m_data[x + y + w + w] +
				4 * img_in->m_data[x + y + 1 + w + w] +
				2 * img_in->m_data[x + y + 2 + w + w]) / 159;
		}
	}
	img_out->m_data = data;
#ifdef CLOCK
	printf("Gaussian noise reduction - time elapsed: %f\n", ((double)clock() - start) / CLOCKS_PER_SEC);
#endif
}