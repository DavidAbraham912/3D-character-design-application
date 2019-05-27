#ifndef ConeAttribute_H
#define ConeAttribute_H
#include "Point.h"
#include <vector>
using namespace std;

class ConeAttribute
{
public:
	//tâm và đỉnh của hình tròn ở đáy
	point centerObject;
	//chiều cao cone
	float height;
	//bán kính của hình tròn đáy
	float radius;
	vector<point> vertexArray;
	//normal vector
	vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	//số đường kinh tuyến và vĩ tuyến của hình cầu(số đường càng nhiều thì hình càng mượt)
	//kinh tuyến nằm dọc còn vĩ tuyến nằm ngang
	//Lưu ý:phải chia hết cho 360
	int numberLongitude, numberLatitude;
	//giá trị dùng khi bo góc
	int numberLongitudeRound, numberLatitudeRound;
	//số độ tối đa được vẽ(360 là vẽ toàn bộ hình cầu,180 là vẽ 1 nửa hình cầu)
	int degreeLongitudeLimit, degreeLatitudeLimit;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	//giá trị id cho texture
	int idTexture;

	ConeAttribute();
	ConeAttribute(ConeAttribute *cone);
	ConeAttribute(ConeAttribute &cone);
	~ConeAttribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	};
	//hàm nhập thuộc tính
	void setCenterCone(float *array);
	void setCenterCone(point center);
	void insertColor(float red, float green, float blue, float alpha);
	//hàm lấy ra thuộc tính
	void getCenterCone(float *arrayOut);
	point getCenterCone();

};
#endif


