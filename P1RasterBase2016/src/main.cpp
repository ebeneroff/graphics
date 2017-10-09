#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"
#define COLOR_1_R 239
#define COLOR_1_G 48
#define COLOR_1_B 84
#define COLOR_2_R 67
#define COLOR_2_G 129
#define COLOR_2_B 193

// This allows you to skip the `std::` in front of C++ standard library
// functions. You can also say `using std::cout` to be more selective.
// You should never do this in a header file.
using namespace std;

struct vertex {
  int x, y;
  float z;
  int r, g, b;
};

struct triangle {
  vertex v0, v1, v2;
  int minX, maxX, minY, maxY;
};

int g_width, g_height;

int convertWorldToPxX(double x, int width, int height) {
  float aspect = (float)max(g_width, g_height)/min(g_width, g_height);

  if(width > height) {
    x /= aspect;
  }

  return (width - 1)/2 * x + ((width - 1)/2);
}

int convertWorldToPxY(double y, int width, int height) {
  float aspect = (float)max(g_width, g_height)/min(g_width, g_height);
  
  if(height > width) {
    y /= aspect;
  }

  return (height - 1)/2 * y + ((height - 1)/2);
}

vector<vertex> convertVertexWorldToPx(vector<float> &posBuf, int width, int height) {
  vector<vertex> vertices(posBuf.size()/3);

  for(int i = 0; i < posBuf.size()/3; i++) {
    vertices[i].x = convertWorldToPxX(posBuf[i * 3 + 0], width, height);
    vertices[i].y = convertWorldToPxY(posBuf[i * 3 + 1], width, height);
    vertices[i].z = posBuf[i * 3 + 2];
  }

  return vertices;
}

vector<triangle> assignVerticesToTriangles(vector<unsigned int> &triBuf, vector<vertex> vertices) {
  vector<triangle> triangles(triBuf.size()/3);

  for(int i = 0; i < triBuf.size()/3; i++) {
    triangles[i].v0 = vertices[triBuf[i * 3 + 0]];
    triangles[i].v1 = vertices[triBuf[i * 3 + 1]];
    triangles[i].v2 = vertices[triBuf[i * 3 + 2]];

    triangles[i].minX = triangles[i].v2.x < (triangles[i].v0.x < triangles[i].v1.x ? triangles[i].v0.x : triangles[i].v1.x) ? triangles[i].v2.x : (triangles[i].v0.x < triangles[i].v1.x ? triangles[i].v0.x : triangles[i].v1.x);
    triangles[i].minY = triangles[i].v2.y < (triangles[i].v0.y < triangles[i].v1.y ? triangles[i].v0.y : triangles[i].v1.y) ? triangles[i].v2.y : (triangles[i].v0.y < triangles[i].v1.y ? triangles[i].v0.y : triangles[i].v1.y);
    triangles[i].maxX = triangles[i].v2.x > (triangles[i].v0.x > triangles[i].v1.x ? triangles[i].v0.x : triangles[i].v1.x) ? triangles[i].v2.x : (triangles[i].v0.x > triangles[i].v1.x ? triangles[i].v0.x : triangles[i].v1.x);
    triangles[i].maxY = triangles[i].v2.y > (triangles[i].v0.y > triangles[i].v1.y ? triangles[i].v0.y : triangles[i].v1.y) ? triangles[i].v2.y : (triangles[i].v0.y > triangles[i].v1.y ? triangles[i].v0.y : triangles[i].v1.y);
  }

  return triangles;
}

float calculateBeta(int x, int y, triangle tri) {
	int numerator[4], denominator[4];
	float det0, det1;
	numerator[0] = tri.v0.x - tri.v2.x;
	numerator[1] = x - tri.v2.x;
	numerator[2] = tri.v0.y - tri.v2.y;
	numerator[3] = y - tri.v2.y;
	denominator[0] = tri.v1.x - tri.v0.x;
	denominator[1] = tri.v2.x - tri.v0.x;
	denominator[2] = tri.v1.y - tri.v0.y;
	denominator[3] = tri.v2.y - tri.v0.y;
	// ad - bc
	det0 = numerator[0] * numerator[3] - numerator[1] * numerator[2];
	det1 = denominator[0] * denominator[3] - denominator[1] * denominator[2];
	return det0/det1;
}

