#include "SuppostForApp2.h"

//hàm tải ảnh
int LoadImage(char *filename)
{
	ILboolean success;
	ILuint image;

	ilGenImages(1, &image); /* Tạo một tên hình ảnh */
	ilBindImage(image); /* Liên kết 1 tên hình ảnh */
	success = ilLoadImage(filename); /* tải hình ảnh từ filename bằng evil */

	if (success) /* nếu không có lỗi xảy ra: */
	{
		/* Chuyển đổi mọi thành phần màu thành byte chưa ký. Nếu hình ảnh của bạn chứa kênh alpha, bạn có thể thay thế IL_RGB bằng IL_RGBA */
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (!success)
		{
			return -1;
		}
	}
	else
		return -1;

	return image;
}
//load các kết cấu và gắn tên liên kết cho chúng
void loadTextureForObject(itemTextureObject &itemTexture) {
	//đếm số lượng của cả tệp tin trong thư mục
	namespace fs = std::experimental::filesystem;

	vector<string> pathOfPicture;
	GLuint image;
	int numberPicture = 0;
	char charArray[50];
	//lấy số lượng và tên các đường dẫn cho hình ảnh nằm trong tệp D://picture/texture
	for (auto & p : fs::directory_iterator("D://picture/texture")) {
		pathOfPicture.push_back(p.path().string());
		numberPicture++;
	}

	//lấy số lượng tên liên kết bằng số lượng hình ảnh(lưu lại tên kết cấu đầu tiên vào biến)
	glGenTextures(numberPicture, &itemTexture.startNameTexture);
	itemTexture.numberTexture = numberPicture;
	GLuint nameTexture;
	//tải kết cấu vào và gắn tên liên kết cho chúng
	for (int i = 0; i < numberPicture; i++) {
		strcpy_s(charArray, 50, pathOfPicture.at(i).c_str());
		image = LoadImage(charArray);
		if (image != -1) {
			nameTexture = itemTexture.startNameTexture + i;
			glBindTexture(GL_TEXTURE_2D, nameTexture);
			//hàm dưới xác định màu của kết cấu sẽ thay thế màu của của object(vertex) phía sau luôn
			//mặc định là màu đỉnh sẽ nhân với màu kết cầu
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		}
	}
	/* Bởi vì chúng tôi đã sao chép dữ liệu hình ảnh vào dữ liệu kết cấu, chúng tôi có thể phát hành bộ nhớ được sử dụng bởi hình ảnh. */
	ilDeleteImages(1, &image);
}


