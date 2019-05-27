#include "ConeAttribute.h"

//các hàm khởi tạo
ConeAttribute::ConeAttribute() {
	centerObject = { 0.0f,0.0f,0.0f };
	height = 1.0f;
	radius = 1.0f;
	//số đường kinh tuyến này phải chia hết cho 360(nếu k0 sẽ hở hình)
	numberLongitude = 30;
	numberLatitude = 3;
	degreeLongitudeLimit = 360;
	degreeLatitudeLimit = 360;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 0.0f;
	mShiness = 20.0f;
	id = -1;
	idTexture = -1;
}
ConeAttribute::ConeAttribute(ConeAttribute *cone) {
	centerObject = cone->centerObject;
	radius = cone->radius;
	height = cone->height;
	vertexArray = cone->vertexArray;
	normalVector = cone->normalVector;
	vertexArrayRound = cone->vertexArrayRound;
	normalVectorRound = cone->normalVectorRound;
	numberLongitude = cone->numberLongitude;
	numberLatitude = cone->numberLatitude;
	numberLongitudeRound = cone->numberLongitudeRound;
	numberLatitudeRound = cone->numberLatitudeRound;
	degreeLongitudeLimit = cone->degreeLongitudeLimit;
	degreeLatitudeLimit = cone->degreeLatitudeLimit;
	colorR = cone->colorR;
	colorG = cone->colorG;
	colorB = cone->colorB;
	colorA = cone->colorA;
	mShiness = cone->mShiness;
	id = cone->id;
	idTexture = cone->idTexture;
}
ConeAttribute::ConeAttribute(ConeAttribute &cone) {
	centerObject = cone.centerObject;
	radius = cone.radius;
	height = cone.height;
	vertexArray = cone.vertexArray;
	normalVector = cone.normalVector;
	vertexArrayRound = cone.vertexArrayRound;
	normalVectorRound = cone.normalVectorRound;
	numberLongitude = cone.numberLongitude;
	numberLatitude = cone.numberLatitude;
	degreeLongitudeLimit = cone.degreeLongitudeLimit;
	degreeLatitudeLimit = cone.degreeLatitudeLimit;
	colorR = cone.colorR;
	colorG = cone.colorG;
	colorB = cone.colorB;
	colorA = cone.colorA;
	mShiness = cone.mShiness;
	id = cone.id;
	idTexture = cone.idTexture;
}
//hàm nhập thuộc tính
void ConeAttribute::setCenterCone(float *array) {
	centerObject.x = array[0];
	centerObject.y = array[1];
	centerObject.z = array[2];
}
void ConeAttribute::setCenterCone(point center) {
	centerObject = center;
}
void ConeAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}
//hàm lấy ra thuộc tính
void ConeAttribute::getCenterCone(float *arrayOut) {
	arrayOut[0] = centerObject.x;
	arrayOut[1] = centerObject.y;
	arrayOut[2] = centerObject.z;
}
point ConeAttribute::getCenterCone() {
	return centerObject;
}