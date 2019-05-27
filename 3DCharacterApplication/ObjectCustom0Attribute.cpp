#include "ObjectCustom0Attribute.h"

ObjectCustom0Attribute::ObjectCustom0Attribute() {
	centerObject = { 0.0f,0.0f,0.0f };
	numberLatitude = 3;
	numberLongitude = 3;
	numberLatitudeRound = 3;
	numberLongitudeRound = 3;
	lengthBetween2Row = 1.0f;
	lengthBetween2Column = 1.0f;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 0.0f;
	mShiness = 20.0f;
	id = -1;
	idTexture = -1;
}

ObjectCustom0Attribute::ObjectCustom0Attribute(ObjectCustom0Attribute *object) {
	centerObject = object->centerObject;
	numberLatitude = object->numberLatitude;
	numberLongitude = object->numberLongitude;
	numberLatitudeRound = object->numberLatitudeRound;
	numberLongitudeRound = object->numberLongitudeRound;
	lengthBetween2Row = object->lengthBetween2Row;
	lengthBetween2Column = object->lengthBetween2Column;
	vertexArray = object->vertexArray;
	normalVector = object->normalVector;
	vertexArrayRound = object->vertexArrayRound;
	normalVectorRound = object->normalVectorRound;
	colorR = object->colorR;
	colorG = object->colorG;
	colorB = object->colorB;
	colorA = object->colorA;
	mShiness = object->mShiness;
	id = object->id;
	idTexture = object->idTexture;
}

ObjectCustom0Attribute::ObjectCustom0Attribute(ObjectCustom0Attribute &object) {
	centerObject = object.centerObject;
	numberLatitude = object.numberLatitude;
	numberLongitude = object.numberLongitude;
	numberLatitudeRound = object.numberLatitudeRound;
	numberLongitudeRound = object.numberLongitudeRound;
	lengthBetween2Row = object.lengthBetween2Row;
	lengthBetween2Column = object.lengthBetween2Column;
	vertexArray = object.vertexArray;
	normalVector = object.normalVector;
	vertexArrayRound = object.vertexArrayRound;
	normalVectorRound = object.normalVectorRound;
	colorR = object.colorR;
	colorG = object.colorG;
	colorB = object.colorB;
	colorA = object.colorA;
	mShiness = object.mShiness;
	id = object.id;
	idTexture = object.idTexture;
}
void ObjectCustom0Attribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}