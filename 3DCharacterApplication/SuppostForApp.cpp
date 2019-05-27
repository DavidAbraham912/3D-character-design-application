#include "SuppostForApp.h"

//hàm sắp xếp mảng vector tho thứ tự từ nhỏ đến lớn
//tạm thời đang dùng thuật toán sắp xếp chậm,bữa sau sẽ viết thuật toán quicksort
void ArrangeOrderFromSmallToLarge(vector<int> &arrayIn) {
	int numberElement = arrayIn.size(), min, positionMin;
	for (int i = 0; i < numberElement - 1; i++) {
		min = arrayIn.at(i);
		positionMin = i;
		for (int j = i + 1; j < numberElement; j++) {
			if (min > arrayIn.at(j)) {
				min = arrayIn.at(j);
				positionMin = j;
			}
		}
		if (positionMin != i) {
			arrayIn.at(positionMin) = arrayIn.at(i);
			arrayIn.at(i) = min;
		}
	}
}
//sắp xếp từ lớn đến nhỏ
void ArrangeOrderFromLargeToSmall(vector<int> &arrayIn) {
	int numberElement = arrayIn.size(), max, positionMax;
	for (int i = 0; i < numberElement - 1; i++) {
		max = arrayIn.at(i);
		positionMax = i;
		for (int j = i + 1; j < numberElement; j++) {
			if (max < arrayIn.at(j)) {
				max = arrayIn.at(j);
				positionMax = j;
			}
		}
		if (positionMax != i) {
			arrayIn.at(positionMax) = arrayIn.at(i);
			arrayIn.at(i) = max;
		}
	}
}
//sắp xếp từ lớn đến nhỏ dành cho itemsChoice
//nếu cùng 1 kiều phần tử thì các phần tử có vị trí lớn hơn trong mảng sẽ đứng trước
void ArrangeOrderFromSmallToLarge(vector<itemChoice> &itemsChoice) {
	int numberElement = itemsChoice.size(), min, positionMin, whichObject;
	itemChoice itemCheck;
	for (int i = 0; i < numberElement - 1; i++) {
		min = itemsChoice.at(i).positionOfChoice;
		whichObject = itemsChoice.at(i).object;
		positionMin = i;
		for (int j = i + 1; j < numberElement; j++) {
			itemCheck = itemsChoice.at(j);
			//nếu là cùng kiểu phần tử thì mới kiểm tra xem vị trí của nó trong mảng
			//nhỏ hơn hay lớn hơn vị trí của phần tử trước
			if (whichObject == itemCheck.object && min > itemCheck.positionOfChoice) {
				min = itemCheck.positionOfChoice;
				positionMin = j;
			}
		}
		//hoán đổi
		if (positionMin != i) {
			itemCheck = itemsChoice.at(i);
			itemsChoice.at(i) = itemsChoice.at(positionMin);
			itemsChoice.at(positionMin) = itemCheck;
		}
	}
}
//hàm đảo ngược thứ tự của các item trong mảng vector
void reverseItemInVector(vector<int> &vertexArray) {
	int numberVertex = vertexArray.size(), halfNumberVertex = numberVertex / 2;
	for (int i = 0; i < halfNumberVertex; i++) {
		//hàm hoán đổi giá trị 2 phần tử trong vertex
		iter_swap(vertexArray.begin() + i, vertexArray.begin() + (numberVertex - 1 - i));

	}
}
void reverseItemInVector(vector<PositionRowOrColumn> &vertexArray) {
	int numberVertex = vertexArray.size(), halfNumberVertex = numberVertex / 2;
	for (int i = 0; i < halfNumberVertex; i++) {
		//hàm hoán đổi giá trị 2 phần tử trong vertex
		iter_swap(vertexArray.begin() + i, vertexArray.begin() + (numberVertex - 1 - i));

	}
}

//hàm lấy id để đặt cho vật
int getIdForObject(vector<int> &idsUsing) {
	int idToSet = 0, numberIdsUsing = idsUsing.size();
	bool isGetId = false;
	//tìm ra id chưa có trong mảng id đang được dùng để đặt
	//nếu mảng các id đang được sử dụng mà không rỗng thì mới kiểm tra
	if (numberIdsUsing > 0) {
		while (!isGetId)
		{
			for (int i = 0; i < numberIdsUsing; i++) {
				if (idToSet == idsUsing.at(i)) {
					idToSet++;
					break;
				}
				else if (i == numberIdsUsing - 1) {
					isGetId = true;
				}
			}
		}
	}
	//đặt id được chọn hiện tại vào mảng idsUsing
	idsUsing.push_back(idToSet);
	return idToSet;
}

//tính toán mặt phẳng cắt
bool caculatorPlane(GLdouble *v1, GLdouble *v2, GLdouble *v3, GLdouble *plane) {
	//plane là mảng chứa 4 phần tử theo thứ tự A,B,C,D
	try
	{
		GLdouble v1v2[3], v2v3[3];
		for (int j = 0; j < 3; j++) {
			v1v2[j] = v2[j] - v1[j];
			v2v3[j] = v3[j] - v2[j];
		}
		plane[0] = v1v2[1] * v2v3[2] - v1v2[2] * v2v3[1];
		plane[1] = v1v2[2] * v2v3[0] - v1v2[0] * v2v3[2];
		plane[2] = v1v2[0] * v2v3[1] - v1v2[1] * v2v3[0];
		plane[3] = plane[0] * (-v1[0]) + plane[1] * (-v1[1]) + plane[2] * (-v1[2]);
		if (isnan(plane[0]) || isnan(plane[1]) || isnan(plane[2]) || isnan(plane[3])) {
			throw 1;
		}
		return true;
	}
	catch (...)
	{
		plane[0] = 0.0;
		plane[1] = 0.0;
		plane[2] = 0.0;
		plane[3] = 0.0;
		return false;
	}
}
bool caculatorPlane(point v1, point v2, point v3, GLdouble *plane) {
	//plane là mảng chứa 4 phần tử theo thứ tự A,B,C,D
	try
	{
		GLdouble v1v2[3], v2v3[3];

		v1v2[0] = v2.x - v1.x;
		v2v3[0] = v3.x - v2.x;
		v1v2[1] = v2.y - v1.y;
		v2v3[1] = v3.y - v2.y;
		v1v2[2] = v2.z - v1.z;
		v2v3[2] = v3.z - v2.z;

		plane[0] = v1v2[1] * v2v3[2] - v1v2[2] * v2v3[1];
		plane[1] = v1v2[2] * v2v3[0] - v1v2[0] * v2v3[2];
		plane[2] = v1v2[0] * v2v3[1] - v1v2[1] * v2v3[0];
		plane[3] = plane[0] * (-v1.x) + plane[1] * (-v1.y) + plane[2] * (-v1.z);
		if (isnan(plane[0]) || isnan(plane[1]) || isnan(plane[2]) || isnan(plane[3])) {
			throw 1;
		}
		return true;
	}
	catch (...)
	{
		plane[0] = 0.0;
		plane[1] = 0.0;
		plane[2] = 0.0;
		plane[3] = 0.0;
		return false;
	}
}
bool caculatorPlane(point v1, point v2, point v3, float *plane) {
	//plane là mảng chứa 4 phần tử theo thứ tự A,B,C,D
	try
	{
		GLdouble v1v2[3], v2v3[3];

		v1v2[0] = v2.x - v1.x;
		v2v3[0] = v3.x - v2.x;
		v1v2[1] = v2.y - v1.y;
		v2v3[1] = v3.y - v2.y;
		v1v2[2] = v2.z - v1.z;
		v2v3[2] = v3.z - v2.z;

		plane[0] = v1v2[1] * v2v3[2] - v1v2[2] * v2v3[1];
		plane[1] = v1v2[2] * v2v3[0] - v1v2[0] * v2v3[2];
		plane[2] = v1v2[0] * v2v3[1] - v1v2[1] * v2v3[0];
		plane[3] = plane[0] * (-v1.x) + plane[1] * (-v1.y) + plane[2] * (-v1.z);
		if (isnan(plane[0]) || isnan(plane[1]) || isnan(plane[2]) || isnan(plane[3])) {
			throw 1;
		}
		return true;
	}
	catch (...)
	{
		plane[0] = 0.0;
		plane[1] = 0.0;
		plane[2] = 0.0;
		plane[3] = 0.0;
		return false;
	}
}


//các hàm tính toán normal vector
//bình thường hóa normal vector
void normalize(float v[3])
{
	//tính ra trung bình cộng của cả 3 vị trí x,y,z
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	//nếu bằng 0 thì thôi lấy normal vector đó
	if (d == 0.0) {
		return;
	}
	//nếu k0 bằng 0 thì lấy từng vị trí x,y,z chia cho số trung bình cộng đó
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}
void normalize(point &v)
{
	//tính ra trung bình cộng của cả 3 vị trí x,y,z
	float d = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	//nếu bằng 0 thì thôi lấy normal vector đó
	if (d == 0.0) {
		return;
	}
	//nếu k0 bằng 0 thì lấy từng vị trí x,y,z chia cho số trung bình cộng đó
	v.x /= d;
	v.y /= d;
	v.z /= d;
}
//hàm tính toán normal vector của tam giác từ 3 đỉnh thuộc tam giác
bool normcrossprod(float v1[3], float v2[3], float v3[3], float out[3])
{
	float d1[3], d2[3];
	for (int j = 0; j < 3; j++) {
		//d1,d2 mỗi mảng sẽ chứa 3 vị trí x,y,z là hiệu của mỗi của 2 đỉnh(vertex) 
		//trong số 3 đỉnh của 1 bề mặt
		d1[j] = v1[j] - v2[j];
		d2[j] = v2[j] - v3[j];
	}
	//tính toán chéo 2 vector để tìm ra vector vuông góc với 2 vector này
	//đó chính là normal vector
	out[0] = d1[1] * d2[2] - d1[2] * d2[1];
	out[1] = d1[2] * d2[0] - d1[0] * d2[2];
	out[2] = d1[0] * d2[1] - d1[1] * d2[0];
	normalize(out);
	if (isnan(out[0]) || isnan(out[1]) || isnan(out[2])) {
		//nếu lỗi thì trả về false
		out[0] = 0.0;
		out[1] = 0.0;
		out[2] = 0.0;
		return false;
	}
	//nếu không bị lỗi gì thì trả về true
	else
	{
		return true;
	}
}
bool normcrossprod(point v1, point v2, point v3, point &out)
{
	point d1, d2;
	//d1,d2 mỗi mảng sẽ chứa 3 vị trí x,y,z là hiệu của mỗi của 2 đỉnh(vertex) 
	//trong số 3 đỉnh của 1 bề mặt
	d1.x = v1.x - v2.x;
	d2.x = v2.x - v3.x;
	d1.y = v1.y - v2.y;
	d2.y = v2.y - v3.y;
	d1.z = v1.z - v2.z;
	d2.z = v2.z - v3.z;

	//tính toán chéo 2 vector để tìm ra vector vuông góc với 2 vector này
	//đó chính là normal vector
	out.x = d1.y * d2.z - d1.z * d2.y;
	out.y = d1.z * d2.x - d1.x * d2.z;
	out.z = d1.x * d2.y - d1.y * d2.x;
	normalize(out);
	if (isnan(out.x) || isnan(out.y) || isnan(out.z)) {
		out.x = 0.0;
		out.y = 0.0;
		out.z = 0.0;
		return false;
	}
	//nếu không bị lỗi gì thì trả về true
	else
	{
		return true;
	}
}
//tìm khoảng cách giữa 2 điểm
float distanceTwoPoint(point a, point b) {
	float distance = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	if (isnan(distance)) {
		return 0.0;
	}
	else
	{
		return distance;
	}
}
//vẽ với kiểu chữ lớn mặc định
void drawText(GLuint x, GLuint y, char* format)
{
	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
	glRasterPos2i(x, y);
	glutBitmapString(font_style, (unsigned char*)format);
}
//vẽ với kiểu chữ tùy chỉnh
void drawText(GLuint x, GLuint y, char* format, char* name, int size)
{
	GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;
	font_style = GLUT_BITMAP_HELVETICA_10;
	if (strcmp(name, "helvetica") == 0) {
		if (size == 12)
			font_style = GLUT_BITMAP_HELVETICA_12;
		else if (size == 18)
			font_style = GLUT_BITMAP_HELVETICA_18;
	}
	else if (strcmp(name, "times roman") == 0) {
		font_style = GLUT_BITMAP_TIMES_ROMAN_10;
		if (size == 24)
			font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	}
	else if (strcmp(name, "8x13") == 0) {
		font_style = GLUT_BITMAP_8_BY_13;
	}
	else if (strcmp(name, "9x15") == 0) {
		font_style = GLUT_BITMAP_9_BY_15;
	}
	glRasterPos2i(x, y);
	glutBitmapString(font_style, (unsigned char*)format);
}

//hàm chuyển mảng char sang số
float getFloatFromCharArray(char* charArray) {
	//đầu tiên kiểm tra xem mảng char này có bị rỗng hay chứa giá trị nào
	//không phải là số không nếu lỗi thì trả về 0.0
	int numberChar = sizeof(charArray);
	for (int i = 0; i < numberChar; i++) {
		if (charArray[i] == NULL) {
			if (i == 0) {
				return 0.0;
			}
			else
			{
				break;
			}
		}
		else if (charArray[i] != '.' && charArray[i] != '-' && charArray[i] != '0' && charArray[i] != '1' &&
			charArray[i] != '2' && charArray[i] != '3' && charArray[i] != '4' && charArray[i] != '5' &&
			charArray[i] != '6' && charArray[i] != '7' && charArray[i] != '8' && charArray[i] != '9') {
			return 0.0;
		}
	}
	//nếu không rỗng cũng không có ký tự lỗi thì chuyển mảng char thành số
	return atof(charArray);
}
int getIntFromCharArray(char* charArray) {
	//đầu tiên kiểm tra xem mảng char này có bị rỗng hay chứa giá trị nào
	//không phải là số không nếu lỗi thì trả về 0.0
	int numberChar = sizeof(charArray);
	for (int i = 0; i < numberChar; i++) {
		if (charArray[i] == NULL) {
			if (i == 0) {
				return 0;
			}
			else
			{
				break;
			}
		}
		else if (charArray[i] != '.' && charArray[i] != '-' && charArray[i] != '0' && charArray[i] != '1' &&
			charArray[i] != '2' && charArray[i] != '3' && charArray[i] != '4' && charArray[i] != '5' &&
			charArray[i] != '6' && charArray[i] != '7' && charArray[i] != '8' && charArray[i] != '9') {
			return 0;
		}
	}
	//nếu không rỗng cũng không có ký tự lỗi thì chuyển mảng char thành số
	return atoi(charArray);
}
//Hàm chuyển số sang mảng char với charArray[10]
void changeNumberIntToCharArray(char* charArray, int number) {
	std::string numberString;
	//chuyển kiểu số sang kiểu chuỗi
	numberString = std::to_string(number);
	//hàm này chuyển 1 chuỗi về 1 mảng char,nếu nhiều hơn 10 ký tự thì bỏ những ký tự phía sau đi
	strcpy_s(charArray, 10, numberString.c_str());
}
void changeNumberIntToVertexCharArray(char* charArray, int number) {
	std::string numberString;
	//chuyển kiểu số sang kiểu chuỗi
	numberString = std::to_string(number);
	//hàm này chuyển 1 chuỗi về 1 mảng char,nếu nhiều hơn 10 ký tự thì bỏ những ký tự phía sau đi
	//append để chuyển 1 chuỗi vào
	//numberString.append("Vertex :");
	numberString = "Vertex " + numberString;
	numberString.append(" :");
	strcpy_s(charArray, 20, numberString.c_str());
}
void changeNumberFloatToCharArray(char* charArray, float number) {
	std::string numberString;
	//chuyển kiểu số sang kiểu chuỗi
	numberString = std::to_string(number);
	//xóa đi 4 số 0 trong chuỗi
	numberString.pop_back();
	numberString.pop_back();
	numberString.pop_back();
	numberString.pop_back();
	//hàm này chuyển 1 chuỗi về 1 mảng char,nếu nhiều hơn 10 ký tự thì bỏ những ký tự phía sau đi
	strcpy_s(charArray, 10, numberString.c_str());
}

