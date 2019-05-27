#ifndef CubeRoundAttribute_H
#define CubeRoundAttribute_H
#include <vector>
#include "Point.h"
using namespace std;

class CubeRoundAttribute
{
public:
	//tọa độ tâm hình chữ nhật bo tròn
	point centerObject;
	vector<point> vertexArray;
	//normal vector
	vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	//số đường kinh tuyến và vĩ tuyến của hình cầu(số đường càng nhiều thì hình càng mượt)
	//kinh tuyến nằm dọc còn vĩ tuyến nằm ngang
	//đối với hình chữ nhật bo tròn thì các đường kinh tuyến hay vĩ tuyến đều phải là số chẵn
	int numberLongitude, numberLatitude;
	//bán kính bo góc
	float radiusRound;
	//chiều rộng,chiều cao và chiều dài của hình hộp bo tròn(bữa sau tính phải trừ đi phần bo góc rồi mới thêm vào)
	//giá trị tổng của 2 phần bo góc đối diện phải nhỏ hơn hoặc bằng chiều dài mặt đó(nếu không hình sẽ không đẹp)
	float xLength, yLength, zLength;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;


	CubeRoundAttribute();
	CubeRoundAttribute(CubeRoundAttribute *cube);
	CubeRoundAttribute(CubeRoundAttribute &cube);
	~CubeRoundAttribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	}
	void insertColor(float red, float green, float blue, float alpha);
};

#endif
