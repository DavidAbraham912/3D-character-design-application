#include "TriangleFanAttribute.h"

TriangleFanAttribute::TriangleFanAttribute() {
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	mShiness = 20.0f; id = 0;
	centerObject = { 0,0,0 };
	idTexture = -1;
}
TriangleFanAttribute::TriangleFanAttribute(TriangleFanAttribute *triaFan) {
	vertexArray = triaFan->vertexArray;
	normalVector = triaFan->normalVector;
	centerObject = triaFan->centerObject;
	colorR = triaFan->colorR;
	colorG = triaFan->colorG;
	colorB = triaFan->colorB;
	colorA = triaFan->colorA;
	mShiness = triaFan->mShiness;
	id = triaFan->id;
	idTexture = triaFan->idTexture;
}
TriangleFanAttribute::TriangleFanAttribute(TriangleFanAttribute &triaFan) {
	vertexArray = triaFan.vertexArray;
	normalVector = triaFan.normalVector;
	centerObject = triaFan.centerObject;
	colorR = triaFan.colorR;
	colorG = triaFan.colorG;
	colorB = triaFan.colorB;
	colorA = triaFan.colorA;
	mShiness = triaFan.mShiness;
	id = triaFan.id;
	idTexture = triaFan.idTexture;
}
void TriangleFanAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}