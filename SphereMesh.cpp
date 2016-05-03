#include "stdafx.h"
#include "SphereMesh.h"
//#include <SDL.h>


SphereMesh::SphereMesh(int radialSamples, int axialSamples, float radius)
{
	
	for (int row = 0; row < radialSamples; ++row) {
		float angle1 = row * M_PI / (radialSamples - 1);
		float z = radius * cos(angle1);
		float zRadius = radius * sin(angle1);

		for (int column = 0; column < axialSamples; ++column) {
			float angle = 2 * column * M_PI / (axialSamples - 1);
			float x = zRadius * cos(angle);
			float y = zRadius * sin(angle);
			//System.out.println("Adding : " + x + "," + y + "," + z);
			AddVertex(x, y, z);
			AddTexCoord(angle1 / M_PI, angle / (2 * M_PI));
			float length = sqrt(x*x + y*y + z*z);
			AddNormal(x/length,y/length,z/length);
		}
	}
	
	int triangleIndex = 0;
	for (int row = 0; row < radialSamples - 1; ++row) {
		for (int column = 0; column < axialSamples - 1; ++column) {
			int index1 = row * radialSamples + column;
			int index2 = index1 + 1;
			int index3 = index2 + radialSamples;
			int index4 = index3 - 1;
			//if ((row + column) % 2 == 0) {
				AddTriangle(index1, index2, index3);
				AddTriangle(index1, index3, index4);
			/*}
			else {
				AddTriangle(index3, index2, index1);
				AddTriangle(index4, index3, index1);
			}*/
			++triangleIndex;
		}
	}
}


SphereMesh::~SphereMesh()
{
}
