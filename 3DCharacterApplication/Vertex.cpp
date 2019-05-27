#include "Vertex.h"

//các hàm khởi tạo
Vertex::Vertex() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}
Vertex::Vertex(float insertX, float insertY, float insertZ) {
	x = insertX;
	y = insertY;
	z = insertZ;
}
Vertex::Vertex(Vertex *vertex) {
	x = vertex->x;
	y = vertex->y;
	z = vertex->z;
}
Vertex::Vertex(Vertex &vertex) {
	x = vertex.x;
	y = vertex.y;
	z = vertex.z;
}
void Vertex::setValue(float insertX, float insertY, float insertZ) {
	x = insertX;
	y = insertY;
	z = insertZ;
}
void Vertex::getValue(float *arrayValue) {
	arrayValue[0] = x;
	arrayValue[1] = y;
	arrayValue[2] = z;
}