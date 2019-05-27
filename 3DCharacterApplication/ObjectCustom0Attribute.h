#ifndef ObjectCustom0Attribute_H
#define ObjectCustom0Attribute_H
#include "Point.h"
#include <vector>
using namespace std;

class ObjectCustom0Attribute
{
public:
	//tâm và đỉnh của hình tròn ở đáy
	point centerObject;
	//tương tự như numberLongitude và numberLatitude của sphere,cone,...
	int numberLongitude, numberLatitude, numberLongitudeRound, numberLatitudeRound;
	//khoảng cách giữa 2 row,khoảng cách giữa 2 column
	float lengthBetween2Row, lengthBetween2Column;
	vector<point> vertexArray;
	vector<point> normalVector;
	//vector và normal dùng khi vẽ hình bo góc
	std::vector<point> vertexArrayRound;
	std::vector<point> normalVectorRound;
	
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	//giá trị id cho texture
	int idTexture;

	ObjectCustom0Attribute();
	ObjectCustom0Attribute(ObjectCustom0Attribute *object);
	ObjectCustom0Attribute(ObjectCustom0Attribute &cone);
	~ObjectCustom0Attribute() {
		vertexArray.clear();
		normalVector.clear();
		vertexArrayRound.clear();
		normalVectorRound.clear();
	};
	void insertColor(float red, float green, float blue, float alpha);

};
#endif
