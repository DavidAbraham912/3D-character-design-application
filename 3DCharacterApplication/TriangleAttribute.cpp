#include "TriangleAttribute.h"

TriangleAttribute::TriangleAttribute() {
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	vertexArray[0] = {0.0f,0.0f,0.0f};
	vertexArray[1] = { 0.0f,0.0f,0.0f };
	vertexArray[2] = { 0.0f,0.0f,0.0f };
	normalVector = { 0.0f,0.0f,0.0f };
	centerObject = { 0,0,0 };
	mShiness = 20.0f; id = 0;
	idTexture = -1;
}
TriangleAttribute::TriangleAttribute(TriangleAttribute *tria) {
	for (int i = 0; i < 3; i++) {
		vertexArray[i] = tria->vertexArray[i];
	}
	colorR = tria->colorR;
	colorG = tria->colorG;
	colorB = tria->colorB;
	colorA = tria->colorA;
	centerObject = tria->centerObject;
	normalVector = tria->normalVector;
	mShiness = tria->mShiness;
	id = tria->id;
	idTexture = tria->idTexture;
}
TriangleAttribute::TriangleAttribute(TriangleAttribute &tria) {
	for (int i = 0; i < 9; i++) {
		vertexArray[i] = tria.vertexArray[i];
	}
	colorR = tria.colorR;
	colorG = tria.colorG;
	colorB = tria.colorB;
	colorA = tria.colorA;
	centerObject = tria.centerObject;
	normalVector = tria.normalVector;
	mShiness = tria.mShiness;
	id = tria.id;
	idTexture = tria.idTexture;
}
//các hàm thêm thuộc tính
void TriangleAttribute::setVertexAtIndex(int index, point vertex) {
	vertexArray[index] = vertex;
}
void TriangleAttribute::setNormalVector(point normal) {
	normalVector = normal;
}
void TriangleAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}
//các hàm lấy giá trị
point TriangleAttribute::getVertexAtIndex(int index) {
	return vertexArray[index];
}
void TriangleAttribute::getVertexAtIndex(int index, float *arrayOut) {
	arrayOut[0] = vertexArray[index].x;
	arrayOut[1] = vertexArray[index].y;
	arrayOut[2] = vertexArray[index].z;
}
point TriangleAttribute::getNormalVector() {
	return normalVector;
}
//lấy số đỉnh hiện có
int TriangleAttribute::getNumberVertex() {
	return 3;
}
