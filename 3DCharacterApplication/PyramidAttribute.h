#ifndef PyramidAttribute_H
#define PyramidAttribute_H
#include "Point.h"

class PyramidAttribute
{
public:
	//có 5 vertex dùng cho hình kim tự tháp
	point vertexArray[5];
	//tọa độ tâm hình hộp
	point centerObject;
	//có 6 normal vector đại diện cho 6 mặt tam giác
	point normalVector[6];
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;

	PyramidAttribute();
	PyramidAttribute(PyramidAttribute *pyr);
	PyramidAttribute(PyramidAttribute &pyr);
	~PyramidAttribute() {
	}
	//các hàm đặt giá trị
	void setVertexAtIndex(int index, float x, float y, float z);
	void setNormalVectorAtIndex(int index, float x, float y, float z);
	void setNormalVectorAtIndex(int index, float *array);
	void setCenterPyramid(float x, float y, float z);
	void getCenterPyramid(float *arrayOut);
	point getCenterPyramid();
	void insertColor(float red, float green, float blue, float alpha);
	//các hàm lấy giá trị
	void getVertexAtIndex(int index, float *arrayOut);
	point getVertexAtIndex(int index);
	point getNormalVectorAtIndex(int index);
	void getNormalVectorAtIndex(int index, float *arrayOut);
	//lấy số đỉnh hiện có
	int getNumberVertex();
};

#endif