float calculateGamma(int x, int y, triangle tri) {
	int numerator[4], denominator[4];
	float det0, det1;
	numerator[0] = tri.v1.x - tri.v0.x;
	numerator[1] = x - tri.v0.x;
	numerator[2] = tri.v1.y - tri.v0.y;
	numerator[3] = y - tri.v0.y;
	denominator[0] = tri.v1.x - tri.v0.x;
	denominator[1] = tri.v2.x - tri.v0.x;
	denominator[2] = tri.v1.y - tri.v0.y;
	denominator[3] = tri.v2.y - tri.v0.y;
	// ad - bc
	det0 = numerator[0] * numerator[3] - numerator[1] * numerator[2];
	det1 = denominator[0] * denominator[3] - denominator[1] * denominator[2];
	return det0/det1;
}

/*
   Helper function you will want all quarter
   Given a vector of shapes which has already been read from an obj file
   resize all vertices to the range [-1, 1]
 */
void resize_obj(std::vector<tinyobj::shape_t> &shapes){
   float minX, minY, minZ;
   float maxX, maxY, maxZ;
   float scaleX, scaleY, scaleZ;
   float shiftX, shiftY, shiftZ;
   float epsilon = 0.001;

   minX = minY = minZ = 1.1754E+38F;
   maxX = maxY = maxZ = -1.1754E+38F;

   //Go through all vertices to determine min and max of each dimension
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         if(shapes[i].mesh.positions[3*v+0] < minX) minX = shapes[i].mesh.positions[3*v+0];
         if(shapes[i].mesh.positions[3*v+0] > maxX) maxX = shapes[i].mesh.positions[3*v+0];

         if(shapes[i].mesh.positions[3*v+1] < minY) minY = shapes[i].mesh.positions[3*v+1];
         if(shapes[i].mesh.positions[3*v+1] > maxY) maxY = shapes[i].mesh.positions[3*v+1];

         if(shapes[i].mesh.positions[3*v+2] < minZ) minZ = shapes[i].mesh.positions[3*v+2];
         if(shapes[i].mesh.positions[3*v+2] > maxZ) maxZ = shapes[i].mesh.positions[3*v+2];
      }
   }

  //From min and max compute necessary scale and shift for each dimension
   float maxExtent, xExtent, yExtent, zExtent;
   xExtent = maxX-minX;
   yExtent = maxY-minY;
   zExtent = maxZ-minZ;
   if (xExtent >= yExtent && xExtent >= zExtent) {
      maxExtent = xExtent;
   }
   if (yExtent >= xExtent && yExtent >= zExtent) {
      maxExtent = yExtent;
   }
   if (zExtent >= xExtent && zExtent >= yExtent) {
      maxExtent = zExtent;
   }
   scaleX = 2.0 /maxExtent;
   shiftX = minX + (xExtent/ 2.0);
   scaleY = 2.0 / maxExtent;
   shiftY = minY + (yExtent / 2.0);
   scaleZ = 2.0/ maxExtent;
   shiftZ = minZ + (zExtent)/2.0;

   // Go through all vertices shift and scale them
   for (size_t i = 0; i < shapes.size(); i++) {
      for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
         shapes[i].mesh.positions[3*v+0] = (shapes[i].mesh.positions[3*v+0] - shiftX) * scaleX;
         assert(shapes[i].mesh.positions[3*v+0] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+0] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+1] = (shapes[i].mesh.positions[3*v+1] - shiftY) * scaleY;
         assert(shapes[i].mesh.positions[3*v+1] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+1] <= 1.0 + epsilon);
         shapes[i].mesh.positions[3*v+2] = (shapes[i].mesh.positions[3*v+2] - shiftZ) * scaleZ;
         assert(shapes[i].mesh.positions[3*v+2] >= -1.0 - epsilon);
         assert(shapes[i].mesh.positions[3*v+2] <= 1.0 + epsilon);
      }
   }
}

