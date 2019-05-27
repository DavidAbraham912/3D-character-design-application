#include "TriangleStripAttribute.h"

TriangleStripAttribute::TriangleStripAttribute(){
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	mShiness = 20.0f; id = 0;
	centerObject = { 0,0,0 };
	idTexture = -1;
}
TriangleStripAttribute::TriangleStripAttribute(TriangleStripAttribute *triaStri){
	vertexArray = triaStri->vertexArray;
	normalVector = triaStri->normalVector;
	vertexArrayRound = triaStri->vertexArrayRound;
	normalVectorRound = triaStri->normalVectorRound;
	centerObject = triaStri->centerObject;
	colorR = triaStri->colorR;
	colorG = triaStri->colorG;
	colorB = triaStri->colorB;
	colorA = triaStri->colorA;
	mShiness = triaStri->mShiness;
	id = triaStri->id;
	idTexture = triaStri->idTexture;
}
TriangleStripAttribute::TriangleStripAttribute(TriangleStripAttribute &triaStri) {
	vertexArray = triaStri.vertexArray;
	normalVector = triaStri.normalVector;
	vertexArrayRound = triaStri.vertexArrayRound;
	normalVectorRound = triaStri.normalVectorRound;
	centerObject = triaStri.centerObject;
	colorR = triaStri.colorR;
	colorG = triaStri.colorG;
	colorB = triaStri.colorB;
	colorA = triaStri.colorA;
	mShiness = triaStri.mShiness;
	id = triaStri.id;
	idTexture = triaStri.idTexture;
}
void TriangleStripAttribute::insertColor(float red, float green, float blue, float alpha){
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}