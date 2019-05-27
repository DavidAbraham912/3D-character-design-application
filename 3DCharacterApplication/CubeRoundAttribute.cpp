#include "CubeRoundAttribute.h"

CubeRoundAttribute::CubeRoundAttribute() {
	centerObject = { 0,0,0 };
	numberLongitude = 30;
	numberLatitude = 30;
	radiusRound = 0.1f;
	xLength = 2.0f;
	yLength = 2.0f;
	zLength = 2.0f;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	mShiness = 20.0f;
	id = -1;
	idTexture = -1;
}
CubeRoundAttribute::CubeRoundAttribute(CubeRoundAttribute *cube) {
	vertexArray = cube->vertexArray;
	normalVector = cube->normalVector;
	vertexArrayRound = cube->vertexArrayRound;
	normalVectorRound = cube->normalVectorRound;
	numberLongitude = cube->numberLongitude;
	numberLatitude = cube->numberLatitude;
	radiusRound = cube->radiusRound;
	xLength = cube->xLength;
	yLength = cube->yLength;
	zLength = cube->zLength;
	centerObject = cube->centerObject;
	colorR = cube->colorR;
	colorG = cube->colorG;
	colorB = cube->colorB;
	colorA = cube->colorA;
	mShiness = cube->mShiness;
	id = cube->id;
	idTexture = cube->idTexture;
}
CubeRoundAttribute::CubeRoundAttribute(CubeRoundAttribute &cube) {
	vertexArray = cube.vertexArray;
	normalVector = cube.normalVector;
	vertexArrayRound = cube.vertexArrayRound;
	normalVectorRound = cube.normalVectorRound;
	numberLongitude = cube.numberLongitude;
	numberLatitude = cube.numberLatitude;
	radiusRound = cube.radiusRound;
	xLength = cube.xLength;
	yLength = cube.yLength;
	zLength = cube.zLength;
	centerObject = cube.centerObject;
	colorR = cube.colorR;
	colorG = cube.colorG;
	colorB = cube.colorB;
	colorA = cube.colorA;
	mShiness = cube.mShiness;
	id = cube.id;
	idTexture = cube.idTexture;
}
void CubeRoundAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}