//vẽ đường trắng bao ngoài để biết hình đang được chọn
void DrawTrianglesLine(TriangleAttribute *tria) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; i++) {
		v = tria->getVertexAtIndex(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawTriangleStripLine(TriangleStripAttribute *triaStrip) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	int numberVertex = triaStrip->vertexArray.size();
	for (int i = 0; i < numberVertex; i++) {
		v = triaStrip->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < numberVertex; i+=2) {
		v = triaStrip->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (int i = 1; i < numberVertex; i += 2) {
		v = triaStrip->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawTriangleFanLine(TriangleFanAttribute *triaFan) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	int numberVertex = triaFan->vertexArray.size();
	for (int i = 0; i < numberVertex; i++) {
		v = triaFan->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glBegin(GL_LINES);
	for (int i = 2; i < numberVertex - 1; i++) {
		v = triaFan->vertexArray.at(0);
		glVertex3f(v.x, v.y, v.z);
		v = triaFan->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawSphereLine(SphereAttribute *sphere,int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int numberVertex, minusLatitude = 0, minusLongitude = 0,
		numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	glLineWidth(4.0);
	numberVertex = sphere->vertexArray.size();
	minusLatitude = (360 - sphere->degreeLatitudeLimit) * (sphere->numberLatitude / 360.0);
	minusLongitude = (360 - sphere->degreeLongitudeLimit) * (sphere->numberLongitude / 360.0);
	//vẽ các đường kẻ ngang của hình
	for (int i = 0; i < sphere->numberLatitude - minusLatitude; i++) {
		//kiểm tra xem có chọn trúng hàng không
		for (int m = 0; m < numberChoiceRowOrColumn; m++) {
			if (positionChoiceRowOrColumn.at(m).positionRow == i) {
				isChoice = true;
			}
		}
		if (modelEditStyle == 2 && isChoice) {
			glColor3f(0.8f, 1.0f, 0.6f);
			glBegin(GL_LINE_STRIP);
			for (int j = minusLongitude; j < sphere->numberLongitude; j++) {
				v0 = sphere->vertexArray.at(i*sphere->numberLongitude + j);
				glVertex3f(v0.x, v0.y, v0.z);
				//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
				if (j == sphere->numberLongitude - 1) {
					v0 = sphere->vertexArray.at(i*sphere->numberLongitude);
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			glEnd();
			glColor3f(0.6f, 0.6f, 0.6f);
			isChoice = false;
		}
		else
		{
			glBegin(GL_LINE_STRIP);
			for (int j = minusLongitude; j < sphere->numberLongitude; j++) {
				v0 = sphere->vertexArray.at(i*sphere->numberLongitude + j);
				glVertex3f(v0.x, v0.y, v0.z);
				//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
				if (j == sphere->numberLongitude - 1) {
					v0 = sphere->vertexArray.at(i*sphere->numberLongitude);
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			glEnd();
		}
	}
	//vẽ các đường kẻ dọc của hình
	for (int j = minusLongitude; j < sphere->numberLongitude; j++) {
		//kiểm tra xem có chọn trúng cột không
		for (int m = 0; m < numberChoiceRowOrColumn; m++) {
			if (positionChoiceRowOrColumn.at(m).positionColumn == j) {
				isChoice = true;
			}
		}
		if (modelEditStyle == 2 && isChoice) {
			glColor3f(0.8f, 1.0f, 0.6f);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < sphere->numberLatitude - minusLatitude; i++) {
				v0 = sphere->vertexArray.at(i*sphere->numberLongitude + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
			glColor3f(0.6f, 0.6f, 0.6f);
			isChoice = false;
		}
		else
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < sphere->numberLatitude - minusLatitude; i++) {
				v0 = sphere->vertexArray.at(i*sphere->numberLongitude + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawCubeLine(CubeAttribute *cube, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	glLineWidth(3.0);
	int offset1, offset2, offset3, offset4, offset5, numberVertexInRow,
		numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	point v0;
	numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
	// vẽ line cho hình bao quanh hình cầu
	for (int i = 0; i < cube->numberVertexInAxisY; i++) {
		//kiểm tra xem có chọn trúng hàng không
		for (int m = 0; m < numberChoiceRowOrColumn; m++) {
			if (positionChoiceRowOrColumn.at(m).positionRow == i) {
				isChoice = true;
			}
		}
		if (modelEditStyle == 2 && isChoice) {
			glColor3f(0.8f, 1.0f, 0.6f);
			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < numberVertexInRow; j++) {
				v0 = cube->vertexArray.at(i*numberVertexInRow + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
			glColor3f(0.6f, 0.6f, 0.6f);
			isChoice = false;
		}
		else
		{
			glBegin(GL_LINE_LOOP);
			for (int j = 0; j < numberVertexInRow; j++) {
				v0 = cube->vertexArray.at(i*numberVertexInRow + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
		}
	}
	//vẽ các đường thẳng dọc ở các mặt bên
	for (int j = 0; j < numberVertexInRow; j++) {
		//kiểm tra xem có chọn trúng hàng không
		for (int m = 0; m < numberChoiceRowOrColumn; m++) {
			if (positionChoiceRowOrColumn.at(m).positionColumn == j ||
				positionChoiceRowOrColumn.at(m).positionColumnOpposite == j) {
				isChoice = true;
			}
		}
		if (modelEditStyle == 2 && isChoice) {
			glColor3f(0.8f, 1.0f, 0.6f);
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < cube->numberVertexInAxisY; i++) {
				v0 = cube->vertexArray.at(i*numberVertexInRow + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
			glColor3f(0.6f, 0.6f, 0.6f);
			isChoice = false;
		}
		else
		{
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < cube->numberVertexInAxisY; i++) {
				v0 = cube->vertexArray.at(i*numberVertexInRow + j);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			glEnd();
		}
	}
	
	//các offset cần dùng nhiều
	offset1 = cube->numberVertexInAxisX - 1;
	//điểm đầu tiên của vertexUp(tức là cụm các đỉnh nằm phía trong)
	offset2 = numberVertexInRow*cube->numberVertexInAxisY;
	//điểm đầu tiên của vertexDown(tức là cụm các đỉnh nằm phía trong)
	offset4 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
	//vị trí đầu tiên của vòng đỉnh ngoài phía dưới cùng
	offset5 = (cube->numberVertexInAxisY - 1)*numberVertexInRow;

	//vẽ các đường thẳng từ các điểm nằm trên trục X(nếu số điểm trên trục X lớn hơn 2(các điểm ở rìa ngoài đã được nối))
	if (cube->numberVertexInAxisX > 2) {
		offset3 = cube->numberVertexInAxisX * 2 + cube->numberVertexInAxisZ - 3;
		for (int i = 1; i < offset1; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == i) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
			}
			//vẽ các điểm nằm ở mặt trên
			glBegin(GL_LINE_STRIP);
			//vẽ điểm nẳm ở phía trước
			v0 = cube->vertexArray.at(i);
			glVertex3f(v0.x, v0.y, v0.z);
			//nếu numberVertexInAxisZ>2 nghĩa là có điểm ở trong vòng tròn trong
			if (cube->numberVertexInAxisZ > 2) {
				for (int m = 0; m < cube->numberVertexInAxisZ - 2; m++) {
					v0 = cube->vertexArray.at(offset2+m*(cube->numberVertexInAxisX-2)+(i-1));
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			//vẽ điểm nằm ở phía sau
			v0 = cube->vertexArray.at(offset3-i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();

			//vẽ các điểm nằm ở mặt dưới
			glBegin(GL_LINE_STRIP);
			//vẽ điểm nẳm ở phía trước
			v0 = cube->vertexArray.at(offset5 + i);
			glVertex3f(v0.x, v0.y, v0.z);
			//nếu numberVertexInAxisZ>2 nghĩa là có điểm ở trong vòng tròn trong
			if (cube->numberVertexInAxisZ > 2) {
				for (int m = 0; m < cube->numberVertexInAxisZ - 2; m++) {
					v0 = cube->vertexArray.at(offset4 + m*(cube->numberVertexInAxisX - 2) + (i - 1));
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			//vẽ điểm nằm ở phía sau
			v0 = cube->vertexArray.at(offset5 + offset3 - i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();

			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
		}
	}
	//vẽ các đường thẳng từ các điểm nằm trên trục Z(nếu số điểm trên trục Z lớn hơn 2(các điểm ở rìa ngoài đã được nối))
	if (cube->numberVertexInAxisZ > 2) {
		for (int i = 1; i < cube->numberVertexInAxisZ - 1; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == i + offset1) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
			}
			//vẽ các điểm nằm ở mặt trên
			glBegin(GL_LINE_STRIP);
			//vẽ điểm ngoài cùng phía bên phải
			v0 = cube->vertexArray.at(offset1 + i);
			glVertex3f(v0.x, v0.y, v0.z);
			//nếu numberVertexInAxisX>2 nghĩa là có điểm ở trong vòng tròn trong
			if (cube->numberVertexInAxisX > 2) {
				for (int m = 0; m < cube->numberVertexInAxisX - 2; m++) {
					v0 = cube->vertexArray.at(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + m);
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			//vẽ điểm ngoài cùng phía bên trái
			v0 = cube->vertexArray.at(numberVertexInRow - i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();

			//vẽ các điểm nằm ở mặt dưới
			glBegin(GL_LINE_STRIP);
			//vẽ điểm ngoài cùng phía bên phải
			v0 = cube->vertexArray.at(offset5 + offset1 + i);
			glVertex3f(v0.x, v0.y, v0.z);
			//nếu numberVertexInAxisX>2 nghĩa là có điểm ở trong vòng tròn trong
			if (cube->numberVertexInAxisX > 2) {
				for (int m = 0; m < cube->numberVertexInAxisX - 2; m++) {
					v0 = cube->vertexArray.at(offset4 + (i - 1)*(cube->numberVertexInAxisX - 2) + m);
					glVertex3f(v0.x, v0.y, v0.z);
				}
			}
			//vẽ điểm ngoài cùng phía bên trái
			v0 = cube->vertexArray.at(offset5 + numberVertexInRow - i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawCubeRoundLine(CubeRoundAttribute *cube) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int numberVertex;
	glLineWidth(4.0);
	numberVertex = cube->vertexArray.size();
	//vẽ các đường kẻ ngang của hình
	for (int i = 0; i < cube->numberLatitude; i++) {
		glBegin(GL_LINE_STRIP);
		for (int j = 0; j < cube->numberLongitude; j++) {
			v0 = cube->vertexArray.at(i*cube->numberLongitude + j);
			glVertex3f(v0.x, v0.y, v0.z);
		}
		glEnd();
	}
	//vẽ các đường kẻ dọc của hình
	for (int j = 0; j < cube->numberLongitude; j++) {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < cube->numberLatitude ; i++) {
			v0 = cube->vertexArray.at(i*cube->numberLongitude + j);
			glVertex3f(v0.x, v0.y, v0.z);
		}
		glEnd();
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawConeLine(ConeAttribute *cone, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int minusLatitude=0, minusLongitude=0,
		numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	glLineWidth(3.0);
	if (!cone->vertexArray.empty()) {
		minusLatitude = (360 - cone->degreeLatitudeLimit) * (cone->numberLatitude / 360.0);
		minusLongitude = (360 - cone->degreeLongitudeLimit) * (cone->numberLongitude / 360.0);
		
		//vẽ các đường kẻ ngang của hình
		for (int i = 0; i < cone->numberLatitude - minusLatitude; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionRow == i) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cone->numberLongitude; j++) {
					v0 = cone->vertexArray.at(i*cone->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cone->numberLongitude - 1) {
						v0 = cone->vertexArray.at(i*cone->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cone->numberLongitude; j++) {
					v0 = cone->vertexArray.at(i*cone->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cone->numberLongitude - 1) {
						v0 = cone->vertexArray.at(i*cone->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
			}
		}
		//vẽ các đường kẻ dọc của hình
		for (int j = minusLongitude; j < cone->numberLongitude; j++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == j) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cone->numberLatitude - minusLatitude; i++) {
					v0 = cone->vertexArray.at(i*cone->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cone->numberLatitude - minusLatitude; i++) {
					v0 = cone->vertexArray.at(i*cone->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
			}
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawCylinderLine(CylinderAttribute *cylinder, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int minusLatitude = 0, minusLongitude = 0,
		numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	glLineWidth(3.0);
	if (!cylinder->vertexArray.empty()) {
		minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
		minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);
		
		//vẽ các đường kẻ ngang của hình
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionRow == i) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cylinder->numberLongitude - 1) {
						v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cylinder->numberLongitude - 1) {
						v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
			}
		}
		//vẽ các đường kẻ dọc của hình
		for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == j) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
			}
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawPyramidLine(PyramidAttribute *pyr) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	//mảng chứa các giá trị đỉnh theo thứ tự của pyramid
	int vertexArrayPyr[][3]{
		{ 0,1,2 },{ 0,2,3 },{ 0,3,4 },{ 0,4,1 }
	};
	point v0, v1, v2;
	glLineWidth(3.0);
	//vẽ từng mặt cube
	for (int i = 0; i < 6; i++) {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 5; i++) {
			if (i < 4) {
				v0 = pyr->getVertexAtIndex(vertexArrayPyr[i][0]);
				v1 = pyr->getVertexAtIndex(vertexArrayPyr[i][1]);
				v2 = pyr->getVertexAtIndex(vertexArrayPyr[i][2]);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			else
			{
				//vẽ mặt đáy
				v0 = pyr->getVertexAtIndex(1);
				v1 = pyr->getVertexAtIndex(2);
				v2 = pyr->getVertexAtIndex(3);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				v1 = pyr->getVertexAtIndex(4);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
		}
		glEnd();
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawEmptyCylinderLine(EmptyCylinderAttribute *cylinder, int modelEditStyle, vector<PositionRowOrColumn> positionChoiceRowOrColumn) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int minusLatitude = 0, minusLongitude = 0,
		numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	glLineWidth(3.0);
	if (!cylinder->vertexArray.empty()) {
		minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
		minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);
		
		//vẽ các đường kẻ ngang của hình
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionRow == i) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cylinder->numberLongitude - 1) {
						v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
					//nếu là đỉnh cuối cùng thì nối với đỉnh đầu tiên
					if (j == cylinder->numberLongitude - 1) {
						v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude);
						glVertex3f(v0.x, v0.y, v0.z);
					}
				}
				glEnd();
			}
		}
		//vẽ các đường kẻ dọc của hình
		for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == j) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
					v0 = cylinder->vertexArray.at(i*cylinder->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
			}
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawTorusLine(TorusAttribute *torus) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v;
	glLineWidth(3.0);
	int numberVertex = torus->vertexArray.size();
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < numberVertex; i++) {
		v = torus->vertexArray.at(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();

	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawPicturesLine(PictureAttribute *picture) {
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		v = picture->vertexArray[i];
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}
void DrawObjectCustom0Line(ObjectCustom0Attribute *object, int modelEditStyle,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn) {

	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	point v0;
	int numberChoiceRowOrColumn = positionChoiceRowOrColumn.size();
	bool isChoice = false;
	glLineWidth(3.0);
	if (!object->vertexArray.empty()) {
		//vẽ các đường kẻ ngang của hình
		for (int i = 0; i < object->numberLatitude; i++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionRow == i) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int j = 0; j < object->numberLongitude; j++) {
					v0 = object->vertexArray.at(i*object->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int j = 0; j < object->numberLongitude; j++) {
					v0 = object->vertexArray.at(i*object->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
			}
		}
		//vẽ các đường kẻ dọc của hình
		for (int j = 0; j < object->numberLongitude; j++) {
			//kiểm tra xem có chọn trúng hàng không
			for (int m = 0; m < numberChoiceRowOrColumn; m++) {
				if (positionChoiceRowOrColumn.at(m).positionColumn == j) {
					isChoice = true;
				}
			}
			if (modelEditStyle == 2 && isChoice) {
				glColor3f(0.8f, 1.0f, 0.6f);
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < object->numberLatitude; i++) {
					v0 = object->vertexArray.at(i*object->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
				glColor3f(0.6f, 0.6f, 0.6f);
				isChoice = false;
			}
			else
			{
				glBegin(GL_LINE_STRIP);
				for (int i = 0; i < object->numberLatitude; i++) {
					v0 = object->vertexArray.at(i*object->numberLongitude + j);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				glEnd();
			}
		}
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}

//vẽ các nét chấm trắng trên hình để chọn vertex
void DrawTrianglesPoint(TriangleAttribute *tria, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v;
	if (mode == GL_SELECT) {
		for (int i = 0; i < 3; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = tria->getVertexAtIndex(i);
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;

		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++) {
			//kiểm tra xem phần tử này có được chọn k0
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v = tria->getVertexAtIndex(i);
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawTriangleStripPoint(TriangleStripAttribute *triaStrip, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v;
	int numberVertex = triaStrip->vertexArray.size();
	if (mode == GL_SELECT) {
		for (int i = 0; i < numberVertex; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = triaStrip->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glBegin(GL_POINTS);
		for (int i = 0; i < numberVertex; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v = triaStrip->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawTriangleFanPoint(TriangleFanAttribute *triaFan, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v;
	int numberVertex = triaFan->vertexArray.size();
	if (mode == GL_SELECT) {
		for (int i = 0; i < numberVertex; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = triaFan->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glBegin(GL_POINTS);
		for (int i = 0; i < numberVertex; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v = triaFan->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawSpherePoint(SphereAttribute *sphere, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v;
	int offset, minusLatitude=0, minusLongitude=0;
	minusLatitude = (360 - sphere->degreeLatitudeLimit) * (sphere->numberLatitude / 360.0);
	minusLongitude = (360 - sphere->degreeLongitudeLimit) * (sphere->numberLongitude / 360.0);

	if (mode == GL_SELECT) {
		for (int i = 0; i < sphere->numberLatitude - minusLatitude; i++) {
			for (int k = minusLongitude; k < sphere->numberLongitude; k++) {
				offset = i*sphere->numberLongitude + k;
				glLoadName(offset);
				glBegin(GL_POINTS);
				v = sphere->vertexArray.at(offset);
				glVertex3f(v.x, v.y, v.z);
				glEnd();
			}
		}
	}
	else
	{
		glColor3f(0.0f, 0.2f, 0.8f);
		glDisable(GL_LIGHTING);
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glBegin(GL_POINTS);
		for (int i = 0; i < sphere->numberLatitude - minusLatitude; i++) {
			for (int k = minusLongitude; k < sphere->numberLongitude; k++) {
				offset = i*sphere->numberLongitude + k;
				for (int j = 0; j < vertexChoiceSize; j++) {
					if (modelVertexChoice.at(j) == offset) {
						glColor3f(1.0f, 1.0f, 0.4f);
						isChangeColor = true;
						break;
					}
				}
				v = sphere->vertexArray.at(offset);
				glVertex3f(v.x, v.y, v.z);
				if (isChangeColor) {
					glColor3f(0.0f, 0.2f, 0.8f);
					isChangeColor = false;
				}
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawCubePoint(CubeAttribute *cube, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v0;
	int numberVertex = cube->vertexArray.size();

	if (mode == GL_SELECT) {
		for (int i = 0; i < numberVertex; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v0 = cube->vertexArray.at(i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < numberVertex; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(1.0f, 1.0f, 0.4f);
					isChangeColor = true;
					break;
				}
			}
			v0 = cube->vertexArray.at(i);
			glVertex3f(v0.x, v0.y, v0.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawCubeRoundPoint(CubeRoundAttribute *cube, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v;
	int numberVertex = cube->vertexArray.size();
	
	if (mode == GL_SELECT) {
		for (int i = 0; i < numberVertex; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = cube->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glColor3f(0.0f, 0.2f, 0.8f);
		glDisable(GL_LIGHTING);
		glBegin(GL_POINTS);
		for (int i = 0; i < numberVertex; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(1.0f, 1.0f, 0.4f);
					isChangeColor = true;
					break;
				}
			}
			v = cube->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawConePoint(ConeAttribute *cone, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v0;
	int offset, minusLatitude=0, minusLongitude=0;
	minusLatitude = (360 - cone->degreeLatitudeLimit) * (cone->numberLatitude / 360.0);
	minusLongitude = (360 - cone->degreeLongitudeLimit) * (cone->numberLongitude / 360.0);

	if (mode == GL_SELECT) {
		for (int i = 0; i < cone->numberLatitude - minusLatitude; i++) {
			offset = i * cone->numberLongitude;
			for (int j = minusLongitude; j < cone->numberLongitude; j++) {
				glLoadName(offset + j);
				v0 = cone->vertexArray.at(offset + j);
				glBegin(GL_POINTS);
				glVertex3f(v0.x, v0.y, v0.z);
				glEnd();
			}
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < cone->numberLatitude - minusLatitude; i++) {
			offset = i * cone->numberLongitude;
			for (int j = minusLongitude; j < cone->numberLongitude; j++) {
				for (int k = 0; k < vertexChoiceSize; k++) {
					if (modelVertexChoice.at(k) == offset + j) {
						glColor3f(1.0f, 1.0f, 0.4f);
						isChangeColor = true;
						break;
					}
				}
				v0 = cone->vertexArray.at(offset + j);
				glVertex3f(v0.x, v0.y, v0.z);
				if (isChangeColor) {
					glColor3f(0.0f, 0.2f, 0.8f);
					isChangeColor = false;
				}
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawCylinderPoint(CylinderAttribute *cylinder, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v0;
	int offset, minusLatitude=0, minusLongitude=0;

	minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
	minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);

	if (mode == GL_SELECT) {
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			offset = i * cylinder->numberLongitude;
			for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
				glLoadName(offset + j);
				v0 = cylinder->vertexArray.at(offset + j);
				glBegin(GL_POINTS);
				glVertex3f(v0.x, v0.y, v0.z);
				glEnd();
			}
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			offset = i * cylinder->numberLongitude;
			for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
				for (int k = 0; k < vertexChoiceSize; k++) {
					if (modelVertexChoice.at(k) == offset + j) {
						glColor3f(1.0f, 1.0f, 0.4f);
						isChangeColor = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offset + j);
				glVertex3f(v0.x, v0.y, v0.z);
				if (isChangeColor) {
					glColor3f(0.0f, 0.2f, 0.8f);
					isChangeColor = false;
				}
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawPyramidPoint(PyramidAttribute *pyr, GLenum mode, std::vector<int> modelVertexChoice) {
	point v0;
	glPointSize(8.0);
	if (mode == GL_SELECT) {
		for (int i = 0; i < 5; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v0 = pyr->getVertexAtIndex(i);
			glVertex3f(v0.x, v0.y, v0.z);
			glEnd();
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glColor3f(0.0f, 0.2f, 0.8f);
		glDisable(GL_LIGHTING);
		glBegin(GL_POINTS);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v0 = pyr->getVertexAtIndex(i);
			glVertex3f(v0.x, v0.y, v0.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawEmptyCylinderPoint(EmptyCylinderAttribute *cylinder, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v0;
	int offset, minusLatitude=0, minusLongitude=0;

	minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
	minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);

	if (mode == GL_SELECT) {
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			offset = i * cylinder->numberLongitude;
			for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
				glLoadName(offset + j);
				v0 = cylinder->vertexArray.at(offset + j);
				glBegin(GL_POINTS);
				glVertex3f(v0.x, v0.y, v0.z);
				glEnd();
			}
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < cylinder->numberLatitude - minusLatitude; i++) {
			offset = i * cylinder->numberLongitude;
			for (int j = minusLongitude; j < cylinder->numberLongitude; j++) {
				for (int k = 0; k < vertexChoiceSize; k++) {
					if (modelVertexChoice.at(k) == offset + j) {
						glColor3f(1.0f, 1.0f, 0.4f);
						isChangeColor = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offset + j);
				glVertex3f(v0.x, v0.y, v0.z);
				if (isChangeColor) {
					glColor3f(0.0f, 0.2f, 0.8f);
					isChangeColor = false;
				}
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawTorusPoint(TorusAttribute *torus, GLenum mode, std::vector<int> modelVertexChoice) {
	point v;
	glPointSize(8.0);
	int numberVertex = torus->vertexArray.size();
	if (mode == GL_SELECT) {
		for (int i = 0; i < numberVertex; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = torus->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < numberVertex; i++) {
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v = torus->vertexArray.at(i);
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	
	glPointSize(1.0);
}
void DrawPicturesPoint(PictureAttribute *picture, GLenum mode, std::vector<int> modelVertexChoice) {
	point v;
	glPointSize(8.0);
	if (mode == GL_SELECT) {
		for (int i = 0; i < 4; i++) {
			glLoadName(i);
			glBegin(GL_POINTS);
			v = picture->vertexArray[i];
			glVertex3f(v.x, v.y, v.z);
			glEnd();
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < 4; i++) {
			//kiểm tra xem phần tử này có được chọn k0
			for (int j = 0; j < vertexChoiceSize; j++) {
				if (modelVertexChoice.at(j) == i) {
					glColor3f(0.8f, 1.0f, 0.6f);
					isChangeColor = true;
					break;
				}
			}
			v = picture->vertexArray[i];
			glVertex3f(v.x, v.y, v.z);
			if (isChangeColor) {
				glColor3f(0.0f, 0.2f, 0.8f);
				isChangeColor = false;
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}
void DrawObjectCustom0Point(ObjectCustom0Attribute *object, GLenum mode, std::vector<int> modelVertexChoice) {
	glPointSize(8.0);
	point v0;
	int offset;

	if (mode == GL_SELECT) {
		for (int i = 0; i < object->numberLatitude; i++) {
			offset = i * object->numberLongitude;
			for (int j = 0; j < object->numberLongitude; j++) {
				glLoadName(offset + j);
				v0 = object->vertexArray.at(offset + j);
				glBegin(GL_POINTS);
				glVertex3f(v0.x, v0.y, v0.z);
				glEnd();
			}
		}
	}
	else
	{
		int vertexChoiceSize = modelVertexChoice.size();
		bool isChangeColor = false;
		glDisable(GL_LIGHTING);
		glColor3f(0.0f, 0.2f, 0.8f);
		glBegin(GL_POINTS);
		for (int i = 0; i < object->numberLatitude; i++) {
			offset = i * object->numberLongitude;
			for (int j = 0; j < object->numberLongitude; j++) {
				for (int k = 0; k < vertexChoiceSize; k++) {
					if (modelVertexChoice.at(k) == offset + j) {
						glColor3f(1.0f, 1.0f, 0.4f);
						isChangeColor = true;
						break;
					}
				}
				v0 = object->vertexArray.at(offset + j);
				glVertex3f(v0.x, v0.y, v0.z);
				if (isChangeColor) {
					glColor3f(0.0f, 0.2f, 0.8f);
					isChangeColor = false;
				}
			}
		}
		glEnd();
		glEnable(GL_LIGHTING);
	}
	glPointSize(1.0);
}

//vẽ các mặt tam giác để chọn mặt cần chỉnh sửa của hình
/* Mà triangle thì khỏi cần vì nó chỉ có 1 mặt tam giác,nếu chọn 1 mặt thì chẳng bằng chọn 
void DrawTrianglesFace(TriangleAttribute *tria) {
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.8, 0.8);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; i++) {
		v = tria->getVertexAtIndex(i);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}*/
void DrawTriangleStripFace(TriangleStripAttribute *triaStrip, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0,v1,v2,normal;
	int numberFace = triaStrip->vertexArray.size() - 2, numberFacesChoice = indexesFaceChoice.size();
	bool isDraw = false;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < numberFace; i++) {
		//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
		//nếu có thì bật màu,không thì thôi
		for (int k = 0; k < numberFacesChoice; k++) {
			if (indexesFaceChoice.at(k) == i) {
				isDraw = true;
				break;
			}
		}
		v0 = triaStrip->vertexArray.at(i);
		v1 = triaStrip->vertexArray.at(i + 1);
		v2 = triaStrip->vertexArray.at(i + 2);
		normal = triaStrip->vertexArray.at(i);
		glNormal3f(normal.x, normal.y, normal.z);
		if (isDraw) {
			glColor3f(0.6f, 0.6f, 0.6f);
			glVertex3f(v0.x, v0.y, v0.z);
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			isDraw = false;
			glColor3f(0.2f, 0.2f, 0.2f);
		}
		else
		{
			glVertex3f(v0.x, v0.y, v0.z);
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
		}
	}
	glEnd();
}
void DrawTriangleFanFace(TriangleFanAttribute *triaFan, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0=triaFan->vertexArray.at(0), v1, v2,normal;
	int numberFace = triaFan->vertexArray.size() - 1, numberFacesChoice = indexesFaceChoice.size();
	bool isDraw = false;

	glBegin(GL_TRIANGLES);
	for (int i = 1; i < numberFace; i++) {
		//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
		//nếu có thì bật màu,không thì thôi
		for (int k = 0; k < numberFacesChoice; k++) {
			if (indexesFaceChoice.at(k) == i) {
				isDraw = true;
				break;
			}
		}
		v1 = triaFan->vertexArray.at(i);
		v2 = triaFan->vertexArray.at(i + 1);
		normal = triaFan->normalVector.at(i);
		glNormal3f(normal.x, normal.y, normal.z);
		if (isDraw) {
			glColor3f(0.6f, 0.6f, 0.6f);
			glVertex3f(v0.x, v0.y, v0.z);
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			isDraw = false;
			glColor3f(0.2f, 0.2f, 0.2f);
		}
		else
		{
			glVertex3f(v0.x, v0.y, v0.z);
			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
		}
	}
	glEnd();
}

void DrawSphereFace(SphereAttribute *sphere, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2,normal0,normal1,normal2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow, minusLatitude=0, minusLongitude=0;
	bool isDraw = false;

	minusLatitude = (360 - sphere->degreeLatitudeLimit) * (sphere->numberLatitude / 360.0);
	minusLongitude = (360 - sphere->degreeLongitudeLimit) * (sphere->numberLongitude / 360.0);
	
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < sphere->numberLatitude - minusLatitude; i++) {
		offsetLast = (i - 1) * sphere->numberLongitude;
		offsetNow = i * sphere->numberLongitude;
		for (int j = minusLongitude+1; j < sphere->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = sphere->vertexArray.at(offsetLast + j - 1);
			v1 = sphere->vertexArray.at(offsetNow + j - 1);
			v2 = sphere->vertexArray.at(offsetLast + j);
			normal0 = sphere->normalVector.at(offsetLast + j - 1);
			normal1 = sphere->normalVector.at(offsetNow + j - 1);
			normal2 = sphere->normalVector.at(offsetLast + j);

			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);

			}
			offsetFace++;
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = sphere->vertexArray.at(offsetNow + j);
			normal0 = sphere->normalVector.at(offsetNow + j);
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
			//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
			if (j == sphere->numberLongitude - 1) {
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = sphere->vertexArray.at(offsetLast + j);
				v1 = sphere->vertexArray.at(offsetNow + j);
				v2 = sphere->vertexArray.at(offsetLast);
				normal0 = sphere->normalVector.at(offsetLast + j);
				normal1 = sphere->normalVector.at(offsetNow + j);
				normal2 = sphere->normalVector.at(offsetLast);

				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);

				}
				offsetFace++;
				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = sphere->vertexArray.at(offsetNow);
				normal0 = sphere->normalVector.at(offsetNow);
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				offsetFace++;
			}
		}
	}
	glEnd();
}
void DrawCubeFace(CubeAttribute *cube, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2,normal;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offset1, offset2, offset3, numberVertexInRow, offsetNormal = 0;
	bool isDraw = false;

	numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
	glBegin(GL_TRIANGLES);
	// vẽ mặt cho hình bao quanh hình vuông
	for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
		offset1 = i * numberVertexInRow;
		offset2 = (i + 1) * numberVertexInRow;
		for (int j = 1; j < numberVertexInRow; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cube->vertexArray.at(offset1 + j - 1);
			v1 = cube->vertexArray.at(offset2 + j - 1);
			v2 = cube->vertexArray.at(offset1 + j);
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cube->vertexArray.at(offset2 + j);
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//nếu là cặp đỉnh cuối cùng thì vẽ nối với cặp đỉnh đầu tiên
			if (j == numberVertexInRow - 1) {
				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v1 = cube->vertexArray.at(offset1);
				normal = cube->normalVector.at(offsetNormal);
				glNormal3f(normal.x, normal.y, normal.z);
				offsetNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v1.x, v1.y, v1.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glVertex3f(v2.x, v2.y, v2.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v1.x, v1.y, v1.z);
				}
				offsetFace++;

				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v2 = cube->vertexArray.at(offset2);
				normal = cube->normalVector.at(offsetNormal);
				glNormal3f(normal.x, normal.y, normal.z);
				offsetNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v2.x, v2.y, v2.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glVertex3f(v1.x, v1.y, v1.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glVertex3f(v2.x, v2.y, v2.z);
				}
				offsetFace++;
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

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

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

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
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

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
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

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			normal = cube->normalVector.at(offsetNormal);
			glNormal3f(normal.x, normal.y, normal.z);
			offsetNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;
		}
	}
	glEnd();

	glLineWidth(1.0);
}
//chưa có normal********
void DrawCubeRoundFace(CubeRoundAttribute *cube, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow;
	bool isDraw = false;

	glBegin(GL_TRIANGLES);
	for (int i = 1; i < cube->numberLatitude ; i++) {
		offsetLast = (i - 1) * cube->numberLongitude;
		offsetNow = i * cube->numberLongitude;
		for (int j = 1; j < cube->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cube->vertexArray.at(offsetLast + j - 1);
			v1 = cube->vertexArray.at(offsetNow + j - 1);
			v2 = cube->vertexArray.at(offsetLast + j);
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cube->vertexArray.at(offsetNow + j);
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
		}
	}
	glEnd();
}
void DrawConeFace(ConeAttribute *cone, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2,normal0,normal1,normal2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow, minusLatitude=0, minusLongitude=0, positionNextNormal = 0;
	bool isDraw = false;

	minusLatitude = (360 - cone->degreeLatitudeLimit) * (cone->numberLatitude / 360.0);
	minusLongitude = (360 - cone->degreeLongitudeLimit) * (cone->numberLongitude / 360.0);
	
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < cone->numberLatitude - minusLatitude; i++) {
		offsetLast = (i - 1) * cone->numberLongitude;
		offsetNow = i * cone->numberLongitude;
		for (int j = minusLongitude + 1; j < cone->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cone->vertexArray.at(offsetLast + j - 1);
			v1 = cone->vertexArray.at(offsetNow + j - 1);
			v2 = cone->vertexArray.at(offsetLast + j);
			if (j == minusLongitude + 1) {
				normal0 = cone->normalVector.at(positionNextNormal);
				positionNextNormal++;
				normal1 = cone->normalVector.at(positionNextNormal);
				positionNextNormal++;
			}
			else
			{
				normal0 = cone->normalVector.at(positionNextNormal-2);
				normal1 = cone->normalVector.at(positionNextNormal-1);
			}
			normal2 = cone->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cone->vertexArray.at(offsetNow + j);
			normal0 = cone->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
			//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
			if (j == cone->numberLongitude - 1) {
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cone->vertexArray.at(offsetLast + j);
				v1 = cone->vertexArray.at(offsetNow + j);
				v2 = cone->vertexArray.at(offsetLast);
				if (j == minusLongitude + 1) {
					normal0 = cone->normalVector.at(positionNextNormal);
					positionNextNormal++;
					normal1 = cone->normalVector.at(positionNextNormal);
					positionNextNormal++;
				}
				else
				{
					normal0 = cone->normalVector.at(positionNextNormal - 2);
					normal1 = cone->normalVector.at(positionNextNormal - 1);
				}
				normal2 = cone->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
				}
				offsetFace++;

				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cone->vertexArray.at(offsetNow);
				normal0 = cone->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				offsetFace++;
			}
		}
	}
	glEnd();
}
void DrawCylinderFace(CylinderAttribute *cylinder, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2,normal0,normal1,normal2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow, minusLatitude=0, minusLongitude=0, positionNextNormal=0;
	bool isDraw = false;

	minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
	minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);
	
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
		offsetLast = (i - 1) * cylinder->numberLongitude;
		offsetNow = i * cylinder->numberLongitude;
		for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cylinder->vertexArray.at(offsetLast + j - 1);
			v1 = cylinder->vertexArray.at(offsetNow + j - 1);
			v2 = cylinder->vertexArray.at(offsetLast + j);
			if (j == minusLongitude + 1) {
				normal0 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				normal1 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
			}
			else
			{
				normal0 = cylinder->normalVector.at(positionNextNormal - 2);
				normal1 = cylinder->normalVector.at(positionNextNormal - 1);
			}
			normal2 = cylinder->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cylinder->vertexArray.at(offsetNow + j);
			normal0 = cylinder->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
			//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
			if (j == cylinder->numberLongitude - 1) {
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offsetLast + j);
				v1 = cylinder->vertexArray.at(offsetNow + j);
				v2 = cylinder->vertexArray.at(offsetLast);
				if (j == minusLongitude + 1) {
					normal0 = cylinder->normalVector.at(positionNextNormal);
					positionNextNormal++;
					normal1 = cylinder->normalVector.at(positionNextNormal);
					positionNextNormal++;
				}
				else
				{
					normal0 = cylinder->normalVector.at(positionNextNormal - 2);
					normal1 = cylinder->normalVector.at(positionNextNormal - 1);
				}
				normal2 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
				}
				offsetFace++;

				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offsetNow);
				normal0 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				offsetFace++;
			}
		}
	}
	glEnd();
}
/*void DrawPyramidFace(PyramidAttribute *pyr) {
	//mảng chứa các giá trị đỉnh theo thứ tự của pyramid
	int vertexArrayPyr[][3]{
		{ 0,1,2 },{ 0,2,3 },{ 0,3,4 },{ 0,4,1 }
	};
	point v0, v1, v2;
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);
	glColor3f(0.8, 0.8, 0.8);
	//vẽ từng mặt cube
	for (int i = 0; i < 6; i++) {
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 5; i++) {
			if (i < 4) {
				v0 = pyr->getVertexAtIndex(vertexArrayPyr[i][0]);
				v1 = pyr->getVertexAtIndex(vertexArrayPyr[i][1]);
				v2 = pyr->getVertexAtIndex(vertexArrayPyr[i][2]);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			else
			{
				//vẽ mặt đáy
				v0 = pyr->getVertexAtIndex(1);
				v1 = pyr->getVertexAtIndex(2);
				v2 = pyr->getVertexAtIndex(3);
				glVertex3f(v0.x, v0.y, v0.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v2.x, v2.y, v2.z);
				v1 = pyr->getVertexAtIndex(4);
				glVertex3f(v2.x, v2.y, v2.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
		}
		glEnd();
	}
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}*/
void DrawEmptyCylinderFace(EmptyCylinderAttribute *cylinder, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2,normal0,normal1,normal2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow, minusLatitude=0, minusLongitude=0, positionNextNormal=0;
	bool isDraw = false;

	minusLatitude = (360 - cylinder->degreeLatitudeLimit) * (cylinder->numberLatitude / 360.0);
	minusLongitude = (360 - cylinder->degreeLongitudeLimit) * (cylinder->numberLongitude / 360.0);
	
	glBegin(GL_TRIANGLES);
	for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
		offsetLast = (i - 1) * cylinder->numberLongitude;
		offsetNow = i * cylinder->numberLongitude;
		for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cylinder->vertexArray.at(offsetLast + j - 1);
			v1 = cylinder->vertexArray.at(offsetNow + j - 1);
			v2 = cylinder->vertexArray.at(offsetLast + j);
			if (j == minusLongitude + 1) {
				normal0 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				normal1 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
			}
			else
			{
				normal0 = cylinder->normalVector.at(positionNextNormal - 2);
				normal1 = cylinder->normalVector.at(positionNextNormal - 1);
			}
			normal2 = cylinder->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = cylinder->vertexArray.at(offsetNow + j);
			normal0 = cylinder->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
			//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
			if (j == cylinder->numberLongitude - 1) {
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offsetLast + j);
				v1 = cylinder->vertexArray.at(offsetNow + j);
				v2 = cylinder->vertexArray.at(offsetLast);
				if (j == minusLongitude + 1) {
					normal0 = cylinder->normalVector.at(positionNextNormal);
					positionNextNormal++;
					normal1 = cylinder->normalVector.at(positionNextNormal);
					positionNextNormal++;
				}
				else
				{
					normal0 = cylinder->normalVector.at(positionNextNormal - 2);
					normal1 = cylinder->normalVector.at(positionNextNormal - 1);
				}
				normal2 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
				}
				offsetFace++;

				//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
				//nếu có thì bật màu,không thì thôi
				for (int k = 0; k < numberFacesChoice; k++) {
					if (indexesFaceChoice.at(k) == offsetFace) {
						isDraw = true;
						break;
					}
				}
				v0 = cylinder->vertexArray.at(offsetNow);
				normal0 = cylinder->normalVector.at(positionNextNormal);
				positionNextNormal++;
				if (isDraw) {
					glColor3f(0.6f, 0.6f, 0.6f);
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
					isDraw = false;
					glColor3f(0.2f, 0.2f, 0.2f);
				}
				else
				{
					glNormal3f(normal1.x, normal1.y, normal1.z);
					glVertex3f(v1.x, v1.y, v1.z);
					glNormal3f(normal2.x, normal2.y, normal2.z);
					glVertex3f(v2.x, v2.y, v2.z);
					glNormal3f(normal0.x, normal0.y, normal0.z);
					glVertex3f(v0.x, v0.y, v0.z);
				}
				offsetFace++;
			}
		}
	}
	glEnd();
}
void DrawTorusFace(TorusAttribute *torus, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2, normal;
	int numberFace = torus->vertexArray.size() - 2, numberFacesChoice = indexesFaceChoice.size();
	bool isDraw = false;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < numberFace; i++) {
		//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
		//nếu có thì bật màu,không thì thôi
		for (int k = 0; k < numberFacesChoice; k++) {
			if (indexesFaceChoice.at(k) == i) {
				isDraw = true;
				break;
			}
		}
		v0 = torus->vertexArray.at(i);
		v1 = torus->vertexArray.at(i + 1);
		v2 = torus->vertexArray.at(i + 2);
		if (isDraw) {
			glColor3f(0.6f, 0.6f, 0.6f);
			normal = torus->normalVector.at(i);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v0.x, v0.y, v0.z);
			normal = torus->normalVector.at(i+1);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v1.x, v1.y, v1.z);
			normal = torus->normalVector.at(i+2);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v2.x, v2.y, v2.z);
			isDraw = false;
			glColor3f(0.2f, 0.2f, 0.2f);
		}
		else
		{
			normal = torus->normalVector.at(i);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v0.x, v0.y, v0.z);
			normal = torus->normalVector.at(i + 1);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v1.x, v1.y, v1.z);
			normal = torus->normalVector.at(i + 2);
			glNormal3f(normal.x, normal.y, normal.z);
			glVertex3f(v2.x, v2.y, v2.z);
		}
	}
	glEnd();
}
/*void DrawPicturesFace(PictureAttribute *picture) {
	glDisable(GL_LIGHTING);
	glColor3f(0.8, 0.8, 0.8);
	point v;
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		v = picture->vertexArray[i];
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glLineWidth(1.0);
	glEnable(GL_LIGHTING);
}*/
void DrawObjectCustom0Face(ObjectCustom0Attribute *object, vector<int> indexesFaceChoice) {
	glColor3f(0.2f, 0.2f, 0.2f);
	point v0, v1, v2, normal0, normal1, normal2;
	int numberFacesChoice = indexesFaceChoice.size(), offsetFace = 0,
		offsetLast, offsetNow, positionNextNormal = 0;
	bool isDraw = false;

	glBegin(GL_TRIANGLES);
	for (int i = 1; i < object->numberLatitude; i++) {
		offsetLast = (i - 1) * object->numberLongitude;
		offsetNow = i * object->numberLongitude;
		for (int j = 1; j < object->numberLongitude; j++) {
			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = object->vertexArray.at(offsetLast + j - 1);
			v1 = object->vertexArray.at(offsetNow + j - 1);
			v2 = object->vertexArray.at(offsetLast + j);
			if (j == 1) {
				normal0 = object->normalVector.at(positionNextNormal);
				positionNextNormal++;
				normal1 = object->normalVector.at(positionNextNormal);
				positionNextNormal++;
			}
			else
			{
				normal0 = object->normalVector.at(positionNextNormal - 2);
				normal1 = object->normalVector.at(positionNextNormal - 1);
			}
			normal2 = object->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
			}
			offsetFace++;

			//kiểm tra xem mặt này có nằm trong các mặt đang chọn không,
			//nếu có thì bật màu,không thì thôi
			for (int k = 0; k < numberFacesChoice; k++) {
				if (indexesFaceChoice.at(k) == offsetFace) {
					isDraw = true;
					break;
				}
			}
			v0 = object->vertexArray.at(offsetNow + j);
			normal0 = object->normalVector.at(positionNextNormal);
			positionNextNormal++;
			if (isDraw) {
				glColor3f(0.6f, 0.6f, 0.6f);
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
				isDraw = false;
				glColor3f(0.2f, 0.2f, 0.2f);
			}
			else
			{
				glNormal3f(normal1.x, normal1.y, normal1.z);
				glVertex3f(v1.x, v1.y, v1.z);
				glNormal3f(normal2.x, normal2.y, normal2.z);
				glVertex3f(v2.x, v2.y, v2.z);
				glNormal3f(normal0.x, normal0.y, normal0.z);
				glVertex3f(v0.x, v0.y, v0.z);
			}
			offsetFace++;
		}
	}
	glEnd();
}

//vẽ đường lưới,hay các điểm chọn,hay các mặt tam giác chọn cho hình đang được chọn
void drawObjectLineOrPoint(GLenum mode,int modelEditStyle,vector<itemChoice> itemsChoice,
	vector<int> positionVerticesChoice,vector<int> positionFacesChoice,vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	if (!itemsChoice.empty()) {
		int numberItemChoice = itemsChoice.size();
		for (int i = 0; i < numberItemChoice; i++) {
			itemChoice item = itemsChoice.at(i);
			switch (item.object)
			{
			case 3:
			{
				TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					//đối với kiểu chọn vật thì các đường kẻ chỉ đển hiển thị xem vật có được chọn hay 
					//không thôi.
					if (mode == GL_RENDER) {
						DrawTrianglesLine(tria);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawTrianglesPoint(tria, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawTrianglesLine(tria);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawTrianglesLine(tria);
				}
			}
			break;
			case 4:
			{
				TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawTriangleStripLine(triaStrip);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawTriangleStripPoint(triaStrip, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawTriangleStripLine(triaStrip);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawTriangleStripLine(triaStrip);
				}
				else
				{
					DrawTriangleStripFace(triaStrip, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawTriangleStripLine(triaStrip);
					}
				}
			}
			break;
			case 5:
			{
				TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawTriangleFanLine(triaFan);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawTriangleFanPoint(triaFan, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawTriangleFanLine(triaFan);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawTriangleFanLine(triaFan);
				}
				else
				{
					DrawTriangleFanFace(triaFan, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawTriangleFanLine(triaFan);
					}
				}
			}
			break;
			case 10:
			{
				SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawSphereLine(sphere, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawSpherePoint(sphere, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawSphereLine(sphere, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawSphereLine(sphere, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawSphereFace(sphere, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawSphereLine(sphere, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			case 11:
			{
				CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawCubeLine(cube, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawCubePoint(cube, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawCubeLine(cube, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawCubeLine(cube, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawCubeFace(cube, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawCubeLine(cube, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			case 12:
			{
				CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawCubeRoundLine(cube);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawCubeRoundPoint(cube, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawCubeRoundLine(cube);
					}
				}
				else if (modelEditStyle == 2) {
					DrawCubeRoundLine(cube);
				}
				else
				{
					DrawCubeRoundFace(cube, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawCubeRoundLine(cube);
					}
				}
			}
			break;
			case 13:
			{
				ConeAttribute *cone = coneArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawConeLine(cone, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1) {
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawConePoint(cone, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawConeLine(cone, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawConeLine(cone, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawConeFace(cone, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawConeLine(cone, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			case 14:
			{
				CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1) {
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawCylinderPoint(cylinder, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawCylinderFace(cylinder, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			case 15:
			{
				PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawPyramidLine(pyr);
					}
				}
				else if (modelEditStyle == 1)
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawPyramidPoint(pyr, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawPyramidLine(pyr);
					}
				}
				else if (modelEditStyle == 2) {
					DrawPyramidLine(pyr);
				}
			}
			break;
			case 16:
			{
				EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawEmptyCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1) {
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawEmptyCylinderPoint(cylinder, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawEmptyCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawEmptyCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawEmptyCylinderFace(cylinder, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawEmptyCylinderLine(cylinder, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			case 17:
			{
				TorusAttribute *torus = torusArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawTorusLine(torus);
					}
				}
				else if (modelEditStyle == 1) {
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawTorusPoint(torus, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawTorusLine(torus);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawTorusLine(torus);
				}
				else
				{
					DrawTorusFace(torus, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawTorusLine(torus);
					}
				}
			}
			break;
			case 18:
			{
				PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawPicturesLine(picture);
					}
				}
				else
				{
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawPicturesPoint(picture, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawPicturesLine(picture);
					}
				}
			}
			break;
			case 19:
			{
				ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
				if (modelEditStyle == 0) {
					if (mode == GL_RENDER) {
						DrawObjectCustom0Line(object, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 1) {
					//nếu là item đầu tiên được chọn thì mới vẽ vertex
					if (i == 0) {
						DrawObjectCustom0Point(object, mode, positionVerticesChoice);
					}
					//nếu là chế độ vertex và là chế độ vẽ thì hiện thêm đường kẻ nối các vertex
					if (mode == GL_RENDER) {
						DrawObjectCustom0Line(object, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
				else if (modelEditStyle == 2)
				{
					DrawObjectCustom0Line(object, modelEditStyle, positionChoiceRowOrColumn);
				}
				else
				{
					DrawObjectCustom0Face(object, positionFacesChoice);
					if (mode == GL_RENDER) {
						DrawObjectCustom0Line(object, modelEditStyle, positionChoiceRowOrColumn);
					}
				}
			}
			break;
			default:
				break;
			}
		}
	}
}

//hàm lấy ra các vertex từ vị trí chuỗi vertex được chọn
void getVerticesFromRowOrColumn(itemChoice item,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn, vector<int> &positionVerticesChoice,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//xóa đi các vị trí vertex được chọn
	positionVerticesChoice.clear();
	int numberElement = positionChoiceRowOrColumn.size();
	PositionRowOrColumn pNow;
	switch (item.object)
	{
	case 10: {
		SphereAttribute *object = sphereArray.at(item.positionOfChoice);
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				int offset0 = pNow.positionRow*object->numberLongitude,
					offset1 = offset0 + object->numberLongitude;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				for (int k = 0; k < object->numberLatitude; k++) {
					positionVerticesChoice.push_back(k*object->numberLongitude
						+ pNow.positionColumn);
				}
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				int offset0 = pNow.positionRow*numberVertexInRow,
					offset1 = offset0 + numberVertexInRow;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				for (int k = 0; k < cube->numberVertexInAxisY; k++) {
					positionVerticesChoice.push_back(k*numberVertexInRow + pNow.positionColumn);
				}
				//tìm các điểm nằm nằm trên các hàng đối diện
				for (int k = cube->numberVertexInAxisY - 1; k >= 0; k--) {
					positionVerticesChoice.push_back(k*numberVertexInRow + pNow.positionColumnOpposite);
				}
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *object = coneArray.at(item.positionOfChoice);
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				int offset0 = pNow.positionRow*object->numberLongitude,
					offset1 = offset0 + object->numberLongitude;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				for (int k = 0; k < object->numberLatitude; k++) {
					positionVerticesChoice.push_back(k*object->numberLongitude
						+ pNow.positionColumn);
				}
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				int offset0 = pNow.positionRow*object->numberLongitude,
					offset1 = offset0 + object->numberLongitude;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				for (int k = 0; k < object->numberLatitude; k++) {
					positionVerticesChoice.push_back(k*object->numberLongitude
						+ pNow.positionColumn);
				}
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				int offset0 = pNow.positionRow*object->numberLongitude,
					offset1 = offset0 + object->numberLongitude;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				for (int k = 0; k < object->numberLatitude; k++) {
					positionVerticesChoice.push_back(k*object->numberLongitude
						+ pNow.positionColumn);
				}
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		for (int i = 0; i < numberElement; i++) {
			pNow = positionChoiceRowOrColumn.at(i);

			//nếu là đang chọn hàng
			if (pNow.positionRow != -1) {
				//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
				int offset0 = pNow.positionRow*object->numberLongitude,
					offset1 = offset0 + object->numberLongitude;
				for (int k = offset0; k < offset1; k++) {
					positionVerticesChoice.push_back(k);
				}
			}
			//nếu là đag chọn cột
			else
			{
				for (int k = 0; k < object->numberLatitude; k++) {
					positionVerticesChoice.push_back(k*object->numberLongitude
						+ pNow.positionColumn);
				}
			}
		}
	}
			 break;
	default:
		break;
	}
}

//hàm lấy chuỗi row haowcj column từ chuỗi vertex(dùng cho các hình được tạo theo kiểu dạng sphere)
void getRowOrColumnByVertices(int numberLongitude, int numberLatitude,
	vector<int> positionVerticesChoice, vector<PositionRowOrColumn> &positionChoiceRowOrColumn) {

	//đầu tiên xóa tất cả các phần tử trong mảng các row và column được chọn
	positionChoiceRowOrColumn.clear();

	int offset, valueCheck, numberVertexChoice = positionVerticesChoice.size();
	bool isFound = false;
	//kiểm tra để lấy ra các row từ các vertex
	for (int i = 0; i < numberLatitude; i++) {
		offset = i*numberLongitude;
		for (int j = 0; j < numberLongitude; j++) {
			valueCheck = offset + j;
			//kiểm tra xem trong mảng vertexChoice có phần tử này không
			for (int k = 0; k < numberVertexChoice; k++) {
				if (valueCheck == positionVerticesChoice.at(k)) {
					isFound = true;
					//sau khi tìm được thì xóa phần tử đó ra khỏi mảng
					//(do đây chỉ là bản copy nên không lo bị mất phần tử ở mảng chính)
					positionVerticesChoice.erase(positionVerticesChoice.begin() + k);
					numberVertexChoice--;
					break;
				}
			}
			//nếu chỉ cần có bất kì một điểm nào trong row không được chọn thì không có row đó
			if (!isFound) {
				break;
			}
			//nếu đến cuối mảng và isFound là true thì đã tìm ra row được xác định bởi vertices
			else {
				if (j == numberLongitude - 1) {
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });
				}
				isFound = false;
			}
		}
	}
	//nếu đã tìm thấy dù chỉ 1 row thì không tìm column nữa
	if (positionChoiceRowOrColumn.empty()) {
		//kiểm tra để lấy ra các column từ các vertex được chọn
		for (int i = 0; i < numberLongitude; i++) {
			for (int j = 0; j < numberLatitude; j++) {
				valueCheck = j*numberLongitude + i;
				//kiểm tra xem trong mảng vertexChoice có phần tử này không
				for (int k = 0; k < numberVertexChoice; k++) {
					if (valueCheck == positionVerticesChoice.at(k)) {
						isFound = true;
						//sau khi tìm được thì xóa phần tử đó ra khỏi mảng
						//(do đây chỉ là bản copy nên không lo bị mất phần tử ở mảng chính)
						positionVerticesChoice.erase(positionVerticesChoice.begin() + k);
						numberVertexChoice--;
						break;
					}
				}
				//nếu chỉ cần có bất kì một điểm nào trong row không được chọn thì không có row đó
				if (!isFound) {
					break;
				}
				//nếu đến cuối mảng và isFound là true thì đã tìm ra row được xác định bởi vertices
				else {
					if (j == numberLatitude - 1) {
						positionChoiceRowOrColumn.push_back({ -1,i,-1 });
					}
					isFound = false;
				}
			}
		}
	}
}
//hàm lấy ra row và column từ các vertex đang được chọn của hình đang chọn
void getRowOrColumnByVertices(itemChoice item,
	vector<int> positionVerticesChoice, vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	
	switch (item.object)
	{
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		getRowOrColumnByVertices(sphere->numberLongitude, sphere->numberLatitude,
			positionVerticesChoice, positionChoiceRowOrColumn);
	}
			 break;
	/*case 11: {
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);

	}
			 break;*/
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		getRowOrColumnByVertices(cone->numberLongitude, cone->numberLatitude,
			positionVerticesChoice, positionChoiceRowOrColumn);
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		getRowOrColumnByVertices(cylinder->numberLongitude, cylinder->numberLatitude,
			positionVerticesChoice, positionChoiceRowOrColumn);
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		getRowOrColumnByVertices(cylinder->numberLongitude, cylinder->numberLatitude,
			positionVerticesChoice, positionChoiceRowOrColumn);
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		getRowOrColumnByVertices(object->numberLongitude, object->numberLatitude,
			positionVerticesChoice, positionChoiceRowOrColumn);
	}
			 break;
	default:
		break;
	}
}

//lấy ra các vertex được chọn mà có gắn liền với khuôn mặt được chọn
//phải kiểm tra độ sâu cảu mặt được chọn nữa
void getVertexByFace(vector<int> &positionVerticesChoice, vector<int> &positionFacesChoice, itemChoice item,
	vector<TriangleStripAttribute*> triaStripArray, vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<PyramidAttribute*> pyrArray,
	vector<EmptyCylinderAttribute*> emptyCylinderArray, vector<TorusAttribute*> torusArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	//xóa hết các vertex được chọn trong mảng vertex chọn
	positionVerticesChoice.clear();

	int numberFace = positionFacesChoice.size(), faceValue;

	int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;
	bool isFoundValue = false;
	switch (item.object)
	{
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		for (int k = 0; k < numberFace; k++) {
			faceValue = positionFacesChoice.at(k);
			positionVerticesChoice.push_back(faceValue);
			positionVerticesChoice.push_back(faceValue + 1);
			positionVerticesChoice.push_back(faceValue + 2);
		}
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		if (numberFace > 0) {
			positionVerticesChoice.push_back(0);
		}
		for (int k = 0; k < numberFace; k++) {
			faceValue = positionFacesChoice.at(k);
			//đối với triaFan thì điểm khởi đầu luôn được nối với 2 điểm liên tiếp
			positionVerticesChoice.push_back(faceValue);
			positionVerticesChoice.push_back(faceValue + 1);
		}
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = sphere->numberLatitude - (sphere->degreeLatitudeLimit / (360 / sphere->numberLatitude));
		minusLongitude = sphere->numberLongitude - (sphere->degreeLongitudeLimit / (360 / sphere->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}

		offsetFace = 0;
		for (int i = 1; i < sphere->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * sphere->numberLongitude;
			offsetNow = i * sphere->numberLongitude;
			for (int j = minusLongitude + 1; j < sphere->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
				//nếu là cặp đỉnh đầu tiên thì nối với cặp đỉnh cuối cùng
				if (j == sphere->numberLongitude - 1) {
					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetLast + j);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;

					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetNow);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;
				}
			}
		}
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int numberVertexInRow, offsetFace = 0,
			offset1, offset2, offset3, offsetNormal = 0;
		numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;

		glBegin(GL_TRIANGLES);
		// vẽ mặt cho hình bao quanh hình vuông
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 1; j < numberVertexInRow; j++) {
				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offset1 + j - 1);
						positionVerticesChoice.push_back(offset2 + j - 1);
						positionVerticesChoice.push_back(offset1 + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offset2 + j);
						positionVerticesChoice.push_back(offset2 + j - 1);
						positionVerticesChoice.push_back(offset1 + j);
						break;
					}
				}
				offsetFace++;

				//nếu là cặp đỉnh cuối cùng thì vẽ nối với cặp đỉnh đầu tiên
				if (j == numberVertexInRow - 1) {
					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offset2 + j);
							positionVerticesChoice.push_back(offset1);
							positionVerticesChoice.push_back(offset1 + j);
							break;
						}
					}
					offsetFace++;

					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offset2 + j);
							positionVerticesChoice.push_back(offset1);
							positionVerticesChoice.push_back(offset2);
							break;
						}
					}
					offsetFace++;
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

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						//tính đỉnh v0
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset1 - (j - 1));
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(numberVertexInRow - i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v1
						if (i == 1) {
							positionVerticesChoice.push_back(j - 1);
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(numberVertexInRow - (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v2
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset1 - j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(cube->numberVertexInAxisX - 1 + i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						break;
					}
				}

				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						//tính đỉnh v3
						if (i == 1) {
							positionVerticesChoice.push_back(j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(cube->numberVertexInAxisX - 1 + (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						//tính đỉnh v1
						if (i == 1) {
							positionVerticesChoice.push_back(j - 1);
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(numberVertexInRow - (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v2
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset1 - j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(cube->numberVertexInAxisX - 1 + i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						break;
					}
				}
				offsetFace++;
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
				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						//tính đỉnh v0
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset3 + offset1 - (j - 1));
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(offset3 + numberVertexInRow - i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v1
						if (i == 1) {
							positionVerticesChoice.push_back(offset3 + j - 1);
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(offset3 + numberVertexInRow - (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v2
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset3 + offset1 - j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(offset3 + cube->numberVertexInAxisX - 1 + i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						break;
					}
				}
				offsetFace++;
				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						//tính đỉnh v3
						if (i == 1) {
							positionVerticesChoice.push_back(offset3 + j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(offset3 + cube->numberVertexInAxisX - 1 + (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						//tính đỉnh v1
						if (i == 1) {
							positionVerticesChoice.push_back(offset3 + j - 1);
						}
						else
						{
							if (j == 1) {
								positionVerticesChoice.push_back(offset3 + numberVertexInRow - (i - 1));
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 2)*(cube->numberVertexInAxisX - 2) + (j - 2));
							}
						}
						//tính đỉnh v2
						if (i == cube->numberVertexInAxisZ - 1) {
							positionVerticesChoice.push_back(offset3 + offset1 - j);
						}
						else
						{
							if (j == cube->numberVertexInAxisX - 1) {
								positionVerticesChoice.push_back(offset3 + cube->numberVertexInAxisX - 1 + i);
							}
							else
							{
								positionVerticesChoice.push_back(offset2 + (i - 1)*(cube->numberVertexInAxisX - 2) + (j - 1));
							}
						}
						break;
					}
				}
				offsetFace++;
			}
		}
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);

		offsetFace = 0;
		for (int i = 1; i < cube->numberLatitude; i++) {
			offsetLast = (i - 1) * cube->numberLongitude;
			offsetNow = i * cube->numberLongitude;
			for (int j = 1; j < cube->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
			}
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cone->numberLatitude - (cone->degreeLatitudeLimit / (360 / cone->numberLatitude));
		minusLongitude = cone->numberLongitude - (cone->degreeLongitudeLimit / (360 / cone->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}

		offsetFace = 0;
		for (int i = 1; i < cone->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cone->numberLongitude;
			offsetNow = i * cone->numberLongitude;
			for (int j = minusLongitude + 1; j < cone->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cone->numberLongitude - 1) {
					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetLast + j);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;

					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetNow);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;
				}
			}
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}

		offsetFace = 0;
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetLast + j);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;

					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetNow);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;
				}
			}
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}

		offsetFace = 0;
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetLast + j);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;

					for (int k = 0; k < numberFace; k++) {
						if (positionFacesChoice.at(k) == offsetFace) {
							positionVerticesChoice.push_back(offsetNow);
							positionVerticesChoice.push_back(offsetNow + j);
							positionVerticesChoice.push_back(offsetLast);
							break;
						}
					}
					offsetFace++;
				}
			}
		}
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		for (int i = 0; i < numberFace; i++) {

			for (int k = 0; k < numberFace; k++) {
				if (positionFacesChoice.at(k) == i) {
					positionVerticesChoice.push_back(i);
					positionVerticesChoice.push_back(i + 1);
					positionVerticesChoice.push_back(i + 2);
					break;
				}
			}

		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		offsetFace = 0;
		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1) * object->numberLongitude;
			offsetNow = i * object->numberLongitude;
			for (int j = 1; j < object->numberLongitude; j++) {

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetLast + j - 1);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;

				for (int k = 0; k < numberFace; k++) {
					if (positionFacesChoice.at(k) == offsetFace) {
						positionVerticesChoice.push_back(offsetNow + j);
						positionVerticesChoice.push_back(offsetNow + j - 1);
						positionVerticesChoice.push_back(offsetLast + j);
						break;
					}
				}
				offsetFace++;
			}
		}
	}
	break;
	default:
		break;
	}
	//xóa hết các vertex trùng(do các mặt gần nhau dùng chung 1 đến 2 phần tử)
	clearSamePoints(positionVerticesChoice);
}

//kiểm tra xem có thể thêm các chuỗi vertex vào trong hình đang được chọn
void checkToCreatRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<point> &vertexToDrawRectangle, vector<point> &vertexToDrawRectangleSymmetry,
	itemTextureObject itemTexture, PositionRowOrColumn &positionAddRowOrColumn,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;

	int offsetLast = 0, offsetNow = 0, elementCheck = -1,
		numberSymmetry, numberItemSymmetry;
	bool isHaveSymmetryVertices = false, isHaveSymmetryObjects = false;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectsCheck;
	float distanceUpToPoint, distanceDownToPoint, distanceUpToDown, scaleUpPointAndUpDown;
	point up, down, poi;
	point ver;

	//xóa hết độ sâu vè vẽ lại chỉ các hình để lấy độ sâu
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);

	//xóa đi các vertex vẽ hình chữ nhật để thêm lại
	vertexToDrawRectangle.clear();
	vertexToDrawRectangleSymmetry.clear();
	itemChoice item = itemsChoice.at(0);
	switch (item.object)
	{
	case 10:
	{
		DrawSphere(GL_RENDER, sphereArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < sphere->numberLatitude; i++) {
			offsetLast = (i - 1)*sphere->numberLongitude;
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j < sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetLast + j);
				down = sphere->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != (i - 1)) {
						return;
					}
					for (int k = 0; k < sphere->numberLongitude; k++) {
						up = sphere->vertexArray.at(offsetLast + k);
						down = sphere->vertexArray.at(offsetNow + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetLast = (elementCheck + 1)*sphere->numberLongitude;
						offsetNow = elementCheck*sphere->numberLongitude;
						for (int k = 0; k < sphere->numberLongitude; k++) {
							up = sphere->vertexArray.at(offsetLast + k);
							down = sphere->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray1);
						}
						//đặt hàng thêm vào object đối diện
						for (int k = 0; k < sphere->numberLongitude; k++) {
							up = sphere->vertexArray.at(offsetLast + k);
							down = sphere->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i - 1;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < sphere->numberLatitude; i++) {
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j<sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetNow + j);
				if (j == sphere->numberLongitude - 1) {
					down = sphere->vertexArray.at(offsetNow);
				}
				else
				{
					down = sphere->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != j) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < sphere->numberLatitude; k++) {
						offsetNow = k*sphere->numberLongitude + j;
						up = sphere->vertexArray.at(offsetNow);
						if (j == sphere->numberLongitude - 1) {
							down = sphere->vertexArray.at(k*sphere->numberLongitude);
						}
						else {
							down = sphere->vertexArray.at(offsetNow + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
						//vị trí 2 điểm đó luôn vì nó giống nhau
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
						for (int k = 0; k < sphere->numberLatitude; k++) {
							offsetNow = k*sphere->numberLongitude + elementCheck;
							up = sphere->vertexArray.at(offsetNow);
							if (elementCheck == 0) {
								down = sphere->vertexArray.at((k + 1)*sphere->numberLongitude - 1);
							}
							else {
								down = sphere->vertexArray.at(offsetNow - 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						//thêm ở hình đối diện 
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray1);
						}
						for (int k = 0; k < sphere->numberLatitude; k++) {
							offsetNow = k*sphere->numberLongitude + j;
							up = sphere->vertexArray.at(offsetNow);
							if (j == sphere->numberLongitude - 1) {
								down = sphere->vertexArray.at(k*sphere->numberLongitude);
							}
							else {
								down = sphere->vertexArray.at(offsetNow + 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
	}
	break;
	case 11:
	{
		DrawCube(GL_RENDER, cubeArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		//kiểm tra xem có chọn trúng các điểm nằm dọc hình hộp không
		//biến thông báo số hàng của cube
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2,
			offset1, offset2;
		//kiểm tra các điểm nằm dọc hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				down = cube->vertexArray.at(offset2 + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != i) {
						return;
					}
					for (int k = 0; k < numberVertexInRow; k++) {
						up = cube->vertexArray.at(offset1 + k);
						down = cube->vertexArray.at(offset2 + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown * scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i;
					return;
				}
			}
		}
		//kiểm tra các điểm nằm ngang hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				if (j == numberVertexInRow - 1) {
					down = cube->vertexArray.at(offset1);
				}
				else
				{
					down = cube->vertexArray.at(offset1 + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//tìm ra điểm đối diện của điểm được chọn

					int startZ1 = cube->numberVertexInAxisX - 1,
						startX2 = startZ1 + cube->numberVertexInAxisZ - 1,
						startZ2 = startX2 + cube->numberVertexInAxisX - 1, pointOpposite, position;
					//vị trí theo thứ tự trước sau hay phải sang trái
					int positionFirst, positionLast;
					//biến thông báo có di chuyển ngươc giá trị không(do nếu nhấn ở hàng sau hoặc bên phải thì giá trị
					//di chuyển sẽ ngược với khi nhấn ở hàng trước và bên trái)
					bool isTurnAround = false;

					//kiểm tra xem j nằm ở hàng nào
					if (j < startZ1) {
						pointOpposite = j + (startZ1 - j - 1) + cube->numberVertexInAxisZ + (startZ1 - j - 1);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j >= startZ1 && j<startX2)
					{
						pointOpposite = j + (startX2 - j - 1) + cube->numberVertexInAxisX + (startX2 - j - 1);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j >= startX2 && j<startZ2)
					{
						pointOpposite = j - ((j - startX2) + cube->numberVertexInAxisZ + (j - startX2));
						positionFirst = pointOpposite;
						positionLast = j;
						isTurnAround = true;
					}
					else
					{
						pointOpposite = j - ((j - startZ2) + cube->numberVertexInAxisX + (j - startZ2));
						positionFirst = pointOpposite;
						positionLast = j;
						isTurnAround = true;
					}
					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != positionFirst) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cube->numberVertexInAxisY; k++) {
						offset1 = k*numberVertexInRow;
						up = cube->vertexArray.at(offset1 + positionFirst);
						if (positionFirst == numberVertexInRow - 1) {
							down = cube->vertexArray.at(offset1);
						}
						else
						{
							down = cube->vertexArray.at(offset1 + positionFirst + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
							//với nhấn ở phía trước và trái
							if (isTurnAround) {
								distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceDownToPoint);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
							}
							vertexToDrawRectangle.push_back(ver);
						}
					}

					//tìm các điểm ở nắp dưới(các điểm ở phía trong nếu có)

					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = 1; k < cube->numberVertexInAxisZ - 1; k++) {
								//nếu điểm được chọn là điểm đầu tiên hay cuối cùng thì sẽ lấy các điểm 
								//khác với các vị trí khác nằm ở giữa
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);

								if (positionFirst == 0) {
									up = cube->vertexArray.at(offset3 + numberVertexInRow - k);
								}
								else
								{
									up = cube->vertexArray.at(offset1 + (positionFirst - 1) + offset2);
								}

								if (positionFirst == cube->numberVertexInAxisX - 2) {
									down = cube->vertexArray.at(offset3 + cube->numberVertexInAxisX - 1 + k);
								}
								else
								{
									down = cube->vertexArray.at(offset1 + positionFirst + offset2);
								}

								distanceUpToDown = distanceTwoPoint(up, down);
								if (distanceUpToDown == 0) {
									vertexToDrawRectangle.push_back(up);
								}
								else
								{
									//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
									//với nhấn ở phía trước và trái
									if (isTurnAround) {
										distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceDownToPoint);
									}
									else
									{
										distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceUpToPoint);
									}
									vertexToDrawRectangle.push_back(ver);
								}
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						//nếu số hàng của trục x lớn hơn 2 thì cần thêm điểm
						if (cube->numberVertexInAxisX > 2) {
							position = positionFirst - (cube->numberVertexInAxisX - 1);

							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = cube->numberVertexInAxisX - 2; k >= 1; k--) {

								//nếu điểm nhấn là 1 trong 2 điểm ngoài cùng thì sẽ lấy khác với các điểm khác
								if (position == 0) {
									up = cube->vertexArray.at(offset3 + k);
								}
								else
								{
									up = cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)* (position - 1) + (k - 1));
								}

								if (position == cube->numberVertexInAxisZ - 2) {
									down = cube->vertexArray.at(offset3 + cube->numberVertexInAxisX * 2 + cube->numberVertexInAxisZ - 3 - k);
								}
								else
								{
									down = cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)*position + (k - 1));
								}

								distanceUpToDown = distanceTwoPoint(up, down);
								if (distanceUpToDown == 0) {
									vertexToDrawRectangle.push_back(up);
								}
								else
								{
									//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
									//với nhấn ở phía trước và trái
									if (isTurnAround) {
										distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceDownToPoint);
									}
									else
									{
										distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceUpToPoint);
									}
									vertexToDrawRectangle.push_back(ver);
								}
							}
						}
					}


					//tìm các điểm nằm nằm trên các hàng đối diện

					for (int k = cube->numberVertexInAxisY - 1; k >= 0; k--) {
						offset1 = k*numberVertexInRow;
						down = cube->vertexArray.at(offset1 + positionLast);
						if (positionLast == numberVertexInRow - 1) {
							up = cube->vertexArray.at(offset1);
						}
						else
						{
							up = cube->vertexArray.at(offset1 + positionLast + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
						//với nhấn ở phía trước và trái
						if (isTurnAround) {
							distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceDownToPoint);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
						}
						vertexToDrawRectangle.push_back(ver);
					}
					//tìm các điểm ở nắp trên
					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía trên)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY;

							for (int k = cube->numberVertexInAxisZ - 2; k >= 1; k--) {
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);
								if (positionFirst == 0) {
									up = cube->vertexArray.at(numberVertexInRow - k);
								}
								else
								{
									up = cube->vertexArray.at(offset1 + (positionFirst - 1) + offset2);
								}

								if (positionFirst == cube->numberVertexInAxisX - 2) {
									down = cube->vertexArray.at(cube->numberVertexInAxisX - 1 + k);
								}
								else
								{
									down = cube->vertexArray.at(offset1 + positionFirst + offset2);
								}

								distanceUpToDown = distanceTwoPoint(up, down);
								if (distanceUpToDown == 0) {
									vertexToDrawRectangle.push_back(up);
								}
								else
								{
									//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
									//với nhấn ở phía trước và trái
									if (isTurnAround) {
										distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceDownToPoint);
									}
									else
									{
										distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
										normalizeWithRadius(up, down, ver, distanceUpToPoint);
									}
									vertexToDrawRectangle.push_back(ver);
								}
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						position = positionFirst - (cube->numberVertexInAxisX - 1);
						//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
						offset1 = numberVertexInRow*cube->numberVertexInAxisY;

						for (int k = 1; k < cube->numberVertexInAxisX - 1; k++) {
							//nếu điểm nhấn là 1 trong 2 điểm ngoài cùng thì sẽ lấy khác với các điểm khác
							if (position == 0) {
								up = cube->vertexArray.at(k);
							}
							else
							{
								up = cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)*(position - 1) + (k - 1));
							}

							if (position == cube->numberVertexInAxisZ - 2) {
								down = cube->vertexArray.at(cube->numberVertexInAxisX * 2 + cube->numberVertexInAxisZ - 3 - k);
							}
							else
							{
								down = cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)*position + (k - 1));
							}

							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangle.push_back(up);
							}
							else
							{
								//nếu nhấn vào phía sau hoặc bên phải thì lấy giá trị khoảng cách khác
								//với nhấn ở phía trước và trái
								if (isTurnAround) {
									distanceDownToPoint = distanceUpToDown - distanceUpToDown*scaleUpPointAndUpDown;
									normalizeWithRadius(up, down, ver, distanceDownToPoint);
								}
								else
								{
									distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
									normalizeWithRadius(up, down, ver, distanceUpToPoint);
								}
								vertexToDrawRectangle.push_back(ver);
							}
						}
					}

					positionAddRowOrColumn.positionColumn = positionFirst;
					positionAddRowOrColumn.positionColumnOpposite = positionLast;
					return;
				}
			}
		}

	}
	break;
	case 13:
	{
		DrawCone(GL_RENDER, coneArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cone->numberLatitude; i++) {
			offsetLast = (i - 1)*cone->numberLongitude;
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j < cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetLast + j);
				down = cone->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != (i - 1)) {
						return;
					}
					for (int k = 0; k < cone->numberLongitude; k++) {
						up = cone->vertexArray.at(offsetLast + k);
						down = cone->vertexArray.at(offsetNow + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetLast = (elementCheck + 1)*cone->numberLongitude;
						offsetNow = elementCheck*cone->numberLongitude;
						for (int k = 0; k < cone->numberLongitude; k++) {
							up = cone->vertexArray.at(offsetLast + k);
							down = cone->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cone = coneArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cone = coneArray.at(symmetryObjectsCheck.positionInArray1);
						}
						//đặt hàng thêm vào object đối diện
						for (int k = 0; k < cone->numberLongitude; k++) {
							up = cone->vertexArray.at(offsetLast + k);
							down = cone->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i - 1;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cone->numberLatitude; i++) {
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j<cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetNow + j);
				if (j == cone->numberLongitude - 1) {
					down = cone->vertexArray.at(offsetNow);
				}
				else
				{
					down = cone->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != j) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cone->numberLatitude; k++) {
						offsetNow = k*cone->numberLongitude + j;
						up = cone->vertexArray.at(offsetNow);
						if (j == cone->numberLongitude - 1) {
							down = cone->vertexArray.at(k*cone->numberLongitude);
						}
						else {
							down = cone->vertexArray.at(offsetNow + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
						//vị trí 2 điểm đó luôn vì nó giống nhau
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{

							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
						for (int k = 0; k < cone->numberLatitude; k++) {
							offsetNow = k*cone->numberLongitude + elementCheck;
							up = cone->vertexArray.at(offsetNow);
							if (elementCheck == 0) {
								down = cone->vertexArray.at((k + 1)*cone->numberLongitude - 1);
							}
							else {
								down = cone->vertexArray.at(offsetNow - 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						//thêm ở hình đối diện 
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cone = coneArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cone = coneArray.at(symmetryObjectsCheck.positionInArray1);
						}
						for (int k = 0; k < cone->numberLatitude; k++) {
							offsetNow = k*cone->numberLongitude + j;
							up = cone->vertexArray.at(offsetNow);
							if (j == cone->numberLongitude - 1) {
								down = cone->vertexArray.at(k*cone->numberLongitude);
							}
							else {
								down = cone->vertexArray.at(offsetNow + 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
	}
	break;
	case 14:
	{
		DrawCylinder(GL_RENDER, cylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != (i - 1)) {
						return;
					}
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						up = cylinder->vertexArray.at(offsetLast + k);
						down = cylinder->vertexArray.at(offsetNow + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetLast = (elementCheck + 1)*cylinder->numberLongitude;
						offsetNow = elementCheck*cylinder->numberLongitude;
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							up = cylinder->vertexArray.at(offsetLast + k);
							down = cylinder->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}
						//đặt hàng thêm vào object đối diện
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							up = cylinder->vertexArray.at(offsetLast + k);
							down = cylinder->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i - 1;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != j) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						offsetNow = k*cylinder->numberLongitude + j;
						up = cylinder->vertexArray.at(offsetNow);
						if (j == cylinder->numberLongitude - 1) {
							down = cylinder->vertexArray.at(k*cylinder->numberLongitude);
						}
						else {
							down = cylinder->vertexArray.at(offsetNow + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
						//vị trí 2 điểm đó luôn vì nó giống nhau
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{

							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							offsetNow = k*cylinder->numberLongitude + elementCheck;
							up = cylinder->vertexArray.at(offsetNow);
							if (elementCheck == 0) {
								down = cylinder->vertexArray.at((k + 1)*cylinder->numberLongitude - 1);
							}
							else {
								down = cylinder->vertexArray.at(offsetNow - 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						//thêm ở hình đối diện 
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							offsetNow = k*cylinder->numberLongitude + j;
							up = cylinder->vertexArray.at(offsetNow);
							if (j == cylinder->numberLongitude - 1) {
								down = cylinder->vertexArray.at(k*cylinder->numberLongitude);
							}
							else {
								down = cylinder->vertexArray.at(offsetNow + 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
	}
	break;
	case 16:
	{
		DrawEmptyCylinder(GL_RENDER, emptyCylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != (i - 1)) {
						return;
					}
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						up = cylinder->vertexArray.at(offsetLast + k);
						down = cylinder->vertexArray.at(offsetNow + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetLast = (elementCheck + 1)*cylinder->numberLongitude;
						offsetNow = elementCheck*cylinder->numberLongitude;
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							up = cylinder->vertexArray.at(offsetLast + k);
							down = cylinder->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}
						//đặt hàng thêm vào object đối diện
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							up = cylinder->vertexArray.at(offsetLast + k);
							down = cylinder->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i - 1;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != j) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						offsetNow = k*cylinder->numberLongitude + j;
						up = cylinder->vertexArray.at(offsetNow);
						if (j == cylinder->numberLongitude - 1) {
							down = cylinder->vertexArray.at(k*cylinder->numberLongitude);
						}
						else {
							down = cylinder->vertexArray.at(offsetNow + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
						//vị trí 2 điểm đó luôn vì nó giống nhau
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{

							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							offsetNow = k*cylinder->numberLongitude + elementCheck;
							up = cylinder->vertexArray.at(offsetNow);
							if (elementCheck == 0) {
								down = cylinder->vertexArray.at((k + 1)*cylinder->numberLongitude - 1);
							}
							else {
								down = cylinder->vertexArray.at(offsetNow - 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						//thêm ở hình đối diện 
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							offsetNow = k*cylinder->numberLongitude + j;
							up = cylinder->vertexArray.at(offsetNow);
							if (j == cylinder->numberLongitude - 1) {
								down = cylinder->vertexArray.at(k*cylinder->numberLongitude);
							}
							else {
								down = cylinder->vertexArray.at(offsetNow + 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
	}
	break;
	case 19:
	{
		DrawObjectCustom0(GL_RENDER, objectCustom0Array, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1)*object->numberLongitude;
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j < object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetLast + j);
				down = object->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì tính ra các điểm nằm giữa 2 hàng hiện tại
					//và cách điểm trên 1 khoảng cách đúng như hiện tại

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionRow != (i - 1)) {
						return;
					}
					for (int k = 0; k < object->numberLongitude; k++) {
						up = object->vertexArray.at(offsetLast + k);
						down = object->vertexArray.at(offsetNow + k);
						distanceUpToDown = distanceTwoPoint(up, down);
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{
							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetLast = (elementCheck + 1)*object->numberLongitude;
						offsetNow = elementCheck*object->numberLongitude;
						for (int k = 0; k < object->numberLongitude; k++) {
							up = object->vertexArray.at(offsetLast + k);
							down = object->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray1);
						}
						//đặt hàng thêm vào object đối diện
						for (int k = 0; k < object->numberLongitude; k++) {
							up = object->vertexArray.at(offsetLast + k);
							down = object->vertexArray.at(offsetNow + k);
							distanceUpToDown = distanceTwoPoint(up, down);
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionRow = i - 1;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < object->numberLatitude; i++) {
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j<object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetNow + j);
				if (j == object->numberLongitude - 1) {
					down = object->vertexArray.at(offsetNow);
				}
				else
				{
					down = object->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				scaleUpPointAndUpDown = distanceUpToPoint / distanceUpToDown;
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionAddRowOrColumn.positionColumn != j) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < object->numberLatitude; k++) {
						offsetNow = k*object->numberLongitude + j;
						up = object->vertexArray.at(offsetNow);
						if (j == object->numberLongitude - 1) {
							down = object->vertexArray.at(k*object->numberLongitude);
						}
						else {
							down = object->vertexArray.at(offsetNow + 1);
						}
						distanceUpToDown = distanceTwoPoint(up, down);
						//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
						//vị trí 2 điểm đó luôn vì nó giống nhau
						if (distanceUpToDown == 0) {
							vertexToDrawRectangle.push_back(up);
						}
						else
						{

							distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
							normalizeWithRadius(up, down, ver, distanceUpToPoint);
							vertexToDrawRectangle.push_back(ver);
						}
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
						for (int k = 0; k < object->numberLatitude; k++) {
							offsetNow = k*object->numberLongitude + elementCheck;
							up = object->vertexArray.at(offsetNow);
							if (elementCheck == 0) {
								down = object->vertexArray.at((k + 1)*object->numberLongitude - 1);
							}
							else {
								down = object->vertexArray.at(offsetNow - 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					else if (isHaveSymmetryObjects) {
						//thêm ở hình đối diện 
						if (symmetryObjectsCheck.positionInArray1 == item.positionOfChoice) {
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray1);
						}
						for (int k = 0; k < object->numberLatitude; k++) {
							offsetNow = k*object->numberLongitude + j;
							up = object->vertexArray.at(offsetNow);
							if (j == object->numberLongitude - 1) {
								down = object->vertexArray.at(k*object->numberLongitude);
							}
							else {
								down = object->vertexArray.at(offsetNow + 1);
							}
							distanceUpToDown = distanceTwoPoint(up, down);
							//nếu khoảng cách giữa 2 điểm là 0 tức là 2 điểm trùng nhau thì đặt điểm cần đặt vào 1 trong 
							//vị trí 2 điểm đó luôn vì nó giống nhau
							if (distanceUpToDown == 0) {
								vertexToDrawRectangleSymmetry.push_back(up);
							}
							else
							{
								distanceUpToPoint = distanceUpToDown*scaleUpPointAndUpDown;
								normalizeWithRadius(up, down, ver, distanceUpToPoint);
								vertexToDrawRectangleSymmetry.push_back(ver);
							}
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột thêm các dãy vertex vào sau
					positionAddRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
	}
	break;
	default:
		break;
	}
}
//hàm thêm chuỗi vào vị trí chọn và cả vị trí đối xứng(nếu có)
//hàm nay dùng cho các hình tương tự sphere
void addVerticesAndVerticesSymmetryInRowOrColumn(int &numberLongitude, int &numberLatitude,
	bool isAddChoiceInROrC1,
	PositionRowOrColumn positionAddRowOrColumn, PositionRowOrColumn positionAddRowOrColumnSymmetry,
	vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	vector<point> &vertexArray,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	SymmetryVertices &symmetryVerticesNow) {

	int numberElement;

	if (positionAddRowOrColumn.positionRow != -1) {
		//kiểm tra xem cái nào lớn hơn để thêm tương ứng
		if (positionAddRowOrColumnSymmetry.positionRow > positionAddRowOrColumn.positionRow) {
			vertexArray.insert(vertexArray.begin() + positionAddRowOrColumnSymmetry.positionRow*numberLongitude,
				vertexToDrawRectangleSymmetry.begin(), vertexToDrawRectangleSymmetry.end());

			vertexArray.insert(vertexArray.begin() + (positionAddRowOrColumn.positionRow + 1)*numberLongitude,
				vertexToDrawRectangle.begin(), vertexToDrawRectangle.end());
			//xem phần tử nào thuộc symmetry1 thì thêm vào đầu,2 thì vào sau
			if (isAddChoiceInROrC1) {
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 1,-1,-1 });
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumnSymmetry.positionRow + 1,-1,-1 });
			}
			else
			{
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumnSymmetry.positionRow + 1,-1,-1 });
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 1,-1,-1 });
			}

			//nếu itemSymmetry lớn hơn thì itemSymmetry+1
			positionAddRowOrColumnSymmetry.positionRow++;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			//phải load từ sau ra trước để tăng các giá trị mốc vừa thêm vào nếu cần
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu itemSymmetry lớn hơn thì so sánh positionAddRowOrColumn.positionRow trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow >= (positionAddRowOrColumn.positionRow + 1)) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow++;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow >= positionAddRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow++;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu itemSymmetry lớn hơn thì so sánh positionAddRowOrColumn.positionRow trước
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow >= (positionAddRowOrColumn.positionRow + 1)) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow++;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow >= positionAddRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow++;
				}
			}
		}
		else
		{
			vertexArray.insert(vertexArray.begin() + (positionAddRowOrColumn.positionRow + 1)*numberLongitude,
				vertexToDrawRectangle.begin(), vertexToDrawRectangle.end());

			vertexArray.insert(vertexArray.begin() + positionAddRowOrColumnSymmetry.positionRow*numberLongitude,
				vertexToDrawRectangleSymmetry.begin(), vertexToDrawRectangleSymmetry.end());
			//xem phần tử nào thuộc symmetry1 thì thêm vào đầu,2 thì vào sau
			if (isAddChoiceInROrC1) {
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 2,-1,-1 });
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumnSymmetry.positionRow,-1,-1 });
			}
			else
			{
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumnSymmetry.positionRow,-1,-1 });
				positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 2,-1,-1 });
			}

			//nếu positionAddRowOrColumn.positionRow lớn hơn thì positionAddRowOrColumn.positionRow+1
			positionAddRowOrColumn.positionRow++;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			//phải load từ sau ra trước để tăng các giá trị mốc vừa thêm vào nếu cần
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu positionAddRowOrColumn.positionColumn lớn hơn thì so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow >= positionAddRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow++;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow >= (positionAddRowOrColumn.positionRow + 1)) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow++;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = numberElement - 1; i >= 0; i--) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow >= positionAddRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow++;
				}
				//nếu positionAddRowOrColumn.positionRow lớn hơn thì so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow >= (positionAddRowOrColumn.positionRow + 1)) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow++;
				}
			}
		}
		//tăng giá trị số vertex trên hàng ngang là 2
		numberLatitude += 2;

		//sau khi thêm vào các chuỗi vertex thì thêm vị trí các chuỗi đó vào positionSymmetry
		if (isAddChoiceInROrC1) {
			symmetryVerticesNow.positionROrC1.push_back({ (positionAddRowOrColumn.positionRow + 1),-1,-1 });
			symmetryVerticesNow.positionROrC2.push_back({ positionAddRowOrColumnSymmetry.positionRow,-1,-1 });
		}
		else
		{
			symmetryVerticesNow.positionROrC1.push_back({ positionAddRowOrColumnSymmetry.positionRow,-1,-1 });
			symmetryVerticesNow.positionROrC2.push_back({ (positionAddRowOrColumn.positionRow + 1),-1,-1 });
		}

	}
	else if (positionAddRowOrColumn.positionColumn != -1) {
		//để thêm vertex vào theo chiều dọc,ta thêm từ các điểm cuối cùng lên các điểm đầu trong mảng
		int offset = 0;
		//kiểm tra xem cái nào lớn hơn để thêm tương ứng
		if (positionAddRowOrColumnSymmetry.positionColumn > positionAddRowOrColumn.positionColumn) {
			for (int i = numberLatitude - 1; i >= 0; i--) {
				offset = i*numberLongitude;
				vertexArray.insert(vertexArray.begin() + offset + positionAddRowOrColumnSymmetry.positionColumn,
					vertexToDrawRectangleSymmetry.at(i));

				vertexArray.insert(vertexArray.begin() + offset + positionAddRowOrColumn.positionColumn + 1,
					vertexToDrawRectangle.at(i));
			}
			//xem phần tử nào thuộc symmetry1 thì thêm vào đầu,2 thì vào sau
			if (isAddChoiceInROrC1) {
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumn.positionColumn + 1,-1 });
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn + 1,-1 });
			}
			else
			{
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn + 1,-1 });
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumn.positionColumn + 1,-1 });
			}

			//nếu itemSymmetry lớn hơn thì itemSymmetry+1
			positionAddRowOrColumnSymmetry.positionColumn++;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			//phải load từ sau ra trước để tăng các giá trị mốc vừa thêm vào nếu cần
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu itemSymmetry lớn hơn thì so sánh positionAddRowOrColumn.positionColumn trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn >= (positionAddRowOrColumn.positionColumn + 1)) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn++;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn >= positionAddRowOrColumnSymmetry.positionColumn) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn++;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu itemSymmetry lớn hơn thì so sánh positionAddRowOrColumn.positionColumn trước
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn >= (positionAddRowOrColumn.positionColumn + 1)) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn++;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn >= positionAddRowOrColumnSymmetry.positionColumn) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn++;
				}
			}
		}
		else
		{
			for (int i = numberLatitude - 1; i >= 0; i--) {
				offset = i*numberLongitude;
				vertexArray.insert(vertexArray.begin() + offset + positionAddRowOrColumn.positionColumn + 1,
					vertexToDrawRectangle.at(i));

				vertexArray.insert(vertexArray.begin() + offset + positionAddRowOrColumnSymmetry.positionColumn,
					vertexToDrawRectangleSymmetry.at(i));
			}
			//xem phần tử nào thuộc symmetry1 thì thêm vào đầu,2 thì vào sau
			if (isAddChoiceInROrC1) {
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumn.positionColumn + 2,-1 });
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn,-1 });
			}
			else
			{
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn,-1 });
				positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumn.positionColumn + 2,-1 });
			}

			//nếu positionAddRowOrColumn.positionColumn lớn hơn thì positionAddRowOrColumn.positionColumn+1
			positionAddRowOrColumn.positionColumn++;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			//phải load từ sau ra trước để tăng các giá trị mốc vừa thêm vào nếu cần
			for (int i = numberElement - 1; i >= 0; i--) {
				//nếu positionAddRowOrColumn.positionColumn lớn hơn thì so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn >= positionAddRowOrColumnSymmetry.positionColumn) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn++;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn >= (positionAddRowOrColumn.positionColumn + 1)) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn++;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = numberElement - 1; i >= 0; i--) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn >= positionAddRowOrColumnSymmetry.positionColumn) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn++;
				}
				//nếu positionAddRowOrColumn.positionColumn lớn hơn thì so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn >= (positionAddRowOrColumn.positionColumn + 1)) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn++;
				}
			}

		}
		//tăng giá trị số vertex trên hàng dọc là 2
		numberLongitude += 2;

		//sau khi thêm vào các chuỗi vertex thì thêm vị trí các chuỗi đó vào positionSymmetry
		if (isAddChoiceInROrC1) {
			symmetryVerticesNow.positionROrC1.push_back({ -1,(positionAddRowOrColumn.positionColumn + 1),-1 });
			symmetryVerticesNow.positionROrC2.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn,-1 });
		}
		else
		{
			symmetryVerticesNow.positionROrC1.push_back({ -1,positionAddRowOrColumnSymmetry.positionColumn,-1 });
			symmetryVerticesNow.positionROrC2.push_back({ -1,(positionAddRowOrColumn.positionColumn + 1),-1 });
		}
	}

}
//hàm thêm cụm vertex cho object hiện tại,không thêm cho đối xưng vertices 
void addVerticesInRowOrColumn(int &numberLongitude, int &numberLatitude,
	PositionRowOrColumn positionAddRowOrColumn, vector<PositionRowOrColumn> &positionChoiceRowOrColumn,
	vector<point> &vertexArray,
	vector<point> vertexToDrawRectangle) {

	if (positionAddRowOrColumn.positionRow != -1) {
		vertexArray.insert(vertexArray.begin() + (positionAddRowOrColumn.positionRow + 1)*numberLongitude,
			vertexToDrawRectangle.begin(), vertexToDrawRectangle.end());
		//tăng giá trị số vertex trên 1 hàng dọc là 1
		numberLatitude++;
		positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 1,-1,-1 });
	}
	else if (positionAddRowOrColumn.positionColumn != -1) {
		//để thêm vertex vào theo chiều dọc,ta thêm từ các điểm cuối cùng lên các điểm đầu trong mảng
		int offset = 0;
		for (int i = numberLatitude - 1; i >= 0; i--) {
			offset = i*numberLongitude + positionAddRowOrColumn.positionColumn + 1;
			vertexArray.insert(vertexArray.begin() + offset,
				vertexToDrawRectangle.at(i));
		}
		//tăng giá trị số vertex trên hàng ngang lên 1
		numberLongitude++;
		positionChoiceRowOrColumn.push_back({ -1,positionAddRowOrColumn.positionColumn + 1,-1 });
	}
}

