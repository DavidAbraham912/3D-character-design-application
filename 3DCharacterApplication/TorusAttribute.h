#ifndef TorusAttribute_H
#define TorusAttribute_H
#include "Point.h"
#include <vector>
class TorusAttribute {
public:
	//tâm của torus
	point centerObject;
	//bán kính bánh
	float radiusCake;
	//bán kính vòng bánh
	float radiusRoundCake;
	//chiều rộng của bánh
	float widthCake;
	//độ mượt của bánh và vòng bánh(360 là mượt nhất)
	int depthCake;
	int depthRoundCake;
	//các vertex và normal vector cho từng vertex
	std::vector<point> vertexArray;
	std::vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;

	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;


	TorusAttribute();
	~TorusAttribute(){
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	}
	TorusAttribute(TorusAttribute *torus);
	TorusAttribute(TorusAttribute &torus);

	void insertColor(float red, float green, float blue, float alpha);

};

#endif
