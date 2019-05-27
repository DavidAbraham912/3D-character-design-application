#ifndef PictureAttribute_H
#define PictureAttribute_H
#include "Point.h"
#include <vector>
using namespace std;

class PictureAttribute
{
public:
	//tâm hình ảnh
	point centerObject;
	point vertexArray[4];
	//normal vector
	point normalVector[4];
	int id;
	//giá trị id cho texture
	int idTexture;

	PictureAttribute();
	PictureAttribute(PictureAttribute *picture);
	PictureAttribute(PictureAttribute &picture);
	~PictureAttribute() {
	};
};
#endif