//hàm thêm chuỗi vertex
void addRowVertexInObject(vector<itemChoice> itemsChoice, PositionRowOrColumn positionAddRowOrColumn,
	vector<PositionRowOrColumn> &positionChoiceRowOrColumn, vector<int> &positionVerticesChoice,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//xóa hết các vị trí chọn lúc trước để chỉ hiện chọn chuỗi mới add vào
	positionChoiceRowOrColumn.clear();

	itemChoice item = itemsChoice.at(0);

	bool isHaveSymmetryVertices = false, isHaveSymmetryObjects = false, isAddChoiceInROrC1;
	int numberSymmetry, positionSymmetryVertices = -1, numberItemSymmetry;
	PositionRowOrColumn positionAddRowOrColumnSymmetry;

	SymmetryObjects symmetryObjectCheck;
	SymmetryVertices symmetryVerticesCheck;

	//đầu tiên kiểm tra xem object được chọn có thong tin trong symmetryObject không
	numberSymmetry = symmetryObjects.size();
	for (int i = 0; i < numberSymmetry; i++) {
		symmetryObjectCheck = symmetryObjects.at(i);
		if (symmetryObjectCheck.object1 == item.object &&
			(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
				symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
			isHaveSymmetryObjects = true;
			break;
		}
	}
	//nếu không tìm ra thông tin của hình hiện tại trong symmetryObject thì thử tìm kiểm trong
	//symmetryVertices xem có chứa thông tin về object này không
	if (!isHaveSymmetryObjects) {
		numberSymmetry = symmetryVertices.size();
		for (int m = 0; m < numberSymmetry; m++) {
			symmetryVerticesCheck = symmetryVertices.at(m);
			//đầu tiên kiểm tra xem đối tượng được chọn có được lưu trữ trong item hiện tại không
			if (symmetryVerticesCheck.object == item.object &&
				symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
				positionSymmetryVertices = m;

				numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
					symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
				//kiểm tra xem trong chuỗi này có vị trí thêm không
				for (int n = 0; n < numberItemSymmetry; n++) {
					if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == positionAddRowOrColumn.positionRow &&
						symmetryVerticesCheck.positionROrC1.at(n).positionColumn == positionAddRowOrColumn.positionColumn) {

						positionAddRowOrColumnSymmetry = symmetryVerticesCheck.positionROrC2.at(n);
						//nếu chuỗi vertex thêm hiện tại thêm vào positionROrC1 và chuỗi vertex đối xứng
						//thêm vào positionROrC2
						isAddChoiceInROrC1 = true;
						isHaveSymmetryVertices = true;
						break;
					}
					else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == positionAddRowOrColumn.positionRow &&
						symmetryVerticesCheck.positionROrC2.at(n).positionColumn == positionAddRowOrColumn.positionColumn) {

						positionAddRowOrColumnSymmetry = symmetryVerticesCheck.positionROrC1.at(n);
						//nếu chuỗi vertex thêm hiện tại thêm vào positionROrC2 và chuỗi vertex đối xứng
						//thêm vào positionROrC1
						isAddChoiceInROrC1 = false;
						isHaveSymmetryVertices = true;
						break;
					}
				}

				break;
			}
		}
	}

	switch (item.object)
	{
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			addVerticesAndVerticesSymmetryInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				isAddChoiceInROrC1,
				positionAddRowOrColumn, positionAddRowOrColumnSymmetry,
				positionChoiceRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
		}
		else if (isHaveSymmetryObjects) {
			//nếu object hiện tại có thông tin trong symmetryObject thì đầu tiên thêm cụm vertex vào object đang chọn
			addVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);

			//tiếp theo thêm cụm vertex vào object đối xứng của object đang được chọn
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			addVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangleSymmetry);

			//phải xóa đi 1 positionChoiceRowOrColumn do ta thêm 2 lần cho object hiện tại và object đối xứng
			positionChoiceRowOrColumn.pop_back();

			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
		}
		else
		{
			addVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
		}

	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
		//thêm các vertex ngang
		if (positionAddRowOrColumn.positionRow != -1) {
			cube->vertexArray.insert(cube->vertexArray.begin() + (positionAddRowOrColumn.positionRow + 1)*numberVertexInRow,
				vertexToDrawRectangle.begin(), vertexToDrawRectangle.end());
			//tăng giá trị số vertex trên 1 hàng dọc là 1
			cube->numberVertexInAxisY++;

			positionChoiceRowOrColumn.push_back({ positionAddRowOrColumn.positionRow + 1, -1,-1 });
		}
		//thêm các vertex dọc
		else if (positionAddRowOrColumn.positionColumn != -1) {
			int numberVertexAddInUpOrDown, offset;
			bool isAddInAxisX = false;
			//tính số vertex thêm vào mặt dưới hoặc trên(vì có thể thêm theo chiều x hoặc z nên sẽ có 2 
			//giá trị khác nhau)
			if (positionAddRowOrColumn.positionColumn < cube->numberVertexInAxisX - 1) {
				numberVertexAddInUpOrDown = cube->numberVertexInAxisZ - 2;
				isAddInAxisX = true;
			}
			else
			{
				numberVertexAddInUpOrDown = cube->numberVertexInAxisX - 2;
				isAddInAxisX = false;
			}
			//phải thêm theo thứ tự từ các đỉnh sau cùng ra trước,tức là 
			//từ vertexDown,vertexUp,vertexAroundBehind,vertexAroundFront
			//riêng vertexAroundBehind và vertexAroundFront là so le nhau nên thêm cùng nhau,
			//còn 2 vertex kia thì sẽ thêm riêng biệt

			//thêm vertex down

			//nếu thêm vào trục x
			if (isAddInAxisX) {
				//nếu số hàng trên trục z>2 thì mới cần thêm
				if (cube->numberVertexInAxisZ > 2) {
					//vị trí đầu tiên của các vertex phía trong của đáy dưới
					offset = numberVertexInRow*cube->numberVertexInAxisY +
						(cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2);

					for (int i = cube->numberVertexInAxisZ - 2; i >= 1; i--) {
						cube->vertexArray.insert(cube->vertexArray.begin() + offset +
							(i - 1)*(cube->numberVertexInAxisX - 2)
							+ positionAddRowOrColumn.positionColumn
							, vertexToDrawRectangle.at(cube->numberVertexInAxisY + i - 1));
					}
				}
			}
			else
			{
				if (cube->numberVertexInAxisX > 2) {
					int position = positionAddRowOrColumn.positionColumn - (cube->numberVertexInAxisX - 1);
					//vị trí đầu tiên của hàng cần thêm các vertex
					offset = numberVertexInRow*cube->numberVertexInAxisY +
						(cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2) +
						position*(cube->numberVertexInAxisX - 2);

					//nếu thêm vào trục z
					for (int i = 1; i < cube->numberVertexInAxisX - 1; i++) {
						cube->vertexArray.insert(cube->vertexArray.begin() + offset,
							vertexToDrawRectangle.at(cube->numberVertexInAxisY + i - 1));
					}
				}
			}

			//thêm vertex up

			//nếu thêm vào trục x
			if (isAddInAxisX) {
				//nếu số hàng trên trục z>2 thì mới cần thêm
				if (cube->numberVertexInAxisZ > 2) {
					//vị trí đầu tiên của các vertex phía trong của đáy trên
					offset = numberVertexInRow*cube->numberVertexInAxisY;

					for (int i = cube->numberVertexInAxisZ - 2; i >= 1; i--) {
						cube->vertexArray.insert(cube->vertexArray.begin() + offset +
							(i - 1)*(cube->numberVertexInAxisX - 2)
							+ positionAddRowOrColumn.positionColumn
							, vertexToDrawRectangle.at(vertexToDrawRectangle.size() - i));
					}
				}
			}
			//nếu thêm vào trục z
			else
			{
				if (cube->numberVertexInAxisX > 2) {
					int position = positionAddRowOrColumn.positionColumn - (cube->numberVertexInAxisX - 1);
					//vị trí đầu tiên của hàng cần thêm các vertex
					offset = numberVertexInRow*cube->numberVertexInAxisY +
						position*(cube->numberVertexInAxisX - 2);

					for (int i = 1; i < cube->numberVertexInAxisX - 1; i++) {
						cube->vertexArray.insert(cube->vertexArray.begin() + offset
							, vertexToDrawRectangle.at(vertexToDrawRectangle.size() - i));
					}
				}
			}

			//thêm vertex vào các vertex ở vòng ngoài
			for (int i = cube->numberVertexInAxisY - 1; i >= 0; i--) {
				//ta phải thêm từ sau ra trước thì k0 bị trôi vị trí thêm vertex
				//thêm vào hàng dọc sau hay bên phải
				cube->vertexArray.insert(cube->vertexArray.begin() + (i*numberVertexInRow)
					+ positionAddRowOrColumn.positionColumnOpposite + 1
					, vertexToDrawRectangle.at(vertexToDrawRectangle.size() - 1 - numberVertexAddInUpOrDown - i));
				//add vertex vào hàng dọc trước hay bên trái
				cube->vertexArray.insert(cube->vertexArray.begin() + (i*numberVertexInRow) +
					positionAddRowOrColumn.positionColumn + 1, vertexToDrawRectangle.at(i));

			}
			if (isAddInAxisX) {
				//nếu đang nhấn ở truc x thì tăng số vertex của trục x lên
				cube->numberVertexInAxisX++;
			}
			else
			{
				//nếu đang nhấn ở truc z thì tăng số vertex của trục z lên
				cube->numberVertexInAxisZ++;
			}

			positionChoiceRowOrColumn.push_back({ -1, positionAddRowOrColumn.positionColumn + 1,
				positionAddRowOrColumn.positionColumn + 2 });
		}

		//tính toán lại normal vector
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
			, cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			addVerticesAndVerticesSymmetryInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				isAddChoiceInROrC1,
				positionAddRowOrColumn, positionAddRowOrColumnSymmetry,
				positionChoiceRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
		}
		else if (isHaveSymmetryObjects) {
			//nếu object hiện tại có thông tin trong symmetryObject thì đầu tiên thêm cụm vertex vào object đang chọn
			addVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);

			//tiếp theo thêm cụm vertex vào object đối xứng của object đang được chọn
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			addVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangleSymmetry);

			//phải xóa đi 1 positionChoiceRowOrColumn do ta thêm 2 lần cho object hiện tại và object đối xứng
			positionChoiceRowOrColumn.pop_back();

			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
		}
		else
		{
			addVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			addVerticesAndVerticesSymmetryInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				isAddChoiceInROrC1,
				positionAddRowOrColumn, positionAddRowOrColumnSymmetry,
				positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else if (isHaveSymmetryObjects) {
			//nếu object hiện tại có thông tin trong symmetryObject thì đầu tiên thêm cụm vertex vào object đang chọn
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//tiếp theo thêm cụm vertex vào object đối xứng của object đang được chọn
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangleSymmetry);

			//phải xóa đi 1 positionChoiceRowOrColumn do ta thêm 2 lần cho object hiện tại và object đối xứng
			positionChoiceRowOrColumn.pop_back();

			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else
		{
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			addVerticesAndVerticesSymmetryInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				isAddChoiceInROrC1,
				positionAddRowOrColumn, positionAddRowOrColumnSymmetry,
				positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else if (isHaveSymmetryObjects) {
			//nếu object hiện tại có thông tin trong symmetryObject thì đầu tiên thêm cụm vertex vào object đang chọn
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//tiếp theo thêm cụm vertex vào object đối xứng của object đang được chọn
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangleSymmetry);

			//phải xóa đi 1 positionChoiceRowOrColumn do ta thêm 2 lần cho object hiện tại và object đối xứng
			positionChoiceRowOrColumn.pop_back();

			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else
		{
			addVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			addVerticesAndVerticesSymmetryInRowOrColumn(object->numberLongitude, object->numberLatitude,
				isAddChoiceInROrC1,
				positionAddRowOrColumn, positionAddRowOrColumnSymmetry,
				positionChoiceRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
		}
		else if (isHaveSymmetryObjects) {
			//nếu object hiện tại có thông tin trong symmetryObject thì đầu tiên thêm cụm vertex vào object đang chọn
			addVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);

			//tiếp theo thêm cụm vertex vào object đối xứng của object đang được chọn
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			addVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangleSymmetry);

			//phải xóa đi 1 positionChoiceRowOrColumn do ta thêm 2 lần cho object hiện tại và object đối xứng
			positionChoiceRowOrColumn.pop_back();

			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
		}
		else
		{
			addVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionAddRowOrColumn, positionChoiceRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
		}
	}
	break;
	default:
		break;
	}

	//lấy ra vị trí các vertex vừa thêm vào vào mảng các vertex được chọn
	getVerticesFromRowOrColumn(item, positionChoiceRowOrColumn, positionVerticesChoice,
		sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);


	//nếu vật được chọn có thông tin về đối xứng vertex thì sau khi add dù có add đối xứng hay không
	//thì vẫn phải tính lại các vertex từ các row và column
	if (positionSymmetryVertices != -1) {
		//đối với trường hợp object này có thông tin trong symmetryVertices mà vertex được thêm vào lại ở
		//vị trí không có đối xứng thì chỉ có 1 hàng hay cột được thêm vào.
		//do đó ta phải đẩy các hàng hay cột có giá trị lớn hơn(không có bằng do nếu có thì đã thuộc positionROrC rồi)
		if(!isHaveSymmetryVertices){
			if (positionAddRowOrColumn.positionRow != -1) {
				numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size();
				for (int i = 0; i<numberItemSymmetry; i++) {
					if (symmetryVerticesCheck.positionROrC1.at(i).positionRow > positionAddRowOrColumn.positionRow) {
						symmetryVertices.at(positionSymmetryVertices).positionROrC1.at(i).positionRow++;
					}
				}
				numberItemSymmetry = symmetryVerticesCheck.positionROrC2.size();
				for (int i = 0; i<numberItemSymmetry; i++) {
					if (symmetryVerticesCheck.positionROrC2.at(i).positionRow > positionAddRowOrColumn.positionRow) {
						symmetryVertices.at(positionSymmetryVertices).positionROrC2.at(i).positionRow++;
					}
				}
			}
			else
			{
				numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size();
				for (int i = 0; i<numberItemSymmetry; i++) {
					if (symmetryVerticesCheck.positionROrC1.at(i).positionColumn > positionAddRowOrColumn.positionColumn) {
						symmetryVertices.at(positionSymmetryVertices).positionROrC1.at(i).positionColumn++;
					}
				}
				numberItemSymmetry = symmetryVerticesCheck.positionROrC2.size();
				for (int i = 0; i<numberItemSymmetry; i++) {
					if (symmetryVerticesCheck.positionROrC2.at(i).positionColumn > positionAddRowOrColumn.positionColumn) {
						symmetryVertices.at(positionSymmetryVertices).positionROrC2.at(i).positionColumn++;
					}
				}
			}
		}

		//sau khi đã đặt đúng các hàng theo tên thì lấy ra các vertex gán với chúng
		getVerticesFromRowOrColumn(item,
			symmetryVertices.at(positionSymmetryVertices).positionROrC1, symmetryVertices.at(positionSymmetryVertices).positionVertices1,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
		getVerticesFromRowOrColumn(item,
			symmetryVertices.at(positionSymmetryVertices).positionROrC2, symmetryVertices.at(positionSymmetryVertices).positionVertices2,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
	}
}

//hàm chọn các chuỗi vertex dọc hay ngang
void checkToChoiceRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	itemTextureObject itemTexture, vector<PositionRowOrColumn> &positionChoiceRowOrColumn, vector<int> &positionVertexChoice,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;

	int offsetLast = 0, offsetNow = 0;
	float distanceUpToPoint, distanceDownToPoint, distanceUpToDown;
	point up, down, poi;

	//kiểm tra xem có đang giữ phím shif không để xóa các item cũ đi
	bool isClearItemBefore = false;
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		positionChoiceRowOrColumn.clear();
		positionVertexChoice.clear();
		isClearItemBefore = true;
	}

	//xóa hết độ sâu vè vẽ lại chỉ các hình để lấy độ sâu
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	itemChoice item = itemsChoice.at(0);
	switch (item.object)
	{
	case 10:
	{
		DrawSphere(GL_RENDER, sphereArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < sphere->numberLatitude; i++) {
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j<sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetNow + j);
				if (j == sphere->numberLongitude - 1) {
					down = sphere->vertexArray.at(offsetNow);
				}
				else
				{
					down = sphere->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < sphere->numberLongitude; k++) {
						positionVertexChoice.push_back(offsetNow + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa các dãy
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < sphere->numberLatitude; i++) {
			offsetLast = (i - 1)*sphere->numberLongitude;
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j < sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetLast + j);
				down = sphere->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < sphere->numberLatitude; k++) {
						positionVertexChoice.push_back(k*sphere->numberLongitude + j);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa các dãy vertex
					positionChoiceRowOrColumn.push_back({ -1,j,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
	}
	break;
	case 11:
	{
		DrawCube(GL_RENDER, cubeArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		//kiểm tra xem có chọn trúng các điểm nằm dọc hình hộp không
		//biến thông báo số hàng của cube
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2,
			offset1, offset2;
		//kiểm tra các điểm nằm dọc hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				down = cube->vertexArray.at(offset2 + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra tất cả các điểm nằm dọc vị trí này

					//tìm ra điểm đối diện của điểm được chọn

					int startZ1 = cube->numberVertexInAxisX - 1,
						startX2 = startZ1 + cube->numberVertexInAxisZ - 1,
						startZ2 = startX2 + cube->numberVertexInAxisX - 1, pointOpposite, position;
					//vị trí theo thứ tự trước sau hay phải sang trái
					int positionFirst = -1, positionLast = -1;

					//đối với việc delete chuỗi vertex thì không cho phép chọn hàng ngoài
					//kiểm tra xem j nằm ở hàng nào
					if (j < startZ1 && j > 0) {
						pointOpposite = j + (startZ1 - j - 1) + cube->numberVertexInAxisZ + (startZ1 - j);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j > startZ1 && j<startX2)
					{
						pointOpposite = j + (startX2 - j - 1) + cube->numberVertexInAxisX + (startX2 - j);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j > startX2 && j <startZ2)
					{
						pointOpposite = j - ((j - startX2) + cube->numberVertexInAxisZ + (j - startX2 - 1));
						positionFirst = pointOpposite;
						positionLast = j;
					}
					else if (j > startZ2 && j < numberVertexInRow)
					{
						pointOpposite = j - ((j - startZ2) + cube->numberVertexInAxisX + (j - startZ2 - 1));
						positionFirst = pointOpposite;
						positionLast = j;
					}

					//nếu chọn 1 trong các chuỗi vertex ở rìa ngoài thì hủy không cho lấy nữa
					if (positionFirst == -1) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cube->numberVertexInAxisY; k++) {
						positionVertexChoice.push_back(k*numberVertexInRow + positionFirst);
					}

					//tìm các điểm ở nắp dưới(các điểm ở phía trong nếu có)

					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = 1; k < cube->numberVertexInAxisZ - 1; k++) {
								//nếu điểm được chọn là điểm đầu tiên hay cuối cùng thì sẽ lấy các điểm 
								//khác với các vị trí khác nằm ở giữa
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);
								positionVertexChoice.push_back(offset1 + (positionFirst - 1) + offset2);
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						//nếu số hàng của trục x lớn hơn 2 thì cần thêm điểm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisX > 2) {
							position = positionFirst - (cube->numberVertexInAxisX - 1);

							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = cube->numberVertexInAxisX - 2; k >= 1; k--) {
								positionVertexChoice.push_back(offset1 + (cube->numberVertexInAxisX - 2)
									* (position - 1) + (k - 1));
							}
						}
					}

					//tìm các điểm nằm nằm trên các hàng đối diện
					for (int k = cube->numberVertexInAxisY - 1; k >= 0; k--) {
						positionVertexChoice.push_back(k*numberVertexInRow + positionLast);
					}

					//tìm các điểm ở nắp trên
					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía trên)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY;

							for (int k = cube->numberVertexInAxisZ - 2; k >= 1; k--) {
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);
								positionVertexChoice.push_back(offset1 + (positionFirst - 1) + offset2);
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						//nếu số hàng của trục x lớn hơn 2 thì cần thêm điểm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisX > 2) {
							position = positionFirst - (cube->numberVertexInAxisX - 1);
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY;

							for (int k = 1; k < cube->numberVertexInAxisX - 1; k++) {
								positionVertexChoice.push_back(offset1 + (cube->numberVertexInAxisX - 2)*(position - 1) + (k - 1));
							}
						}
					}
					positionChoiceRowOrColumn.push_back({ -1,positionFirst,positionLast });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các điểm nằm ngang hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				if (j == numberVertexInRow - 1) {
					down = cube->vertexArray.at(offset1);
				}
				else
				{
					down = cube->vertexArray.at(offset1 + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					for (int k = 0; k < numberVertexInRow; k++) {
						positionVertexChoice.push_back(offset1 + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;

				}
			}
		}

	}
	break;
	case 13:
	{
		DrawCone(GL_RENDER, coneArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cone->numberLatitude; i++) {
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j<cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetNow + j);
				if (j == cone->numberLongitude - 1) {
					down = cone->vertexArray.at(offsetNow);
				}
				else
				{
					down = cone->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cone->numberLongitude; k++) {
						positionVertexChoice.push_back(offsetNow + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cone->numberLatitude; i++) {
			offsetLast = (i - 1)*cone->numberLongitude;
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j < cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetLast + j);
				down = cone->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cone->numberLatitude; k++) {
						positionVertexChoice.push_back(k*cone->numberLongitude + j);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ -1,j,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
	}
	break;
	case 14:
	{
		DrawCylinder(GL_RENDER, cylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						positionVertexChoice.push_back(offsetNow + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						positionVertexChoice.push_back(k*cylinder->numberLongitude + j);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ -1,j,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
	}
	break;
	case 16:
	{
		DrawEmptyCylinder(GL_RENDER, emptyCylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						positionVertexChoice.push_back(offsetNow + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						positionVertexChoice.push_back(k*cylinder->numberLongitude + j);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ -1,j,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
	}
	break;
	case 19:
	{
		DrawObjectCustom0(GL_RENDER, objectCustom0Array, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < object->numberLatitude; i++) {
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j<object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetNow + j);
				if (j == object->numberLongitude - 1) {
					down = object->vertexArray.at(offsetNow);
				}
				else
				{
					down = object->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < object->numberLongitude; k++) {
						positionVertexChoice.push_back(offsetNow + k);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ i,-1,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1)*object->numberLongitude;
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j < object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetLast + j);
				down = object->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < object->numberLatitude; k++) {
						positionVertexChoice.push_back(k*object->numberLongitude + j);
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionChoiceRowOrColumn.push_back({ -1,j,-1 });

					//nếu chưa xóa các chuỗi vertex được chọn trước đó thì phải kiểm tra xem có bị trùng không
					if (!isClearItemBefore) {
						clearSamePositionRowOrColumn(positionChoiceRowOrColumn);
						clearSamePoints(positionVertexChoice);
					}
					return;
				}
			}
		}
	}
	break;
	default:
		break;
	}

}

