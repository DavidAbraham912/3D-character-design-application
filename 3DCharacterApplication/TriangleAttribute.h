#ifndef TriangleAttribute_H
#define TriangleAttribute_H
#include "Point.h"
class TriangleAttribute
{
public:
	//mỗi tam giác có 3 đỉnh chứa trong đó các giá trị x,y,z
	point vertexArray[3];
	point centerObject;
	point normalVector;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;

	TriangleAttribute();
	TriangleAttribute(TriangleAttribute *triaStri);
	TriangleAttribute(TriangleAttribute &triaStri);
	~TriangleAttribute() {
	}
	//các hàm đặt giá trị
	void setVertexAtIndex(int index,point vertex);
	void setNormalVector(point normal);
	void insertColor(float red, float green, float blue, float alpha);
	//các hàm lấy giá trị
	point getVertexAtIndex(int index);
	void getVertexAtIndex(int index, float *arrayOut);
	point getNormalVector();
	//lấy số đỉnh hiện có
	int getNumberVertex();
	
};

#endif
