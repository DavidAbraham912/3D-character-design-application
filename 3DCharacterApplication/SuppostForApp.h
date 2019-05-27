#ifndef SuppostForApp_H
#define SuppostForApp_H
#include <iostream>
#include <string>
#include <freeglut.h>
#include "TriangleAttribute.h"
#include "TriangleStripAttribute.h"
#include "TriangleFanAttribute.h"
#include "CubeAttribute.h"
#include "SphereAttribute.h"
#include "ConeAttribute.h"
#include "CylinderAttribute.h"
#include "PyramidAttribute.h"
#include "EmptyCylinderAttribute.h"
#include "TorusAttribute.h"
#include "CubeRoundAttribute.h"
#include "PictureAttribute.h"
#include "ObjectCustom0Attribute.h"
#include "Point.h"
#include "vector.h"
#include "Quaternion.h"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


//hàm sắp xếp mảng vector tho thứ tự từ nhỏ đến lớn
//tạm thời đang dùng thuật toán sắp xếp chậm,bữa sau sẽ viết thuật toán quicksort
void ArrangeOrderFromSmallToLarge(vector<int> &arrayIn);
//sắp xếp từ lớn đến nhỏ
void ArrangeOrderFromLargeToSmall(vector<int> &arrayIn);
//sắp xếp từ lớn đến nhỏ dành cho itemsChoice
//nếu cùng 1 kiều phần tử thì các phần tử có vị trí lớn hơn trong mảng sẽ đứng trước
void ArrangeOrderFromSmallToLarge(vector<itemChoice> &itemsChoice);

//hàm đảo ngược thứ tự của các item trong mảng vector
void reverseItemInVector(vector<int> &vertexArray);
void reverseItemInVector(vector<PositionRowOrColumn> &vertexArray);
//hàm lấy id để đặt cho vật
int getIdForObject(vector<int> &idsUsing);
//tính toán mặt phẳng cắt
bool caculatorPlane(GLdouble *v1, GLdouble *v2, GLdouble *v3, GLdouble *plane);
bool caculatorPlane(point v1, point v2, point v3, GLdouble *plane);
bool caculatorPlane(point v1, point v2, point v3, float *plane);

//các hàm tính toán normal vector
//bình thường hóa normal vector
void normalize(float v[3]);
void normalize(point &v);
//hàm tính toán normal vector của tam giác từ 3 đỉnh thuộc tam giác
bool normcrossprod(float v1[3], float v2[3], float v3[3], float out[3]);
bool normcrossprod(point v1, point v2, point v3, point &out);
//tìm khoảng cách giuwac 2 điểm
float distanceTwoPoint(point a, point b);

//hàm vẽ bitmap
//vẽ chữ với kiểu chữ lớn mặc định
void drawText(GLuint x, GLuint y, char* format);
//vẽ với kiểu chữ tùy chỉnh
void drawText(GLuint x, GLuint y, char* format, char* name, int size);