//vẽ mũi tên chỉ hướng 2D cho khung hình
void drawArrow(double *projectMatrixArrow, double *modelMatrixArrow) {
	glDisable(GL_LIGHTING);
	//Đặt phép chiếu song song để vẽ mũi tên
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrixArrow);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrixArrow);
	
	//mui ten x
	glColor3f(1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.1f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidCone(0.015f, 0.1f, 10, 10);
	glPopMatrix();
	//mui ten y
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.1f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.015f, 0.1f, 10, 10);
	glPopMatrix();
	//mui ten z
	glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.1f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutSolidCone(0.015f, 0.1f, 10, 10);
	glPopMatrix();

	glBegin(GL_LINES);
	//duong thang x
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.1f, 0.0f, 0.0f);
	//hiện X
	glVertex2f(0.12, 0.05);
	glVertex2f(0.14, 0.08);
	glVertex2f(0.14, 0.05);
	glVertex2f(0.12, 0.08);
	//duong thang y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.1f, 0.0f);
	//hiện Y
	glVertex2f(-0.01, 0.21);
	glVertex2f(0.01, 0.25);
	glVertex2f(-0.001, 0.23);
	glVertex2f(-0.01, 0.25);
	//duong thang z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	//hiện Z
	glVertex3f(0.0, 0.08, 0.12);
	glVertex3f(0.0, 0.08, 0.14);
	glVertex3f(0.0, 0.05, 0.14);
	glVertex3f(0.0, 0.08, 0.12);
	glVertex3f(0.0, 0.05, 0.12);
	glVertex3f(0.0, 0.05, 0.14);
	glEnd();


	glFlush();
	glEnable(GL_LIGHTING);
}
//vẽ các hình vuông để các giá trị theo cả 2 hướng(zy,yx hay xz)
void drawQuadForObject(point center,float arrowSize, int startLoadName) {
	//0 là dich chuyển xy,1 là dịch chuyển xz,2 là dịch chuyển yz
	glDisable(GL_LIGHTING);
	//vẽ hình vuông dịch chuyển xy
	if (startLoadName != -1) {
		glLoadName(startLoadName);
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(center.x + arrowSize*0.5f, center.y + arrowSize * 1, center.z);
	glVertex3f(center.x + arrowSize*0.5f, center.y + arrowSize*0.5f, center.z);
	glVertex3f(center.x + arrowSize * 1, center.y + arrowSize*0.5f, center.z);
	glVertex3f(center.x + arrowSize * 1, center.y + arrowSize * 1, center.z);
	glEnd();
	//vẽ hình vuông dịch chuyển xz
	if (startLoadName != -1) {
		glLoadName(startLoadName+1);
	}
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(center.x + arrowSize*0.5f, center.y, center.z + arrowSize*0.5f);
	glVertex3f(center.x + arrowSize*0.5f, center.y, center.z + arrowSize * 1);
	glVertex3f(center.x + arrowSize * 1, center.y, center.z + arrowSize * 1);
	glVertex3f(center.x + arrowSize * 1, center.y, center.z + arrowSize*0.5f);
	glEnd();
	//vẽ hình vuông dịch chuyển yz
	if (startLoadName != -1) {
		glLoadName(startLoadName + 2);
	}
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(center.x, center.y + arrowSize * 1, center.z + arrowSize * 1);
	glVertex3f(center.x, center.y + arrowSize*0.5f, center.z + arrowSize * 1);
	glVertex3f(center.x, center.y + arrowSize*0.5f, center.z + arrowSize*0.5f);
	glVertex3f(center.x, center.y + arrowSize * 1, center.z + arrowSize*0.5f);
	glEnd();

	//vẽ hình hộp để dịch chuyển theo cả 3 chiều
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	if (startLoadName != -1) {
		glLoadName(startLoadName + 3);
		glutSolidCube(arrowSize*0.4);
	}
	else
	{
		glutWireCube(arrowSize*0.4);
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);
}
//vẽ các mũi tên chỉ hướng 3D cho vật
void drawArrowForObject(float x, float y, float z, float arrowSize,
	bool isCube,int changeRotateFor2D, int startLoadName) {
	//nếu isCube là true thì vẽ đầu mũi tên là hình cube(cái này để phân biệt giữa scale và các thuộc tính khác)
	//biến changeRotateFor2D dùng để thông báo đang chiếu ở hướng nào để loại bỏ mũi tên thừa đi
	glDisable(GL_LIGHTING);
	glLineWidth(2.0f);
	
	//nếu không phải chiếu từ bên phải hay bên trái thì mới hiện mũi tên X
	if (changeRotateFor2D != 1 && changeRotateFor2D != 3) {
		if (startLoadName != -1) {
			glLoadName(startLoadName);
		}
		glBegin(GL_LINES);
		//duong thang x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(x + arrowSize * 0.2, y, z);
		glVertex3f(x + arrowSize * 1.5f, y, z);
		glEnd();
		//mui ten x
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(x + arrowSize * 1.5f, y, z);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		if (isCube) {
			glutSolidCube(arrowSize * 0.15);
		}
		else
		{
			glutSolidCone(arrowSize * 0.15f, arrowSize * 0.7f, 10, 10);
		}
		glPopMatrix();
	}

	if (startLoadName != -1) {
		glLoadName(startLoadName + 1);
	}
	glBegin(GL_LINES);
	//duong thang y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y + arrowSize * 0.2f, z);
	glVertex3f(x, y + arrowSize * 1.5f, z);
	glEnd();
	//mui ten y
	glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(x, y + arrowSize * 1.5f, z);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	if (isCube) {
		glutSolidCube(arrowSize * 0.15);
	}
	else
	{
		glutSolidCone(arrowSize * 0.15f, arrowSize * 0.7f, 10, 10);
	}
	glPopMatrix();

	//nếu không phải chiếu từ trước hay sau thì mới hiện mũi tên Z
	if (changeRotateFor2D != 0 && changeRotateFor2D != 2) {
		if (startLoadName != -1) {
			glLoadName(startLoadName + 2);
		}
		glBegin(GL_LINES);
		//duong thang z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, z + arrowSize * 0.2f);
		glVertex3f(x, y, z + arrowSize * 1.5f);
		glEnd();
		//mui ten z
		glColor3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(x, y, z + arrowSize * 1.5f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		if (isCube) {
			glutSolidCube(arrowSize * 0.15);
		}
		else
		{
			glutSolidCone(arrowSize * 0.15, arrowSize * 0.7, 10, 10);
		}
		glPopMatrix();
	}

	glEnable(GL_LIGHTING);
	glLineWidth(1.0f);
}
//vẽ 1 mũi tên chỉ hướng,dùng cho điều chỉnh thuộc tính của vật
void drawOneArrowForObject(float x, float y, float z,int whichDirection, int loadName) {
	glDisable(GL_LIGHTING);
	glLineWidth(2.0f);
	//whichDirection cho biết mũi tên được vẽ hướng nào
	//0 là hướng X,1 là hướng Y,2 là hướng Z
	if (loadName != -1) {
		glLoadName(loadName);
	}
	if (whichDirection == 0) {
		//mui ten x
		glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		glTranslatef(x + 2.0f, y, z);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glutSolidCone(0.2, 0.7, 10, 10);
		glPopMatrix();
		glBegin(GL_LINES);
		//duong thang x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(x, y, z);
		glVertex3f(x + 2.0f, y, z);
		glEnd();
	}else if (whichDirection == 1) {
		//mui ten y
		glColor3f(0.0f, 1.0f, 0.0f);
		glPushMatrix();
		glTranslatef(x, y + 2.0f, z);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		glutSolidCone(0.2f, 0.7f, 10, 10);
		glPopMatrix();
		glBegin(GL_LINES);
		//duong thang y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(x, y, z);
		glVertex3f(x, y + 2.0f, z);
		glEnd();
	}
	else
	{
		//mui ten z
		glColor3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glTranslatef(x, y, z + 2.0f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glutSolidCone(0.2f, 0.7f, 10, 10);
		glPopMatrix();
		glBegin(GL_LINES);
		//duong thang z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(x, y, z);
		glVertex3f(x, y, z + 2.0f);
		glEnd();
	}
	glEnable(GL_LIGHTING);
	glLineWidth(1.0f);
}
//vẽ hình tròn dùng cho thao tác xoay vật cũng như các thao tác liên quan đến đường tròn
//vẽ đường tròn để hiển thị
void drawCircleForRotate(int whichAxis, float radius, point centerCircle,int firstItemChoice,int lastItemChoice,bool isMoveLikeClockwise) {
	glDisable(GL_LIGHTING);
	//whichAxis là trục xoay nào 0 là trục x,1 là trục y,2 là trục z
	const float DEG2RAD = 3.14159f / 180;
	float degInRad;
	int i;
	//xoay quanh trục x
	if (whichAxis == 0) {
		float yCircle, zCircle;
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			yCircle = sin(degInRad)*radius + centerCircle.y;
			zCircle = cos(degInRad)*radius + centerCircle.z;
			glVertex3f(centerCircle.x, yCircle, zCircle);
		}
		glEnd();
		//vẽ tam giác để xác định góc quay(nếu firstItemChoice và lastItemChoice khác -1)
		if (firstItemChoice != -1 && lastItemChoice != -1) {
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(centerCircle.x, centerCircle.y, centerCircle.z);
			if (firstItemChoice > lastItemChoice) {
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i < 360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
					for (i = 0; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
				}
				else
				{
					for (i = lastItemChoice; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
				}
			}
			else if (firstItemChoice < lastItemChoice)
			{
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
				}
				else
				{
					for (i = lastItemChoice; i < 360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
					for (i = 0; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						yCircle = sin(degInRad)*radius + centerCircle.y;
						zCircle = cos(degInRad)*radius + centerCircle.z;
						glVertex3f(centerCircle.x, yCircle, zCircle);
					}
				}
			}
			glEnd();
		}
	}
	//xoay quanh trục y
	else if (whichAxis == 1) {
		float xCircle, zCircle;
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = cos(degInRad)*radius + centerCircle.x;
			zCircle = sin(degInRad)*radius + centerCircle.z;
			glVertex3f(xCircle, centerCircle.y, zCircle);
		}
		glEnd();
		//vẽ tam giác để xác định góc quay(nếu firstItemChoice và lastItemChoice khác -1)
		if (firstItemChoice != -1 && lastItemChoice != -1) {
			glColor3f(1.0f, 1.0f, 1.0f);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(centerCircle.x, centerCircle.y, centerCircle.z);
			if (firstItemChoice > lastItemChoice) {
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i < 360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
					for (i = 0; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
				}
				else
				{
					for (i = lastItemChoice; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
				}
			}
			else if (firstItemChoice < lastItemChoice)
			{
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
				}
				else
				{
					for (i = lastItemChoice; i <360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
					for (i = 0; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = cos(degInRad)*radius + centerCircle.x;
						zCircle = sin(degInRad)*radius + centerCircle.z;
						glVertex3f(xCircle, centerCircle.y, zCircle);
					}
				}
			}
			glEnd();
		}
	}
	//xoay quanh trục z
	else
	{
		float xCircle, yCircle;
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.x và y vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = sin(degInRad)*radius + centerCircle.x;
			yCircle = cos(degInRad)*radius + centerCircle.y;
			glVertex3f(xCircle, yCircle, centerCircle.z);
		}
		glEnd();
		//vẽ tam giác để xác định góc quay(nếu firstItemChoice và lastItemChoice khác -1)
		if (firstItemChoice != -1 && lastItemChoice != -1) {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3f(centerCircle.x, centerCircle.y, centerCircle.z);
			if (firstItemChoice > lastItemChoice) {
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i <360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
					for (i = 0; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
				}
				else
				{
					for (i = lastItemChoice; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
				}
			}
			else if (firstItemChoice < lastItemChoice)
			{
				if (isMoveLikeClockwise) {
					for (i = firstItemChoice; i <= lastItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
				}
				else
				{
					for (i = lastItemChoice; i <360; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
					for (i = 0; i <= firstItemChoice; i++) {
						degInRad = (359 - i)*DEG2RAD;
						xCircle = sin(degInRad)*radius + centerCircle.x;
						yCircle = cos(degInRad)*radius + centerCircle.y;
						glVertex3f(xCircle, yCircle, centerCircle.z);
					}
				}
			}
			glEnd();
		}
	}

	glEnable(GL_LIGHTING);
}
//hàm kiểm tra xem chuột nằm gần điểm nào của đường tròng xoay
void getPositionForRotate(int x, int y, float radiusCircle,
	GLdouble *modelMatrix,GLdouble *projectMatrix,GLint *viewport, itemRotateObject &itemRotate,point centerObjectOrVertices) {
	const float DEG2RAD = 3.14159f / 180;
	float degInRad;

	double dt[2];
	//a là vị trí tâm xoay trên màn hình
	//b là vị trí điểm chạm trên màn hình
	double a[3], b[2];
	gluProject((GLdouble)centerObjectOrVertices.x, (GLdouble)centerObjectOrVertices.y, (GLdouble)centerObjectOrVertices.z,
		modelMatrix, projectMatrix, viewport, &a[0], &a[1], &a[2]);
	b[0] = x; b[1] = y;
	//dt[0],dt[1] là 2 giá trị a,b của phương trình đường thẳng đi qua 2 điểm là
	//tâm đường tròn xoay và điểm chạm.Lát ta dùng phương trình đường thằng này để xét,nếu điểm nào(x,y)
	//bỏ vào phương trình đường thẳng này mà thỏa mãn thì nó nằm trên đường thẳng này
	dt[0] = (b[1] - a[1]) / (b[0] - a[0]);
	dt[1] = a[1] - a[0] * dt[0];
	double xWin, yWin, zWin;
	int right;
	int distancePointAndCenter, distancePointAndTouch;
	float xCircle, yCircle, zCircle;
	if (itemRotate.whichCircleChoice == 0) {
		for (int i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			yCircle = sin(degInRad)*radiusCircle + centerObjectOrVertices.y;
			zCircle = cos(degInRad)*radiusCircle + centerObjectOrVertices.z;
			//chuyển điểm này của đường tròn sang tọa độ màn hình
			gluProject((GLdouble)centerObjectOrVertices.x, (GLdouble)yCircle, (GLdouble)zCircle,
				modelMatrix, projectMatrix, viewport, &xWin, &yWin, &zWin);
			//bỏ giá trị x,y vào phương trình đường thẳng,nếu thỏa mãn thì điểm đó nằm trên đường thẳng,cho phép sai số 2 pixel
			right = xWin*dt[0] + dt[1];
			if ((int)yWin == right || (int)yWin == right + 1 || (int)yWin == right - 1) {
				//kiểm tra xem khoảng cách từ điểm đó đến center circle có lớn hơn khoảng cách từ điểm đó đến điểm chạm không
				//nếu lớn hơn nghĩa là nó nằm ở phía bên kia(cũng nằm trên đường thẳng từ tâm đến điểm chạm) của đường tròn
				//chứ k0 phải nằm gần tâm và điểm chạm
				distancePointAndCenter = sqrt(pow(xWin - a[0], 2) + pow(yWin - a[1], 2));
				distancePointAndTouch = sqrt(pow(xWin - x, 2) + pow(yWin - y, 2));
				if (distancePointAndCenter > distancePointAndTouch) {
					//nếu là lần đầu tiên thì đặt giá trị cho cả firstItemChoice luôn
					if (itemRotate.firstItemChoice == -1) {
						itemRotate.firstItemChoice = i;
					}
					//nếu không phải là lần đầu tiên thì tính ra giá trị rotate
					else {
						int choiceNow=0,lastChoice=0;
						//chuyển đổi lại các tọa độ chạm sao cho gốc 0 nằm ở điểm chạm đàu tiên
						if (i >= itemRotate.firstItemChoice) {
							choiceNow = i - itemRotate.firstItemChoice;
						}
						else
						{
							choiceNow = i + (360 - itemRotate.firstItemChoice);
						}
						if (itemRotate.itemChoiceNow >= itemRotate.firstItemChoice) {
							lastChoice = itemRotate.itemChoiceNow - itemRotate.firstItemChoice;
						}
						else
						{
							lastChoice = itemRotate.itemChoiceNow + (360 - itemRotate.firstItemChoice);
						}
						//kiểm tra xem xoay cùng chiều hay ngược chiều kim đồng hồ
						//nếu điểm chạm trước nằm trong khoảng 0->45 mà điểm chạm tiếp theo nằm trong khoảng
						//359->345 nghĩa là xoay ngược chiều kim đồng hồ
						if (lastChoice >= 0 && lastChoice < 45 && choiceNow>315) {
							itemRotate.isRotateLikeClockwise = false;
						}
						//nếu điểm chạm cuối cùng nằm trong khoảng 359->315 hoặc bằng 0 và điểm chạm tiếp
						//theo nằm trong khoảng 1->45
						else if ((lastChoice > 315 || lastChoice == 0) && choiceNow >= 1 && lastChoice < 45) {
							itemRotate.isRotateLikeClockwise = true;
						}
					}
					itemRotate.itemChoiceNow = i;
					break;
				}
			}
		}
	}
	else if (itemRotate.whichCircleChoice == 1) {
		for (int i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = cos(degInRad)*radiusCircle + centerObjectOrVertices.x;
			zCircle = sin(degInRad)*radiusCircle + centerObjectOrVertices.z;
			//chuyển điểm này của đường tròn sang tọa độ màn hình
			gluProject((GLdouble)xCircle, (GLdouble)centerObjectOrVertices.y, (GLdouble)zCircle,
				modelMatrix, projectMatrix, viewport, &xWin, &yWin, &zWin);
			right = xWin*dt[0] + dt[1];
			if ((int)yWin == right || (int)yWin == right + 1 || (int)yWin == right - 1) {
				//kiểm tra xem khoảng cách từ điểm đó đến center circle có lớn hơn khoảng cách từ điểm đó đến điểm chạm không
				//nếu lớn hơn nghĩa là nó nằm ở phía bên kia(cũng nằm trên đường thẳng từ tâm đến điểm chạm) của đường tròn
				//chứ k0 phải nằm gần tâm và điểm chạm
				distancePointAndCenter = sqrt(pow(xWin - a[0], 2) + pow(yWin - a[1], 2));
				distancePointAndTouch = sqrt(pow(xWin - x, 2) + pow(yWin - y, 2));
				if (distancePointAndCenter > distancePointAndTouch) {
					//nếu là lần đầu tiên thì đặt giá trị cho cả firstItemChoice luôn
					if (itemRotate.firstItemChoice == -1) {
						itemRotate.firstItemChoice = i;
					}
					//nếu không phải là lần đầu tiên thì tính ra giá trị rotate
					else {
						int choiceNow = 0, lastChoice = 0;
						//chuyển đổi lại các tọa độ chạm sao cho gốc 0 nằm ở điểm chạm đàu tiên
						if (i >= itemRotate.firstItemChoice) {
							choiceNow = i - itemRotate.firstItemChoice;
						}
						else
						{
							choiceNow = i + (360 - itemRotate.firstItemChoice);
						}
						if (itemRotate.itemChoiceNow >= itemRotate.firstItemChoice) {
							lastChoice = itemRotate.itemChoiceNow - itemRotate.firstItemChoice;
						}
						else
						{
							lastChoice = itemRotate.itemChoiceNow + (360 - itemRotate.firstItemChoice);
						}
						//kiểm tra xem xoay cùng chiều hay ngược chiều kim đồng hồ
						//nếu điểm chạm trước nằm trong khoảng 0->45 mà điểm chạm tiếp theo nằm trong khoảng
						//359->345 nghĩa là xoay ngược chiều kim đồng hồ
						if (lastChoice >= 0 && lastChoice < 45 && choiceNow>315) {
							itemRotate.isRotateLikeClockwise = false;
						}
						//nếu điểm chạm cuối cùng nằm trong khoảng 359->315 hoặc bằng 0 và điểm chạm tiếp
						//theo nằm trong khoảng 1->45
						else if ((lastChoice > 315 || lastChoice == 0) && choiceNow >= 1 && lastChoice < 45) {
							itemRotate.isRotateLikeClockwise = true;
						}
					}
					itemRotate.itemChoiceNow = i;
					break;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 360; i++) {
			degInRad = (359 - i)*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = sin(degInRad)*radiusCircle + centerObjectOrVertices.x;
			yCircle = cos(degInRad)*radiusCircle + centerObjectOrVertices.y;
			//chuyển điểm này của đường tròn sang tọa độ màn hình
			gluProject((GLdouble)xCircle, (GLdouble)yCircle, (GLdouble)centerObjectOrVertices.z,
				modelMatrix, projectMatrix, viewport, &xWin, &yWin, &zWin);
			right = xWin*dt[0] + dt[1];
			if ((int)yWin == right || (int)yWin == right + 1 || (int)yWin == right - 1) {
				//kiểm tra xem khoảng cách từ điểm đó đến center circle có lớn hơn khoảng cách từ điểm đó đến điểm chạm không
				//nếu lớn hơn nghĩa là nó nằm ở phía bên kia(cũng nằm trên đường thẳng từ tâm đến điểm chạm) của đường tròn
				//chứ k0 phải nằm gần tâm và điểm chạm
				distancePointAndCenter = sqrt(pow(xWin - a[0], 2) + pow(yWin - a[1], 2));
				distancePointAndTouch = sqrt(pow(xWin - x, 2) + pow(yWin - y, 2));
				if (distancePointAndCenter > distancePointAndTouch) {
					//nếu là lần đầu tiên thì đặt giá trị cho cả firstItemChoice luôn
					if (itemRotate.firstItemChoice == -1) {
						itemRotate.firstItemChoice = i;
					}
					//nếu không phải là lần đầu tiên thì tính ra giá trị rotate
					else {
						int choiceNow = 0, lastChoice = 0;
						//chuyển đổi lại các tọa độ chạm sao cho gốc 0 nằm ở điểm chạm đàu tiên
						if (i >= itemRotate.firstItemChoice) {
							choiceNow = i - itemRotate.firstItemChoice;
						}
						else
						{
							choiceNow = i + (360 - itemRotate.firstItemChoice);
						}
						if (itemRotate.itemChoiceNow >= itemRotate.firstItemChoice) {
							lastChoice = itemRotate.itemChoiceNow - itemRotate.firstItemChoice;
						}
						else
						{
							lastChoice = itemRotate.itemChoiceNow + (360 - itemRotate.firstItemChoice);
						}
						//kiểm tra xem xoay cùng chiều hay ngược chiều kim đồng hồ
						//nếu điểm chạm trước nằm trong khoảng 0->45 mà điểm chạm tiếp theo nằm trong khoảng
						//359->345 nghĩa là xoay ngược chiều kim đồng hồ
						if (lastChoice >= 0 && lastChoice < 45 && choiceNow>315) {
							itemRotate.isRotateLikeClockwise = false;
						}
						//nếu điểm chạm cuối cùng nằm trong khoảng 359->315 hoặc bằng 0 và điểm chạm tiếp
						//theo nằm trong khoảng 1->45
						else if ((lastChoice > 315 || lastChoice == 0) && choiceNow >= 1 && lastChoice < 45) {
							itemRotate.isRotateLikeClockwise = true;
						}
					}
					itemRotate.itemChoiceNow = i;
					break;
				}
			}
		}
	}
}

//vẽ đường lưới ở mặt đất
void drawNet() {
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
	glLineWidth(1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	int positionX = -30;
	int positionZ = -30;
	for (int i = 0; i < 60; i++) {
		if (i == 30) {
			glLineWidth(3.0f);
			glColor3f(0.0f, 0.0f, 0.0f);
		}
		glBegin(GL_LINES);
		glVertex3f(positionX, 0, -30);
		glVertex3f(positionX, 0, 29);
		positionX++;
		glVertex3f(-30, 0, positionZ);
		glVertex3f(29, 0, positionZ);
		positionZ++;
		glEnd();
		if (i == 30) {
			glColor3f(1.0f, 1.0f, 1.0f);
			glLineWidth(1.0f);
		}
	}
	
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}
//các hàm vẽ hình
//hàm hiển thị tam giác đã định nghĩa trong mảng
void DrawTriangles(GLenum mode, vector<TriangleAttribute*> triangleArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!triangleArray.empty()) {
		point normal, v;
		bool isDraw = false;
		int numberItemChoice = itemsChoice.size(), numberObject = triangleArray.size(), i, k;
		for (i = 0; i < numberObject; i++) {
			TriangleAttribute  *tria = triangleArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (k = 0; k < numberItemChoice; k++) {
					if (tria->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw==2) {
				for (k = 0; k < numberItemChoice; k++) {
					if (tria->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(tria->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (tria->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, tria->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(tria->colorR, tria->colorG, tria->colorB, tria->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, tria->mShiness);
			}
			normal = tria->getNormalVector();
			glBegin(GL_TRIANGLES);
			glNormal3f(normal.x, normal.y, normal.z);
			for (int i = 0; i < 3; i++) {
				v = tria->getVertexAtIndex(i);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			if (tria->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị tam giác liên tục(tringle strip) đã định nghĩa trong mảng
void DrawTriangleStrip(GLenum mode, vector<TriangleStripAttribute*> triaStripArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!triaStripArray.empty()) {
		point normal, v;
		int numberVertex, numberItemChoice = itemsChoice.size(), numberObject = triaStripArray.size(), i, j, k;
		bool isDraw = false;
		for (i = 0; i < numberObject; i++) {
			TriangleStripAttribute  *triaStrip = triaStripArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (k = 0; k < numberItemChoice; k++) {
					if (triaStrip->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (k = 0; k < numberItemChoice; k++) {
					if (triaStrip->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(triaStrip->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (triaStrip->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, triaStrip->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(triaStrip->colorR, triaStrip->colorG, triaStrip->colorB, triaStrip->colorA);

				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, triaStrip->mShiness);
			}
			//nếu đang ở chế độ bo cạnh thì dùng các vertex và normal bo cạnh
			if (isRoundCorner) {
				glBegin(GL_TRIANGLE_STRIP);
				numberVertex = triaStrip->vertexArrayRound.size();
				for (j = 0; j < numberVertex; j++) {
					normal = triaStrip->normalVectorRound.at(j);
					v = triaStrip->vertexArrayRound.at(j);
					//mỗi đỉnh có 1 normal vector
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(v.x, v.y, v.z);
				}
				glEnd();
			}
			else
			{
				glBegin(GL_TRIANGLE_STRIP);
				numberVertex = triaStrip->vertexArray.size();
				for (j = 0; j < numberVertex; j++) {
					normal = triaStrip->normalVector.at(j);
					v = triaStrip->vertexArray.at(j);
					//mỗi đỉnh có 1 normal vector
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(v.x, v.y, v.z);
				}
				glEnd();
			}
			
			if (triaStrip->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị tam giác quạt(tringle fan) đã định nghĩa trong mảng
void DrawTriangleFan(GLenum mode, vector<TriangleFanAttribute*> triaFanArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!triaFanArray.empty()) {
		point normal, v;
		int numberVertex, numberItemChoice = itemsChoice.size(), numberObject = triaFanArray.size(), i, j, k;
		bool isDraw = false;
		for (i = 0; i < numberObject; i++) {
			TriangleFanAttribute  *triaFan = triaFanArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (k = 0; k < numberItemChoice; k++) {
					if (triaFan->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (k = 0; k < numberItemChoice; k++) {
					if (triaFan->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(triaFan->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (triaFan->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, triaFan->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(triaFan->colorR, triaFan->colorG, triaFan->colorB, triaFan->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, triaFan->mShiness);
			}
			glBegin(GL_TRIANGLE_FAN);
			numberVertex = triaFan->vertexArray.size();
			for (j = 0; j < numberVertex; j++) {
				normal = triaFan->normalVector.at(j);
				v = triaFan->vertexArray.at(j);
				//mỗi đỉnh có 1 normal vector
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			if (triaFan->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//vẽ các hình cầu đã định nghĩa ở trong các mảng sphere array
void DrawSphere(GLenum mode, vector<SphereAttribute*> sphereArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!sphereArray.empty()) {
		point v0, v1, normal;
		int offsetLast, offsetNow, minusLatitude = 0, minusLongitude = 0, numberItemChoice = itemsChoice.size(),
			numberObject= sphereArray.size(),i,m,n,k;
		bool isDraw = false;
		for (i = 0; i < numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (k = 0; k < numberItemChoice; k++) {
					if (sphere->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (k = 0; k < numberItemChoice; k++) {
					if (sphere->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(sphere->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (sphere->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, sphere->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(sphere->colorR, sphere->colorG, sphere->colorB, sphere->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, sphere->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (sphere->vertexArray.empty()) {
				CaculatorSphere(sphere->radius, sphere->numberLongitude, sphere->numberLatitude, sphere->centerObject,
					sphere->vertexArray);
				CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);
			}
			if (isRoundCorner) {
				minusLatitude = (360 - sphere->degreeLatitudeLimit) * (sphere->numberLatitudeRound / 360.0);
				minusLongitude = (360 - sphere->degreeLongitudeLimit) * (sphere->numberLongitudeRound / 360.0);

				for (m = 1; m < sphere->numberLatitudeRound - minusLatitude; m++) {
					offsetLast = (m - 1) * sphere->numberLongitudeRound;
					offsetNow = m * sphere->numberLongitudeRound;
					glBegin(GL_TRIANGLE_STRIP);
					for (n = minusLongitude; n < sphere->numberLongitudeRound; n++) {
						v0 = sphere->vertexArrayRound.at(offsetLast + n);
						normal = sphere->normalVectorRound.at(offsetLast + n);
						glNormal3f(normal.x, normal.y, normal.z);
						glVertex3f(v0.x, v0.y, v0.z);
						v1 = sphere->vertexArrayRound.at(offsetNow + n);
						normal = sphere->normalVectorRound.at(offsetNow + n);
						glNormal3f(normal.x, normal.y, normal.z);
						glVertex3f(v1.x, v1.y, v1.z);
						//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
						if (n == sphere->numberLongitudeRound - 1) {
							v0 = sphere->vertexArrayRound.at(offsetLast);
							normal = sphere->normalVectorRound.at(offsetLast);
							glNormal3f(normal.x, normal.y, normal.z);
							glVertex3f(v0.x, v0.y, v0.z);
							v1 = sphere->vertexArrayRound.at(offsetNow);
							normal = sphere->normalVectorRound.at(offsetNow);
							glNormal3f(normal.x, normal.y, normal.z);
							glVertex3f(v1.x, v1.y, v1.z);
						}
					}
					glEnd();
				}
			}
			else
			{
				minusLatitude = (360 - sphere->degreeLatitudeLimit) * (sphere->numberLatitude / 360.0);
				minusLongitude = (360 - sphere->degreeLongitudeLimit) * (sphere->numberLongitude / 360.0);

				for (m = 1; m < sphere->numberLatitude - minusLatitude; m++) {
					offsetLast = (m - 1) * sphere->numberLongitude;
					offsetNow = m * sphere->numberLongitude;
					glBegin(GL_TRIANGLE_STRIP);
					for (n = minusLongitude; n < sphere->numberLongitude; n++) {
						v0 = sphere->vertexArray.at(offsetLast + n);
						normal = sphere->normalVector.at(offsetLast + n);
						glNormal3f(normal.x, normal.y, normal.z);
						glVertex3f(v0.x, v0.y, v0.z);
						v1 = sphere->vertexArray.at(offsetNow + n);
						normal = sphere->normalVector.at(offsetNow + n);
						glNormal3f(normal.x, normal.y, normal.z);
						glVertex3f(v1.x, v1.y, v1.z);
						//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
						if (n == sphere->numberLongitude - 1) {
							v0 = sphere->vertexArray.at(offsetLast);
							normal = sphere->normalVector.at(offsetLast);
							glNormal3f(normal.x, normal.y, normal.z);
							glVertex3f(v0.x, v0.y, v0.z);
							v1 = sphere->vertexArray.at(offsetNow);
							normal = sphere->normalVector.at(offsetNow);
							glNormal3f(normal.x, normal.y, normal.z);
							glVertex3f(v1.x, v1.y, v1.z);
						}
					}
					glEnd();
				}
			}
			
			if (sphere->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//vẽ hình chữ nhật bo tròn
void DrawCubeRound(GLenum mode, vector<CubeRoundAttribute*> cubeRoundArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!cubeRoundArray.empty()) {
		point v0, v1, normal;
		int offsetLast, offsetNow, numberVertex, numberItemChoice = itemsChoice.size(), numberObject = cubeRoundArray.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			CubeRoundAttribute  *cube = cubeRoundArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cube->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cube->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(cube->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (cube->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cube->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(cube->colorR, cube->colorG, cube->colorB, cube->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, cube->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (cube->vertexArray.empty()) {
				CaculatorCubeRound(cube->xLength,cube->yLength,cube->zLength, cube->numberLongitude, cube->numberLatitude, cube->centerObject,
					 cube->radiusRound,cube->vertexArray);
				CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);
			}
			numberVertex = cube->vertexArray.size();
			glBegin(GL_TRIANGLE_STRIP);
			for (int i = 1; i < cube->numberLatitude; i++) {
				offsetLast = (i - 1) * cube->numberLongitude;
				offsetNow = i * cube->numberLongitude;
				for (int j = 0; j < cube->numberLongitude; j++) {
					v0 = cube->vertexArray.at(offsetLast + j);
					normal = cube->normalVector.at(offsetLast + j);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(v0.x, v0.y, v0.z);
					v1 = cube->vertexArray.at(offsetNow + j);
					normal = cube->normalVector.at(offsetNow + j);
					glNormal3f(normal.x, normal.y, normal.z);
					glVertex3f(v1.x, v1.y, v1.z);
				}
			}
			glEnd();
			if (cube->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình hộp(cube) đã định nghĩa trong mảng
void DrawCube(GLenum mode, vector<CubeAttribute*> cubeArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!cubeArray.empty()) {
		point v0, v1, v2, normal;
		int offset1, offset2, offset3, offsetNormal, numberVertexInRow,
			numberCube = cubeArray.size(), numberItemChoice = itemsChoice.size();
		bool isDraw = false;
		for (int k = 0; k < numberCube; k++) {
			CubeAttribute  *cube = cubeArray.at(k);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cube->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cube->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(cube->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (cube->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cube->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(cube->colorR, cube->colorG, cube->colorB, cube->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, cube->mShiness);
			}

			if (cube->normalVector.empty()) {
				//nếu chưa tính normal thì phải tính
				CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
					, cube->vertexArray, cube->normalVector);
			}
			offsetNormal = 0;
			numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
			glBegin(GL_TRIANGLES);
			for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
				offset1 = i * numberVertexInRow;
				offset2 = (i + 1) * numberVertexInRow;
				for (int j = 1; j < numberVertexInRow; j++) {
					v0 = cube->vertexArray.at(offset1 + j - 1);
					v1 = cube->vertexArray.at(offset2 + j - 1);
					v2 = cube->vertexArray.at(offset1 + j);
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;
					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v2.x, v2.y, v2.z);
					v0 = cube->vertexArray.at(offset2 + j);
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;
					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v0.x, v0.y, v0.z);
					if (j == numberVertexInRow - 1) {
						//nếu là đến đỉnh cuối thì vẽ nối với đỉnh đầu
						v1 = cube->vertexArray.at(offset1);
						normal = cube->normalVector.at(offsetNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						offsetNormal++;
						glVertex3f(v2.x, v2.y, v2.z);
						glVertex3f(v0.x, v0.y, v0.z);
						glVertex3f(v1.x, v1.y, v1.z);
						v2 = cube->vertexArray.at(offset2);
						normal = cube->normalVector.at(offsetNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						offsetNormal++;
						glVertex3f(v1.x, v1.y, v1.z);
						glVertex3f(v0.x, v0.y, v0.z);
						glVertex3f(v2.x, v2.y, v2.z);
					}
				}
			}
			//các offset dùng nhiều
			offset1 = cube->numberVertexInAxisX + cube->numberVertexInAxisZ + cube->numberVertexInAxisX - 3;
			//điểm đầu tiên của vertexUp(tức là cụm các đỉnh nằm phía trong)
			offset2 = numberVertexInRow*cube->numberVertexInAxisY;
			//vẽ mặt trên của hình khối
			for (int i = 1; i < cube->numberVertexInAxisZ; i++) {
				for (int j = 1; j < cube->numberVertexInAxisX; j++) {
					//tính đỉnh v0
					if (i == cube->numberVertexInAxisZ - 1) {
						v0 = cube->vertexArray.at(offset1 - (j - 1));
					}
					else
					{
						if (j == 1) {
							v0 = cube->vertexArray.at(numberVertexInRow - i);
						}
						else
						{
							v0 = cube->vertexArray.at(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 2));
						}
					}
					//tính đỉnh v1
					if (i == 1) {
						v1 = cube->vertexArray.at(j - 1);
					}
					else
					{
						if (j == 1) {
							v1 = cube->vertexArray.at(numberVertexInRow - (i - 1));
						}
						else
						{
							v1 = cube->vertexArray.at(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
						}
					}
					//tính đỉnh v2
					if (i == cube->numberVertexInAxisZ - 1) {
						v2 = cube->vertexArray.at(offset1 - j);
					}
					else
					{
						if (j == cube->numberVertexInAxisX - 1) {
							v2 = cube->vertexArray.at(cube->numberVertexInAxisX - 1 + i);
						}
						else
						{
							v2 = cube->vertexArray.at(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
						}
					}
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;

					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v2.x, v2.y, v2.z);

					//tính đỉnh v3
					if (i == 1) {
						v0 = cube->vertexArray.at(j);
					}
					else
					{
						if (j == cube->numberVertexInAxisX - 1) {
							v0 = cube->vertexArray.at(cube->numberVertexInAxisX - 1 + (i - 1));
						}
						else
						{
							v0 = cube->vertexArray.at(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 1));
						}
					}
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;

					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}

			//các offset dùng nhiều
			offset1 = cube->numberVertexInAxisX + cube->numberVertexInAxisZ + cube->numberVertexInAxisX - 3;
			//điểm đầu tiên của vertexDown(tức là cụm các đỉnh nằm phía trong)
			offset2 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
			//vị trí đầu tiên của vòng đỉnh ngoài phía dưới cùng
			offset3 = (cube->numberVertexInAxisY - 1)*numberVertexInRow;
			//vẽ các mặt dưới của hình khối
			for (int i = 1; i < cube->numberVertexInAxisZ; i++) {
				for (int j = 1; j < cube->numberVertexInAxisX; j++) {
					//tính đỉnh v0
					if (i == cube->numberVertexInAxisZ - 1) {
						v0 = cube->vertexArray.at(offset3 + offset1 - (j - 1));
					}
					else
					{
						if (j == 1) {
							v0 = cube->vertexArray.at(offset3 + numberVertexInRow - i);
						}
						else
						{
							v0 = cube->vertexArray.at(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 2));
						}
					}
					//tính đỉnh v1
					if (i == 1) {
						v1 = cube->vertexArray.at(offset3 + j - 1);
					}
					else
					{
						if (j == 1) {
							v1 = cube->vertexArray.at(offset3 + numberVertexInRow - (i - 1));
						}
						else
						{
							v1 = cube->vertexArray.at(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
						}
					}
					//tính đỉnh v2
					if (i == cube->numberVertexInAxisZ - 1) {
						v2 = cube->vertexArray.at(offset3 + offset1 - j);
					}
					else
					{
						if (j == cube->numberVertexInAxisX - 1) {
							v2 = cube->vertexArray.at(offset3 + cube->numberVertexInAxisX - 1 + i);
						}
						else
						{
							v2 = cube->vertexArray.at(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
						}
					}
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;

					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v0.x, v0.y, v0.z);

					//tính đỉnh v3
					if (i == 1) {
						v0 = cube->vertexArray.at(offset3 + j);
					}
					else
					{
						if (j == cube->numberVertexInAxisX - 1) {
							v0 = cube->vertexArray.at(offset3 + cube->numberVertexInAxisX - 1 + (i - 1));
						}
						else
						{
							v0 = cube->vertexArray.at(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 1));
						}
					}
					normal = cube->normalVector.at(offsetNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					offsetNormal++;

					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v2.x, v2.y, v2.z);
				}
			}

			glEnd();

			if (cube->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình nón mượt(cone) đã định nghĩa trong mảng
void DrawCone(GLenum mode, vector<ConeAttribute*> coneArray,itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!coneArray.empty()) {
		point v0, normal;
		int offsetLast, offsetNow, minusLatitude = 0, minusLongitude = 0, positionNextNormal,
			numberItemChoice = itemsChoice.size(), numberObject = coneArray.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			positionNextNormal = 0;
			ConeAttribute  *cone = coneArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cone->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cone->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(cone->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (cone->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cone->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(cone->colorR, cone->colorG, cone->colorB, cone->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, cone->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (cone->vertexArray.empty()) {
				caculatorCone(cone->centerObject,cone->radius,cone->height, cone->numberLongitude, cone->numberLatitude,
					cone->vertexArray);
				CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
			}
			if (isRoundCorner) {
				minusLatitude = (360 - cone->degreeLatitudeLimit) * (cone->numberLatitudeRound / 360.0);
				minusLongitude = (360 - cone->degreeLongitudeLimit) * (cone->numberLongitudeRound / 360.0);
				for (int i = 1; i < cone->numberLatitudeRound - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cone->numberLongitudeRound;
					offsetNow = i * cone->numberLongitudeRound;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cone->numberLongitudeRound; j++) {
						normal = cone->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cone->vertexArrayRound.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cone->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cone->vertexArrayRound.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cone->numberLongitudeRound - 1) {
							normal = cone->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cone->vertexArrayRound.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cone->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cone->vertexArrayRound.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
			}
			else
			{
				minusLatitude = (360 - cone->degreeLatitudeLimit) * (cone->numberLatitude / 360.0);
				minusLongitude = (360 - cone->degreeLongitudeLimit) * (cone->numberLongitude / 360.0);
				for (int i = 1; i < cone->numberLatitude - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cone->numberLongitude;
					offsetNow = i * cone->numberLongitude;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cone->numberLongitude; j++) {
						normal = cone->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cone->vertexArray.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cone->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cone->vertexArray.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cone->numberLongitude - 1) {
							normal = cone->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cone->vertexArray.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cone->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cone->vertexArray.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
			}
			
			if (cone->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình trụ tròn(cylinder) đã định nghĩa trong mảng
void DrawCylinder(GLenum mode, vector<CylinderAttribute*> cylinderArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!cylinderArray.empty()) {
		point v0, normal;
		int offsetLast, offsetNow, minusLatitude=0, minusLongitude=0, positionNextNormal,
			numberItemChoice = itemsChoice.size(),numberObject= cylinderArray.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			positionNextNormal = 0;
			CylinderAttribute  *cylinder = cylinderArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cylinder->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cylinder->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(cylinder->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (cylinder->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cylinder->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(cylinder->colorR, cylinder->colorG, cylinder->colorB, cylinder->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, cylinder->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (cylinder->vertexArray.empty()) {
				caculatorCylinder(cylinder->centerObject, cylinder->radiusUp,cylinder->radiusDown, cylinder->height,
					cylinder->numberLongitude, cylinder->numberLatitude,cylinder->vertexArray);
				CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
			if (isRoundCorner) {
				minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitudeRound / 360.0);
				minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitudeRound / 360.0);

				for (int i = 1; i < cylinder->numberLatitudeRound - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cylinder->numberLongitudeRound;
					offsetNow = i * cylinder->numberLongitudeRound;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cylinder->numberLongitudeRound; j++) {
						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cylinder->numberLongitudeRound - 1) {
							normal = cylinder->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArrayRound.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cylinder->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArrayRound.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
			}
			else
			{
				minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
				minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);

				for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cylinder->numberLongitude;
					offsetNow = i * cylinder->numberLongitude;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cylinder->numberLongitude - 1) {
							normal = cylinder->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArray.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cylinder->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArray.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
			}
			
			if (cylinder->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình kim tự tháp(pyramid) đã định nghĩa trong mảng
void DrawPyramid(GLenum mode, vector<PyramidAttribute*> pyrArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!pyrArray.empty()) {
		int numberItemChoice = itemsChoice.size(),numberObject= pyrArray.size();
		bool isDraw = false;
		//mảng chứa các giá trị đỉnh theo thứ tự của pyramid
		int vertexArrayPyr[][3]{
			{ 0,1,2 },{ 0,2,3 },{ 0,3,4 },{ 0,4,1 },{1,4,2},{2,4,3}
		};
		point v0, v1, v2, normal;
		for (int i = 0; i < numberObject; i++) {
			PyramidAttribute  *pyr = pyrArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (pyr->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (pyr->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(pyr->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (pyr->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, pyr->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(pyr->colorR, pyr->colorG, pyr->colorB, pyr->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, pyr->mShiness);
			}
			glBegin(GL_TRIANGLES);
			//vẽ từng mặt pyramid
			//có 4 mặt hình tam giác và 1 mặt đáy hình vuông được vẽ từ 2 hình tam giác ghép lai lại
			for (int i = 0; i < 6; i++) {
				normal = pyr->getNormalVectorAtIndex(i);
				glNormal3f(normal.x, normal.y, normal.z);
				v0 = pyr->getVertexAtIndex(vertexArrayPyr[i][0]);
				v1 = pyr->getVertexAtIndex(vertexArrayPyr[i][1]);
				v2 = pyr->getVertexAtIndex(vertexArrayPyr[i][2]);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			glEnd();
			if (pyr->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình trụ tròn rỗng trong(cylinder2) đã định nghĩa trong mảng
void DrawEmptyCylinder(GLenum mode, vector<EmptyCylinderAttribute*> emptyCylinderArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!emptyCylinderArray.empty()) {
		point v0, normal;
		int offsetLast, offsetNow, minusLatitude = 0, minusLongitude = 0, positionNextNormal,
			numberItemChoice = itemsChoice.size(), numberObject = emptyCylinderArray.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			positionNextNormal = 0;
			EmptyCylinderAttribute  *cylinder = emptyCylinderArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cylinder->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (cylinder->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(cylinder->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (cylinder->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, cylinder->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(cylinder->colorR, cylinder->colorG, cylinder->colorB, cylinder->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, cylinder->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (cylinder->vertexArray.empty()) {
				caculatorEmptyCylinder(cylinder->centerObject, cylinder->radiusUpOut, cylinder->radiusDownOut,
					cylinder->radiusUpIn, cylinder->radiusDownIn, cylinder->height,cylinder->numberLongitude,
					cylinder->numberLatitude, cylinder->vertexArray);
				CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
			if (isRoundCorner) {
				minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitudeRound / 360.0);
				minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitudeRound / 360.0);
				for (int i = 1; i < cylinder->numberLatitudeRound - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cylinder->numberLongitudeRound;
					offsetNow = i * cylinder->numberLongitudeRound;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cylinder->numberLongitudeRound; j++) {
						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cylinder->numberLongitudeRound - 1) {
							normal = cylinder->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArrayRound.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cylinder->normalVectorRound.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArrayRound.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
				//vẽ vòng bao trong emptyCylinder
				offsetLast = 0;
				offsetNow = cylinder->vertexArrayRound.size() - cylinder->numberLongitudeRound;

				//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
				positionNextNormal += minusLongitude * 2;

				glBegin(GL_TRIANGLE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitudeRound; j++) {
					normal = cylinder->normalVectorRound.at(positionNextNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					positionNextNormal++;
					v0 = cylinder->vertexArrayRound.at(offsetLast + j);
					glVertex3f(v0.x, v0.y, v0.z);

					normal = cylinder->normalVectorRound.at(positionNextNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					positionNextNormal++;
					v0 = cylinder->vertexArrayRound.at(offsetNow + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
					if (j == cylinder->numberLongitudeRound - 1) {
						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetLast);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArrayRound.at(offsetNow);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();

			}
			else
			{
				minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
				minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);
				for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
					//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
					positionNextNormal += minusLongitude * 2;

					offsetLast = (i - 1) * cylinder->numberLongitude;
					offsetNow = i * cylinder->numberLongitude;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
						//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
						if (j == cylinder->numberLongitude - 1) {
							normal = cylinder->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArray.at(offsetNow);
							glVertex3f(v0.x, v0.y, v0.z);

							normal = cylinder->normalVector.at(positionNextNormal);
							glNormal3f(normal.x, normal.y, normal.z);
							positionNextNormal++;
							v0 = cylinder->vertexArray.at(offsetLast);
							glVertex3f(v0.x, v0.y, v0.z);
						}
					}
					glEnd();
				}
				//vẽ vòng bao trong emptyCylinder
				offsetLast = 0;
				offsetNow = cylinder->vertexArray.size() - cylinder->numberLongitude;

				//tăng giá trị next normal mỗi lần nếu có vertex k0 cần hiển thị
				positionNextNormal += minusLongitude * 2;

				glBegin(GL_TRIANGLE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
					normal = cylinder->normalVector.at(positionNextNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					positionNextNormal++;
					v0 = cylinder->vertexArray.at(offsetLast + j);
					glVertex3f(v0.x, v0.y, v0.z);

					normal = cylinder->normalVector.at(positionNextNormal);
					glNormal3f(normal.x, normal.y, normal.z);
					positionNextNormal++;
					v0 = cylinder->vertexArray.at(offsetNow + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là cặp dỉnh cuối cùng thì nối nó với cặp đỉnh đầu tiên luôn
					if (j == cylinder->numberLongitude - 1) {
						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetLast);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = cylinder->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = cylinder->vertexArray.at(offsetNow);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
			}

			if (cylinder->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}

//vẽ các hình vòng xe(bánh rán)
void DrawTorus(GLenum mode, vector<TorusAttribute*> torusArray, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!torusArray.empty()) {
		point v, normal;
		int numberItemChoice = itemsChoice.size(), numberObject = torusArray.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (torus->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (torus->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(torus->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (torus->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, torus->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(torus->colorR, torus->colorG, torus->colorB, torus->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, torus->mShiness);
			}
			//nếu chưa được tính thì tính ra rồi mới hiển thị
			if (torus->vertexArray.empty()) {
				caculatorTorus(torus->radiusCake, torus->radiusRoundCake,torus->widthCake, torus->depthCake, torus->depthRoundCake,
					torus->centerObject, torus->vertexArray);
				CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
			}
			int numbervertex = torus->vertexArray.size();
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 0; j < numbervertex; j++) {
				v = torus->vertexArray.at(j);
				normal = torus->normalVector.at(j);
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			if (torus->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}
//hàm hiển thị hình ảnh đã định nghĩa trong mảng
void DrawPictures(GLenum mode, vector<PictureAttribute*> pictureArray, itemTextureObject itemTexture,
	int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!pictureArray.empty()) {
		int numberItemChoice = itemsChoice.size(), numberObject = pictureArray.size();
		bool isDraw = false;
		float textureCoord[][2] = {
			{0.0,0.0},{0.0,1.0},{1.0,1.0},{1.0,0.0}
		};
		point normal, v;
		glDisable(GL_LIGHTING);
		for (int i = 0; i < numberObject; i++) {
			PictureAttribute  *picture = pictureArray.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (picture->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (picture->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(picture->id);
			}
			else
			{
				//hình ảnh thì luôn có kết cấu để hiển thị
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, picture->idTexture + itemTexture.startNameTexture);
				glColor3f(1.0, 1.0, 1.0);
			}
			glBegin(GL_TRIANGLE_FAN);
			for (int i = 0; i < 4; i++) {
				normal = picture->normalVector[i];
				glNormal3f(normal.x, normal.y, normal.z);
				v = picture->vertexArray[i];
				glTexCoord2f(textureCoord[i][0], textureCoord[i][1]);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		glEnable(GL_LIGHTING);
	}
}
//hàm hiển thị ObjectCustom0 đã định nghĩa trong mảng
//nó cũng tương tự như sphere,cone,.. chỉ có là cụm đỉnh đầu và cuối không nối với nhau
//và đỉnh cuối cùng của 1 cụm không vẽ nối với đỉnh đầu tiên
void DrawObjectCustom0(GLenum mode, vector<ObjectCustom0Attribute*> objectCustom0Array, itemTextureObject itemTexture,
	bool isRoundCorner, int whichStyleDraw, vector<itemChoice> itemsChoice) {
	if (!objectCustom0Array.empty()) {
		point v0, normal;
		int offsetLast, offsetNow, positionNextNormal,
			numberItemChoice = itemsChoice.size(), numberObject = objectCustom0Array.size();
		bool isDraw = false;
		for (int i = 0; i < numberObject; i++) {
			positionNextNormal = 0;
			ObjectCustom0Attribute  *object = objectCustom0Array.at(i);
			//nếu bằng 0 là vẽ bình thường,1 là chỉ vẽ các vật đang được chọn,2 là chỉ vẽ các vật không được chọn
			if (whichStyleDraw == 1) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (object->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu không phải là hình đang được chọn thì bỏ qua
				if (!isDraw) {
					continue;
				}
				//nếu là hình đang được chọn thì vẽ tiếp
				else {
					isDraw = false;
				}
			}
			else if (whichStyleDraw == 2) {
				for (int k = 0; k < numberItemChoice; k++) {
					if (object->id == itemsChoice.at(k).id) {
						isDraw = true;
						break;
					}
				}
				//nếu là hình đang được chọn thì không vẽ nữa,kiểm tra hình tiếp theo
				if (isDraw) {
					isDraw = false;
					continue;
				}
			}

			if (mode == GL_SELECT) {
				//glLoadName phải gọi trươc khi vẽ vật và trước cả hàm glBegin();
				glLoadName(object->id);
			}
			else
			{
				//nêu có texture thì khỏi đặt màu vì có đặt cũng chẳng ảnh hưởng
				if (object->idTexture != -1) {
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, object->idTexture + itemTexture.startNameTexture);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
					glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
				}
				else
				{
					glColor4f(object->colorR, object->colorG, object->colorB, object->colorA);
				}
				
				glMaterialf(GL_FRONT, GL_SHININESS, object->mShiness);
			}
			//nếu chưa tính vertex array hay normal thì tính ra rồi mới vẽ
			if (object->vertexArray.empty()) {
				caculatorObjectCustom0(object->numberLongitude, object->numberLatitude,
					object->lengthBetween2Row, object->lengthBetween2Column, object->centerObject, object->vertexArray);
				CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
					object->vertexArray, object->normalVector);
			}
			
			if (isRoundCorner) {
				for (int i = 1; i < object->numberLatitudeRound; i++) {
					offsetLast = (i - 1) * object->numberLongitudeRound;
					offsetNow = i * object->numberLongitudeRound;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = 0; j < object->numberLongitudeRound; j++) {
						normal = object->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = object->vertexArrayRound.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = object->normalVectorRound.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = object->vertexArrayRound.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
					}
					glEnd();
				}
			}
			else
			{
				for (int i = 1; i < object->numberLatitude; i++) {
					offsetLast = (i - 1) * object->numberLongitude;
					offsetNow = i * object->numberLongitude;
					glBegin(GL_TRIANGLE_STRIP);
					for (int j = 0; j < object->numberLongitude; j++) {
						normal = object->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = object->vertexArray.at(offsetNow + j);
						glVertex3f(v0.x, v0.y, v0.z);

						normal = object->normalVector.at(positionNextNormal);
						glNormal3f(normal.x, normal.y, normal.z);
						positionNextNormal++;
						v0 = object->vertexArray.at(offsetLast + j);
						glVertex3f(v0.x, v0.y, v0.z);
					}
					glEnd();
				}
			}

			if (object->idTexture != -1) {
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_TEXTURE_GEN_S);
				glDisable(GL_TEXTURE_GEN_T);
			}
		}
	}
}

//các hàm dùng cho tính bo tròn hình cầu

//trả về một điểm nằm trên A,B,cách một khoảng cách nhất định từ A.(3D)
void normalizeWithRadius(float *a, float *b, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b[0] - a[0];
		float dy = b[1] - a[1];
		float dz = b[2] - a[2];
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		dz = dz*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		b[0] = a[0] + dx;
		b[1] = a[1] + dy;
		b[2] = a[2] + dz;
		if (isnan(b[0]) || isnan(b[1]) || isnan(b[2])) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		b[0] = a[0];
		b[1] = a[1];
		b[2] = a[2];
	}
}
void normalizeWithRadius(point a, point &b, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		dz = dz*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		b.x = a.x + dx;
		b.y = a.y + dy;
		b.z = a.z + dz;
		if (isnan(b.x) || isnan(b.y) || isnan(b.z)) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		b.x = a.x;
		b.y = a.y;
		b.z = a.z;
	}
}
void normalizeWithRadius(point a, point b,point &out, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		float dz = b.z - a.z;
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		dz = dz*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		out.x = a.x + dx;
		out.y = a.y + dy;
		out.z = a.z + dz;
		if (isnan(out.x) || isnan(out.y) || isnan(out.z)) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		out.x = a.x;
		out.y = a.y;
		out.z = a.z;
	}
}
//trả về một điểm nằm trên A,B,cách một khoảng cách nhất định từ A.(2D)
void normalizeWithRadius2D(double *a, double *b, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b[0] - a[0];
		float dy = b[1] - a[1];
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		b[0] = a[0] + dx;
		b[1] = a[1] + dy;
		if (isnan(b[0]) || isnan(b[1])) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		b[0] = a[0];
		b[1] = a[1];
	}
}
void normalizeWithRadius2D(float *a, float *b,float *c, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b[0] - a[0];
		float dy = b[1] - a[1];
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		c[0] = a[0] + dx;
		c[1] = a[1] + dy;
		if (isnan(c[0]) || isnan(c[1])) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		c[0] = a[0];
		c[1] = a[1];
	}
}
void normalizeWithRadius2D(point a, point &b, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		b.x = a.x + dx;
		b.y = a.y + dy;
		if (isnan(b.x) || isnan(b.y)) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		b.x = a.x;
		b.y = a.y;
	}
}
void normalizeWithRadius2D(point a, point b, point &out, float length) {
	//nên để trong hàm kiểm tra ngoại lệ để đề phóng lỗi
	try {
		//length ở đây chính là bán kính
		//lấy khoảng cách giữa a và b dọc theo trục x,y và z
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		//tính khoảng cách giữa 2 điểm trong không gian 3 chiều
		float distanceA_B = sqrt(pow(dx, 2) + pow(dy, 2));
		if (distanceA_B == 0.0) {
			throw 1;
		}
		//đoạn tiếp theo tính tỉ lệ khoảng cách theo chiều x của ab so với khoảng cách thực của ab
		//sau đó nhân tỉ lệ này với khoảng cách thực của ac(lenghth) thì ra khoảng cách theo chiều x của ac
		//tương tự với trục y và z
		dx = dx*length / distanceA_B;
		dy = dy*length / distanceA_B;
		//tính ra vị trí của điểm c từ khoảng cách vừa tính ra
		out.x = a.x + dx;
		out.y = a.y + dy;
		if (isnan(out.x) || isnan(out.y)) {
			throw 1;
		}
	}
	catch (...) {
		//nếu tính giá trị bị lỗi thì đặt nó bằng giá trị a luôn
		out.x = a.x;
		out.y = a.y;
	}
}
//tìm các điểm nằm giữa 2 điểm(mảng sẽ tìm bắt đầu từ điểm gần nhất với first tới điểm xa first nhất)
void findPointsBetweenTwoPoint(point first, point last, int numberElement, point *arrayOut) {
	//tìm ra khoảng cách giữa 2 điểm gần nhất khi đã thêm các đỉnh con vào giữa 
	float distance = 0.0,distanceToFirst=0.0;
	distance = distanceTwoPoint(first, last) / (numberElement + 1);
	if (isnan(distance)) {
		distance = 0.0;
	}
	for (int i = 0; i < numberElement; i++) {
		distanceToFirst += distance;
		//tìm ra các điểm nằm trên đường thẳng first,last và cách first một khoảng distanceToFirst
		normalizeWithRadius(first, last, arrayOut[i], distanceToFirst);
	}
}
//hàm này khác hàm trên là có vị trí bắt đầu đầu tiên trong mảng chứ không phải chỉ bắt đầu từ 0
void findPointsBetweenTwoPoint(point first, point last, int numberElement, point *arrayOut,int offsetArrayOut) {
	//tìm ra khoảng cách giữa 2 điểm gần nhất khi đã thêm các đỉnh con vào giữa 
	float distance = 0.0, distanceToFirst = 0.0;
	distance = distanceTwoPoint(first, last) / (numberElement + 1);
	if (isnan(distance)) {
		distance = 0.0;
	}
	for (int i = 0; i < numberElement; i++) {
		distanceToFirst += distance;
		//tìm ra các điểm nằm trên đường thẳng first,last và cách first một khoảng distanceToFirst
		normalizeWithRadius(first, last, arrayOut[i + offsetArrayOut], distanceToFirst);
	}
}

void CaculatorSphere(int radius, int numberLongitude,int numberLatitude, point centerSphere,std::vector<point> &vertexArray) {
	float const R = 1. / (float)(numberLatitude - 1);
	//để đỉnh cuối cùng nằm trùng lên đình đầu tiên thì
	//float const S = 1. / (float)(numberLongitude-1);
	float const S = 1. / (float)numberLongitude;
	for (int r = 0; r < numberLatitude; ++r) {
		for (int s = 0; s < numberLongitude; ++s) {
			float const y = sin(-M_PI_2 + M_PI * r * R)*radius+centerSphere.y;
			float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R)*radius+centerSphere.x;
			float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R)*radius+centerSphere.z;
			vertexArray.push_back({ x,y,z });
		}
	}
}

void CaculatorCubeRound(float xLength,float yLength,float zLength, int numberLongitude, int numberLatitude, point centerSphere,
	float radiusRound,std::vector<point> &vertexArray) {
	//tính toán vẽ hình cầu rồi mới chia khoảng cách ra để tạo ra hình vuông bo tròn
	float const R = 1. / (float)(numberLatitude - 1);
	float const S = 1. / (float)(numberLongitude - 1);
	float x, y, z,xPlus,yPlus,zPlus;
	for (int r = 0; r < numberLatitude; ++r) {
		for (int s = 0; s < numberLongitude; ++s) {
			xPlus = 0; yPlus = 0; zPlus = 0;
			if (r != 0 && r != numberLatitude - 1) {
				//chỉ phần mặt trước và sau
				if (s < numberLongitude / 2) {
					//mức độ chiều rộng của hình bằng chiều rộng tăng lên + với bán kính bo tròn
					//nên chiều rộng tăng lên của 1 nửa bên bằng 1 nửa chiều rộng - bán kính bo tròn mặt bên đó
					zPlus = (zLength / 2 - radiusRound);
				}
				else
				{
					zPlus = -(zLength / 2 - radiusRound);
				}
				//chỉnh mặt trái và phải
				if (s<numberLongitude*0.25 || s>numberLongitude*0.75) {
					xPlus = xLength / 2 - radiusRound;
				}
				else
				{
					xPlus = -(xLength / 2 - radiusRound);
				}
			}
			//chỉnh mặt trên và dưới
			if (r < numberLatitude / 2) {
				yPlus = -(yLength / 2 - radiusRound);
			}
			else
			{
				yPlus = yLength / 2 - radiusRound;
			}
			y = sin(-M_PI_2 + M_PI * r * R)*radiusRound + centerSphere.y+yPlus;
			x = cos(2 * M_PI * s * S) * sin(M_PI * r * R)*radiusRound + centerSphere.x+xPlus;
			z = sin(2 * M_PI * s * S) * sin(M_PI * r * R)*radiusRound + centerSphere.z+zPlus;
			vertexArray.push_back({ x,y,z });
		}
	}
}


//tính toán cone cho lần đầu
void caculatorCone(point centerCone, float radius, float height,int numberLongitude,int &numberLatitude,
	std::vector<point> &vertexArray) {

	//đối với tính toán cone lúc đầu thì numberLatitude luôn phải =3
	numberLatitude = 3;

	const float DEG2RAD = 3.14159 / 180;
	float degInRad, xCircle, zCircle;
	int deg = 360 / numberLongitude;
	//vẽ ngược lại để nó xoay cùng chiều kim đồng hồ
	//tính toán cho các vertex ở tâm đáy cone
	for (int i = 0; i < numberLongitude; i++) {
		//các vertex của đáy dưới cùng nằm cùng 1 chỗ và có vị trí tại centerCone
		vertexArray.push_back({ centerCone.x, centerCone.y,centerCone.z });
	}
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radius + centerCone.x;
		zCircle = sin(degInRad)*radius + centerCone.z;
		vertexArray.push_back({ xCircle, centerCone.y, zCircle });

	}
	//tính toán đỉnh trên cùng của cone
	for (int i = 0; i < numberLongitude; i++) {
		//các vertex của đỉnh trên cùng nằm cùng 1 chỗ và có vị trí tại centerCone + height
		vertexArray.push_back({ centerCone.x, centerCone.y+height,centerCone.z });
	}
}
void caculatorCylinder(point centerCylinder, float radiusUp, float radiusDown, float height,
	int numberLongitude, int &numberLatitude,std::vector<point> &vertexArray){
	//đối với tính toán cylinder lúc đầu thì numberLatitude luôn phải =4
	numberLatitude = 4;

	const float DEG2RAD = 3.14159 / 180;
	float degInRad, xCircle, zCircle;
	int deg = 360 / numberLongitude;
	//vẽ ngược lại để nó xoay cùng chiều kim đồng hồ
	//tính toán cho các vertex ở tâm đáy dưới cylinder
	for (int i = 0; i < numberLongitude; i++) {
		//các vertex của đáy dưới cùng nằm cùng 1 chỗ và có vị trí tại centerCone
		vertexArray.push_back({ centerCylinder.x, centerCylinder.y-height/2,centerCylinder.z });
	}
	//vẽ vòng bao ngoài của đáy phía dưới
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusDown + centerCylinder.x;
		zCircle = sin(degInRad)*radiusDown + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y - height / 2, zCircle });

	}
	//vẽ vòng bao ngoài của đáy phía trên
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusUp + centerCylinder.x;
		zCircle = sin(degInRad)*radiusUp + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y + height / 2, zCircle });

	}
	//tính toán cho các vertex ở tâm đáy trên cylinder
	for (int i = 0; i < numberLongitude; i++) {
		//các vertex của đáy dưới cùng nằm cùng 1 chỗ và có vị trí tại centerCone
		vertexArray.push_back({ centerCylinder.x, centerCylinder.y + height / 2,centerCylinder.z });
	}
}
//tính toán và hiển thị cho cylinder2 lần đầu
void caculatorEmptyCylinder(point centerCylinder, float radiusUpOut, float radiusDownOut, float radiusUpIn, float radiusDownIn,
	float height, int numberLongitude, int &numberLatitude, std::vector<point> &vertexArray) {
	//đối với tính toán empty cylinder lúc đầu thì numberLatitude luôn phải =4
	numberLatitude = 4;

	const float DEG2RAD = 3.14159 / 180;
	float degInRad, xCircle, zCircle;
	int deg = 360 / numberLongitude;
	//vẽ ngược lại để nó xoay cùng chiều kim đồng hồ

	//tính toán cho các vertex ở vòng trong đáy dưới cylinder
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusDownIn + centerCylinder.x;
		zCircle = sin(degInRad)*radiusDownIn + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y - height / 2, zCircle });

	}
	//tính toán cho các vertex ở vòng ngoài đáy dưới cylinder
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusDownOut + centerCylinder.x;
		zCircle = sin(degInRad)*radiusDownOut + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y - height / 2, zCircle });

	}
	//tính toán cho các vertex ở vòng ngoài đáy trên cylinder
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusUpOut + centerCylinder.x;
		zCircle = sin(degInRad)*radiusUpOut + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y + height / 2, zCircle });

	}
	//tính toán cho các vertex ở vòng trong đáy trên cylinder
	for (int i = 0; i < numberLongitude; i++)
	{
		//tính toán vòng bao dưới cùng của vertexAround
		degInRad = i*deg*DEG2RAD;
		//phải cộng thêm centerCone.x và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
		xCircle = cos(degInRad)*radiusUpIn + centerCylinder.x;
		zCircle = sin(degInRad)*radiusUpIn + centerCylinder.z;
		vertexArray.push_back({ xCircle, centerCylinder.y + height / 2, zCircle });

	}
}
void caculatorTorus(float radiusCake,float radiusRoundCake,float widthCake,int depthCake,int depthRoundCake,point centerTorus,
	vector<point> &vertexArray) {
	//2 cái này là số điểm bao quanh quả hình torus và số điểm bao quanh mỗi vòng
	//số điểm bao quanh hình càng lớn thì hình càng tròn,mượt
	//số điểm bao quanh mỗi vòng càng lớn thì các vòng bánh sẽ càng tròn
	double TWOPI = 2 * M_PI, s, t, x, y, z;
	for (int i = 0; i < depthCake; i++) {
		for (int j = 0; j <= depthRoundCake; j++) {
			for (int k = 1; k >= 0; k--) {
				s = (i + k) % depthCake + 0.5;
				t = j % depthRoundCake;
				x = (1 + 0.1 * cos(s * TWOPI / depthCake) * radiusRoundCake) * cos(t * TWOPI / depthRoundCake) * radiusCake ;
				y = (1 + 0.1 * cos(s * TWOPI / depthCake) * radiusRoundCake) * sin(t * TWOPI / depthRoundCake) * radiusCake ;
				z = 0.1 * sin(s * TWOPI / depthCake) * widthCake;
				vertexArray.push_back({ (float)(x*2) + centerTorus.x, (float)(y*2) + centerTorus.y,(float)(z*2) + centerTorus.z });
			}
		}
	}
}
//tính toán vẽ ban đầu objectCustom để thực hiện vẽ các đối tượng khó
//điều kiện là numberRow và numberColumn phải từ 2 trở lên
void caculatorObjectCustom0(int numberLongitude, int numberLatitude, float lengthBetween2Row, float lengthBetween2Column,
	point centerObject, vector<point> &vertexArray) {
	float rowCenter = (numberLatitude - 1) / 2.0f, columnCenter = (numberLongitude - 1) / 2.0f;
	//vì các hình tương tự với hình này như sphere,vylinder,... đều vẽ các triaStrip từ dưới lên trên nên hình này ta cũng
	//nên làm tương tự
	for (int i = numberLatitude - 1; i >= 0; i--) {
		for (int j = 0; j < numberLongitude; j++) {
			vertexArray.push_back({ (columnCenter - (float)j)*lengthBetween2Column + centerObject.x,
				(rowCenter - (float)i)*lengthBetween2Row + centerObject.y,centerObject.z });
		}
	}
}


//hàm kiểm tra xem 3 điểm có nằm trên cùng 1 đường thẳng không
bool checkIs3PointsInLine(point *v) {
	//kiểm tra xem 3 đỉnh này có cùng nằm trên 2 đường thẳng không
	float distanceMax = 0.0f, distance;
	bool is3PointInOneLine = false;
	int mMax = 0, nMax = 1;

	//lấy ra 2 điểm nằm ngoài cùng
	for (int m = 0; m < 2; m++) {
		for (int n = m + 1; n < 3; n++) {
			distance = distanceTwoPoint(v[m], v[n]);
			if (distance > distanceMax) {
				distanceMax = distance;
				mMax = m;
				nMax = n;
			}
		}
	}
	//kiểm tra xem 3 điểm có nằm trên cùng 1 đường thẳng không
	for (int m = 0; m < 3; m++) {
		//nếu không phải là 2 điểm đầu cuối thì kiểm tra
		if (m != mMax && m != nMax) {
			distance = distanceTwoPoint(v[m], v[mMax]) + distanceTwoPoint(v[m], v[nMax]);
			//kiểm tra xem tổng khoảng cách từ điểm cần xét tới 2 điểm ngoài cùng có bằng khoảng cách 2 điểm 
			//ngoài cùng không(cho phép sai số nhỏ)
			if (distanceMax == distance) {
				return true;
			}
		}
	}
	return false;
}
bool checkIs3PointsInLine(point v0, point v1, point v2) {
	point v[3] = { v0,v1,v2 };
	//kiểm tra xem 3 đỉnh này có cùng nằm trên 2 đường thẳng không
	float distanceMax = 0.0f, distance;
	bool is3PointInOneLine = false;
	int mMax = 0, nMax = 1;

	//lấy ra 2 điểm nằm ngoài cùng
	for (int m = 0; m < 2; m++) {
		for (int n = m + 1; n < 3; n++) {
			distance = distanceTwoPoint(v[m], v[n]);
			if (distance > distanceMax) {
				distanceMax = distance;
				mMax = m;
				nMax = n;
			}
		}
	}
	//kiểm tra xem 3 điểm có nằm trên cùng 1 đường thẳng không
	for (int m = 0; m < 3; m++) {
		//nếu không phải là 2 điểm đầu cuối thì kiểm tra
		if (m != mMax && m != nMax) {
			distance = distanceTwoPoint(v[m], v[mMax]) + distanceTwoPoint(v[m], v[nMax]);
			//kiểm tra xem tổng khoảng cách từ điểm cần xét tới 2 điểm ngoài cùng có bằng khoảng cách 2 điểm 
			//ngoài cùng không(cho phép sai số nhỏ)
			if (distanceMax == distance) {
				return true;
			}
		}
	}
	return false;
}
//các hàm tính toán normal vector cho hình
void CaculatorNormalForTriangles(point *vertexArray, point &vectorNormal) {
	point v0, v1, v2, normal;
	v0 = vertexArray[0];
	v1 = vertexArray[1];
	v2 = vertexArray[2];
	normcrossprod(v0, v1, v2,normal);
	vectorNormal = normal;
}
void CaculatorNormalForTriangleStrip(vector<point> vertexArray, vector<point> &vectorNormal) {
	point v0, v1, v2, normal;
	int numberVertex = vertexArray.size();
	//biến thông báo có tìm được normal không,trường hợp bị lỗi sẽ lấy normal trước nó để dùng(nếu có)
	//nếu không thì lấy giá trị mặc định 0.0
	bool isFound;
	vectorNormal.clear();
	//bắt đầu từ vertex thứ 3 mới tính được2
	if (numberVertex > 2) {
		for (int i = 2; i < numberVertex; i++) {
			v0 = vertexArray.at(i - 2);
			v1 = vertexArray.at(i - 1);
			v2 = vertexArray.at(i);
			if (i % 2 == 0) {
				isFound = normcrossprod(v0, v1, v2, normal);
				//nếu không tìm thấy và vertexNormal không rổng thì lấy điểm sau cùng bỏ vào
				if (!isFound && !vectorNormal.empty()) {
					normal = vectorNormal.back();
				}
			}
			else
			{
				isFound = normcrossprod(v2, v1, v0, normal);
				//nếu không tìm thấy và vertexNormal không rổng thì lấy điểm sau cùng bỏ vào
				if (!isFound && !vectorNormal.empty()) {
					normal = vectorNormal.back();
				}
			}

			if (i == 2) {
				vectorNormal.push_back(normal);
				vectorNormal.push_back(normal);
				vectorNormal.push_back(normal);
			}
			else
			{
				vectorNormal.push_back(normal);
			}
		}
	}
	//nếu từ 2 vertex trở xuống thì mỗi đỉnh cứ đặt normal={0.0,0.0,0.0}
	else
	{
		for (int i = 0; i < numberVertex; i++) {
			vectorNormal.push_back({ 0.0,0.0,0.0 });
		}
	}
}
void CaculatorNormalForTriangleFan(vector<point> vertexArray, vector<point> &vectorNormal) {
	point v0, v1, v2, normal;
	int numberVertex = vertexArray.size();
	//biến thông báo có tìm được normal không,trường hợp bị lỗi sẽ lấy normal trước nó để dùng(nếu có)
	//nếu không thì lấy giá trị mặc định 0.0
	bool isFound;
	vectorNormal.clear();
	//đối với triaFan thì đỉnh đầu luôn là đỉnh chung của các tan giác kia
	v0 = vertexArray.at(0);
	//bắt đầu từ vertex thứ 3 mới tính được
	if (numberVertex > 2) {
		for (int i = 2; i < numberVertex; i++) {
			v1 = vertexArray.at(i - 1);
			v2 = vertexArray.at(i);
			isFound = normcrossprod(v0, v1, v2, normal);
			//nếu không tìm thấy và vertexNormal không rổng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			if (i == 2) {
				vectorNormal.push_back(normal);
				vectorNormal.push_back(normal);
				vectorNormal.push_back(normal);
			}
			else
			{
				vectorNormal.push_back(normal);
			}
		}
	}
	//nếu từ 2 vertex trở xuống thì mỗi đỉnh cứ đặt normal={0.0,0.0,0.0}
	else
	{
		for (int i = 0; i < numberVertex; i++) {
			vectorNormal.push_back({ 0.0,0.0,0.0 });
		}
	}
}

void CaculatorNormalForSphere(int numberLongitude, int numberLatitude, vector<point> &vertexArray, vector<point> &normalVector) {
	point v[4], vCheck1, vCheck2, normal;
	int offset1, offset2, halfLongitude = numberLongitude / 2,
		mMax, nMax;
	float distance, distanceMax;
	bool isSame2Vertex = false, isSame4Vertex = false, isFound = false,
		is3PointInOneLine, is4PointInOneLine, isFirstTriaCantUse;
	normalVector.clear();

	//tính toán normal cho cụm đỉnh đầu tiên
	//đầu tiên ta kiểm tra từ cụm đỉnh thứ 1(tức là thứ 2) trở đi xem có tìm được 3 đỉnh 
	//không trùng nhau để tính normal dùng để gắn cho toàn bộ cụm đỉnh đầu không
	
	for (int i = 1; i < numberLatitude - 1; i++) {
		offset1 = i * numberLongitude;
		offset2 = ((i + 1) * numberLongitude) - 1;
		for (int j = 0; j < halfLongitude; j++) {
			v[0] = vertexArray.at(offset1 + j);
			v[1] = vertexArray.at(offset1 + halfLongitude);
			v[2] = vertexArray.at(offset2 - j);
			is3PointInOneLine = checkIs3PointsInLine(v);
			//nếu không phải cả 3 đỉnh nằm trên cùng 1 đường thẳng thì đây là tam giác cần tìm
			if (!is3PointInOneLine)
			{
				isFound = normcrossprod(v[0], v[1], v[2], normal);
				if (isFound) {
					break;
				}
			}
		}
		if (isFound) {
			break;
		}
	}
	//lấy normal vừa tìm được đặt cho tất cả đỉnh của chuỗi đỉnh đầu tiên
	for (int i = 0; i < numberLongitude; i++) {
		normalVector.push_back(normal);
	}

	//tính toán normal cho các cụm đỉnh ở giữa
	for (int i = 1; i < numberLatitude-1; i++) {
		offset1 = (i - 1) * numberLongitude;
		offset2 = i * numberLongitude;
		for (int j = 0; j < numberLongitude; j++) {
			//đầu tiên lấy ra tất cả 4 đỉnh có thể dùng dể xác định normal
			//v0:trên-trái,v1:dưới-phải,v2:trên-phải,v3:dưới-trái
			if (j == 0) {
				v[0] = vertexArray.at(offset2 + numberLongitude - 1);
				v[1] = vertexArray.at(offset1);
				v[2] = vertexArray.at(offset2);
				v[3] = vertexArray.at(offset1 + numberLongitude - 1);
			}
			else {
				v[0] = vertexArray.at(offset2 + j - 1);
				v[1] = vertexArray.at(offset1 + j);
				v[2] = vertexArray.at(offset2 + j);
				v[3] = vertexArray.at(offset1 + j - 1);
			}

			//kiểm tra xem có 4 điểm này có nằm trên cùng 1 đường thẳng không
			//không thể kiểm tra theo kiểu thỏa mãn phương trình đường thẳng được vì có sai số
			//ta tìm ra điểm 
			distanceMax = 0.0f;
			is3PointInOneLine = false;
			is4PointInOneLine = false;
			isFirstTriaCantUse = false;
			mMax = 0;
			nMax = 1;
			for (int m = 0; m < 3; m++) {
				for (int n = m + 1; n < 4; n++) {
					distance = distanceTwoPoint(v[m], v[n]);
					if (distance > distanceMax) {
						distanceMax = distance;
						mMax = m;
						nMax = n;
					}
				}
			}
			
			//sau khi tìm ra được 2 điểm ngoài cùng ta kiểm tra 2 điểm còn lại có nằm trên cùng
			//1 đường thẳng với 2 điểm này không bằng cách xem tổng khoảng cách giữa điểm cần xét
			//tới 2 điểm ngoài cùng có bằng 2 điểm ngoài cùng không
			for (int m = 0; m < 4; m++) {
				//nếu không phải là 2 điểm đầu cuối thì kiểm tra
				if (m != mMax && m != nMax) {
					distance = distanceTwoPoint(v[m], v[mMax]) + distanceTwoPoint(v[m], v[nMax]);
					//kiểm tra xem tổng khoảng cách từ điểm cần xét tới 2 điểm ngoài cùng có bằng khoảng cách 2 điểm 
					//ngoài cùng không(cho phép sai số nhỏ)
					if (distanceMax == distance) {
						//nếu chưa xác định được 3 điểm trên cùng 1 đường thẳng thì bây giờ xác định
						if(!is3PointInOneLine){
							is3PointInOneLine = true;
							//kiểm tra xem 2 điểm ngoài cùng và điểm đang xét có thuộc tam giác thứ nhất không,
							//nếu có thì xác định(nếu có 4 điểm trùng thì khỏi xét vì nó nghĩa là không thể xét cả 2 tam giác)
							if (mMax < 3 && nMax < 3 && m < 3) {
								isFirstTriaCantUse = true;
							}
						}
						//nếu đã xác định được 3 điểm ở cùng 1 đường thẳng rồi thì đây là điểm thứ 4
						else
						{
							is4PointInOneLine = true;
						}
					}
				}
			}

			//nếu cả 4 điểm nằm trên 1 đường thẳng thì lấy normal của điểm thuộc hàng phía trên thay thế
			if (is4PointInOneLine) {
				normal = normalVector.back();
				//nếu 4 điểm nằm trên cùng 1 đường thẳng thì ta tìm ra điểm thay thế
			}
			//nếu nhiều nhất chỉ có 3 điểm nằm trên 1 đường thẳng thì vẫn có tam giác để xét
			else
			{
				//kiểm tra xem tam giác thứ nhất có dùng được không,nếu không thì dùng tam giác thứ 2
				if (isFirstTriaCantUse) {
					isFound = normcrossprod(v[0], v[1], v[3], normal);
				}
				else
				{
					isFound = normcrossprod(v[2], v[1], v[0], normal);
				}
			}
			
			//nếu không tìm thấy và vertexNormal không rổng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !normalVector.empty()) {
				normal = normalVector.back();
			}
			normalVector.push_back(normal);
		}
	}

	//tính toán normal cho cụm đỉnh cuối cùng
	isFound = false;
	for (int i = numberLatitude - 2; i > 1; i--) {
		offset1 = i * numberLongitude;
		offset2 = (i + 1) * numberLongitude - 1;
		for (int j = 0; j < halfLongitude; j++) {
			v[0] = vertexArray.at(offset1 + j);
			v[1] = vertexArray.at(offset1 + halfLongitude);
			v[2] = vertexArray.at(offset2 - j);
			is3PointInOneLine = checkIs3PointsInLine(v);
			//nếu không phải cả 3 đỉnh nằm trên cùng 1 đường thẳng thì đây là tam giác cần tìm
			if (!is3PointInOneLine)
			{
				isFound = normcrossprod(v[2], v[1], v[0], normal);
				if (isFound) {
					break;
				}
			}
		}
		if (isFound) {
			break;
		}
	}
	//lấy normal vừa tìm được đặt cho tất cả đỉnh của chuỗi đỉnh cuối cùng
	for (int i = 0; i < numberLongitude; i++) {
		normalVector.push_back(normal);
	}
}
void CaculatorNormalForCubeRound(int numberLongitude, int numberLatitude, vector<point> &vertexArray, vector<point> &normalVector) {
	point v0, v1, v2, normal;
	int offsetLast, offsetNow;
	bool isFound;
	normalVector.clear();
	for (int i = 1; i <= numberLatitude; i++) {
		//nếu là cụm đỉnh cuối cùng thì dùng chung normal với cụm đỉnh trước nó
		if (i == numberLatitude) {
			normalVector.insert(normalVector.end(), normalVector.begin() + ((numberLatitude - 2) * numberLongitude), normalVector.end());
			break;
		}
		else
		{
			offsetLast = (i - 1) * numberLongitude;
			offsetNow = i * numberLongitude;
		}
		for (int j = 0; j < numberLongitude; j++) {
			//đầu tiên ta xét 3 đỉnh trên-dưới-trên,nếu chúng bị trùng ở 2 điểm thì là dưới-trên-dưới
			if (j == 0) {
				v0 = vertexArray.at(offsetNow + numberLongitude - 2);
				v1 = vertexArray.at(offsetLast);
				v2 = vertexArray.at(offsetNow);
			}
			else {
				v0 = vertexArray.at(offsetNow + j - 1);
				v1 = vertexArray.at(offsetLast + j);
				v2 = vertexArray.at(offsetNow + j);
			}
			//kiểm tra xem 3 điểm này có 2 điểm nào trùng nhau không(ở điểm nút)
			//nếu trùng thì lấy mặt kia( một cái là dưới-trên-dưới và 1 cái là trên-dưới-trên )
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				if (j == 0) {
					v0 = vertexArray.at(offsetLast);
					v1 = vertexArray.at(offsetNow);
					v2 = vertexArray.at(offsetLast + numberLongitude - 2);
				}
				else {
					v0 = vertexArray.at(offsetLast + j);
					v1 = vertexArray.at(offsetNow + j);
					v2 = vertexArray.at(offsetLast + j - 1);
				}
			}

			isFound = normcrossprod(v2, v1, v0, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !normalVector.empty()) {
				normal = normalVector.back();
			}
			normalVector.push_back(normal);
		}
	}
}
void CaculatorNormalForCube(int numberVertexInAxisX,int numberVertexInAxisY,int numberVertexInAxisZ,
	vector<point> vertexArray, vector<point> &vectorNormal) {
	bool isFound;
	//phải xóa hết trước khi tính lại
	vectorNormal.clear();

	int offset1, offset2,offset3, numberVertexInRow;
	point v0, v1, v2, normal;
	numberVertexInRow = (numberVertexInAxisX - 1) * 2 + (numberVertexInAxisZ - 1) * 2;
	for (int i = 0; i < numberVertexInAxisY - 1; i++) {
		offset1 = i * numberVertexInRow;
		offset2 = (i + 1) * numberVertexInRow;
		for (int j = 1; j < numberVertexInRow; j++) {
			v0 = vertexArray.at(offset1 + j - 1);
			v1 = vertexArray.at(offset2 + j - 1);
			v2 = vertexArray.at(offset1 + j);
			isFound = normcrossprod(v0, v1, v2, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);
			v0 = vertexArray.at(offset2 + j);
			isFound = normcrossprod(v2, v1, v0, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);
			if (j == numberVertexInRow - 1) {
				//nếu là đến đỉnh cuối thì vẽ nối với đỉnh đầu
				v1 = vertexArray.at(offset1);
				isFound = normcrossprod(v2, v0, v1, normal);
				//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
				if (!isFound && !vectorNormal.empty()) {
					normal = vectorNormal.back();
				}
				vectorNormal.push_back(normal);
				v2 = vertexArray.at(offset2);
				isFound = normcrossprod(v1, v0, v2, normal);
				//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
				if (!isFound && !vectorNormal.empty()) {
					normal = vectorNormal.back();
				}
				vectorNormal.push_back(normal);
			}
		}
	}
	//các offset dùng nhiều
	offset1 = numberVertexInAxisX + numberVertexInAxisZ + numberVertexInAxisX - 3;
	//điểm đầu tiên của vertexUp(tức là cụm các đỉnh nằm phía trong)
	offset2 = numberVertexInRow*numberVertexInAxisY;
	//vẽ mặt trên của hình khối
	for (int i = 1; i < numberVertexInAxisZ; i++) {
		for (int j = 1; j < numberVertexInAxisX; j++) {
			//tính đỉnh v0
			if (i == numberVertexInAxisZ - 1) {
				v0 = vertexArray.at(offset1 - (j - 1));
			}
			else
			{
				if (j == 1) {
					v0 = vertexArray.at(numberVertexInRow - i);
				}
				else
				{
					v0 = vertexArray.at(offset2 + (i - 1)*(numberVertexInAxisX - 2) + (j - 2));
				}
			}
			//tính đỉnh v1
			if (i == 1) {
				v1 = vertexArray.at(j - 1);
			}
			else
			{
				if (j == 1) {
					v1 = vertexArray.at(numberVertexInRow - (i - 1));
				}
				else
				{
					v1 = vertexArray.at(offset2 + (i - 2)*(numberVertexInAxisX - 2) + (j - 2));
				}
			}
			//tính đỉnh v2
			if (i == numberVertexInAxisZ - 1) {
				v2 = vertexArray.at(offset1 - j);
			}
			else
			{
				if (j == numberVertexInAxisX - 1) {
					v2 = vertexArray.at(numberVertexInAxisX - 1 + i);
				}
				else
				{
					v2 = vertexArray.at(offset2 + (i - 1)*(numberVertexInAxisX - 2) + (j - 1));
				}
			}

			isFound = normcrossprod(v0, v1, v2, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);

			//tính đỉnh v3
			if (i == 1) {
				v0 = vertexArray.at(j);
			}
			else
			{
				if (j == numberVertexInAxisX - 1) {
					v0 = vertexArray.at(numberVertexInAxisX - 1 + (i - 1));
				}
				else
				{
					v0 = vertexArray.at(offset2 + (i - 2)*(numberVertexInAxisX - 2) + (j - 1));
				}
			}
			isFound = normcrossprod(v2, v1, v0, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);
		}
	}

	//các offset dùng nhiều
	offset1 = numberVertexInAxisX + numberVertexInAxisZ + numberVertexInAxisX - 3;
	//điểm đầu tiên của vertexDown(tức là cụm các đỉnh nằm phía trong)
	offset2 = numberVertexInRow*numberVertexInAxisY + ((numberVertexInAxisX - 2)*(numberVertexInAxisZ - 2));
	//vị trí đầu tiên của vòng đỉnh ngoài phía dưới cùng
	offset3 = (numberVertexInAxisY - 1)*numberVertexInRow;
	//vẽ các mặt dưới của hình khối
	for (int i = 1; i < numberVertexInAxisZ; i++) {
		for (int j = 1; j < numberVertexInAxisX; j++) {
			//tính đỉnh v0
			if (i == numberVertexInAxisZ - 1) {
				v0 = vertexArray.at(offset3 + offset1 - (j - 1));
			}
			else
			{
				if (j == 1) {
					v0 = vertexArray.at(offset3 + numberVertexInRow - i);
				}
				else
				{
					v0 = vertexArray.at(offset2 + (i - 1)*(numberVertexInAxisX - 2) + (j - 2));
				}
			}
			//tính đỉnh v1
			if (i == 1) {
				v1 = vertexArray.at(offset3 + j - 1);
			}
			else
			{
				if (j == 1) {
					v1 = vertexArray.at(offset3 + numberVertexInRow - (i - 1));
				}
				else
				{
					v1 = vertexArray.at(offset2 + (i - 2)*(numberVertexInAxisX - 2) + (j - 2));
				}
			}
			//tính đỉnh v2
			if (i == numberVertexInAxisZ - 1) {
				v2 = vertexArray.at(offset3 + offset1 - j);
			}
			else
			{
				if (j == numberVertexInAxisX - 1) {
					v2 = vertexArray.at(offset3 + numberVertexInAxisX - 1 + i);
				}
				else
				{
					v2 = vertexArray.at(offset2 + (i - 1)*(numberVertexInAxisX - 2) + (j - 1));
				}
			}

			isFound = normcrossprod(v2, v1, v0, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);

			//tính đỉnh v3
			if (i == 1) {
				v0 = vertexArray.at(offset3 + j);
			}
			else
			{
				if (j == numberVertexInAxisX - 1) {
					v0 = vertexArray.at(offset3 + numberVertexInAxisX - 1 + (i - 1));
				}
				else
				{
					v0 = vertexArray.at(offset2 + (i - 2)*(numberVertexInAxisX - 2) + (j - 1));
				}
			}
			isFound = normcrossprod(v0, v1, v2, normal);
			//nếu không tìm thấy và vertexNormal không rỗng thì lấy điểm sau cùng bỏ vào
			if (!isFound && !vectorNormal.empty()) {
				normal = vectorNormal.back();
			}
			vectorNormal.push_back(normal);
		}
	}
}

void CaculatorNormalForCone(int numberLongitude,int numberLatitude,vector<point> vertexArray, vector<point> &normalVector) {
	point v0, v1, v2, normal;
	int offsetLast, offsetNow;
	bool isSame2Vertex = false, isFound;
	normalVector.clear();
	for (int i = 1; i < numberLatitude; i++) {
		//tính normal vector cho các cụm đỉnh tam giác tiếp theo
		offsetLast = (i - 1) * numberLongitude;
		offsetNow = i * numberLongitude;
		for (int j = 1; j < numberLongitude; j++) {
			//mỗi lần lần tính 2 normal cho 2 tam giác nằm giữa 2 cụm đỉnh

			//tuy nhiên khi tính cho các tam giác nối với tâm đáy dưới cùng hay đỉnh trên cùng thì sẽ
			//gặp trường hợp 2 đỉnh trùng nhau do đó không tính được normal vector,trong trường hợp đó,nếu 1 trong 
			//2 tam giác bị thì lấy tam giác kia
			v0 = vertexArray.at(offsetNow + j);
			v1 = vertexArray.at(offsetLast + j);
			v2 = vertexArray.at(offsetNow + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				isSame2Vertex = true;
			}
			else
			{
				isFound = normcrossprod(v0, v1, v2, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
					isSame2Vertex = false;
				}
				else
				{
					isSame2Vertex = true;
				}
			}
			v0 = vertexArray.at(offsetLast + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				//nếu tam giác 2 bi trùng thì tam giác 1 không bị trùng,ta lấy normal của tam giác 1
				//nếu cả 2 tam giác bị trùng thì lấy giá trị trước nó
				if (isSame2Vertex)
				{
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
				}
				else
				{
					normalVector.push_back(normal);
				}
			}
			else
			{
				isFound = normcrossprod(v2, v1, v0, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
				else
				{
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
				
			}
			//nếu là cặp đỉnh cuối cùng thì thêm 2 normal để nối với cặp đỉnh đầu và lấy chung normal với cặp đỉnh đầu để tạo cảm giác mượt
			if (j == numberLongitude - 1) {
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
			}
		}
	}
}
void CaculatorNormalForCylinder(int numberLongitude, int numberLatitude, vector<point> vertexArray,vector<point> &normalVector) {
	point v0, v1, v2, normal;
	int offsetLast, offsetNow;
	bool isSame2Vertex = false, isFound;
	normalVector.clear();
	for (int i = 1; i < numberLatitude; i++) {
		//tính normal vector cho các cụm đỉnh tam giác tiếp theo
		offsetLast = (i - 1) * numberLongitude;
		offsetNow = i * numberLongitude;
		for (int j = 1; j < numberLongitude; j++) {
			//mỗi lần lần tính 2 normal cho 2 tam giác nằm giữa 2 cụm đỉnh

			//tuy nhiên khi tính cho các tam giác nối với tâm đáy dưới cùng hay đỉnh trên cùng thì sẽ
			//gặp trường hợp 2 đỉnh trùng nhau do đó không tính được normal vector,trong trường hợp đó,nếu 1 trong 
			//2 tam giác bị thì lấy tam giác kia
			v0 = vertexArray.at(offsetNow + j);
			v1 = vertexArray.at(offsetLast + j);
			v2 = vertexArray.at(offsetNow + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				isSame2Vertex = true;
			}
			else
			{
				isFound = normcrossprod(v0, v1, v2, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
					isSame2Vertex = false;
				}
				else
				{
					isSame2Vertex = true;
				}
			}

			v0 = vertexArray.at(offsetLast + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				//nếu tam giác 2 bi trùng thì tam giác 1 không bị trùng,ta lấy normal của tam giác 1
				//nếu cả 2 bị trùng thì ta lấy normal trước đó(nếu có)
				if (isSame2Vertex) {
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
				}
				else
				{
					normalVector.push_back(normal);
				}
			}
			else
			{
				isFound = normcrossprod(v2, v1, v0, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
				else
				{
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
			}
			//nếu là cặp đỉnh cuối cùng thì lấy chung normal với cặp đỉnh đầu để tạo cảm giác mượt
			if (j == numberLongitude - 1) {
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
			}
		}
	}
}
void CaculatorNormalForPyramid(point *vertexArray,point *normalVector) {
	//mảng chứa các giá trị đỉnh theo thứ tự của pyramid
	int vertexArrayPyr[][3]{
		{ 0,1,2 },{ 0,2,3 },{ 0,3,4 },{ 0,4,1 },{ 1,4,2 },{ 2,4,3 }
	};
	point v0, v1, v2, normal;
	for (int i = 0; i < 6; i++) {
		v0 = vertexArray[vertexArrayPyr[i][0]];
		v1 = vertexArray[vertexArrayPyr[i][1]];
		v2 = vertexArray[vertexArrayPyr[i][2]];
		normcrossprod(v0, v1, v2, normal);
		normalVector[i] = normal;
	}
}
void CaculatorNormalForEmptyCylinder(int numberLongitude, int numberLatitude,
	vector<point> vertexArray, vector<point> &normalVector) {
	point v0, v1, v2, normal;
	int offsetLast, offsetNow;
	bool isSame2Vertex = false,isFound;
	normalVector.clear();
	//tính normal cho vòng bao bên ngoài và nắp trên dưới emptyCylinder
	for (int i = 1; i < numberLatitude; i++) {
		//tính normal vector cho các cụm đỉnh tam giác tiếp theo
		offsetLast = (i - 1) * numberLongitude;
		offsetNow = i * numberLongitude;
		for (int j = 1; j < numberLongitude; j++) {
			//mỗi lần lần tính 2 normal cho 2 tam giác nằm giữa 2 cụm đỉnh

			//tuy nhiên khi tính cho các tam giác nối với tâm đáy dưới cùng hay đỉnh trên cùng thì sẽ
			//gặp trường hợp 2 đỉnh trùng nhau do đó không tính được normal vector,trong trường hợp đó,nếu 1 trong 
			//2 tam giác bị thì lấy tam giác kia
			v0 = vertexArray.at(offsetNow + j);
			v1 = vertexArray.at(offsetLast + j);
			v2 = vertexArray.at(offsetNow + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				isSame2Vertex = true;
			}
			else
			{
				isFound = normcrossprod(v0, v1, v2, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
					isSame2Vertex = false;
				}
				else
				{
					isSame2Vertex = true;
				}
			}

			v0 = vertexArray.at(offsetLast + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				//nếu tam giác 2 bi trùng thì tam giác 1 không bị trùng,ta lấy normal của tam giác 1
				//nếu cả 2 bị trùng thì lấy normal trước đó(nếu có)
				if (isSame2Vertex) {
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
				}
				else
				{
					normalVector.push_back(normal);
				}
			}
			else
			{
				normcrossprod(v2, v1, v0, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
				else
				{
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
			}
			//nếu là cặp đỉnh cuối cùng thì lấy chung normal với cặp đỉnh đầu để tạo cảm giác mượt
			if (j == numberLongitude - 1) {
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
				normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
			}
		}
	}
	//tính normal cho vòng bao bên trong(tính bằng cụm đỉnh đầu tiên và cụm đỉnh cuối cùng)
	offsetLast = 0;
	offsetNow = vertexArray.size() - numberLongitude;
	for (int j = 1; j < numberLongitude; j++) {
		v0 = vertexArray.at(offsetLast + j);
		v1 = vertexArray.at(offsetNow + j);
		v2 = vertexArray.at(offsetLast + j - 1);
		isFound = normcrossprod(v0, v1, v2, normal);
		if (!isFound && !normalVector.empty()) {
			normal = normalVector.back();
		}
		normalVector.push_back(normal);
		//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
		if (j == 1) {
			normalVector.push_back(normal);
			normalVector.push_back(normal);
		}
		v0 = vertexArray.at(offsetNow + j - 1);
		isFound = normcrossprod(v2, v1, v0, normal);
		if (!isFound && !normalVector.empty()) {
			normal = normalVector.back();
		}
		normalVector.push_back(normal);
		//nếu là cặp đỉnh cuối cùng thì lấy chung normal với cặp đỉnh đầu để tạo cảm giác mượt
		if (j == numberLongitude - 1) {
			normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
			normalVector.push_back(normalVector.at(normalVector.size() - ((numberLongitude - 1) * 2)));
		}
	}

}

void CaculatorNormalForTorus(int depthRound, vector<point> vertexArray, vector<point> &normalVector) {
	int numberVertex = vertexArray.size();
	bool isFound;
	point v0, v1, v2, normal;
	//2 đối số dùng để tìm ra điểm đầu và điểm cuối giữa 2 mối nối torus
	//để đặt chung normal cho chúng vừa để tránh vết răng cưa,vừa là do 
	//normal ở đoạn cuối bị lỗi do các vertex xoay 1 vòng để chuyển đường xoay
	int ab = (depthRound + 1) * 2;
	int ub = depthRound * 2;
	normalVector.clear();
	for (int i = 2; i < numberVertex; i++) {
		v0 = vertexArray.at(i - 2);
		v1 = vertexArray.at(i - 1);
		v2 = vertexArray.at(i);
		if (i % 2 == 0) {
			isFound = normcrossprod(v0, v1, v2, normal);
		}
		else
		{
			isFound = normcrossprod(v2, v1, v0, normal);
		}
		//nếu bị lỗi không tìm được normal vector thì lấy normal trước đó(nếu có)
		if (!isFound && !normalVector.empty()) {
			normal = normalVector.back();
		}

		if ((i % ab == ub || i % ab == ub+1) && i != 0) {
			//do đây là 2 điểm trùng nhau và có 1 điểm tính sai do đoạn này do nó đi thành 1 vòng tròn để chuyển đến
			//đường vẽ mới nên sẽ tạo ra normal vector sai(và do 2 điểm này trùng nhau nên nếu sử dụng chung normal
			//thì sẽ nhìn rất mịn)
			normalVector.at(i - ub) = normal;
		}
		if (i == 2) {
			//nếu là vertex số 2 thì tính normal cho 2 vertex đầu tiên luôn
			normalVector.push_back(normal);
			normalVector.push_back(normal);
			normalVector.push_back(normal);
		}
		else
		{
			normalVector.push_back(normal);
		}
	}
}
void CaculatorNormalForPictures(point *vertexArray, point *vectorNormal) {
	point v0, v1, v2, normal;
	v0 = vertexArray[0];
	v1 = vertexArray[1];
	v2 = vertexArray[2];
	normcrossprod(v0, v1, v2, normal);
	vectorNormal[0] = normal;
	vectorNormal[1] = normal;
	vectorNormal[2] = normal;
	v1 = vertexArray[3];
	normcrossprod(v0, v2, v1, normal);
	vectorNormal[3] = normal;
}
void CaculatorNormalForObjectCustom0(int numberLongitude, int numberLatitude,
	vector<point> vertexArray, vector<point> &normalVector) {

	point v0, v1, v2, normal;
	int offsetLast, offsetNow;
	bool isSame2Vertex = false, isFound;
	normalVector.clear();
	for (int i = 1; i < numberLatitude; i++) {
		//tính normal vector cho các cụm đỉnh tam giác tiếp theo
		offsetLast = (i - 1) * numberLongitude;
		offsetNow = i * numberLongitude;
		for (int j = 1; j < numberLongitude; j++) {
			//mỗi lần lần tính 2 normal cho 2 tam giác nằm giữa 2 cụm đỉnh

			//tuy nhiên khi tính cho các tam giác nối với tâm đáy dưới cùng hay đỉnh trên cùng thì sẽ
			//gặp trường hợp 2 đỉnh trùng nhau do đó không tính được normal vector,trong trường hợp đó,nếu 1 trong 
			//2 tam giác bị thì lấy tam giác kia
			v0 = vertexArray.at(offsetNow + j);
			v1 = vertexArray.at(offsetLast + j);
			v2 = vertexArray.at(offsetNow + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				isSame2Vertex = true;
			}
			else
			{
				isFound = normcrossprod(v0, v1, v2, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
					isSame2Vertex = false;
				}
				else
				{
					isSame2Vertex = true;
				}
			}

			v0 = vertexArray.at(offsetLast + j - 1);
			//kiểm tra xem có 2 đỉnh nào cùng nằm cùng 1 vị trí không
			if ((v0.x == v1.x&&v0.y == v1.y&&v0.z == v1.z) ||
				(v0.x == v2.x&&v0.y == v2.y&&v0.z == v2.z) ||
				(v1.x == v2.x&&v1.y == v2.y&&v1.z == v2.z)) {
				//nếu tam giác 2 bi trùng thì tam giác 1 không bị trùng,ta lấy normal của tam giác 1
				//nếu cả 2 bị trùng thì ta lấy normal trước đó(nếu có)
				if (isSame2Vertex) {
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					normalVector.push_back(normal);
					//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
					if (j == 1) {
						normalVector.push_back(normal);
						normalVector.push_back(normal);
					}
				}
				else
				{
					normalVector.push_back(normal);
				}
			}
			else
			{
				isFound = normcrossprod(v2, v1, v0, normal);
				if (isFound) {
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
				else
				{
					//nếu normalVector không rỗng thì lấy phần tử sau cùng dùng
					if (!normalVector.empty()) {
						normal = normalVector.back();
					}
					else
					{
						normal = { 0.0,0.0,0.0 };
					}
					normalVector.push_back(normal);
					//kiểm tra xem tam giác 1 có bị trùng không,nếu bị trùng thì thêm 1 normal vector cho tam giác 1
					if (isSame2Vertex) {
						//nếu đang tính cho tam giác đầu tiên thì thêm 2 normal cho 2 đỉnh trước luôn
						if (j == 1) {
							normalVector.push_back(normal);
							normalVector.push_back(normal);
						}
						normalVector.push_back(normal);
					}
				}
			}
		}
	}
}


//tìm điểm chính giữa mảng vertex
point getPointCenterVertexes(vector<point> vertexArray) {
	float valueX = 0, valueY = 0, valueZ = 0;
	int numberVertex = vertexArray.size();
	if (numberVertex > 0) {
		for (int i = 0; i < numberVertex; i++) {
			valueX += vertexArray.at(i).x;
			valueY += vertexArray.at(i).y;
			valueZ += vertexArray.at(i).z;
		}
		return{ valueX / numberVertex,valueY / numberVertex,valueZ / numberVertex };
	}
	else
	{
		return{ 0.0,0.0,0.0 };
	}
}
point getPointCenterVertexes(point *vertexArray, int numberVertex) {
	float valueX = 0, valueY = 0, valueZ = 0;
	if (numberVertex > 0) {
		for (int i = 0; i < numberVertex; i++) {
			valueX += vertexArray[i].x;
			valueY += vertexArray[i].y;
			valueZ += vertexArray[i].z;
		}
		return{ valueX / numberVertex,valueY / numberVertex,valueZ / numberVertex };
	}
	else
	{
		return{ 0.0,0.0,0.0 };
	}
}
//tỉm điểm chính giữa mảng các vertex được chỉ định vị trí
point getPointCenterVertexesAtPosition(vector<point> vertexArray, vector<int> position) {
	float valueX = 0, valueY = 0, valueZ = 0;
	int numberPosition = position.size(), offset,
		numberVertex = vertexArray.size();
	if (numberVertex > 0 && numberPosition > 0) {
		for (int i = 0; i < numberPosition; i++) {
			offset = position.at(i);
			if (offset < numberVertex) {
				valueX += vertexArray.at(offset).x;
				valueY += vertexArray.at(offset).y;
				valueZ += vertexArray.at(offset).z;
			}
		}
		return{ valueX / numberPosition,valueY / numberPosition,valueZ / numberPosition };
	}
	else
	{
		return{ 0.0,0.0,0.0 };
	}
}
point getPointCenterVertexesAtPosition(point *vertexArray, vector<int> position) {
	float valueX = 0, valueY = 0, valueZ = 0;
	int numberVertex = position.size();
	if (numberVertex > 0) {
		for (int i = 0; i < numberVertex; i++) {
			valueX += vertexArray[position.at(i)].x;
			valueY += vertexArray[position.at(i)].y;
			valueZ += vertexArray[position.at(i)].z;
		}
		return{ valueX / numberVertex,valueY / numberVertex,valueZ / numberVertex };
	}
	else
	{
		return{ 0.0,0.0,0.0 };
	}
}
//hàm lấy điểm chính giữa của các vertex đối xứng của mảng các vertex được chọn
point getPointCenterVertexesSymmetryAtPosition(vector<point> vertexArray, vector<int> position,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {
	float valueX = 0, valueY = 0, valueZ = 0;
	int numberPosition = position.size(), offset,
		numberVertex = vertexArray.size(),
		numberElement = positionVertexSymmetry1.size() < positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	if (numberVertex > 0 && numberPosition > 0 && numberElement > 0) {
		for (int i = 0; i < numberPosition; i++) {
			//vị trí điểm được chọn
			offset = position.at(i);
			//tìm kiếm trong mảng đối xứng xem có không
			for (int k = 0; k < numberElement; k++) {
				if (offset == positionVertexSymmetry1.at(k)) {
					offset = positionVertexSymmetry2.at(k);
					if (offset < numberVertex) {
						valueX += vertexArray.at(offset).x;
						valueY += vertexArray.at(offset).y;
						valueZ += vertexArray.at(offset).z;
					}
					//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
					//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
					positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
					positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
					numberElement--;
					break;
				}else if (offset == positionVertexSymmetry2.at(k)) {
					offset = positionVertexSymmetry1.at(k);
					if (offset < numberVertex) {
						valueX += vertexArray.at(offset).x;
						valueY += vertexArray.at(offset).y;
						valueZ += vertexArray.at(offset).z;
					}
					//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
					//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
					positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
					positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
					numberElement--;
					break;
				}
				//nếu bất kỳ trường hợp nào đến cuối mảng vẫn chưa tìm được thì trả về {0.0,0.0,0.0}
				//luôn vì bắt buộc tất cả các điểm được chọn phải có điểm đối xứng thì mới được thực hiện
				//các biến đổi như rotate và scale(đối với translate thì không phải lo về trường hợp này)
				else if (k == numberElement - 1) {
					return{ NULL,NULL,NULL };
				}
			}
		}
		return{ valueX / numberPosition,valueY / numberPosition,valueZ / numberPosition };
	}
	else
	{
		return{ NULL,NULL,NULL };
	}
}
point getPointCenterVertexesSymmetryAtPosition(point *vertexArray, vector<int> position,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {
	float valueX = 0, valueY = 0, valueZ = 0;
	int numberPosition = position.size(),offset,
		numberElement = positionVertexSymmetry1.size() < positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	if (numberPosition > 0 && numberElement > 0) {
		for (int i = 0; i < numberPosition; i++) {
			//vị trí điểm được chọn
			offset = position.at(i);
			//tìm kiếm trong mảng đối xứng xem có không
			for (int k = 0; k < numberElement; k++) {
				if (offset == positionVertexSymmetry1.at(k)) {
					offset = positionVertexSymmetry2.at(k);

					valueX += vertexArray[offset].x;
					valueY += vertexArray[offset].y;
					valueZ += vertexArray[offset].z;

					//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
					//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
					positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
					positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
					numberElement--;
					break;
				}
				else if (offset == positionVertexSymmetry2.at(k)) {
					offset = positionVertexSymmetry1.at(k);

					valueX += vertexArray[offset].x;
					valueY += vertexArray[offset].y;
					valueZ += vertexArray[offset].z;

					//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
					//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
					positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
					positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
					numberElement--;
					break;
				}
				//nếu bất kỳ trường hợp nào đến cuối mảng vẫn chưa tìm được thì trả về {0.0,0.0,0.0}
				//luôn vì bắt buộc tất cả các điểm được chọn phải có điểm đối xứng thì mới được thực hiện
				//các biến đổi như rotate và scale(đối với translate thì không phải lo về trường hợp này)
				else if (k == numberElement - 1) {
					return{ NULL,NULL,NULL };
				}
			}
		}
		return{ valueX / numberPosition,valueY / numberPosition,valueZ / numberPosition };
	}
	else
	{
		return{ NULL,NULL,NULL };
	}
}

//hàm rotate Vertex
//mảng nhập vào là vector
void CaculatorRotateVertex(vector<point> &vertexArray, point centerOrigin, float deg, int axis) {
	//axis là thông báo xoay quanh trục nào
	//0 là trục x,1 là trục y,2 là trục z
	int numberVertex = vertexArray.size();
	try {
		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		for (int i = 0; i < numberVertex; i++) {
			vertexArray[i].x -= centerOrigin.x;
			vertexArray[i].y -= centerOrigin.y;
			vertexArray[i].z -= centerOrigin.z;
		}
		Quaternion q;
		Vector v;
		//xoay các vertex
		for (int i = 0; i < numberVertex; i++) {
			if (axis == 0) {
				q = Quaternion(Vector(1, 0, 0), deg);
				v = q * Vector(vertexArray.at(i).x, vertexArray.at(i).y, vertexArray.at(i).z);
			}
			else if (axis == 1) {
				q = Quaternion(Vector(0, 1, 0), deg);
				v = q * Vector(vertexArray.at(i).x, vertexArray.at(i).y, vertexArray.at(i).z);
			}
			else
			{
				q = Quaternion(Vector(0, 0, 1), deg);
				v = q * Vector(vertexArray.at(i).x, vertexArray.at(i).y, vertexArray.at(i).z);
			}
			vertexArray[i].x = v.x + centerOrigin.x;
			vertexArray[i].y = v.y + centerOrigin.y;
			vertexArray[i].z = v.z + centerOrigin.z;
		}
	}
	catch (...) {

	}
}
//mảng nhập vào là mảng
void CaculatorRotateVertex(point *vertexArray, int numberVertex, point centerOrigin, float deg, int axis) {
	try
	{
		//axis là thông báo xoay quanh trục nào
		//0 là trục x,1 là trục y,2 là trục z
		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		for (int i = 0; i < numberVertex; i++) {
			vertexArray[i].x -= centerOrigin.x;
			vertexArray[i].y -= centerOrigin.y;
			vertexArray[i].z -= centerOrigin.z;
		}
		Quaternion q;
		Vector v;
		//xoay các vertex
		for (int i = 0; i < numberVertex; i++) {
			if (axis == 0) {
				q = Quaternion(Vector(1, 0, 0), deg);
				v = q * Vector(vertexArray[i].x, vertexArray[i].y, vertexArray[i].z);
			}
			else if (axis == 1) {
				q = Quaternion(Vector(0, 1, 0), deg);
				v = q * Vector(vertexArray[i].x, vertexArray[i].y, vertexArray[i].z);
			}
			else
			{
				q = Quaternion(Vector(0, 0, 1), deg);
				v = q * Vector(vertexArray[i].x, vertexArray[i].y, vertexArray[i].z);
			}
			vertexArray[i].x = v.x + centerOrigin.x;
			vertexArray[i].y = v.y + centerOrigin.y;
			vertexArray[i].z = v.z + centerOrigin.z;
		}
	}
	catch (...)
	{

	}
}
//nhập vào là 1 vertex riêng lẻ
void CaculatorRotateVertex(point &vertexArray, point centerOrigin, float deg, int axis) {
	try
	{
		//0 là trục x,1 là trục y,2 là trục z
		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		vertexArray.x -= centerOrigin.x;
		vertexArray.y -= centerOrigin.y;
		vertexArray.z -= centerOrigin.z;
		Quaternion q;
		Vector v;
		//xoay các vertex
		if (axis == 0) {
			q = Quaternion(Vector(1, 0, 0), deg);
			v = q * Vector(vertexArray.x, vertexArray.y, vertexArray.z);
		}
		else if (axis == 1) {
			q = Quaternion(Vector(0, 1, 0), deg);
			v = q * Vector(vertexArray.x, vertexArray.y, vertexArray.z);
		}
		else
		{
			q = Quaternion(Vector(0, 0, 1), deg);
			v = q * Vector(vertexArray.x, vertexArray.y, vertexArray.z);
		}
		vertexArray.x = v.x + centerOrigin.x;
		vertexArray.y = v.y + centerOrigin.y;
		vertexArray.z = v.z + centerOrigin.z;
	}
	catch (...)
	{

	}
}
//hàm scale vertex
//mảng nhập vào là vector
void CaculatorScaleVertex(vector<point> &vertexArray, point centerOrigin, float scaleX, float scaleY, float scaleZ) {
	try
	{
		double matrix[3][3];
		//nếu không scale theo chiều nào thì đặt nó là 1.0
		matrix[0][0] = scaleX; matrix[0][1] = 0; matrix[0][2] = 0;
		matrix[1][0] = 0; matrix[1][1] = scaleY; matrix[1][2] = 0;
		matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = scaleZ;

		int numberVertex = vertexArray.size();
		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		for (int i = 0; i < numberVertex; i++) {
			vertexArray[i].x -= centerOrigin.x;
			vertexArray[i].y -= centerOrigin.y;
			vertexArray[i].z -= centerOrigin.z;
		}
		float v[3];
		//xoay các vertex
		for (int i = 0; i < numberVertex; i++) {
			//tính giá trị và để vào 1 biến
			v[0] = (matrix[0][0] * vertexArray[i].x + matrix[0][1] * vertexArray[i].y + matrix[0][2] * vertexArray[i].z);
			v[1] = (matrix[1][0] * vertexArray[i].x + matrix[1][1] * vertexArray[i].y + matrix[1][2] * vertexArray[i].z);
			v[2] = (matrix[2][0] * vertexArray[i].x + matrix[2][1] * vertexArray[i].y + matrix[2][2] * vertexArray[i].z);
			//sau khi xoay xong thì tăng giá trị lúc này giảm và gán giá trị đã tính vào mảng()
			vertexArray[i].x = v[0] + centerOrigin.x;
			vertexArray[i].y = v[1] + centerOrigin.y;
			vertexArray[i].z = v[2] + centerOrigin.z;
		}
	}
	catch (...)
	{

	}
}
//mảng nhập vào là 1 mảng vertex
void CaculatorScaleVertex(point *vertexArray, int numberVertex, point centerOrigin, float scaleX, float scaleY, float scaleZ) {
	try
	{
		double matrix[3][3];
		//nếu không scale theo chiều nào thì đặt nó là 1.0
		matrix[0][0] = scaleX; matrix[0][1] = 0; matrix[0][2] = 0;
		matrix[1][0] = 0; matrix[1][1] = scaleY; matrix[1][2] = 0;
		matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = scaleZ;

		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		for (int i = 0; i < numberVertex; i++) {
			vertexArray[i].x -= centerOrigin.x;
			vertexArray[i].y -= centerOrigin.y;
			vertexArray[i].z -= centerOrigin.z;
		}
		float v[3];
		//xoay các vertex
		for (int i = 0; i < numberVertex; i++) {
			//tính giá trị và để vào 1 biến
			v[0] = (matrix[0][0] * vertexArray[i].x + matrix[0][1] * vertexArray[i].y + matrix[0][2] * vertexArray[i].z);
			v[1] = (matrix[1][0] * vertexArray[i].x + matrix[1][1] * vertexArray[i].y + matrix[1][2] * vertexArray[i].z);
			v[2] = (matrix[2][0] * vertexArray[i].x + matrix[2][1] * vertexArray[i].y + matrix[2][2] * vertexArray[i].z);
			//sau khi xoay xong thì tăng giá trị lúc này giảm và gán giá trị đã tính vào mảng()
			vertexArray[i].x = v[0] + centerOrigin.x;
			vertexArray[i].y = v[1] + centerOrigin.y;
			vertexArray[i].z = v[2] + centerOrigin.z;
		}
	}
	catch (...)
	{

	}
}
//nhập vào là 1 vertex lẻ
void CaculatorScaleVertex(point &vertex, point centerOrigin, float scaleX, float scaleY, float scaleZ) {
	try
	{
		double matrix[3][3];
		//nếu không scale theo chiều nào thì đặt nó là 1.0
		matrix[0][0] = scaleX; matrix[0][1] = 0; matrix[0][2] = 0;
		matrix[1][0] = 0; matrix[1][1] = scaleY; matrix[1][2] = 0;
		matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = scaleZ;

		//lùi tâm xoay của hình về gốc tọa độ(bằng cách giảm tất cả các vertex),rồi mới xoay được
		vertex.x -= centerOrigin.x;
		vertex.y -= centerOrigin.y;
		vertex.z -= centerOrigin.z;
		float v[3];
		//xoay vertex
		v[0] = (matrix[0][0] * vertex.x + matrix[0][1] * vertex.y + matrix[0][2] * vertex.z);
		v[1] = (matrix[1][0] * vertex.x + matrix[1][1] * vertex.y + matrix[1][2] * vertex.z);
		v[2] = (matrix[2][0] * vertex.x + matrix[2][1] * vertex.y + matrix[2][2] * vertex.z);
		//sau khi xoay xong thì tăng giá trị lúc này giảm và gán giá trị đã tính vào mảng()
		vertex.x = v[0] + centerOrigin.x;
		vertex.y = v[1] + centerOrigin.y;
		vertex.z = v[2] + centerOrigin.z;
	}
	catch (...)
	{

	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//dịch chuyển tâm xoay
	//*** tâm xoay ở chế độ object chỉ dùng để làm vị trí hiện mũi tên dịch chuyển nên
	//không cần dịch chuyển centerObjectOrVerticesSymmetry(nếu có)
	centerObjectOrVertices.x += valuePlusX;
	centerObjectOrVertices.y += valuePlusY;
	centerObjectOrVertices.z += valuePlusZ;

	//nếu chỉ có 1 hình thì  kiêm tra xem hình được chọn có thông tin trong item nào của symmetryObject không
	int numberSymmetry = symmetryObjects.size();
	SymmetryObjects symmetryCheck;
	bool isHaveSymmetryObject = false;
	if (itemsChoice.size() == 1) {
		itemChoice itemCheck = itemsChoice.back();
		for (int i = 0; i < numberSymmetry; i++) {
			symmetryCheck = symmetryObjects.at(i);
			if (itemCheck.object == symmetryCheck.object1 &&
				(itemCheck.positionOfChoice == symmetryCheck.positionInArray1 ||
					itemCheck.positionOfChoice == symmetryCheck.positionInArray2)) {

				isHaveSymmetryObject = true;
				break;
			}
		}
	}
	

	//dịch chuyển hình
	//dịch chuyển tất cả các item đang được chọn
	int numberItemChoice = itemsChoice.size();
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
			for (int j = 0; j < 3; j++) {
				tria->vertexArray[j].x += valuePlusX;
				tria->vertexArray[j].y += valuePlusY;
				tria->vertexArray[j].z += valuePlusZ;
			}
			tria->centerObject.x += valuePlusX;
			tria->centerObject.y += valuePlusY;
			tria->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					tria = triangleArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					tria = triangleArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < 3; j++) {
					tria->vertexArray[j].x += valuePlusX;
					tria->vertexArray[j].y += valuePlusY;
					tria->vertexArray[j].z += valuePlusZ;
				}
				tria->centerObject.x += valuePlusX;
				tria->centerObject.y += valuePlusY;
				tria->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			int numberVertex = triaStrip->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				triaStrip->vertexArray.at(j).x += valuePlusX;
				triaStrip->vertexArray.at(j).y += valuePlusY;
				triaStrip->vertexArray.at(j).z += valuePlusZ;
			}
			triaStrip->centerObject.x += valuePlusX;
			triaStrip->centerObject.y += valuePlusY;
			triaStrip->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					triaStrip->vertexArray.at(j).x += valuePlusX;
					triaStrip->vertexArray.at(j).y += valuePlusY;
					triaStrip->vertexArray.at(j).z += valuePlusZ;
				}
				triaStrip->centerObject.x += valuePlusX;
				triaStrip->centerObject.y += valuePlusY;
				triaStrip->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			int numberVertex = triaFan->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				triaFan->vertexArray.at(j).x += valuePlusX;
				triaFan->vertexArray.at(j).y += valuePlusY;
				triaFan->vertexArray.at(j).z += valuePlusZ;
			}
			triaFan->centerObject.x += valuePlusX;
			triaFan->centerObject.y += valuePlusY;
			triaFan->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaFan = triaFanArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaFan = triaFanArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					triaFan->vertexArray.at(j).x += valuePlusX;
					triaFan->vertexArray.at(j).y += valuePlusY;
					triaFan->vertexArray.at(j).z += valuePlusZ;
				}
				triaFan->centerObject.x += valuePlusX;
				triaFan->centerObject.y += valuePlusY;
				triaFan->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 10:
		{
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			int numberVertex = sphere->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				sphere->vertexArray.at(j).x += valuePlusX;
				sphere->vertexArray.at(j).y += valuePlusY;
				sphere->vertexArray.at(j).z += valuePlusZ;
			}
			sphere->centerObject.x += valuePlusX;
			sphere->centerObject.y += valuePlusY;
			sphere->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					sphere = sphereArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					sphere = sphereArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					sphere->vertexArray.at(j).x += valuePlusX;
					sphere->vertexArray.at(j).y += valuePlusY;
					sphere->vertexArray.at(j).z += valuePlusZ;
				}
				sphere->centerObject.x += valuePlusX;
				sphere->centerObject.y += valuePlusY;
				sphere->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 11:
		{
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			int numberVertex = cube->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				cube->vertexArray.at(j).x += valuePlusX;
				cube->vertexArray.at(j).y += valuePlusY;
				cube->vertexArray.at(j).z += valuePlusZ;
			}
			cube->centerObject.x += valuePlusX;
			cube->centerObject.y += valuePlusY;
			cube->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					cube->vertexArray.at(j).x += valuePlusX;
					cube->vertexArray.at(j).y += valuePlusY;
					cube->vertexArray.at(j).z += valuePlusZ;
				}
				cube->centerObject.x += valuePlusX;
				cube->centerObject.y += valuePlusY;
				cube->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 12:
		{
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			int numberVertex = cube->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				cube->vertexArray.at(j).x += valuePlusX;
				cube->vertexArray.at(j).y += valuePlusY;
				cube->vertexArray.at(j).z += valuePlusZ;
			}
			cube->centerObject.x += valuePlusX;
			cube->centerObject.y += valuePlusY;
			cube->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeRoundArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeRoundArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					cube->vertexArray.at(j).x += valuePlusX;
					cube->vertexArray.at(j).y += valuePlusY;
					cube->vertexArray.at(j).z += valuePlusZ;
				}
				cube->centerObject.x += valuePlusX;
				cube->centerObject.y += valuePlusY;
				cube->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 13:
		{
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			int numberVertex = cone->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				cone->vertexArray.at(j).x += valuePlusX;
				cone->vertexArray.at(j).y += valuePlusY;
				cone->vertexArray.at(j).z += valuePlusZ;
			}
			cone->centerObject.x += valuePlusX;
			cone->centerObject.y += valuePlusY;
			cone->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cone = coneArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cone = coneArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					cone->vertexArray.at(j).x += valuePlusX;
					cone->vertexArray.at(j).y += valuePlusY;
					cone->vertexArray.at(j).z += valuePlusZ;
				}
				cone->centerObject.x += valuePlusX;
				cone->centerObject.y += valuePlusY;
				cone->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 14:
		{
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			int numberVertex = cylinder->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				cylinder->vertexArray.at(j).x += valuePlusX;
				cylinder->vertexArray.at(j).y += valuePlusY;
				cylinder->vertexArray.at(j).z += valuePlusZ;
			}
			cylinder->centerObject.x += valuePlusX;
			cylinder->centerObject.y += valuePlusY;
			cylinder->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = cylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = cylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					cylinder->vertexArray.at(j).x += valuePlusX;
					cylinder->vertexArray.at(j).y += valuePlusY;
					cylinder->vertexArray.at(j).z += valuePlusZ;
				}
				cylinder->centerObject.x += valuePlusX;
				cylinder->centerObject.y += valuePlusY;
				cylinder->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 15:
		{
			PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
			for (int i = 0; i<5; i++) {
				pyr->vertexArray[i].x += valuePlusX;
				pyr->vertexArray[i].y += valuePlusY;
				pyr->vertexArray[i].z += valuePlusZ;
			}
			pyr->centerObject.x += valuePlusX;
			pyr->centerObject.y += valuePlusY;
			pyr->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					pyr = pyrArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					pyr = pyrArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int i = 0; i<5; i++) {
					pyr->vertexArray[i].x += valuePlusX;
					pyr->vertexArray[i].y += valuePlusY;
					pyr->vertexArray[i].z += valuePlusZ;
				}
				pyr->centerObject.x += valuePlusX;
				pyr->centerObject.y += valuePlusY;
				pyr->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 16:
		{
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			int numberVertex = cylinder->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				cylinder->vertexArray.at(j).x += valuePlusX;
				cylinder->vertexArray.at(j).y += valuePlusY;
				cylinder->vertexArray.at(j).z += valuePlusZ;
			}
			cylinder->centerObject.x += valuePlusX;
			cylinder->centerObject.y += valuePlusY;
			cylinder->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					cylinder->vertexArray.at(j).x += valuePlusX;
					cylinder->vertexArray.at(j).y += valuePlusY;
					cylinder->vertexArray.at(j).z += valuePlusZ;
				}
				cylinder->centerObject.x += valuePlusX;
				cylinder->centerObject.y += valuePlusY;
				cylinder->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 17:
		{
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			int numberVertex = torus->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				torus->vertexArray.at(j).x += valuePlusX;
				torus->vertexArray.at(j).y += valuePlusY;
				torus->vertexArray.at(j).z += valuePlusZ;
			}
			torus->centerObject.x += valuePlusX;
			torus->centerObject.y += valuePlusY;
			torus->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					torus = torusArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					torus = torusArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					torus->vertexArray.at(j).x += valuePlusX;
					torus->vertexArray.at(j).y += valuePlusY;
					torus->vertexArray.at(j).z += valuePlusZ;
				}
				torus->centerObject.x += valuePlusX;
				torus->centerObject.y += valuePlusY;
				torus->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 18:
		{
			PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
			for (int j = 0; j < 4; j++) {
				picture->vertexArray[j].x += valuePlusX;
				picture->vertexArray[j].y += valuePlusY;
				picture->vertexArray[j].z += valuePlusZ;
			}
			picture->centerObject.x += valuePlusX;
			picture->centerObject.y += valuePlusY;
			picture->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					picture = pictureArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					picture = pictureArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < 4; j++) {
					picture->vertexArray[j].x += valuePlusX;
					picture->vertexArray[j].y += valuePlusY;
					picture->vertexArray[j].z += valuePlusZ;
				}
				picture->centerObject.x += valuePlusX;
				picture->centerObject.y += valuePlusY;
				picture->centerObject.z += valuePlusZ;
			}
		}
		break;
		case 19:
		{
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			int numberVertex = object->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				object->vertexArray.at(j).x += valuePlusX;
				object->vertexArray.at(j).y += valuePlusY;
				object->vertexArray.at(j).z += valuePlusZ;
			}
			object->centerObject.x += valuePlusX;
			object->centerObject.y += valuePlusY;
			object->centerObject.z += valuePlusZ;

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					object = objectCustom0Array.at(symmetryCheck.positionInArray2);
				}
				else
				{
					object = objectCustom0Array.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_translateX) {
					valuePlusX = -valuePlusX;
				}
				if (symmetry_translateY) {
					valuePlusY = -valuePlusY;
				}
				if (symmetry_translateZ) {
					valuePlusZ = -valuePlusZ;
				}
				for (int j = 0; j < numberVertex; j++) {
					object->vertexArray.at(j).x += valuePlusX;
					object->vertexArray.at(j).y += valuePlusY;
					object->vertexArray.at(j).z += valuePlusZ;
				}
				object->centerObject.x += valuePlusX;
				object->centerObject.y += valuePlusY;
				object->centerObject.z += valuePlusZ;
			}
		}
		break;
		default:
			break;
		}
	}

}
//hàm dich chuyển chỉ duy nhất vertex choice
void moveVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point *vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		vertexArray[positionElement].x += valuePlusX;
		vertexArray[positionElement].y += valuePlusY;
		vertexArray[positionElement].z += valuePlusZ;
		
	}
}
void moveVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, vector<point> &vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		vertexArray[positionElement].x += valuePlusX;
		vertexArray[positionElement].y += valuePlusY;
		vertexArray[positionElement].z += valuePlusZ;
	}
}

//hàm dịch chuyển vertex chọn và vertex nghịch đảo
void moveVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point *vertexArray,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		vertexArray[positionElement].x += valuePlusX;
		vertexArray[positionElement].y += valuePlusY;
		vertexArray[positionElement].z += valuePlusZ;
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_translateX) {
						vertexArray[positionElement].x -= valuePlusX;
					}
					else
					{
						vertexArray[positionElement].x += valuePlusX;
					}

					if (symmetry_translateY) {
						vertexArray[positionElement].y -= valuePlusY;
					}
					else
					{
						vertexArray[positionElement].y += valuePlusY;
					}

					if (symmetry_translateZ) {
						vertexArray[positionElement].z -= valuePlusZ;
					}
					else
					{
						vertexArray[positionElement].z += valuePlusZ;
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_translateX) {
						vertexArray[positionElement].x -= valuePlusX;
					}
					else
					{
						vertexArray[positionElement].x += valuePlusX;
					}

					if (symmetry_translateY) {
						vertexArray[positionElement].y -= valuePlusY;
					}
					else
					{
						vertexArray[positionElement].y += valuePlusY;
					}

					if (symmetry_translateZ) {
						vertexArray[positionElement].z -= valuePlusZ;
					}
					else
					{
						vertexArray[positionElement].z += valuePlusZ;
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
void moveVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, vector<point> &vertexArray,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		vertexArray[positionElement].x += valuePlusX;
		vertexArray[positionElement].y += valuePlusY;
		vertexArray[positionElement].z += valuePlusZ;
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_translateX) {
						vertexArray[positionElement].x -= valuePlusX;
					}
					else
					{
						vertexArray[positionElement].x += valuePlusX;
					}

					if (symmetry_translateY) {
						vertexArray[positionElement].y -= valuePlusY;
					}
					else
					{
						vertexArray[positionElement].y += valuePlusY;
					}

					if (symmetry_translateZ) {
						vertexArray[positionElement].z -= valuePlusZ;
					}
					else
					{
						vertexArray[positionElement].z += valuePlusZ;
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_translateX) {
						vertexArray[positionElement].x -= valuePlusX;
					}
					else
					{
						vertexArray[positionElement].x += valuePlusX;
					}

					if (symmetry_translateY) {
						vertexArray[positionElement].y -= valuePlusY;
					}
					else
					{
						vertexArray[positionElement].y += valuePlusY;
					}

					if (symmetry_translateZ) {
						vertexArray[positionElement].z -= valuePlusZ;
					}
					else
					{
						vertexArray[positionElement].z += valuePlusZ;
					}
				}
				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	//dịch chuyển tâm xoay
	centerObjectOrVertices.x += valuePlusX;
	centerObjectOrVertices.y += valuePlusY;
	centerObjectOrVertices.z += valuePlusZ;

	bool isTransformVerticesSymmetry = false, isTransformObjectSymmetry = false;
	int numberElement;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectCheck;
	itemChoice item = itemsChoice.at(0);

	//nếu tâm xoay của các item nghịch đảo khác NULL thì cho phép biến đổi item nghịch đảo
	if (centerObjectOrVerticesSymmetry.x != NULL) {
		//phải kiểm tra tiếp xem đối tượng này có vertex đối xứng không để kiểm tra
		//nếu không có thì chỉ di chuyển các vertex được chọn thôi
		numberElement = symmetryVertices.size();
		for (int i = 0; i < numberElement; i++) {
			symmetryVerticesCheck = symmetryVertices.at(i);
			if (symmetryVerticesCheck.object == item.object &&
				symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
				//bật dịch chuyển các vertex đối xứng
				isTransformVerticesSymmetry = true;
				break;
			}
		}
		//nếu không có vertex đối xứng thì kiểm tra đối tượng này có object đối xứng không
		if (!isTransformVerticesSymmetry) {
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object &&
					(symmetryObjectCheck.positionInArray1 == item.positionOfChoice||
						symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {

					//bật dịch chuyển các vertex đối xứng
					isTransformObjectSymmetry = true;
					break;
				}
			}
		}

		//dịch chuyển tâm của các item đối xứng
		if (symmetry_translateX) {
			centerObjectOrVerticesSymmetry.x -= valuePlusX;
		}
		else
		{
			centerObjectOrVerticesSymmetry.x += valuePlusX;
		}

		if (symmetry_translateX) {
			centerObjectOrVerticesSymmetry.y -= valuePlusY;
		}
		else
		{
			centerObjectOrVerticesSymmetry.y += valuePlusY;
		}

		if (symmetry_translateX) {
			centerObjectOrVerticesSymmetry.z -= valuePlusZ;
		}
		else
		{
			centerObjectOrVerticesSymmetry.z += valuePlusZ;
		}
	}

	//biên numberElement chứa số phần tử nhỏ nhất của 2 mảng vì nếu mảng này có phần
	//tử thứ k mà mảng kia không có thì cũng như không
	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				tria->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, tria->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				tria = triangleArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				tria = triangleArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 3;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, tria->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, tria->vertexArray);
		}
		//tính toán lại center triangle
		tria->centerObject = getPointCenterVertexes(tria->vertexArray, 3);
		CaculatorNormalForTriangles(tria->vertexArray, tria->normalVector);
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				triaStrip->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaStrip->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaStrip->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaStrip->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaStrip->vertexArray);
		}
		triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				triaFan->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaFan->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaFan->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaFan->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, triaFan->vertexArray);
		}
		triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				sphere->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, sphere->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, sphere->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, sphere->vertexArray);
		}
		sphere->centerObject = getPointCenterVertexes(sphere->vertexArray);
		CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				cube->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cube->vertexArray);
		}
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
			, cube->vertexArray, cube->normalVector);
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				cube->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cube->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cube->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cube->vertexArray);
		}
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				cone->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cone->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cone->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cone->vertexArray);
		}
		cone->centerObject = getPointCenterVertexes(cone->vertexArray);
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				cylinder->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);
		}
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 15:
	{
		PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				pyr->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, pyr->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				pyr = pyrArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				pyr = pyrArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 5;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, pyr->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, pyr->vertexArray);
		}
		CaculatorNormalForPyramid(pyr->vertexArray, pyr->normalVector);
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				cylinder->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, cylinder->vertexArray);
		}
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				torus->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, torus->vertexArray);
		}
		torus->centerObject = getPointCenterVertexes(torus->vertexArray);
		CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				picture->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, picture->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 4;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, picture->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, picture->vertexArray);
		}
		//tính toán lại center triangle
		picture->centerObject = getPointCenterVertexes(picture->vertexArray, 4);
		CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			moveVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ, positionVerticesChoice,
				object->vertexArray, symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, object->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_translateX) {
				valuePlusX = -valuePlusX;
			}
			if (symmetry_translateY) {
				valuePlusY = -valuePlusY;
			}
			if (symmetry_translateZ) {
				valuePlusZ = -valuePlusZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, object->vertexArray);
		}
		else
		{
			moveVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, object->vertexArray);
		}
		object->centerObject = getPointCenterVertexes(object->vertexArray);
		CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
	}
	break;
	default:
		break;
	}
}
//hàm dịch chuyển hình cũng như vertex(tùy chế độ đang chọn)
//hàm này sẽ phân chia gọi đến các hàm dịch chuyển vertex hay object và 
//xác định các giá trị nào dựa trên arrow và quad
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	//dịch chuyển tâm xoay
	if (whichArrowChoice == -1) {
		if (whichQuadChoice == 0) {
			if (modelEditStyle == 0) {
				moveObject(valuePlus2, valuePlus1, 0.0, itemsChoice,
					centerObjectOrVertices, 
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(valuePlus2, valuePlus1, 0.0, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else if (whichQuadChoice == 1)
		{
			if (modelEditStyle == 0) {
				moveObject(valuePlus1, 0.0, valuePlus2, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(valuePlus1, 0.0, valuePlus2, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else if (whichQuadChoice == 2)
		{
			if (modelEditStyle == 0) {
				moveObject(0.0, valuePlus2, valuePlus1, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(0.0, valuePlus2, valuePlus1, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else {
			if (modelEditStyle == 0) {
				moveObject(valuePlus1, valuePlus2, valuePlus3, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(valuePlus1, valuePlus2, valuePlus3, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
	}
	else
	{
		if (whichArrowChoice == 0) {
			if (modelEditStyle == 0) {
				moveObject(valuePlus1, 0.0, 0.0, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(valuePlus1, 0.0, 0.0, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else if (whichArrowChoice == 1)
		{
			if (modelEditStyle == 0) {
				moveObject(0.0, valuePlus1, 0.0, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(0.0, valuePlus1, 0.0, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else
		{
			if (modelEditStyle == 0) {
				moveObject(0.0, 0.0, valuePlus1, itemsChoice,
					centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				moveVertex(0.0, 0.0, valuePlus1, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//nếu chỉ có 1 hình thì  kiêm tra xem hình được chọn có thông tin trong item nào của symmetryObject không
	int numberSymmetry = symmetryObjects.size();
	SymmetryObjects symmetryCheck;
	bool isHaveSymmetryObject = false;
	if (itemsChoice.size() == 1) {
		itemChoice itemCheck = itemsChoice.back();
		for (int i = 0; i < numberSymmetry; i++) {
			symmetryCheck = symmetryObjects.at(i);
			if (itemCheck.object == symmetryCheck.object1 &&
				(itemCheck.positionOfChoice == symmetryCheck.positionInArray1 ||
					itemCheck.positionOfChoice == symmetryCheck.positionInArray2)) {

				isHaveSymmetryObject = true;
				break;
			}
		}
	}

	int numberItemChoice = itemsChoice.size();
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
			CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(tria->centerObject, tria->centerObject, deg, axis);
			CaculatorNormalForTriangles(tria->vertexArray, tria->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					tria = triangleArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					tria = triangleArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if(axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if(axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(tria->centerObject, tria->centerObject, deg, axis);
				CaculatorNormalForTriangles(tria->vertexArray, tria->normalVector);
			}
		}
		break;
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, deg, axis);
			CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, deg, axis);
				CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
			}
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, deg, axis);
			CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaFan = triaFanArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaFan = triaFanArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, deg, axis);
				CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
			}
		}
		break;
		case 10:
		{
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					sphere = sphereArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					sphere = sphereArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 11:
		{
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 12:
		{
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeRoundArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeRoundArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 13:
		{
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cone->vertexArray, cone->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cone->centerObject, cone->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cone = coneArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cone = coneArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(cone->vertexArray, cone->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cone->centerObject, cone->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 14:
		{
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = cylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = cylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 15:
		{
			PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
			CaculatorRotateVertex(pyr->vertexArray, 6, pyr->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					pyr = pyrArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					pyr = pyrArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(pyr->vertexArray, 6, pyr->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 16:
		{
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 17:
		{
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			CaculatorRotateVertex(torus->vertexArray, torus->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(torus->centerObject, torus->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					torus = torusArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					torus = torusArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(torus->vertexArray, torus->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(torus->centerObject, torus->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		case 18:
		{
			PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
			CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(picture->centerObject, picture->centerObject, deg, axis);
			//xoay normal
			CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					picture = pictureArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					picture = pictureArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(picture->centerObject, picture->centerObject, deg, axis);
				//xoay normal
				CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
			}
		}
		break;
		case 19:
		{
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			CaculatorRotateVertex(object->vertexArray, object->centerObject, deg, axis);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(object->centerObject, object->centerObject, deg, axis);
			//tính toán normal vector
			CaculatorRotateVertex(object->normalVector, { 0,0,0 }, deg, axis);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					object = objectCustom0Array.at(symmetryCheck.positionInArray2);
				}
				else
				{
					object = objectCustom0Array.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (axis == 0) {
					if (symmetry_rotateX) {
						deg = -deg;
					}
				}
				else if (axis == 1) {
					if (symmetry_rotateY) {
						deg = -deg;
					}
				}
				else
				{
					if (symmetry_rotateZ) {
						deg = -deg;
					}
				}

				CaculatorRotateVertex(object->vertexArray, object->centerObject, deg, axis);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(object->centerObject, object->centerObject, deg, axis);
				//tính toán normal vector
				CaculatorRotateVertex(object->normalVector, { 0,0,0 }, deg, axis);
			}
		}
		break;
		default:
			break;
		}
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//nếu chỉ có 1 hình thì  kiêm tra xem hình được chọn có thông tin trong item nào của symmetryObject không
	int numberSymmetry = symmetryObjects.size();
	SymmetryObjects symmetryCheck;
	bool isHaveSymmetryObject = false;
	if (itemsChoice.size() == 1) {
		itemChoice itemCheck = itemsChoice.back();
		for (int i = 0; i < numberSymmetry; i++) {
			symmetryCheck = symmetryObjects.at(i);
			if (itemCheck.object == symmetryCheck.object1 &&
				(itemCheck.positionOfChoice == symmetryCheck.positionInArray1 ||
					itemCheck.positionOfChoice == symmetryCheck.positionInArray2)) {

				isHaveSymmetryObject = true;
				break;
			}
		}
	}

	int numberItemChoice = itemsChoice.size();
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
			CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateX, 0);
			CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateY, 1);
			CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateX, 0);
			CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateY, 1);
			CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateZ, 2);
			CaculatorNormalForTriangles(tria->vertexArray, tria->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					tria = triangleArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					tria = triangleArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateX, 0);
				CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateY, 1);
				CaculatorRotateVertex(tria->vertexArray, 3, tria->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateX, 0);
				CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateY, 1);
				CaculatorRotateVertex(tria->centerObject, tria->centerObject, rotateZ, 2);
				CaculatorNormalForTriangles(tria->vertexArray, tria->normalVector);
			}
		}
		break;
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateX, 0);
			CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateY, 1);
			CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateX, 0);
			CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateY, 1);
			CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateZ, 2);
			CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateX, 0);
				CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateY, 1);
				CaculatorRotateVertex(triaStrip->vertexArray, triaStrip->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateX, 0);
				CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateY, 1);
				CaculatorRotateVertex(triaStrip->centerObject, triaStrip->centerObject, rotateZ, 2);
				CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
			}
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateX, 0);
			CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateY, 1);
			CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateX, 0);
			CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateY, 1);
			CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateZ, 2);
			CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaFan = triaFanArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaFan = triaFanArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateX, 0);
				CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateY, 1);
				CaculatorRotateVertex(triaFan->vertexArray, triaFan->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateX, 0);
				CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateY, 1);
				CaculatorRotateVertex(triaFan->centerObject, triaFan->centerObject, rotateZ, 2);
				CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
			}
		}
		break;
		case 10:
		{
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateX, 0);
			CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateY, 1);
			CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateX, 0);
			CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateY, 1);
			CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					sphere = sphereArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					sphere = sphereArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateX, 0);
				CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateY, 1);
				CaculatorRotateVertex(sphere->vertexArray, sphere->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateX, 0);
				CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateY, 1);
				CaculatorRotateVertex(sphere->centerObject, sphere->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(sphere->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 11:
		{
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateX, 0);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateY, 1);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateX, 0);
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateY, 1);
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateX, 0);
				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateY, 1);
				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateX, 0);
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateY, 1);
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 12:
		{
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateX, 0);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateY, 1);
			CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateX, 0);
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateY, 1);
			CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeRoundArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeRoundArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateX, 0);
				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateY, 1);
				CaculatorRotateVertex(cube->vertexArray, cube->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateX, 0);
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateY, 1);
				CaculatorRotateVertex(cube->centerObject, cube->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(cube->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 13:
		{
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateX, 0);
			CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateY, 1);
			CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateX, 0);
			CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateY, 1);
			CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cone = coneArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cone = coneArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateX, 0);
				CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateY, 1);
				CaculatorRotateVertex(cone->vertexArray, cone->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateX, 0);
				CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateY, 1);
				CaculatorRotateVertex(cone->centerObject, cone->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(cone->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 14:
		{
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateX, 0);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateY, 1);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateX, 0);
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateY, 1);
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = cylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = cylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateX, 0);
				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateY, 1);
				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateX, 0);
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateY, 1);
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 15:
		{
			PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
			CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateX, 0);
			CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateY, 1);
			CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateX, 0);
			CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateY, 1);
			CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					pyr = pyrArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					pyr = pyrArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateX, 0);
				CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateY, 1);
				CaculatorRotateVertex(pyr->vertexArray, 4, pyr->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateX, 0);
				CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateY, 1);
				CaculatorRotateVertex(pyr->centerObject, pyr->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(pyr->normalVector, 6, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 16:
		{
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateX, 0);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateY, 1);
			CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateX, 0);
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateY, 1);
			CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateX, 0);
				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateY, 1);
				CaculatorRotateVertex(cylinder->vertexArray, cylinder->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateX, 0);
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateY, 1);
				CaculatorRotateVertex(cylinder->centerObject, cylinder->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(cylinder->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 17:
		{
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateX, 0);
			CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateY, 1);
			CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateX, 0);
			CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateY, 1);
			CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					torus = torusArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					torus = torusArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateX, 0);
				CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateY, 1);
				CaculatorRotateVertex(torus->vertexArray, torus->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateX, 0);
				CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateY, 1);
				CaculatorRotateVertex(torus->centerObject, torus->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(torus->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		case 18:
		{
			PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
			CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateX, 0);
			CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateY, 1);
			CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateX, 0);
			CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateY, 1);
			CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateZ, 2);
			//xoay normal
			CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					picture = pictureArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					picture = pictureArray.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateX, 0);
				CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateY, 1);
				CaculatorRotateVertex(picture->vertexArray, 4, picture->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateX, 0);
				CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateY, 1);
				CaculatorRotateVertex(picture->centerObject, picture->centerObject, rotateZ, 2);
				//xoay normal
				CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
			}
		}
		break;
		case 19:
		{
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateX, 0);
			CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateY, 1);
			CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateZ, 2);
			//xoay tâm của hình theo góc xoay
			CaculatorRotateVertex(object->centerObject, object->centerObject, rotateX, 0);
			CaculatorRotateVertex(object->centerObject, object->centerObject, rotateY, 1);
			CaculatorRotateVertex(object->centerObject, object->centerObject, rotateZ, 2);
			//tính toán normal vector
			CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateX, 0);
			CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateY, 1);
			CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateZ, 2);

			//kiểm tra xem có object đối xứng không để dịch chuyển luôn
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					object = objectCustom0Array.at(symmetryCheck.positionInArray2);
				}
				else
				{
					object = objectCustom0Array.at(symmetryCheck.positionInArray1);
				}
				//xác định xem có đối nghịch x,y,z không
				if (symmetry_rotateX) {
					rotateX = -rotateX;
				}
				if (symmetry_rotateY) {
					rotateY = -rotateY;
				}
				if (symmetry_rotateZ) {
					rotateZ = -rotateZ;
				}

				CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateX, 0);
				CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateY, 1);
				CaculatorRotateVertex(object->vertexArray, object->centerObject, rotateZ, 2);
				//xoay tâm của hình theo góc xoay
				CaculatorRotateVertex(object->centerObject, object->centerObject, rotateX, 0);
				CaculatorRotateVertex(object->centerObject, object->centerObject, rotateY, 1);
				CaculatorRotateVertex(object->centerObject, object->centerObject, rotateZ, 2);
				//tính toán normal vector
				CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateX, 0);
				CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateY, 1);
				CaculatorRotateVertex(object->normalVector, { 0,0,0 }, rotateZ, 2);
			}
		}
		break;
		default:
			break;
		}
	}
}
//hàm chỉ xoay vertex đang được chọn
void rotateVertexChoice(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateX, 0);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateY, 1);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateZ, 2);
	}

}
void rotateVertexChoice(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, deg, axis);
	}
}
void rotateVertexChoice(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateX, 0);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateY, 1);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateZ, 2);
	}
}
void rotateVertexChoice(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, deg, axis);
	}
}


