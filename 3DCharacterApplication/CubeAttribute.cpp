#include "CubeAttribute.h"

//các hàm khởi tạo
CubeAttribute::CubeAttribute() {
	numberVertexInAxisX = 2;
	numberVertexInAxisY = 2;
	numberVertexInAxisZ = 2;
	colorR = 1.0f; colorG = 1.0f; colorB = 1.0f; colorA = 1.0f;
	centerObject = { 0.0f,0.0f,0.0f };
	mShiness = 20.0f; id = 0;
	idTexture = -1;
}
CubeAttribute::CubeAttribute(CubeAttribute *cube) {
	colorR = cube->colorR;
	colorG = cube->colorG;
	colorB = cube->colorB;
	colorA = cube->colorA;
	centerObject = cube->centerObject;
	numberVertexInAxisX = cube->numberVertexInAxisX;
	numberVertexInAxisY = cube->numberVertexInAxisY;
	numberVertexInAxisZ = cube->numberVertexInAxisZ;
	vertexArray = cube->vertexArray;
	normalVector = cube->normalVector;
	vertexArrayRound = cube->vertexArrayRound;
	normalVectorRound = cube->normalVectorRound;
	mShiness = cube->mShiness;
	id = cube->id;
	idTexture = cube->idTexture;
}
CubeAttribute::CubeAttribute(CubeAttribute &cube) {
	colorR = cube.colorR;
	colorG = cube.colorG;
	colorB = cube.colorB;
	colorA = cube.colorA;
	centerObject = cube.centerObject;
	numberVertexInAxisX = cube.numberVertexInAxisX;
	numberVertexInAxisY = cube.numberVertexInAxisY;
	numberVertexInAxisZ = cube.numberVertexInAxisZ;
	vertexArray = cube.vertexArray;
	normalVector = cube.normalVector;
	vertexArrayRound = cube.vertexArrayRound;
	normalVectorRound = cube.normalVectorRound;
	mShiness = cube.mShiness;
	id = cube.id;
	idTexture = cube.idTexture;
}

void CubeAttribute::insertColor(float red, float green, float blue, float alpha) {
	colorR = red;
	colorG = green;
	colorB = blue;
	colorA = alpha;
}