//các hàm vẽ hình
void DrawTriangles(GLenum mode, vector<TriangleAttribute*> triangleArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawTriangleStrip(GLenum mode, vector<TriangleStripAttribute*> triaStripArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawTriangleFan(GLenum mode, vector<TriangleFanAttribute*> triaFanArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawSphere(GLenum mode, vector<SphereAttribute*> sphereArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawCube(GLenum mode, vector<CubeAttribute*> cubeArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawCubeRound(GLenum mode, vector<CubeRoundAttribute*> cubeRoundArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawCone(GLenum mode, vector<ConeAttribute*> coneArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawCylinder(GLenum mode, vector<CylinderAttribute*> cylinderArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawPyramid(GLenum mode, vector<PyramidAttribute*> pyrArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawEmptyCylinder(GLenum mode, vector<EmptyCylinderAttribute*> emptyCylinderArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawTorus(GLenum mode, vector<TorusAttribute*> torusArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawPictures(GLenum mode, vector<PictureAttribute*> pictureArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice);
void DrawObjectCustom0(GLenum mode, vector<ObjectCustom0Attribute*> cylinderArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice);

//hàm chuyển mảng char sang số
float getFloatFromCharArray(char* charArray);
int getIntFromCharArray(char* charArray);
//Hàm chuyển số sang mảng char với charArray[10](cho chắc ăn,k0 bị thiếu bộ nhớ)
void changeNumberIntToCharArray(char* charArray, int number);
void changeNumberIntToVertexCharArray(char* charArray, int number);
void changeNumberFloatToCharArray(char* charArray, float number);
//vẽ mũi tên chỉ hướng 2D cho khung hình
void drawArrow(double *projectMatrixArrow, double *modelMatrixArrow);
//vẽ các hình vuông để các giá trị theo cả 2 hướng(zy,yx hay xz)
void drawQuadForObject(point center, float arrowSize, int startLoadName);
//vẽ các mũi tên chỉ hướng 3D cho vật
void drawArrowForObject(float x, float y, float z , float arrowSize,
	bool isCube, int changeRotateFor2D, int startLoadName);
//vẽ 1 mũi tên chỉ hướng,dùng cho điều chỉnh thuộc tính của vật
void drawOneArrowForObject(float x, float y, float z, int whichDirection, int loadName);
//vẽ hình tròn dùng cho thao tác xoay vật cũng như các thao tác liên quan đến đường tròn
//chỉ vẽ để hiển thị
void drawCircleForRotate(int whichAxis, float radius, point centerCircle, int firstItemChoice, int lastItemChoice, bool isMoveLikeClockwise);
//hàm kiểm tra xem chuột nằm gần điểm nào của đường tròng xoay
void getPositionForRotate(int x, int y, float radiusCircle,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport, itemRotateObject &itemRotate, point centerObjectOrVertices);

//vẽ đường lưới ở mặt đất
void drawNet();

//các hàm dùng cho tính bo tròn hình cầu
// trả về một điểm trùng với A và B, một khoảng cách nhất định từ A.(3D)
void normalizeWithRadius(float *a, float *b, float length);
void normalizeWithRadius(point a, point &b, float length);
void normalizeWithRadius(point a, point b, point &out, float length);
//trả về một điểm nằm trên A,B,cách một khoảng cách nhất định từ A.(2D)
void normalizeWithRadius2D(double *a, double *b, float length);
void normalizeWithRadius2D(float *a, float *b, float *c, float length);
void normalizeWithRadius2D(point a, point &b, float length);
void normalizeWithRadius2D(point a, point b, point &out, float length);

//tìm các điểm nằm giữa 2 điểm
void findPointsBetweenTwoPoint(point first, point last, int numberElement, point *arrayOut);
//hàm này khác hàm trên là có vị trí bắt đầu đầu tiên trong mảng chứ không phải chỉ bắt đầu từ 0
void findPointsBetweenTwoPoint(point first, point last, int numberElement, point *arrayOut, int offsetArrayOut);

void CaculatorSphere(int radius, int numberLongitude, int numberLatitude, point centerSphere, std::vector<point> &vertexArray);
void CaculatorCubeRound(float xLength, float yLength, float zLength, int numberLongitude, int numberLatitude, point centerSphere,
	float radiusRound,std::vector<point> &vertexArray);
//tính toán và hiển thị cho cone lần đầu
void caculatorCone(point centerCone, float radius, float height, int numberLongitude, int &numberLatitude,
	std::vector<point> &vertexArray);
//tính toán và hiển thị cho cylinder lần đầu
void caculatorCylinder(point centerCylinder, float radiusUp, float radiusDown, float height,
	int numberLongitude, int &numberLatitude, std::vector<point> &vertexArray);
//tính toán và hiển thị cho cylinder2 lần đầu
void caculatorEmptyCylinder(point centerCylinder, float radiusUpOut, float radiusDownOut, float radiusUpIn, float radiusDownIn,
	float height, int numberLongitude, int &numberLatitude, std::vector<point> &vertexArray);
void caculatorTorus(float radiusCake, float radiusRoundCake, float widthCake, int depthCake, int depthRoundCake, point centerTorus,
	vector<point> &vertexArray);
void caculatorObjectCustom0(int numberLongitude, int numberLatitude, float lengthBetween2Row, float lengthBetween2Column,
	point centerObject, vector<point> &vertexArray);

//hàm kiểm tra xem 3 điểm có nằm trên cùng 1 đường thẳng không
bool checkIs3PointsInLine(point *v);
bool checkIs3PointsInLine(point v0, point v1, point v2);
//các hàm tính toán normal vector cho hình
void CaculatorNormalForTriangles(point *vertexArray, point &vectorNormal);
void CaculatorNormalForTriangleStrip(vector<point> vertexArray, vector<point> &vectorNormal);
void CaculatorNormalForTriangleFan(vector<point> vertexArray, vector<point> &vectorNormal);
void CaculatorNormalForSphere(int numberLongitude, int numberLatitude, vector<point> &vertexArray, vector<point> &normalVector);
void CaculatorNormalForCubeRound(int numberLongitude, int numberLatitude, vector<point> &vertexArray, vector<point> &normalVector);
void CaculatorNormalForCube(int numberVertexInAxisX, int numberVertexInAxisY, int numberVertexInAxisZ,
	vector<point> vertexArray, vector<point> &vectorNormal);
void CaculatorNormalForCone(int numberLongitude, int numberLatitude, vector<point> vertexArray, vector<point> &normalVector);
void CaculatorNormalForCylinder(int numberLongitude, int numberLatitude, vector<point> vertexArray, vector<point> &normalVector);
void CaculatorNormalForPyramid(point *vertexArray, point *normalVector);
void CaculatorNormalForEmptyCylinder(int numberLongitude, int numberLatitude,
	vector<point> vertexArray, vector<point> &normalVector);
void CaculatorNormalForTorus(int depthRound, vector<point> vertexArray, vector<point> &normalVector);
void CaculatorNormalForPictures(point *vertexArray, point *vectorNormal);
void CaculatorNormalForObjectCustom0(int numberLongitude, int numberLatitude,
	vector<point> vertexArray, vector<point> &normalVector);

//tìm điểm chính giữa mảng vertex
point getPointCenterVertexes(vector<point> vertexArray);
point getPointCenterVertexes(point *vertexArray, int numberVertex);

//tỉm điểm chính giữa mảng các vertex được chỉ định vị trí
point getPointCenterVertexesAtPosition(vector<point> vertexArray, vector<int> position);
point getPointCenterVertexesAtPosition(point *vertexArray, vector<int> position);

//hàm lấy điểm chính giữa của các vertex đối xứng của mảng các vertex được chọn
point getPointCenterVertexesSymmetryAtPosition(vector<point> vertexArray, vector<int> position,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
point getPointCenterVertexesSymmetryAtPosition(point *vertexArray, vector<int> position,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);

//hàm rotate Vertex
//vectorArray là 1 vector
void CaculatorRotateVertex(vector<point> &vertexArray, point centerOrigin, float deg, int axis);
//vectorArray là 1 mảng các điểm (point)
void CaculatorRotateVertex(point *vertexArray, int numberVertex, point centerOrigin, float deg, int axis);
//nhập vào là 1 vertex riêng lẻ
void CaculatorRotateVertex(point &vertexArray, point centerOrigin, float deg, int axis);
//hàm scale vertex
//mảng nhập vào là vector
void CaculatorScaleVertex(vector<point> &vertexArray, point centerOrigin, float scaleX, float scaleY, float scaleZ);
//mảng nhập vào là 1 mảng vertex
void CaculatorScaleVertex(point *vertexArray, int numberVertex, point centerOrigin, float scaleX, float scaleY, float scaleZ);
//nhập vào là 1 vertex lẻ
void CaculatorScaleVertex(point &vertex, point centerOrigin, float scaleX, float scaleY, float scaleZ);

//hàm dịch chuyển hình
void moveObject(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<itemChoice> itemsChoice,
	point &centerObjectOrVertices,
	vector<SymmetryObjects> symmetryObjects,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm dich chuyển chỉ duy nhất vertex choice
void moveVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point *vertexArray);
void moveVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, vector<point> &vertexArray);

//hàm dịch chuyển vertex chọn và vertex nghịch đảo
void moveVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point *vertexArray,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
void moveVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, vector<point> &vertexArray,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
//hàm dịch chuyển vertex
void moveVertex(float valuePlusX, float valuePlusY, float valuePlusZ,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, vector<int> positionVerticesChoice,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm dịch chuyển hình cũng như vertex(tùy chế độ đang chọn)
void moveShape(float valuePlus1, float valuePlus2, float valuePlus3,
	int modelEditStyle, int whichArrowChoice, int whichQuadChoice,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, vector<int> positionVerticesChoice,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm xoay vật được chọn
void rotateObject(float deg, int axis, vector<itemChoice> itemsChoice,
	vector<SymmetryObjects> symmetryObjects,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm xoay vật được chọn
void rotateObject(float rotateX, float rotateY, float rotateZ, vector<itemChoice> itemsChoice,
	vector<SymmetryObjects> symmetryObjects,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm chỉ xoay vertex đang được chọn
void rotateVertexChoice(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray);
void rotateVertexChoice(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray);
void rotateVertexChoice(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray);
void rotateVertexChoice(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray);

//hàm xoay vertex chọn và vertex nghịch đảo
void rotateVertexChoiceAndSymmetry(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
void rotateVertexChoiceAndSymmetry(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
void rotateVertexChoiceAndSymmetry(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
void rotateVertexChoiceAndSymmetry(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
//rotate vertexs in object
void rotateVertex(int deg, int axis,
	vector<itemChoice> itemsChoice, vector<int> positionVerticesChoice,
	point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//rotate vertexs in object
void rotateVertex(float rotateX, float rotateY, float rotateZ,
	vector<itemChoice> itemsChoice, vector<int> positionVerticesChoice,
	point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm xoay các vật hay vertex được chọn
void rotateShape(float deg, int axis,point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, int modelEditStyle, vector<int> positionVerticesChoice,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//chỉnh sửa các thuộc tính của vật
void EditAttribute(float plus,
	vector<itemChoice> itemsChoice, int whichArrowChoice,
	vector<SphereAttribute*> &sphereArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray);
//chỉnh sửa các thuộc tính liên quan đến góc độ
void EditAttributeAboutDeg(int plusDegree,
	itemRotateObject itemRotate, vector<itemChoice> itemsChoice,
	vector<SphereAttribute*> &sphereArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray);

//hàm scale vật
void scaleObject(float valuePlusX, float valuePlusY, float valuePlusZ, vector<itemChoice> itemsChoice,
	vector<SymmetryObjects> symmetryObjects,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm scale chỉ các vertex đang chọn
void scaleVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray);
void scaleVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray);

//hàm scale vertex chọn và vertex nghịch đảo
void scaleVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
void scaleVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2);
//scale vertexs in object(đối với scale,rotate,move vertex thì ta phải tính lại center object)
void scaleVertex(float valuePlusX, float valuePlusY, float valuePlusZ, vector<itemChoice> itemsChoice,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm scale vật hay vertex ở chế độ scale
void scaleShape(float valuePlus, int modelEditStyle, vector<itemChoice> itemsChoice,
	point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<int> positionVerticesChoice,
	int whichArrowChoice, int whichQuadChoice,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);


//tính toán giá trị tăng lên khi dịch chuyển cho mũi tên
bool caculatorPlusArrow(point &center, int whichArrow, int xNow, int yNow,
	float &valuePlus, double *modelMatrix, double *projectMatrix, int *viewport);
//tính toán giá trị tăng lên khi dịch chuyển cho quad
//đây là cách tính để dịch chuyển,nó có 2 giá trị tăng
bool caculatorPlusQuad(point &center, int whichQuad, int xNow, int yNow,
	float &valuePlus1, float &valuePlus2, double *modelMatrix, double *projectMatrix, int *viewport);
//đây là cách tính để scale,nó chỉ tính 1 giá trị tăng
bool caculatorPlusQuad(point &center, int whichQuad, int xNow, int yNow,
	float &valuePlus, double *modelMatrix, double *projectMatrix, int *viewport);
//đây là cách tính khi có 3 giá trị tăng
//nó sẽ dùng độ sâu lấy từ vị trí chuột và x,y của màn hình(nếu độ sâu =1.0 là vô cực thì không xác
//định nên sẽ không di chuyển)
bool caculatorPlusQuad(point center, point &firstTouch, int x, int y, float &valuePlusX, float &valuePlusY, float &valuePlusZ,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport);

//hàm nghịch đảo vertex thông qua trục
//đối xứng qua trục X
void inverseVertexesX(vector<point> &vertexArray, float valueInAxisX);
void inverseVertexesX(point *vertexArray, int numberVertex, float valueInAxisX);
//đối xứng qua trục Y
void inverseVertexesY(vector<point> &vertexArray, float valueInAxisY);
void inverseVertexesY(point *vertexArray, int numberVertex, float valueInAxisY);
//đối xứng qua trục Z
void inverseVertexesZ(vector<point> &vertexArray, float valueInAxisZ);
void inverseVertexesZ(point *vertexArray, int numberVertex, float valueInAxisZ);
//hàm nghịc đảo các vertex dành riêng cho các hình
//hàm này dùng cho các hình bao vòng (có numberLongitude và numberLagitude như sphere)
void inverseCylinder_Sphere_Cone(int axis,
	int numberLongitude, int numberLagitude, vector<point> &vertexArray, point center);
//hàm này dùng riêng cho cube
void inverseCube(int axis,
	int numberVertexInAxisX, int numberVertexInAxisY, int numberVertexInAxisZ, vector<point> &vertexArray, point center);
//hàm này dùng riêng cho torus
void inverseTorus(int axis,
	int depthRound, vector<point> &vertexArray, point center);

//lấy các ma trận modelview
void getModelMatrix(double *modelMatrix, double *modelMatrixArrow,
	float translateX, float translateY, float translateZ,
	float zoomObject, float rotateX, float rotateY, int modelSpace);
//chỉ lấy duy nhất ma trận model matrix
void getModelMatrixOnly(double *modelMatrix, float translateX, float translateY,
	float zoomObject, float rotateX, float rotateY, int modelSpace);

//hàm lấy các ma trận chiếu cho project
void getMatrixForProjection(int modelSpace, int w, int h,
	GLdouble *projectMatrix, GLdouble *projectMatrixArrow);
//hàm lấy duy nhất ma trận chiếu
void getMatrixForProjectionOnly(int modelSpace, int w, int h, GLdouble *projectMatrix);

void getCenterObjectChoice(itemChoice item,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray, 
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//lấy tâm vertex cho việc xoay các vertex được chọn,vertex đối xứng và object đối xứng
void getCenterVertexsForScale(itemChoice item, vector<int> positionVerticesChoice,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//xóa các điểm chọn giống nhau trong chế độ chọn cộng dồn(mouseModel=1)
void clearSamePoints(vector<int> &vertexArrayChoice);
//xóa các itemChoice trùng nhau
void clearSameItemsChoice(vector<itemChoice> &itemsChoice);
//xóa các PositionRowOrColumn
void clearSamePositionRowOrColumn(vector<PositionRowOrColumn> &positionRowOrColumn);
//kiểm tra xem có phần tư nào trong mảng được chọn nằm sau phần tử vừa xóa(cùng kiểu phần tử) k0
//nếu có thì lùi giá trị của vị trí 1 đơn vị
void checkHaveAnyElementBehindElementDelete(vector<itemChoice> &itemsChoice, itemChoice item, int positionItem);
void deleteVertexChoice(itemChoice item, vector<int> &positionVerticesChoice,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray);
void deleteModelChoice(vector<itemChoice> &itemsChoice, vector<int> &positionVerticesChoice,
	int modelEditStyle, vector<int> &idsUsing,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
void setColorForModelChoice(vector<itemChoice> itemsChoice, float *colorDefaul,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm này xóa các vật đang vẽ hiện tại mà chưa vẽ xong
bool clearLastDrawNotDone(int lastDraw, vector<int> &idsUsing,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray);
//hàm này xóa đi vertex cuối cùng của các hình vẽ bằng vertex
void clearLastVertexDraw(itemChoice item,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray);
//hàm dichjc huyển vertex cuối cùng của hình đang vẽ dở(hình sau cùng)
void moveLastVertexDraw(itemChoice item, float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<TriangleAttribute*> &triangleArray,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray);

//hàm tính góc từ 3 điểm
float CaculatorDegreesFrom3Point(point v0, point v1, point v2);

//hàm nhắc nhở vị trí cho vertex hay hình đang dịch chuyển bằng chuột nhờ
//vào vị trí các vertex có sẵn trong tất cả các hình đang tồn tại
//biến isRemind sẽ thông báo có bật nhắc nhở không,nếu có thì sẽ kiểm tra nếu có vị trí gần vị
//trí chuột thì lấy vị trí đó luôn chứ không dùng độ sâu để lấy vị trí nữa
bool getPositionByVertexExist(int x, int y, float &xPosition, float &yPosition, float &zPosition,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm chuyển các điểm về cùng 1 vị trí X trên trục X
void MakeVertexSameX(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm chuyển các điểm về cùng 1 vị trí Y trên trục Y
void MakeVertexSameY(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm chuyển các điểm về cùng 1 vị trí Z trên trục Z
void MakeVertexSameZ(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);




#endif