void checkArgs(int width, int height, int mode) {
  if(mode != 1 && mode != 2) {
    cout << "Mode must be 1 or 2" << endl;
    cout << "Usage: raster meshfile imagefile width height mode" << endl;
    cout << "Example: ./raster ../resources/bunny.obj out.png 512 512 1" << endl;
    exit(1);
  }
  if(width == 0 || height == 0) {
    cout << "Please specify a nonzero size" << endl;
    cout << "Usage: raster meshfile imagefile width height mode" << endl;
    cout << "Example: ./raster ../resources/bunny.obj out.png 512 512 1" << endl;
    exit(1);
  }
}

int main(int argc, char **argv)
{
  if(argc < 6) {
      cout << "Usage: raster meshfile imagefile width height mode" << endl;
      return 0;
  }

  // OBJ filename
  string meshName(argv[1]);
  string imgName(argv[2]);
  g_width = atoi(argv[3]);
  g_height = atoi(argv[4]);
  int mode = atoi(argv[5]);
  checkArgs(g_width, g_height, mode);

  // create an image
  auto image = make_shared<Image>(g_width, g_height);
  
  // triangle buffer
  vector<unsigned int> triBuf;
  // position buffer
  vector<float> posBuf;
  // Some obj files contain material information.
  // We'll ignore them for this assignment.
  vector<tinyobj::shape_t> shapes; // geometry
  vector<tinyobj::material_t> objMaterials; // material
  string errStr;

  bool rc = tinyobj::LoadObj(shapes, objMaterials, errStr, meshName.c_str());
  /* error checking on read */
  if(!rc) {
    cerr << errStr << endl;
  } else {
    // keep this code to resize your object to be within -1 -> 1
    resize_obj(shapes); 
    posBuf = shapes[0].mesh.positions;
    triBuf = shapes[0].mesh.indices;
  }
  cout << "Number of vertices: " << posBuf.size()/3 << endl;
  cout << "Number of triangles: " << triBuf.size()/3 << endl;

  vector<triangle> triangles(triBuf.size()/3);
  vector<vertex> vertices(posBuf.size()/3);
  vector<vector<float>> zbuffer(g_width, vector<float>(g_height));

  // initialize z buffer
  for(int i = 0; i < g_width; i++) {
    for(int j = 0; j < g_height; j++) {
      zbuffer[i][j] = -1;
    }
  }

  // convert vertices from world to pixel coordinates
  vertices = convertVertexWorldToPx(posBuf, g_width, g_height);

  // attach vertices to each triangle
  triangles = assignVerticesToTriangles(triBuf, vertices);

  // draw triangles
  for(int i = 0; i < triangles.size(); i++) {
    for(int x = triangles[i].minX; x <= triangles[i].maxX; x++) {
      for(int y = triangles[i].minY; y <= triangles[i].maxY; y++) {
        float b = calculateBeta(x, y, triangles[i]);
        float g = calculateGamma(x, y, triangles[i]);
        float a = 1 - b - g;
   
        if(b >= 0 && b <= 1 && g >= 0 && g <= 1 && a >=0 && a <= 1) {
          if(mode == 1) {
            float currZ = a * triangles[i].v0.z + b * triangles[i].v1.z + g * triangles[i].v2.z;
            if(zbuffer[x][y] < currZ) {
              image->setPixel(x, y , (currZ + 1) * 127.5, 0, 0);
              zbuffer[x][y] = currZ;
            }
          }
          else {
            float currY = a * triangles[i].v0.y + b * triangles[i].v1.y + g * triangles[i].v2.y;
            float m = currY/g_height;
            image->setPixel(x, y, COLOR_1_R * m + ((1 - m) * COLOR_2_R), COLOR_1_G * m + ((1 - m) * COLOR_2_G), COLOR_1_B * m + ((1 - m) * COLOR_2_B));
          } 
        }
      }
    }
  }

  // write out the image
  image->writeToFile(imgName);

  return 0;
}
