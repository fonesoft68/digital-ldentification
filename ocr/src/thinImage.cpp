#include "ocr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

unsigned char* thinImage(unsigned char *origin)
{
	unsigned char *res;
	res = (unsigned char*) malloc (sizeof(unsigned char) * 28 * 28);
	memset(res, 0, sizeof(unsigned char) * 28 * 28);
	int flag = 0;
	int check = 0;
	for (int i = 0; i < heightOfImage; ++ i) {
		int left = 0;
		int right = 0;
		flag = 0;
		while (left < widthOfImage && right < widthOfImage) {
			int repair = 0;

			while (left < widthOfImage && !origin[i * widthOfImage + left]) {
				++ left;
			}
			right = left;
			while (right < widthOfImage && origin[i * widthOfImage + right]) {
				++ right;
			}

			if (left <= right && right < widthOfImage) {
				++ res[i * widthOfImage + ((left + right) >> 1)];
				flag = 1;
			}

			if(check) {
				int l = (left + right) >> 1;
				-- l;
				int r = l + 2;
				while (origin[(i - 1) * widthOfImage + l] || origin[i * widthOfImage + l]) {
					if (res[(i - 1) * widthOfImage + l]) {
						res[(i - 1) * widthOfImage + ((left + right) >> 1) - 1] = 1;
						for (int x = l; x < ((left + right) >> 1) - 1; ++ x) {
							if (i >= 2 && res[(i - 2) * widthOfImage + x] == 0) {
								res[(i - 1) * widthOfImage + x] = 1;
							}
						}
					}
					
					-- l;
				}

				while (origin[(i - 1) * widthOfImage + r] || origin[i * widthOfImage + r]) {
					if (res[(i - 1) * widthOfImage + r]) {
						res[(i - 1) * widthOfImage + ((left + right) >> 1) + 1] = 1;
						for (int x = ((left + right) >> 1) + 2; x <= r; ++ x) {
							if (i >= 2 && res[(i - 2) * widthOfImage + x] == 0) {
								res[(i - 1) * widthOfImage + x] = 1;
							}
						}
					}
					++ r;
				}
			}

			left = right;
		}
		
		if (flag) {
			check = 1;
		}
		else {
			check = 0;
		}

	}
	memcpy(origin, res, sizeof(unsigned char) * widthOfImage * heightOfImage);
	return res;
}
