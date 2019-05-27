#include "TorusAttribute.h"

TorusAttribute::TorusAttribute(){
	centerObject = { 0,0,0 };
	radiusCake = 2.0f;
	radiusRoundCake = 1.0f;
	widthCake = 1.0f;
	depthCake=20;
	depthRoundCake = 40;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	mShiness = 20.0f; id = 0;
	idTexture = -1;
}
TorusAttribute::TorusAttribute(TorusAttribute *torus){
	centerObject = torus->centerObject;
	radiusCake = torus->radiusCake;
	radiusRoundCake = torus->radiusRoundCake;
	widthCake = torus->widthCake;
	depthCake = torus->depthCake;
	depthRoundCake = torus->depthRoundCake;
	vertexArray = torus->vertexArray;
	normalVector = torus->normalVector;
	vertexArrayRound = torus->vertexArrayRound;
	normalVectorRound = torus->normalVectorRound;
	colorR = torus->colorR;
	colorG = torus->colorG;
	colorB = torus->colorB;
	colorA = torus->colorA;
	mShiness = torus->mShiness;
	id = torus->id;
	idTexture = torus->idTexture;
}
TorusAttribute::TorusAttribute(TorusAttribute &torus){
	centerObject = torus.centerObject;
	radiusCake = torus.radiusCake;
	radiusRoundCake = torus.radiusRoundCake;
	widthCake = torus.widthCake;
	depthCake = torus.depthCake;
	depthRoundCake = torus.depthRoundCake;
	vertexArray = torus.vertexArray;
	normalVector = torus.normalVector;
	vertexArrayRound = torus.vertexArrayRound;
	normalVectorRound = torus.normalVectorRound;
	colorR = torus.colorR;
	colorG = torus.colorG;
	colorB = torus.colorB;
	colorA = torus.colorA;
	mShiness = torus.mShiness;
	id = torus.id;
	idTexture = torus.idTexture;
}

void TorusAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}