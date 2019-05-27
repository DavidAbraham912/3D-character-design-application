#ifndef SphereAttribute_H
#define SphereAttribute_H
#include <vector>
#include "Point.h"
using namespace std;

class SphereAttribute
{
public:
	//có tổng cộng 8 vertexArray dùng cho 8 mặt của hình cầu

	//tọa độ tâm hình cầu
	point centerObject;
	vector<point> vertexArray;
	//normal vector
	vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	//số đường kinh tuyến và vĩ tuyến của hình cầu(số đường càng nhiều thì hình càng mượt)
	//kinh tuyến nằm dọc còn vĩ tuyến nằm ngang
	int numberLongitude, numberLatitude;
	//giá trị dùng khi bo góc
	int numberLongitudeRound, numberLatitudeRound;
	//số độ tối đa được vẽ(360 là vẽ toàn bộ hình cầu,180 là vẽ 1 nửa hình cầu)
	int degreeLongitudeLimit, degreeLatitudeLimit;
	//bán kính hình cầu
	float radius;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;

	SphereAttribute();
	SphereAttribute(SphereAttribute *sphere);
	SphereAttribute(SphereAttribute &sphere);
	~SphereAttribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	}
	//các hàm đặt giá trị
	void setCenterSphere(float x, float y, float z);
	void setRadius(float insertRadius);
	void insertColor(float red, float green, float blue, float alpha);
	//các hàm lấy giá trị
	void getCenterSphere(float *arrayOut);
	point getCenterSphere();


};

#endif