//hàm xoay vertex chọn và vertex nghịch đảo
void rotateVertexChoiceAndSymmetry(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateX, 0);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateY, 1);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateZ, 2);
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_rotateX) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateX, 0);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateX, 0);
					}

					if (symmetry_rotateY) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateY, 1);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateY, 1);
					}

					if (symmetry_rotateZ) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateZ, 2);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateZ, 2);
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_rotateX) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateX, 0);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateX, 0);
					}

					if (symmetry_rotateY) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateY, 1);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateY, 1);
					}

					if (symmetry_rotateZ) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateZ, 2);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateZ, 2);
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}

}
void rotateVertexChoiceAndSymmetry(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, deg, axis);
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (axis == 0) {
						if (symmetry_rotateX) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else if (axis == 1) {
						if (symmetry_rotateY) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else
					{
						if (symmetry_rotateZ) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (axis == 0) {
						if (symmetry_rotateX) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else if (axis == 1) {
						if (symmetry_rotateY) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else
					{
						if (symmetry_rotateZ) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
void rotateVertexChoiceAndSymmetry(float rotateX, float rotateY, float rotateZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateX, 0);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateY, 1);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, rotateZ, 2);
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_rotateX) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateX, 0);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateX, 0);
					}

					if (symmetry_rotateY) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateY, 1);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateY, 1);
					}

					if (symmetry_rotateZ) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateZ, 2);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateZ, 2);
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (symmetry_rotateX) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateX, 0);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateX, 0);
					}

					if (symmetry_rotateY) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateY, 1);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateY, 1);
					}

					if (symmetry_rotateZ) {
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -rotateZ, 2);
					}
					else
					{
						CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, rotateZ, 2);
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
void rotateVertexChoiceAndSymmetry(float deg, int axis,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVertices, deg, axis);
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (axis == 0) {
						if (symmetry_rotateX) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else if (axis == 1) {
						if (symmetry_rotateY) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else
					{
						if (symmetry_rotateZ) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					if (axis == 0) {
						if (symmetry_rotateX) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else if (axis == 1) {
						if (symmetry_rotateY) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
					else
					{
						if (symmetry_rotateZ) {
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, -deg, axis);
						}
						else
						{
							CaculatorRotateVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry, deg, axis);
						}
					}
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	bool isTransformVerticesSymmetry = false, isTransformObjectSymmetry = false;
	int numberElement;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectCheck;
	itemChoice item = itemsChoice.at(0);

	//nếu tâm xoay của các item nghịch đảo khác NULL thì cho phép biến đổi item nghịch đảo
	if (centerObjectOrVerticesSymmetry.x != NULL) {
		//phải kiểm tra tiếp xem đối tượng này có vertex đối xứng không để kiểm tra
		//nếu không có thì chỉ di chuyển các vertex được chọn thôi
		numberElement = symmetryVertices.size();
		for (int i = 0; i < numberElement; i++) {
			symmetryVerticesCheck = symmetryVertices.at(i);
			if (symmetryVerticesCheck.object == item.object &&
				symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
				//bật dịch chuyển các vertex đối xứng
				isTransformVerticesSymmetry = true;
				break;
			}
		}
		//nếu không có vertex đối xứng thì kiểm tra đối tượng này có object đối xứng không
		if (!isTransformVerticesSymmetry) {
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object &&
					(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
						symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {

					//bật dịch chuyển các vertex đối xứng
					isTransformObjectSymmetry = true;
					break;
				}
			}
		}
	}

	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *triangle = triangleArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triangle->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 3;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triangle->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);
		}
		
		//tính toán lại center triangle
		triangle->centerObject = getPointCenterVertexes(triangle->vertexArray, 3);
		CaculatorNormalForTriangles(triangle->vertexArray, triangle->normalVector);
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaStrip->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaStrip->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaStrip->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);
		}
		
		//tính toán lại center
		triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaFan->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaFan->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaFan->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);
		}
		
		//tính toán lại center
		triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, sphere->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, sphere->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);
		}
		
		//tính toán lại center 
		sphere->centerObject = getPointCenterVertexes(sphere->vertexArray);
		CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
			sphere->vertexArray, sphere->normalVector);
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cube->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cone->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cone->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);
		}
		
		//tính toán lại center 
		cone->centerObject = getPointCenterVertexes(cone->vertexArray);
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
			cone->vertexArray, cone->normalVector);
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, torus->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, torus->vertexArray);
		}
		
		//tính toán lại center 
		torus->centerObject = getPointCenterVertexes(torus->vertexArray);
		CaculatorNormalForTorus(torus->depthRoundCake,
			torus->vertexArray, torus->normalVector);
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, picture->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 4;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, picture->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);
		}
		//tính toán lại center 
		picture->centerObject = getPointCenterVertexes(picture->vertexArray, 4);
		CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, object->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (axis == 0) {
				if (symmetry_rotateX) {
					deg = -deg;
				}
			}
			else if (axis == 1) {
				if (symmetry_rotateY) {
					deg = -deg;
				}
			}
			else
			{
				if (symmetry_rotateZ) {
					deg = -deg;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, object->vertexArray);
		}
		else
		{
			rotateVertexChoice(deg, axis,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);
		}

		//tính toán lại center 
		object->centerObject = getPointCenterVertexes(object->vertexArray);
		CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
	}
	break;
	default:
		break;
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	bool isTransformVerticesSymmetry = false, isTransformObjectSymmetry = false;
	int numberElement;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectCheck;
	itemChoice item = itemsChoice.at(0);

	//nếu tâm xoay của các item nghịch đảo khác NULL thì cho phép biến đổi item nghịch đảo
	if (centerObjectOrVerticesSymmetry.x != NULL) {
		//phải kiểm tra tiếp xem đối tượng này có vertex đối xứng không để kiểm tra
		//nếu không có thì chỉ di chuyển các vertex được chọn thôi
		numberElement = symmetryVertices.size();
		for (int i = 0; i < numberElement; i++) {
			symmetryVerticesCheck = symmetryVertices.at(i);
			if (symmetryVerticesCheck.object == item.object &&
				symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
				//bật dịch chuyển các vertex đối xứng
				isTransformVerticesSymmetry = true;
				break;
			}
		}
		//nếu không có vertex đối xứng thì kiểm tra đối tượng này có object đối xứng không
		if (!isTransformVerticesSymmetry) {
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object &&
					(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
						symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {

					//bật dịch chuyển các vertex đối xứng
					isTransformObjectSymmetry = true;
					break;
				}
			}
		}
	}

	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *triangle = triangleArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triangle->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 3;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triangle->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);
		}
		
		//tính toán lại center triangle
		triangle->centerObject = getPointCenterVertexes(triangle->vertexArray, 3);
		CaculatorNormalForTriangles(triangle->vertexArray, triangle->normalVector);
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaStrip->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaStrip->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaStrip->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);
		}
		
		//tính toán lại center
		triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaFan->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaFan->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaFan->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);
		}
		
		//tính toán lại center
		triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, sphere->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, sphere->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);
		}
		
		//tính toán lại center 
		sphere->centerObject = getPointCenterVertexes(sphere->vertexArray);
		CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
			sphere->vertexArray, sphere->normalVector);
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cube->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cone->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cone->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);
		}
		
		//tính toán lại center 
		cone->centerObject = getPointCenterVertexes(cone->vertexArray);
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
			cone->vertexArray, cone->normalVector);
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, torus->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, torus->vertexArray);
		}
		
		//tính toán lại center 
		torus->centerObject = getPointCenterVertexes(torus->vertexArray);
		CaculatorNormalForTorus(torus->depthRoundCake,
			torus->vertexArray, torus->normalVector);
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, picture->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 4;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, picture->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);
		}
		
		//tính toán lại center 
		picture->centerObject = getPointCenterVertexes(picture->vertexArray, 4);
		CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			rotateVertexChoiceAndSymmetry(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, object->vertexArray,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}

			//kiểm tra xem có bật nghịch đảo x,y,z không
			if (symmetry_rotateX) {
				rotateX = -rotateX;
			}
			if (symmetry_rotateY) {
				rotateY = -rotateY;
			}
			if (symmetry_rotateZ) {
				rotateZ = -rotateZ;
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, object->vertexArray);
		}
		else
		{
			rotateVertexChoice(rotateX, rotateY, rotateZ,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);
		}

		//tính toán lại center 
		object->centerObject = getPointCenterVertexes(object->vertexArray);
		CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
	}
	break;
	default:
		break;
	}
}
//hàm xoay các vật hay vertex được chọn
void rotateShape(float deg, int axis, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, int modelEditStyle, vector<int> positionVerticesChoice,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	if (modelEditStyle == 0) {
		rotateObject(deg, axis, itemsChoice,
			symmetryObjects,
			symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
	}
	else
	{
		rotateVertex(deg, axis, itemsChoice, positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
			symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
			symmetryVertices, symmetryObjects,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
	}
}
//chỉnh sửa các thuộc tính của vật
void EditAttribute(float plus,
	vector<itemChoice> itemsChoice, int whichArrowChoice,
	vector<SphereAttribute*> &sphereArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray) {
	itemChoice item = itemsChoice.back();
	switch (item.object)
	{
	case 10:
	{
		if (whichArrowChoice == 0) {
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			sphere->radius += plus;
			//thêm các điều kiện 
			if (sphere->radius < 0.1f) {
				sphere->radius = 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int numberVertex = sphere->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				normalizeWithRadius(sphere->centerObject, sphere->vertexArray.at(j), sphere->radius);
			}
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (whichArrowChoice == 0) {
			int offset = cone->numberLongitude;
			cone->radius += plus;
			if (cone->radius < 0.1f) {
				cone->radius = 0.1f;
			}
			//tính từ phần tử thứ 1 trong vertex aray vì phần tử đầu tiên là đỉnh
			for (int j = 0; j < cone->numberLongitude; j++) {
				normalizeWithRadius(cone->centerObject, cone->vertexArray.at(offset), cone->radius);
				offset++;
			}
		}
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		//nếu là chỉnh sửa radiusUp
		if (whichArrowChoice == 3) {
			cylinder->radiusUp += plus;
			if (cylinder->radiusUp < 0.1f) {
				cylinder->radiusUp = 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->vertexArray.size() - (cylinder->numberLongitude * 2);
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusUp);
				offset++;
			}
		}
		//nếu là chỉnh sửa radius Down
		else if (whichArrowChoice == 0) {
			cylinder->radiusDown += plus;
			if (cylinder->radiusDown < 0.1f) {
				cylinder->radiusDown = 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->numberLongitude;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusDown);
				offset++;
			}
		}
		//nếu là chỉnh sửa chiều cao phía trên
		else if (whichArrowChoice == 4) {
			//giá trị sẽ - do đỉnh này nằm trên tâm hình trụ(và giá trị y ngược,do cách tính của ta)
			cylinder->height += plus;
			if (cylinder->height < 0.2f) {
				cylinder->height = 0.2f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, centerNow, centerLast;
			offset = cylinder->vertexArray.size() - (cylinder->numberLongitude * 2);
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			centerNow.x = (v1.x + v2.x) / 2;
			centerNow.y = (v1.y + v2.y) / 2;
			centerNow.z = (v1.z + v2.z) / 2;
			centerLast.x = centerNow.x;
			centerLast.y = centerNow.y;
			centerLast.z = centerNow.z;
			normalizeWithRadius(cylinder->centerObject, centerNow, cylinder->height / 2);
			float plusValue[3];
			plusValue[0] = roundf((centerNow.x - centerLast.x) * 1000) / 1000;
			plusValue[1] = roundf((centerNow.y - centerLast.y) * 1000) / 1000;
			plusValue[2] = roundf((centerNow.z - centerLast.z) * 1000) / 1000;
			//tăng hay giảm các giá trị centerCylinder
			cylinder->centerObject.x += (plusValue[0] / 2);
			cylinder->centerObject.y += (plusValue[1] / 2);
			cylinder->centerObject.z += (plusValue[2] / 2);
			//tăng hay giảm các vertex của đỉnh trên và vòng bao trên
			for (int j = 0; j < cylinder->numberLongitude * 2; j++) {
				cylinder->vertexArray.at(offset).x += plusValue[0];
				cylinder->vertexArray.at(offset).y += plusValue[1];
				cylinder->vertexArray.at(offset).z += plusValue[2];
				offset++;
			}
		}
		//nếu là chỉnh sửa chiều cao phía dưới
		else if (whichArrowChoice == 1) {
			//giá trị sẽ - do đỉnh này nằm trên tâm hình trụ(và giá trị y ngược,do cách tính của ta)
			cylinder->height -= plus;
			if (cylinder->height < 0.2f) {
				cylinder->height = 0.2f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, centerNow, centerLast;
			offset = cylinder->numberLongitude;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			centerNow.x = (v1.x + v2.x) / 2;
			centerNow.y = (v1.y + v2.y) / 2;
			centerNow.z = (v1.z + v2.z) / 2;
			centerLast.x = centerNow.x;
			centerLast.y = centerNow.y;
			centerLast.z = centerNow.z;
			normalizeWithRadius(cylinder->centerObject, centerNow, cylinder->height / 2);
			float plusValue[3];
			plusValue[0] = roundf((centerNow.x - centerLast.x) * 1000) / 1000;
			plusValue[1] = roundf((centerNow.y - centerLast.y) * 1000) / 1000;
			plusValue[2] = roundf((centerNow.z - centerLast.z) * 1000) / 1000;
			//tăng hay giảm các giá trị centerCylinder
			cylinder->centerObject.x += (plusValue[0] / 2);
			cylinder->centerObject.y += (plusValue[1] / 2);
			cylinder->centerObject.z += (plusValue[2] / 2);
			offset = 0;
			//tăng hay giảm các vertex
			for (int j = 0; j < cylinder->numberLongitude * 2; j++) {
				cylinder->vertexArray.at(offset).x += plusValue[0];
				cylinder->vertexArray.at(offset).y += plusValue[1];
				cylinder->vertexArray.at(offset).z += plusValue[2];
				offset++;
			}
		}
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 16://(trên ngoài, trên trong, dưới ngoài, dưới trong)
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		//nếu là chỉnh sửa radiusUpOut
		if (whichArrowChoice == 6) {
			cylinder->radiusUpOut += plus;
			//bán kính ngoài luôn phải lớn hơn bán kính trong
			if (cylinder->radiusUpOut < cylinder->radiusUpIn + 0.1f) {
				cylinder->radiusUpOut = cylinder->radiusUpIn + 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->vertexArray.size() - cylinder->numberLongitude * 2;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusUpOut);
				offset++;
			}
		}
		//nếu là chỉnh sửa radiusUpIn
		else if (whichArrowChoice == 9) {
			cylinder->radiusUpIn -= plus;
			//bán kính trong phải lớn hơn 0.1 và bé hơn bán kính ngoài;
			if (cylinder->radiusUpIn < 0.1f) {
				cylinder->radiusUpIn = 0.1f;
			}
			else if (cylinder->radiusUpIn > cylinder->radiusUpOut - 0.1f) {
				cylinder->radiusUpIn = cylinder->radiusUpOut - 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->vertexArray.size() - cylinder->numberLongitude * 2;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			offset = offset + cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusUpIn);
				offset++;
			}
		}
		//nếu là chỉnh sửa radiusDownOut
		else if (whichArrowChoice == 0) {
			cylinder->radiusDownOut += plus;
			//bán kính ngoài luôn phải lớn hơn bán kính trong
			if (cylinder->radiusDownOut < cylinder->radiusDownIn + 0.1f) {
				cylinder->radiusDownOut = cylinder->radiusDownIn + 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->numberLongitude;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusDownOut);
				offset++;
			}
		}
		//nếu là chỉnh sửa radius DownIn
		else if (whichArrowChoice == 3) {
			cylinder->radiusDownIn -= plus;
			//bán kính trong phải lớn hơn 0.1 và bé hơn bán kính ngoài;
			if (cylinder->radiusDownIn < 0.1f) {
				cylinder->radiusDownIn = 0.1f;
			}
			else if (cylinder->radiusDownIn > cylinder->radiusDownOut - 0.1f) {
				cylinder->radiusDownIn = cylinder->radiusDownOut - 0.1f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, center;
			offset = cylinder->numberLongitude;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			center.x = (v1.x + v2.x) / 2;
			center.y = (v1.y + v2.y) / 2;
			center.z = (v1.z + v2.z) / 2;
			offset = 0;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				normalizeWithRadius(center, cylinder->vertexArray.at(offset), cylinder->radiusDownIn);
				offset++;
			}
		}
		//nếu là chỉnh sửa chiều cao phía trên
		else if (whichArrowChoice == 4) {
			//giá trị sẽ - do đỉnh này nằm trên tâm hình trụ(và giá trị y ngược,do cách tính của ta)
			cylinder->height += plus;
			if (cylinder->height < 0.2f) {
				cylinder->height = 0.2f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, centerNow, centerLast;
			offset = cylinder->vertexArray.size() - cylinder->numberLongitude * 2;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			centerNow.x = (v1.x + v2.x) / 2;
			centerNow.y = (v1.y + v2.y) / 2;
			centerNow.z = (v1.z + v2.z) / 2;
			centerLast.x = centerNow.x;
			centerLast.y = centerNow.y;
			centerLast.z = centerNow.z;
			normalizeWithRadius(cylinder->centerObject, centerNow, cylinder->height / 2);
			float plusValue[3];
			plusValue[0] = roundf((centerNow.x - centerLast.x) * 1000) / 1000;
			plusValue[1] = roundf((centerNow.y - centerLast.y) * 1000) / 1000;
			plusValue[2] = roundf((centerNow.z - centerLast.z) * 1000) / 1000;
			//tăng hay giảm các giá trị centerCylinder
			cylinder->centerObject.x += (plusValue[0] / 2);
			cylinder->centerObject.y += (plusValue[1] / 2);
			cylinder->centerObject.z += (plusValue[2] / 2);
			//tăng hay giảm các vertex của cả trong và ngoài
			for (int j = 0; j < cylinder->numberLongitude * 2; j++) {
				cylinder->vertexArray.at(offset).x += plusValue[0];
				cylinder->vertexArray.at(offset).y += plusValue[1];
				cylinder->vertexArray.at(offset).z += plusValue[2];
				offset++;
			}
		}
		//nếu là chỉnh sửa chiều cao phía dưới
		else if (whichArrowChoice == 1) {
			//giá trị sẽ - do đỉnh này nằm trên tâm hình trụ(và giá trị y ngược,do cách tính của ta)
			cylinder->height -= plus;
			if (cylinder->height < 0.2f) {
				cylinder->height = 0.2f;
			}
			//tính toán tăng lên cho các vertex của mỗi mặt
			int offset = 0;
			point v1, v2, centerNow, centerLast;
			offset = cylinder->numberLongitude;
			v1 = cylinder->vertexArray.at(offset);
			v2 = cylinder->vertexArray.at(offset + cylinder->numberLongitude / 2);
			centerNow.x = (v1.x + v2.x) / 2;
			centerNow.y = (v1.y + v2.y) / 2;
			centerNow.z = (v1.z + v2.z) / 2;
			centerLast.x = centerNow.x;
			centerLast.y = centerNow.y;
			centerLast.z = centerNow.z;
			normalizeWithRadius(cylinder->centerObject, centerNow, cylinder->height / 2);
			float plusValue[3];
			plusValue[0] = roundf((centerNow.x - centerLast.x) * 1000) / 1000;
			plusValue[1] = roundf((centerNow.y - centerLast.y) * 1000) / 1000;
			plusValue[2] = roundf((centerNow.z - centerLast.z) * 1000) / 1000;
			//tăng hay giảm các giá trị centerCylinder
			cylinder->centerObject.x += (plusValue[0] / 2);
			cylinder->centerObject.y += (plusValue[1] / 2);
			cylinder->centerObject.z += (plusValue[2] / 2);
			//tăng hay giảm các vertex
			offset = 0;
			for (int j = 0; j < cylinder->numberLongitude * 2; j++) {
				cylinder->vertexArray.at(offset).x += plusValue[0];
				cylinder->vertexArray.at(offset).y += plusValue[1];
				cylinder->vertexArray.at(offset).z += plusValue[2];
				offset++;
			}
		}
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 17:
	{
		if (whichArrowChoice == 0) {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			torus->radiusCake += plus;
			//thêm các điều kiện 
			if (torus->radiusCake < 0.1f) {
				torus->radiusCake = 0.1f;
			}
			torus->vertexArray.clear();
			caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
				torus->centerObject, torus->vertexArray);
		}
		else if (whichArrowChoice == 3) {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			torus->radiusRoundCake += plus;
			//thêm các điều kiện 
			if (torus->radiusRoundCake < 0.1f) {
				torus->radiusRoundCake = 0.1f;
			}
			torus->vertexArray.clear();
			caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
				torus->centerObject, torus->vertexArray);
		}
		else if (whichArrowChoice == 2) {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			torus->widthCake += plus;
			//thêm các điều kiện 
			if (torus->widthCake < 0.1f) {
				torus->widthCake = 0.1f;
			}
			torus->vertexArray.clear();
			//torus->normalVector.clear();
			caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
				torus->centerObject, torus->vertexArray);
			//CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
		}
	}
	break;
	default:
		break;
	}
}
//chỉnh sửa các thuộc tính liên quan đến góc độ
void EditAttributeAboutDeg(int plusDegree,
	itemRotateObject itemRotate, vector<itemChoice> itemsChoice,
	vector<SphereAttribute*> &sphereArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray) {
	itemChoice item = itemsChoice.back();
	switch (item.object)
	{
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (itemRotate.whichCircleChoice == 0) {
			sphere->degreeLatitudeLimit -= plusDegree;
			//k0 được vượt quá giới hạn
			if (sphere->degreeLatitudeLimit > 360) {
				sphere->degreeLatitudeLimit = 360;
			}
			else if (sphere->degreeLatitudeLimit < 0) {
				sphere->degreeLatitudeLimit = 0;
			}
		}
		else if (itemRotate.whichCircleChoice == 1)
		{
			sphere->degreeLongitudeLimit += plusDegree;
			//k0 được vượt quá giới hạn
			if (sphere->degreeLongitudeLimit > 360) {
				sphere->degreeLongitudeLimit = 360;
			}
			else if (sphere->degreeLongitudeLimit < 0) {
				sphere->degreeLongitudeLimit = 0;
			}
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		cone->degreeLongitudeLimit += plusDegree;
		//k0 được vượt quá giới hạn
		if (cone->degreeLongitudeLimit > 360) {
			cone->degreeLongitudeLimit = 360;
		}
		else if (cone->degreeLongitudeLimit < 0) {
			cone->degreeLongitudeLimit = 0;
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		cylinder->degreeLongitudeLimit += plusDegree;
		//k0 được vượt quá giới hạn
		if (cylinder->degreeLongitudeLimit > 360) {
			cylinder->degreeLongitudeLimit = 360;
		}
		else if (cylinder->degreeLongitudeLimit < 0) {
			cylinder->degreeLongitudeLimit = 0;
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		cylinder->degreeLongitudeLimit += plusDegree;
		//k0 được vượt quá giới hạn
		if (cylinder->degreeLongitudeLimit > 360) {
			cylinder->degreeLongitudeLimit = 360;
		}
		else if (cylinder->degreeLongitudeLimit < 0) {
			cylinder->degreeLongitudeLimit = 0;
		}
	}
	break;
	default:
		break;
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//nếu chỉ có 1 hình thì  kiêm tra xem hình được chọn có thông tin trong item nào của symmetryObject không
	int numberSymmetry = symmetryObjects.size();
	SymmetryObjects symmetryCheck;
	bool isHaveSymmetryObject = false;
	if (itemsChoice.size() == 1) {
		itemChoice itemCheck = itemsChoice.back();
		for (int i = 0; i < numberSymmetry; i++) {
			symmetryCheck = symmetryObjects.at(i);
			if (itemCheck.object == symmetryCheck.object1 &&
				(itemCheck.positionOfChoice == symmetryCheck.positionInArray1 ||
					itemCheck.positionOfChoice == symmetryCheck.positionInArray2)) {

				isHaveSymmetryObject = true;
				break;
			}
		}
	}

	int numberItemChoice = itemsChoice.size();
	//scale tất cả các item đang được chọn
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			TriangleAttribute *triangle = triangleArray.at(item.positionOfChoice);
			CaculatorScaleVertex(triangle->vertexArray, 3, triangle->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForTriangles(triangle->vertexArray, triangle->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triangle = triangleArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triangle = triangleArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(triangle->vertexArray, 3, triangle->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForTriangles(triangle->vertexArray, triangle->normalVector);
			}
		}
		break;
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			CaculatorScaleVertex(triaStrip->vertexArray, triaStrip->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaStrip = triaStripArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(triaStrip->vertexArray, triaStrip->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
			}
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			CaculatorScaleVertex(triaFan->vertexArray, triaFan->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					triaFan = triaFanArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					triaFan = triaFanArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(triaFan->vertexArray, triaFan->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
			}
		}
		break;
		case 10:
		{
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			CaculatorScaleVertex(sphere->vertexArray, sphere->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					sphere = sphereArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					sphere = sphereArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(sphere->vertexArray, sphere->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);
			}
		}
		break;
		case 11:
		{
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			CaculatorScaleVertex(cube->vertexArray, cube->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
				, cube->vertexArray, cube->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(cube->vertexArray, cube->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
					, cube->vertexArray, cube->normalVector);
			}
		}
		break;
		case 12:
		{
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			CaculatorScaleVertex(cube->vertexArray, cube->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cube = cubeRoundArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cube = cubeRoundArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(cube->vertexArray, cube->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);
			}
		}
		break;
		case 13:
		{
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			CaculatorScaleVertex(cone->vertexArray, cone->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cone = coneArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cone = coneArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(cone->vertexArray, cone->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
			}
		}
		break;
		case 14:
		{
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			CaculatorScaleVertex(cylinder->vertexArray, cylinder->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = cylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = cylinderArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(cylinder->vertexArray, cylinder->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
		}
		break;
		case 16:
		{
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			CaculatorScaleVertex(cylinder->vertexArray, cylinder->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(cylinder->vertexArray, cylinder->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
		}
		break;
		case 17:
		{
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			CaculatorScaleVertex(torus->vertexArray, torus->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					torus = torusArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					torus = torusArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(torus->vertexArray, torus->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
			}
		}
		break;
		case 18:
		{
			PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
			CaculatorScaleVertex(picture->vertexArray, 4, picture->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					picture = pictureArray.at(symmetryCheck.positionInArray2);
				}
				else
				{
					picture = pictureArray.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(picture->vertexArray, 4, picture->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
			}
		}
		break;
		case 19:
		{
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			CaculatorScaleVertex(object->vertexArray, object->centerObject, valuePlusX, valuePlusY, valuePlusZ);
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);

			//kiểm tra xem có object đối xứng không
			if (isHaveSymmetryObject) {
				if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
					object = objectCustom0Array.at(symmetryCheck.positionInArray2);
				}
				else
				{
					object = objectCustom0Array.at(symmetryCheck.positionInArray1);
				}

				CaculatorScaleVertex(object->vertexArray, object->centerObject, valuePlusX, valuePlusY, valuePlusZ);
				CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
			}
		}
		break;
		default:
			break;
		}
	}
}

//hàm scale chỉ các vertex đang chọn
void scaleVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point *vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVertices,
			valuePlusX, valuePlusY, valuePlusZ);
	}
}
void scaleVertexChoice(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, vector<point> &vertexArray) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement;
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVertices,
			valuePlusX, valuePlusY, valuePlusZ);
	}
}

//hàm scale vertex chọn và vertex nghịch đảo
void scaleVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, point *vertexArray,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVertices,
			valuePlusX, valuePlusY, valuePlusZ);
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					//đoạn này chưa biết chỉnh scale nghịch đảo
					CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry,
						valuePlusX, valuePlusY, valuePlusZ);
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					//đoạn này chưa biết chỉnh scale nghịch đảo
					CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry,
						valuePlusX, valuePlusY, valuePlusZ);
				}
				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
