#include "PyramidAttribute.h"

PyramidAttribute::PyramidAttribute() {
	//cái này chưa tính
	point normalDefaul[] = {
		{ -0.66f,0.33f,0.66f },{ 0.66f,0.33f,0.66f } ,{ 0.66f,0.33f,-0.66f } ,{ -0.66f,0.33f,-0.66f } ,{ 0,-1,0 },{0,-1,0}
	};
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	centerObject = { 0.0f,0.0f,0.0f };
	for (int i = 0; i < 6; i++) {
		normalVector[i] = normalDefaul[i];
	}
	mShiness = 20.0f; id = 0;
	idTexture = -1;
}
PyramidAttribute::PyramidAttribute(PyramidAttribute *pyr) {
	colorR = pyr->colorR;
	colorG = pyr->colorG;
	colorB = pyr->colorB;
	colorA = pyr->colorA;
	centerObject = pyr->centerObject;
	for (int i = 0; i < 5; i++) {
		vertexArray[i] = pyr->vertexArray[i];
	}
	for (int i = 0; i < 6; i++) {
		normalVector[i] = pyr->normalVector[i];
	}
	mShiness = pyr->mShiness;
	id = pyr->id;
	idTexture = pyr->idTexture;
}
PyramidAttribute::PyramidAttribute(PyramidAttribute &pyr) {
	colorR = pyr.colorR;
	colorG = pyr.colorG;
	colorB = pyr.colorB;
	colorA = pyr.colorA;
	centerObject = pyr.centerObject;
	for (int i = 0; i < 5; i++) {
		vertexArray[i] = pyr.vertexArray[i];
	}
	for (int i = 0; i < 6; i++) {
		normalVector[i] = pyr.normalVector[i];
	}
	mShiness = pyr.mShiness;
	id = pyr.id;
	idTexture = pyr.idTexture;
}
//các hàm đặt giá trị
void PyramidAttribute::setVertexAtIndex(int index, float x, float y, float z) {
	vertexArray[index].x = x;
	vertexArray[index].y = y;
	vertexArray[index].z = z;
}
void PyramidAttribute::setNormalVectorAtIndex(int index, float x, float y, float z) {
	normalVector[index].x = x;
	normalVector[index].y = y;
	normalVector[index].z = z;
}
void PyramidAttribute::setNormalVectorAtIndex(int index, float *array) {
	normalVector[index].x = array[0];
	normalVector[index].y = array[1];
	normalVector[index].z = array[2];
}
void PyramidAttribute::setCenterPyramid(float x, float y, float z) {
	centerObject.x = x;
	centerObject.y = y;
	centerObject.z = z;
}
void PyramidAttribute::getCenterPyramid(float *arrayOut) {
	arrayOut[0] = centerObject.x;
	arrayOut[1] = centerObject.y;
	arrayOut[2] = centerObject.z;
}
point PyramidAttribute::getCenterPyramid() {
	return centerObject;
}
void PyramidAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}
//các hàm lấy giá trị
void PyramidAttribute::getVertexAtIndex(int index, float *arrayOut) {
	if (index<5) {
		arrayOut[0] = vertexArray[index].x;
		arrayOut[1] = vertexArray[index].y;
		arrayOut[2] = vertexArray[index].z;
	}
	else
	{
		//nếu vị trí đó k0 tồn tại thì trả về các giá trị 0
		arrayOut[0] = 0;
		arrayOut[1] = 0;
		arrayOut[2] = 0;
	}
}
point PyramidAttribute::getVertexAtIndex(int index) {
	return vertexArray[index];
}
point PyramidAttribute::getNormalVectorAtIndex(int index) {
	return normalVector[index];
}
void PyramidAttribute::getNormalVectorAtIndex(int index, float *arrayOut) {
	if (index<6) {
		arrayOut[0] = normalVector[index].x;
		arrayOut[1] = normalVector[index].y;
		arrayOut[2] = normalVector[index].z;
	}
	else
	{
		//nếu vị trí đó k0 tồn tại thì trả về các giá trị 0
		arrayOut[0] = 0;
		arrayOut[1] = 0;
		arrayOut[2] = 0;
	}
}
//lấy số đỉnh hiện có
int PyramidAttribute::getNumberVertex() {
	return 5;
}