#ifndef CubeAttribute_H
#define CubeAttribute_H
#include "Point.h"
#include <vector>

class CubeAttribute
{
public:
	//các mảng vertex chứa các đỉnh cho hình hộp
	std::vector<point> vertexArray;
	//tọa độ tâm hình hộp
	point centerObject;
	//số lượng vertex trên 1 hàng
	int numberVertexInAxisX, numberVertexInAxisY, numberVertexInAxisZ;
	//các mảng vertex chứa các normal vector cho hình hộp
	std::vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;
	CubeAttribute();
	CubeAttribute(CubeAttribute *cube);
	CubeAttribute(CubeAttribute &cube);
	~CubeAttribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	}
	void insertColor(float red, float green, float blue, float alpha);
};

#endif