//kiểm tra xem có thể xóa các chuỗi vertex vào trong hình đang được chọn
void checkToDeleteRowVertexInObject(vector<itemChoice> itemsChoice, int x, int y, bool isMove,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<point> &vertexToDrawRectangle, vector<point> &vertexToDrawRectangleSymmetry,
	itemTextureObject itemTexture, PositionRowOrColumn &positionDeleteRowOrColumn,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;

	int offsetLast = 0, offsetNow = 0;
	float distanceUpToPoint, distanceDownToPoint, distanceUpToDown;
	point up, down, poi;

	//xóa hết độ sâu vè vẽ lại chỉ các hình để lấy độ sâu
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);

	int elementCheck, numberSymmetry, numberItemSymmetry;
	bool isHaveSymmetryVertices = false, isHaveSymmetryObjects = false;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectsCheck;

	//xóa đi các vertex vẽ hình chữ nhật để thêm lại
	vertexToDrawRectangle.clear();
	itemChoice item = itemsChoice.at(0);
	switch (item.object)
	{
	case 10:
	{
		DrawSphere(GL_RENDER, sphereArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < sphere->numberLatitude; i++) {
			offsetLast = (i - 1)*sphere->numberLongitude;
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j < sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetLast + j);
				down = sphere->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != j) {
						return;
					}
					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < sphere->numberLatitude; k++) {
						vertexToDrawRectangle.push_back(sphere->vertexArray.at(k*sphere->numberLongitude + j));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						for (int k = 0; k < sphere->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(sphere->vertexArray.at(k*sphere->numberLongitude + elementCheck));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < sphere->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(sphere->vertexArray.at(k*sphere->numberLongitude + j));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa các dãy vertex
					positionDeleteRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < sphere->numberLatitude; i++) {
			offsetNow = i*sphere->numberLongitude;
			for (int j = 0; j<sphere->numberLongitude; j++) {
				up = sphere->vertexArray.at(offsetNow + j);
				if (j == sphere->numberLongitude - 1) {
					down = sphere->vertexArray.at(offsetNow);
				}
				else
				{
					down = sphere->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionRow != i) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < sphere->numberLongitude; k++) {
						vertexToDrawRectangle.push_back(sphere->vertexArray.at(offsetNow + k));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetNow = elementCheck*sphere->numberLongitude;
						for (int k = 0; k < sphere->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(sphere->vertexArray.at(offsetNow + k));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							sphere = sphereArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < sphere->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(sphere->vertexArray.at(offsetNow + k));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa các dãy
					positionDeleteRowOrColumn.positionRow = i;
					return;
				}
			}
		}
	}
	break;
	case 11:
	{
		DrawCube(GL_RENDER, cubeArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		//kiểm tra xem có chọn trúng các điểm nằm dọc hình hộp không
		//biến thông báo số hàng của cube
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2,
			offset1, offset2;
		//kiểm tra các điểm nằm dọc hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				down = cube->vertexArray.at(offset2 + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra tất cả các điểm nằm dọc vị trí này

					//tìm ra điểm đối diện của điểm được chọn

					int startZ1 = cube->numberVertexInAxisX - 1,
						startX2 = startZ1 + cube->numberVertexInAxisZ - 1,
						startZ2 = startX2 + cube->numberVertexInAxisX - 1, pointOpposite, position;
					//vị trí theo thứ tự trước sau hay phải sang trái
					int positionFirst = -1, positionLast = -1;

					//đối với việc delete chuỗi vertex thì không cho phép chọn hàng ngoài
					//kiểm tra xem j nằm ở hàng nào
					if (j < startZ1 && j > 0) {
						pointOpposite = j + (startZ1 - j - 1) + cube->numberVertexInAxisZ + (startZ1 - j);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j > startZ1 && j<startX2)
					{
						pointOpposite = j + (startX2 - j - 1) + cube->numberVertexInAxisX + (startX2 - j);
						positionFirst = j;
						positionLast = pointOpposite;
					}
					else if (j > startX2 && j <startZ2)
					{
						pointOpposite = j - ((j - startX2) + cube->numberVertexInAxisZ + (j - startX2 - 1));
						positionFirst = pointOpposite;
						positionLast = j;
					}
					else if (j > startZ2 && j < numberVertexInRow)
					{
						pointOpposite = j - ((j - startZ2) + cube->numberVertexInAxisX + (j - startZ2 - 1));
						positionFirst = pointOpposite;
						positionLast = j;
					}

					//nếu chọn 1 trong các chuỗi vertex ở rìa ngoài thì hủy không cho lấy nữa
					if (positionFirst == -1) {
						return;
					}
					//nếu đang ở chế độ dịch chuyển vùng thêm thì k0 được thay đổi vị thêm,chỉ được di chuyển trong phạm
					//vi đó thôi
					if (isMove && positionDeleteRowOrColumn.positionColumn != positionFirst) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cube->numberVertexInAxisY; k++) {
						vertexToDrawRectangle.push_back(cube->vertexArray.at(k*numberVertexInRow + positionFirst));
					}

					//tìm các điểm ở nắp dưới(các điểm ở phía trong nếu có)

					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = 1; k < cube->numberVertexInAxisZ - 1; k++) {
								//nếu điểm được chọn là điểm đầu tiên hay cuối cùng thì sẽ lấy các điểm 
								//khác với các vị trí khác nằm ở giữa
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);
								vertexToDrawRectangle.push_back(cube->vertexArray.at(offset1 + (positionFirst - 1) + offset2));
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						//nếu số hàng của trục x lớn hơn 2 thì cần thêm điểm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisX > 2) {
							position = positionFirst - (cube->numberVertexInAxisX - 1);

							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY + ((cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2));
							//ví trí đầu tiên của đỉnh ở vòng ngoài phía dưới cùng
							int offset3 = numberVertexInRow*(cube->numberVertexInAxisY - 1);

							for (int k = cube->numberVertexInAxisX - 2; k >= 1; k--) {
								vertexToDrawRectangle.push_back(cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)
									* (position - 1) + (k - 1)));
							}
						}
					}

					//tìm các điểm nằm nằm trên các hàng đối diện

					for (int k = cube->numberVertexInAxisY - 1; k >= 0; k--) {
						vertexToDrawRectangle.push_back(cube->vertexArray.at(k*numberVertexInRow + positionLast));
					}

					//tìm các điểm ở nắp trên
					//nếu điểm được chọn nằm ở trục x
					if (positionFirst < startZ1) {
						//nếu số hàng của trục z lớn hơn 2 là có điểm cần phải thêm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisZ > 2) {
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía trên)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY;

							for (int k = cube->numberVertexInAxisZ - 2; k >= 1; k--) {
								offset2 = (cube->numberVertexInAxisX - 2)*(k - 1);
								vertexToDrawRectangle.push_back(cube->vertexArray.at(offset1 + (positionFirst - 1) + offset2));
							}
						}
					}
					//nếu điểm được chọn nằm ở trục z
					else
					{
						//nếu số hàng của trục x lớn hơn 2 thì cần thêm điểm(tất nhiên là nếu điểm chọn
						//không nằm ở đầu,hay cuối dãy chọn vì đó là các điểm thuộc vòng ngoài)
						if (cube->numberVertexInAxisX > 2) {
							position = positionFirst - (cube->numberVertexInAxisX - 1);
							//vị trí đầu tiên của chuỗi vertex phía trong(mặt phía dưới)
							offset1 = numberVertexInRow*cube->numberVertexInAxisY;

							for (int k = 1; k < cube->numberVertexInAxisX - 1; k++) {
								vertexToDrawRectangle.push_back(cube->vertexArray.at(offset1 + (cube->numberVertexInAxisX - 2)*(position - 1) + (k - 1)));
							}
						}
					}
					positionDeleteRowOrColumn.positionColumn = positionFirst;
					positionDeleteRowOrColumn.positionColumnOpposite = positionLast;
					return;
				}
			}
		}
		//kiểm tra các điểm nằm ngang hình hộp
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			for (int j = 0; j < numberVertexInRow; j++) {
				up = cube->vertexArray.at(offset1 + j);
				if (j == numberVertexInRow - 1) {
					down = cube->vertexArray.at(offset1);
				}
				else
				{
					down = cube->vertexArray.at(offset1 + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != i) {
						return;
					}

					for (int k = 0; k < numberVertexInRow; k++) {
						vertexToDrawRectangle.push_back(cube->vertexArray.at(offset1 + k));
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionRow = i;
					return;

				}
			}
		}

	}
	break;
	case 13:
	{
		DrawCone(GL_RENDER, coneArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cone->numberLatitude; i++) {
			offsetLast = (i - 1)*cone->numberLongitude;
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j < cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetLast + j);
				down = cone->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != j) {
						return;
					}
					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cone->numberLatitude; k++) {
						vertexToDrawRectangle.push_back(cone->vertexArray.at(k*cone->numberLongitude + j));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}

					//nếu tìm được
					if (isHaveSymmetryVertices) {
						for (int k = 0; k < cone->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cone->vertexArray.at(k*cone->numberLongitude + elementCheck));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cone = coneArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cone = coneArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cone->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cone->vertexArray.at(k*cone->numberLongitude + j));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cone->numberLatitude; i++) {
			offsetNow = i*cone->numberLongitude;
			for (int j = 0; j<cone->numberLongitude; j++) {
				up = cone->vertexArray.at(offsetNow + j);
				if (j == cone->numberLongitude - 1) {
					down = cone->vertexArray.at(offsetNow);
				}
				else
				{
					down = cone->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionRow != i) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cone->numberLongitude; k++) {
						vertexToDrawRectangle.push_back(cone->vertexArray.at(offsetNow + k));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetNow = elementCheck*cone->numberLongitude;
						for (int k = 0; k < cone->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cone->vertexArray.at(offsetNow + k));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cone = coneArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cone = coneArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cone->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cone->vertexArray.at(offsetNow + k));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionRow = i;
					return;
				}
			}
		}
	}
	break;
	case 14:
	{
		DrawCylinder(GL_RENDER, cylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != j) {
						return;
					}
					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						vertexToDrawRectangle.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + j));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + elementCheck));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cylinder->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + j));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionRow != i) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						vertexToDrawRectangle.push_back(cylinder->vertexArray.at(offsetNow + k));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetNow = elementCheck*cylinder->numberLongitude;
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(offsetNow + k));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = cylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cylinder->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(offsetNow + k));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionRow = i;
					return;
				}
			}
		}
	}
	break;
	case 16:
	{
		DrawEmptyCylinder(GL_RENDER, emptyCylinderArray, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < cylinder->numberLatitude; i++) {
			offsetLast = (i - 1)*cylinder->numberLongitude;
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j < cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetLast + j);
				down = cylinder->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != j) {
						return;
					}
					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < cylinder->numberLatitude; k++) {
						vertexToDrawRectangle.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + j));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						for (int k = 0; k < cylinder->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + elementCheck));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cylinder->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(k*cylinder->numberLongitude + j));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < cylinder->numberLatitude; i++) {
			offsetNow = i*cylinder->numberLongitude;
			for (int j = 0; j<cylinder->numberLongitude; j++) {
				up = cylinder->vertexArray.at(offsetNow + j);
				if (j == cylinder->numberLongitude - 1) {
					down = cylinder->vertexArray.at(offsetNow);
				}
				else
				{
					down = cylinder->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionRow != i) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < cylinder->numberLongitude; k++) {
						vertexToDrawRectangle.push_back(cylinder->vertexArray.at(offsetNow + k));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetNow = elementCheck*cylinder->numberLongitude;
						for (int k = 0; k < cylinder->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(offsetNow + k));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							cylinder = emptyCylinderArray.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < cylinder->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(cylinder->vertexArray.at(offsetNow + k));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionRow = i;
					return;
				}
			}
		}
	}
	break;
	case 19:
	{
		DrawObjectCustom0(GL_RENDER, objectCustom0Array, itemTexture, false, 1, itemsChoice);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		poi = { (float)xDown,(float)yDown,(float)zDown };

		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		//kiểm tra các hàng dọc xem có chọn trúng hàng dọc nào không
		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1)*object->numberLongitude;
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j < object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetLast + j);
				down = object->vertexArray.at(offsetNow + j);
				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {
					//khi đã xác định điểm này nằm giữa 2 điểm này rồi thì lấy ra các điểm trên cùng hàng dọc đó

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionColumn != j) {
						return;
					}
					//khi đã tìm được vị trí trên hàng dọc,thì load tất cả hàng ngang để lấy tất cả các điểm có vị trí đó
					//trên hàng dọc
					for (int k = 0; k < object->numberLatitude; k++) {
						vertexToDrawRectangle.push_back(object->vertexArray.at(k*object->numberLongitude + j));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionColumn == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionColumn;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						for (int k = 0; k < object->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(object->vertexArray.at(k*object->numberLongitude + elementCheck));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < object->numberLatitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(object->vertexArray.at(k*object->numberLongitude + j));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionColumn = j;
					return;
				}
			}
		}
		//kiểm tra các hàng ngang xem có chọn trúng hàng ngang nào không
		for (int i = 0; i < object->numberLatitude; i++) {
			offsetNow = i*object->numberLongitude;
			for (int j = 0; j<object->numberLongitude; j++) {
				up = object->vertexArray.at(offsetNow + j);
				if (j == object->numberLongitude - 1) {
					down = object->vertexArray.at(offsetNow);
				}
				else
				{
					down = object->vertexArray.at(offsetNow + j + 1);
				}

				distanceUpToPoint = distanceTwoPoint(up, poi);
				distanceDownToPoint = distanceTwoPoint(down, poi);
				distanceUpToDown = distanceTwoPoint(up, down);
				//xem tổng của khoảng cách từ điểm tới đỉnh 1 cộng khoảng cách từ đỉnh tới điểm 2 không
				//nếu có thì đó là điểm cần tìm,cho phép chênh lệch 0.02
				if (distanceUpToDown <= distanceUpToPoint + distanceDownToPoint + 0.01 &&
					distanceUpToDown >= distanceUpToPoint + distanceDownToPoint - 0.01) {

					//việc dịch chuyển này dùng để hủy xóa dãy vertex cần xóa
					if (isMove && positionDeleteRowOrColumn.positionRow != i) {
						return;
					}

					//tìm ra các điểm nằm trên các hàng hiện tại tại cùng vị trí nhấn
					for (int k = 0; k < object->numberLongitude; k++) {
						vertexToDrawRectangle.push_back(object->vertexArray.at(offsetNow + k));
					}
					//kiểm tra đối xứng
					numberSymmetry = symmetryVertices.size();
					for (int m = 0; m < numberSymmetry; m++) {
						symmetryVerticesCheck = symmetryVertices.at(m);
						//kiểm tra xem item này của symmetryVertex có chứa thông tin của object này không
						if (symmetryVerticesCheck.object == item.object &&
							symmetryVerticesCheck.positionInArray == item.positionOfChoice) {

							numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
								symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
							//kiểm tra xem trong chuỗi này có vị trí thêm không
							for (int n = 0; n < numberItemSymmetry; n++) {
								if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC2.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
								else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == i) {
									elementCheck = symmetryVerticesCheck.positionROrC1.at(n).positionRow;
									isHaveSymmetryVertices = true;
									break;
								}
							}
							break;
						}
					}
					//nếu không tìm thấy thông tin trong symmetryVertices thì tìm thông tin trong symmetryObject
					if (!isHaveSymmetryVertices) {
						numberSymmetry = symmetryObjects.size();
						for (int m = 0; m < numberSymmetry; m++) {
							symmetryObjectsCheck = symmetryObjects.at(m);
							if (symmetryObjectsCheck.object1 == item.object &&
								(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
								isHaveSymmetryObjects = true;
								break;
							}
						}
					}
					//nếu tìm được
					if (isHaveSymmetryVertices) {
						offsetNow = elementCheck*object->numberLongitude;
						for (int k = 0; k < object->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(object->vertexArray.at(offsetNow + k));
						}
					}
					else if (isHaveSymmetryObjects) {
						if (item.positionOfChoice == symmetryObjectsCheck.positionInArray1) {
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray2);
						}
						else
						{
							object = objectCustom0Array.at(symmetryObjectsCheck.positionInArray1);
						}

						for (int k = 0; k < object->numberLongitude; k++) {
							vertexToDrawRectangleSymmetry.push_back(object->vertexArray.at(offsetNow + k));
						}
					}
					//đặt vị trí hàng ngang để khi thả chuột xóa dãy vertex
					positionDeleteRowOrColumn.positionRow = i;
					return;
				}
			}
		}
	}
	break;
	default:
		break;
	}
}
//hàm kiểm tra 1 điểm có nằm trong tam giác được tạo bởi 3 điểm không
bool checkPointInTriangle(point pointTouch, point pointTria0, point pointTria1, point pointTria2) {
	//lấy giá trị của 3 góc tại điểm p
	float degree0, degree1, degree2, degreeTotal;
	//tính tổng giá trị của 3 góc nếu bằng 360 nghĩa là p nằm trong tam giác được tạo
	//bởi 3 đỉnh này
	degree0 = CaculatorDegreesFrom3Point(pointTria0, pointTouch, pointTria1);
	degree1 = CaculatorDegreesFrom3Point(pointTria0, pointTouch, pointTria2);
	degree2 = CaculatorDegreesFrom3Point(pointTria1, pointTouch, pointTria2);
	degreeTotal = degree0 + degree1 + degree2;
	if (degreeTotal > 179 && degreeTotal < 181) {
		return true;
	}
	else
	{
		return false;
	}

}
//hàm kiểm tra xem khuôn mặt nào được chọn
void checkToChoiceFaceInObject(itemChoice item, int x, int y, vector<int> &positionFaceChoice,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport,
	vector<TriangleStripAttribute*> triaStripArray, vector<TriangleFanAttribute*> triaFanArray,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<ObjectCustom0Attribute*> objectCustom0Array) {

	GLdouble x3D = 0.0, y3D = 0.0, z3D = 0.0;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &x3D, &y3D, &z3D);

	//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		positionFaceChoice.clear();
	}

	point v0, v1, v2;
	bool isInTria;
	switch (item.object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		int numberFace = triaStrip->vertexArray.size() - 2;
		for (int i = 0; i < numberFace; i++) {
			v0 = triaStrip->vertexArray.at(i);
			v1 = triaStrip->vertexArray.at(i + 1);
			v2 = triaStrip->vertexArray.at(i + 2);
			isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
			if (isInTria) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		int numberFace = triaFan->vertexArray.size() - 1;
		v0 = triaFan->vertexArray.at(0);
		for (int i = 1; i < numberFace; i++) {
			v1 = triaFan->vertexArray.at(i);
			v2 = triaFan->vertexArray.at(i + 1);
			isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
			if (isInTria) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = sphere->numberLatitude - (sphere->degreeLatitudeLimit / (360 / sphere->numberLatitude));
		minusLongitude = sphere->numberLongitude - (sphere->degreeLongitudeLimit / (360 / sphere->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < sphere->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * sphere->numberLongitude;
			offsetNow = i * sphere->numberLongitude;
			for (int j = minusLongitude + 1; j < sphere->numberLongitude; j++) {
				v0 = sphere->vertexArray.at(offsetLast + j - 1);
				v1 = sphere->vertexArray.at(offsetNow + j - 1);
				v2 = sphere->vertexArray.at(offsetLast + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = sphere->vertexArray.at(offsetNow + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == sphere->numberLongitude - 1) {
					v0 = sphere->vertexArray.at(offsetLast + j);
					v1 = sphere->vertexArray.at(offsetNow + j);
					v2 = sphere->vertexArray.at(offsetLast);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = sphere->vertexArray.at(offsetNow);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int offsetFace = 0, offset1, offset2, offset3, numberVertexInRow;
		bool isDraw = false;

		numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
		// vẽ mặt cho hình bao quanh hình vuông
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 1; j < numberVertexInRow; j++) {
				v0 = cube->vertexArray.at(offset1 + j - 1);
				v1 = cube->vertexArray.at(offset2 + j - 1);
				v2 = cube->vertexArray.at(offset1 + j);
				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

				v0 = cube->vertexArray.at(offset2 + j);
				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

				//nếu là cặp đỉnh cuối cùng thì vẽ nối với cặp đỉnh đầu tiên
				if (j == numberVertexInRow - 1) {
					v1 = cube->vertexArray.at(offset1);
					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v2, v0, v1);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}
					offsetFace++;

					v2 = cube->vertexArray.at(offset2);
					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v0, v2);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}
					offsetFace++;
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
				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

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
				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v2, v1, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;
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
				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v2, v1, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

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

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cone->numberLatitude - (cone->degreeLatitudeLimit / (360 / cone->numberLatitude));
		minusLongitude = cone->numberLongitude - (cone->degreeLongitudeLimit / (360 / cone->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cone->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cone->numberLongitude;
			offsetNow = i * cone->numberLongitude;
			for (int j = minusLongitude + 1; j < cone->numberLongitude; j++) {
				v0 = cone->vertexArray.at(offsetLast + j - 1);
				v1 = cone->vertexArray.at(offsetNow + j - 1);
				v2 = cone->vertexArray.at(offsetLast + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cone->vertexArray.at(offsetNow + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cone->numberLongitude - 1) {
					v0 = cone->vertexArray.at(offsetLast + j);
					v1 = cone->vertexArray.at(offsetNow + j);
					v2 = cone->vertexArray.at(offsetLast);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cone->vertexArray.at(offsetNow);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
				v0 = cylinder->vertexArray.at(offsetLast + j - 1);
				v1 = cylinder->vertexArray.at(offsetNow + j - 1);
				v2 = cylinder->vertexArray.at(offsetLast + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cylinder->vertexArray.at(offsetNow + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					v0 = cylinder->vertexArray.at(offsetLast + j);
					v1 = cylinder->vertexArray.at(offsetNow + j);
					v2 = cylinder->vertexArray.at(offsetLast);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cylinder->vertexArray.at(offsetNow);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
				v0 = cylinder->vertexArray.at(offsetLast + j - 1);
				v1 = cylinder->vertexArray.at(offsetNow + j - 1);
				v2 = cylinder->vertexArray.at(offsetLast + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cylinder->vertexArray.at(offsetNow + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					v0 = cylinder->vertexArray.at(offsetLast + j);
					v1 = cylinder->vertexArray.at(offsetNow + j);
					v2 = cylinder->vertexArray.at(offsetLast);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cylinder->vertexArray.at(offsetNow);

					isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
					if (isInTria) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		int numberFace = torus->vertexArray.size() - 2;
		for (int i = 0; i < numberFace; i++) {
			v0 = torus->vertexArray.at(i);
			v1 = torus->vertexArray.at(i + 1);
			v2 = torus->vertexArray.at(i + 2);
			isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
			if (isInTria) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1) * object->numberLongitude;
			offsetNow = i * object->numberLongitude;
			for (int j = 1; j < object->numberLongitude; j++) {
				v0 = object->vertexArray.at(offsetLast + j - 1);
				v1 = object->vertexArray.at(offsetNow + j - 1);
				v2 = object->vertexArray.at(offsetLast + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v0, v1, v2);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = object->vertexArray.at(offsetNow + j);

				isInTria = checkPointInTriangle({ (float)x3D,(float)y3D,(float)z3D }, v1, v2, v0);
				if (isInTria) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
			}
		}
	}
			 break;
	default:
		break;
	}
	//xóa các mặt chọn trùng
	clearSamePoints(positionFaceChoice);
}

//hàm xóa chuỗi vào vị trí chọn và cả vị trí đối xứng(nếu có)
//hàm nay dùng cho các hình tương tự sphere
void deleteVerticesAndVerticesSymmetryInRowOrColumn(int &numberLongitude, int &numberLatitude,
	int positionFoundItemDelete,
	PositionRowOrColumn positionDeleteRowOrColumn, PositionRowOrColumn positionDeleteRowOrColumnSymmetry,
	vector<point> &vertexArray,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	SymmetryVertices &symmetryVerticesNow) {

	int numberElement;

	if (positionDeleteRowOrColumn.positionRow != -1) {
		//xóa phần tử tại vị trí tìm thấy trong cả 2 mảng symmetry
		symmetryVerticesNow.positionROrC1.erase(symmetryVerticesNow.positionROrC1.begin() + positionFoundItemDelete);
		symmetryVerticesNow.positionROrC2.erase(symmetryVerticesNow.positionROrC2.begin() + positionFoundItemDelete);

		//kiểm tra xem cái nào lớn hơn để thêm tương ứng
		if (positionDeleteRowOrColumnSymmetry.positionRow > positionDeleteRowOrColumn.positionRow) {
			//do đây là cùng 1 hàng ngang nên cứ xóa phần tử đầu tiên là các phần tử sau sẽ trượt dần lên
			for (int i = 0; i < numberLongitude; i++) {
				vertexArray.erase(vertexArray.begin() + positionDeleteRowOrColumnSymmetry.positionRow*numberLongitude);
			}
			for (int i = 0; i < numberLongitude; i++) {
				vertexArray.erase(vertexArray.begin() + positionDeleteRowOrColumn.positionRow*numberLongitude);
			}

			//nếu itemSymmetry lớn hơn thì lùi giá trị của itemSymmetry
			positionDeleteRowOrColumnSymmetry.positionRow--;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//do itemSymmetry lớn hơn nên so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow--;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow > positionDeleteRowOrColumn.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow--;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow--;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow > positionDeleteRowOrColumn.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow--;
				}
			}
		}
		else
		{
			//do đây là cùng 1 hàng ngang nên cứ xóa phần tử đầu tiên là các phần tử sau sẽ trượt dần lên
			for (int i = 0; i < numberLongitude; i++) {
				vertexArray.erase(vertexArray.begin() + positionDeleteRowOrColumn.positionRow*numberLongitude);
			}
			for (int i = 0; i < numberLongitude; i++) {
				vertexArray.erase(vertexArray.begin() + positionDeleteRowOrColumnSymmetry.positionRow*numberLongitude);
			}

			//nếu positionDeleteRowOrColumn.positionRow lớn hơn thì lùi giá trị của positionDeleteRowOrColumn.positionRow
			positionDeleteRowOrColumn.positionRow--;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//do positionDeleteRowOrColumn.positionRow lớn hơn nên so sánh positionDeleteRowOrColumn.positionRow trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow > positionDeleteRowOrColumn.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow--;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionRow > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionRow--;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow > positionDeleteRowOrColumn.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow--;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionRow > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionRow--;
				}
			}
		}

		//giảm giá trị số vertex trên hàng ngang là 2
		numberLatitude -= 2;

	}
	else if (positionDeleteRowOrColumn.positionColumn != -1) {
		//xóa phần tử tại vị trí tìm thấy trong cả 2 mảng symmetry
		symmetryVerticesNow.positionROrC1.erase(symmetryVerticesNow.positionROrC1.begin() + positionFoundItemDelete);
		symmetryVerticesNow.positionROrC2.erase(symmetryVerticesNow.positionROrC2.begin() + positionFoundItemDelete);

		//kiểm tra xem cái nào lớn hơn để thêm tương ứng
		if (positionDeleteRowOrColumnSymmetry.positionRow > positionDeleteRowOrColumn.positionColumn) {
			int offset = 0;
			//phải xóa từ phần tử dưới cùng lên phần tử đầu tiên
			for (int i = numberLatitude - 1; i >= 0; i--) {
				offset = i*numberLongitude + positionDeleteRowOrColumnSymmetry.positionRow;
				vertexArray.erase(vertexArray.begin() + offset);
				offset = i*numberLongitude + positionDeleteRowOrColumn.positionColumn;
				vertexArray.erase(vertexArray.begin() + offset);
			}

			//nếu itemSymmetry lớn hơn thì lùi giá trị của itemSymmetry
			positionDeleteRowOrColumnSymmetry.positionRow--;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//do itemSymmetry lớn hơn nên so sánh itemSymmetry trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn--;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn > positionDeleteRowOrColumn.positionColumn) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn--;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn--;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn > positionDeleteRowOrColumn.positionColumn) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn--;
				}
			}
		}
		else
		{
			int offset = 0;
			//phải xóa từ phần tử dưới cùng lên phần tử đầu tiên
			for (int i = numberLatitude - 1; i >= 0; i--) {
				offset = i*numberLongitude + positionDeleteRowOrColumn.positionColumn;
				vertexArray.erase(vertexArray.begin() + offset);
				offset = i*numberLongitude + positionDeleteRowOrColumnSymmetry.positionRow;
				vertexArray.erase(vertexArray.begin() + offset);
			}

			//nếu positionDeleteRowOrColumn.positionColumn lớn hơn thì lùi giá trị của positionDeleteRowOrColumn.positionColumn
			positionDeleteRowOrColumn.positionColumn--;

			numberElement = symmetryVerticesNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//do positionDeleteRowOrColumn.positionColumn lớn hơn nên so sánh positionDeleteRowOrColumn.positionColumn trước
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn > positionDeleteRowOrColumn.positionColumn) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn--;
				}
				if (symmetryVerticesNow.positionROrC1.at(i).positionColumn > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC1.at(i).positionColumn--;
				}
			}
			numberElement = symmetryVerticesNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn > positionDeleteRowOrColumn.positionColumn) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn--;
				}
				if (symmetryVerticesNow.positionROrC2.at(i).positionColumn > positionDeleteRowOrColumnSymmetry.positionRow) {
					symmetryVerticesNow.positionROrC2.at(i).positionColumn--;
				}
			}
		}

		//giảm giá trị số vertex trên hàng ngang là 2
		numberLongitude -= 2;
	}
}
void deleteVerticesInRowOrColumn(int &numberLongitude, int &numberLatitude,
	PositionRowOrColumn positionDeleteRowOrColumn,
	vector<point> &vertexArray,
	vector<point> vertexToDrawRectangle) {
	if (positionDeleteRowOrColumn.positionRow != -1) {
		//do đây là cùng 1 hàng ngang nên cứ xóa phần tử đầu tiên là các phần tử sau sẽ trượt dần lên
		for (int i = 0; i < numberLongitude; i++) {
			vertexArray.erase(vertexArray.begin() + positionDeleteRowOrColumn.positionRow*numberLongitude);
		}
		//giảm giá trị số vertex trên 1 hàng dọc là 1
		numberLatitude--;
	}
	else
	{
		int offset = 0;
		//phải xóa từ phần tử dưới cùng lên phần tử đầu tiên
		for (int i = numberLatitude - 1; i >= 0; i--) {
			offset = i*numberLongitude + positionDeleteRowOrColumn.positionColumn;
			vertexArray.erase(vertexArray.begin() + offset);
		}
		//giảm giá trị số vertex trên hàng ngang lên 1
		numberLongitude--;
	}
}
//hàm để sửa lỗi khi xóa một hàng hay cột mà không có đối xứng,trong 1 object có thông tin trong symmetryVertices
void fixErrorWhenDeleteItemNotHaveItemSymmetry(PositionRowOrColumn positionDeleteRowOrColumn,
	SymmetryVertices &symmetryVerticesNow) {
	vector<PositionRowOrColumn> *positionROrC;
	int numberElement;

	if (positionDeleteRowOrColumn.positionRow != -1) {
		positionROrC = &symmetryVerticesNow.positionROrC1;
		numberElement = positionROrC->size();
		for (int i = 0; i<numberElement; i++) {
			if (positionROrC->at(i).positionRow>positionDeleteRowOrColumn.positionRow) {
				positionROrC->at(i).positionRow--;
			}
		}
		positionROrC = &symmetryVerticesNow.positionROrC2;
		numberElement = positionROrC->size();
		for (int i = 0; i<numberElement; i++) {
			if (positionROrC->at(i).positionRow>positionDeleteRowOrColumn.positionRow) {
				positionROrC->at(i).positionRow--;
			}
		}
	}
	else
	{
		positionROrC = &symmetryVerticesNow.positionROrC1;
		numberElement = positionROrC->size();
		for (int i = 0; i<numberElement; i++) {
			if (positionROrC->at(i).positionColumn>positionDeleteRowOrColumn.positionColumn) {
				positionROrC->at(i).positionColumn--;
			}
		}
		positionROrC = &symmetryVerticesNow.positionROrC2;
		numberElement = positionROrC->size();
		for (int i = 0; i<numberElement; i++) {
			if (positionROrC->at(i).positionColumn>positionDeleteRowOrColumn.positionColumn) {
				positionROrC->at(i).positionColumn--;
			}
		}
	}
}
//hàm xóa chuỗi vertex
void deleteRowVertexInObject(vector<itemChoice> itemsChoice, PositionRowOrColumn positionDeleteRowOrColumn,
	vector<point> vertexToDrawRectangle, vector<point> vertexToDrawRectangleSymmetry,
	vector<SymmetryVertices> &symmetryVertices, vector<SymmetryObjects> &symmetryObjects,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	
	itemChoice item = itemsChoice.at(0);

	bool isHaveSymmetryVertices = false, isHaveSymmetryObjects = false;
	int numberSymmetry, positionSymmetryVertices = -1, numberItemSymmetry, positionFoundItemDelete;
	PositionRowOrColumn positionDeleteRowOrColumnSymmetry;

	SymmetryObjects symmetryObjectCheck;
	SymmetryVertices symmetryVerticesCheck;

	//đối với việc thêm hay xóa các chuỗi vertices thì
	//dù là đang ở chế độ đối xứng hay không cũng phải kiểm tra xem hình hiện tại có 
	//thông tin trong symmetryVertices không,nếu có thì có 2 trường hợp chỉ xóa 1 cụm đỉnh là 
	//1 đang tắt chế độ symmetry
	//2 chọn trúng cụm đỉnh không có thông tin trong đối xứng vertex
	//đối với cả 2 trường hợp này đều phải cần tính toán lại các vertex tương ứng với các hàng hay cột trong symmetryVertices
	//và xóa đi hàng hay cột trong symmetry nếu hàng hay cột bị xóa mà có thông tin trong symmetryVertices

	numberSymmetry = symmetryVertices.size();
	for (int m = 0; m < numberSymmetry; m++) {
		symmetryVerticesCheck = symmetryVertices.at(m);
		//đầu tiên kiểm tra xem đối tượng được chọn có được lưu trữ trong item hiện tại không
		if (symmetryVerticesCheck.object == item.object &&
			symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
			positionSymmetryVertices = m;

			numberItemSymmetry = symmetryVerticesCheck.positionROrC1.size() < symmetryVerticesCheck.positionROrC2.size() ?
				symmetryVerticesCheck.positionROrC1.size() : symmetryVerticesCheck.positionROrC2.size();
			//kiểm tra xem trong chuỗi này có vị trí thêm không
			for (int n = 0; n < numberItemSymmetry; n++) {
				if (symmetryVerticesCheck.positionROrC1.at(n).positionRow == positionDeleteRowOrColumn.positionRow &&
					symmetryVerticesCheck.positionROrC1.at(n).positionColumn == positionDeleteRowOrColumn.positionColumn) {

					positionDeleteRowOrColumnSymmetry = symmetryVerticesCheck.positionROrC2.at(n);
					//vị trí tìm thấy item để delete
					positionFoundItemDelete = n;
					isHaveSymmetryVertices = true;
					break;
				}
				else if (symmetryVerticesCheck.positionROrC2.at(n).positionRow == positionDeleteRowOrColumn.positionRow &&
					symmetryVerticesCheck.positionROrC2.at(n).positionColumn == positionDeleteRowOrColumn.positionColumn) {

					positionDeleteRowOrColumnSymmetry = symmetryVerticesCheck.positionROrC1.at(n);
					//vị trí tìm thấy item để delete
					positionFoundItemDelete = n;
					isHaveSymmetryVertices = true;
					break;
				}
			}

			break;
		}
	}
	//nếu object hiện tại không có thông tin trong symmetryVertices
	if (!isHaveSymmetryVertices) {
		//đầu tiên kiểm tra xem object được chọn có thong tin trong symmetryObject không
		numberSymmetry = symmetryObjects.size();
		for (int i = 0; i < numberSymmetry; i++) {
			symmetryObjectCheck = symmetryObjects.at(i);
			if (symmetryObjectCheck.object1 == item.object &&
				(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
					symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
				isHaveSymmetryObjects = true;
				break;
			}
		}
	}
	

	switch (item.object)
	{
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			deleteVerticesAndVerticesSymmetryInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionFoundItemDelete,
				positionDeleteRowOrColumn, positionDeleteRowOrColumnSymmetry,
				sphere->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);

		}
		else if (isHaveSymmetryObjects) {
			//đầu tiên xóa cụm vertex của object đang chọn
			deleteVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionDeleteRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);

			//tiếp theo xóa cụm vertex của object đối xứng
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);
			}
			deleteVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionDeleteRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
		}
		else
		{
			deleteVerticesInRowOrColumn(sphere->numberLongitude, sphere->numberLatitude,
				positionDeleteRowOrColumn,
				sphere->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
		}
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
		//xóa các vertex ngang
		if (positionDeleteRowOrColumn.positionRow != -1) {
			//do đây là cùng 1 hàng ngang nên cứ xóa phần tử đầu tiên là các phần tử sau sẽ trượt dần lên
			for (int i = 0; i < numberVertexInRow; i++) {
				cube->vertexArray.erase(cube->vertexArray.begin() + positionDeleteRowOrColumn.positionRow * numberVertexInRow);
			}
			//giảm giá trị số vertex trên 1 hàng dọc là 1
			cube->numberVertexInAxisY--;
		}
		//xóa các vertex dọc
		else if (positionDeleteRowOrColumn.positionColumn != -1) {
			int numberVertexAddInUpOrDown, offset;
			bool isAddInAxisX = false;
			//tính số vertex xóa ở mặt dưới hoặc trên(vì có thể thêm theo chiều x hoặc z nên sẽ có 2 
			//giá trị khác nhau)
			if (positionDeleteRowOrColumn.positionColumn < cube->numberVertexInAxisX - 1) {
				numberVertexAddInUpOrDown = cube->numberVertexInAxisZ - 2;
				isAddInAxisX = true;
			}
			else
			{
				numberVertexAddInUpOrDown = cube->numberVertexInAxisX - 2;
				isAddInAxisX = false;
			}
			//phải xóa theo thứ tự từ các đỉnh sau cùng ra trước,tức là 
			//từ vertexDown,vertexUp,vertexAroundBehind,vertexAroundFront
			//riêng vertexAroundBehind và vertexAroundFront là so le nhau nên thêm cùng nhau,
			//còn 2 vertex kia thì sẽ thêm riêng biệt

			//xóa ở vertex down

			//nếu xóa ở trục x
			if (isAddInAxisX) {
				//nếu số hàng trên trục z>2 thì mới cần thêm
				if (cube->numberVertexInAxisZ > 2) {
					//vị trí đầu tiên của các vertex phía trong của đáy dưới
					offset = numberVertexInRow*cube->numberVertexInAxisY +
						(cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2);

					for (int i = cube->numberVertexInAxisZ - 2; i >= 1; i--) {
						cube->vertexArray.erase(cube->vertexArray.begin() + offset +
							(i - 1)*(cube->numberVertexInAxisX - 2)
							+ (positionDeleteRowOrColumn.positionColumn - 1));
					}
				}
			}
			//nếu xóa ở trục z
			else
			{
				if (cube->numberVertexInAxisX > 2) {
					int position = (positionDeleteRowOrColumn.positionColumn - 1) - (cube->numberVertexInAxisX - 1);
					//vị trí đầu tiên của hàng cần thêm các vertex
					offset = numberVertexInRow * cube->numberVertexInAxisY +
						(cube->numberVertexInAxisX - 2)*(cube->numberVertexInAxisZ - 2) +
						position*(cube->numberVertexInAxisX - 2);

					for (int i = 1; i < cube->numberVertexInAxisX - 1; i++) {
						cube->vertexArray.erase(cube->vertexArray.begin() + offset);
					}
				}
			}

			//xóa ở vertex up

			//nếu xóa ở trục x
			if (isAddInAxisX) {
				//nếu số hàng trên trục z > 2 thì mới cần thêm
				if (cube->numberVertexInAxisZ > 2) {
					//vị trí đầu tiên của các vertex phía trong của đáy trên
					offset = numberVertexInRow*cube->numberVertexInAxisY;

					for (int i = cube->numberVertexInAxisZ - 2; i >= 1; i--) {
						cube->vertexArray.erase(cube->vertexArray.begin() + offset +
							(i - 1)*(cube->numberVertexInAxisX - 2)
							+ (positionDeleteRowOrColumn.positionColumn - 1));
					}
				}
			}
			//nếu xóa ở trục z
			else
			{
				if (cube->numberVertexInAxisX > 2) {
					int position = (positionDeleteRowOrColumn.positionColumn - 1) - (cube->numberVertexInAxisX - 1);
					//vị trí đầu tiên của hàng cần thêm các vertex
					offset = numberVertexInRow*cube->numberVertexInAxisY +
						position*(cube->numberVertexInAxisX - 2);

					for (int i = 1; i < cube->numberVertexInAxisX - 1; i++) {
						cube->vertexArray.erase(cube->vertexArray.begin() + offset);
					}
				}
			}

			//xóa vertex ở các vertex ở vòng ngoài
			for (int i = cube->numberVertexInAxisY - 1; i >= 0; i--) {
				//ta phải xóa từ sau ra trước thì k0 bị trôi vị trí thêm vertex
				//thêm vào hàng dọc sau hay bên phải
				cube->vertexArray.erase(cube->vertexArray.begin() + (i*numberVertexInRow)
					+ positionDeleteRowOrColumn.positionColumnOpposite);
				//add vertex vào hàng dọc trước hay bên trái
				cube->vertexArray.erase(cube->vertexArray.begin() + (i*numberVertexInRow) +
					positionDeleteRowOrColumn.positionColumn);

			}
			if (isAddInAxisX) {
				//nếu đang nhấn ở truc x thì tăng số vertex của trục x lên
				cube->numberVertexInAxisX--;
			}
			else
			{
				//nếu đang nhấn ở truc z thì tăng số vertex của trục z lên
				cube->numberVertexInAxisZ--;
			}
		}

		//tính toán lại normal vector
		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
			, cube->vertexArray, cube->normalVector);
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			deleteVerticesAndVerticesSymmetryInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionFoundItemDelete,
				positionDeleteRowOrColumn, positionDeleteRowOrColumnSymmetry,
				cone->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);

		}
		else if (isHaveSymmetryObjects) {
			//đầu tiên xóa cụm vertex của object đang chọn
			deleteVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionDeleteRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);

			//tiếp theo xóa cụm vertex của object đối xứng
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cone = coneArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cone = coneArray.at(symmetryObjectCheck.positionInArray1);
			}
			deleteVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionDeleteRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
		}
		else
		{
			deleteVerticesInRowOrColumn(cone->numberLongitude, cone->numberLatitude,
				positionDeleteRowOrColumn,
				cone->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			deleteVerticesAndVerticesSymmetryInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionFoundItemDelete,
				positionDeleteRowOrColumn, positionDeleteRowOrColumnSymmetry,
				cylinder->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

		}
		else if (isHaveSymmetryObjects) {
			//đầu tiên xóa cụm vertex của object đang chọn
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//tiếp theo xóa cụm vertex của object đối xứng
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else
		{
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			deleteVerticesAndVerticesSymmetryInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionFoundItemDelete,
				positionDeleteRowOrColumn, positionDeleteRowOrColumnSymmetry,
				cylinder->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

		}
		else if (isHaveSymmetryObjects) {
			//đầu tiên xóa cụm vertex của object đang chọn
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);

			//tiếp theo xóa cụm vertex của object đối xứng
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);
			}
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
		else
		{
			deleteVerticesInRowOrColumn(cylinder->numberLongitude, cylinder->numberLatitude,
				positionDeleteRowOrColumn,
				cylinder->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (isHaveSymmetryVertices) {
			deleteVerticesAndVerticesSymmetryInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionFoundItemDelete,
				positionDeleteRowOrColumn, positionDeleteRowOrColumnSymmetry,
				object->vertexArray,
				vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
				symmetryVertices.at(positionSymmetryVertices));
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);

		}
		else if (isHaveSymmetryObjects) {
			//đầu tiên xóa cụm vertex của object đang chọn
			deleteVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionDeleteRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);

			//tiếp theo xóa cụm vertex của object đối xứng
			if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);
			}
			else
			{
				object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);
			}
			deleteVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionDeleteRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
		}
		else
		{
			deleteVerticesInRowOrColumn(object->numberLongitude, object->numberLatitude,
				positionDeleteRowOrColumn,
				object->vertexArray,
				vertexToDrawRectangle);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
		}
	}
	break;
	default:
		break;
	}

	//nếu vật được chọn có thông tin về đối xứng vertex thì sau khi add dù có add đối xứng hay không
	//thì vẫn phải tính lại các vertex từ các row và column
	if (positionSymmetryVertices != -1) {
		//phải kiểm tra xem có phải chỉ xóa 1 cụm đỉnh không để chỉnh lại thông tin positionROrC của vật này
		//trường hợp chọn trúng cụm item không có thông tin trong đối xứng vertex
		if(!isHaveSymmetryVertices){
			//nếu xóa trúng item không có thông tin trong positionROrC thì xem xét xem có giá trị nào lớn hơn giá trị
			//này thì lùi xuống 1 giá trị
			fixErrorWhenDeleteItemNotHaveItemSymmetry(positionDeleteRowOrColumn,
				symmetryVertices.at(positionSymmetryVertices));
		}

		//sau khi đã đặt đúng các hàng theo tên thì lấy ra các vertex gán với chúng
		getVerticesFromRowOrColumn(item,
			symmetryVertices.at(positionSymmetryVertices).positionROrC1, 
			symmetryVertices.at(positionSymmetryVertices).positionVertices1,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
		getVerticesFromRowOrColumn(item,
			symmetryVertices.at(positionSymmetryVertices).positionROrC2,
			symmetryVertices.at(positionSymmetryVertices).positionVertices2,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
	}
}


//tạo ra 1 bản copy của các hình đang được chọn
void copyObjectsChoice(vector<itemChoice> &itemsChoice, vector<int> &idsUsing,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	int numberItemChoice = itemsChoice.size();
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			//lấy ra object để copy
			TriangleAttribute *triaNow = triangleArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleAttribute *triaCopy = new TriangleAttribute(triaNow);
			triaCopy->id = getIdForObject(idsUsing);
			triangleArray.push_back(triaCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 3, triaCopy->id, (int)triangleArray.size() - 1 });
		}
		break;
		case 4:
		{
			//lấy ra object để copy
			TriangleStripAttribute *triaStripNow = triaStripArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleStripAttribute *triaStripCopy = new TriangleStripAttribute(triaStripNow);
			triaStripCopy->id = getIdForObject(idsUsing);
			triaStripArray.push_back(triaStripCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 4, triaStripCopy->id, (int)triaStripArray.size() - 1 });
		}
		break;
		case 5:
		{
			//lấy ra object để copy
			TriangleFanAttribute *triaFanNow = triaFanArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleFanAttribute *triaFanCopy = new TriangleFanAttribute(triaFanNow);
			triaFanCopy->id = getIdForObject(idsUsing);
			triaFanArray.push_back(triaFanCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 5, triaFanCopy->id, (int)triaFanArray.size() - 1 });
		}
		break;
		case 10:
		{
			//lấy ra object để copy
			SphereAttribute *sphereNow = sphereArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			SphereAttribute *sphereCopy = new SphereAttribute(sphereNow);
			sphereCopy->id = getIdForObject(idsUsing);
			sphereArray.push_back(sphereCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 10, sphereCopy->id, (int)sphereArray.size() - 1 });
		}
		break;
		case 11:
		{
			//lấy ra object để copy
			CubeAttribute *cubeNow = cubeArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CubeAttribute *cubeCopy = new CubeAttribute(cubeNow);
			cubeCopy->id = getIdForObject(idsUsing);
			cubeArray.push_back(cubeCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 11, cubeCopy->id, (int)cubeArray.size() - 1 });
		}
		break;
		case 12:
		{
			//lấy ra object để copy
			CubeRoundAttribute *cubeNow = cubeRoundArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CubeRoundAttribute *cubeCopy = new CubeRoundAttribute(cubeNow);
			cubeCopy->id = getIdForObject(idsUsing);
			cubeRoundArray.push_back(cubeCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 12, cubeCopy->id, (int)cubeRoundArray.size() - 1 });
		}
		break;
		case 13:
		{
			//lấy ra object để copy
			ConeAttribute *coneNow = coneArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			ConeAttribute *coneCopy = new ConeAttribute(coneNow);
			coneCopy->id = getIdForObject(idsUsing);
			coneArray.push_back(coneCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 13, coneCopy->id, (int)coneArray.size() - 1 });
		}
		break;
		case 14:
		{
			//lấy ra object để copy
			CylinderAttribute *cylinderNow = cylinderArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CylinderAttribute *cylinderCopy = new CylinderAttribute(cylinderNow);
			cylinderCopy->id = getIdForObject(idsUsing);
			cylinderArray.push_back(cylinderCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 14, cylinderCopy->id, (int)cylinderArray.size() - 1 });
		}
		break;
		case 15:
		{
			//lấy ra object để copy
			PyramidAttribute *pyrNow = pyrArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			PyramidAttribute *pyrCopy = new PyramidAttribute(pyrNow);
			pyrCopy->id = getIdForObject(idsUsing);
			pyrArray.push_back(pyrCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 15, pyrCopy->id, (int)pyrArray.size() - 1 });
		}
		break;
		case 16:
		{
			//lấy ra object để copy
			EmptyCylinderAttribute *cylinderNow = emptyCylinderArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			EmptyCylinderAttribute *cylinderCopy = new EmptyCylinderAttribute(cylinderNow);
			cylinderCopy->id = getIdForObject(idsUsing);
			emptyCylinderArray.push_back(cylinderCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 16, cylinderCopy->id, (int)emptyCylinderArray.size() - 1 });
		}
		break;
		case 17:
		{
			//lấy ra object để copy
			TorusAttribute *torusNow = torusArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TorusAttribute *torusCopy = new TorusAttribute(torusNow);
			torusCopy->id = getIdForObject(idsUsing);
			torusArray.push_back(torusCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 17, torusCopy->id, (int)torusArray.size() - 1 });
		}
		break;
		case 18:
		{
			//lấy ra object để copy
			PictureAttribute *pictureNow = pictureArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			PictureAttribute *pictureCopy = new PictureAttribute(pictureNow);
			pictureCopy->id = getIdForObject(idsUsing);
			pictureArray.push_back(pictureCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 18, pictureCopy->id, (int)pictureArray.size() - 1 });
		}
		break;
		case 19:
		{
			//lấy ra object để copy
			ObjectCustom0Attribute *objectNow = objectCustom0Array.at(item.positionOfChoice);
			//tạo ra 1 object mới
			ObjectCustom0Attribute *objectCopy = new ObjectCustom0Attribute(objectNow);
			objectCopy->id = getIdForObject(idsUsing);
			objectCustom0Array.push_back(objectCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 19, objectCopy->id, (int)objectCustom0Array.size() - 1 });
		}
		break;
		default:
			break;
		}
	}
}

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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberItemChoice = itemsChoice.size();
	for (int i = 0; i < numberItemChoice; i++) {
		itemChoice item = itemsChoice.at(i);
		switch (item.object)
		{
		case 3:
		{
			//lấy ra object để copy
			TriangleAttribute *triaNow = triangleArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleAttribute *triaCopy = new TriangleAttribute(triaNow);
			triaCopy->id = getIdForObject(idsUsing);
			if (axis == 0) {
				inverseVertexesX(triaCopy->vertexArray, 3, triaNow->centerObject.x);
			}
			else if (axis == 1) {
				inverseVertexesY(triaCopy->vertexArray, 3, triaNow->centerObject.y);
			}
			else
			{
				inverseVertexesZ(triaCopy->vertexArray, 3, triaNow->centerObject.z);
			}
			
			//tính toán lại normal vector
			CaculatorNormalForTriangles(triaCopy->vertexArray, triaCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			triaCopy->centerObject = getPointCenterVertexes(triaCopy->vertexArray, 3);
			triangleArray.push_back(triaCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 3, triaCopy->id, (int)triangleArray.size() - 1 });
		}
		break;
		case 4:
		{
			//lấy ra object để copy
			TriangleStripAttribute *triaStripNow = triaStripArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleStripAttribute *triaStripCopy = new TriangleStripAttribute(triaStripNow);
			triaStripCopy->id = getIdForObject(idsUsing);
			if (axis == 0) {
				inverseVertexesX(triaStripCopy->vertexArray, triaStripNow->centerObject.x);
			}
			else if (axis == 1) {
				inverseVertexesY(triaStripCopy->vertexArray, triaStripNow->centerObject.y);
			}
			else
			{
				inverseVertexesZ(triaStripCopy->vertexArray, triaStripNow->centerObject.z);
			}
			//tính toán lại normal vector
			CaculatorNormalForTriangleStrip(triaStripCopy->vertexArray, triaStripCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			triaStripCopy->centerObject = getPointCenterVertexes(triaStripCopy->vertexArray);
			triaStripArray.push_back(triaStripCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 4, triaStripCopy->id, (int)triaStripArray.size() - 1 });
		}
		break;
		case 5:
		{
			//lấy ra object để copy
			TriangleFanAttribute *triaFanNow = triaFanArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TriangleFanAttribute *triaFanCopy = new TriangleFanAttribute(triaFanNow);
			triaFanCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục
			if (axis == 0) {
				inverseVertexesX(triaFanCopy->vertexArray, triaFanNow->centerObject.x);
			}
			else if (axis == 1) {
				inverseVertexesY(triaFanCopy->vertexArray, triaFanNow->centerObject.y);
			}
			else
			{
				inverseVertexesZ(triaFanCopy->vertexArray, triaFanNow->centerObject.z);
			}
			//tính toán lại normal vector
			CaculatorNormalForTriangleFan(triaFanCopy->vertexArray, triaFanCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			triaFanCopy->centerObject = getPointCenterVertexes(triaFanCopy->vertexArray);
			triaFanArray.push_back(triaFanCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 5, triaFanCopy->id, (int)triaFanArray.size() - 1 });
		}
		break;
		case 10:
		{
			//lấy ra object để copy
			SphereAttribute *sphereNow = sphereArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			SphereAttribute *sphereCopy = new SphereAttribute(sphereNow);
			sphereCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục X
			inverseCylinder_Sphere_Cone(axis, sphereCopy->numberLongitude, sphereCopy->numberLatitude,
				sphereCopy->vertexArray, sphereNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForSphere(sphereCopy->numberLongitude, sphereCopy->numberLatitude, sphereCopy->vertexArray, sphereCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			sphereCopy->centerObject = getPointCenterVertexes(sphereCopy->vertexArray);
			sphereArray.push_back(sphereCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 10, sphereCopy->id, (int)sphereArray.size() - 1 });
		}
		break;
		case 11:
		{
			//lấy ra object để copy
			CubeAttribute *cubeNow = cubeArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CubeAttribute *cubeCopy = new CubeAttribute(cubeNow);
			cubeCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục X
			inverseCube(axis, cubeCopy->numberVertexInAxisX, cubeCopy->numberVertexInAxisY, cubeCopy->numberVertexInAxisZ,
				cubeCopy->vertexArray, cubeCopy->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForCube(cubeCopy->numberVertexInAxisX, cubeCopy->numberVertexInAxisY, cubeCopy->numberVertexInAxisZ,
				cubeCopy->vertexArray, cubeCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			cubeCopy->centerObject = getPointCenterVertexes(cubeCopy->vertexArray);
			cubeArray.push_back(cubeCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 11, cubeCopy->id, (int)cubeArray.size() - 1 });
		}
		break;
		case 12:
		{
			//lấy ra object để copy
			CubeRoundAttribute *cubeNow = cubeRoundArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CubeRoundAttribute *cubeCopy = new CubeRoundAttribute(cubeNow);
			cubeCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục axis
			inverseCylinder_Sphere_Cone(axis, cubeCopy->numberLongitude, cubeCopy->numberLatitude,
				cubeCopy->vertexArray, cubeNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForCubeRound(cubeCopy->numberLongitude, cubeCopy->numberLatitude,
				cubeCopy->vertexArray, cubeCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			cubeCopy->centerObject = getPointCenterVertexes(cubeCopy->vertexArray);
			cubeRoundArray.push_back(cubeCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 12, cubeCopy->id, (int)cubeRoundArray.size() - 1 });
		}
		break;
		case 13:
		{
			//lấy ra object để copy
			ConeAttribute *coneNow = coneArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			ConeAttribute *coneCopy = new ConeAttribute(coneNow);
			coneCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục axis
			inverseCylinder_Sphere_Cone(axis, coneCopy->numberLongitude, coneCopy->numberLatitude,
				coneCopy->vertexArray, coneNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForCone(coneCopy->numberLongitude, coneCopy->numberLatitude,
				coneCopy->vertexArray, coneCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			coneCopy->centerObject = getPointCenterVertexes(coneCopy->vertexArray);
			coneArray.push_back(coneCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 13, coneCopy->id, (int)coneArray.size() - 1 });
		}
		break;
		case 14:
		{
			//lấy ra object để copy
			CylinderAttribute *cylinderNow = cylinderArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			CylinderAttribute *cylinderCopy = new CylinderAttribute(cylinderNow);
			cylinderCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục axis
			inverseCylinder_Sphere_Cone(axis, cylinderCopy->numberLongitude, cylinderCopy->numberLatitude,
				cylinderCopy->vertexArray, cylinderNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForCylinder(cylinderCopy->numberLongitude, cylinderCopy->numberLatitude,
				cylinderCopy->vertexArray, cylinderCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			cylinderCopy->centerObject = getPointCenterVertexes(cylinderCopy->vertexArray);
			cylinderArray.push_back(cylinderCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 14, cylinderCopy->id, (int)cylinderArray.size() - 1 });
		}
		break;
		case 16:
		{
			//lấy ra object để copy
			EmptyCylinderAttribute *cylinderNow = emptyCylinderArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			EmptyCylinderAttribute *cylinderCopy = new EmptyCylinderAttribute(cylinderNow);
			cylinderCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục axis
			inverseCylinder_Sphere_Cone(axis, cylinderCopy->numberLongitude, cylinderCopy->numberLatitude,
				cylinderCopy->vertexArray, cylinderNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForEmptyCylinder(cylinderCopy->numberLongitude, cylinderCopy->numberLatitude,
				cylinderCopy->vertexArray, cylinderCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			cylinderCopy->centerObject = getPointCenterVertexes(cylinderCopy->vertexArray);
			emptyCylinderArray.push_back(cylinderCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 16, cylinderCopy->id, (int)emptyCylinderArray.size() - 1 });
		}
		break;
		case 17:
		{
			//lấy ra object để copy
			TorusAttribute *torusNow = torusArray.at(item.positionOfChoice);
			//tạo ra 1 object mới
			TorusAttribute *torusCopy = new TorusAttribute(torusNow);
			torusCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục X
			inverseTorus(axis, torusCopy->depthRoundCake, torusCopy->vertexArray, torusNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForTorus(torusCopy->depthRoundCake, torusCopy->vertexArray, torusCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			torusCopy->centerObject = getPointCenterVertexes(torusCopy->vertexArray);
			torusArray.push_back(torusCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 17, torusCopy->id, (int)torusArray.size() - 1 });
		}
		break;
		case 19:
		{
			//lấy ra object để copy
			ObjectCustom0Attribute *objectNow = objectCustom0Array.at(item.positionOfChoice);
			//tạo ra 1 object mới
			ObjectCustom0Attribute *objectCopy = new ObjectCustom0Attribute(objectNow);
			objectCopy->id = getIdForObject(idsUsing);
			//làm nghịch đảo các vertex thông qua trục y cho trước bởi giá trị trên trục axis
			inverseCylinder_Sphere_Cone(axis, objectCopy->numberLongitude, objectCopy->numberLatitude,
				objectCopy->vertexArray, objectNow->centerObject);
			//tính toán lại normal vector
			CaculatorNormalForObjectCustom0(objectCopy->numberLongitude, objectCopy->numberLatitude,
				objectCopy->vertexArray, objectCopy->normalVector);
			//tính toán lại điểm trung tam của hình
			objectCopy->centerObject = getPointCenterVertexes(objectCopy->vertexArray);
			objectCustom0Array.push_back(objectCopy);
			//đặt đối tượng vừa tạo là đối tượng được chọn
			itemsChoice.clear();
			itemsChoice.push_back({ 19, objectCopy->id, (int)objectCustom0Array.size() - 1 });
		}
		break;
		default:
			break;
		}
	}
}

//hàm tìm các điểm trên đối tượng được chọn bằng vùng chọn
void getVertexByArea(itemChoice item, AreaChoice areaChoice, vector<int> &positionVerticesChoice,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		positionVerticesChoice.clear();
	}

	float distancePointToCenter;
	int numberVertex;
	point v;
	switch (item.object)
	{
	case 3: {
		TriangleAttribute *object = triangleArray.at(item.positionOfChoice);
		//so sánh khoảng cách từ các điểm của tam giác tới tâm vùng chọn
		for (int i = 0; i < 3; i++) {
			v = object->vertexArray[i];
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			break;
	case 4: {
		TriangleStripAttribute *object = triaStripArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *object = triaFanArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *object = sphereArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *object = cubeArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *object = cubeRoundArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *object = coneArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 15: {
		PyramidAttribute *object = pyrArray.at(item.positionOfChoice);
		//so sánh khoảng cách từ các điểm của tam giác tới tâm vùng chọn
		for (int i = 0; i < 5; i++) {
			v = object->vertexArray[i];
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *object = torusArray.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 18: {
		PictureAttribute *object = pictureArray.at(item.positionOfChoice);
		//so sánh khoảng cách từ các điểm của tam giác tới tâm vùng chọn
		for (int i = 0; i < 4; i++) {
			v = object->vertexArray[i];
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		numberVertex = object->vertexArray.size();
		for (int i = 0; i < numberVertex; i++) {
			v = object->vertexArray.at(i);
			distancePointToCenter = distanceTwoPoint(v, areaChoice.centerArea);
			if (distancePointToCenter <= areaChoice.radius) {
				positionVerticesChoice.push_back(i);
			}
		}
	}
			 break;
	default:
		break;
	}
	//xóa các vertex trùng
	clearSamePoints(positionVerticesChoice);
}
//hàm kiểm tra xem vùng chọn có cắt trúng đường thẳng nối 2 điểm không
bool checkAreaCutLine(AreaChoice areaChoice, point v0, point v1) {
	point AB, H;
	float t, distanceAB, distanceAH, distanceBH;
	//phương trình đường thẳng nối 2 điểm v0,v1
	//vector chỉ phương v0v1
	AB = { (v1.x - v0.x),(v1.y - v0.y), (v1.z - v0.z) };
	//tính ra điểm nằm trên đường thẳng v1v0 mà gần tâm chọn nhất
	//tính tham số t
	t = (-AB.x*v0.x - AB.y*v0.y - AB.z*v0.z
		+ AB.x*areaChoice.centerArea.x + AB.y*areaChoice.centerArea.y + AB.z*areaChoice.centerArea.z) /
		(AB.x*AB.x + AB.y*AB.y + AB.z*AB.z);
	//tìm điểm giao
	H = { v0.x + AB.x*t,v0.y + AB.y*t, v0.z + AB.z*t };
	//đầu tiên phải kiểm tra điểm H có nằm ngoài AB không,nếu nằm ngoài thì nghĩa là đường thẳng không cắt hình cầu
	//do xét đến bước này nghĩa là A và B đều nằm ngoài hình cầu,nếu H nằm bên ngoài AB thì nghĩa là phần đoạn thẳng nối
	//A và B không cắt hình cầu.

	//đầu tiên tính khoảng cách A và B
	distanceAB = distanceTwoPoint(v0, v1);
	//tiếp theo tính khoảng cách B và H
	distanceBH = distanceTwoPoint(H, v1);
	//tiếp theo tính khoảng cách A và H
	distanceAH = distanceTwoPoint(H, v0);
	//nếu khoảng cách BH và AH Nhỏ hơn AB thì H nằm trong AB
	if (distanceAB > distanceBH && distanceAB > distanceAH) {
		//nếu H nằm trong AB thì phải xem xem khoảng cách từ H đến tâm có nhỏ hơn bán kính không,nếu có thì đường thẳng cắt hình cầu
		if (distanceTwoPoint(H, areaChoice.centerArea) < areaChoice.radius) {
			return true;
		}
	}
	return false;
}
//kiểm tra xem tâm giác được tạo bởi 3 điểm có nằm trong vùng chọn không
bool checkTriaInArea(AreaChoice areaChoice, point v0, point v1, point v2) {
	bool isCutLine, isInTria;
	//đầu tiên kiểm tra xem điểm nhấn có nằm trong tam giác không
	isInTria = checkPointInTriangle(areaChoice.centerArea, v0, v1, v2);
	if (isInTria) {
		return true;
	}
	//nếu không thì kiểm tra xem xem có điểm nào thuộc face mà nằm trong vùng chọn không,nếu có thì lấy face đó luôn
	//kiểm tra bằng cách xem khoảng cách giữa tâm và điểm đó có lớn hơn bán kính không,
	//nếu không thì là nằm trong vùng chọn
	else if (distanceTwoPoint(v0, areaChoice.centerArea) < areaChoice.radius) {
		return true;
	}
	else if (distanceTwoPoint(v1, areaChoice.centerArea) < areaChoice.radius) {
		return true;
	}
	else if (distanceTwoPoint(v2, areaChoice.centerArea) < areaChoice.radius) {
		return true;
	}
	//nếu không thì mới kiểm tra vùng chọn có cắt các đường thẳng tạo thành face không
	else {
		isCutLine = checkAreaCutLine(areaChoice, v0, v1);
		if (isCutLine) {
			return true;
		}
		else
		{
			isCutLine = checkAreaCutLine(areaChoice, v1, v2);
			if (isCutLine) {
				return true;
			}
			else
			{
				isCutLine = checkAreaCutLine(areaChoice, v0, v2);
				if (isCutLine) {
					return true;
				}
			}
		}
	}
	return false;
}
//hàm tìm các điểm trên đối tượng được chọn bằng vùng chọn
void getFaceByArea(itemChoice item, AreaChoice areaChoice, vector<int> &positionFaceChoice,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		positionFaceChoice.clear();
	}

	point v0, v1, v2;
	bool isInArea;

	switch (item.object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		int numberFace = triaStrip->vertexArray.size() - 2;

		for (int i = 0; i < numberFace; i++) {
			v0 = triaStrip->vertexArray.at(i);
			v1 = triaStrip->vertexArray.at(i + 1);
			v2 = triaStrip->vertexArray.at(i + 2);
			isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
			if (isInArea) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		int numberFace = triaFan->vertexArray.size() - 1;
		v0 = triaFan->vertexArray.at(0);
		for (int i = 1; i < numberFace; i++) {
			v1 = triaFan->vertexArray.at(i);
			v2 = triaFan->vertexArray.at(i + 1);
			isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
			if (isInArea) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = sphere->numberLatitude - (sphere->degreeLatitudeLimit / (360 / sphere->numberLatitude));
		minusLongitude = sphere->numberLongitude - (sphere->degreeLongitudeLimit / (360 / sphere->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < sphere->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * sphere->numberLongitude;
			offsetNow = i * sphere->numberLongitude;
			for (int j = minusLongitude + 1; j < sphere->numberLongitude; j++) {
				v0 = sphere->vertexArray.at(offsetLast + j - 1);
				v1 = sphere->vertexArray.at(offsetNow + j - 1);
				v2 = sphere->vertexArray.at(offsetLast + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = sphere->vertexArray.at(offsetNow + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == sphere->numberLongitude - 1) {
					v0 = sphere->vertexArray.at(offsetLast + j);
					v1 = sphere->vertexArray.at(offsetNow + j);
					v2 = sphere->vertexArray.at(offsetLast);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = sphere->vertexArray.at(offsetNow);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int offsetFace = 0, offset1, offset2, offset3, numberVertexInRow;
		bool isDraw = false;

		numberVertexInRow = (cube->numberVertexInAxisX - 1) * 2 + (cube->numberVertexInAxisZ - 1) * 2;
		// vẽ mặt cho hình bao quanh hình vuông
		for (int i = 0; i < cube->numberVertexInAxisY - 1; i++) {
			offset1 = i * numberVertexInRow;
			offset2 = (i + 1) * numberVertexInRow;
			for (int j = 1; j < numberVertexInRow; j++) {
				v0 = cube->vertexArray.at(offset1 + j - 1);
				v1 = cube->vertexArray.at(offset2 + j - 1);
				v2 = cube->vertexArray.at(offset1 + j);
				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

				v0 = cube->vertexArray.at(offset2 + j);
				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

				//nếu là cặp đỉnh cuối cùng thì vẽ nối với cặp đỉnh đầu tiên
				if (j == numberVertexInRow - 1) {
					v1 = cube->vertexArray.at(offset1);
					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}
					offsetFace++;

					v2 = cube->vertexArray.at(offset2);
					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}
					offsetFace++;
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
				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

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
				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;
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
				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;

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

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}
				offsetFace++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cone->numberLatitude - (cone->degreeLatitudeLimit / (360 / cone->numberLatitude));
		minusLongitude = cone->numberLongitude - (cone->degreeLongitudeLimit / (360 / cone->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cone->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cone->numberLongitude;
			offsetNow = i * cone->numberLongitude;
			for (int j = minusLongitude + 1; j < cone->numberLongitude; j++) {
				v0 = cone->vertexArray.at(offsetLast + j - 1);
				v1 = cone->vertexArray.at(offsetNow + j - 1);
				v2 = cone->vertexArray.at(offsetLast + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cone->vertexArray.at(offsetNow + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cone->numberLongitude - 1) {
					v0 = cone->vertexArray.at(offsetLast + j);
					v1 = cone->vertexArray.at(offsetNow + j);
					v2 = cone->vertexArray.at(offsetLast);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cone->vertexArray.at(offsetNow);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
				v0 = cylinder->vertexArray.at(offsetLast + j - 1);
				v1 = cylinder->vertexArray.at(offsetNow + j - 1);
				v2 = cylinder->vertexArray.at(offsetLast + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cylinder->vertexArray.at(offsetNow + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					v0 = cylinder->vertexArray.at(offsetLast + j);
					v1 = cylinder->vertexArray.at(offsetNow + j);
					v2 = cylinder->vertexArray.at(offsetLast);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cylinder->vertexArray.at(offsetNow);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow, minusLatitude, minusLongitude;

		//tính toán ra số độ bị cắt để bỏ đi
		minusLatitude = cylinder->numberLatitude - (cylinder->degreeLatitudeLimit / (360 / cylinder->numberLatitude));
		minusLongitude = cylinder->numberLongitude - (cylinder->degreeLongitudeLimit / (360 / cylinder->numberLongitude));
		if (minusLatitude < 0) {
			minusLatitude = 0;
		}
		if (minusLongitude < 0) {
			minusLongitude = 0;
		}
		for (int i = 1; i < cylinder->numberLatitude - minusLatitude; i++) {
			offsetLast = (i - 1) * cylinder->numberLongitude;
			offsetNow = i * cylinder->numberLongitude;
			for (int j = minusLongitude + 1; j < cylinder->numberLongitude; j++) {
				v0 = cylinder->vertexArray.at(offsetLast + j - 1);
				v1 = cylinder->vertexArray.at(offsetNow + j - 1);
				v2 = cylinder->vertexArray.at(offsetLast + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = cylinder->vertexArray.at(offsetNow + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
				//nếu là cặp đỉnh cuối cùng thì nối với cặp đỉnh đầu tiên
				if (j == cylinder->numberLongitude - 1) {
					v0 = cylinder->vertexArray.at(offsetLast + j);
					v1 = cylinder->vertexArray.at(offsetNow + j);
					v2 = cylinder->vertexArray.at(offsetLast);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;

					v0 = cylinder->vertexArray.at(offsetNow);

					isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
					if (isInArea) {
						positionFaceChoice.push_back(offsetFace);
					}

					offsetFace++;
				}
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		int numberFace = torus->vertexArray.size() - 2;
		for (int i = 0; i < numberFace; i++) {
			v0 = torus->vertexArray.at(i);
			v1 = torus->vertexArray.at(i + 1);
			v2 = torus->vertexArray.at(i + 2);
			isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
			if (isInArea) {
				positionFaceChoice.push_back(i);
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		int offsetFace = 0, offsetLast, offsetNow;

		for (int i = 1; i < object->numberLatitude; i++) {
			offsetLast = (i - 1) * object->numberLongitude;
			offsetNow = i * object->numberLongitude;
			for (int j = 1; j < object->numberLongitude; j++) {
				v0 = object->vertexArray.at(offsetLast + j - 1);
				v1 = object->vertexArray.at(offsetNow + j - 1);
				v2 = object->vertexArray.at(offsetLast + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;

				v0 = object->vertexArray.at(offsetNow + j);

				isInArea = checkTriaInArea(areaChoice, v0, v1, v2);
				if (isInArea) {
					positionFaceChoice.push_back(offsetFace);
				}

				offsetFace++;
			}
		}
	}
			 break;
	default:
		break;
	}
	//xóa các mặt trùng
	clearSamePoints(positionFaceChoice);
}

//hàm thêm cụm vertex trên,dưới,trái hay phải ObjectCustom0
//whichDirection=0 là phía trên,1 là phía bên trái,2 là phía dưới,3 là phía bên phải
//sau khi được thêm các vertex vừa thêm sẽ chuyển sang chế độ chọn và mouseModel sẽ = 3(chế độ dịch chuyển)
void AddVerticesAroundObjectCustom0(int whichDirection,ObjectCustom0Attribute* object,
	vector<int> &positionVerticesChoice) {

	positionVerticesChoice.clear();

	switch (whichDirection)
	{
	//nếu thêm vào phía trên object
	case 0: {
		//do hình này sắp xếp thứ tự vertex để vẽ từ dưới lên trên,nên sẽ thêm vào sau cùng mảng vertex
		//vertex được thêm sẽ nằm cùng chỗ phần tử cùng vị trí ở dãy trước nó
		int offset0 = (object->numberLatitude - 1)*object->numberLongitude,
			offset1 = offset0 + object->numberLongitude;
		for (int i = 0; i < object->numberLongitude; i++) {
			object->vertexArray.push_back(object->vertexArray.at(offset0 + i));
			//thêm vị trí vừa thêm vào mảng các vertex được chọn
			positionVerticesChoice.push_back(offset1 + i);
		}

		//số lượng các hàng tăng lên 1
		object->numberLatitude++;
	}
			break;
	//nếu thêm vào phía bên trái object
	case 1: {
		//phải thêm tử dưới lên trên
		int offset = 0;
		for (int i = object->numberLatitude; i >= 1; i--) {
			offset = i*object->numberLongitude - 1;
			object->vertexArray.insert(object->vertexArray.begin() + offset, object->vertexArray.at(offset));
		}

		//số lượng các cột tăng lên 1
		object->numberLongitude++;

		//lấy toàn bộ phần tử của dãy hàng dọc cuối là phần tử được chọn
		for (int i = 1; i <= object->numberLatitude; i++) {
			positionVerticesChoice.push_back(i*object->numberLongitude - 1);
		}
	}
			break;
	//nếu thêm vào phía dưới object
	case 2: {
		//copy toàn bộ phần tử của hàng đầu tiên và đặt vào đầu tiên
		object->vertexArray.insert(object->vertexArray.begin(),
			object->vertexArray.begin(), object->vertexArray.begin() + object->numberLongitude);

		//số lượng các hàng tăng lên 1
		object->numberLatitude++;

		//lấy toàn bộ phần tử của hàng đầu tiên là phần tử được chọn
		for (int i = 0; i < object->numberLongitude; i++) {
			positionVerticesChoice.push_back(i);
		}
	}
			break;
	//nếu thêm vào phía bên phải object
	case 3: {
		//phải thêm tử dưới lên trên
		int offset = 0;
		for (int i = object->numberLatitude - 1; i >= 0; i--) {
			offset = i*object->numberLongitude;
			object->vertexArray.insert(object->vertexArray.begin() + offset, object->vertexArray.at(offset));
		}

		//số lượng các cột tăng lên 1
		object->numberLongitude++;

		//lấy toàn bộ phần tử của dãy hàng dọc cuối là phần tử được chọn
		for (int i = 0; i < object->numberLatitude; i++) {
			positionVerticesChoice.push_back(i*object->numberLongitude);
		}
	}
			break;
	default:
		break;
	}
	
	//tính toán lại normal cho object
	CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
}