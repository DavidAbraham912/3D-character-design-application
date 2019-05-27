#ifndef SuppostForApp2_H
#define SuppostForApp2_H

#include "SuppostForApp.h"
//thư viện dùng để đọc file
#include <filesystem>
//thư viện dùng để đọc các pixel trong hình ảnh thành mảng
#include <il.h>

//hàm tải ảnh
int LoadImage(char *filename);
//load các kết cấu và gắn tên liên kết cho chúng
void loadTextureForObject(itemTextureObject &itemTexture);


//vẽ đường trắng bao ngoài để biết hình đang được chọn
void DrawTrianglesLine(TriangleAttribute *tria);
void DrawTriangleStripLine(TriangleStripAttribute *triaStrip);
void DrawTriangleFanLine(TriangleFanAttribute *triaFan);
void DrawSphereLine(SphereAttribute *sphere, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn);
void DrawCubeLine(CubeAttribute *cube, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn);
void DrawCubeRoundLine(CubeRoundAttribute *cube);
void DrawConeLine(ConeAttribute *cone, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn);
void DrawCylinderLine(CylinderAttribute *cylinder, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn);
void DrawPyramidLine(PyramidAttribute *pyr);
void DrawEmptyCylinderLine(EmptyCylinderAttribute *cylinder, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn);
void DrawTorusLine(TorusAttribute *torus);
void DrawPicturesLine(PictureAttribute *picture);
void DrawObjectCustom0Line(ObjectCustom0Attribute *object, int modelEditStyle,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn);
//vẽ hình chấm ở các vertex
void DrawTrianglesPoint(TriangleAttribute *tria, GLenum mode, std::vector<int> modelVertexChoice);
void DrawTriangleStripPoint(TriangleStripAttribute *triaStrip, GLenum mode, std::vector<int> modelVertexChoice);
void DrawTriangleFanPoint(TriangleFanAttribute *triaFan, GLenum mode, std::vector<int> modelVertexChoice);
void DrawSpherePoint(SphereAttribute *sphere, GLenum mode, std::vector<int> modelVertexChoice);
void DrawCubePoint(CubeAttribute *cube, GLenum mode, std::vector<int> modelVertexChoice);
void DrawCubeRoundPoint(CubeRoundAttribute *cube, GLenum mode, std::vector<int> modelVertexChoice);
void DrawConePoint(ConeAttribute *cone, GLenum mode, std::vector<int> modelVertexChoice);
void DrawCylinderPoint(CylinderAttribute *cylinder, GLenum mode, std::vector<int> modelVertexChoice);
void DrawPyramidPoint(PyramidAttribute *pyr, GLenum mode, std::vector<int> modelVertexChoice);
void DrawEmptyCylinderPoint(EmptyCylinderAttribute *cylinder, GLenum mode, std::vector<int> modelVertexChoice);
void DrawTorusPoint(TorusAttribute *torus, GLenum mode, std::vector<int> modelVertexChoice);
void DrawPicturesPoint(PictureAttribute *picture, GLenum mode, std::vector<int> modelVertexChoice);
void DrawObjectCustom0Point(ObjectCustom0Attribute *object, GLenum mode, std::vector<int> modelVertexChoice);
//vẽ các mặt được chọn
void DrawTriangleStripFace(TriangleStripAttribute *triaStrip, vector<int> indexesFaceChoice);
void DrawTriangleFanFace(TriangleFanAttribute *triaFan, vector<int> indexesFaceChoice);
void DrawSphereFace(SphereAttribute *sphere, vector<int> indexesFaceChoice);
void DrawCubeFace(CubeAttribute *cube, vector<int> indexesFaceChoice);
void DrawCubeRoundFace(CubeRoundAttribute *cube, vector<int> indexesFaceChoice);
void DrawConeFace(ConeAttribute *cone, vector<int> indexesFaceChoice);
void DrawCylinderFace(CylinderAttribute *cylinder, vector<int> indexesFaceChoice);
void DrawEmptyCylinderFace(EmptyCylinderAttribute *cylinder, vector<int> indexesFaceChoice);
void DrawTorusFace(TorusAttribute *torus, vector<int> indexesFaceChoice);
void DrawObjectCustom0Face(ObjectCustom0Attribute *object, vector<int> indexesFaceChoice);

//vẽ đường lưới,hay các điểm chọn,hay các mặt tam giác chọn cho hình đang được chọn
void drawObjectLineOrPoint(GLenum mode, int modelEditStyle, vector<itemChoice> itemsChoice,
	vector<int> positionVerticesChoice, vector<int> positionFacesChoice, vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);


