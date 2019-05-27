#ifndef SqlServerConnect_H
#define SqlServerConnect_H

//các thư viện để kết nối sql
#include <iostream>
#include <fstream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

//các thư viện cần cho thương trình
#include "SuppostForApp2.h"

//hàm in lỗi khi kết nối
void extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type);
//hàm kết nối và lưu dữ liệu
void saveDataBase(vector<TriangleAttribute*> triaArray,vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray,vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray,vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray,vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray,vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray,vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm kết nối và lấy dữ liệu từ cơ sở dữ liệu
void loadDataBase(vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing);

//hàm lưu lại các thông tin về các đối tượng trên app vào .txt
void saveObjectsInTxt(char *nameTxt,
	vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm lưu các thông tin về thuộc tính của ứng dụng vào tệp .txt
void saveAttributeApp(char *nameTxt,
	vector<int> positionVerticesChoice, vector<int> positionFacesChoice,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, int mouseModel, int modelStyleDraw, int modelTop,
	int modelEditStyle, int modelSpace, int modelMenuGroup1, int modelMenuGroup2,
	int whichStyleRound, int numberVertexRound2Side, int numberVertexRoundHorizontal, int numberVertexRoundVertical,
	float radiusRound2Side, float radiusRoundHorizontal, float radiusRoundVertical,
	int menu_whichTransform, float menu_translateX, float menu_translateY, float menu_translateZ,
	float menu_rotateX, float menu_rotateY, float menu_rotateZ,
	float menu_scaleX, float menu_scaleY, float menu_scaleZ,
	bool symmetryVertexOrObject, int whichStyleSymmetry, int whichItemSymmetry,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	bool tool_isShowBeforeDraw, bool tool_isRemind, bool tool_isDrawNet,
	float tool_arrowSize, float tool_circleSize);
//hàm lấy ra các thuộc tính của app đã lưu trong tệp txt
void loadAttributeApp(char *nameTxt,
	vector<int> &positionVerticesChoice, vector<int> &positionFacesChoice,
	vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<itemChoice> &itemsChoice, int &mouseModel, int &modelStyleDraw, int &modelTop,
	int &modelEditStyle, int &modelSpace, int &modelMenuGroup1, int &modelMenuGroup2,
	int &whichStyleRound, int &numberVertexRound2Side, int &numberVertexRoundHorizontal, int &numberVertexRoundVertical,
	float &radiusRound2Side, float &radiusRoundHorizontal, float &radiusRoundVertical,
	int &menu_whichTransform, float &menu_translateX, float &menu_translateY, float &menu_translateZ,
	float &menu_rotateX, float &menu_rotateY, float &menu_rotateZ,
	float &menu_scaleX, float &menu_scaleY, float &menu_scaleZ,
	bool &symmetryVertexOrObject, int &whichStyleSymmetry, int &whichItemSymmetry,
	bool &symmetry_translateX, bool &symmetry_translateY, bool &symmetry_translateZ,
	bool &symmetry_rotateX, bool &symmetry_rotateY, bool &symmetry_rotateZ,
	bool &symmetry_scaleX, bool &symmetry_scaleY, bool &symmetry_scaleZ,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool &isGetSymmetryLikeClockwise1, bool &isGetSymmetryLikeClockwise2,
	bool &tool_isShowBeforeDraw, bool &tool_isRemind, bool &tool_isDrawNet,
	float &tool_arrowSize, float &tool_circleSize);

//hàm ghi các dữ liệu đỉnh và hình vào tệp .txt
void saveDataToTxt(vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm lấy tên để đặt tiếp cho txt và thay đổi giá trị trong mảng txtUsing và biến offsetTxtUsing(nếu cần)
void getNameTxtForSave(vector<int> &txtUsing, int &offsetTxtUsing,
	char *pathObjectTxt, char *pathAttributeTxt);
//hàm lấy tên txt từ vị trí
void getNameTxt(int position,
	char *pathObjectTxt, char *pathAttributeTxt);

//hàm lưu các thông tin dịch chuyển vào tệp txt để khi cần thì trở lại dịch chuyển trước
//hay tiến lên dịch chuyển tiếp theo
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi thuộc tính dẫn đến thay đổi vật
//,6 là tạo mới các vertex,7 là xóa các vertex
void saveInformationChange(char *nameTxt,
	int whichEffect, float value1, float value2, float value3);


// lưu lại toàn bộ thông tin của các vật vừa được thay đổi, để lát đặt lại(nếu cần) sau khi bị xóa
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void saveInformationObject(char *nameTxt, int whichEffect, vector<itemChoice> itemsChoice,
	vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
// lưu lại toàn bộ thông tin của các vertex , để lát đặt lại(nếu cần) sau khi bị xóa
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void saveInformationVertices(char *nameTxt, int whichEffect, itemChoice item, vector<int> positionVerticesChoice,
	vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

//hàm lấy ra và thêm vào các object đã được lưu trong txt
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void loadInformationObject(char *path, int isTurnUp, vector<itemChoice> &itemsChoice,
	int &whichItemSymmetry,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing);
//hàm load các thông tin về các vật đã lưu lần trước trong tệp txt
void loadObjectsInTxt(char *path,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing);

//hàm lấy ra và thêm vào các vertex đã được lưu trong txt
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void loadInformationVertices(char *path, int isTurnUp,
	vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm lấy ra thông tin về các lần dịch chuyển trước để dịch chuyển lại
//cái này dùng chung cho cả vertex và object
void loadInformationChange(char *path, bool isTurnUp,
	vector<itemChoice> itemsChoice, vector<int> positionVerticesChoice,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry, int modelEditStyle,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);



#endif
