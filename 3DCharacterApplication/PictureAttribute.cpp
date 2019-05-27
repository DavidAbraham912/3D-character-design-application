#include "PictureAttribute.h"

PictureAttribute::PictureAttribute() {
	centerObject = { 0.0f,0.0f,0.0f };
	id = -1;
	idTexture = 0;
}
PictureAttribute::PictureAttribute(PictureAttribute *picture) {
	centerObject = picture->centerObject;
	for (int i = 0; i < 4; i++) {
		vertexArray[i] = picture->vertexArray[i];
		normalVector[i] = picture->normalVector[i];
	}
	id = picture->id;
	idTexture = picture->idTexture;
}
PictureAttribute::PictureAttribute(PictureAttribute &picture) {
	centerObject = picture.centerObject;
	for (int i = 0; i < 4; i++) {
		vertexArray[i] = picture.vertexArray[i];
		normalVector[i] = picture.normalVector[i];
	}
	id = picture.id;
	idTexture = picture.idTexture;
}
