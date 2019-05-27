#ifndef EmptyCylinderAttribute_H
#define EmptyCylinderAttribute_H
#include "Point.h"
#include <vector>

class EmptyCylinderAttribute
{
public:
	//tâm của hình tròn ở đáy
	point centerObject;
	//chiều cao
	float height;
	//bán kính của hình tròn đáy
	float radiusUpIn, radiusDownIn, radiusUpOut, radiusDownOut;
	//số đường kinh tuyến và vĩ tuyến của hình cầu(số đường càng nhiều thì hình càng mượt)
	//kinh tuyến nằm dọc còn vĩ tuyến nằm ngang
	//Lưu ý:phải chia hết cho 360
	int numberLongitude, numberLatitude;
	//giá trị dùng khi bo góc
	int numberLongitudeRound, numberLatitudeRound;
	//số độ tối đa được vẽ(360 là vẽ toàn bộ hình cầu,180 là vẽ 1 nửa hình cầu)
	int degreeLongitudeLimit, degreeLatitudeLimit;
	//các vertex đã được máy tính
	std::vector<point> vertexArray;
	//các normal vector đã được máy tính
	std::vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;

	EmptyCylinderAttribute();
	EmptyCylinderAttribute(EmptyCylinderAttribute *cylinder);
	EmptyCylinderAttribute(EmptyCylinderAttribute &cylinder);
	~EmptyCylinderAttribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	};
	
	void insertColor(float red, float green, float blue, float alpha);
	
};

#endif
