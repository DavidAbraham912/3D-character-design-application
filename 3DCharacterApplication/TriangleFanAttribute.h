#ifndef TriangleFanAttribute_H
#define TriangleFanAttribute_H
#include <vector>
#include "Point.h"


//hàm define này là định nghĩa thư viện,còn cặp #ifndef và #endif là nếu thư viện có tên 
//trong hàm ifndef đã được định nghĩa rồi thì k0 định nghĩa nữa
class TriangleFanAttribute
{
public:
	//mảng vector này lưu trữ các giá trị vertex(mỗi giá trị có chứa 3 giá trị x,y,z)
	std::vector<point> vertexArray;
	point centerObject;
	//mảng vector này định nghĩa các giá trị của normal vector là các giá trị x,y,z
	//cứ 3 phần tử là tạo thành 1 normal vector (3 vertex đầu tiên dùng chung 1 normal vector còn từ đỉnh thứ 4
	//mỗi vertex dùng 1 normal vector)
	std::vector<point> normalVector;
	float colorR, colorG, colorB, colorA, mShiness;
	int id;
	int idTexture;
	TriangleFanAttribute();
	TriangleFanAttribute(TriangleFanAttribute *triaFan);
	TriangleFanAttribute(TriangleFanAttribute &triaFan);
	~TriangleFanAttribute() {
		vertexArray.clear();
		normalVector.clear();
	}
	void insertColor(float red, float green, float blue, float alpha);
};

#endif

