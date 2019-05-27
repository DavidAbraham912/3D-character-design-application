#include "SphereAttribute.h"


SphereAttribute::SphereAttribute(){
	centerObject = { 0,0,0 };
	radius=1.0f;
	numberLongitude = 30;
	numberLatitude = 30;
	degreeLongitudeLimit = 360;
	degreeLatitudeLimit = 360;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	mShiness = 20.0f;
	id=-1;
	idTexture = -1;
}
SphereAttribute::SphereAttribute(SphereAttribute *sphere){
	vertexArray = sphere->vertexArray;
	normalVector = sphere->normalVector;
	vertexArrayRound = sphere->vertexArrayRound;
	normalVectorRound = sphere->normalVectorRound;
	numberLongitude = sphere->numberLongitude;
	numberLatitude = sphere->numberLatitude;
	numberLongitudeRound = sphere->numberLongitudeRound;
	numberLatitudeRound = sphere->numberLatitudeRound;
	degreeLongitudeLimit = sphere->degreeLongitudeLimit;
	degreeLatitudeLimit = sphere->degreeLatitudeLimit;
	centerObject = sphere->centerObject;
	radius = sphere->radius;
	colorR = sphere->colorR;
	colorG = sphere->colorG;
	colorB = sphere->colorB;
	colorA = sphere->colorA;
	mShiness = sphere->mShiness;
	id = sphere->id;
	idTexture = sphere->idTexture;
}
SphereAttribute::SphereAttribute(SphereAttribute &sphere){
	vertexArray = sphere.vertexArray;
	normalVector = sphere.normalVector;
	vertexArrayRound = sphere.vertexArrayRound;
	normalVectorRound = sphere.normalVectorRound;
	numberLongitude = sphere.numberLongitude;
	numberLatitude = sphere.numberLatitude;
	numberLongitudeRound = sphere.numberLongitudeRound;
	numberLatitudeRound = sphere.numberLatitudeRound;
	degreeLongitudeLimit = sphere.degreeLongitudeLimit;
	degreeLatitudeLimit = sphere.degreeLatitudeLimit;
	centerObject = sphere.centerObject;
	radius = sphere.radius;
	colorR = sphere.colorR;
	colorG = sphere.colorG;
	colorB = sphere.colorB;
	colorA = sphere.colorA;
	mShiness = sphere.mShiness;
	id = sphere.id;
	idTexture = sphere.idTexture;
}

//các hàm đặt giá trị
void SphereAttribute::setCenterSphere(float x, float y, float z) {
	centerObject.x = x;
	centerObject.y = y;
	centerObject.z = z;
}
void SphereAttribute::setRadius(float insertRadius) {
	radius = insertRadius;
}
void SphereAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}
//các hàm lấy giá trị
void SphereAttribute::getCenterSphere(float *arrayOut) {
	arrayOut[0] = centerObject.x;
	arrayOut[1] = centerObject.y;
	arrayOut[2] = centerObject.z;
}
point SphereAttribute::getCenterSphere() {
	return centerObject;
}