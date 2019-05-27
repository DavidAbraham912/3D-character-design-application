#include "EmptyCylinderAttribute.h"

EmptyCylinderAttribute::EmptyCylinderAttribute(){
	centerObject = { 0.0f,0.0f,0.0f };
	height = 4.0f;
	radiusUpOut = 1.0f;
	radiusDownOut = 1.0f;
	radiusUpIn = 0.2f;
	radiusDownIn = 0.2f;
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
EmptyCylinderAttribute::EmptyCylinderAttribute(EmptyCylinderAttribute *cylinder){
	centerObject = cylinder->centerObject;
	radiusUpOut = cylinder->radiusUpOut;
	radiusDownOut = cylinder->radiusDownOut;
	radiusUpIn = cylinder->radiusUpIn;
	radiusDownIn = cylinder->radiusDownIn;
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
EmptyCylinderAttribute::EmptyCylinderAttribute(EmptyCylinderAttribute &cylinder){
	centerObject = cylinder.centerObject;
	radiusUpOut = cylinder.radiusUpOut;
	radiusDownOut = cylinder.radiusDownOut;
	radiusUpIn = cylinder.radiusUpIn;
	radiusDownIn = cylinder.radiusDownIn;
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
void EmptyCylinderAttribute::insertColor(float red, float green, float blue, float alpha){
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}