//hàm lấy ra các vertex từ vị trí chuỗi vertex được chọn
void getVerticesFromRowOrColumn(itemChoice item,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn, vector<int> &positionVerticesChoice,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm lấy chuỗi row và column từ chuỗi vertex(dùng cho các hình được tạo theo kiểu dạng sphere)
void getRowOrColumnByVertices(int numberLongitude, int numberLatitude,
	vector<int> positionVerticesChoice, vector<PositionRowOrColumn> &positionChoiceRowOrColumn);
//hàm lấy ra row và column từ các vertex đang được chọn của hình đang chọn
void getRowOrColumnByVertices(itemChoice item,
	vector<int> positionVerticesChoice, vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//lấy ra các vertex được chọn mà có gắn liền với khuôn mặt được chọn
//phải kiểm tra độ sâu cảu mặt được chọn nữa
void getVertexByFace(vector<int> &positionVerticesChoice, vector<int> &positionFacesChoice, itemChoice item,
	vector<TriangleStripAttribute*> triaStripArray, vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<PyramidAttribute*> pyrArray,
	vector<EmptyCylinderAttribute*> emptyCylinderArray, vector<TorusAttribute*> torusArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//kiểm tra xem có thể thêm các chuỗi vertex vào trong hình đang được chọn
void checkToCreatRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<point> &vertexToDrawRectangle, vector<point> &vertexToDrawRectangleSymmetry,
	itemTextureObject itemTexture, PositionRowOrColumn &positionAddRowOrColumn,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm chọn các chuỗi vertex dọc hay ngang
void checkToChoiceRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	itemTextureObject itemTexture, vector<PositionRowOrColumn> &positionChoiceRowOrColumn, vector<int> &positionVertexChoice,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//kiểm tra xem có thể xóa các chuỗi vertex vào trong hình đang được chọn
void checkToDeleteRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<point> &vertexToDrawRectangle, vector<point> &vertexToDrawRectangleSymmetry,
	itemTextureObject itemTexture, PositionRowOrColumn &positionDeleteRowOrColumn,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm kiểm tra 1 điểm có nằm trong tam giác được tạo bởi 3 điểm không
bool checkPointInTriangle(point pointTouch, point pointTria0, point pointTria1, point pointTria2);
//hàm kiểm tra xem khuôn mặt nào được chọn
void checkToChoiceFaceInObject(itemChoice item, int x, int y, vector<int> &positionFaceChoice,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<TriangleStripAttribute*> triaStripArray, vector<TriangleFanAttribute*> triaFanArray,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm để sửa lỗi khi xóa một hàng hay cột mà không có đối xứng,trong 1 object có thông tin trong symmetryVertices
void fixErrorWhenDeleteItemNotHaveItemSymmetry(PositionRowOrColumn positionDeleteRowOrColumn,
	SymmetryVertices &symmetryVerticesNow);
//hàm xóa chuỗi vertex
void deleteRowVertexInObject(vector<itemChoice> itemsChoice, PositionRowOrColumn positionDeleteRowOrColumn,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm thêm chuỗi vertex
void addRowVertexInObject(vector<itemChoice> itemsChoice, PositionRowOrColumn positionAddRowOrColumn,
	vector<PositionRowOrColumn> &positionChoiceRowOrColumn, vector<int> &positionVerticesChoice,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//tạo ra 1 bản copy của các hình đang được chọn
void copyObjectsChoice(vector<itemChoice> &itemsChoice, vector<int> &idsUsing,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//sao chép nghịch đảo vật
//axis thông báo trục copy đối xứng
//axis =0 là đối xứng qua trục X,1 là đối xứng qua trục Y,2 là đối xứng qua trục Z
void copyInverseObjectChoice(int axis, vector<itemChoice> &itemsChoice, vector<int> &idsUsing,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm tìm các điểm trên đối tượng được chọn bằng vùng chọn
void getVertexByArea(itemChoice item, AreaChoice areaChoice, vector<int> &positionVerticesChoice,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm kiểm tra xem vùng chọn có cắt trúng đường thẳng nối 2 điểm không
bool checkAreaCutLine(AreaChoice areaChoice, point v0, point v1);
//kiểm tra xem tâm giác được tạo bởi 3 điểm có nằm trong vùng chọn không
bool checkTriaInArea(AreaChoice areaChoice, point v0, point v1, point v2);
//hàm tìm các điểm trên đối tượng được chọn bằng vùng chọn
void getFaceByArea(itemChoice item, AreaChoice areaChoice, vector<int> &positionFaceChoice,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm thêm cụm vertex trên,dưới,trái hay phải ObjectCustom0
void AddVerticesAroundObjectCustom0(int whichDirection, ObjectCustom0Attribute* object,
	vector<int> &positionVerticesChoice);

#endif
