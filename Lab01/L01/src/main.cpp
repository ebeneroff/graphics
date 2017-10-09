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
	int v1X, v1Y, v2X, v2Y, v3X, v3Y;
} t;

struct box {
	int minX, maxX, minY, maxY;
} b;

int main(int argc, char **argv)
{
	if(argc < 10) {
		cout << "Usage: Lab1 <out_image_name>.png width height v1X v1Y v2X v2Y v3X v3Y" << endl;
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
	t.v2X = atoi(argv[6]);
	t.v2Y = atoi(argv[7]);
	t.v3X = atoi(argv[8]);
	t.v3Y = atoi(argv[9]);

	// find bounding mins and maxs
	b.minX = t.v3X < (t.v1X < t.v2X ? t.v1X : t.v2X) ? t.v3X : (t.v1X < t.v2X ? t.v1X : t.v2X);
	b.minY = t.v3Y < (t.v1Y < t.v2Y ? t.v1Y : t.v2Y) ? t.v3Y : (t.v1Y < t.v2Y ? t.v1Y : t.v2Y);
	b.maxX = t.v3X > (t.v1X > t.v2X ? t.v1X : t.v2X) ? t.v3X : (t.v1X > t.v2X ? t.v1X : t.v2X);
	b.maxY = t.v3Y > (t.v1Y > t.v2Y ? t.v1Y : t.v2Y) ? t.v3Y : (t.v1Y > t.v2Y ? t.v1Y : t.v2Y);

	// Create the image. We're using a `shared_ptr`, a C++11 feature.
	auto image = make_shared<Image>(width, height);

	for(int x = b.minX; x <= b.maxX; x++) {
		for(int y = b.minY; y <= b.maxY; y++) {
			image->setPixel(x, y, 0, 0, 255);
		}
	}

	image->setPixel(t.v1X, t.v1Y, 255, 0, 0);
	image->setPixel(t.v2X, t.v2Y, 255, 0, 0);
	image->setPixel(t.v3X, t.v3Y, 255, 0, 0);

	// Write image to file
	image->writeToFile(filename);
	return 0;
}
