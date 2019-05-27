#include "CylinderAttribute.h"

CylinderAttribute::CylinderAttribute(){
	centerObject = { 0.0f,0.0f,0.0f };
	height = 4.0f;
	radiusUp = 1.0f;
	radiusDown = 1.0f;
	//số đường kinh tuyến này phải chia hết cho 360(nếu k0 sẽ hở hình)
	numberLongitude = 40;
	numberLatitude = 4;
	degreeLongitudeLimit = 360;
	degreeLatitudeLimit = 360;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 0.0f;
	mShiness = 20.0f;
	id = -1;
	idTexture = -1;
}
CylinderAttribute::CylinderAttribute(CylinderAttribute *cylinder){
	centerObject = cylinder->centerObject;
	radiusUp = cylinder->radiusUp;
	radiusDown = cylinder->radiusDown;
	height = cylinder->height;
	numberLongitude = cylinder->numberLongitude;
	numberLatitude = cylinder->numberLatitude;
	numberLongitudeRound = cylinder->numberLongitudeRound;
	numberLatitudeRound = cylinder->numberLatitudeRound;
	degreeLongitudeLimit = cylinder->degreeLongitudeLimit;
	degreeLatitudeLimit = cylinder->degreeLatitudeLimit;
	vertexArray = cylinder->vertexArray;
	normalVector = cylinder->normalVector;
	vertexArrayRound = cylinder->vertexArrayRound;
	normalVectorRound = cylinder->normalVectorRound;
	colorR = cylinder->colorR;
	colorG = cylinder->colorG;
	colorB = cylinder->colorB;
	colorA = cylinder->colorA;
	mShiness = cylinder->mShiness;
	id = cylinder->id;
	idTexture = cylinder->idTexture;
}
CylinderAttribute::CylinderAttribute(CylinderAttribute &cylinder){
	centerObject = cylinder.centerObject;
	radiusUp = cylinder.radiusUp;
	radiusDown = cylinder.radiusDown;
	height = cylinder.height;
	numberLongitude = cylinder.numberLongitude;
	numberLatitude = cylinder.numberLatitude;
	degreeLongitudeLimit = cylinder.degreeLongitudeLimit;
	degreeLatitudeLimit = cylinder.degreeLatitudeLimit;
	vertexArray = cylinder.vertexArray;
	normalVector = cylinder.normalVector;
	vertexArrayRound = cylinder.vertexArrayRound;
	normalVectorRound = cylinder.normalVectorRound;
	colorR = cylinder.colorR;
	colorG = cylinder.colorG;
	colorB = cylinder.colorB;
	colorA = cylinder.colorA;
	mShiness = cylinder.mShiness;
	id = cylinder.id;
	idTexture = cylinder.idTexture;
}
//hàm nhập thuộc tính
void CylinderAttribute::insertColor(float red, float green, float blue, float alpha){
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}