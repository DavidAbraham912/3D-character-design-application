#ifndef Point_H
#define Point_H
#include <vector>
#include <freeglut.h>
using namespace std;

typedef struct point2D {
	float x, y;
} point2D;

typedef struct point {
	float x, y, z;
} point;
/*0:Lines,1:line_strip,2:line_loop,3:triangles,4:triangle_strip,5:triangle_fan
10 là hình khối cầu,11 là hình khối vuông,12 hình khối vuông bo tròn,13 là hình nón,14 là hình trụ tròn,
15 là hình kim tự tháp,16 là hình trụ tròn rỗng,17 là hình bánh rán,18 là hình ảnh
19 là ObjectCustom0,
(-1 là k0 chọn hình nào)*/
typedef struct itemChoice {
	int object;//kiểu đối tượng
	int id;//id của đối tượng được chọn
	int positionOfChoice;//vị trí của hình được chọn trong mảng hình đó
} itemChoice;
//kiểu đối tượng chứa các dữ liệu trục xoay,vị trí xoay,.. để xoay đối tượng cũng như các hàm liên quan đến
//xoay,cũng như góc độ của đối tượng
typedef struct itemRotateObject {
	int whichCircleChoice;//hình tròn nào được chọn để xoay(0 là trục x,1 là y,2 là z)
	int firstItemChoice;//vị trí item nhấp chuột chạm đầu tiên
	int itemChoiceNow;//vị trí item mà chuột đang chọn hiện tại
	bool isRotateLikeClockwise;
} itemRotateObject;
//cấu trúc dùng cho texture
typedef struct itemTextureObject {
	GLuint startNameTexture;//tên liên kết đầu tiên của dãy tên cho texture
	int textureChoiceNow;//vị trí của texture đang được chọn hiện tại
	int numberTexture;//số lượng texture đã load
} itemTextureObject;
//kiểu dùng cho thêm,xóa,chọn chuỗi vertex
typedef struct PositionRowOrColumn {
	int positionRow;
	int positionColumn;
	int positionColumnOpposite;
} PositionRowOrColumn;

//kiểu dùng cho chọn bằng vùng chọn
typedef struct AreaChoice {
	//trung tâm hình tròn
	point centerArea;
	//bán kính hình tròn
	float radius;
	//3 vị trí xung quanh điểm nhấn để tạo thành mặt phẳng nhấn
	point v[3];
	//có đang nhấn chọn vùng chọn không
	bool isChoice;
} AreaChoice;

//kiểu dùng cho đối xứng vertex,row hay column
typedef struct SymmetryVertices {
	int object;
	int positionInArray;
	vector<PositionRowOrColumn> positionROrC1;
	vector<PositionRowOrColumn> positionROrC2;
	vector<int> positionVertices1;
	vector<int> positionVertices2;
} SymmetryVertices;

//kiểu dùng cho đối xứng Object
typedef struct SymmetryObjects {
	int object1;
	int positionInArray1;
	int object2;
	int positionInArray2;
	//có làm đảo ngược đối xứng trên hàng của vật đối xứng
	bool isInvertedItemsInRow;
	//số lượng vertex trên 1 hàng(row) dùng khi bật isInvertedItemsInRow = true;
	int numberItemInRow;
} SymmetryObjects;

#endif