void scaleVertexChoiceAndSymmetry(float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<int> positionVerticesChoice, point centerObjectOrVertices, point centerObjectOrVerticesSymmetry, vector<point> &vertexArray,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<int> positionVertexSymmetry1, vector<int> positionVertexSymmetry2) {

	int numberVertexChoice = positionVerticesChoice.size(), positionElement,
		numberElement = positionVertexSymmetry1.size()<positionVertexSymmetry2.size() ?
		positionVertexSymmetry1.size() : positionVertexSymmetry2.size();
	for (int i = 0; i < numberVertexChoice; i++) {
		positionElement = positionVerticesChoice.at(i);
		CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVertices,
			valuePlusX, valuePlusY, valuePlusZ);
		//kiểm tra xem trong cụm vertexSymmetry1 hay 2 có vị trí này không,
		//nếu có thì dịch chuyển vị trí tương đướng trong mang còn lại
		for (int k = 0; k < numberElement; k++) {
			if (positionVertexSymmetry1.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry2.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry2.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					//đoạn này chưa biết chỉnh scale nghịch đảo
					CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry,
						valuePlusX, valuePlusY, valuePlusZ);
				}

				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
			else if (positionVertexSymmetry2.at(k) == positionElement) {
				//kiểm tra nếu điểm này và điểm đối xứng là cùng 1 đỉnh thì khỏi biên đổi nữa
				if (positionElement != positionVertexSymmetry1.at(k)) {
					//nếu có phần tử cần dịch chuyển đối nghịch thì lấy phần tử đối nghịch để dịch chuyển
					positionElement = positionVertexSymmetry1.at(k);
					//kiểm tra xem dịch chuyển nghịch đảo hay cùng chiều
					//đoạn này chưa biết chỉnh scale nghịch đảo
					CaculatorScaleVertex(vertexArray[positionElement], centerObjectOrVerticesSymmetry,
						valuePlusX, valuePlusY, valuePlusZ);
				}
				//sau khi tìm được điểm đối xứng thì xóa điểm này ra khỏi mảng luôn để lần sau đỡ phải tìm
				//kiếm,vì đây chỉ là bản sao của mảng nên nó không làm thay đổi gì mảng chính ở bên ngoài
				positionVertexSymmetry1.erase(positionVertexSymmetry1.begin() + k);
				positionVertexSymmetry2.erase(positionVertexSymmetry2.begin() + k);
				numberElement--;
				break;
			}
		}
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	bool isTransformVerticesSymmetry = false, isTransformObjectSymmetry = false;
	int numberElement;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectCheck;
	itemChoice item = itemsChoice.at(0);

	//nếu tâm xoay của các item nghịch đảo khác NULL thì cho phép biến đổi item nghịch đảo
	if (centerObjectOrVerticesSymmetry.x != NULL) {
		//phải kiểm tra tiếp xem đối tượng này có vertex đối xứng không để kiểm tra
		//nếu không có thì chỉ di chuyển các vertex được chọn thôi
		numberElement = symmetryVertices.size();
		for (int i = 0; i < numberElement; i++) {
			symmetryVerticesCheck = symmetryVertices.at(i);
			if (symmetryVerticesCheck.object == item.object &&
				symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
				//bật dịch chuyển các vertex đối xứng
				isTransformVerticesSymmetry = true;
				break;
			}
		}
		//nếu không có vertex đối xứng thì kiểm tra đối tượng này có object đối xứng không
		if (!isTransformVerticesSymmetry) {
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object &&
					(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
						symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
					//bật dịch chuyển các vertex đối xứng
					isTransformObjectSymmetry = true;
					break;
				}
			}
		}
	}
	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *triangle = triangleArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triangle->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triangle = triangleArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 3;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triangle->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triangle->vertexArray);
		}
		
		//tính toán lại center 
		triangle->centerObject = getPointCenterVertexes(triangle->vertexArray, 3);
		CaculatorNormalForTriangles(triangle->vertexArray, triangle->normalVector);
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaStrip->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaStrip->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaStrip->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triaStrip->vertexArray);
		}
		
		//tính toán lại center 
		triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, triaFan->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaFan->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, triaFan->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, triaFan->vertexArray);
		}
		
		//tính toán lại center 
		triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		CaculatorNormalForTriangleFan(triaFan->vertexArray, triaFan->normalVector);
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, sphere->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, sphere->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, sphere->vertexArray);
		}
		
		//tính toán lại center 
		sphere->centerObject = getPointCenterVertexes(sphere->vertexArray);
		CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
			sphere->vertexArray, sphere->normalVector);
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cube->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cube->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cube->vertexArray);
		}
		
		//tính toán lại center 
		cube->centerObject = getPointCenterVertexes(cube->vertexArray);
		CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude,
			cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cone->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cone->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cone->vertexArray);
		}
		
		//tính toán lại center 
		cone->centerObject = getPointCenterVertexes(cone->vertexArray);
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
			cone->vertexArray, cone->normalVector);
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, cylinder->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, cylinder->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, cylinder->vertexArray);
		}
		
		//tính toán lại center 
		cylinder->centerObject = getPointCenterVertexes(cylinder->vertexArray);
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, torus->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, torus->vertexArray);
		}
		
		//tính toán lại center 
		torus->centerObject = getPointCenterVertexes(torus->vertexArray);
		CaculatorNormalForTorus(torus->depthRoundCake,
			torus->vertexArray, torus->normalVector);
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, picture->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 4;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, picture->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, picture->vertexArray);
		}
		
		//tính toán lại center 
		picture->centerObject = getPointCenterVertexes(picture->vertexArray, 4);
		CaculatorNormalForPictures(picture->vertexArray, picture->normalVector);
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isTransformVerticesSymmetry) {
			scaleVertexChoiceAndSymmetry(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry, object->vertexArray,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVerticesCheck.positionVertices1, symmetryVerticesCheck.positionVertices2);
		}
		else if (isTransformObjectSymmetry) {
			//đầu tiên dịch chuyển Object đang chọn
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);

			//tiếp theo dịch chuyển object bản sao
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryObjectCheck.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryObjectCheck.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryObjectCheck.numberItemInRow;
						endRow += symmetryObjectCheck.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryObjectCheck.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì áp dụng biến đổi cho hình đối xứng
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVerticesSymmetry, object->vertexArray);
		}
		else
		{
			scaleVertexChoice(valuePlusX, valuePlusY, valuePlusZ,
				positionVerticesChoice, centerObjectOrVertices, object->vertexArray);
		}

		//tính toán lại center 
		object->centerObject = getPointCenterVertexes(object->vertexArray);
		CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
	}
	break;
	default:
		break;
	}
}
//hàm scale vật hoặc vertex ở chế độ scale
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	if (whichArrowChoice == -1) {
		//nếu scale theo chiều yx
		if (whichQuadChoice == 0) {
			if (modelEditStyle == 0) {
				scaleObject(valuePlus, valuePlus, 1.0, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(valuePlus, valuePlus, 1.0, itemsChoice, 
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		//nếu scale theo chiều xz
		else if (whichQuadChoice == 1) {
			if (modelEditStyle == 0) {
				scaleObject(valuePlus, 1.0, valuePlus, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(valuePlus, 1.0, valuePlus, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		//nếu scale theo chiều zy
		else if (whichQuadChoice == 2)
		{
			if (modelEditStyle == 0) {
				scaleObject(1.0, valuePlus, valuePlus, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(1.0, valuePlus, valuePlus, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		else
		{
			if (modelEditStyle == 0) {
				scaleObject(valuePlus, valuePlus, valuePlus, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(valuePlus, valuePlus, valuePlus, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
	}
	else
	{
		//nếu scale theo chiều x
		if (whichArrowChoice == 0) {
			if (modelEditStyle == 0) {
				scaleObject(valuePlus, 1.0, 1.0, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(valuePlus, 1.0, 1.0, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		//nếu scale theo chiều y
		else if (whichArrowChoice == 1) {
			if (modelEditStyle == 0) {
				scaleObject(1.0, valuePlus, 1.0, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(1.0, valuePlus, 1.0, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
		//nếu scale theo chiều z
		else
		{
			if (modelEditStyle == 0) {
				scaleObject(1.0, 1.0, valuePlus, itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				scaleVertex(1.0, 1.0, valuePlus, itemsChoice,
					positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
		}
	}
}


//tính toán giá trị tăng lên khi dịch chuyển cho mũi tên
bool caculatorPlusArrow(point &center, int whichArrow, int xNow, int yNow,
	float &valuePlus, double *modelMatrix, double *projectMatrix, int *viewport) {

	double centerOnScreen[3], arrowOnScreen[3], touchOnScreen[2];

	//tính toán tọa độ các mũi tên theo chiều khác nhau ra tọa độ màn hình
	if (whichArrow == 0) {
		gluProject((GLdouble)(center.x + 1), (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	else if (whichArrow == 1) {
		gluProject((GLdouble)center.x, (GLdouble)(center.y + 1), (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	else
	{
		gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)(center.z + 1), modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	//lấy vị trí trung tâm hình trên tọa độ màn hình
	gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
		&centerOnScreen[0], &centerOnScreen[1], &centerOnScreen[2]);

	try
	{
		//lấy tỷ giữa mũi tên trong tọa độ 3D và trên màn hình 
		float lengthArrowOnScreen = sqrt(pow((arrowOnScreen[0] - centerOnScreen[0]), 2) + pow((arrowOnScreen[1] - centerOnScreen[1]), 2));
		float scale3dAndScreen = 1 / lengthArrowOnScreen;

		touchOnScreen[0] = xNow;
		touchOnScreen[1] = yNow;
		//lấy ra khoảng cách giữa tâm chạm lần đầu trên mũi tên và điểm chạm hiện tại
		float distanceTouchAndCenterOnScreen = sqrt(pow(centerOnScreen[0] - touchOnScreen[0], 2) + pow(centerOnScreen[1] - touchOnScreen[1], 2));

		//lấy ra vị trí nằm trên đường thảng chứa mũi tên và cách tâm 1 khoảng bằng plusScreen(để ta xem nó nằm ở góc bao nhiêu độ cảu đường tròn vẽ từ tâm)
		normalizeWithRadius2D(centerOnScreen, arrowOnScreen, distanceTouchAndCenterOnScreen);
		//lấy ra vị trí nằm trên đường thẳng chứa tâm và điểm chạm và cách tâm 1 khoảng bằng plusScreen
		normalizeWithRadius2D(centerOnScreen, touchOnScreen, distanceTouchAndCenterOnScreen);

		//vẽ đường tròn để xét xem các điểm kia nằm ở góc bao nhiêu độ
		int degOfArrow = -1, degOfTouch = -1;
		const float DEG2RAD = 3.14159f / 180;
		float degInRad, xCircle, yCircle;

		//tính mức độ sai số cho phép dựa theo bán kính(mức độ sai số cho phép bằng khoảng cách 2 điểm gần nhất)
		float v0[2], v1[2];
		v0[0] = sin(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v0[1] = cos(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		v1[0] = sin(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v1[1] = cos(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		float allowError = sqrt(pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1], 2));

		//tính các điểm trên đường tròn để xem mũi tên và điểm chạm nằm ở vị trí nào
		for (int i = 0; i < 360; i++) {
			degInRad = i*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = sin(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
			yCircle = cos(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
			//kiểm tra xem điểm nào trên đường tròn trùng với điểm nằm trên dường thẳng chứa mũi tên và điểm nằm
			//trên đường thẳng chứa điểm chạm
			if (xCircle <= arrowOnScreen[0] + allowError && xCircle >= arrowOnScreen[0] - allowError &&
				yCircle <= arrowOnScreen[1] + allowError && yCircle >= arrowOnScreen[1] - allowError) {
				degOfArrow = i;
			}
			else if (xCircle <= touchOnScreen[0] + allowError && xCircle >= touchOnScreen[0] - allowError &&
				yCircle <= touchOnScreen[1] + allowError && yCircle >= touchOnScreen[1] - allowError) {
				degOfTouch = i;
			}
			if (degOfArrow != -1 && degOfTouch != -1) {
				break;
			}
		}
		//nếu không tính được vòng xoay của mũi tên hay điểm chạm thì bỏ qua
		if (degOfArrow == -1 || degOfTouch == -1) {
			return false;
		}
		//tính lại độ của điểm chạm với vị trí arrow trên màn hình là tâm
		if (degOfTouch >= degOfArrow) {
			degOfTouch -= degOfArrow;
		}
		else
		{
			degOfTouch -= degOfArrow;
			degOfTouch += 360;
		}

		//tính ra giá trị tăng lên(luôn dương,vì đây chỉ là khoảng cách,để biết dương hay âm thì phải dựa vào góc độ của điểm chạm và mũi tên để đặt)
		//tính diện tích của tam giác(gồm 3 điểm là tâm đường tròn,vị trí điểm chạm trên đường tròn,vị trí mũi tên trên đường tròn)
		float distanceTouchAndArrowOnCircle = sqrt(pow(arrowOnScreen[0] - touchOnScreen[0], 2) + pow(arrowOnScreen[1] - touchOnScreen[1], 2));
		float p = (distanceTouchAndCenterOnScreen + distanceTouchAndCenterOnScreen + distanceTouchAndArrowOnCircle) / 2;
		float acreage = sqrt(p*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndArrowOnCircle));
		//từ diện tích tam giác tính ra chiều cao từ đỉnh touch xuống
		float heightFromTouch = (2 * acreage) / distanceTouchAndCenterOnScreen;
		//tính ra mức độ tăng lên của mũi tên
		//nếu điểm kéo nằm ở nửa vòng tròn trước thì tăng lên,nếu không thì giảm xuống
		if ((degOfTouch>90 && degOfTouch<270)) {
			valuePlus = -(sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen);
		}
		else
		{
			valuePlus = sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen;
		}

		//nếu valuePlus là không xác định thì báo lỗi
		if (isnan(valuePlus)) {
			throw 1;
		}

		//tăng giá trị điểm chạm đầu tiên để tính cho lần tiếp theo
		if (whichArrow == 0) {
			center.x += valuePlus;
		}
		else if (whichArrow == 1) {
			center.y += valuePlus;
		}
		else
		{
			center.z += valuePlus;
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}

//tính toán giá trị tăng lên khi dịch chuyển cho quad
//đây là cách tính để dịch chuyển,nó có 2 giá trị tăng
bool caculatorPlusQuad(point &center, int whichQuad, int xNow, int yNow,
	float &valuePlus1, float &valuePlus2, double *modelMatrix, double *projectMatrix, int *viewport) {

	double centerOnScreen[3], arrowOnScreen1[3], arrowOnScreen2[3], touchOnScreen[2];

	//tính toán tọa độ các mũi tên theo chiều khác nhau ra tọa độ màn hình
	if (whichQuad == 0) {
		gluProject((GLdouble)center.x, (GLdouble)(center.y + 1), (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen1[0], &arrowOnScreen1[1], &arrowOnScreen1[2]);
		gluProject((GLdouble)(center.x + 1), (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen2[0], &arrowOnScreen2[1], &arrowOnScreen2[2]);
	}
	else if (whichQuad == 1) {
		gluProject((GLdouble)(center.x + 1), (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen1[0], &arrowOnScreen1[1], &arrowOnScreen1[2]);
		gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)(center.z + 1), modelMatrix, projectMatrix, viewport,
			&arrowOnScreen2[0], &arrowOnScreen2[1], &arrowOnScreen2[2]);
	}
	else
	{
		gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)(center.z + 1), modelMatrix, projectMatrix, viewport,
			&arrowOnScreen1[0], &arrowOnScreen1[1], &arrowOnScreen1[2]);
		gluProject((GLdouble)center.x, (GLdouble)(center.y + 1), (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen2[0], &arrowOnScreen2[1], &arrowOnScreen2[2]);
	}
	//lấy vị trí trung tâm hình trên tọa độ màn hình
	gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
		&centerOnScreen[0], &centerOnScreen[1], &centerOnScreen[2]);

	try
	{
		//lấy tỷ giữa mũi tên trong tọa độ 3D và trên màn hình 
		float lengthArrowOnScreen = sqrt(pow((arrowOnScreen1[0] - centerOnScreen[0]), 2) + pow((arrowOnScreen1[1] - centerOnScreen[1]), 2));
		float scale3dAndScreen1 = 1 / lengthArrowOnScreen;
		lengthArrowOnScreen = sqrt(pow((arrowOnScreen2[0] - centerOnScreen[0]), 2) + pow((arrowOnScreen2[1] - centerOnScreen[1]), 2));
		float scale3dAndScreen2 = 1 / lengthArrowOnScreen;

		touchOnScreen[0] = xNow;
		touchOnScreen[1] = yNow;
		//lấy ra khoảng cách giữa tâm chạm lần đầu trên mũi tên và điểm chạm hiện tại
		float distanceTouchAndCenterOnScreen = sqrt(pow(centerOnScreen[0] - touchOnScreen[0], 2) + pow(centerOnScreen[1] - touchOnScreen[1], 2));

		//lấy ra vị trí nằm trên đường thảng chứa mũi tên và cách tâm 1 khoảng bằng plusScreen(để ta xem nó nằm ở góc bao nhiêu độ cảu đường tròn vẽ từ tâm)
		normalizeWithRadius2D(centerOnScreen, arrowOnScreen1, distanceTouchAndCenterOnScreen);
		normalizeWithRadius2D(centerOnScreen, arrowOnScreen2, distanceTouchAndCenterOnScreen);
		//lấy ra vị trí nằm trên đường thẳng chứa tâm và điểm chạm và cách tâm 1 khoảng bằng plusScreen
		normalizeWithRadius2D(centerOnScreen, touchOnScreen, distanceTouchAndCenterOnScreen);

		//vẽ đường tròn để xét xem các điểm kia nằm ở góc bao nhiêu độ
		int degOfArrow1 = -1, degOfArrow2 = -1, degOfTouch1 = -1, degOfTouch2 = -1;
		const float DEG2RAD = 3.14159 / 180;
		float degInRad, xCircle, yCircle;

		//tính mức độ sai số cho phép dựa theo bán kính(mức độ sai số cho phép bằng khoảng cách 2 điểm gần nhất)
		float v0[2], v1[2];
		v0[0] = sin(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v0[1] = cos(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		v1[0] = sin(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v1[1] = cos(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		float allowError = sqrt(pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1], 2));

		//tính các điểm trên đường tròn để xem mũi tên và điểm chạm nằm ở vị trí nào
		for (int i = 0; i < 360; i++) {
			degInRad = i*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = sin(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
			yCircle = cos(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
			//kiểm tra xem điểm nào trên đường tròn trùng với điểm nằm trên dường thẳng chứa mũi tên và điểm nằm
			//trên đường thẳng chứa điểm chạm
			if (xCircle <= arrowOnScreen1[0] + allowError && xCircle >= arrowOnScreen1[0] - allowError &&
				yCircle <= arrowOnScreen1[1] + allowError && yCircle >= arrowOnScreen1[1] - allowError) {
				degOfArrow1 = i;
			}
			else if (xCircle <= arrowOnScreen2[0] + allowError && xCircle >= arrowOnScreen2[0] - allowError &&
				yCircle <= arrowOnScreen2[1] + allowError && yCircle >= arrowOnScreen2[1] - allowError) {
				degOfArrow2 = i;
			}
			else if (xCircle <= touchOnScreen[0] + allowError && xCircle >= touchOnScreen[0] - allowError &&
				yCircle <= touchOnScreen[1] + allowError && yCircle >= touchOnScreen[1] - allowError) {
				degOfTouch1 = i;
				degOfTouch2 = i;
			}
			if (degOfArrow1 != -1 && degOfArrow2 != -1 && degOfTouch1 != -1) {
				break;
			}
		}
		//nếu không tính được vòng xoay của mũi tên hay điểm chạm thì bỏ qua
		if (degOfArrow1 == -1 || degOfArrow2 == -1 || degOfTouch1 == -1) {
			return false;
		}
		//tính lại độ của điểm chạm với vị trí arrow trên màn hình là tâm
		if (degOfTouch1 >= degOfArrow1) {
			degOfTouch1 -= degOfArrow1;
		}
		else
		{
			degOfTouch1 -= degOfArrow1;
			degOfTouch1 += 360;
		}

		if (degOfTouch2 >= degOfArrow2) {
			degOfTouch2 -= degOfArrow2;
		}
		else
		{
			degOfTouch2 -= degOfArrow2;
			degOfTouch2 += 360;
		}

		//tính ra giá trị tăng lên(luôn dương,vì đây chỉ là khoảng cách,để biết dương hay âm thì phải dựa vào góc độ của điểm chạm và mũi tên để đặt)
		//tính diện tích của tam giác(gồm 3 điểm là tâm đường tròn,vị trí điểm chạm trên đường tròn,vị trí mũi tên trên đường tròn)
		float distanceTouchAndArrowOnCircle = sqrt(pow(arrowOnScreen1[0] - touchOnScreen[0], 2) + pow(arrowOnScreen1[1] - touchOnScreen[1], 2));
		float p = (distanceTouchAndCenterOnScreen + distanceTouchAndCenterOnScreen + distanceTouchAndArrowOnCircle) / 2;
		float acreage = sqrt(p*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndArrowOnCircle));
		//từ diện tích tam giác tính ra chiều cao từ đỉnh touch xuống
		float heightFromTouch = (2 * acreage) / distanceTouchAndCenterOnScreen;
		//tính ra mức độ tăng lên của mũi tên
		//nếu điểm kéo nằm ở nửa vòng tròn trước thì tăng lên,nếu không thì giảm xuống
		if ((degOfTouch1>90 && degOfTouch1<270)) {
			valuePlus1 = -(sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen1);
		}
		else
		{
			valuePlus1 = sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen1;
		}

		//nếu valuePlus1 là không xác định thì báo lỗi
		if (isnan(valuePlus1)) {
			throw 1;
		}

		//tính cho mũi tên 2
		distanceTouchAndArrowOnCircle = sqrt(pow(arrowOnScreen2[0] - touchOnScreen[0], 2) + pow(arrowOnScreen2[1] - touchOnScreen[1], 2));
		p = (distanceTouchAndCenterOnScreen + distanceTouchAndCenterOnScreen + distanceTouchAndArrowOnCircle) / 2;
		acreage = sqrt(p*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndArrowOnCircle));
		//từ diện tích tam giác tính ra chiều cao từ đỉnh touch xuống
		heightFromTouch = (2 * acreage) / distanceTouchAndCenterOnScreen;
		//tính ra mức độ tăng lên của mũi tên
		//nếu điểm kéo nằm ở nửa vòng tròn trước thì tăng lên,nếu không thì giảm xuống
		if ((degOfTouch2>90 && degOfTouch2<270)) {
			valuePlus2 = -(sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen2);
		}
		else
		{
			valuePlus2 = sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen2;
		}

		//nếu valuePlus2 là không xác định thì báo lỗi
		if (isnan(valuePlus2)) {
			throw 1;
		}

		//tăng giá trị điểm chạm đầu tiên để tính cho lần tiếp theo
		if (whichQuad == 0) {
			center.y += valuePlus1;
			center.x += valuePlus2;
		}
		else if (whichQuad == 1) {
			center.x += valuePlus1;
			center.z += valuePlus2;
		}
		else
		{
			center.z += valuePlus1;
			center.y += valuePlus2;
		}

		return true;
	}
	catch (...)
	{
		return false;
	}
}
//đây là cách tính để scale,nó chỉ tính 1 giá trị tăng
bool caculatorPlusQuad(point &center, int whichQuad, int xNow, int yNow,
	float &valuePlus, double *modelMatrix, double *projectMatrix, int *viewport) {

	double centerOnScreen[3], arrowOnScreen[3], touchOnScreen[2];

	//tính toán tọa độ các mũi tên theo chiều khác nhau ra tọa độ màn hình
	if (whichQuad == 0) {
		gluProject((GLdouble)(center.x + 1), (GLdouble)(center.y + 1), (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	else if (whichQuad == 1) {
		gluProject((GLdouble)(center.x + 1), (GLdouble)center.y, (GLdouble)(center.z + 1), modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	else
	{
		gluProject((GLdouble)center.x, (GLdouble)(center.y + 1), (GLdouble)(center.z + 1), modelMatrix, projectMatrix, viewport,
			&arrowOnScreen[0], &arrowOnScreen[1], &arrowOnScreen[2]);
	}
	//lấy vị trí trung tâm hình trên tọa độ màn hình
	gluProject((GLdouble)center.x, (GLdouble)center.y, (GLdouble)center.z, modelMatrix, projectMatrix, viewport,
		&centerOnScreen[0], &centerOnScreen[1], &centerOnScreen[2]);

	try
	{
		//lấy tỷ giữa mũi tên trong tọa độ 3D và trên màn hình 
		float lengthArrowOnScreen = sqrt(pow((arrowOnScreen[0] - centerOnScreen[0]), 2) + pow((arrowOnScreen[1] - centerOnScreen[1]), 2));
		float scale3dAndScreen = sqrt(2.0) / lengthArrowOnScreen;

		touchOnScreen[0] = xNow;
		touchOnScreen[1] = yNow;
		//lấy ra khoảng cách giữa tâm chạm lần đầu trên mũi tên và điểm chạm hiện tại
		float distanceTouchAndCenterOnScreen = sqrt(pow(centerOnScreen[0] - touchOnScreen[0], 2) + pow(centerOnScreen[1] - touchOnScreen[1], 2));

		//lấy ra vị trí nằm trên đường thảng chứa mũi tên và cách tâm 1 khoảng bằng plusScreen(để ta xem nó nằm ở góc bao nhiêu độ cảu đường tròn vẽ từ tâm)
		normalizeWithRadius2D(centerOnScreen, arrowOnScreen, distanceTouchAndCenterOnScreen);
		//lấy ra vị trí nằm trên đường thẳng chứa tâm và điểm chạm và cách tâm 1 khoảng bằng plusScreen
		normalizeWithRadius2D(centerOnScreen, touchOnScreen, distanceTouchAndCenterOnScreen);

		//vẽ đường tròn để xét xem các điểm kia nằm ở góc bao nhiêu độ
		int degOfArrow = -1, degOfTouch = -1;
		const float DEG2RAD = 3.14159 / 180;
		float degInRad, xCircle, yCircle;

		//tính mức độ sai số cho phép dựa theo bán kính(mức độ sai số cho phép bằng khoảng cách 2 điểm gần nhất)
		float v0[2], v1[2];
		v0[0] = sin(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v0[1] = cos(0 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		v1[0] = sin(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
		v1[1] = cos(1 * DEG2RAD)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
		float allowError = sqrt(pow(v0[0] - v1[0], 2) + pow(v0[1] - v1[1], 2));

		//tính các điểm trên đường tròn để xem mũi tên và điểm chạm nằm ở vị trí nào
		for (int i = 0; i < 360; i++) {
			degInRad = i*DEG2RAD;
			//phải cộng thêm centerCone.y và z vì đây chỉ là vẽ hình tròn quanh tâm 0 thôi(cần dịch chuyển nó đi)
			xCircle = sin(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[0];
			yCircle = cos(degInRad)*distanceTouchAndCenterOnScreen + centerOnScreen[1];
			//kiểm tra xem điểm nào trên đường tròn trùng với điểm nằm trên dường thẳng chứa mũi tên và điểm nằm
			//trên đường thẳng chứa điểm chạm
			if (xCircle <= arrowOnScreen[0] + allowError && xCircle >= arrowOnScreen[0] - allowError &&
				yCircle <= arrowOnScreen[1] + allowError && yCircle >= arrowOnScreen[1] - allowError) {
				degOfArrow = i;
			}
			else if (xCircle <= touchOnScreen[0] + allowError && xCircle >= touchOnScreen[0] - allowError &&
				yCircle <= touchOnScreen[1] + allowError && yCircle >= touchOnScreen[1] - allowError) {
				degOfTouch = i;
			}
			if (degOfArrow != -1 && degOfTouch != -1) {
				break;
			}
		}
		//nếu không tính được vòng xoay của mũi tên hay điểm chạm thì bỏ qua
		if (degOfArrow == -1 || degOfTouch == -1) {
			return false;
		}
		//tính lại độ của điểm chạm với vị trí arrow trên màn hình là tâm
		if (degOfTouch >= degOfArrow) {
			degOfTouch -= degOfArrow;
		}
		else
		{
			degOfTouch -= degOfArrow;
			degOfTouch += 360;
		}

		//tính ra giá trị tăng lên(luôn dương,vì đây chỉ là khoảng cách,để biết dương hay âm thì phải dựa vào góc độ của điểm chạm và mũi tên để đặt)
		//tính diện tích của tam giác(gồm 3 điểm là tâm đường tròn,vị trí điểm chạm trên đường tròn,vị trí mũi tên trên đường tròn)
		float distanceTouchAndArrowOnCircle = sqrt(pow(arrowOnScreen[0] - touchOnScreen[0], 2) + pow(arrowOnScreen[1] - touchOnScreen[1], 2));
		float p = (distanceTouchAndCenterOnScreen + distanceTouchAndCenterOnScreen + distanceTouchAndArrowOnCircle) / 2;
		float acreage = sqrt(p*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndCenterOnScreen)*(p - distanceTouchAndArrowOnCircle));
		//từ diện tích tam giác tính ra chiều cao từ đỉnh touch xuống
		float heightFromTouch = (2 * acreage) / distanceTouchAndCenterOnScreen;
		//tính ra mức độ tăng lên của mũi tên
		//nếu điểm kéo nằm ở nửa vòng tròn trước thì tăng lên,nếu không thì giảm xuống
		float valuePlusTwoSize;
		if ((degOfTouch>90 && degOfTouch<270)) {
			valuePlus = -(sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen);
			valuePlusTwoSize = -sqrt(pow(valuePlus, 2) / 2);
		}
		else
		{
			valuePlus = sqrt(pow(distanceTouchAndCenterOnScreen, 2) - pow(heightFromTouch, 2))*scale3dAndScreen;
			valuePlusTwoSize = sqrt(pow(valuePlus, 2) / 2);
		}

		//nếu valuePlus là không xác định thì báo lỗi
		if (isnan(valuePlus) || isnan(valuePlusTwoSize)) {
			throw 1;
		}

		//tăng giá trị điểm chạm đầu tiên để tính cho lần tiếp theo

		if (whichQuad == 0) {
			center.y += valuePlusTwoSize;
			center.x += valuePlusTwoSize;
		}
		else if (whichQuad == 1) {
			center.x += valuePlusTwoSize;
			center.z += valuePlusTwoSize;
		}
		else
		{
			center.z += valuePlusTwoSize;
			center.y += valuePlusTwoSize;
		}
		return true;
	}
	catch (...)
	{
		return false;
	}
}
//đây là cách tính khi có 3 giá trị tăng
//nó sẽ dùng độ sâu lấy từ vị trí chuột và x,y của màn hình(nếu độ sâu =1.0 là vô cực thì không xác
//định nên sẽ không di chuyển)
bool caculatorPlusQuad(point center, point &firstTouch, int x, int y, float &valuePlusX, float &valuePlusY, float &valuePlusZ,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	//nếu độ sâu khác 1.0 tthif lấy ra vị trí điểm hiện tại
	if (z > 0.0 && z< 1.0) {
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);

		valuePlusX = xDown - center.x;
		valuePlusY = yDown - center.y;
		valuePlusZ = zDown - center.z;

		//tăng vị trí điểm chạm đầu lên để tính toán lần sau
		firstTouch.x += valuePlusX;
		firstTouch.y += valuePlusY;
		firstTouch.z += valuePlusZ;

		return true;
	}
	else
	{
		return false;
	}
}

//hàm nghịch đảo vertex thông qua trục 
//xác định đối xứng qua trục X
void inverseVertexesX(point *vertexArray, int numberVertex, float valueInAxisX) {
	float distanceVertexAndAxis;
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray[i].x - valueInAxisX;
		vertexArray[i].x -= (distanceVertexAndAxis * 2);
	}
}
void inverseVertexesX(vector<point> &vertexArray, float valueInAxisX) {
	float distanceVertexAndAxis;
	int numberVertex = vertexArray.size();
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray.at(i).x - valueInAxisX;
		vertexArray.at(i).x -= (distanceVertexAndAxis * 2);
	}
}
//Xác định đối xứng qua trục Y
void inverseVertexesY(point *vertexArray, int numberVertex, float valueInAxisY) {
	float distanceVertexAndAxis;
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray[i].y - valueInAxisY;
		vertexArray[i].y -= (distanceVertexAndAxis * 2);
	}
}
void inverseVertexesY(vector<point> &vertexArray, float valueInAxisY) {
	float distanceVertexAndAxis;
	int numberVertex = vertexArray.size();
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray.at(i).y - valueInAxisY;
		vertexArray.at(i).y -= (distanceVertexAndAxis * 2);
	}
}
//Xác định đối xứng qua trục Z
void inverseVertexesZ(point *vertexArray, int numberVertex, float valueInAxisZ) {
	float distanceVertexAndAxis;
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray[i].z - valueInAxisZ;
		vertexArray[i].z -= (distanceVertexAndAxis * 2);
	}
}
void inverseVertexesZ(vector<point> &vertexArray, float valueInAxisZ) {
	float distanceVertexAndAxis;
	int numberVertex = vertexArray.size();
	for (int i = 0; i < numberVertex; i++) {
		distanceVertexAndAxis = vertexArray.at(i).z - valueInAxisZ;
		vertexArray.at(i).z -= (distanceVertexAndAxis * 2);
	}
}

//hàm nghịc đảo các vertex dành riêng cho các hình
//hàm này dùng cho các hình bao vòng (có numberLongitude và numberLagitude như sphere)
void inverseCylinder_Sphere_Cone(int axis,
	int numberLongitude, int numberLatitude, vector<point> &vertexArray, point center) {
	//đàu tiên đảo chiều đối xứng tất cả các vertex thông qua trục
	if (axis == 0) {
		inverseVertexesX(vertexArray, center.x);
	}
	else if (axis == 1) {
		inverseVertexesY(vertexArray, center.y);
	}
	else
	{
		inverseVertexesZ(vertexArray, center.z);
	}
	//đảo chiều tất cả các vertex trong mỗi vòng(vì khi đảo chiều đối xứng sẽ ngược chiều,tính normal vector bị sai)
	point v;
	int halfLongitude = numberLongitude / 2, offset1, offset2;
	for (int i = 0; i < numberLatitude; i++) {
		//vị trí đầu tiên của cụm vertex
		offset1 = i*numberLongitude;
		//vị trí cuối cùng của cụm vertex
		offset2 = (i + 1)*numberLongitude;
		//bắt đầu từ 1 do vị trí 0 không thay đổi(nếu numberLongitude là chẵn thì vị trí đối diện với 0 cũng không hay đổi)
		for (int j = 1; j < halfLongitude; j++) {
			v = vertexArray[offset1 + j];
			vertexArray[offset1 + j] = vertexArray[offset2 - j];
			vertexArray[offset2 - j] = v;
		}
	}
}
//hàm này dùng riêng cho cube
void inverseCube(int axis,
	int numberVertexInAxisX, int numberVertexInAxisY, int numberVertexInAxisZ, vector<point> &vertexArray, point center) {
	//đàu tiên đảo chiều đối xứng tất cả các vertex thông qua trục
	if (axis == 0) {
		inverseVertexesX(vertexArray, center.x);
	}
	else if (axis == 1) {
		inverseVertexesY(vertexArray, center.y);
	}
	else
	{
		inverseVertexesZ(vertexArray, center.z);
	}

	//đảo chiều tất cả các vertex trong mỗi vòng(vì khi đảo chiều đối xứng sẽ ngược chiều,tính normal vector bị sai)
	/*point v;
	int numberVertexOnRow = (numberVertexInAxisX - 1) * 2 + (numberVertexInAxisZ - 1) * 2,
		halfVertexOnRow = numberVertexOnRow / 2, offset1, offset2;
	for (int i = 0; i < numberVertexInAxisY; i++) {
		//vị trí đầu tiên của cụm vertex
		offset1 = i*numberVertexOnRow;
		//vị trí cuối cùng của cụm vertex
		offset2 = (i + 1)*numberVertexOnRow - 1;
		for (int j = 0; j < halfVertexOnRow; j++) {
			v = vertexArray[offset1 + j];
			vertexArray[offset1 + j] = vertexArray[offset2 - j];
			vertexArray[offset2 - j] = v;
		}
	}*/
}
//hàm này dùng riêng cho torus
void inverseTorus(int axis,
	int depthRound, vector<point> &vertexArray, point center) {
	//đàu tiên đảo chiều đối xứng tất cả các vertex thông qua trục
	if (axis == 0) {
		inverseVertexesX(vertexArray, center.x);
	}
	else if (axis == 1) {
		inverseVertexesY(vertexArray, center.y);
	}
	else
	{
		inverseVertexesZ(vertexArray, center.z);
	}

	//đảo chiều tất cả các vertex trong mỗi vòng(vì khi đảo chiều đối xứng sẽ ngược chiều,tính normal vector bị sai)
	point v;
	int depthCake = vertexArray.size() / depthRound;
	int halfDepthCake = depthCake / 2, offset1, offset2;
	for (int i = 0; i < depthRound; i++) {
		//vị trí đầu tiên của cụm vertex
		offset1 = i*depthCake;
		//vị trí cuối cùng của cụm vertex
		offset2 = (i + 1)*depthCake - 1;
		for (int j = 0; j < halfDepthCake; j++) {
			v = vertexArray[offset1 + j];
			vertexArray[offset1 + j] = vertexArray[offset2 - j];
			vertexArray[offset2 - j] = v;
		}
	}
}
//lấy các ma trận modelview
void getModelMatrix(double *modelMatrix, double *modelMatrixArrow,
	float translateX, float translateY, float translateZ,
	float zoomObject, float rotateX, float rotateY, int modelSpace) {
	glMatrixMode(GL_MODELVIEW);
	//lấy ma trận modelview cho vật
	glLoadIdentity();
	//các thao tác xoay và zoom vật
	//để thiết lâp camera tự xoay quanh mình chứ k0 phải xoay quanh vật thì đặt rotate trước rồi mới translate
	//nhưng cần phải tính cách translate dựa trên mức xoay của mày ảnh,vì nếu k0 nó sẽ vẫn đi theo trục x,y,z 
	//ban đầu do ta dịch chuyển trước khi xoay

	//đàu tiên là đẩy tâm xoay ra xa theo giá trị của zoomObject
	if (modelSpace == 0) {
		glTranslatef(0.0f, 0.0f, -50);
	}
	else
	{
		//nếu là chế độ 3D thì vật lớn hay nhỏ còn phục thuộc vào khoảng cách vật đến máy ảnh
		glTranslatef(0.0f, 0.0f, zoomObject);
	}
	//tiếp theo ta xoay tâm xoay theo hướng mình muốn
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	//cuối cùng ta dịch chuyển tâm xoay
	if (modelSpace == 0) {
		float valueZoom = 30 / (-zoomObject);
		//nếu là chế độ 2D thì vật lớn hay nhỏ tùy thuộc vào kích thước vật và kích thước khung ảnh
		glTranslatef(translateX, translateY, translateZ);
		glScalef(valueZoom, valueZoom, valueZoom);
	}
	else
	{
		//nếu là chế độ 3D thì vật lớn hay nhỏ còn phục thuộc vào khoảng cách vật đến máy ảnh
		glTranslatef(translateX, translateY, translateZ);
	}

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
	//lấy ma trận modelview cho các mũi tên
	glLoadIdentity();
	glTranslatef(-1.0, -1.0, -2.0);
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrixArrow);
}
//chỉ lấy duy nhất ma trận model matrix
void getModelMatrixOnly(double *modelMatrix, float translateX, float translateY,
	float zoomObject, float rotateX, float rotateY, int modelSpace) {
	glMatrixMode(GL_MODELVIEW);
	//lấy ma trận modelview cho vật
	glLoadIdentity();
	//các thao tác xoay và zoom vật
	//để thiết lâp camera tự xoay quanh mình chứ k0 phải xoay quanh vật thì đặt rotate trước rồi mới translate
	//nhưng cần phải tính cách translate dựa trên mức xoay của mày ảnh,vì nếu k0 nó sẽ vẫn đi theo trục x,y,z 
	//ban đầu do ta dịch chuyển trước khi xoay
	if (modelSpace == 0) {
		float valueZoom = 30 / (-zoomObject);
		//nếu là chế độ 2D thì vật lớn hay nhỏ tùy thuộc vào kích thước vật và kích thước khung ảnh
		glTranslatef(translateX, translateY, -50);
		glScalef(valueZoom, valueZoom, valueZoom);
	}
	else
	{
		//nếu là chế độ 3D thì vật lớn hay nhỏ còn phục thuộc vào khoảng cách vật đến máy ảnh
		glTranslatef(translateX, translateY, zoomObject);
	}
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
}
//hàm lấy các ma trận chiếu cho project
void getMatrixForProjection(int modelSpace, int w, int h,
	GLdouble *projectMatrix, GLdouble *projectMatrixArrow) {
	//modelSpace = 0 là 2D và = 1 là 3D

	glMatrixMode(GL_PROJECTION);
	//lấy ma trận chiếu 3D
	glLoadIdentity();
	if (modelSpace == 0) {
		float halfWidth = w / (100), halfHeight = h / (100);
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1, 100.0);
	}
	else {
		gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	}

	glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
	//lấy ma trận chiếu 2D cho mũi tên
	glLoadIdentity();
	glOrtho(-1.3, 3.0, -1.3, 3.0, -3.0, 3.0);
	glGetDoublev(GL_PROJECTION_MATRIX, projectMatrixArrow);
}

//hàm lấy duy nhất ma trận chiếu
void getMatrixForProjectionOnly(int modelSpace, int w, int h, GLdouble *projectMatrix) {
	//modelSpace = 0 là 2D và = 1 là 3D

	glMatrixMode(GL_PROJECTION);
	//lấy ma trận chiếu 3D
	glLoadIdentity();
	if (modelSpace == 0) {
		float halfWidth = w / (100), halfHeight = h / (100);
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0, 100.0);
	}
	else {
		gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	}

	glGetDoublev(GL_PROJECTION_MATRIX, projectMatrix);
}

void getCenterObjectChoice(itemChoice item,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//kiêm tra xem hình được chọn có thông tin trong item nào của symmetryObject không
	int numberSymmetry = symmetryObjects.size();
	SymmetryObjects symmetryCheck;
	bool isHaveSymmetryObject = false;
	for (int i = 0; i < numberSymmetry; i++) {
		symmetryCheck = symmetryObjects.at(i);
		if (item.object == symmetryCheck.object1 &&
			(item.positionOfChoice == symmetryCheck.positionInArray1 ||
				item.positionOfChoice == symmetryCheck.positionInArray2)) {
			isHaveSymmetryObject = true;
			break;
		}
	}

	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
		centerObjectOrVertices = tria->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				tria = triangleArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				tria = triangleArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = tria->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		centerObjectOrVertices = triaStrip->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = triaStrip->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		centerObjectOrVertices = triaFan->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = triaFan->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		centerObjectOrVertices = sphere->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = sphere->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		centerObjectOrVertices = cube->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				cube = cubeArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = cube->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		centerObjectOrVertices = cube->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = cube->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		centerObjectOrVertices = cone->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = cone->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		centerObjectOrVertices = cylinder->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = cylinder->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 15:
	{
		PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
		centerObjectOrVertices = pyr->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				pyr = pyrArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				pyr = pyrArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = pyr->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		centerObjectOrVertices = cylinder->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = cylinder->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		centerObjectOrVertices = torus->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				torus = torusArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				torus = torusArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = torus->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		centerObjectOrVertices = picture->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryCheck.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = picture->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		centerObjectOrVertices = object->centerObject;
		if (isHaveSymmetryObject) {
			if (symmetryCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryCheck.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = object->centerObject;
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	default:
		break;
	}
}
void getCenterVertexsForScale(itemChoice item, vector<int> positionVerticesChoice,
	point &centerObjectOrVertices, point &centerObjectOrVerticesSymmetry,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	bool isHaveSymmetryVertices = false, isHaveSymmetryObjects = false;
	//kiểm tra xem có thông tin về hình được chọn trong đối xứng vertex không
	int numberElement = symmetryVertices.size();
	SymmetryVertices symmetryCheckVertices;
	SymmetryObjects symmetryCheckObject;

	for (int i = 0; i < numberElement; i++) {
		symmetryCheckVertices = symmetryVertices.at(i);
		if (symmetryCheckVertices.object == item.object &&
			symmetryCheckVertices.positionInArray == item.positionOfChoice) {
			isHaveSymmetryVertices = true;
			break;
		}
	}
	//nếu không có đối xứng vertex thì
	//kiểm tra xem có hình được chọn trong đối xứng object không
	if (!isHaveSymmetryVertices) {
		numberElement = symmetryObjects.size();
		for (int i = 0; i < numberElement; i++) {
			symmetryCheckObject = symmetryObjects.at(i);
			if (symmetryCheckObject.object1 == item.object &&
				(symmetryCheckObject.positionInArray1 == item.positionOfChoice ||
					symmetryCheckObject.positionInArray2 == item.positionOfChoice)) {
				isHaveSymmetryObjects = true;
				break;
			}
		}
	}

	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(tria->vertexArray, positionVerticesChoice);

		//nếu là đối xứng vertex thì lấy ra tâm đối xứng vertex
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(tria->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		//nếu là đối xứng object thì lấy ra tâm đối xứng object
		else if (isHaveSymmetryObjects)
		{
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				tria = triangleArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				tria = triangleArray.at(symmetryCheckObject.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(tria->vertexArray, positionVerticesChoice);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				tria = triangleArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				tria = triangleArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 3;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(tria->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
		
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(triaStrip->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(triaStrip->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				triaStrip = triaStripArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				triaStrip = triaStripArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaStrip->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(triaStrip->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(triaFan->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(triaFan->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				triaFan = triaFanArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				triaFan = triaFanArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = triaFan->vertexArray.size();
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(triaFan->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(sphere->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(sphere->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(sphere->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(cube->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(cube->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects)
		{
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				cube = cubeArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				cube = cubeArray.at(symmetryCheckObject.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(cube->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(cube->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(cube->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				cube = cubeRoundArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				cube = cubeRoundArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(cube->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(cone->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(cone->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(cone->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(cylinder->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(cylinder->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(cylinder->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(cylinder->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(cylinder->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(cylinder->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(torus->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(torus->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects)
		{
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				torus = torusArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				torus = torusArray.at(symmetryCheckObject.positionInArray1);
			}
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(torus->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 18:
	{
		PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(picture->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(picture->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				picture = pictureArray.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				picture = pictureArray.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đối với các hình không có numberLongitude và numberLatitude thì chỉ cần
				//đảo ngược vị trí các vertex từ trước->sau thành sau->trước
				numberElement = positionVerticesChoice.size();
				int numberVertex = 4;
				for (int i = 0; i < numberElement; i++) {
					positionVerticesChoice.at(i) = numberVertex - 1 - positionVerticesChoice.at(i);
				}
			}

			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(picture->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		centerObjectOrVertices = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);
		if (isHaveSymmetryVertices) {
			centerObjectOrVerticesSymmetry = getPointCenterVertexesSymmetryAtPosition(object->vertexArray, positionVerticesChoice,
				symmetryCheckVertices.positionVertices1, symmetryCheckVertices.positionVertices2);
		}
		else if (isHaveSymmetryObjects) {
			//lấy object đối xứng với object được chọn để lấy tâm xoay vertex của object đối xứng
			if (symmetryCheckObject.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryCheckObject.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryCheckObject.positionInArray1);
			}
			//nếu nghịch đảo trên hàng thì biến đổi positionVerticesChoice vì nó chỉ là bản sao
			//nên không ảnh hưởng đến bản chính
			if (symmetryCheckObject.isInvertedItemsInRow) {
				//đảo ngược các vertex trên mỗi hàng(ngoài các vertex đầu tiên của mỗi hàng)
				numberElement = positionVerticesChoice.size();
				int startRow = 0, endRow = symmetryCheckObject.numberItemInRow, elementCheck;
				for (int i = 0; i < numberElement; i++) {
					elementCheck = positionVerticesChoice.at(i);
					//tìm ra điểm bắt đầu và kết thúc của hàng(row) chứa điểm hiện tại
					while (elementCheck >= endRow) {
						startRow += symmetryCheckObject.numberItemInRow;
						endRow += symmetryCheckObject.numberItemInRow;
					}
					//nếu elementCheck == startRow thì không thay đổi giá trị
					//còn nếu khác thì mới biến đổi trước->sau thành sau->trước trên hàng(row)
					if (elementCheck != startRow) {
						positionVerticesChoice.at(i) = endRow - (elementCheck - startRow);
					}

					startRow = 0;
					endRow = symmetryCheckObject.numberItemInRow;
				}
			}
			//sau khi đã thay đổi positionVerticesChoice(nếu cần) thì lấy tâm biến đổi cho hình đối xứng
			centerObjectOrVerticesSymmetry = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);
		}
		else
		{
			centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };
		}
	}
	break;
	default:
		break;
	}
}

//xóa các điểm chọn giống nhau trong chế độ chọn cộng dồn(mouseModel=1)
void clearSamePoints(vector<int> &vertexArrayChoice) {
	int numberVertex = vertexArrayChoice.size(),
		pNow;
	for (int i = 0; i < numberVertex - 1; i++) {
		pNow = vertexArrayChoice.at(i);
		for (int j = i + 1; j < numberVertex; j++) {
			//nếu điểm được chọn giống nhau thì xóa điểm đó đi
			if (pNow == vertexArrayChoice.at(j)) {
				vertexArrayChoice.erase(vertexArrayChoice.begin() + j);
				numberVertex--;
				j--;
			}
		}
	}
}
//xóa các itemChoice trùng nhau
void clearSameItemsChoice(vector<itemChoice> &itemsChoice) {
	int numberItemChoice = itemsChoice.size(),
		idNow;
	for (int i = 0; i < numberItemChoice - 1; i++) {
		idNow = itemsChoice.at(i).id;
		for (int j = i + 1; j < numberItemChoice; j++) {
			//mỗi vật sẽ có 1 id riêng nên nếu trùng id là cùng 1 vật
			if (idNow == itemsChoice.at(j).id) {
				itemsChoice.erase(itemsChoice.begin() + j);
				numberItemChoice--;
				j--;
			}
		}
	}
}
//xóa các PositionRowOrColumn
void clearSamePositionRowOrColumn(vector<PositionRowOrColumn> &positionRowOrColumn) {
	int numberPosition = positionRowOrColumn.size();
	PositionRowOrColumn pNow, pCheck;
	for (int i = 0; i < numberPosition - 1; i++) {
		pNow = positionRowOrColumn.at(i);
		for (int j = i + 1; j < numberPosition; j++) {
			pCheck = positionRowOrColumn.at(j);
			//nếu row hay column mà trùng 1 số ngoại trừ -1 thì bị trùng
			//nếu cùng là chọn hàng thì kiểm tra xem có trùng hàng không
			//nếu cùng là chọn cột thì kiểm tra xem có trùng cột không
			if ((pNow.positionRow != -1 && pNow.positionRow == pCheck.positionRow) || 
				(pNow.positionColumn != -1 && pNow.positionColumn == pCheck.positionColumn)) {
				positionRowOrColumn.erase(positionRowOrColumn.begin() + j);
				numberPosition--;
				j--;
			}
		}
	}
}
//kiểm tra xem có phần tư nào trong mảng được chọn nằm sau phần tử vừa xóa(cùng kiểu phần tử) k0
//nếu có thì lùi giá trị của vị trí 1 đơn vị
void checkHaveAnyElementBehindElementDelete(vector<itemChoice> &itemsChoice, itemChoice item, int positionItem) {
	int numberItemChoice = itemsChoice.size();
	for (int j = 0; j < numberItemChoice; j++) {
		//nếu phần tử này là cùng kiểu phần tử,k0 phải phần tử hiện tại và phần tử này có vị trí 
		//trong mảng phần tử lớn hơn vị trí của phần tử hiện tại thì lùi lại 1 vị trí
		if (positionItem != j && itemsChoice.at(j).object == item.object &&
			itemsChoice.at(j).positionOfChoice>item.positionOfChoice) {
			itemsChoice.at(j).positionOfChoice--;
		}
	}
}
void deleteVertexChoice(itemChoice item, vector<int> &positionVerticesChoice,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray) {
	//lấy phần tử được chọn đầu tiên

	int numberItemDelete = positionVerticesChoice.size();
	int a;
	//sắp xếp các item được chọn để xóa theo thứ tự giảm dần
	for (int i = 0; i < numberItemDelete; i++) {
		for (int j = 1; j < numberItemDelete; j++) {
			if (positionVerticesChoice.at(j) > positionVerticesChoice.at(j - 1)) {
				a = positionVerticesChoice.at(j);
				positionVerticesChoice.at(j) = positionVerticesChoice.at(j - 1);
				positionVerticesChoice.at(j - 1) = a;
			}
		}
	}
	switch (item.object)
	{
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		int numberVertex = triaStrip->vertexArray.size();
		//nếu số lượng item hiện có trừ số lượng cần xóa mà lớn hơn hoặc bằng 3 thì cho phép
		if ((numberVertex - numberItemDelete) >= 3) {
			//xóa các vertex đang được chọn
			for (int i = 0; i < numberItemDelete; i++) {
				triaStrip->vertexArray.erase(triaStrip->vertexArray.begin() + positionVerticesChoice.at(i));
				triaStrip->normalVector.erase(triaStrip->normalVector.begin() + positionVerticesChoice.at(i));
			}
			//sau khi xóa xong thì xóa hết giá trị các phần tử đang chọn
			positionVerticesChoice.clear();
		}
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		int numberVertex = triaFan->vertexArray.size();
		//nếu số lượng item hiện có trừ số lượng cần xóa mà lớn hơn hoặc bằng 3 thì cho phép
		if ((numberVertex - numberItemDelete) >= 3) {
			//xóa các vertex đang được chọn
			for (int i = 0; i < numberItemDelete; i++) {
				triaFan->vertexArray.erase(triaFan->vertexArray.begin() + positionVerticesChoice.at(i));
				triaFan->normalVector.erase(triaFan->normalVector.begin() + positionVerticesChoice.at(i));
			}
			//sau khi xóa xong thì xóa hết giá trị các phần tử đang chọn
			positionVerticesChoice.clear();
		}
	}
	break;
	default:
		break;
	}
}
void deleteModelChoice(vector<itemChoice> &itemsChoice, vector<int> &positionVerticesChoice,
	int modelEditStyle, vector<int> &idsUsing,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	if (!itemsChoice.empty()) {
		int idObject;
		//nếu đang ở chế độ chọn vertex và chỉ có 1 đối tượng được chọn
		if (modelEditStyle == 1) {
			deleteVertexChoice(itemsChoice.at(0), positionVerticesChoice, triaStripArray, triaFanArray);
		}
		else if (modelEditStyle == 2) {
			//phải có hàm xóa chuỗi vertex ở đây

		}
		else if (modelEditStyle == 0)
		{
			int numberItemChoice = itemsChoice.size(),
				numberItemUsing = idsUsing.size(),
				numberVerticesSymmetry = symmetryVertices.size(),
				numberObjectsSymmetry = symmetryObjects.size();
			SymmetryVertices symmetryVerticesCheck;
			SymmetryObjects symmetryObjectsCheck;
			for (int i = 0; i < numberItemChoice; i++) {
				itemChoice item = itemsChoice.at(i);

				//nếu là chế độ xóa vật thì kiểm tra nếu vật bị xóa nằm trong mảng xác đinh đối xứng thì xóa
				//vật đó ra khỏi mảng xác định các vật có đỉnh đối xứng
				for (int j = 0; j < numberVerticesSymmetry; j++) {
					symmetryVerticesCheck = symmetryVertices.at(j);
					if (symmetryVerticesCheck.object == item.object &&
						symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
						//xóa phần tử có đối tượng là đối tượng đối xứng
						symmetryVertices.erase(symmetryVertices.begin() + j);
						numberVerticesSymmetry--;
						break;
					}
				}
				//kiểm tra xem vật bị xóa có thông tin nằm trong symmetryObjects không
				for (int j = 0; j < numberObjectsSymmetry; j++) {
					symmetryObjectsCheck = symmetryObjects.at(j);
					if (symmetryObjectsCheck.object1 == item.object &&
						(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
							symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
						//xóa phần tử có đối tượng là đối tượng đối xứng
						symmetryObjects.erase(symmetryObjects.begin() + j);
						numberObjectsSymmetry--;
						break;
					}
				}

				//nếu là chế độ
				switch (item.object)
				{
					//trước khi xóa các con trỏ phải xóa các vùng nhớ mà nó trỏ đến nếu k0 sẽ bị rò rỉ bộ nhớ
				case 3:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = triangleArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete triangleArray.at(item.positionOfChoice);
					triangleArray.erase(triangleArray.begin() + item.positionOfChoice);
					break;
				case 4:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = triaStripArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete triaStripArray.at(item.positionOfChoice);
					triaStripArray.erase(triaStripArray.begin() + item.positionOfChoice);
					break;
				case 5:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = triaStripArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete triaFanArray.at(item.positionOfChoice);
					triaFanArray.erase(triaFanArray.begin() + item.positionOfChoice);
					break;
				case 10:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = sphereArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete sphereArray.at(item.positionOfChoice);
					sphereArray.erase(sphereArray.begin() + item.positionOfChoice);
					break;
				case 11:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = cubeArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete cubeArray.at(item.positionOfChoice);
					cubeArray.erase(cubeArray.begin() + item.positionOfChoice);
					break;
				case 12:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = cubeRoundArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete cubeRoundArray.at(item.positionOfChoice);
					cubeRoundArray.erase(cubeRoundArray.begin() + item.positionOfChoice);
					break;
				case 13:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = coneArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete coneArray.at(item.positionOfChoice);
					coneArray.erase(coneArray.begin() + item.positionOfChoice);
					break;
				case 14:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = cylinderArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete cylinderArray.at(item.positionOfChoice);
					cylinderArray.erase(cylinderArray.begin() + item.positionOfChoice);
					break;
				case 15:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = pyrArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete pyrArray.at(item.positionOfChoice);
					pyrArray.erase(pyrArray.begin() + item.positionOfChoice);
					break;
				case 16:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = emptyCylinderArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete emptyCylinderArray.at(item.positionOfChoice);
					emptyCylinderArray.erase(emptyCylinderArray.begin() + item.positionOfChoice);
					break;
				case 17:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = torusArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete torusArray.at(item.positionOfChoice);
					torusArray.erase(torusArray.begin() + item.positionOfChoice);
					break;
				case 18:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = pictureArray.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete pictureArray.at(item.positionOfChoice);
					pictureArray.erase(pictureArray.begin() + item.positionOfChoice);
					break;
				case 19:
					//xóa id của vật ở trong mảng id đang được dùng
					idObject = objectCustom0Array.at(item.positionOfChoice)->id;
					for (int k = 0; k < numberItemUsing; k++) {
						if (idsUsing.at(k) == idObject) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
					delete objectCustom0Array.at(item.positionOfChoice);
					objectCustom0Array.erase(objectCustom0Array.begin() + item.positionOfChoice);
					break;
				default:
					break;
				}
				checkHaveAnyElementBehindElementDelete(itemsChoice, item, i);
			}
			itemsChoice.clear();
		}
	}
}
void setColorForModelChoice(vector<itemChoice> itemsChoice, float *colorDefaul,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	if (!itemsChoice.empty()) {
		int numberItemChoice = itemsChoice.size();
		for (int i = 0; i < numberItemChoice; i++) {
			itemChoice item = itemsChoice.at(i);
			switch (item.object)
			{
			case 3: {
				TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
				tria->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					break;
			case 4: {
				TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
				triaStrip->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					break;
			case 5: {
				TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
				triaFan->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					break;
			case 10: {
				SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
				sphere->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 11: {
				CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
				cube->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 12: {
				CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
				cube->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 13: {
				ConeAttribute *cone = coneArray.at(item.positionOfChoice);
				cone->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 14: {
				CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
				cylinder->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 15: {
				PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
				pyr->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 16: {
				EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
				cylinder->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 17: {
				TorusAttribute *torus = torusArray.at(item.positionOfChoice);
				torus->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			case 19: {
				ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
				object->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			}
					 break;
			default:
				break;
			}
		}
	}
}
//hàm này xóa các vật đang vẽ hiện tại mà chưa vẽ xong
bool clearLastDrawNotDone(int lastDraw, vector<int> &idsUsing,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray) {
	switch (lastDraw)
	{
	case 4:
		//kiểm tra số vertex của tam giác cuối cùng,nếu không đủ thì xóa đi
		if (triaStripArray.back()->vertexArray.size() < 3) {
			//xóa id cuối cùng mới thêm vào
			idsUsing.erase(idsUsing.begin() + idsUsing.size() - 1);
			triaStripArray.pop_back();
		}
		return true;
	case 5:
		//kiểm tra số vertex của tam giác cuối cùng,nếu không đủ thì xóa đi
		if (triaFanArray.back()->vertexArray.size() < 3) {
			//xóa id cuối cùng mới thêm vào
			idsUsing.erase(idsUsing.begin() + idsUsing.size() - 1);
			triaFanArray.pop_back();
		}
		return true;
	default:
		break;
	}
	return false;
}
//hàm này xóa đi vertex cuối cùng của các hình vẽ bằng vertex
//Chỉ dùng cho 2 hình triaStrip và triaFan vì triangle chỉ có 3 vertex
//nó đòng thời cũng xóa đi normal tương ứng với vertex đó
void clearLastVertexDraw(itemChoice item,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray) {
	switch (item.object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		triaStrip->vertexArray.pop_back();
		//nếu chỉ mới có 2 vertex thì chưa xác định được normal nên phải đề phòng không sẽ bị lỗi
		if (!triaStrip->normalVector.empty()) {
			triaStrip->normalVector.pop_back();
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		triaFan->vertexArray.pop_back();
		//nếu chỉ mới có 2 vertex thì chưa xác định được normal nên phải đề phòng không sẽ bị lỗi
		if (!triaFan->normalVector.empty()) {
			triaFan->normalVector.pop_back();
		}
	}
			break;
	default:
		break;
	}
}
//hàm dichjc huyển vertex cuối cùng của hình đang vẽ dở
void moveLastVertexDraw(itemChoice item, float valuePlusX, float valuePlusY, float valuePlusZ,
	vector<TriangleAttribute*> &triangleArray,
	vector<TriangleStripAttribute*> &triaStripArray, vector<TriangleFanAttribute*> &triaFanArray) {
	switch (item.object)
	{
	case 3: {
		TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
		//kiểm tra xem vertex đang vẽ dở là vertex nào
		for (int i = 2; i >= 0; i--) {
			if (tria->vertexArray[i].x != NULL) {
				tria->vertexArray[i].x += valuePlusX;
				tria->vertexArray[i].y += valuePlusY;
				tria->vertexArray[i].z += valuePlusZ;
				break;
			}
		}
	}
			break;
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		triaStrip->vertexArray.back().x += valuePlusX;
		triaStrip->vertexArray.back().y += valuePlusY;
		triaStrip->vertexArray.back().z += valuePlusZ;
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		triaFan->vertexArray.back().x += valuePlusX;
		triaFan->vertexArray.back().y += valuePlusY;
		triaFan->vertexArray.back().z += valuePlusZ;
	}
			break;
	default:
		break;
	}
}

//hàm tính góc từ 3 điểm
float CaculatorDegreesFrom3Point(point v0, point v1, point v2) {
	try
	{
		//lấy vector cho 2 đường thẳng
		point v0v1 = { v1.x - v0.x,v1.y - v0.y,v1.z - v0.z },
			v1v2 = { v2.x - v1.x,v2.y - v1.y,v2.z - v1.z };
		float distanceV0V1 = sqrt(pow(v0v1.x, 2) + pow(v0v1.y, 2) + pow(v0v1.z, 2)),
			distanceV1V2 = sqrt(pow(v1v2.x, 2) + pow(v1v2.y, 2) + pow(v1v2.z, 2));
		float multiplyTwoVector = v0v1.x*v1v2.x + v0v1.y*v1v2.y + v0v1.z*v1v2.z;

		return (acos(multiplyTwoVector / (distanceV0V1*distanceV1V2)))*(180 / M_PI);
	}
	catch (...)
	{
		return 0.0;
	}

}

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
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	//có 2 phương án:1 là chuyển sang tọa độ màn hình hết để so sánh,2 là chuyển sang tọa độ 3D hết rồi so sánh
	//ta chuyển sang tọa độ 3D thì cần ít phép tính hơn,và lấy cũng chính xác hơn,nhưng chọn trúng ít điểm hơn
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	int numberObject, numberVertex;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	//nếu độ sâu khác 1.0 tthif lấy ra vị trí điểm hiện tại
	if (z > 0.0 && z< 1.0) {
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		//load lên hết tất cả các vertex của các hình đang tồn tại để lấy ra vị trí gần nhất với vị trí chuột
		numberObject = triangleArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleAttribute *tria = triangleArray.at(i);
			for (int j = 0; j < 3; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(tria->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = tria->vertexArray[j].x;
					yPosition = tria->vertexArray[j].y;
					zPosition = tria->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = triaStripArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			numberVertex = triaStrip->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(triaStrip->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = triaStrip->vertexArray[j].x;
					yPosition = triaStrip->vertexArray[j].y;
					zPosition = triaStrip->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = triaFanArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			numberVertex = triaFan->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(triaFan->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = triaFan->vertexArray[j].x;
					yPosition = triaFan->vertexArray[j].y;
					zPosition = triaFan->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = sphereArray.size();
		for (int i = 0; i < numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			numberVertex = sphere->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(sphere->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = sphere->vertexArray[j].x;
					yPosition = sphere->vertexArray[j].y;
					zPosition = sphere->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = cubeArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			numberVertex = cube->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(cube->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = cube->vertexArray[j].x;
					yPosition = cube->vertexArray[j].y;
					zPosition = cube->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = cubeRoundArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);
			numberVertex = cube->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(cube->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = cube->vertexArray[j].x;
					yPosition = cube->vertexArray[j].y;
					zPosition = cube->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = coneArray.size();
		for (int i = 0; i < numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);
			numberVertex = cone->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(cone->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = cone->vertexArray[j].x;
					yPosition = cone->vertexArray[j].y;
					zPosition = cone->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = cylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			numberVertex = cylinder->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(cylinder->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = cylinder->vertexArray[j].x;
					yPosition = cylinder->vertexArray[j].y;
					zPosition = cylinder->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = pyrArray.size();
		for (int i = 0; i < numberObject; i++) {
			PyramidAttribute *pyr = pyrArray.at(i);
			for (int j = 0; j < 5; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(pyr->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = pyr->vertexArray[j].x;
					yPosition = pyr->vertexArray[j].y;
					zPosition = pyr->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			numberVertex = cylinder->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(cylinder->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = cylinder->vertexArray[j].x;
					yPosition = cylinder->vertexArray[j].y;
					zPosition = cylinder->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = torusArray.size();
		for (int i = 0; i < numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			numberVertex = torus->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.001 thì lấy điểm đó
				if (distanceTwoPoint(torus->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = torus->vertexArray[j].x;
					yPosition = torus->vertexArray[j].y;
					zPosition = torus->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = pictureArray.size();
		for (int i = 0; i < numberObject; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			for (int j = 0; j < 4; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(picture->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = picture->vertexArray[j].x;
					yPosition = picture->vertexArray[j].y;
					zPosition = picture->vertexArray[j].z;
					return true;
				}
			}
		}
		numberObject = objectCustom0Array.size();
		for (int i = 0; i < numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			numberVertex = object->vertexArray.size();
			for (int j = 0; j < numberVertex; j++) {
				//nếu khoảng cách nhỏ hơn 0.05 thì lấy điểm đó
				if (distanceTwoPoint(object->vertexArray[j], { (float)xDown,(float)yDown,(float)zDown }) < 0.05) {
					xPosition = object->vertexArray[j].x;
					yPosition = object->vertexArray[j].y;
					zPosition = object->vertexArray[j].z;
					return true;
				}
			}
		}
	}
	//nếu không có gì xảy ra thì không có điểm nào được tìm thấy gần vị trí nhấn chuột
	return false;
}

//hàm chuyển các điểm về cùng 1 vị trí X trên trục X
void MakeVertexSameX(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberVertexChoice = positionVertexChoice.size();
	float positionX = 0.0;
	if (numberVertexChoice > 0) {
		switch (item.object)
		{
		case 3: {
			TriangleAttribute *object = triangleArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				break;
		case 4: {
			TriangleStripAttribute *object = triaStripArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *object = triaFanArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				break;
		case 10: {
			SphereAttribute *object = sphereArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 11: {
			CubeAttribute *object = cubeArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *object = cubeRoundArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 13: {
			ConeAttribute *object = coneArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 14: {
			CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 15: {
			PyramidAttribute *object = pyrArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 17: {
			TorusAttribute *object = torusArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 18: {
			PictureAttribute *object = pictureArray.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			//đầu tiên tính ra điểm X nằm chính giữa
			for (int i = 0; i < numberVertexChoice; i++) {
				positionX += object->vertexArray[positionVertexChoice[i]].x;
			}
			positionX = positionX / numberVertexChoice;
			//sau khi tính ra vị trí X chính giữa thì đặt X cho tất cả các item đang chọn
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].x = positionX;
			}
		}
				 break;
		default:
			break;
		}
	}
}
//hàm chuyển các điểm về cùng 1 vị trí Y trên trục Y
void MakeVertexSameY(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberVertexChoice = positionVertexChoice.size();
	float positionY = 0.0;
	if (numberVertexChoice > 0) {
		switch (item.object)
		{
		case 3: {
			TriangleAttribute *object = triangleArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				break;
		case 4: {
			TriangleStripAttribute *object = triaStripArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *object = triaFanArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				break;
		case 10: {
			SphereAttribute *object = sphereArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 11: {
			CubeAttribute *object = cubeArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *object = cubeRoundArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 13: {
			ConeAttribute *object = coneArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 14: {
			CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 15: {
			PyramidAttribute *object = pyrArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 17: {
			TorusAttribute *object = torusArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 18: {
			PictureAttribute *object = pictureArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionY += object->vertexArray[positionVertexChoice[i]].y;
			}
			positionY = positionY / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].y = positionY;
			}
		}
				 break;
		default:
			break;
		}
	}
}
//hàm chuyển các điểm về cùng 1 vị trí Z trên trục Z
void MakeVertexSameZ(itemChoice item, vector<int> positionVertexChoice,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberVertexChoice = positionVertexChoice.size();
	float positionZ = 0.0;
	if (numberVertexChoice > 0) {
		switch (item.object)
		{
		case 3: {
			TriangleAttribute *object = triangleArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				break;
		case 4: {
			TriangleStripAttribute *object = triaStripArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *object = triaFanArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				break;
		case 10: {
			SphereAttribute *object = sphereArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 11: {
			CubeAttribute *object = cubeArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *object = cubeRoundArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 13: {
			ConeAttribute *object = coneArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 14: {
			CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 15: {
			PyramidAttribute *object = pyrArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 17: {
			TorusAttribute *object = torusArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 18: {
			PictureAttribute *object = pictureArray.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			for (int i = 0; i < numberVertexChoice; i++) {
				positionZ += object->vertexArray[positionVertexChoice[i]].z;
			}
			positionZ = positionZ / numberVertexChoice;
			for (int i = 0; i < numberVertexChoice; i++) {
				object->vertexArray[positionVertexChoice[i]].z = positionZ;
			}
		}
				 break;
		default:
			break;
		}
	}
}