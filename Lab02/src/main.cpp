#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Image.h"

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

struct triangle {
	int v1X, v1Y, r0, g0, b0, v2X, v2Y, r1, g1, b1, v3X, v3Y, r2, g2, b2;
} t;

struct box {
	int minX, maxX, minY, maxY;
} b;

float calculateBeta(int x, int y, triangle tri) {
	int numerator[4], denominator[4];
	float det0, det1;
	numerator[0] = tri.v1X - tri.v3X;
	numerator[1] = x - tri.v3X;
	numerator[2] = tri.v1Y - tri.v3Y;
	numerator[3] = y - tri.v3Y;
	denominator[0] = tri.v2X - tri.v1X;
	denominator[1] = tri.v3X - tri.v1X;
	denominator[2] = tri.v2Y - tri.v1Y;
	denominator[3] = tri.v3Y - tri.v1Y;
	// ad - bc
	det0 = numerator[0] * numerator[3] - numerator[1] * numerator[2];
	det1 = denominator[0] * denominator[3] - denominator[1] * denominator[2];
	return det0/det1;
}

float calculateGamma(int x, int y, triangle tri) {
	int numerator[4], denominator[4];
	float det0, det1;
	numerator[0] = tri.v2X - tri.v1X;
	numerator[1] = x - tri.v1X;
	numerator[2] = tri.v2Y - tri.v1Y;
	numerator[3] = y - tri.v1Y;
	denominator[0] = tri.v2X - tri.v1X;
	denominator[1] = tri.v3X - tri.v1X;
	denominator[2] = tri.v2Y - tri.v1Y;
	denominator[3] = tri.v3Y - tri.v1Y;
	// ad - bc
	det0 = numerator[0] * numerator[3] - numerator[1] * numerator[2];
	det1 = denominator[0] * denominator[3] - denominator[1] * denominator[2];
	return det0/det1;
}

int main(int argc, char **argv)
{
	if(argc < 10) {
		cout << "Usage: Lab1 <out_image_name>.png width height x0 y0 r0 g0 b0 x1 y1 r1 g1 b1 x2 y2 r2 g2 b2" << endl;
		return 0;
	}
	// Output filename
	string filename(argv[1]);
	// Width of image
	int width = atoi(argv[2]);
	// Height of image
	int height = atoi(argv[3]);
	t.v1X = atoi(argv[4]);
	t.v1Y = atoi(argv[5]);
	t.r0 = atoi(argv[6]);
	t.g0 = atoi(argv[7]);
	t.b0 = atoi(argv[8]);
	t.v2X = atoi(argv[9]);
	t.v2Y = atoi(argv[10]);
	t.r1 = atoi(argv[11]);
	t.g1 = atoi(argv[12]);
	t.b1 = atoi(argv[13]);
	t.v3X = atoi(argv[14]);
	t.v3Y = atoi(argv[15]);
	t.r2 = atoi(argv[16]);
	t.g2 = atoi(argv[17]);
	t.b2 = atoi(argv[18]);


	// find bounding mins and maxs
	b.minX = t.v3X < (t.v1X < t.v2X ? t.v1X : t.v2X) ? t.v3X : (t.v1X < t.v2X ? t.v1X : t.v2X);
	b.minY = t.v3Y < (t.v1Y < t.v2Y ? t.v1Y : t.v2Y) ? t.v3Y : (t.v1Y < t.v2Y ? t.v1Y : t.v2Y);
	b.maxX = t.v3X > (t.v1X > t.v2X ? t.v1X : t.v2X) ? t.v3X : (t.v1X > t.v2X ? t.v1X : t.v2X);
	b.maxY = t.v3Y > (t.v1Y > t.v2Y ? t.v1Y : t.v2Y) ? t.v3Y : (t.v1Y > t.v2Y ? t.v1Y : t.v2Y);

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

	for(int x = b.minX; x <= b.maxX; x++) {
		for(int y = b.minY; y <= b.maxY; y++) {
			float b = calculateBeta(x, y, t);
			float g = calculateGamma(x, y, t);
			float a = 1 - b - g;
			if(b >= 0 && b <= 1 && g >= 0 && g <= 1 && a >=0 && a <= 1) {
				image->setPixel(x, y, a * t.r0 + b * t.r1 + g * t.r2, a * t.g0 + b * t.g1 + g * t.g2, a * t.b0 + b * t.b1 + g * t.b2);
			}
		}
	}

	// image->setPixel(t.v1X, t.v1Y, 255, 0, 0);
	// image->setPixel(t.v2X, t.v2Y, 255, 0, 0);
	// image->setPixel(t.v3X, t.v3Y, 255, 0, 0);

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
