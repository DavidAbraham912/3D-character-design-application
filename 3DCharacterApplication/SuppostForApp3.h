#ifndef SuppostForApp3_H
#define SuppostForApp3_H

#include "SuppostForApp2.h"


//các hàm xử lý cho menu app

//hàm đặt kết cấu cho các vật được chọn
void setTextureForObjectChoice(int whichTexture, vector<itemChoice> itemsChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo,3 là bị chồng chéo điểm
int getErrorToRound(point v0, point v1, point v2, float radiusRound);
//hàm bo góc
void roundEdge(point A, point B, point C, float radiusRound, int numberVertexAdd, point *arrayVertex, int errorRound, int errorChange);

//hàm bo tròn các góc cạnh
void roundEdgeTriaStrip(TriangleStripAttribute *triaStrip, float radiusRound, int numberVertexAdd);

//hàm bo góc cạnh dùng cho các hình có thuộc tính giống sphere như sphere,cone,cylinder,empty cylinder
void roundEdgeForObject1(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo góc cạnh dùng cho các hình có thuộc tính giống empty cylinder(cụm đỉnh trên cùng và dưới cùng bị hở)
void roundEdgeForObject2(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo góc cạnh dùng cho các hình có thuộc tính giống ObjectCustom1
void roundEdgeForObject3(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);

//hàm bo tròn góc cạnh của sphere
void roundEdgeSphere(SphereAttribute *sphere, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo tròn góc cạnh của cone
void roundEdgeCone(ConeAttribute *cone, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo tròn góc cạnh của cylinder
void roundEdgeCylinder(CylinderAttribute *cylinder, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo tròn góc cạnh của empty cylinder
void roundEdgeEmptyCylinder(EmptyCylinderAttribute *cylinder, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);
//hàm bo tròn góc cạnh của ObjectCustom0
void roundEdgeObjectCustom0(ObjectCustom0Attribute *object, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical);

//hàm vẽ menu có nút tăng giảm
//vị trí các nút tăng giảm là (left+90 left+100,top top+10),(left+170 left+180,top top+10)
//vị trí khung giá trị(left+95 left+165,top top+10)
void drawMenuPlusMinus(char* text, float value, bool isChoice,
	int leftItem, int topItem);
void drawMenuPlusMinus(char* text, int value, bool isChoice,
	int leftItem, int topItem);
void drawMenuPlusMinus(char* text, char* charValue,
	int leftItem, int topItem);
//hàm vẽ menu Off/On
//vị trí điểm nhấn là (left + 110 left+150,top top+10)
void drawMenuOffOn(char* text, bool isOn,
	int leftItem, int topItem);
//hàm vẽ menu get value
//vị trí nut get(+65 +95,-2 +12) max(+100 +130,-2 +12)  min(+135 +165,-2 +12)
//vị trí ô hiện giá trị(0 +60,-2 +12)
void drawMenuGetValue(int value, bool isChoiceText,
	int leftItem, int topItem);

//hiện thông tin về các cài đặt của ứng dụng

//hiện hộp chọn màu(menuGroup1)
void showMenuGroup1(float *colorDefaul, int modelMenuGroup, GLint colorPicker,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//kiểm tra xem chọn trúng mục nào của hộp chọn màu không
bool checkChoiceMenuGroup1(int x, int y, bool &isChoiceColorPicker, int &modelMenuGroup,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);

//hiện các texture cho thuộc tính texture
void showMenuTexture(itemTextureObject itemTexture,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm kiểm tra xem có chọn trúng texture nào không
bool checkToChoiceMenuTexture(int x, int y, itemTextureObject &itemTexture, vector<itemChoice> itemsChoice,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hiện các nút tăng giảm và các giá trị thuộc tính liên quan như(depthRound,numberLongitude,...)
void showToolChangeAttribute(itemChoice item, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<SphereAttribute*> sphereArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<EmptyCylinderAttribute*> emptyCylinderArray, vector<TorusAttribute*> torusArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//tìm ra số chia hết cho 360,dùng cho các hình như cone,cylinder,...
int findNumberDivisibleBy360(int valueStart, bool isPlus);

//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
bool appendCharArrayForValueAttribute(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	itemChoice item,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm lấy giá trị trong ô thuộc tính đang được chọn để chuyển thành mảng char
void getCharArrayFromValueAttribute(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	itemChoice item,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm tăng giảm giá trị các thuộc tính của object tại vị trí
bool plusAttributeObject(bool isPlus, itemChoice item,
	int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm chỉnh sửa các thuộc tính của hình
bool changeAttributeObject(int x, int y, itemChoice item,
	int &mouseModel, int &modelEditStyle,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<int> &positionVerticesChoice,
	int &item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array);

//hàm hiện các thông tin cần thay đổi để xử lý bo tròn góc các vật
void showToolChangeRoundEffect(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	bool isRoundCorned, int whichStyleRound, int numberVertexRound2Side, float radiusRound2Side,
	int numberVertexRoundHorizontal, int numberVertexRoundVertical, float radiusRoundHorizontal, float radiusRoundVertical,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueRound(int &whichStyleRound, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	int &numberVertexRound2Side, float &radiusRound2Side,
	int &numberVertexRoundHorizontal, int &numberVertexRoundVertical,
	float &radiusRoundHorizontal, float &radiusRoundVertical);
//hàm áp dụng bo tròn cho hình
void appendRoundInMenu(bool &isRoundCorner, int &whichStyleRound,
	int &numberVertexRound2Side, float &radiusRound2Side,
	int &numberVertexRoundHorizontal, int &numberVertexRoundVertical, float &radiusRoundHorizontal, float &radiusRoundVertical,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm chọn các thông tin cũng như áp dụng bo tròn góc của tất cả các hình
bool checkToApplyRound(int x, int y, int &item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	bool &isRoundCorned, int &whichStyleRound,
	int &numberVertexRound2Side, float &radiusRound2Side,
	int &numberVertexRoundHorizontal, int &numberVertexRoundVertical, float &radiusRoundHorizontal, float &radiusRoundVertical,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array);
//hàm hiên thông tin về các biến đổi muốn áp dụng(translate,rotate,scale)
void showToolTransform(int whichTransform, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	float translateX, float translateY, float translateZ, float rotateX,
	float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueTransform(int whichTransform, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	float &translateX, float &translateY, float &translateZ, float &rotateX,
	float &rotateY, float &rotateZ, float &scaleX, float &scaleY, float &scaleZ);

//hàm hiện thông tin cho symmetryVertices
void showInformationSymmetryVertices(int whichStyleSymmetry, int whichItemSymmetry,
	vector<SymmetryVertices> symmetryVertices,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm lấy ra tên của các hình từ giá trị tên bằng số
void getCharNameByIntName(char *charArray, int object);
//hàm hiện thông tin cho symmetryObjects
void showInformationSymmetryObjects(int whichItemSymmetry, vector<SymmetryObjects> symmetryObjects,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hiên thông tin về cài đặt đối xứng
void showToolOfSymmetry(vector<itemChoice> itemsChoice, int item_choice_in_MenuGroup2,
	bool symmetryVertexOrObject, int whichStyleSymmetry, int whichItemSymmetry,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm lấy ra giá trị lớn nhất cho cả vertex,row,column của hình đang được chọn
//whichAttribute = 0 là vertex,1 là row,2 là column
int getMaxValueAttribute(int whichAttribute, itemChoice item,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm lấy ra các item(vertex,row hay column) từ 2 item đầu và cuối(hàm này dùng để lấy các item để xác định các đỉnh đối xứng)
void getAllItemCenterOfStartAndEnd(int whichStyleSymmetry, itemChoice item,
	bool &isGetSymmetryLikeClockwise, int *startAndEndSymmetry, int maxValue,
	vector<int> &positionVertex, vector<PositionRowOrColumn> &positionRowOrColumn,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm lấy ra id của vật khi có object và positionInArray
int getIdOfObject(int object, int positionObject,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm kiểm tra các cài đặt trong symmetryVertices
bool checkToChoiceSymmetryVertices(int x, int y,
	int &whichStyleSymmetry, int &whichItemSymmetry,
	vector<itemChoice> &itemsChoice, vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	vector<int> positionVerticesChoice,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool &isGetSymmetryLikeClockwise1, bool &isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//kiểm tra xem 2 hình được chọn có cùng chung thuộc tính(cùng loại và cùng numberLongitude và numberLatitude)
bool isSameAttribute(itemChoice item1, itemChoice item2,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm thêm các item vào symmetryObject
void addItemInSymmetryObject(vector<SymmetryObjects> &symmetryObjects, itemChoice item1, itemChoice item2,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm kiểm tra các cài đặt trong symmetryObjects
bool checkToChoiceSymmetryObjects(int x, int y, int &whichItemSymmetry,
	vector<itemChoice> &itemsChoice,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);
//hàm kiểm tra chọn các cài đặt đối xứng
bool checkToChoiceToolOfSymmetry(int x, int y, int &item_choice_in_MenuGroup2,
	bool &symmetryVertexOrObject, int &whichStyleSymmetry, int &whichItemSymmetry,
	vector<itemChoice> &itemsChoice, vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	vector<int> positionVerticesChoice,
	bool &symmetry_translateX, bool &symmetry_translateY, bool &symmetry_translateZ,
	bool &symmetry_rotateX, bool &symmetry_rotateY, bool &symmetry_rotateZ,
	bool &symmetry_scaleX, bool &symmetry_scaleY, bool &symmetry_scaleZ,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool &isGetSymmetryLikeClockwise1, bool &isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array);

void showToolOfApp(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	bool isRemind, bool isShowBeforeDraw, bool isDrawNet,
	float tool_arrowSize, float tool_circleSize,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueTool(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	float &tool_arrowSize, float &tool_circleSize);
//hàm kiểm tra chọn ToolApp
bool checkToChoiceToolApp(int x, int y, int &item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	bool &isRemind, bool &isShowBeforeDraw, bool &isDrawNet,
	float &tool_arrowSize, float &tool_circleSize,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu);



#endif
