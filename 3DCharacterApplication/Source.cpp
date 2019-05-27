#include <freeglut.h>
#include <thread>
//#include <stdlib.h> 
#include "SqlServerConnect.h"
#include "SuppostForApp.h"
#include "SuppostForApp2.h"
#include "SuppostForApp3.h"


#define GAP 4   /* khoảng cách giữa các subwindows */
int window_width = 1700, window_height = 900,
window_top = 10, window_left = 10,
screen_width = 500, screen_height = 500,
screen2D_width = 0, screen2D_height = 0;

//biến thông báo có đang ở trạng thái full màn hình không
bool isFullScreen;

//vị trí các nguồn sáng
float lightPosition[4], lightPositionFront[4], lightPositionLeft[4],
lightAmbient[4], lightDiffuse[4], lightSpecular[4], lightOff[4];

//màu mặc định
float colorDefaul[4], colorScreen[4];

//xoay vật và dịch chuyển camera(thực ra là dịch chuyển tất cả vật)
float zoomCamera, rotateCameraX, rotateCameraY,
translateCameraX, translateCameraY, translateCameraZ,
zoomCameraImage1, translateCameraXImage1, translateCameraYImage1,
zoomCameraImage2, translateCameraXImage2, translateCameraYImage2;


//biến thông báo có mở tệp khung chọn tệp không
bool isOpenChoiceForder;
//biến xác định tệp được chọn để lưu hay mở dữ liệu
int whichDataChoice;


//biến thông báo có vertex vừa được chọn bằng mouseDown(sử dụng để dịch chuyển bằng cách kéo chuột)
bool isChoiceVertexNow;

//biến thông báo hình thứ bao nhiêu trong mảng các hình được chọn cùng với mũi tên nào của đỉnh đang bị chọn
int whichArrowChoice;
//biến thông báo hình thứ bao nhiêu trong mảng các hình được chọn cùng với hình vuông dịch chuyển nào đang được chọn
int whichQuadChoice;
//biến xác định các giá trị liên quan đến xoay bao gồm giá trị để xác định vòng xoay,...
itemRotateObject itemRotate;

//biến thông báo có đang ở chế độ dịch chuyển tâm xoay hay scale không
bool isMoveCenterRotate;

//biến thông báo vị trí của chuột và bán kính khi chọn bằng vùng chọn
AreaChoice areaChoice;

//điểm dùng làm tâm xoay,scale,move của vật hay điểm
point centerObjectOrVertices, centerObjectOrVerticesSymmetry;

//vị trí của các vertex được chọn để dùng cho chế độ chỉnh sửa vertex
std::vector<int> positionVerticesChoice;
//vị trí các mặt tam giác được chọn để dùng cho chế độ chỉnh sửa các mặt đa giác
std::vector<int> positionFacesChoice;

//các biến chứa thông tin về việc thêm,bớt chuỗi vertex
PositionRowOrColumn positionAddRowOrColumn, positionDeleteRowOrColumn;
//mảng chứa các chuỗi vertex row hay column được chọn
vector<PositionRowOrColumn> positionChoiceRowOrColumn;

//biến xác định các giá trị dành cho texture
itemTextureObject itemTextureWindow = { 0U,-1,0 };

//biến thông báo có chấp nhận vị trí hiện tại của vật hay vertex trong chế độ đặt hay vẽ chưa.
//nếu chấp nhận rồi thì được,còn nếu chưa thì khi nhấn vào bất kỳ nút nào trên menu thì sẽ xóa vật hay vertex cuối cùng
bool isAgreePossition;

//Tên vật được chọn và vị trí của nó trong mảng
/*0:Lines,1:line_strip,2:line_loop,3:triangles,4:triangle_strip,5:triangle_fan,6 là hình hộp triangle_strip,
7 là hình hộp triangle_fan,8 là hình hộp triangle_strip có thể bo tròn,9 là hình hộp triangle_fan có thể bo tròn,
10 là hình khối cầu,11 là hình khối vuông,12 hình khối vuông bo tròn,13 là hình nón,14 là hình trụ tròn,
15 là hình kim tự tháp,16 là hình trụ tròn rỗng,17 là hình bánh rán,18 là hình ảnh
19 là ObjectCustom0
(-1 là k0 chọn hình nào)*/
std::vector<itemChoice> itemsChoice;

//mảng vector chứa các id đang được dùng,khi đặt vật mới thì kiểm tra từ 0 xem id đó được dùng chưa,nếu chưa thì đặt
//khi thêm hay xóa id thì phải xóa nó ở trong mảng này luôn
std::vector<int> idsUsing;

//mảng vector lưu tên các txt theo thứ tự sử dụng
vector<int> txtUsing;
//biến chứa vị trí txt đang sử dụng trong mảng trên
int offsetTxtUsing;

//cái này dùng cho các tam giác hay đường thẳng k0 giới hạn số đỉnh(đay là vị trí đỉnh đầu tiên trong 3 đỉnh liên tiếp sẽ được hiển thị)
int offsetOfVertexInfor;
//các menu cho title(có 4 menu nhưng chỉ 3 cái ấn được,cái còn lại là title)
//(0 là kéo thả window,1 là phóng to/thu nhỏ,2 là đóng ứng dụng)
int modelTitleApp;

//các menu cho app,lưu,quay lại
int modelApp;
//-1 là chế độ xoay camera,0 là chế độ chọn,1 là chế độ chọn từ vùng chọn không đồng đều,
//2 là chế độ chọn bằng vùng chọn hình cầu,3 là chế độ dịch chuyển hình,
//4 là chế độ xoay hình,5 là chế độ phóng to hình,6 là chế độ chỉnh sửa thuộc tính hình
//7 là chế độ thêm vertex vào hình,8 là chế độ xóa vertex
int mouseModel;
//chọn kiểu vẽ 
//0 là chế độ vẽ băng đường thẳng hay tam giác,1 là chế độ vẽ bằng cách đặt vật
int modelStyleDraw;

//chọn đối tượng vẽ
//-1 là không vẽ gì cả
//nếu menuStyleDraw=0
/*0:Lines,1:line_strip,2:line_loop,3:triangles,4:triangle_strip,5:triangle_fan*/
//nếu menuStyleDraw=1
//chọn đối tượng để kéo thả lên màn hình
/*0 là hình khối cầu,1 là hình khối vuông,2 hình khối vuông có thể bo tròn,3 là hình nón
4 là hình trụ tròn,5 là hình kim tự tháp,6 là hình trụ tròn rỗng,7 là hình bánh rán,8 là hình ảnh*/
int modelTop;

//chọn kiểu chỉnh sửa đối tượng
//chọn kiểu chỉnh sửa
//0 là sắp xếp các vertex cùng vị trí X,1 là sắp xếp các vertex cùng vị trí Y,
//2 là sắp xếp các vertex cùng vị trí Z,3 là chế độ copy các vật đang được chọn,
//4 là chế độ copy đảo chiều của vật theo chiều X,
//5 là chế độ copy đảo chiều của vật theo chiều Y,
//6 là chế độ copy đảo chiều của vật theo chiều Z,
//7 là bật chế độ dịch chuyển tâm xoay
int modelEdit;

//kiểu đối tượng chỉnh sửa(0 là chỉnh sửa cả đối tượng,1 là chỉnh sửa các vertex lẻ,2 là chỉnh sửa 1 cụm vertex(đối với chế độ 1,2 cho phép chọn nhiều
//hình nhưng chỉ hình đầu tiên là hiện vertex còn các hình còn lại chỉ hiện đường lưới)
//3 là chọn các mặt cũng như các vertex có liên quan đên mặt đó)
int modelEditStyle;
//chọn kiểu chiếu 0 là chiếu 2D và 1 là chiếu 3D,2 là 2 hình 2D và 1 hình 3D
int modelSpace;

//biến này dùng để thay đổi vị trí chiếu cho phép chiếu 2D
//-1 là chiếu 3D,0 là chiếu thẳng,1 là chiếu từ bên phải,
//2 là chiếu từ phía sau,3 là chiếu từ bên trái
int changeRotateFor2D;

//chứa giá trị các vertex để vẽ hình chữ nhật chọn hoặc hình chữ nhật thêm vertex
//các phần tử sắp xếp theo chiều ngược chiều kim đồng hồ,
//vertexToDrawRectangleSymmetry chứa các vertex đối nghịch trong trường hợp bật đối nghịch
vector<point> vertexToDrawRectangle, vertexToDrawRectangleSymmetry;

GLdouble clipPlane1[4], clipPlane2[4], clipPlane3[4], clipPlane4[4];
int mouseDownX, mouseDownY;
int lastTouchX, lastTouchY;

//điểm chạm đầu tiên của chuột khi nhấn vào mũi tên hay quad để dịch chuyển hình
point firstTouch = { 0,0,0 };

//các biến chứa các thông tin về giá trị dịch chuyển để khi thả chuột thì lưu vào
float move_X, move_Y, move_Z,
   scale_X, scale_Y, scale_Z,
   rotate_X, rotate_Y, rotate_Z;

//biến lưu lại giá trị mouseModel khi dùng chuột phải để xoay hình
int lastMouseModel;

//****các biến dùng cho menu bên phải màn hình
//menu đang chọn trong menuGroup1
int modelMenuGroup1;
//menu đang chọn trong menuGroup2
int modelMenuGroup2;
//item con hiện đang được chọn trong menuGroup2
int item_choice_in_MenuGroup2;

bool isChoiceColorPicker, isRoundCorner, menu_isChangeCharNumberValue;
//biến whichStyleRound thông báo cách dùng giá trị bo tròn(0 là bo cả 2 chiều theo cùng 1 giá trị,1 là
//bo 2 chiều theo 2 giá trị khác nhau)
int whichStyleRound,
    numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical;
float radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical;
//biến whichTransform thông báo kiểu biến đổi cho hình được chọn(0 là translate,1 là scale,2 là scale)
int menu_whichTransform;
float menu_translateX, menu_translateY, menu_translateZ,
      menu_rotateX, menu_rotateY, menu_rotateZ,
      menu_scaleX, menu_scaleY, menu_scaleZ;
//mảng char dùng để áp dụng giá trị trên bàn phím sang giá trị trong phần cài đặt
//dùng mảng động vì ta đang thiếu bộ nhớ trên stack,nên chuyển sang dùng bộ nhớ trên head
char menu_charNumberValue[11];

//biến symmetryVertexOrObject xem các vertex hay object đang được áp dụng đối xứng(0 tức là vertex,1 là object)
//biến whichStyleSymmetry thông báo hiện vertex,row hay column trong chế độ symmetryVertices
//0 là xem đối xứng cho vertex,1 là xem đối xứng cho hàng ngang,2 là xem đối xứng cho hàng dọc
//whichSymmetry là xem item thứ bao nhiêu để hiện ra các vertex,row,column hayobject đối xứng
bool symmetryVertexOrObject;
int whichStyleSymmetry , whichItemSymmetry;
//các biến xác định áp dụng đối xứng cho kiểu biến đổi này không
//nếu true sẽ di chuyển ngược chiều và false sẽ di chuyển cùng chiều
bool symmetry_translateX, symmetry_translateY, symmetry_translateZ,
   symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
   symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ;

//mảng chứa các giá trị đối xứng vertex
vector<SymmetryVertices> symmetryVertices;
//mảng chứa các giá trị đối xứng object
vector<SymmetryObjects> symmetryObjects;

//mảng chứa vị trí bắt đầu và kết thúc của cả 2symmetry để dùng lấy các phần tử nằm giữa
int startAndEndSymmetry1[2], startAndEndSymmetry2[2];
//biến chứa giá trị thông báo sẽ lấy giá trị theo chiều kim đồng hồ hay ngược chiều
bool isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2;

//biến này thông báo có hiện hình vẽ trước khi thật sự vẽ không
bool tool_isShowBeforeDraw;

//biến thông báo có bật nhắc nhở bằng vị trí không
//khi di chuyển chuột sẽ load ra hết các vertex đang tồn tại để xem chuột ở gần điểm nào thì lấy điểm đó
bool tool_isRemind;

//biến thông báo có vẽ lưới hay không
bool tool_isDrawNet;

//2 biến chứa kích thước của mũi tên và đường tròn xoay
float tool_arrowSize, tool_circleSize;

//left,right,top,bottom
int positionMenu1[4];
int positionMenu2[4];

//các vị trí cho menu
int positionMenuTitle[4][2];
int positionMenuApp[5][2];
//các giá trị -1 nghĩa là chưa xác định,phải đợi có kích thước cửa sổ mới tính được
int positionMenuMouse[9][2];
int positionMenuTop[11][2];
int positionMenuEdit[8][2];
int positionMenuEditStyle[4][2];
int positionMenuSpace[3][2];

//các biến dành cho ảnh và kết cấu
//biến tên liên kết kết cấu
GLuint menuTitle[4], menuApp[5], menuMouse[9], menuDraw[6], menuPick[11], menuStyleDraw[2],
menuEditStyle[4], menuEdit[8], menuSpace[3], colorPicker;

//Các giá trị ma trận,và viewport
GLdouble modelMatrix[16], modelMatrixArrow[16],
      projectMatrixWindow[16], projectMatrix[16],
	  projectMatrixArrow[16], modelMatrixImage1[16],
	  modelMatrixImage2[16], projectMatrixImage1[16],
	  projectMatrixImage2[16];
GLint viewport[4], viewportImage1[4], viewportImage2[4];

//tên đại diện cho khung hình
GLuint window, subwindow, screen, screen1, screen2;

#define BUFSIZE 40000
//mảng lưu trữ các gia trị tên(id của vật)
GLuint bufferIdChoice[BUFSIZE];

//số vertex còn lại cần phải vẽ để hoàn thành hình
int vertexLeftToDraw = 0, totalVertexOfShape = 0;

//Các mảng lưu trữ các thuộc tính để vẽ
std::vector<TriangleAttribute*> triangleArray;
std::vector<TriangleStripAttribute*> triaStripArray;
std::vector<TriangleFanAttribute*> triaFanArray;
std::vector<SphereAttribute*> sphereArray;
std::vector<CubeAttribute*> cubeArray;
std::vector<CubeRoundAttribute*> cubeRoundArray;
std::vector<ConeAttribute*> coneArray;
std::vector<CylinderAttribute*> cylinderArray;
std::vector<PyramidAttribute*> pyrArray;
std::vector<EmptyCylinderAttribute*> emptyCylinderArray;
std::vector<TorusAttribute*> torusArray;
std::vector<PictureAttribute*> pictureArray;
std::vector<ObjectCustom0Attribute*> objectCustom0Array;



//hàm quay lại hoặc tiến tiếp thay đổi trước đó
//hàm này sẽ phân phối đến 2 hàm khác là hàm thực hiện lùi lại các dịch chuyển,chuyển đổi
//và hàm thêm lại hoặc xóa đi objects(dùng cho các vật bị xóa)
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void returnChange(bool isTurnUp) {
	//nếu đang có file txt đang sử dụng và offsetTxtUsing khác -1(tức là không còn file nào nữa để quay lại)
	if ((!isTurnUp && offsetTxtUsing != -1) || (isTurnUp && offsetTxtUsing != txtUsing.size() - 1) && !txtUsing.empty()) {
		char pathObject[40], pathAttribute[40], charNumber[2];
		string stringPath;
		int nameTxt;

		if (isTurnUp) {
			//tăng offsetTxtUsing
			//con trỏ không cho viết kiểu *offsetTxtUsing++ hay *offsetTxtUsing--;
			offsetTxtUsing += 1;
			nameTxt = txtUsing.at(offsetTxtUsing);
		}
		else
		{
			nameTxt = txtUsing.at(offsetTxtUsing);
			//lùi offsetTxtUsing
			offsetTxtUsing -= 1;
		}

		//các biến lưu giá trị cho thuộc tính
		int whichEffect = -1;

		//lấy ra tên để load object.txt và attribute.txt từ vị trí đã lưu
		getNameTxt(nameTxt,
			pathObject, pathAttribute);

		
		//sau đó kiểm tra xem kiểu chỉnh sửa nào để load object,vertex hay biến đổi tương ứng
		ifstream myfile(pathObject);
		if (myfile.is_open())
		{
			//ta phải kiểm tra xem kiểu chỉnh sửa ở đây là gì
			//nếu là move(0),rotate(1),scale(2),delete(3)

			//đọc hàng đầu tiên của tệp sẽ cho biết kiểu chỉnh sửa
			getline(myfile, stringPath);
			charNumber[0] = stringPath[2];
			whichEffect = atoi(charNumber);
			//phải đóng file lại trước khi gọi hàm bên kia
			myfile.close();
		}
		else {
			cout << "Unable to open file";
			return;
		}

		//nếu kiểu chỉnh sửa khác 5 thì thực hiện,còn nếu bằng 5 thì ta tiến thêm hay lùi lại 1 file nữa
		//do khi thay đổi thuộc tính của vật thì ta lưu lại 2 file,1 file lưu lại giá trị trước khi thay đổi
		//và 1 file lưu lại giá trị sau khi thay đổi
		if (whichEffect == 5) {
			if (isTurnUp) {
				//tăng offsetTxtUsing
				//con trỏ không cho viết kiểu *offsetTxtUsing++ hay *offsetTxtUsing--;
				offsetTxtUsing += 1;
				nameTxt = txtUsing.at(offsetTxtUsing);
			}
			else
			{
				nameTxt = txtUsing.at(offsetTxtUsing);
				//lùi offsetTxtUsing
				offsetTxtUsing -= 1;
			}

			//lấy ra tên để load object.txt và attribute.txt từ vị trí đã lưu
			getNameTxt(nameTxt,
				pathObject, pathAttribute);
		}


		//đàu tiên load lại hết thuộc tính của app ở tời điểm đó
		loadAttributeApp(pathAttribute,
			positionVerticesChoice, positionFacesChoice,
			positionChoiceRowOrColumn,
			centerObjectOrVertices, centerObjectOrVerticesSymmetry,
			itemsChoice, mouseModel, modelStyleDraw, modelTop,
			modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
			whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
			radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
			menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ,
			symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
			symmetry_translateX, symmetry_translateY, symmetry_translateZ,
			symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
			symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
			symmetryVertices, symmetryObjects,
			startAndEndSymmetry1, startAndEndSymmetry2,
			isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
			tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);

		//nêu kiểu chỉnh sửa từ 0 đến 2 thì gọi đến hàm lùi chỉnh sửa thuộc tính
		if (whichEffect <= 2) {
			loadInformationChange(pathObject, isTurnUp, itemsChoice,
				positionVerticesChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				modelEditStyle,
				symmetryVertices, symmetryObjects,
				symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
				objectCustom0Array);
		}
		//nếu kiểu chỉnh sửa từ 3 đến 5 là liên quan đến thêm,xóa hay thay đổi thuộc tính của vật đãn đến thay đổi vật
		else if (whichEffect <= 5) {
			//nếu kiểu chỉnh sửa là delete(4) và isTurnUp==true nghĩa là xóa vật đang được chọn
			//hoặc kiểu chỉnh sửa là creat(3) và isTurnUp==false nghĩa là xóa vật đang được chọn
			//thì phải xóa hết các dữ liệu trong itemsChoice đi vì nếu không nếu vật bị xóa nằm trong các vật đang được chọn
			//thì sẽ bị lỗi
			if ((isTurnUp && whichEffect == 4) || (!isTurnUp && whichEffect == 3)) {
				itemsChoice.clear();
			}

			loadInformationObject(pathObject, isTurnUp, itemsChoice,
				whichItemSymmetry,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
				objectCustom0Array, idsUsing);
		}
		//nếu kiểu chỉnh sửa là thêm hay xóa vertex
		else {
			loadInformationVertices(pathObject, isTurnUp, positionChoiceRowOrColumn,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
				objectCustom0Array);
		}

	}
}
//hàm lưu lại biến đổi của cả vertex và object
void SaveInformationTransform() {
	//hàm này sẽ gọi đến 2 hàm(1 hàm lưu lại các giá trị biến đổi,1 hàm lưu lại các thuộc tính hiện tại của app)
	char pathObject[40], pathAttribute[40];
	getNameTxtForSave(txtUsing, offsetTxtUsing, pathObject, pathAttribute);
	//đầu tiên lưu lại tất cả các thuộc tính của app
	saveAttributeApp(pathAttribute,
		positionVerticesChoice, positionFacesChoice,
		positionChoiceRowOrColumn, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
		itemsChoice, mouseModel, modelStyleDraw, modelTop,
		modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
		whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
		radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
		menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
		menu_rotateX, menu_rotateY, menu_rotateZ,
		menu_scaleX, menu_scaleY, menu_scaleZ,
		symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
		symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
		symmetryVertices, symmetryObjects,
		startAndEndSymmetry1, startAndEndSymmetry2,
		isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
		tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);
	//tiếp theo lưu lại các thông tin về các biến đổi
	//kiểm tra xem đây là dịch chuyển,xoay hay scale
	if (move_X != 0.0 || move_Y != 0.0 || move_Z != 0.0) {
		saveInformationChange(pathObject, 0, move_X, move_Y, move_Z);
		move_X = 0.0; move_Y = 0.0; move_Z = 0.0;
	}
	else if (rotate_X != 0.0 || rotate_Y != 0.0 || rotate_Z != 0.0) {
		saveInformationChange(pathObject, 1, rotate_X, rotate_Y, rotate_Z);
		rotate_X = 0.0; rotate_Y = 0.0; rotate_Z = 0.0;
	}
	else
	{
		saveInformationChange(pathObject, 2, scale_X, scale_Y, scale_Z);
		scale_X = 0.0; scale_Y = 0.0; scale_Z = 0.0;
	}
}
//hàm lưu lại các object vừa tạo hay bị xóa cùng với các thuộc tính của app hiện tại
//whichEffect bằng 3 là tạo mới vật,4 là xóa vật,5 là thay đổi thuộc tính dẫn đến thay đổi vật
void SaveObjectCreatOrDelete(int whichEffect) {
	char pathObject[40], pathAttribute[40];
	getNameTxtForSave(txtUsing, offsetTxtUsing, pathObject, pathAttribute);
	//đầu tiên lưu lại tất cả các thuộc tính của app
	saveAttributeApp(pathAttribute,
		positionVerticesChoice, positionFacesChoice,
		positionChoiceRowOrColumn, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
		itemsChoice, mouseModel, modelStyleDraw, modelTop,
		modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
		whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
		radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
		menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
		menu_rotateX, menu_rotateY, menu_rotateZ,
		menu_scaleX, menu_scaleY, menu_scaleZ,
		symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
		symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
		symmetryVertices, symmetryObjects,
		startAndEndSymmetry1, startAndEndSymmetry2,
		isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
		tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);
	//tiếp theo lưu lại các thông tin về đối tượng vừa tạo hay bị xóa
	saveInformationObject(pathObject, whichEffect, itemsChoice,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
		coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
		objectCustom0Array);
}
//hàm lưu lại các vertex được thêm hay xóa
//whichEffect bằng 6 là tạo mới các vertex,7 là xóa các vertex
void SaveVertexCreatOrDelete(int whichEffect) {
	char pathObject[40], pathAttribute[40];
	getNameTxtForSave(txtUsing, offsetTxtUsing, pathObject, pathAttribute);
	//đầu tiên lưu lại tất cả các thuộc tính của app
	saveAttributeApp(pathAttribute,
		positionVerticesChoice, positionFacesChoice,
		positionChoiceRowOrColumn, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
		itemsChoice, mouseModel, modelStyleDraw, modelTop,
		modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
		whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
		radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
		menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
		menu_rotateX, menu_rotateY, menu_rotateZ,
		menu_scaleX, menu_scaleY, menu_scaleZ,
		symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
		symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
		symmetryVertices, symmetryObjects,
		startAndEndSymmetry1, startAndEndSymmetry2,
		isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
		tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);
	//lưu lại các thông tin về các vertex vừa được tạo hay thêm vào
	saveInformationVertices(pathObject, whichEffect, itemsChoice.at(0), positionVerticesChoice, symmetryObjects,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
		coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
		objectCustom0Array);
}


//các hàm dùng cho menu phía bên phải *****************

//hàm kiểm tra xem có nhấn trung phím nào trong attribute không
bool checkToChangeAttribute(int x, int y,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	if (!itemsChoice.empty()) {
		itemChoice item = itemsChoice.at(0);
		//đầu tiên cúa lưu lại thuộc tính của hình đã(nếu vị trí nhấn nằm trong khoảng hộp menu)
		if (x > leftMenu && x<rightMenu && y>topMenu && y < bottomMenu) {
			//lưu lại hình trước khi thay đổi
			SaveObjectCreatOrDelete(5);
			//nếu không nhấn trúng thay đổi thuộc tính thì lùi offsetTxt lại và xóa vị trí vừa thêm trong mảng txtUsing
			bool good = changeAttributeObject(x, y, item,
				mouseModel, modelEditStyle,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice,
				item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				leftMenu, rightMenu, topMenu, bottomMenu,
				sphereArray, cubeArray, cubeRoundArray, coneArray,
				cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
			if (good) {
				//lưu lại hình sau khi thay đổi
				SaveObjectCreatOrDelete(5);
			}
			else
			{
				//lùi offsetTxt lại và xóa vị trí vừa thêm trong mảng txtUsing
				txtUsing.pop_back();
				offsetTxtUsing -= 1;
			}

			//việc nhấn trúng trong vùng item này là return true được rồi
			return true;
		}
	}
	return false;
}
//hàm áp dụng các giá trị biến đổi trong menu cho các hình đang được chọn
void appendTransformInMenu() {
	if (!itemsChoice.empty()) {
		if (menu_whichTransform == 0) {
			if (modelEditStyle == 0) {
				//lấy vị trí tâm của object đầu tiên trong số các object đang được chọn
				getCenterObjectChoice(itemsChoice.at(0),
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau đó thực hiện biến đổi
				moveObject(menu_translateX, menu_translateY, menu_translateZ,
					itemsChoice, centerObjectOrVertices,
					symmetryObjects,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				//lấy vị trí tâm của các vertex đang được chọn,lấy tâm cho các vertexSymmetry và objectSymmetry(nếu có)
				getCenterVertexsForScale(itemsChoice.at(0), positionVerticesChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau rồi mới biến đổi
				moveVertex(menu_translateX, menu_translateY, menu_translateZ,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					itemsChoice, positionVerticesChoice,
					symmetry_translateX, symmetry_translateY, symmetry_translateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			//Chuyển các giá trị vào biến để lưu lại giá trị thay đổi
			move_X = menu_translateX;
			move_Y = menu_translateY;
			move_Z = menu_translateZ;

			//lưu lại thông tin biến đổi vào tệp .txt
			SaveInformationTransform();
		}
		else if (menu_whichTransform == 1) {
			if (modelEditStyle == 0) {
				//lấy vị trí tâm của object đầu tiên trong số các object đang được chọn
				getCenterObjectChoice(itemsChoice.at(0),
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau đó thực hiện biến đổi
				rotateObject(menu_rotateX, menu_rotateY, menu_rotateZ,
					itemsChoice,
					symmetryObjects,
					symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				//lấy vị trí tâm của các vertex đang được chọn,lấy tâm cho các vertexSymmetry và objectSymmetry(nếu có)
				getCenterVertexsForScale(itemsChoice.at(0), positionVerticesChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau rồi mới biến đổi
				rotateVertex(menu_rotateX, menu_rotateY, menu_rotateZ, itemsChoice, positionVerticesChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			//Chuyển các giá trị vào biến để lưu lại giá trị thay đổi
			rotate_X = menu_rotateX;
			rotate_Y = menu_rotateY;
			rotate_Z = menu_rotateZ;

			//lưu lại thông tin biến đổi vào tệp .txt
			SaveInformationTransform();
		}
		else if (menu_whichTransform == 2) {
			if (modelEditStyle == 0) {
				//lấy vị trí tâm của object đầu tiên trong số các object đang được chọn
				getCenterObjectChoice(itemsChoice.at(0),
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau đó thực hiện biến đổi
				scaleObject(menu_scaleX, menu_scaleY, menu_scaleZ,
					itemsChoice,
					symmetryObjects,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			else
			{
				//lấy vị trí tâm của các vertex đang được chọn,lấy tâm cho các vertexSymmetry và objectSymmetry(nếu có)
				getCenterVertexsForScale(itemsChoice.at(0), positionVerticesChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau rồi mới biến đổi
				scaleVertex(menu_scaleX, menu_scaleY, menu_scaleZ, itemsChoice, positionVerticesChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry,
					symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
			//Chuyển các giá trị vào biến để lưu lại giá trị thay đổi
			scale_X = menu_scaleX - 1.0;
			scale_Y = menu_scaleY - 1.0;
			scale_Z = menu_scaleZ - 1.0;

			//lưu lại thông tin biến đổi vào tệp .txt
			SaveInformationTransform();
		}
	}
}
//hàm chọn các thông tin cũng như áp dụng biến đổi cho tất cả các hình
bool checkToApplyTransform(int x, int y,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	//xác định có nhấn nút chuyển kiểu biến đổi không
	if (x > leftMenu + 5 && x< leftMenu + 15 && y > topMenu + 31 && y < topMenu + 41) {
		menu_whichTransform--;
		if (menu_whichTransform == -1) {
			menu_whichTransform = 2;
		}
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);
		item_choice_in_MenuGroup2 = -1;
		return true;
	}
	else if (x > leftMenu + 120 && x< leftMenu + 130 && y>topMenu + 31 && y < topMenu + 41) {
		menu_whichTransform++;
		if (menu_whichTransform == 3) {
			menu_whichTransform = 0;
		}
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);
		item_choice_in_MenuGroup2 = -1;
		return true;
	}
	else
	{
		//xác định nút được nhấn (tùy theo kiểu bo để xác định các nút nhấn khác nhau)
		if (menu_whichTransform == 0) {
			//leftMenu + 10, topMenu + 60        leftMenu + 10, topMenu + 80      leftMenu + 10, topMenu + 100
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateX -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateX += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateY -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateY += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateZ -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_translateZ += 0.01f;
				return true;
			}
		}
		else if (menu_whichTransform == 1) {
			//leftMenu + 10, topMenu + 60        leftMenu + 10, topMenu + 80      leftMenu + 10, topMenu + 100
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateX -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateX += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateY -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateY += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateZ -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_rotateZ += 0.01f;
				return true;
			}
		}
		else if (menu_whichTransform == 2)
		{
			//leftMenu + 10, topMenu + 60        leftMenu + 10, topMenu + 80      leftMenu + 10, topMenu + 100
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleX -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleX += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleY -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleY += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleZ -= 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 100 && y < topMenu + 110) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ,
					menu_rotateX, menu_rotateY, menu_rotateZ,
					menu_scaleX, menu_scaleY, menu_scaleZ);
				menu_scaleZ += 0.01f;
				return true;
			}
		}
	}

	//kiểm tra xem có nhấn trúng nút áp dụng biến đổi không không
	if (x > rightMenu - 140 && x<rightMenu - 15 && y>bottomMenu - 50 && y < bottomMenu - 20) {
		//khi nhấn trúng nút áp dụng thì đặt item_choice_in_MenuGroup2 thành -1 và áp dụng
		//giá trị trong mảng char vào vị trí tương ứng
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);

		appendTransformInMenu();
		return true;
	}

	//nếu không nhấn trúng các nút trên thì kiểm tra xem có nhấn trúng item không để đặt item được chọn
	if (x > leftMenu + 20 && x< leftMenu + 115 && y > topMenu + 31 && y < topMenu + 41) {
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);
		item_choice_in_MenuGroup2 = 0;
		return true;
	}
	//leftMenu + 10, topMenu + 60        leftMenu + 10, topMenu + 80      leftMenu + 10, topMenu + 100
	else if (x > leftMenu + 10 + 105 && x< leftMenu + 10 + 165 && y > topMenu + 60 && y < topMenu + 70) {
		//nếu trước đó chọn trúng menu khác và đang ở chế độ chỉnh sửa thì áp dụng giá trị cho menu trước
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);

		//nếu đã nhấn trúng item 1 lần và nhấn thêm 1 lần nữa thì chuyển sang chế độ chỉnh sửa 
		if (item_choice_in_MenuGroup2 == 1 && !menu_isChangeCharNumberValue) {
			//xóa các giá trị trong mảng để dùng lại
			memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
			if (menu_whichTransform == 0) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_translateX);
			}
			else if (menu_whichTransform == 1) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateX);
			}
			else
			{
				changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleX);
			}
			menu_isChangeCharNumberValue = true;
		}

		item_choice_in_MenuGroup2 = 1;
		return true;
	}
	else if (x > leftMenu + 10 + 105 && x< leftMenu + 10 + 165 && y > topMenu + 80 && y < topMenu + 90) {
		//nếu trước đó chọn trúng menu khác và đang ở chế độ chỉnh sửa thì áp dụng giá trị cho menu trước
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);
		//nếu đã nhấn trúng item 1 lần và nhấn thêm 1 lần nữa thì chuyển sang chế độ chỉnh sửa 
		if (item_choice_in_MenuGroup2 == 2 && !menu_isChangeCharNumberValue) {
			//xóa các giá trị trong mảng để dùng lại
			memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
			if (menu_whichTransform == 0) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_translateY);
			}
			else if (menu_whichTransform == 1) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateY);
			}
			else
			{
				changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleY);
			}
			menu_isChangeCharNumberValue = true;
		}

		item_choice_in_MenuGroup2 = 2;
		return true;
	}
	else if (x > leftMenu + 10 + 105 && x< leftMenu + 10 + 165 && y > topMenu + 100 && y < topMenu + 110) {
		//nếu trước đó chọn trúng menu khác và đang ở chế độ chỉnh sửa thì áp dụng giá trị cho menu trước
		appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
			menu_isChangeCharNumberValue,
			menu_translateX, menu_translateY, menu_translateZ,
			menu_rotateX, menu_rotateY, menu_rotateZ,
			menu_scaleX, menu_scaleY, menu_scaleZ);
		//nếu đã nhấn trúng item 1 lần và nhấn thêm 1 lần nữa thì chuyển sang chế độ chỉnh sửa 
		if (item_choice_in_MenuGroup2 == 3 && !menu_isChangeCharNumberValue) {
			//xóa các giá trị trong mảng để dùng lại
			memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
			if (menu_whichTransform == 0) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_translateZ);
			}
			else if (menu_whichTransform == 1) {
				changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateZ);
			}
			else
			{
				changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleZ);
			}
			menu_isChangeCharNumberValue = true;
		}

		item_choice_in_MenuGroup2 = 3;
		return true;
	}

	return false;
}

//hiện cụm menu thứ 2
void showMenuGroup2(int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	glDisable(GL_LIGHTING);

	//vẽ hình tứ giác bao cụm menu phía trên
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu, topMenu);
	glVertex2f(leftMenu, bottomMenu);
	glVertex2f(rightMenu, topMenu);
	glVertex2f(rightMenu, bottomMenu);
	glEnd();

	//hiện các tên các cụm menu để nhấn chọn
	int topGroupMenu = topMenu + 15, positionL = leftMenu + 2;
	for (int i = 0; i < 5; i++) {
		if (i == modelMenuGroup2) {
			glColor3f(0.2f, 0.25f, 0.26f);
		}
		else
		{
			glColor3f(0.1, 0.18, 0.2);
		}
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(positionL - 1, topMenu + 2);
		glVertex2f(positionL - 1, topMenu + 22);
		glVertex2f(positionL + 47, topMenu + 2);
		glVertex2f(positionL + 47, topMenu + 22);
		glEnd();
		positionL += 50;
	}
	//vẽ menu tool ở sau cùng
	if (modelMenuGroup2 == 5) {
		glColor3f(0.2f, 0.25f, 0.26f);
	}
	else
	{
		glColor3f(0.1, 0.18, 0.2);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(rightMenu - 50, topMenu + 2);
	glVertex2f(rightMenu - 50, topMenu + 22);
	glVertex2f(rightMenu - 1, topMenu + 2);
	glVertex2f(rightMenu - 1, topMenu + 22);
	glEnd();

	//hiện chữ trên menu
	glColor3f(1.0, 1.0, 1.0);
	drawText(leftMenu + 2, topGroupMenu, "Texture", "helvetica", 12);
	drawText(leftMenu + 52, topGroupMenu, "Attribute", "helvetica", 12);
	drawText(leftMenu + 102, topGroupMenu, "Round", "helvetica", 12);
	drawText(leftMenu + 152, topGroupMenu, "Transfo..", "helvetica", 12);
	drawText(leftMenu + 202, topGroupMenu, "Symmet..", "helvetica", 12);
	//vẽ menu tool ở sau cùng
	drawText(rightMenu - 40, topGroupMenu, "Tool", "helvetica", 12);


	//vẽ khung hiện các menu
	if (modelMenuGroup2 != -1) {
		glColor3f(0.2f, 0.25f, 0.26f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftMenu + 1, topGroupMenu + 4);
		glVertex2f(leftMenu + 1, bottomMenu - 1);
		glVertex2f(rightMenu - 1, topGroupMenu + 4);
		glVertex2f(rightMenu - 1, bottomMenu - 1);
		glEnd();

		//tùy xem menu nào được chọn để hiện các thông tin khác nhau
		if (modelMenuGroup2 == 0) {
			showMenuTexture(itemTextureWindow,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
		else if (modelMenuGroup2 == 1) {
			if (!itemsChoice.empty()) {
				showToolChangeAttribute(itemsChoice.at(0), item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					leftMenu, rightMenu, topMenu, bottomMenu,
					sphereArray, cubeRoundArray, coneArray, cylinderArray, emptyCylinderArray, torusArray,objectCustom0Array);
			}
		}
		else if (modelMenuGroup2 == 2) {
			showToolChangeRoundEffect(item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				isRoundCorner, whichStyleRound,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical, radiusRoundHorizontal, radiusRoundVertical,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
		else if (modelMenuGroup2 == 3) {
			showToolTransform(menu_whichTransform, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				menu_translateX, menu_translateY, menu_translateZ, menu_rotateX,
				menu_rotateY, menu_rotateZ, menu_scaleX, menu_scaleY, menu_scaleZ,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
		else if (modelMenuGroup2 == 4) {
			showToolOfSymmetry(itemsChoice, item_choice_in_MenuGroup2,
				symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
				symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				startAndEndSymmetry1, startAndEndSymmetry2,
				isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
		else if (modelMenuGroup2 == 5) {
			showToolOfApp(item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				tool_isRemind, tool_isShowBeforeDraw, tool_isDrawNet,
				tool_arrowSize, tool_circleSize,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
	}

	glEnable(GL_LIGHTING);
}

//hàm kiểm tra xem cụm menu nào được chọn
bool checkChoiceMenuGroup2(int x, int y,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	int topGroupMenu = topMenu + 15, positionL = leftMenu + 2;
	for (int i = 0; i < 5; i++) {
		if (x > positionL - 1 && x< positionL + 47 && y>topMenu + 2 && y < topMenu + 22) {
			modelMenuGroup2 = i;
			//nếu chọn trúng menu trong cụm menu thì đặt item con được chọn về -1
			item_choice_in_MenuGroup2 = -1;
			return true;
		}
		positionL += 50;
	}
	//kiểm tra menuTool riêng
	if (x > rightMenu - 50 && x< rightMenu - 1 && y>topMenu + 2 && y < topMenu + 22) {
		modelMenuGroup2 = 5;
		//nếu chọn trúng menu trong cụm menu thì đặt item con được chọn về -1
		item_choice_in_MenuGroup2 = -1;
		return true;
	}

	//nếu không chọn trúng các menu cụm thì kiểm tra xem có chọn trúng các menu con phía trong không
	if (modelMenuGroup2 == 0) {
		return checkToChoiceMenuTexture(x, y, itemTextureWindow, itemsChoice,
			leftMenu, rightMenu, topMenu, bottomMenu,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
	else if (modelMenuGroup2 == 1) {
		if (!itemsChoice.empty()) {
			return checkToChangeAttribute(x, y,
				leftMenu, rightMenu, topMenu, bottomMenu);
		}
		else
		{
			return false;
		}
	}
	else if (modelMenuGroup2 == 2) {
		return checkToApplyRound(x, y, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			isRoundCorner, whichStyleRound,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical, radiusRoundHorizontal, radiusRoundVertical,
			leftMenu, rightMenu, topMenu, bottomMenu,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
	else if (modelMenuGroup2 == 3) {
		return checkToApplyTransform(x, y,
			leftMenu, rightMenu, topMenu, bottomMenu);
	}
	else if (modelMenuGroup2 == 4) {
		return checkToChoiceToolOfSymmetry(x, y, item_choice_in_MenuGroup2,
			symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
			itemsChoice, positionChoiceRowOrColumn, positionVerticesChoice,
			symmetry_translateX, symmetry_translateY, symmetry_translateZ,
			symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
			symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
			symmetryVertices, symmetryObjects,
			startAndEndSymmetry1, startAndEndSymmetry2,
			isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
			leftMenu, rightMenu, topMenu, bottomMenu,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
	else if (modelMenuGroup2 == 5) {
		return checkToChoiceToolApp(x, y, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_isRemind, tool_isShowBeforeDraw, tool_isDrawNet,
			tool_arrowSize, tool_circleSize,
			leftMenu, rightMenu, topMenu, bottomMenu);
	}
	return false;
}
//hàm load các thuộc tính đã lưu
void loadAttributeInDataChoice() {
	char nameAtributeTxt[3][40] = {
		{ "D://openGL_txt//attribute_app.txt" },{ "D://openGL_txt//app_attribute1.txt" },
		{ "D://openGL_txt//app_attribute2.txt" }
	};
	//lấy dữ liệu thuộc tính app đã lưu lần trước
	loadAttributeApp(nameAtributeTxt[whichDataChoice],
		positionVerticesChoice, positionFacesChoice,
		positionChoiceRowOrColumn, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
		itemsChoice, mouseModel, modelStyleDraw, modelTop,
		modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
		whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
		radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
		menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
		menu_rotateX, menu_rotateY, menu_rotateZ,
		menu_scaleX, menu_scaleY, menu_scaleZ,
		symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
		symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
		symmetryVertices, symmetryObjects,
		startAndEndSymmetry1, startAndEndSymmetry2,
		isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
		tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);
}
//hàm load các Object đã lưu
void loadObjectInDataChoice() {
	if (whichDataChoice == 0) {
		//lấy dữ liệu lần trước lưu về các object để tiếp tục làm
		loadDataBase(triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
			cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
			torusArray, pictureArray,
			objectCustom0Array, idsUsing);
	}
	else if (whichDataChoice == 1)
	{
		loadObjectsInTxt("D://openGL_txt//app_object1.txt",
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array, idsUsing);
	}
	else
	{
		loadObjectsInTxt("D://openGL_txt//app_object2.txt",
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array, idsUsing);
	}
}

//hàm lưu các thuộc tính của app
void saveAttributeInDataChoice() {
	char nameAtributeTxt[3][40] = {
		{ "D://openGL_txt//attribute_app.txt" },{ "D://openGL_txt//app_attribute1.txt" },
		{ "D://openGL_txt//app_attribute2.txt" }
	};
	saveAttributeApp(nameAtributeTxt[whichDataChoice],
		positionVerticesChoice, positionFacesChoice,
		positionChoiceRowOrColumn, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
		itemsChoice, mouseModel, modelStyleDraw, modelTop,
		modelEditStyle, modelSpace, modelMenuGroup1, modelMenuGroup2,
		whichStyleRound, numberVertexRound2Side, numberVertexRoundHorizontal, numberVertexRoundVertical,
		radiusRound2Side, radiusRoundHorizontal, radiusRoundVertical,
		menu_whichTransform, menu_translateX, menu_translateY, menu_translateZ,
		menu_rotateX, menu_rotateY, menu_rotateZ,
		menu_scaleX, menu_scaleY, menu_scaleZ,
		symmetryVertexOrObject, whichStyleSymmetry, whichItemSymmetry,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
		symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
		symmetryVertices, symmetryObjects,
		startAndEndSymmetry1, startAndEndSymmetry2,
		isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
		tool_isShowBeforeDraw, tool_isRemind, tool_isDrawNet, tool_arrowSize, tool_circleSize);
}
//hàm lưu các Object của app
void saveObjectInDataChoice() {
	if (whichDataChoice == 0) {
		saveDataBase(triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
	else if (whichDataChoice == 1)
	{
		saveObjectsInTxt("D://openGL_txt//app_object1.txt",
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
	else
	{
		saveObjectsInTxt("D://openGL_txt//app_object2.txt",
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
	}
}

//hàm khởi tạo các biến mặc định(và các thông tin trong tệp txt nếu có)
void initializationDefaulValue() {
	zoomCamera = -17.0f; rotateCameraX = 38.0f; rotateCameraY = 300.0f;
	translateCameraX = 0.0f; translateCameraY = 0.0f; translateCameraZ = 0.0f;
	zoomCameraImage1 = -30.0f; translateCameraXImage1 = 0.0f; translateCameraYImage1 = 0.0f;
	zoomCameraImage2 = -30.0f; translateCameraXImage2 = 0.0f; translateCameraYImage2 = 0.0f;

	lightPosition[0] = 0.0f; lightPosition[1] = 50.0f; lightPosition[2] = 7.0f; lightPosition[3] = 1.0f;
	lightPositionFront[0] = 0.0f; lightPositionFront[1] = 0.0f; lightPositionFront[2] = 20.0f; lightPositionFront[3] = 1.0f;
	lightPositionLeft[0] = -20.0f; lightPositionLeft[1] = 0.0f; lightPositionLeft[2] = 0.0f; lightPositionLeft[3] = 1.0f;
	lightAmbient[0] = 0.3f; lightAmbient[1] = 0.3f; lightAmbient[2] = 0.3f; lightAmbient[3] = 0.3f;
	lightDiffuse[0] = 0.8f; lightDiffuse[1] = 0.8f; lightDiffuse[2] = 0.8f; lightDiffuse[3] = 0.8f;
	lightSpecular[0] = 1.0f; lightSpecular[1] = 1.0f; lightSpecular[2] = 1.0f; lightSpecular[3] = 1.0f;
	lightOff[0] = 0.3f; lightOff[1] = 0.3f; lightOff[2] = 0.3f; lightOff[3] = 0.3f;

	colorDefaul[0] = 0.2f;
	colorDefaul[1] = 0.2f;
	colorDefaul[2] = 0.2f;
	colorDefaul[3] = 1.0f;

	colorScreen[0] = 0.3f;
	colorScreen[1] = 0.3f;
	colorScreen[2] = 0.35f;
	colorScreen[3] = 1.0f;

	isFullScreen = false;

	isOpenChoiceForder = false;
	whichDataChoice = 0;

	isChoiceVertexNow = false;

	whichArrowChoice = -1; whichQuadChoice = -1;
	positionAddRowOrColumn = { -1,-1,-1 };
	positionDeleteRowOrColumn = { -1,-1,-1 };
	isMoveCenterRotate = false;
	itemRotate = { -1,-1,-1,true };
	areaChoice = { { 0,0,0 },1.0,{ { 0,0,0 },{ 0,0,0 },{ 0,0,0 } },false };
	centerObjectOrVertices = { 0.0f,0.0f,0.0f };
	//bằng NULL nghĩa là không thể tìm ra tâm,do ít nhất có 1 vertex không tìm ra được đỉnh đối xứng
	centerObjectOrVerticesSymmetry = { NULL,NULL,NULL };

	isAgreePossition = true;

	offsetTxtUsing = -1;
	offsetOfVertexInfor = 0;
	modelTitleApp = -1;
	modelApp = -1;
	mouseModel = 0;
	modelStyleDraw = 0;
	modelTop = -1;
	modelEdit = -1;
	modelEditStyle = 0;
	modelSpace = 1;
	changeRotateFor2D = -1;

	mouseDownX = -1; mouseDownY = -1;
	lastTouchX = -1; lastTouchY = -1;
	move_X = 0.0f; move_Y = 0.0f; move_Z = 0.0f;
	scale_X = 0.0f; scale_Y = 0.0f; scale_Z = 0.0f;
	rotate_X = 0.0f; rotate_Y = 0.0f; rotate_Z = 0.0f;
	lastMouseModel = 0;
	modelMenuGroup1 = 1; modelMenuGroup2 = 0;
	item_choice_in_MenuGroup2 = -1;
	isChoiceColorPicker = false; isRoundCorner = false; menu_isChangeCharNumberValue = false;
	whichStyleRound = 0;
	numberVertexRound2Side = 5; numberVertexRoundHorizontal = 5; numberVertexRoundVertical = 5;
	radiusRound2Side = 1.0f; radiusRoundHorizontal = 1.0f; radiusRoundVertical = 1.0f;
	menu_whichTransform = 0;
	menu_translateX = 0.0f; menu_translateY = 0.0f; menu_translateZ = 0.0f;
	menu_rotateX = 0.0f; menu_rotateY = 0.0f; menu_rotateZ = 0.0f;
	menu_scaleX = 1.0f; menu_scaleY = 1.0f, menu_scaleZ = 1.0f;

	symmetryVertexOrObject = 0;
	whichStyleSymmetry = 0;
	whichItemSymmetry = -1;
	symmetry_translateX = false;
	symmetry_translateY = false;
	symmetry_translateZ = false;
	symmetry_rotateX = false;
	symmetry_rotateY = false;
	symmetry_rotateZ = false;
	symmetry_scaleX = false;
	symmetry_scaleY = false;
	symmetry_scaleZ = false;
	startAndEndSymmetry1[0] = 0;
	startAndEndSymmetry1[1] = 0;
	startAndEndSymmetry2[0] = 0;
	startAndEndSymmetry2[1] = 0;
	isGetSymmetryLikeClockwise1 = true;
	isGetSymmetryLikeClockwise2 = true;

	tool_isShowBeforeDraw = false;
	tool_isRemind = false;
	tool_isDrawNet = true;
	tool_arrowSize = 1.0f;
	tool_circleSize = 1.0f;

	//đặt các vị trí cho menu
	positionMenuTitle[0][0] = 0;
	positionMenuTitle[0][1] = 0;
	positionMenuTitle[1][1] = 0;
	positionMenuTitle[2][1] = 0;
	positionMenuTitle[3][1] = 0;

	positionMenuApp[0][0] = 129;
	positionMenuApp[1][0] = 160;
	positionMenuApp[2][0] = 191;
	positionMenuApp[3][0] = 222;
	positionMenuApp[4][0] = 253;
	positionMenuApp[0][1] = 40;
	positionMenuApp[1][1] = 40;
	positionMenuApp[2][1] = 40;
	positionMenuApp[3][1] = 40;
	positionMenuApp[4][1] = 40;

	positionMenuMouse[0][0] = 1;
	positionMenuMouse[1][0] = 1;
	positionMenuMouse[2][0] = 1;
	positionMenuMouse[3][0] = 1;
	positionMenuMouse[4][0] = 1;
	positionMenuMouse[5][0] = 1;
	positionMenuMouse[6][0] = 1;
	positionMenuMouse[7][0] = 1;
	positionMenuMouse[8][0] = 1;
	positionMenuMouse[0][1] = 142;
	positionMenuMouse[1][1] = 183;
	positionMenuMouse[2][1] = 224;
	positionMenuMouse[3][1] = 265;
	positionMenuMouse[4][1] = 306;
	positionMenuMouse[5][1] = 347;
	positionMenuMouse[6][1] = 388;
	positionMenuMouse[7][1] = 429;
	positionMenuMouse[8][1] = 470;

	positionMenuTop[0][0] = 52;
	positionMenuTop[1][0] = 93;
	positionMenuTop[2][0] = 134;
	positionMenuTop[3][0] = 175;
	positionMenuTop[4][0] = 216;
	positionMenuTop[5][0] = 257;
	positionMenuTop[6][0] = 298;
	positionMenuTop[7][0] = 339;
	positionMenuTop[8][0] = 380;
	positionMenuTop[9][0] = 441;
	positionMenuTop[10][0] = 482;
	positionMenuTop[0][1] = 73;
	positionMenuTop[1][1] = 73;
	positionMenuTop[2][1] = 73;
	positionMenuTop[3][1] = 73;
	positionMenuTop[4][1] = 73;
	positionMenuTop[5][1] = 73;
	positionMenuTop[6][1] = 73;
	positionMenuTop[7][1] = 73;
	positionMenuTop[8][1] = 73;
	positionMenuTop[9][1] = 73;
	positionMenuTop[10][1] = 73;

	positionMenuEdit[0][0] = 400;
	positionMenuEdit[1][0] = 431;
	positionMenuEdit[2][0] = 462;
	positionMenuEdit[3][0] = 497;
	positionMenuEdit[4][0] = 528;
	positionMenuEdit[5][0] = 559;
	positionMenuEdit[6][0] = 590;
	positionMenuEdit[7][0] = 624;
	positionMenuEdit[0][1] = 40;
	positionMenuEdit[1][1] = 40;
	positionMenuEdit[2][1] = 40;
	positionMenuEdit[3][1] = 40;
	positionMenuEdit[4][1] = 40;
	positionMenuEdit[5][1] = 40;
	positionMenuEdit[6][1] = 40;
	positionMenuEdit[7][1] = 40;

	positionMenuEditStyle[0][1] = 40;
	positionMenuEditStyle[1][1] = 40;
	positionMenuEditStyle[2][1] = 40;
	positionMenuEditStyle[3][1] = 40;

	positionMenuSpace[0][0] = 1;
	positionMenuSpace[1][0] = 1;
	positionMenuSpace[2][0] = 1;
	positionMenuSpace[0][1] = 700;
	positionMenuSpace[1][1] = 741;
	positionMenuSpace[2][1] = 782;

	//load các thuộc tính đã lưu(nếu có)
	loadAttributeInDataChoice();
}

//*******các hàm dành cho window và các hàm dùng chung

//hàm thay đổi kích thước của các cửa sổ
void changeSizeWindow(int width, int height) {
	glutSetWindow(subwindow);
	glutPositionWindow(0, 0);
	glutReshapeWindow(width, height);

	//khoảng cách mỗi menu chiếm
	int menuWidth = 42, topScreen = 40 + 42 + 32;
	int totalWidth = width * 0.8 - menuWidth, totalHeight = height - topScreen - menuWidth;

	//nếu ở chế độ 1 màn hình thì đặt kích thước khác còn chế độ 3 màn hình thì đặt kích thước khác
	if (modelSpace == 2) {
		float halfTotalWidth = totalWidth / 2;
		//tính kích thước của màn hình con
		screen_width = halfTotalWidth - GAP / 2;
		screen_height = totalHeight;

		screen2D_width = halfTotalWidth - GAP / 2;
		screen2D_height = totalHeight / 2 - GAP / 2;

		glutSetWindow(screen1);
		glutPositionWindow(42, topScreen);
		glutReshapeWindow(screen2D_width, screen2D_height);

		glutSetWindow(screen2);
		glutPositionWindow(42, screen2D_height + topScreen + GAP);
		glutReshapeWindow(screen2D_width, screen2D_height);

		glutSetWindow(screen);
		glutPositionWindow(screen2D_width + menuWidth + GAP, topScreen);
		glutReshapeWindow(screen_width, screen_height);
	}
	else
	{
		//tính kích thước của màn hình con
		screen_width = totalWidth;
		screen_height = totalHeight;

		glutSetWindow(screen1);
		glutPositionWindow(0, 0);
		glutReshapeWindow(0, 0);

		glutSetWindow(screen2);
		glutPositionWindow(0, 0);
		glutReshapeWindow(0, 0);

		glutSetWindow(screen);
		glutPositionWindow(42, topScreen);
		glutReshapeWindow(screen_width, screen_height);
	}
}

//các load tất cả màn hình
void redisplay_all(void)
{
	glutSetWindow(screen);
	glutPostRedisplay();
	if (modelSpace == 2) {
		glutSetWindow(screen1);
		glutPostRedisplay();
		glutSetWindow(screen2);
		glutPostRedisplay();
	}
	glutSetWindow(subwindow);
	glutPostRedisplay();
}
//hàm load tất cả screen
void redisplay_screens() {
	if (modelSpace == 2) {
		glutSetWindow(screen1);
		glutPostRedisplay();
		glutSetWindow(screen2);
		glutPostRedisplay();
	}
	glutSetWindow(screen);
	glutPostRedisplay();
}
//hàm load chỉ subWindow(các menu)
void redisplay_subWindow() {
	glutSetWindow(subwindow);
	glutPostRedisplay();
}

void drawObjectPickAndDraw(float x3D, float y3D, float z3D, bool isCheck);
//hàm này dùng chung cho toàn bộ các màn hình luôn
bool keyboardForApp(unsigned char key) {
	/*từ số 0 đến 9 có đại diện là 48 đến 57
	dấu . là 46*/
	//key==8 phim xoa
	//key=13 phim enter
	//key= 127 là delete
	//các hàm dịch chuyển cảnh
	switch (key)
	{
		//nếu nhấn trùng các phím số thì tìm vị trí đầu tiên NULL để đặt vào
	case '.':
	case '-':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
		//nếu đang ở chế độ chỉnh sửa giá trị
		if (menu_isChangeCharNumberValue) {
			//nếu có dấu trừ phí trước thì 7 là số phần tử nhiều nhất
			//nếu không thì là 6
			if (menu_charNumberValue[0] == '-') {
				//7 là vị trí xa nhất có số vì -999.00 là giá trị lớn nhất
				for (int i = 0; i < 7; i++) {
					if (menu_charNumberValue[i] == NULL) {
						menu_charNumberValue[i] = (char)key;
						//đoạn này bị lỗi,các giá trị phía sau bị nhảy nên ta đặt thành NULL hết
						for (int k = i + 1; k < 11; k++) {
							menu_charNumberValue[k] = NULL;
						}
						break;
					}
				}
			}
			else
			{
				//6 là vị trí xa nhất có số vì 999.00 là giá trị lớn nhất
				for (int i = 0; i < 6; i++) {
					if (menu_charNumberValue[i] == NULL) {
						menu_charNumberValue[i] = (char)key;
						//đoạn này bị lỗi,các giá trị phía sau bị nhảy nên ta đặt thành NULL hết
						for (int k = i + 1; k < 11; k++) {
							menu_charNumberValue[k] = NULL;
						}
						break;
					}
				}
			}
		}
	}
			  break;
			  //nếu nhấn trúng phím xóa thì đặt giá trị sau cùng thành NULL
	case 8: {
		//nếu đang ở chế độ chỉnh sửa giá trị
		if (menu_isChangeCharNumberValue) {
			for (int i = 0; i < 8; i++) {
				if (menu_charNumberValue[i] == NULL) {
					if (i != 0) {
						menu_charNumberValue[i - 1] = NULL;
					}
					else
					{
						//nếu chỉ còn 1 số thì đặt số đó thành 0
						menu_charNumberValue[0] = NULL;
					}
					break;
				}
			}
		}
	}
			break;
			//khi nhấn phím enter thì đặt chế độ chỉnh sửa về false
	case 13: {
		if (modelMenuGroup2 == 1) {
			if (itemsChoice.size() == 1) {
				//khi nhấn phím enter mà nếu đang ở chế độ chỉnh sửa thì trở về chế độ thường
				if (menu_isChangeCharNumberValue) {
					//lưu lại giá trị trước khi thay đổi
					SaveObjectCreatOrDelete(5);

					bool isChange = appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						itemsChoice.at(0),
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);

					//nếu có thay đổi thì lưu lại giá trị sau khi thay đổi
					if (isChange) {
						SaveObjectCreatOrDelete(5);
					}
					//nếu không có thay đỏi thì xóa file vừa lưu đi
					else
					{
						offsetTxtUsing--;
						txtUsing.pop_back();
					}
				}
				//nếu ở chế độ thường thì chuyển sang chế độ chỉnh sửa
				else
				{
					getCharArrayFromValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						itemsChoice.at(0),
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
			}
		}
		else if (modelMenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
			}
			else
			{
				if (whichStyleRound == 0) {
					if (item_choice_in_MenuGroup2 == 1) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberFloatToCharArray(menu_charNumberValue, radiusRound2Side);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 2) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberIntToCharArray(menu_charNumberValue, numberVertexRound2Side);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 3) {
						appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
							menu_charNumberValue, menu_isChangeCharNumberValue,
							numberVertexRound2Side, radiusRound2Side,
							numberVertexRoundHorizontal, numberVertexRoundVertical,
							radiusRoundHorizontal, radiusRoundVertical);
						appendRoundInMenu(isRoundCorner, whichStyleRound,
							numberVertexRound2Side, radiusRound2Side,
							numberVertexRoundHorizontal, numberVertexRoundVertical, radiusRoundHorizontal, radiusRoundVertical,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
							coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
					}
				}
				else
				{
					if (item_choice_in_MenuGroup2 == 1) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberFloatToCharArray(menu_charNumberValue, radiusRoundHorizontal);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 2) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberIntToCharArray(menu_charNumberValue, numberVertexRoundHorizontal);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 3) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberFloatToCharArray(menu_charNumberValue, radiusRoundVertical);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 4) {
						//xóa các giá trị trong mảng để dùng lại
						memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
						changeNumberIntToCharArray(menu_charNumberValue, numberVertexRoundVertical);
						menu_isChangeCharNumberValue = true;
					}
					else if (item_choice_in_MenuGroup2 == 5) {
						appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
							menu_charNumberValue, menu_isChangeCharNumberValue,
							numberVertexRound2Side, radiusRound2Side,
							numberVertexRoundHorizontal, numberVertexRoundVertical,
							radiusRoundHorizontal, radiusRoundVertical);
						appendRoundInMenu(isRoundCorner, whichStyleRound,
							numberVertexRound2Side, radiusRound2Side,
							numberVertexRoundHorizontal, numberVertexRoundVertical, radiusRoundHorizontal, radiusRoundVertical,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
							coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
					}
				}
			}
		}
		else if (modelMenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
					menu_isChangeCharNumberValue,
					menu_translateX, menu_translateY, menu_translateZ, menu_rotateX,
					menu_rotateY, menu_rotateZ, menu_scaleX, menu_scaleY, menu_scaleZ);
			}
			else
			{
				if (item_choice_in_MenuGroup2 == 1) {
					//xóa các giá trị trong mảng để dùng lại
					memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
					if (menu_whichTransform == 0) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_translateX);
					}
					else if (menu_whichTransform == 1) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateX);
					}
					else
					{
						changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleX);
					}
					menu_isChangeCharNumberValue = true;
				}
				else if (item_choice_in_MenuGroup2 == 2) {
					//xóa các giá trị trong mảng để dùng lại
					memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
					if (menu_whichTransform == 0) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_translateY);
					}
					else if (menu_whichTransform == 1) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateY);
					}
					else
					{
						changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleY);
					}
					menu_isChangeCharNumberValue = true;
				}
				else if (item_choice_in_MenuGroup2 == 3) {
					//xóa các giá trị trong mảng để dùng lại
					memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
					if (menu_whichTransform == 0) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_translateZ);
					}
					else if (menu_whichTransform == 1) {
						changeNumberFloatToCharArray(menu_charNumberValue, menu_rotateZ);
					}
					else
					{
						changeNumberFloatToCharArray(menu_charNumberValue, menu_scaleZ);
					}
					menu_isChangeCharNumberValue = true;
				}
				else if (item_choice_in_MenuGroup2 == 4) {
					appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
						menu_isChangeCharNumberValue,
						menu_translateX, menu_translateY, menu_translateZ, menu_rotateX, menu_rotateY,
						menu_rotateZ, menu_scaleX, menu_scaleY, menu_scaleZ);

					appendTransformInMenu();
				}
			}
		}
		else if (modelMenuGroup2 == 5) {
			if (menu_isChangeCharNumberValue) {
				appendCharArrayForValueTool(item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					tool_arrowSize, tool_circleSize);
			}
			else
			{
				if (item_choice_in_MenuGroup2 == 0) {
					//xóa các giá trị trong mảng để dùng lại
					memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));

					changeNumberFloatToCharArray(menu_charNumberValue, tool_arrowSize);

					menu_isChangeCharNumberValue = true;
				}
				else if (item_choice_in_MenuGroup2 == 1) {
					//xóa các giá trị trong mảng để dùng lại
					memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));

					changeNumberFloatToCharArray(menu_charNumberValue, tool_circleSize);

					menu_isChangeCharNumberValue = true;
				}
			}
		}
	}
			 break;
			 //nhấn phím cách " " để dừng vẽ các hình như triaStrip hay triaFan và vẽ hình mới
	case 32: {
		if (modelStyleDraw == 0 && vertexLeftToDraw == 0 && (modelTop == 4 || modelTop == 5)) {
			vertexLeftToDraw = 3;
			totalVertexOfShape = 3;
			//nếu đang ở chế độ nhắc hình(đang có 1 vertex sau cùng là đang để thử)
			if (tool_isShowBeforeDraw && !isAgreePossition) {
				clearLastVertexDraw(itemsChoice.back(), triaStripArray, triaFanArray);
				itemsChoice.clear();

				drawObjectPickAndDraw(0.0f, 0.0f, 0.0f, true);
			}

			//vẽ lại màn hình hiện tại
			glutPostRedisplay();
		}
	}
			 break;
			 //xóa hình đang được chọn
	case 127:
		//trước khi delete vật ta lưu lại thông tin của vật vào tệp txt
		if (modelEditStyle == 0) {
			SaveObjectCreatOrDelete(4);
		}

		deleteModelChoice(itemsChoice, positionVerticesChoice, modelEditStyle, idsUsing, symmetryVertices, symmetryObjects,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray,
			cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
		//nếu xóa hết vật đang chọn thì chuyển chế độ mouseModel về 0 và đặt chế độ chọn sang chọn vật
		mouseModel = 0;
		modelEditStyle = 0;
		whichItemSymmetry = -1;

		redisplay_all();
		break;
		//thoát ứng dụng
	case 27: {
		glutDestroyWindow(window);
		exit(0);
		break;
	}
	default:
		break;
	}

	redisplay_all();
}
//hàm nhận sự kiện key mũi tên dành cho tất cả
void ClickKeyArrowOnKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
	{
		if (modelMenuGroup2 == 1) {
			if (itemsChoice.size() == 1) {
				//nếu đang ở chế độ chỉnh sửa giá trị thì áp dụng giá trị đã chỉnh sửa
				if (menu_isChangeCharNumberValue) {
					//lưu lại giá trị trước khi thay đổi
					SaveObjectCreatOrDelete(5);

					bool isChange = appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						itemsChoice.at(0),
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);

					//nếu có thay đổi thì lưu lại giá trị sau khi thay đổi
					if (isChange) {
						SaveObjectCreatOrDelete(5);
					}
					//nếu không có thay đỏi thì xóa file vừa lưu đi
					else
					{
						offsetTxtUsing--;
						txtUsing.pop_back();
					}
				}
				item_choice_in_MenuGroup2--;
				if (item_choice_in_MenuGroup2 < -1) {
					item_choice_in_MenuGroup2 = -1;
				}
			}
		}
		else if (modelMenuGroup2 == 2) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			item_choice_in_MenuGroup2--;
			if (item_choice_in_MenuGroup2 < -1) {
				item_choice_in_MenuGroup2 = -1;
			}
		}
		else if (modelMenuGroup2 == 3) {
			//nếu đang ở chế độ chỉnh sửa thì áp dụng giá trị chỉnh sửa cho menu hiện tại trước khi chuyển
			appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
				menu_isChangeCharNumberValue,
				menu_translateX, menu_translateY, menu_translateZ, menu_rotateX,
				menu_rotateY, menu_rotateZ, menu_scaleX, menu_scaleY, menu_scaleZ);

			item_choice_in_MenuGroup2--;
			if (item_choice_in_MenuGroup2 < -1) {
				item_choice_in_MenuGroup2 = -1;
			}
		}
		else if (modelMenuGroup2 == 5) {
			//nếu đang ở chế độ chỉnh sửa thì áp dụng giá trị chỉnh sửa cho menu hiện tại trước khi chuyển
			appendCharArrayForValueTool(item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				tool_arrowSize, tool_circleSize);

			item_choice_in_MenuGroup2--;
			if (item_choice_in_MenuGroup2 < -1) {
				item_choice_in_MenuGroup2 = -1;
			}
		}
	}
	break;
	case GLUT_KEY_DOWN:
	{
		if (modelMenuGroup2 == 1) {
			if (itemsChoice.size() == 1) {
				//nếu đang ở chế độ chỉnh sửa thì áp dụng giá tri chỉnh sửa vào ô đang chọn
				if (menu_isChangeCharNumberValue) {
					//lưu lại giá trị trước khi thay đổi
					SaveObjectCreatOrDelete(5);

					bool isChange = appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						itemsChoice.at(0),
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);

					//nếu có thay đổi thì lưu lại giá trị sau khi thay đổi
					if (isChange) {
						SaveObjectCreatOrDelete(5);
					}
					//nếu không có thay đỏi thì xóa file vừa lưu đi
					else
					{
						offsetTxtUsing--;
						txtUsing.pop_back();
					}
				}
				item_choice_in_MenuGroup2++;

				switch (itemsChoice.back().object)
				{
				case 10: {
					if (item_choice_in_MenuGroup2 > 4) {
						item_choice_in_MenuGroup2 = 4;
					}
				}
						 break;
				case 12: {
					if (item_choice_in_MenuGroup2 > 1) {
						item_choice_in_MenuGroup2 = 1;
					}
				}
						 break;
				case 13: {
					if (item_choice_in_MenuGroup2 > 5) {
						item_choice_in_MenuGroup2 = 5;
					}
				}
						 break;
				case 14: {
					if (item_choice_in_MenuGroup2 > 6) {
						item_choice_in_MenuGroup2 = 6;
					}
				}
						 break;
				case 16: {
					if (item_choice_in_MenuGroup2 > 8) {
						item_choice_in_MenuGroup2 = 8;
					}
				}
						 break;
				case 17: {
					if (item_choice_in_MenuGroup2 > 4) {
						item_choice_in_MenuGroup2 = 4;
					}
				}
						 break;
				case 19: {
					if (item_choice_in_MenuGroup2 > 3) {
						item_choice_in_MenuGroup2 = 3;
					}
				}
						 break;

				default: {
					item_choice_in_MenuGroup2 = -1;
				}
						 break;
				}
			}
		}
		else if (modelMenuGroup2 == 2) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			item_choice_in_MenuGroup2++;
			if (whichStyleRound == 0) {
				if (item_choice_in_MenuGroup2 > 3) {
					item_choice_in_MenuGroup2 = 3;
				}
			}
			else
			{
				if (item_choice_in_MenuGroup2 > 5) {
					item_choice_in_MenuGroup2 = 5;
				}
			}
		}
		else if (modelMenuGroup2 == 3) {
			//nếu đang ở chế độ chỉnh sửa thì áp dụng giá trị chỉnh sửa cho menu hiện tại trước khi chuyển
			appendCharArrayForValueTransform(menu_whichTransform, item_choice_in_MenuGroup2, menu_charNumberValue,
				menu_isChangeCharNumberValue,
				menu_translateX, menu_translateY, menu_translateZ, menu_rotateX,
				menu_rotateY, menu_rotateZ, menu_scaleX, menu_scaleY, menu_scaleZ);

			item_choice_in_MenuGroup2++;
			if (item_choice_in_MenuGroup2 > 4) {
				item_choice_in_MenuGroup2 = 4;
			}
		}
		else if (modelMenuGroup2 == 5) {
			//nếu đang ở chế độ chỉnh sửa thì áp dụng giá trị chỉnh sửa cho menu hiện tại trước khi chuyển
			appendCharArrayForValueTool(item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				tool_arrowSize, tool_circleSize);

			item_choice_in_MenuGroup2++;
			if (item_choice_in_MenuGroup2 > 1) {
				item_choice_in_MenuGroup2 = 1;
			}
		}
	}
	break;
	case GLUT_KEY_LEFT:
	{
		//nếu item_choice_in_MenuGroup2=-1 thì dịch chuyển các menu phía trên
		if (item_choice_in_MenuGroup2 == -1) {
			modelMenuGroup2--;
			if (modelMenuGroup2 < 0) {
				modelMenuGroup2 = 5;
			}
		}
		else
		{
			//nếu không phải đang trong chế độ chỉnh sửa
			if (!menu_isChangeCharNumberValue) {
				if (modelMenuGroup2 == 1) {
					if (itemsChoice.size() == 1) {
						//lưu lại giá trị trước khi thay đổi
						SaveObjectCreatOrDelete(5);

						bool isChange = plusAttributeObject(false, itemsChoice.back(),
							item_choice_in_MenuGroup2,
							menu_charNumberValue, menu_isChangeCharNumberValue,
							sphereArray, cubeArray, cubeRoundArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);

						//nếu có thay đổi thì lưu lại giá trị sau khi thay đổi
						if (isChange) {
							SaveObjectCreatOrDelete(5);
						}
						//nếu không có thay đỏi thì xóa file vừa lưu đi
						else
						{
							offsetTxtUsing--;
							txtUsing.pop_back();
						}
					}
				}
				else if (modelMenuGroup2 == 2) {
					if (item_choice_in_MenuGroup2 == 0) {
						if (whichStyleRound == 0) {
							whichStyleRound = 1;
						}
						else if (whichStyleRound == 1) {
							whichStyleRound = 0;
						}
					}
					else
					{
						if (whichStyleRound == 0) {
							if (item_choice_in_MenuGroup2 == 1) {
								radiusRound2Side -= 0.01f;
								if (radiusRound2Side < 0.1f) {
									radiusRound2Side = 0.1f;
								}
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								numberVertexRound2Side -= 1;
								if (numberVertexRound2Side < 2) {
									numberVertexRound2Side = 2;
								}
							}
						}
						else
						{
							if (item_choice_in_MenuGroup2 == 1) {
								radiusRoundHorizontal -= 0.01f;
								if (radiusRoundHorizontal < 0.1f) {
									radiusRoundHorizontal = 0.1f;
								}
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								numberVertexRoundHorizontal -= 1;
								if (numberVertexRoundHorizontal < 2) {
									numberVertexRoundHorizontal = 2;
								}
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								radiusRoundVertical -= 0.01f;
								if (radiusRoundVertical < 0.1f) {
									radiusRoundVertical = 0.1f;
								}
							}
							else if (item_choice_in_MenuGroup2 == 4) {
								numberVertexRoundVertical -= 1;
								if (numberVertexRoundVertical < 2) {
									numberVertexRoundVertical = 2;
								}
							}
						}
					}
				}
				else if (modelMenuGroup2 == 3) {
					if (item_choice_in_MenuGroup2 == 0) {
						menu_whichTransform--;
						if (menu_whichTransform < 0) {
							menu_whichTransform = 2;
						}
					}
					else
					{
						if (menu_whichTransform == 0) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_translateX -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_translateY -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_translateZ -= 0.01f;
							}
						}
						else if (menu_whichTransform == 1) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_rotateX -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_rotateY -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_rotateZ -= 0.01f;
							}
						}
						else if (menu_whichTransform == 2) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_scaleX -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_scaleY -= 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_scaleZ -= 0.01f;
							}
						}
					}
				}
				else if (modelMenuGroup2 == 5) {
					if (item_choice_in_MenuGroup2 == 0) {
						tool_arrowSize -= 0.1;
						if (tool_arrowSize < 0.1) {
							tool_arrowSize = 0.1;
						}
					}
					else if (item_choice_in_MenuGroup2 == 1) {
						tool_circleSize -= 0.1;
						if (tool_circleSize < 0.1) {
							tool_circleSize = 0.1;
						}
					}
				}
			}
		}
	}
	break;
	case GLUT_KEY_RIGHT:
	{
		//nếu item_choice_in_MenuGroup2=-1 thì dịch chuyển các menu phía trên
		if (item_choice_in_MenuGroup2 == -1) {
			modelMenuGroup2++;
			if (modelMenuGroup2 > 5) {
				modelMenuGroup2 = 0;
			}
		}
		else
		{
			//nếu không phải đang trong chế độ chỉnh sửa
			if (!menu_isChangeCharNumberValue) {
				if (modelMenuGroup2 == 1) {
					if (itemsChoice.size() == 1) {
						//lưu lại giá trị trước khi thay đổi
						SaveObjectCreatOrDelete(5);

						bool isChange = plusAttributeObject(true, itemsChoice.back(),
							item_choice_in_MenuGroup2,
							menu_charNumberValue, menu_isChangeCharNumberValue,
							sphereArray, cubeArray, cubeRoundArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);

						//nếu có thay đổi thì lưu lại giá trị sau khi thay đổi
						if (isChange) {
							SaveObjectCreatOrDelete(5);
						}
						//nếu không có thay đỏi thì xóa file vừa lưu đi
						else
						{
							offsetTxtUsing--;
							txtUsing.pop_back();
						}
					}
				}
				else if (modelMenuGroup2 == 2) {
					if (item_choice_in_MenuGroup2 == 0) {
						if (whichStyleRound == 0) {
							whichStyleRound = 1;
						}
						else if (whichStyleRound == 1) {
							whichStyleRound = 0;
						}
					}
					else
					{
						if (whichStyleRound == 0) {
							if (item_choice_in_MenuGroup2 == 1) {
								radiusRound2Side += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								numberVertexRound2Side += 1;
							}
						}
						else
						{
							if (item_choice_in_MenuGroup2 == 1) {
								radiusRoundHorizontal += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								numberVertexRoundHorizontal += 1;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								radiusRoundVertical += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 4) {
								numberVertexRoundVertical += 1;
							}
						}
					}
				}
				else if (modelMenuGroup2 == 3) {
					if (item_choice_in_MenuGroup2 == 0) {
						menu_whichTransform++;
						if (menu_whichTransform > 2) {
							menu_whichTransform = 0;
						}
					}
					else
					{
						if (menu_whichTransform == 0) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_translateX += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_translateY += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_translateZ += 0.01f;
							}
						}
						else if (menu_whichTransform == 1) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_rotateX += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_rotateY += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_rotateZ += 0.01f;
							}
						}
						else if (menu_whichTransform == 2) {
							if (item_choice_in_MenuGroup2 == 1) {
								menu_scaleX += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 2) {
								menu_scaleY += 0.01f;
							}
							else if (item_choice_in_MenuGroup2 == 3) {
								menu_scaleZ += 0.01f;
							}
						}
					}
				}
				else if (modelMenuGroup2 == 5) {
					if (item_choice_in_MenuGroup2 == 0) {
						tool_arrowSize += 0.1;
					}
					else if (item_choice_in_MenuGroup2 == 1) {
						tool_circleSize += 0.1;
					}
				}
			}
		}
	}
	break;
	}
	redisplay_all();
}
//vẽ mũi tên để dịch chuyển tâm xoay
void drawArrowForMoveCenterRotate(GLenum mode) {
	if (isMoveCenterRotate) {
		if (mode == GL_RENDER) {
			//nếu đang ở chế độ dịch chuyển tâm xoay thì mới hiện mũi tên dịch chuyển
			drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
				false, changeRotateFor2D, -1);
		}
		else
		{
			drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
				false, changeRotateFor2D, 0);
		}
	}
}
//vẽ hình vuông cho các hình được chọn(phải vẽ sau cùng sau khi vẽ hình thì mới nhìn thấy xuyên qua được)
void DrawQuadsOfChoice() {
	if (!itemsChoice.empty() && !isMoveCenterRotate) {
		glDisable(GL_DEPTH_TEST);
		if (mouseModel == 3) {
			if (modelEditStyle == 0) {
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, -1);
			}
			else if (!positionVerticesChoice.empty()) {
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, -1);
			}
		}
		else if (mouseModel == 5) {
			//nêu đang ở chế độ chỉnh sửa vertex thì đặt mũi tên để scale vertex
			if (modelEditStyle != 0) {
				//nếu có từ 2 điểm trở lên mới cho scale(và k0 phải đang ở chế độ dịch chuyển tâm xoay)
				if (!positionVerticesChoice.empty()) {
					drawQuadForObject(centerObjectOrVertices, tool_arrowSize, -1);
				}
			}
			else
			{
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, -1);
			}
		}
		glEnable(GL_DEPTH_TEST);
	}

}
//chỉ duy nhất vẽ các mũi tên chứ k0 vẽ các vật
void drawQuadsForChoice() {
	if (!itemsChoice.empty() && !isMoveCenterRotate) {
		glClear(GL_DEPTH_BUFFER_BIT);
		if (mouseModel == 3) {
			if (modelEditStyle == 0) {
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, 0);
			}
			else if (!positionVerticesChoice.empty()) {
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, 0);
			}
		}
		else if (mouseModel == 5) {
			//nêu đang ở chế độ chỉnh sửa vertex thì đặt mũi tên để scale vertex
			if (modelEditStyle != 0) {
				//nếu có từ 2 điểm trở lên mới cho scale(và k0 phải đang ở chế độ dịch chuyển tâm xoay)
				if (!positionVerticesChoice.empty()) {
					drawQuadForObject(centerObjectOrVertices, tool_arrowSize, 0);
				}
			}
			else
			{
				drawQuadForObject(centerObjectOrVertices, tool_arrowSize, 0);
			}
		}
	}
}

//vẽ mũi tên cho các hình được chọn(phải vẽ sau cùng sau khi vẽ hình thì mới nhìn thấy xuyên qua được)
void DrawArrowOfChoice(int changeRotateFor2D) {
	glDisable(GL_DEPTH_TEST);
	//nêu đang ở chế độ xoay(hoặc scale) mà chế độ dịch chuyển tâm xoay bật thì vẽ mũi tên để dịch chuyển tâm xoay
	if (isMoveCenterRotate) {
		if (modelEditStyle == 0) {
			drawArrowForMoveCenterRotate(GL_RENDER);
		}
		//nếu đang ở chế độ chỉnh sửa vertex thì phải có vertex đang được chọn thì mới cho phép
		else if (!positionVerticesChoice.empty())
		{
			drawArrowForMoveCenterRotate(GL_RENDER);
		}
	}
	else if (!itemsChoice.empty()) {
		if (mouseModel == 3) {
			if (modelEditStyle == 0) {
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					false, changeRotateFor2D, -1);
			}
			//phải có ít nhất 1 điểm đang được chọn thì mới cho phép
			else if (!positionVerticesChoice.empty())
			{
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					false, changeRotateFor2D, -1);
			}
		}
		else if (mouseModel == 5) {
			//nêu đang ở chế độ chỉnh sửa vertex thì đặt mũi tên để scale vertex
			if (modelEditStyle != 0) {
				//phải có ít nhất 1 điểm đang được chọn thì mới cho phép
				if (!positionVerticesChoice.empty()) {
					drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
						true, changeRotateFor2D, -1);
				}
			}
			else
			{
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					true, changeRotateFor2D, -1);
			}
		}
		else if (mouseModel == 6 && itemsChoice.size() == 1)
		{
			itemChoice item = itemsChoice.at(0);
			switch (item.object)
			{
			case 10: {
				SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
				drawOneArrowForObject(sphere->centerObject.x + sphere->radius, sphere->centerObject.y, sphere->centerObject.z, 0, -1);
			}
					 break;
			case 13: {
				ConeAttribute *cone = coneArray.at(item.positionOfChoice);
				drawOneArrowForObject(cone->centerObject.x + cone->radius, cone->centerObject.y, cone->centerObject.z, 0, -1);
			}
					 break;
			case 14: {
				CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
				int offset;
				offset = cylinder->numberLongitude;
				//vẽ mũi tên để chỉnh bán kính
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				//vẽ mũi tên để chỉnh chiều cao
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, -1);
				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 2);
				//vẽ mũi tên để chỉnh bán kính
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				//vẽ mũi tên để chỉnh chiều cao
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, -1);
			}
					 break;
			case 16: {
				EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
				int offset;
				//vẽ 4 mũi tên để chỉnh bán kính(trên ngoài,trên trong,dưới ngoài,dưới trong)
				offset = cylinder->numberLongitude;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				offset = cylinder->numberLongitude / 2;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 2);
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 1) + cylinder->numberLongitude / 2;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, -1);
				//vẽ 2 mũi tên để chỉnh chiều cao
				offset = cylinder->numberLongitude;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, -1);
				offset = cylinder->numberLongitude*(cylinder->numberLatitude - 2);
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, -1);
			}
					 break;
			case 17: {
				TorusAttribute *torus = torusArray.at(item.positionOfChoice);
				drawOneArrowForObject(torus->centerObject.x, torus->centerObject.y, torus->centerObject.z, 0, -1);
				drawOneArrowForObject(torus->centerObject.x, torus->centerObject.y, torus->centerObject.z, 2, -1);
				drawOneArrowForObject(torus->vertexArray.at(0).x, torus->vertexArray.at(0).y, torus->vertexArray.at(0).z, 0, -1);
			}
					 break;
			default:
				break;
			}
		}
	}
	glEnable(GL_DEPTH_TEST);
}
//vẽ các mũi tên chỉ hướng cho các đỉnh của hình được chọn(để lấy ra id của mũi tên được chọn)
//chỉ duy nhất vẽ các mũi tên chứ k0 vẽ các vật
void drawArrowsForChoice(int changeRotateFor2D) {
	glClear(GL_DEPTH_BUFFER_BIT);
	//nêu đang ở chế độ xoay(hoặc scale) mà chế độ dịch chuyển tâm xoay bật thì vẽ mũi tên để dịch chuyển tâm xoay
	if (isMoveCenterRotate) {
		if (modelEditStyle == 0) {
			drawArrowForMoveCenterRotate(GL_SELECT);
		}
		//nếu đang ở chế độ chỉnh sửa vertex thì phải có vertex đang được chọn thì mới cho phép
		else if (!positionVerticesChoice.empty())
		{
			drawArrowForMoveCenterRotate(GL_SELECT);
		}
	}
	else if (!itemsChoice.empty()) {
		int offset = 0;
		if (mouseModel == 3) {
			if (modelEditStyle == 0) {
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					false, changeRotateFor2D, 0);
			}
			//phải có ít nhất 1 điểm đang được chọn thì mới cho phép
			else if (!positionVerticesChoice.empty())
			{
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					false, changeRotateFor2D, 0);
			}
		}
		else if (mouseModel == 5) {
			//nêu đang ở chế độ chỉnh sửa vertex thì đặt mũi tên để scale vertex
			if (modelEditStyle != 0) {
				//phải có ít nhất 1 điểm đang được chọn thì mới cho phép
				if (!positionVerticesChoice.empty()) {
					drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
						true, changeRotateFor2D, 0);
				}
			}
			else
			{
				drawArrowForObject(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z, tool_arrowSize,
					true, changeRotateFor2D, 0);
			}
		}
		else if (mouseModel == 6 && itemsChoice.size() == 1)
		{
			itemChoice item = itemsChoice.at(0);
			switch (item.object)
			{
			case 10: {
				SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
				drawOneArrowForObject(sphere->centerObject.x + sphere->radius, sphere->centerObject.y, sphere->centerObject.z, 0, 0);
			}
					 break;
			case 13: {
				ConeAttribute *cone = coneArray.at(item.positionOfChoice);
				drawOneArrowForObject(cone->centerObject.x + cone->radius, cone->centerObject.y, cone->centerObject.z, 0, 0);
			}
					 break;
			case 14: {
				CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
				offset = cylinder->numberLongitude;
				//vẽ mũi tên để chỉnh bán kính
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 0);
				//vẽ mũi tên để chỉnh chiều cao
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, 1);
				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 2);
				//vẽ mũi tên để chỉnh bán kính
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 3);
				//vẽ mũi tên để chỉnh chiều cao
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, 4);
			}
					 break;
			case 16: {
				EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
				int offset;
				//vẽ 4 mũi tên để chỉnh bán kính(trên ngoài,trên trong,dưới ngoài,dưới trong)
				offset = cylinder->numberLongitude;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 0);
				offset = cylinder->numberLongitude / 2;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 3);

				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 2);
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 6);
				offset = cylinder->numberLongitude * (cylinder->numberLatitude - 1) + cylinder->numberLongitude / 2;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 0, 9);
				//vẽ 2 mũi tên để chỉnh chiều cao
				offset = cylinder->numberLongitude;
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, 1);
				offset = cylinder->numberLongitude*(cylinder->numberLatitude - 2);
				drawOneArrowForObject(cylinder->vertexArray.at(offset).x, cylinder->vertexArray.at(offset).y, cylinder->vertexArray.at(offset).z, 1, 4);
			}
					 break;
			case 17: {
				TorusAttribute *torus = torusArray.at(item.positionOfChoice);
				drawOneArrowForObject(torus->centerObject.x, torus->centerObject.y, torus->centerObject.z, 0, 0);
				drawOneArrowForObject(torus->centerObject.x, torus->centerObject.y, torus->centerObject.z, 2, 2);
				drawOneArrowForObject(torus->vertexArray.at(0).x, torus->vertexArray.at(0).y, torus->vertexArray.at(0).z, 0, 3);
			}
					 break;
			default:
				break;
			}
		}
	}
}
//vẽ vòng tròn xoay cho vật đầu tiên được chọn,dùng để xoay tất cả các vật được chọn
void drawCircleRotateForObject(GLenum mode, bool isClearAllDepth) {
	//vẽ khi đang ở chế độ xoay và có vật đang được chọn
	if (mouseModel == 4 && !itemsChoice.empty() && !isMoveCenterRotate) {
		if (mode == GL_RENDER) {
			if (isClearAllDepth) {
				glLineWidth(10);
				//nếu isClearAllDepthTest là true nghĩa là xóa hết toàn bộ độ sâu để chỉ vẽ chỉ mỗi các vòng tròn 
				//để lấy độ sâu vòng tròn để chọn
				glClear(GL_DEPTH_BUFFER_BIT);
				//vẽ vòng tròn bao để thực hiện các thao tác xoay,chia tỉ lệ hình
				drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				drawCircleForRotate(2, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
			}
			else
			{
				glLineWidth(2);
				//nếu đang ở chế độ vẽ thường thì tắt kiểm tra độ sâu để có thể nhìn thấy xuyên qua các vật khác
				glDisable(GL_DEPTH_TEST);

				/*glPushMatrix();
				glColorMask(0, 0, 0, 0);
				glTranslatef(centerObjectOrVertices.x, centerObjectOrVertices.y, centerObjectOrVertices.z);
				glutSolidSphere(itemRotate.radiusCircle-0.2, 20, 20);
				glColorMask(1, 1, 1, 1);
				glPopMatrix();*/

				//vẽ vòng tròn bao để thực hiện các thao tác xoay,chia tỉ lệ hình
				//nếu đang chọn vòng tròn nào thì đặt firstItemChoice và lastItemChoice để vẽ điểm xoay,nếu k0 phải vòng tròn
				//đang chọn thì đặt vẽ -1
				if (itemRotate.whichCircleChoice == 0) {
					drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
						itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
				}
				else
				{
					drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				}
				if (itemRotate.whichCircleChoice == 1) {
					drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
						itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
				}
				else
				{
					drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				}
				if (itemRotate.whichCircleChoice == 2) {
					drawCircleForRotate(2, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
						itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
				}
				else
				{
					drawCircleForRotate(2, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				}
				glEnable(GL_DEPTH_TEST);
			}
		}
		else
		{
			glLineWidth(10);
			//nếu ở chế độ chọn thì đặt tên cho các trục tròn để xác định chọn trục nào
			glLoadName(0);
			drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
			glLoadName(1);
			drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
			glLoadName(2);
			drawCircleForRotate(2, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
		}
		glLineWidth(1.0);
	}
}
//vẽ đường tròn để chỉnh sửa các thuộc tính liên quan đến độ của đối tượng
void drawCircleForDivideDegrees(GLenum mode, bool isClearAllDepth) {
	//nếu đang ở chế độ chỉnh sửa thuộc tính và có 1 vật đang được chọn
	if (mouseModel == 6 && itemsChoice.size() == 1) {
		itemChoice item = itemsChoice.back();
		switch (item.object)
		{
		case 10:
		{
			if (mode == GL_RENDER) {
				if (isClearAllDepth) {
					glLineWidth(10);
					glClear(GL_DEPTH_BUFFER_BIT);
					drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
					drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
				}
				else
				{
					glLineWidth(2);
					//nếu đang ở chế độ vẽ thường thì tắt kiểm tra độ sâu để có thể nhìn thấy xuyên qua các vật khác
					glDisable(GL_DEPTH_TEST);
					if (itemRotate.whichCircleChoice == 0) {
						drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
							itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
					}
					else
					{
						drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
					}
					if (itemRotate.whichCircleChoice == 1) {
						drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
							itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
					}
					else
					{
						drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, -1, -1, itemRotate.isRotateLikeClockwise);
					}
					glEnable(GL_DEPTH_TEST);
				}
			}
			else
			{
				glLineWidth(10);
				//nếu ở chế độ chọn thì đặt tên cho các trục tròn để xác định chọn trục nào
				glLoadName(0);
				drawCircleForRotate(0, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
					itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
				glLoadName(1);
				drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
					itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
			}
		}
		break;
		case 13:
		case 14:
		case 15:
		case 16:
		{
			if (mode == GL_RENDER) {
				if (isClearAllDepth) {
					glLineWidth(10);
					glClear(GL_DEPTH_BUFFER_BIT);
					drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
						itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
				}
				else
				{
					glLineWidth(2);
					//nếu đang ở chế độ vẽ thường thì tắt kiểm tra độ sâu để có thể nhìn thấy xuyên qua các vật khác
					glDisable(GL_DEPTH_TEST);
					drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
						itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
					glEnable(GL_DEPTH_TEST);
				}
			}
			else
			{
				glLineWidth(10);
				//nếu ở chế độ chọn thì đặt tên cho các trục tròn để xác định chọn trục nào
				glLoadName(1);
				drawCircleForRotate(1, tool_circleSize, centerObjectOrVertices, itemRotate.firstItemChoice,
					itemRotate.itemChoiceNow, itemRotate.isRotateLikeClockwise);
			}
		}
		break;
		default:
			break;
		}
	}
}
//vẽ độ sâu của phần thảm và tất cả các vật trừ những vật đang được chọn
//được dùng trong chế độ dịch chuyển theo cả 3 chiều theo vị trí x,y và độ sâu của chuột
void drawObjectNotGetChoice() {
	glClear(GL_DEPTH_BUFFER_BIT);
	//vẽ độ sâu của thảm đặt vật
	//tắt màu để khỏi tốn đồ họa
	glColorMask(0, 0, 0, 0);

	glBegin(GL_POLYGON);
	glVertex3f(-30, 0, -30);
	glVertex3f(-30, 0, 30);
	glVertex3f(30, 0, 30);
	glVertex3f(30, 0, -30);
	glEnd();

	//vẽ ra các vật không được chọn
	//vẽ các tam giác trong mảng đã định nghĩa
	DrawTriangles(GL_RENDER, triangleArray, itemTextureWindow, 2, itemsChoice);
	//vẽ các bộ tam giác(triangle strip) trong mảng đã định nghĩa
	DrawTriangleStrip(GL_RENDER, triaStripArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các quạt tam giác(triangle fan) trong mảng đã định nghĩa
	DrawTriangleFan(GL_RENDER, triaFanArray, itemTextureWindow, 2, itemsChoice);
	//vẽ các hình cầu đã định nghĩa
	DrawSphere(GL_RENDER, sphereArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các cube đã định nghĩa
	DrawCube(GL_RENDER, cubeArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các hình cube round đã định nghĩa
	DrawCubeRound(GL_RENDER, cubeRoundArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các hình nón mượt đã định nghĩa
	DrawCone(GL_RENDER, coneArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các hình trụ đã định nghĩa
	DrawCylinder(GL_RENDER, cylinderArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các hình kim tự tháp đã định nghĩa
	DrawPyramid(GL_RENDER, pyrArray, itemTextureWindow, 2, itemsChoice);
	//vẽ các hình trụ rỗng đã định nghĩa
	DrawEmptyCylinder(GL_RENDER, emptyCylinderArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các torus(bánh rán) đã định nghĩa
	DrawTorus(GL_RENDER, torusArray, itemTextureWindow, isRoundCorner, 2, itemsChoice);
	//vẽ các hình ảnh đã định nghĩa
	DrawPictures(GL_RENDER, pictureArray, itemTextureWindow, 2, itemsChoice);
	//vẽ các ObjectCustom0 đã định nghĩa
	DrawObjectCustom0(GL_RENDER, objectCustom0Array, itemTextureWindow, isRoundCorner, 2, itemsChoice);

	//bật màu lại
	glColorMask(1, 1, 1, 1);
}
//vẽ tất cả các vật
void drawObject(GLenum mode) {
	//vẽ các tam giác trong mảng đã định nghĩa
	DrawTriangles(mode, triangleArray, itemTextureWindow, 0, itemsChoice);
	//vẽ các bộ tam giác(triangle strip) trong mảng đã định nghĩa
	DrawTriangleStrip(mode, triaStripArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các quạt tam giác(triangle fan) trong mảng đã định nghĩa
	DrawTriangleFan(mode, triaFanArray, itemTextureWindow, 0, itemsChoice);
	//vẽ các hình cầu đã định nghĩa
	DrawSphere(mode, sphereArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các cube đã định nghĩa
	DrawCube(mode, cubeArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các hình cube round đã định nghĩa
	DrawCubeRound(mode, cubeRoundArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các hình nón mượt đã định nghĩa
	DrawCone(mode, coneArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các hình trụ đã định nghĩa
	DrawCylinder(mode, cylinderArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các hình kim tự tháp đã định nghĩa
	DrawPyramid(mode, pyrArray, itemTextureWindow, 0, itemsChoice);
	//vẽ các hình trụ rỗng đã định nghĩa
	DrawEmptyCylinder(mode, emptyCylinderArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các torus(bánh rán) đã định nghĩa
	DrawTorus(mode, torusArray, itemTextureWindow, isRoundCorner, 0, itemsChoice);
	//vẽ các hình ảnh đã định nghĩa
	DrawPictures(mode, pictureArray, itemTextureWindow, 0, itemsChoice);
	//vẽ các ObjectCustom0 đã định nghĩa
	DrawObjectCustom0(mode, objectCustom0Array, itemTextureWindow, isRoundCorner, 0, itemsChoice);
}

//hàm vẽ đường tròn chọn,hình chữ nhật chọn và hình chữ nhật đối xứng
void drawCircleRectangleAndRectangleSymmetry() {
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	//nếu đang ở chế độ chọn bằng vùng chọn hình cầu thì hiện vùng chọn lúc chưa nhấn chuột
	if (mouseModel == 2 && !areaChoice.isChoice) {
		//các điểm được thêm vào giữa 2 đỉnh và mảng chứa chúng
		int numberPointAdd = 20;
		point *arrayOut = new point[numberPointAdd];

		glColor3f(0.8, 0.8, 0.8);

		//đẩy các điểm của mảng v ra bằng bán kính
		normalizeWithRadius(areaChoice.centerArea, areaChoice.v[0], areaChoice.radius);
		normalizeWithRadius(areaChoice.centerArea, areaChoice.v[1], areaChoice.radius);
		normalizeWithRadius(areaChoice.centerArea, areaChoice.v[2], areaChoice.radius);

		glBegin(GL_LINE_LOOP);

		//vẽ điểm nằm trên đường thẳng chứa center và v[0]
		glVertex3f(areaChoice.v[0].x, areaChoice.v[0].y, areaChoice.v[0].z);

		//tìm ra các điểm nằm giữa v[0] và v[1]
		findPointsBetweenTwoPoint(areaChoice.v[0], areaChoice.v[1], numberPointAdd, arrayOut);
		//vẽ các điểm nằm trên đường thẳng chứa center và các điểm vừa tìm được
		for (int i = 0; i < numberPointAdd; i++) {
			normalizeWithRadius(areaChoice.centerArea, arrayOut[i], areaChoice.radius);
			glVertex3f(arrayOut[i].x, arrayOut[i].y, arrayOut[i].z);
		}

		//vẽ điểm nằm trên đường thẳng chứa center và v[1]
		glVertex3f(areaChoice.v[1].x, areaChoice.v[1].y, areaChoice.v[1].z);

		//tìm ra các điểm nằm giữa v[1] và v[2]
		findPointsBetweenTwoPoint(areaChoice.v[1], areaChoice.v[2], numberPointAdd, arrayOut);
		//vẽ các điểm nằm trên đường thẳng chứa center và các điểm vừa tìm được
		for (int i = 0; i < numberPointAdd; i++) {
			normalizeWithRadius(areaChoice.centerArea, arrayOut[i], areaChoice.radius);
			glVertex3f(arrayOut[i].x, arrayOut[i].y, arrayOut[i].z);
		}

		//vẽ điểm nằm trên đường thẳng chứa center và v[2]
		glVertex3f(areaChoice.v[2].x, areaChoice.v[2].y, areaChoice.v[2].z);

		//tìm ra các điểm nằm giữa v[2] và v[0]
		findPointsBetweenTwoPoint(areaChoice.v[2], areaChoice.v[0], numberPointAdd, arrayOut);
		//vẽ các điểm nằm trên đường thẳng chứa center và các điểm vừa tìm được
		for (int i = 0; i < numberPointAdd; i++) {
			normalizeWithRadius(areaChoice.centerArea, arrayOut[i], areaChoice.radius);
			glVertex3f(arrayOut[i].x, arrayOut[i].y, arrayOut[i].z);
		}

		glEnd();

		//xóa vùng lưu trữ của mảng động arrayOut
		delete[] arrayOut;
	}

	//vẽ hình chữ nhật bao để chọn vật
	if (!vertexToDrawRectangle.empty()) {
		glDisable(GL_DEPTH_TEST);

		//nếu đang ở chế độ thêm vertex
		if (mouseModel == 7) {
			glColor3f(0.8, 0.8, 0.8);
			int numberVertex = vertexToDrawRectangle.size();
			glBegin(GL_LINE_LOOP);
			point v;
			for (int i = 0; i < numberVertex; i++) {
				v = vertexToDrawRectangle.at(i);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			if (!vertexToDrawRectangleSymmetry.empty()) {
				numberVertex = vertexToDrawRectangleSymmetry.size();
				glBegin(GL_LINE_LOOP);
				point v;
				for (int i = 0; i < numberVertex; i++) {
					v = vertexToDrawRectangleSymmetry.at(i);
					glVertex3f(v.x, v.y, v.z);
				}
				glEnd();
			}
		}
		//nếu đang ở chế độ xóa vertex
		else if (mouseModel == 8) {
			glColor3f(0.0, 0.0, 0.0);
			int numberVertex = vertexToDrawRectangle.size();
			glBegin(GL_LINE_LOOP);
			point v;
			for (int i = 0; i < numberVertex; i++) {
				v = vertexToDrawRectangle.at(i);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
			if (!vertexToDrawRectangleSymmetry.empty()) {
				numberVertex = vertexToDrawRectangleSymmetry.size();
				glBegin(GL_LINE_LOOP);
				point v;
				for (int i = 0; i < numberVertex; i++) {
					v = vertexToDrawRectangleSymmetry.at(i);
					glVertex3f(v.x, v.y, v.z);
				}
				glEnd();
			}
		}
		//nếu đang ở chế độ chọn vật
		else {
			glColor3f(1.0, 1.0, 1.0);
			glBegin(GL_LINE_LOOP);
			point v;
			for (int i = 0; i < 4; i++) {
				v = vertexToDrawRectangle.at(i);
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}

		glEnable(GL_DEPTH_TEST);
	}

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}

//kiểm tra xem có chọn trúng mũi tên chỉnh sửa giá trị không
void checkIsChoiceArrow(int x, int y, double *modelMatrix, double *projectMatrix, int *viewport) {
	//đầu tiên ta phải xem xét xem có chọn trúng vertex k0(nếu có vật đang được chọn),nếu k0 chọn trúng mũi tên thì xóa tên vật đang được
	//chọn và vẽ lại để chọn(phải làm vậy để tất cả các vật đều có độ sâu,kể cả vật đang chọn(giờ đã xóa tên vật đang chọn nên vật này hiện
	//k0 được chọn nữa,nếu chọn trúng thì sẽ đặt lại,nếu k0 thì bỏ),nếu k0 sẽ chọn trúng vật phía sau nó do vật đang chọn sẽ k0 vẽ độ sâu)
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;

	//vẽ lại chỉ chắc mũi tên để lấy độ sâu của mũi tên
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	drawArrowsForChoice(changeRotateFor2D);
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	int good = gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	if (good == GL_TRUE) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float pointZChange = 0 - zDown;
		glOrtho(xDown - 0.1, xDown + 0.1, yDown - 0.1, yDown + 0.1, pointZChange - 0.1, pointZChange + 0.1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glSelectBuffer(BUFSIZE, bufferIdChoice);
		GLint hits;
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(10000);
		drawArrowsForChoice(changeRotateFor2D);
		//hit là số lượng các tên đã lưu trữ,bắt đầu từ khi lệnh glRenderMode(GL_SELECT) cuối cùng được gọi
		hits = glRenderMode(GL_RENDER);
		if (hits > 0) {
			int posi = bufferIdChoice[3];
			whichArrowChoice = posi;
			//lấy ra điểm chạm đầu tiên để tính giá trị dịch chuyển
			firstTouch = { (float)xDown,(float)yDown,(float)zDown };
		}
	}
}

//kiểm tra xem có chọn trúng hình vuông chỉnh sửa giá trị không
void checkIsChoiceQuad(int x, int y, double *modelMatrix, double *projectMatrix, int *viewport) {
	//đầu tiên ta phải xem xét xem có chọn trúng vertex k0(nếu có vật đang được chọn),nếu k0 chọn trúng mũi tên thì xóa tên vật đang được
	//chọn và vẽ lại để chọn(phải làm vậy để tất cả các vật đều có độ sâu,kể cả vật đang chọn(giờ đã xóa tên vật đang chọn nên vật này hiện
	//k0 được chọn nữa,nếu chọn trúng thì sẽ đặt lại,nếu k0 thì bỏ),nếu k0 sẽ chọn trúng vật phía sau nó do vật đang chọn sẽ k0 vẽ độ sâu)
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;

	//vẽ lại chỉ chắc mũi tên để lấy độ sâu của mũi tên
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	drawQuadsForChoice();
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	int good = gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	if (good == GL_TRUE) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		float pointZChange = 0 - zDown;
		glOrtho(xDown - 0.1, xDown + 0.1, yDown - 0.1, yDown + 0.1, pointZChange - 0.1, pointZChange + 0.1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glSelectBuffer(BUFSIZE, bufferIdChoice);
		GLint hits;
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(10000);
		drawQuadsForChoice();
		//hit là số lượng các tên đã lưu trữ,bắt đầu từ khi lệnh glRenderMode(GL_SELECT) cuối cùng được gọi
		hits = glRenderMode(GL_RENDER);
		if (hits > 0) {
			int posi = bufferIdChoice[3];
			whichQuadChoice = posi;
			//lấy ra điểm chạm đầu tiên để tính giá trị dịch chuyển
			firstTouch = { (float)xDown,(float)yDown,(float)zDown };
		}
	}
}
//kiểm tra xem có chọn trúng vòng tròn xoay
void checkIsChoiceCircleRotate(int x, int y, double *modelMatrix, double *projectMatrix, int *viewport) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z, pointZChange;
	GLint hits;

	//KIỂM TRA XEM CHỌN VÒNG TRÒN NÀO

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	//ở chế độ khác nhau thì vẽ các vòng tròn khác nhau
	if (mouseModel == 4) {
		drawCircleRotateForObject(GL_RENDER, true);
	}
	else if (mouseModel == 6) {
		drawCircleForDivideDegrees(GL_RENDER, true);
	}
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	pointZChange = 0 - zDown;
	glOrtho(xDown - 0.1, xDown + 0.1, yDown - 0.1, yDown + 0.1, pointZChange - 0.1, pointZChange + 0.1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glSelectBuffer(BUFSIZE, bufferIdChoice);
	glRenderMode(GL_SELECT);
	glInitNames();
	glPushName(10000);
	//đầu tiên kiểm tra xem vòng tròn nào được chọn
	if (mouseModel == 4) {
		drawCircleRotateForObject(GL_SELECT, false);
	}
	else if (mouseModel == 6) {
		drawCircleForDivideDegrees(GL_SELECT, false);
	}
	//hit là số lượng các tên đã lưu trữ,bắt đầu từ khi lệnh glRenderMode(GL_SELECT) cuối cùng được gọi
	hits = glRenderMode(GL_RENDER);
	//0 là k0 chọn trúng,-1 là lỗi(thường là do không đủ vùng nhớ để chứa thông tin,ta cho quá ít)
	if (hits > 0) {
		itemRotate.whichCircleChoice = bufferIdChoice[3];
	}
}
//hàm thêm vertex vào vật,
//biến isCheck thông báo việc đặt vertex này chỉ là thử,chưa đặt thật
//vậy nên chưa giảm vertexLeftToDraw
void insertVertexInfor(float x, float y, float z, bool isCheck) {
	//Nếu tổng số vertex của hình bằng số vertex còn lại cần phải vẽ để hoàn thành hình thì
	//có nghĩa là chưa vẽ vertex nào (khởi tạo 1 hình vào mảng các hình)
	//còn nếu số vertex còn lại bằng 1 có nghĩa là kết thúc vẽ 1 hình(ta tính normal vertex từ 3 đỉnh của nó)
	int idToSet = getIdForObject(idsUsing);
	//0:Lines,1:line_strip,2:line_loop,3:triangles,4:triangle_strip,5:triangle_fan,
	switch (modelTop)
	{
		//ve tam giac
	case 3:
	{
		if (vertexLeftToDraw == 3) {
			TriangleAttribute *tria = new TriangleAttribute();
			//thêm vị trí nhấn chuột hiện tại vào mảng vertex
			//lần đầu áp dụng cho cả 3 vertex rồi mới thay đổi dần trong các lượt nhấn sau
			tria->setVertexAtIndex(0, { x,y,z });
			tria->setVertexAtIndex(1, { x,y,z });
			tria->setVertexAtIndex(2, { x,y,z });
			tria->id = idToSet;
			tria->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			triangleArray.push_back(tria);

			//sau khi đặt tam giác vào mảng thì đặt tam giác này là tam giác đang được chọn luôn
			itemsChoice.push_back({ 3,idToSet,(int)(triangleArray.size() - 1) });
		}
		else if (vertexLeftToDraw == 2)
		{
			TriangleAttribute *tria = triangleArray.back();
			tria->setVertexAtIndex(1, { x,y,z });
		}
		else if (vertexLeftToDraw == 1) {
			//khi ở đỉnh 3 ta tính normal vector cho tam giác
			TriangleAttribute *tria = triangleArray.back();
			tria->setVertexAtIndex(2, { x,y,z });

			float normal[3], v1[3], v2[3], v3[3];
			tria->getVertexAtIndex(0, v1);
			tria->getVertexAtIndex(1, v2);
			tria->getVertexAtIndex(2, v3);
			normcrossprod(v1, v2, v3, normal);
			tria->setNormalVector({ normal[0], normal[1], normal[2] });
			tria->centerObject = getPointCenterVertexes(tria->vertexArray, 3);
		}

		if (!isCheck) {
			vertexLeftToDraw--;
			//bang 0 la ve xong 1 hinh
			if (vertexLeftToDraw == 0) {
				vertexLeftToDraw = totalVertexOfShape;
			}
		}
	}
	break;
	//Vẽ Triangle Strip
	case 4:
	{
		//bắt buộc phải vẽ tối thiểu 3 vertex mới đươc(còn vẽ thêm hay k0 thì tùy)
		if (vertexLeftToDraw == 3) {
			TriangleStripAttribute *triaStrip = new TriangleStripAttribute();
			//thêm vị trí nhấn chuột hiện tại vào mảng vertex
			triaStrip->vertexArray.push_back({ x, y, z });
			triaStrip->id = idToSet;
			triaStrip->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			triaStripArray.push_back(triaStrip);
			//vì chưa đủ vertex để tìm normal nên chưa tính
			triaStrip->normalVector.push_back({ 0.0,0.0,0.0 });

			//sau khi đặt tam giác vào mảng thì đặt tam giác này là tam giác đang được chọn luôn
			itemsChoice.push_back({ 4,idToSet,(int)(triaStripArray.size() - 1) });
		}
		else if (vertexLeftToDraw == 2)
		{
			TriangleStripAttribute *triaStrip = triaStripArray.back();
			triaStrip->vertexArray.push_back({ x, y, z });
			//vì chưa đủ vertex để tìm normal nên chưa tính
			triaStrip->normalVector.push_back({ 0.0,0.0,0.0 });
		}
		else if (vertexLeftToDraw == 1) {
			//khi ở đỉnh 3 ta tính normal vector cho đỉnh hiện tại và 2 đỉnh trước đó
			TriangleStripAttribute *triaStrip = triaStripArray.back();
			triaStrip->vertexArray.push_back({ x, y, z });

			if (isCheck) {
				//nếu đang chế độ check thì khỏi tính toán normal,vì nó thay đổi liên tục
				triaStrip->normalVector.push_back({ 0.0,0.0,0.0 });
			}
			else
			{
				//tính toán normal vector
				point normal, v1, v2, v3;
				int sizeVertexArray = triaStrip->vertexArray.size();
				v1 = triaStrip->vertexArray.at(sizeVertexArray - 3);
				v2 = triaStrip->vertexArray.at(sizeVertexArray - 2);
				v3 = triaStrip->vertexArray.at(sizeVertexArray - 1);
				normcrossprod(v1, v2, v3, normal);
				//đặt normal vector cho đỉnh hiện tại và 2 đỉnh đầu luôn
				triaStrip->normalVector.push_back(normal);
				triaStrip->normalVector.at(0) = normal;
				triaStrip->normalVector.at(1) = normal;
			}
			triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		}
		else
		{
			//khi từ đỉnh thứ 4 trở đi ta đều phải tính normal vector cho mỗi đỉnh này(tính từ đỉnh hiện tại và 2 đỉnh trước đó)
			TriangleStripAttribute *triaStrip = triaStripArray.back();
			triaStrip->vertexArray.push_back({ x, y, z });

			if (isCheck) {
				//nếu đang chế độ check thì khỏi tính toán normal,vì nó thay đổi liên tục
				triaStrip->normalVector.push_back({ 0.0,0.0,0.0 });
			}
			else
			{
				//tính toán normal vector
				point normal, v1, v2, v3;
				int sizeVertexArray = triaStrip->vertexArray.size();
				//nếu số đỉnh là chẵng phải đi ngược từ đỉnh cuối lên 2 đỉnh trước để tính normal vector
				//do tính chất của triangleStrip
				v1 = triaStrip->vertexArray.at(sizeVertexArray - 3);
				v2 = triaStrip->vertexArray.at(sizeVertexArray - 2);
				v3 = triaStrip->vertexArray.at(sizeVertexArray - 1);
				if (sizeVertexArray % 2 == 0) {
					normcrossprod(v3, v2, v1, normal);
				}
				else
				{
					normcrossprod(v1, v2, v3, normal);
				}
				triaStrip->normalVector.push_back(normal);
			}
			triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		}

		if (vertexLeftToDraw != 3) {
			positionVerticesChoice.clear();
			//đầu tiên đặt vertex cuối cùng(vertex vừa thêm vào mảng các vertex được chọn)
			positionVerticesChoice.push_back(triaStripArray.back()->vertexArray.size() - 1);
		}

		if (!isCheck) {
			//khi đã vẽ đủ 3 vertex cần thiết thì dừng lại hay vẽ thêm vertex cũng được
			if (vertexLeftToDraw != 0) {
				vertexLeftToDraw--;
			}
		}
	}
	break;
	//Vẽ Triangle Fan
	case 5:
	{
		//bắt buộc phải vẽ tối thiểu 3 vertex mới đươc(còn vẽ thêm hay k0 thì tùy)
		if (vertexLeftToDraw == 3) {
			TriangleFanAttribute *triaFan = new TriangleFanAttribute();
			//thêm vị trí nhấn chuột hiện tại vào mảng vertex
			triaFan->vertexArray.push_back({ x, y, z });
			triaFan->id = idToSet;
			triaFan->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
			triaFanArray.push_back(triaFan);
			//vì chưa đủ vertex để tìm normal nên chưa tính
			triaFan->normalVector.push_back({ 0.0,0.0,0.0 });

			//sau khi đặt tam giác vào mảng thì đặt tam giác này là tam giác đang được chọn luôn
			itemsChoice.push_back({ 5,idToSet,(int)(triaFanArray.size() - 1) });
		}
		else if (vertexLeftToDraw == 2)
		{
			TriangleFanAttribute *triaFan = triaFanArray.back();
			triaFan->vertexArray.push_back({ x, y, z });
			//vì chưa đủ vertex để tìm normal nên chưa tính
			triaFan->normalVector.push_back({ 0.0,0.0,0.0 });
		}
		else if (vertexLeftToDraw == 1) {
			//khi ở đỉnh 3 ta tính normal vector cho đỉnh hiện tại, 1 đỉnh trước đó và đỉnh đầu tiên(vị đây là hình quạt)
			TriangleFanAttribute *triaFan = triaFanArray.back();
			triaFan->vertexArray.push_back({ x, y, z });

			if (isCheck) {
				//nếu đang chế độ check thì khỏi tính toán normal,vì nó thay đổi liên tục
				triaFan->normalVector.push_back({ 0.0,0.0,0.0 });
			}
			else
			{
				//tính toán normal vector
				point normal, v1, v2, v3;
				int sizeVertexArray = triaFan->vertexArray.size();
				v1 = triaFan->vertexArray.at(0);
				v2 = triaFan->vertexArray.at(sizeVertexArray - 2);
				v3 = triaFan->vertexArray.at(sizeVertexArray - 1);
				normcrossprod(v1, v2, v3, normal);
				//đặt normal vector cho đỉnh hiện tại và 2 đỉnh đầu luôn
				triaFan->normalVector.push_back(normal);
				triaFan->normalVector.at(0) = normal;
				triaFan->normalVector.at(1) = normal;
			}
			triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		}
		else
		{
			//khi từ đỉnh thứ 4 trở đi ta đều phải tính normal vector cho mỗi đỉnh này(tính từ đỉnh hiện
			//tại, 1 đỉnh trước đó và đỉnh đầu tiên(vị đây là hình quạt))
			TriangleFanAttribute *triaFan = triaFanArray.back();
			triaFan->vertexArray.push_back({ x, y, z });

			if (isCheck) {
				//nếu đang chế độ check thì khỏi tính toán normal,vì nó thay đổi liên tục
				triaFan->normalVector.push_back({ 0.0,0.0,0.0 });
			}
			else {
				//tính toán normal vector
				point normal, v1, v2, v3;
				int sizeVertexArray = triaFan->vertexArray.size();
				v1 = triaFan->vertexArray.at(0);
				v2 = triaFan->vertexArray.at(sizeVertexArray - 2);
				v3 = triaFan->vertexArray.at(sizeVertexArray - 1);
				normcrossprod(v1, v2, v3, normal);
				triaFan->normalVector.push_back(normal);
			}
			triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		}

		if (vertexLeftToDraw != 3) {
			positionVerticesChoice.clear();
			//đầu tiên đặt vertex cuối cùng(vertex vừa thêm vào mảng các vertex được chọn)
			positionVerticesChoice.push_back(triaFanArray.back()->vertexArray.size() - 1);
		}

		if (!isCheck) {
			//khi đã vẽ đủ 3 vertex cần thiết thì dừng lại hay vẽ thêm vertex cũng được
			if (vertexLeftToDraw != 0) {
				vertexLeftToDraw--;
			}
		}
	}
	break;
	default:
		break;
	}

	
	//nếu không phải là chế độ check thì tùy xem,nếu là đình 0 thì lưu hình mới tạo,
	//còn nếu là các đỉnh còn lại thì lưu vertex add
	if (!isCheck) {
		//bằng 2 vì phía trên là nó lùi đi 1 rồi
		if (vertexLeftToDraw == 2) {
			SaveObjectCreatOrDelete(3);
		}
		else if (vertexLeftToDraw < 2)
		{
			SaveVertexCreatOrDelete(6);
		}
	}
}

//vẽ vật được đặt ở chế độ pick(chế độ vẽ hình khối)
void drawObjectPick(float x, float y, float z, bool isCheck) {
	int idToSet = getIdForObject(idsUsing);
	switch (modelTop)
	{
	case 0:
	{
		SphereAttribute *sphere = new SphereAttribute();
		//để +1 ở y hết vị nếu k0 hình cầu sẽ nằm 1 nửa ở trên,1 nửa ở dưới
		sphere->setCenterSphere(x, y, z);
		sphere->radius = 1.0;
		sphere->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		sphere->id = idToSet;
		sphereArray.push_back(sphere);

		CaculatorSphere(sphere->radius, sphere->numberLongitude, sphere->numberLatitude, sphere->centerObject,
			sphere->vertexArray);
		CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 10,idToSet,(int)(sphereArray.size() - 1) });

	}
	break;
	//chế độ vẽ hình hộp
	case 1:
	{
		CubeAttribute *cube = new CubeAttribute();
		cube->centerObject = { x,y,z };

		cube->vertexArray.push_back({ x - 1, y + 1, z + 1 });
		cube->vertexArray.push_back({ x + 1, y + 1, z + 1 });
		cube->vertexArray.push_back({ x + 1, y + 1, z - 1 });
		cube->vertexArray.push_back({ x - 1, y + 1, z - 1 });

		cube->vertexArray.push_back({ x - 1, y - 1, z + 1 });
		cube->vertexArray.push_back({ x + 1, y - 1, z + 1 });
		cube->vertexArray.push_back({ x + 1, y - 1, z - 1 });
		cube->vertexArray.push_back({ x - 1, y - 1, z - 1 });

		cube->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		cube->id = idToSet;

		cubeArray.push_back(cube);

		CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ
			, cube->vertexArray, cube->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 11,idToSet,(int)(cubeArray.size() - 1) });
	}
	break;
	//chế độ vẽ hình hộp bo tròn
	case 2:
	{
		CubeRoundAttribute *cube = new CubeRoundAttribute();
		cube->centerObject = { x,y,z };
		cube->xLength = 2.0;
		cube->yLength = 2.0;
		cube->zLength = 2.0;
		cube->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		cube->id = idToSet;
		cubeRoundArray.push_back(cube);

		CaculatorCubeRound(cube->xLength, cube->yLength, cube->zLength, cube->numberLongitude, cube->numberLatitude, cube->centerObject,
			cube->radiusRound, cube->vertexArray);
		CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 12,idToSet,(int)(cubeRoundArray.size() - 1) });
	}
	break;
	//chế độ vẽ hình nón
	case 3:
	{
		ConeAttribute *cone = new ConeAttribute();
		cone->centerObject = { x,y,z };
		cone->height = 4;
		cone->radius = 2;
		cone->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		cone->id = idToSet;
		coneArray.push_back(cone);
		//tính toán vertex và normal
		caculatorCone(cone->centerObject, cone->radius, cone->height, cone->numberLongitude, cone->numberLatitude,
			cone->vertexArray);
		CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 13,idToSet,(int)(coneArray.size() - 1) });
	}
	break;
	//chế độ vẽ hình trụ
	case 4:
	{
		CylinderAttribute *cylinder = new CylinderAttribute();
		cylinder->centerObject = { x,y,z };
		cylinder->height = 4;
		//bán kính cho vòng tròn phía trên và bán kính cho đường tròn phía dưới
		//bình thường cứ để nó bằng nhau để tạo thành hình trụ tròn(nếu cho khác nhau sẽ thành hình nón cụt)
		cylinder->radiusUp = 3;
		cylinder->radiusDown = 3;
		cylinder->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		cylinder->id = idToSet;
		cylinderArray.push_back(cylinder);

		caculatorCylinder(cylinder->centerObject, cylinder->radiusUp, cylinder->radiusDown, cylinder->height,
			cylinder->numberLongitude, cylinder->numberLatitude, cylinder->vertexArray);
		CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 14,idToSet,(int)(cylinderArray.size() - 1) });
	}
	break;
	//chế độ vẽ hình kim tự tháp
	case 5:
	{
		PyramidAttribute *pyr = new PyramidAttribute();
		pyr->setCenterPyramid(x, y, z);
		pyr->setVertexAtIndex(0, x, y + 2, z);
		pyr->setVertexAtIndex(1, x - 1, y, z);
		pyr->setVertexAtIndex(2, x, y, z + 1);
		pyr->setVertexAtIndex(3, x + 1, y, z);
		pyr->setVertexAtIndex(4, x, y, z - 1);
		pyr->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		pyr->id = idToSet;

		pyrArray.push_back(pyr);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 15,idToSet,(int)(pyrArray.size() - 1) });
	}
	break;
	//vẽ hình trụ rỗng
	case 6:
	{
		EmptyCylinderAttribute *cylinder = new EmptyCylinderAttribute();
		cylinder->centerObject = { x,y,z };
		cylinder->height = 4;
		//bán kính cho vòng tròn phía trên và bán kính cho đường tròn phía dưới
		//bình thường cứ để nó bằng nhau để tạo thành hình trụ tròn(nếu cho khác nhau sẽ thành hình nón cụt)
		cylinder->radiusUpOut = 3;
		cylinder->radiusDownOut = 3;
		cylinder->radiusUpIn = 2;
		cylinder->radiusDownIn = 2;
		cylinder->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		cylinder->id = idToSet;
		emptyCylinderArray.push_back(cylinder);

		caculatorEmptyCylinder(cylinder->centerObject, cylinder->radiusUpOut, cylinder->radiusDownOut,
			cylinder->radiusUpIn, cylinder->radiusDownIn, cylinder->height, cylinder->numberLongitude,
			cylinder->numberLatitude, cylinder->vertexArray);
		CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
			cylinder->vertexArray, cylinder->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 16,idToSet,(int)(emptyCylinderArray.size() - 1) });
	}
	break;
	//vẽ hình bánh rán
	case 7:
	{
		TorusAttribute *torus = new TorusAttribute();
		torus->centerObject = { x,y,z };
		torus->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		torus->id = idToSet;
		torusArray.push_back(torus);

		caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
			torus->centerObject, torus->vertexArray);
		CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 17,idToSet,(int)(torusArray.size() - 1) });
	}
	break;
	//vẽ hình ảnh
	case 8:
	{
		PictureAttribute *picture = new PictureAttribute();
		picture->centerObject = { x,y,z };
		picture->vertexArray[0] = { x - 1,y + 1,z };
		picture->vertexArray[1] = { x - 1,y - 1,z };
		picture->vertexArray[2] = { x + 1,y - 1,z };
		picture->vertexArray[3] = { x + 1,y + 1,z };
		picture->normalVector[0] = { 0,0,1 };
		picture->normalVector[1] = { 0,0,1 };
		picture->normalVector[2] = { 0,0,1 };
		picture->normalVector[3] = { 0,0,1 };
		picture->id = idToSet;
		pictureArray.push_back(picture);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 18,idToSet,(int)(pictureArray.size() - 1) });
	}
	break;
	//vẽ objectCustom0
	case 9: {
		ObjectCustom0Attribute *object = new ObjectCustom0Attribute();
		object->centerObject = { x,y,z };
		object->insertColor(colorDefaul[0], colorDefaul[1], colorDefaul[2], colorDefaul[3]);
		object->id = idToSet;
		objectCustom0Array.push_back(object);

		//sau khi đặt hình vào mảng thì đặt hình này là hình đang được chọn luôn
		itemsChoice.push_back({ 19,idToSet,(int)(objectCustom0Array.size() - 1) });
	}
			break;
	default:
		break;
	}
	//đối với việc thêm không phải kiểu show trước vẽ sau thì lưu lại thông tin luôn
	if (!isCheck) {
		SaveObjectCreatOrDelete(3);
		//Nếu không phải chế độ check thì sau khi đặt vật xong sẽ đặt modelTop=-1 luôn
		modelTop = -1;
	}
}
//đối với các hình vẽ bằng cách đặt từng vertex thì thêm 1 vertex vào hình đang được chọn
void addVertexInObjectChoice(itemChoice item, int x, int y) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	//nếu không phải là chọn trúng vô cực thì đặt vật,còn nếu chọn trúng vô cực thì bỏ qua
	if (z != 1) {
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		switch (item.object)
		{
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			triaStrip->vertexArray.push_back({ (float)xDown, (float)yDown, (float)zDown });
			//tính toán normal vector
			point v1, v2, v3, normal;
			int sizeVertexArray = triaStrip->vertexArray.size();
			//nếu số đỉnh là chẵng phải đi ngược từ đỉnh cuối lên 2 đỉnh trước để tính normal vector
			//do tính chất của triangleStrip
			v1 = triaStrip->vertexArray.at(sizeVertexArray - 3);
			v2 = triaStrip->vertexArray.at(sizeVertexArray - 2);
			v3 = triaStrip->vertexArray.at(sizeVertexArray - 1);
			if (sizeVertexArray % 2 == 0) {
				normcrossprod(v3, v2, v1, normal);
			}
			else
			{
				normcrossprod(v1, v2, v3, normal);
			}
			triaStrip->normalVector.push_back(normal);
			triaStrip->centerObject = getPointCenterVertexes(triaStrip->vertexArray);
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			triaFan->vertexArray.push_back({ (float)xDown, (float)yDown, (float)zDown });
			//tính toán normal vector
			point normal, v1, v2, v3;
			int sizeVertexArray = triaFan->vertexArray.size();
			//nếu số đỉnh là chẵng phải đi ngược từ đỉnh cuối lên 2 đỉnh trước để tính normal vector
			//do tính chất của triangleStrip
			v1 = triaFan->vertexArray.at(sizeVertexArray - 3);
			v2 = triaFan->vertexArray.at(sizeVertexArray - 2);
			v3 = triaFan->vertexArray.at(sizeVertexArray - 1);
			if (sizeVertexArray % 2 == 0) {
				normcrossprod(v3, v2, v1, normal);
			}
			else
			{
				normcrossprod(v1, v2, v3, normal);
			}
			triaFan->normalVector.push_back(normal);
			triaFan->centerObject = getPointCenterVertexes(triaFan->vertexArray);
		}
		break;
		default:
			break;
		}
	}
}

//hàm kiểm tra xem điểm được cho có bị che khuất trên màn hình không
bool checkDepthForVertex(point vertex, double *modelMatrix, double *projectMatrix, int *viewport) {
	GLdouble xWindowVertex, yWindowVertex, zWindowVertex;
	float zWindow;
	gluProject((GLdouble)vertex.x, (GLdouble)vertex.y, (GLdouble)vertex.z, modelMatrix, projectMatrix, viewport,
		&xWindowVertex, &yWindowVertex, &zWindowVertex);
	//lấy độ sâu nhỏ nhất của màn hình tại ví trí đó
	glReadPixels((int)xWindowVertex, (int)yWindowVertex, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zWindow);
	//kiểm tra xem nếu giá trị zWindow mà nhỏ hơn(gần màn hính hơn) giá trị zVertex thì có nghĩa là
	//vertex đang bị che khuất bởi điểm nào đó trước nó (cho phép sai số 0.0001)
	if (zWindow < ((float)zWindowVertex - 0.0001)) {
		return false;
	}
	else
	{
		return true;
	}
}
//hàm kiểm tra xem vertex được chọn có bị che khuất không,nếu bị che khuất thì 
//bỏ vertex đó đi(cái này dùng khi chọn cộng dồn)
//biến startFrom thông báo vertex mới thêm vào bắt đầu từ vị trí nào(vì các vertex đã được chọn
//từ trước có thể không hiển thị lúc này)
void checkDepthForVertexChoice(vector<int> &vertexChoice, int startFrom,
	double *modelMatrix, double *projectMatrix, int *viewport) {
	itemChoice item = itemsChoice.at(0);
	//biến thông báo điểm đang kiểm tra có bị che khuất hay không
	bool isObscured;
	int numberItem = vertexChoice.size();
	switch (item.object)
	{
	case 3:
	{
		TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(tria->vertexArray[vertexChoice.at(i)],
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(triaStrip->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 5:
	{
		TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(triaFan->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 10:
	{
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(sphere->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 11:
	{
		CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
		int numberVertex = cube->vertexArray.size();
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(cube->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 12:
	{
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(cube->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 13:
	{
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(cone->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 14:
	{
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(cylinder->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 15:
	{
		PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(pyr->vertexArray[vertexChoice.at(i)],
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(cylinder->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 17:
	{
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(torus->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	case 19:
	{
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		for (int i = startFrom; i < numberItem; i++) {
			//kiểm tra xem điểm đang xét có bị che khuất hay không
			isObscured = checkDepthForVertex(object->vertexArray.at(vertexChoice.at(i)),
				modelMatrix, projectMatrix, viewport);
			//nếu bị che khuất thì xóa điểm đó ra khỏi mảng các vertex đang được chọn
			if (!isObscured) {
				vertexChoice.erase(vertexChoice.begin() + i);
				//khi xóa sẽ mất đi 1 phần tử nên giảm tổng số phần tử lại
				i--;
				numberItem--;
			}
		}
	}
	break;
	default:
		break;
	}
}


//kiểm tra xem phần tử nào được chọn bằng id được chọn
void checkWhichObjectById(int hits) {
	//biến này để biết số lượng các vertex trước và sau khi chọn lại
	//nếu khác thì đặt lại centerRotate
	int numberVertexBefore = itemsChoice.size();
	int lastIdChoice = -1, numberObject;
	if (numberVertexBefore > 0) {
		lastIdChoice = itemsChoice.back().id;
	}
	bool isDeleteItemBefore = false;
	//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		itemsChoice.clear();
		isDeleteItemBefore = true;
	}

	int idGetChoiceNow, offset;
	for (int i = 0; i < hits; i++) {
		offset = i * 4;
		//lấy id của vật được chọn
		idGetChoiceNow = bufferIdChoice[offset + 3];
		//kiểm tra xem id này ứng với đối tượng nào
		//kiểm tra các tam giác
		numberObject = triangleArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleAttribute *tria = triangleArray.at(i);
			if (tria->id == idGetChoiceNow) {
				itemsChoice.push_back({ 3,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các triangleStrip
		numberObject = triaStripArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			if (triaStrip->id == idGetChoiceNow) {
				itemsChoice.push_back({ 4,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các triangleFan
		numberObject = triaFanArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			if (triaFan->id == idGetChoiceNow) {
				itemsChoice.push_back({ 5,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các sphere
		numberObject = sphereArray.size();
		for (int i = 0; i < numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			if (sphere->id == idGetChoiceNow) {
				itemsChoice.push_back({ 10,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các cube
		numberObject = cubeArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			if (cube->id == idGetChoiceNow) {
				itemsChoice.push_back({ 11,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các cube round
		numberObject = cubeRoundArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);
			if (cube->id == idGetChoiceNow) {
				itemsChoice.push_back({ 12,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các cone
		numberObject = coneArray.size();
		for (int i = 0; i < numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);
			if (cone->id == idGetChoiceNow) {
				itemsChoice.push_back({ 13,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các cylinder
		numberObject = cylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			if (cylinder->id == idGetChoiceNow) {
				itemsChoice.push_back({ 14,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các pyramid
		numberObject = pyrArray.size();
		for (int i = 0; i < numberObject; i++) {
			PyramidAttribute *pyr = pyrArray.at(i);
			if (pyr->id == idGetChoiceNow) {
				itemsChoice.push_back({ 15,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các emptyCylinder
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			if (cylinder->id == idGetChoiceNow) {
				itemsChoice.push_back({ 16,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các hình bánh rán
		numberObject = torusArray.size();
		for (int i = 0; i < numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			if (torus->id == idGetChoiceNow) {
				itemsChoice.push_back({ 17,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các hình ảnh
		numberObject = pictureArray.size();
		for (int i = 0; i < numberObject; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			if (picture->id == idGetChoiceNow) {
				itemsChoice.push_back({ 18,idGetChoiceNow,i });
				continue;
			}
		}
		//kiểm tra các ObjectCustom0
		numberObject = objectCustom0Array.size();
		for (int i = 0; i < numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			if (object->id == idGetChoiceNow) {
				itemsChoice.push_back({ 19,idGetChoiceNow,i });
				continue;
			}
		}
	}
	//nếu trước đó chưa có vật nào được chọn mà hiện tại có vật được chọn thì đặt lại centerRotate là tâm
	//của vật đầu tiên trong danh sách 
	//có thêm 1 điều kiện thay đổi tâm hình tròn là nếu id của hình cuối cùng của các vật chọn trước khác với
	//id của vật cuối cùng của các vật được chọn hiện tại thì lấy lại centerforRotate
	if (hits > 0) {
		//phải dùng biến để thông báo do nếu lúc trước chưa xóa item mà khi chưa load hết menu đã thả tay ra khỏi phím
		//shift thì các item bị trùng sẽ không bị xóa
		if (!isDeleteItemBefore) {
			clearSameItemsChoice(itemsChoice);
		}
	}
	//nếu chỉ có 1 phần tử được chọn thì xét xem nó có giá trị được lưu trong item nào của symmetryVertex không
	//nếu có thì đặt whichItemSymmetry là vị trí đo
	if (hits == 1 && !symmetryVertices.empty()) {
		//đầu tiên cứ chuyển về -1
		whichItemSymmetry = -1;

		itemChoice item = itemsChoice.back();
		int numberSymmetry;
		//kiểm tra xem ở chế độ nào symmetry nào để xem object đang được chọn có nằm trong chế độ này hay không
		if (symmetryVertexOrObject == 0) {
			SymmetryVertices symmetryVerticesCheck;
			numberSymmetry = symmetryVertices.size();
			for (int i = 0; i < numberSymmetry; i++) {
				symmetryVerticesCheck = symmetryVertices.at(i);
				if (symmetryVerticesCheck.object == item.object &&
					symmetryVerticesCheck.positionInArray == item.positionOfChoice) {
					whichItemSymmetry = i;
					break;
				}
			}
		}
		else
		{
			SymmetryObjects symmetryObjectsCheck;
			numberSymmetry = symmetryObjects.size();
			for (int i = 0; i < numberSymmetry; i++) {
				symmetryObjectsCheck = symmetryObjects.at(i);
				if (symmetryObjectsCheck.object1 == item.object &&
					(symmetryObjectsCheck.positionInArray1 == item.positionOfChoice ||
						symmetryObjectsCheck.positionInArray2 == item.positionOfChoice)) {
					whichItemSymmetry = i;
					break;
				}
			}
		}
	}
	else
	{
		whichItemSymmetry = -1;
	}
}

//kiểm tra xem đối tượng nào được chọn bằng cách nhấn chuột(không chọn xuyên qua đối tượng)
void checkIdChoiceByMouseDown(int x, int y, double *modelMatrix, double *projectMatrix, int *viewport) {
	//vẽ lại để lấy z(do có hàm phía trên xóa hết tất cả vật để xác định mũi tên)
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	drawObject(GL_RENDER);

	bool isClearItemBefore = false;
	double xDown, yDown, zDown;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	int good = gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	if (good == GL_TRUE) {
		float pointZChange = 0 - zDown;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(xDown - 0.02, xDown + 0.02, yDown - 0.02, yDown + 0.02, pointZChange - 0.02, pointZChange + 0.02);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glSelectBuffer(BUFSIZE, bufferIdChoice);
		GLint hits;
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(10000);
		if (modelEditStyle == 0) {
			//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
			if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
				itemsChoice.clear();
				isClearItemBefore = true;
			}
			drawObject(GL_SELECT);
		}
		else
		{
			//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
			if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
				positionFacesChoice.clear();
				positionVerticesChoice.clear();
				isClearItemBefore = true;
			}
			//vẽ các các mặt tam giác để chọn
			drawObjectLineOrPoint(GL_SELECT, modelEditStyle, itemsChoice, positionVerticesChoice, positionFacesChoice, positionChoiceRowOrColumn,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray,
				emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
		}
		//hit là số lượng các tên đã lưu trữ,bắt đầu từ khi lệnh glRenderMode(GL_SELECT) cuối cùng được gọi
		hits = glRenderMode(GL_RENDER);

		if (hits > 0) {
			//nếu là chế độ chọn vật
			if (modelEditStyle == 0)
			{
				//do là chọn bằng cách nhấn chuột nên chỉ có 1 vật được chọn
				checkWhichObjectById(1);
				if (!isClearItemBefore) {
					//xóa đi các vật chọn trùng,nếu không xóa các item trước đó
					clearSameItemsChoice(itemsChoice);
				}
			}
			//nếu là chế độ chọn vertex
			else
			{
				//do là nhấn chuột nên chỉ có 1 vertex được chọn
				positionVerticesChoice.push_back(bufferIdChoice[3]);
				if (!isClearItemBefore) {
					//xóa đi các vertex chọn trùng,nếu không xóa các item trước đó
					clearSamePoints(positionVerticesChoice);
				}
			}
		}
		else
		{
			//nếu không chọn trúng vật nào thì đặt whichItemSymmetry về -1
			if (modelEditStyle == 0) {
				whichItemSymmetry = -1;
			}
		}
	}
}
//hàm kiểm tra xem các đối tượng nào được chọn bằng vùng chọn
void checkIdsChoiceByRectangle(int x, int y, bool isCheckDepth, int modelSpace, double *modelMatrix, double *projectMatrix, int *viewport) {
	float z;
	GLdouble v1[3], v2[3], v3[3];
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	bool isClearItemBefore = false;
	int lastSizeVerticesChoice = positionVerticesChoice.size();

	//nếu k0 chọn trúng mũi tên hay menu thì kiểm tra xem chọn trúng hình k0
	if (mouseDownX != -1) {
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		//tính mặt cắt trái
		gluUnProject((GLdouble)x, (GLdouble)y + 2, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v1[0] = xDown; v1[1] = yDown; v1[2] = zDown;
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v2[0] = xDown; v2[1] = yDown; v2[2] = zDown;
		gluUnProject((GLdouble)x, (GLdouble)y - 1, (GLdouble)z + 0.3, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v3[0] = xDown; v3[1] = yDown; v3[2] = zDown;
		//phải tạo ra 3 điểm k0 cùng nằm trên 1 đường thẳng thì mới tạo ra mặt phẳng được
		//do đó ta thay đổi y và z tùy ý nhưng k0 thay đổi x để cắt theo chiều X

		caculatorPlane(v1, v2, v3, clipPlane3);

		//tính mặt cắt trên
		gluUnProject((GLdouble)x + 2, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v1[0] = xDown; v1[1] = yDown; v1[2] = zDown;
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v2[0] = xDown; v2[1] = yDown; v2[2] = zDown;
		gluUnProject((GLdouble)x - 3, (GLdouble)y, (GLdouble)z + 0.3, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		v3[0] = xDown; v3[1] = yDown; v3[2] = zDown;

		caculatorPlane(v1, v2, v3, clipPlane4);

		glMatrixMode(GL_PROJECTION);
		glLoadMatrixd(projectMatrix);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixd(modelMatrix);
		drawObject(GL_RENDER);

		glSelectBuffer(BUFSIZE, bufferIdChoice);
		GLint hits;
		//đối với chế độ select sẽ chỉ vẽ các tên chứ k0 vẽ cảnh
		//để vẽ cảnh sử dụng GL_RENDER là đối số
		glRenderMode(GL_SELECT);
		//glInitNames() khiến ngăn xếp tên được khởi tạo về trạng thái rỗng mặc định của nó
		//Các cuộc gọi đến glInitNames trong khi chế độ hiển thị không phải là GL_SELECT sẽ bị bỏ qua.
		glInitNames();
		//hàm dưới dùng để đẩy và bật ngăn xếp tên
		glPushName(10000);
		//khi chiếu 2D nó sẽ lấy ngược với khi chiếu 3D
		if (modelSpace == 0) {
			if (x > mouseDownX) {
				for (int i = 0; i < 4; i++) {
					clipPlane1[i] = -clipPlane1[i];
					clipPlane3[i] = -clipPlane3[i];
				}
			}
			if (y < mouseDownY) {
				for (int i = 0; i < 4; i++) {
					clipPlane2[i] = -clipPlane2[i];
					clipPlane4[i] = -clipPlane4[i];
				}
			}
		}
		else
		{
			//các hàm đổi ngược này dùng phòng khi người dùng kéo chuột vẽ hình chữ nhật theo chiều khác
			if (x < mouseDownX) {
				for (int i = 0; i < 4; i++) {
					clipPlane1[i] = -clipPlane1[i];
					clipPlane3[i] = -clipPlane3[i];
				}
			}
			if (y > mouseDownY) {
				for (int i = 0; i < 4; i++) {
					clipPlane2[i] = -clipPlane2[i];
					clipPlane4[i] = -clipPlane4[i];
				}
			}
		}

		glClipPlane(GL_CLIP_PLANE0, clipPlane1);
		glClipPlane(GL_CLIP_PLANE1, clipPlane2);
		glClipPlane(GL_CLIP_PLANE2, clipPlane3);
		glClipPlane(GL_CLIP_PLANE3, clipPlane4);
		glEnable(GL_CLIP_PLANE0);
		glEnable(GL_CLIP_PLANE1);
		glEnable(GL_CLIP_PLANE2);
		glEnable(GL_CLIP_PLANE3);

		//nếu đang ở chế độ chọn vector và chỉ có 1 vật đang được chọn thì cho phép chọn các vertex để thay đổi
		//nếu k0 thì phải chọn vật đã
		if (modelEditStyle != 0 && !itemsChoice.empty()) {
			//nếu phím SHIFT không được nhấn giữ thì xóa hết các item trước đó
			if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
				positionVerticesChoice.clear();
				isClearItemBefore = true;
			}
			drawObjectLineOrPoint(GL_SELECT, modelEditStyle, itemsChoice, positionVerticesChoice, positionFacesChoice, positionChoiceRowOrColumn,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray,
				emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
		}
		else
		{
			drawObject(GL_SELECT);
		}

		//hit là số lượng các tên đã lưu trữ,bắt đầu từ khi lệnh glRenderMode(GL_SELECT) cuối cùng được gọi
		hits = glRenderMode(GL_RENDER);

		glDisable(GL_CLIP_PLANE0);
		glDisable(GL_CLIP_PLANE1);
		glDisable(GL_CLIP_PLANE2);
		glDisable(GL_CLIP_PLANE3);
		if (hits > 0) {
			//trường hợp vượt quá giới hạn của mảng lưu thì sẽ trả về hits là -1(và k0 lưu giá trị nào)
			//giá trị tối đa của mảng lưu ta lưu trong biến BUFSIZE
			int offset = 0;
			//nếu ở chế độ chọn vertex
			if (modelEditStyle != 0) {
				//nếu đang ở chế độ chọn vertex thì kiểm tra xem chọn đỉnh nào để lưu lại
				for (int i = 0; i < hits; i++) {
					offset = i * 4;
					positionVerticesChoice.push_back(bufferIdChoice[offset + 3]);
				}

				if (!isClearItemBefore) {
					//xóa các điểm giống nhau trong chế độ cộng dồn
					clearSamePoints(positionVerticesChoice);
				}
				//nếu có kiểm tra độ sâu thì xóa đi các điểm bị che khuất
				if (isCheckDepth) {
					checkDepthForVertexChoice(positionVerticesChoice, lastSizeVerticesChoice,
						modelMatrix, projectMatrix, viewport);
				}
			}
			//nếu ở chế độ chọn vật thì kiểm tra xem các id đó thuộc những vật nào
			else
			{
				checkWhichObjectById(hits);
			}
		}
		else
		{
			//nếu không chọn trúng vật nào thì đặt whichItemSymmetry về -1
			if (modelEditStyle == 0) {
				whichItemSymmetry = -1;
			}
		}
	}
}
//hàm vẽ các đối tượng pick hoặc draw
void drawObjectPickAndDraw(int x, int y, bool isCheck) {
	//vẽ độ sâu của tất cả các hình đã có và vẽ luôn bề mặt đặt vật để lấy đọ sâu
	drawObjectNotGetChoice();

	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	//nếu không phải chọn trúng vô cực mới thực hiện,nếu không thì bỏ qua
	if (z != 1) {
		int good = gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		if (good == GL_TRUE) {
			//bằng 0 là chế độ vẽ
			if (modelStyleDraw == 0) {
				insertVertexInfor(xDown, yDown, zDown, isCheck);
			}
			//bằng 1 là chế độ dặt các vật hình khối
			else if (modelStyleDraw == 1) {
				drawObjectPick(xDown, yDown, zDown, isCheck);
			}

			//khi đặt vật hay vertex thì ta đặt whichItemSymmetry về -1 luôn
			whichItemSymmetry = -1;
		}
	}
}
//hàm này chỉ thêm vật hay vertex ở vị trí 3D cho trước
void drawObjectPickAndDraw(float x3D, float y3D, float z3D, bool isCheck) {
	if (modelStyleDraw == 0) {
		insertVertexInfor(x3D, y3D, z3D, isCheck);
	}
	//bằng 1 là chế độ dặt các vật hình khối
	else if (modelStyleDraw == 1) {
		drawObjectPick(x3D, y3D, z3D, isCheck);
	}
	//đặt lại vị trí này để lấy dùng cho dịch chuyển
	centerObjectOrVertices = { x3D,y3D,z3D };
}
//hàm dịch chuyển hình hay vertex chưa được xác nhận trong chế độ hiển thị trước vẽ sau
bool moveObjectOrVertexNotDraw(int x, int y,
	GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	//vẽ thêm 1 hình chữ nhật lớn bao phủ các đường viền này để lát khi click chuột vào đây ta có thể
	//lấy được độ sâu của nó chứ k0 phải là độ sâu vô cùng(do k0 click vào vật nào được)


	//vẽ các vật khác ngoại trừ vật đang được chọn(tức là vật đang dịch chuyển nhưng chưa vẽ)
	//vẽ luôn cả phần hình đệm để đặt vật
	//trong hàm này có sẵn hàm xóa các item chưa vẽ xong rồi
	drawObjectNotGetChoice();


	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	//nếu độ sâu khác 1.0 tthif lấy ra vị trí điểm hiện tại
	if (z > 0.0 && z< 1.0) {
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		float valuePlus1, valuePlus2, valuePlus3;
		valuePlus1 = xDown - centerObjectOrVertices.x;
		valuePlus2 = yDown - centerObjectOrVertices.y;
		valuePlus3 = zDown - centerObjectOrVertices.z;

		if (modelStyleDraw == 0) {
			centerObjectOrVertices = { (float)xDown,(float)yDown,(float)zDown };
			//dịch chuyển vertex cuối cùng
			moveLastVertexDraw(itemsChoice.back(), valuePlus1, valuePlus2, valuePlus3,
				triangleArray, triaStripArray, triaFanArray);
		}
		else
		{
			//cái này dùng cho chế độ vẽ đặt vật,còn vẽ vertex thì phải chỉnh sửa lại
			moveShape(valuePlus1, valuePlus2, valuePlus3, modelEditStyle, whichArrowChoice, whichQuadChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
				symmetry_translateX, symmetry_translateY, symmetry_translateZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
		}

		return true;
	}
	else
	{
		return false;
	}
}
//hàm tính mặt cắt trái và trên
void caculatorPlaneTopAndLeft(int x, int y, GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0,
		v1[3], v2[3], v3[3];
	float z;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);

	//tính mặt cắt trái
	gluUnProject((GLdouble)x, (GLdouble)y + 2, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v1[0] = xDown; v1[1] = yDown; v1[2] = zDown;
	gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v2[0] = xDown; v2[1] = yDown; v2[2] = zDown;
	gluUnProject((GLdouble)x, (GLdouble)y - 1, (GLdouble)z + 0.3, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v3[0] = xDown; v3[1] = yDown; v3[2] = zDown;
	//phải tạo ra 3 điểm k0 cùng nằm trên 1 đường thẳng thì mới tạo ra mặt phẳng được
	//do đó ta thay đổi y và z tùy ý nhưng k0 thay đổi x để cắt theo chiều X

	caculatorPlane(v1, v2, v3, clipPlane1);
	//đảo ngược chiều để nó cắt mặt trên(bình thường sẽ cắt mặt dưới)
	clipPlane1[0] = -clipPlane1[0]; clipPlane1[1] = -clipPlane1[1];
	clipPlane1[2] = -clipPlane1[2]; clipPlane1[3] = -clipPlane1[3];

	//tính mặt cắt trên
	gluUnProject((GLdouble)x + 2, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v1[0] = xDown; v1[1] = yDown; v1[2] = zDown;
	gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v2[0] = xDown; v2[1] = yDown; v2[2] = zDown;
	gluUnProject((GLdouble)x - 3, (GLdouble)y, (GLdouble)z + 0.3, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
	v3[0] = xDown; v3[1] = yDown; v3[2] = zDown;

	caculatorPlane(v1, v2, v3, clipPlane2);
	//đảo ngược chiều để nó cắt mặt trên(bình thường sẽ cắt mặt dưới)
	clipPlane2[0] = -clipPlane2[0]; clipPlane2[1] = -clipPlane2[1];
	clipPlane2[2] = -clipPlane2[2]; clipPlane2[3] = -clipPlane2[3];
}
//hàm lấy vertex bằng cách nhấn chuột
bool getVertexByMouseDown(int x, int y, double *modelMatrix, double *projectMatrix, int *viewport) {
	//vẽ lại để lấy z(do có hàm phía trên xóa hết tất cả vật để xác định mũi tên)
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);
	drawObject(GL_RENDER);

	bool isClearItemBefore = false;
	if (glutGetModifiers() != GLUT_ACTIVE_SHIFT) {
		positionFacesChoice.clear();
		positionVerticesChoice.clear();
		isClearItemBefore = true;
	}

	double xDown, yDown, zDown;
	float z, distance, minDistance = 0.03;
	int numberVertex, positionClose = -1;
	point vertexCheck;
	glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
	if (z != 1.0) {
		gluUnProject((GLdouble)x, (GLdouble)y, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		//kiểm tra khoảng cách của tất cả các vertex xem có vertex nào gần điểm cạm này không
		//chỉ lấy 1 vertex gần nhất(cho phép khoảng cách xa nhất 0.04)
		itemChoice item = itemsChoice.at(0);
		switch (item.object)
		{
		case 3: {
			TriangleAttribute *object = triangleArray.at(item.positionOfChoice);
			for (int i = 0; i < 3; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				break;
		case 4: {
			TriangleStripAttribute *object = triaStripArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *object = triaFanArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				break;
		case 10: {
			SphereAttribute *object = sphereArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 11: {
			CubeAttribute *object = cubeArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *object = cubeRoundArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 13: {
			ConeAttribute *object = coneArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 14: {
			CylinderAttribute *object = cylinderArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 15: {
			PyramidAttribute *object = pyrArray.at(item.positionOfChoice);
			for (int i = 0; i < 5; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *object = emptyCylinderArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 17: {
			TorusAttribute *object = torusArray.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 18: {
			PictureAttribute *object = pictureArray.at(item.positionOfChoice);
			for (int i = 0; i < 4; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			numberVertex = object->vertexArray.size();
			for (int i = 0; i < numberVertex; i++) {
				vertexCheck = object->vertexArray[i];
				distance = distanceTwoPoint({ (float)xDown,(float)yDown,(float)zDown }, vertexCheck);
				//nếu khoảng cách này nhỏ hơn min thì thêm vào
				if (distance < minDistance) {
					positionClose = i;
					minDistance = distance;
					//đặt tâm dịch chuyển tại ví trí này luôn
					centerObjectOrVertices = { vertexCheck.x,vertexCheck.y,vertexCheck.z };
				}
			}
		}
				 break;
		default:
			break;
		}

		//nếu đã tìm được điểm gần nhất thì đặt vào
		//nếu không có điểm nào thỏa mãn điều kiện thì bỏ qua
		if (positionClose != -1) {
			positionVerticesChoice.push_back(positionClose);
			if (!isClearItemBefore) {
				//xóa đi các vertex chọn trùng,nếu không xóa các item trước đó
				clearSamePoints(positionVerticesChoice);
			}
			return true;
		}
	}
	return false;
}

//hàm lấy ra row hay Column hiện tại và đối xứng đặt vào positionRowOrColumnChoice và
//đặt tất cả các vertex hiện tại và đối xứng vào positionVerticesChocie
//duy nhất chỉ xét của itemsChoice đầu tiên
void getItemAndItemSymmetryInPositionChoice() {
	//đầu tiên đặt vị trí chọn là vị trí xóa,và lấy ra vị trí các vertex chuân bị xóa
	positionChoiceRowOrColumn.clear();
	positionChoiceRowOrColumn.push_back(positionDeleteRowOrColumn);

	int numberSymmtry = symmetryVertices.size(), numberItemSymmetry;
	SymmetryVertices symmetryCheck;
	//tìm và lấy tất cả các phần tử đối xứng nếu có
	if (numberSymmtry > 0) {
		itemChoice item = itemsChoice.at(0);
		for (int i = 0; i < numberSymmtry; i++) {
			symmetryCheck = symmetryVertices.at(i);
			if (symmetryCheck.object == item.object &&
				symmetryCheck.positionInArray == item.positionOfChoice) {
				numberItemSymmetry = symmetryCheck.positionROrC1.size() < symmetryCheck.positionROrC2.size() ?
					symmetryCheck.positionROrC1.size() : symmetryCheck.positionROrC2.size();
				//nếu đang xóa row của object
				if (positionDeleteRowOrColumn.positionRow != -1) {
					for (int m = 0; m < numberItemSymmetry; m++) {
						if (symmetryCheck.positionROrC1.at(m).positionRow == positionDeleteRowOrColumn.positionRow) {

							positionChoiceRowOrColumn.push_back(symmetryCheck.positionROrC2.at(m));
							break;
						}
						else if (symmetryCheck.positionROrC2.at(m).positionRow == positionDeleteRowOrColumn.positionRow) {
							//do thứ tự phải là symmetry 1 đầu rồi mới đến symmetry 2 nên chuyển cái này lên đầu
							positionChoiceRowOrColumn.insert(positionChoiceRowOrColumn.begin(), symmetryCheck.positionROrC1.at(m));
							break;
						}
					}
				}
				//nếu là xóa column của object
				else
				{
					for (int m = 0; m < numberItemSymmetry; m++) {
						if (symmetryCheck.positionROrC1.at(m).positionColumn == positionDeleteRowOrColumn.positionColumn) {

							positionChoiceRowOrColumn.push_back(symmetryCheck.positionROrC2.at(m));
							break;
						}
						else if (symmetryCheck.positionROrC2.at(m).positionColumn == positionDeleteRowOrColumn.positionColumn) {

							positionChoiceRowOrColumn.insert(positionChoiceRowOrColumn.begin(), symmetryCheck.positionROrC1.at(m));
							break;
						}
					}
				}
			}
		}
	}
	//lấy ra tất cả các vertex có trong row hay column đang được chọn
	getVerticesFromRowOrColumn(itemsChoice.at(0),
		positionChoiceRowOrColumn, positionVerticesChoice,
		sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
		objectCustom0Array);

}

//hàm chỉnh sửa các giá tri bằng mũi tên
void changeValueByArrow(int x, int y, GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	float valuePlus;
	//tính toán giá trị tăng lên cho mũi tên
	bool good = caculatorPlusArrow(firstTouch, whichArrowChoice, x, y, valuePlus,
		modelMatrix, projectMatrix, viewport);
	//nếu bị lỗi trong quá trình xem tìm giá trị tăng lên thì bỏ qua để tính lại
	if (!good) {
		return;
	}

	//nếu kiểu chỉnh sửa là dịch chuyển thì
	if (mouseModel == 3) {
		moveShape(valuePlus, NULL, NULL, modelEditStyle, whichArrowChoice, whichQuadChoice,
			centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
			symmetry_translateX, symmetry_translateY, symmetry_translateZ,
			symmetryVertices, symmetryObjects,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

		//chỉnh giá trị để thêm chuyện đổi vào txt
		if (whichArrowChoice == 0) {
			move_X += valuePlus;
		}
		else if (whichArrowChoice == 1)
		{
			move_Y += valuePlus;
		}
		else
		{
			move_Z += valuePlus;
		}
	}
	//nếu kiểu chỉnh sửa là scale
	else if (mouseModel == 5 && !isMoveCenterRotate) {
		//chỉnh giá trị để thêm chuyện đổi vào txt và scale luôn
		//phải lùi lại scale lúc trước rồi mới scale lại(vì nếu không
		//sẽ cộng dồn scale)
		if (whichArrowChoice == 0) {
			//Phải lùi lại giá trị scale trước vì nếu không sẽ nhân cộng dồn các tỉ lệ
			float valueBack = 1 - (scale_X / (scale_X + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_X += valuePlus;
			scaleShape(scale_X + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
		else if (whichArrowChoice == 1)
		{
			float valueBack = 1 - (scale_Y / (scale_Y + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_Y += valuePlus;
			scaleShape(scale_Y + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
		else
		{
			float valueBack = 1 - (scale_Z / (scale_Z + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_Z += valuePlus;
			scaleShape(scale_Z + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
	}
	//nếu kiểu chỉnh sửa là chỉnh sửa thuộc tính
	else if (mouseModel == 6) {
		EditAttribute(valuePlus, itemsChoice, whichArrowChoice,
			sphereArray, coneArray, cylinderArray, emptyCylinderArray, torusArray);
	}
	//nếu đang ở chế độ xoay mà chọn trúng mũi tên nghĩa là đang ở chế độ dịch chuyển tâm xoay
	else if ((mouseModel == 4 || mouseModel == 5) && isMoveCenterRotate)
	{
		if (whichArrowChoice == 0) {
			centerObjectOrVertices.x += valuePlus;
		}
		else if (whichArrowChoice == 1) {
			centerObjectOrVertices.y += valuePlus;
		}
		else
		{
			centerObjectOrVertices.z += valuePlus;
		}
	}
}

//hàm chỉnh sửa các giá tri bằng quad
void changeValueByQuad(int x, int y, GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	//nếu kiểu chỉnh sửa là dịch chuyển thì
	if (mouseModel == 3) {
		float valuePlus1, valuePlus2, valuePlus3;
		bool good;
		//nếu whichQuadChoice=3 nghĩa là dịch chuyển theo cả 3 chiều sẽ tính khác
		if (whichQuadChoice == 3) {
			//dịch chuyển nhờ vị trí các vertex của các hình đã xác định sẵn
			if (tool_isRemind) {
				float xPosition, yPosition, zPosition;
				good = getPositionByVertexExist(x, y, xPosition, yPosition, zPosition,
					modelMatrix, projectMatrix, viewport,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
				if (good) {
					valuePlus1 = xPosition - centerObjectOrVertices.x;
					valuePlus2 = yPosition - centerObjectOrVertices.y;
					valuePlus3 = zPosition - centerObjectOrVertices.z;

					firstTouch.x += valuePlus1;
					firstTouch.y += valuePlus2;
					firstTouch.z += valuePlus3;
				}
			}
			//tính toán nhờ vị trí x,y và độ sâu
			else
			{
				if (modelEditStyle == 0) {
					drawObjectNotGetChoice();
				}
				good = caculatorPlusQuad(centerObjectOrVertices, firstTouch, x, y, valuePlus1, valuePlus2, valuePlus3,
					modelMatrix, projectMatrix, viewport);
			}
		}
		else
		{
			//tính toán giá trị tăng lên cho quad
			//cái này có 2 giá trị trả về
			good = caculatorPlusQuad(firstTouch, whichQuadChoice, x, y, valuePlus1, valuePlus2,
				modelMatrix, projectMatrix, viewport);
			//nhớ đặt valuePlus3=0 vì đây chỉ dịch chuyển theo 2 hướng
			valuePlus3 = 0;
		}

		//nếu bị lỗi trong quá trình xem tìm giá trị tăng lên thì bỏ qua để tính lại
		if (!good) {
			return;
		}
		moveShape(valuePlus1, valuePlus2, valuePlus3, modelEditStyle, whichArrowChoice, whichQuadChoice,
			centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
			symmetry_translateX, symmetry_translateY, symmetry_translateZ,
			symmetryVertices, symmetryObjects,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

		//chỉnh giá trị để thêm chuyện đổi vào txt
		if (whichQuadChoice == 0) {
			move_Y += valuePlus1;
			move_X += valuePlus2;
		}
		else if (whichQuadChoice == 1)
		{
			move_X += valuePlus1;
			move_Z += valuePlus2;
		}
		else if (whichQuadChoice == 2)
		{
			move_Z += valuePlus1;
			move_Y += valuePlus2;
		}
		else
		{
			move_X += valuePlus1;
			move_Y += valuePlus2;
			move_Z += valuePlus3;
		}
	}
	//nếu kiểu chỉnh sửa là scale
	else if (mouseModel == 5 && !isMoveCenterRotate) {
		float valuePlus;
		bool good;
		//tính toán giá trị tăng lên cho quad
		//cái này có 1 giá trị trả về
		if (whichQuadChoice == 3) {
			//đối với scale qua tất cả các hướng thì ta đặt mũi tên lúc nào cũng hướng lên và sang phải
			GLdouble modelMatrixScale[16];
			glMatrixMode(GL_MODELVIEW);
			//lấy ma trận modelview cho vật
			glLoadIdentity();
			glTranslatef(translateCameraX, translateCameraY, translateCameraZ);
			glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrixScale);
			good = caculatorPlusArrow(firstTouch, 1, x, y, valuePlus,
				modelMatrixScale, projectMatrix, viewport);
			//bị lỗi sẽ nhảy lớn hơn 0.3 hoặc bé hơn -0.3
			/*if (abs(valuePlus) > 0.3) {
			return;
			}*/
		}
		else
		{
			good = caculatorPlusQuad(firstTouch, whichQuadChoice, x, y, valuePlus,
				modelMatrix, projectMatrix, viewport);
		}
		//nếu bị lỗi trong quá trình xem tìm giá trị tăng lên thì bỏ qua để tính lại
		if (!good) {
			return;
		}

		//chỉnh giá trị để thêm chuyện đổi vào txt và scale luôn
		//phải lùi lại scale lúc trước rồi mới scale lại(vì nếu không
		//sẽ cộng dồn scale)
		if (whichQuadChoice == 0) {
			float valueBack = 1 - (scale_X / (scale_X + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_Y += valuePlus;
			scale_X += valuePlus;
			scaleShape(scale_X + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
		else if (whichQuadChoice == 1)
		{
			float valueBack = 1 - (scale_X / (scale_X + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_X += valuePlus;
			scale_Z += valuePlus;
			scaleShape(scale_X + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
		else if (whichQuadChoice == 2) {
			float valueBack = 1 - (scale_Z / (scale_Z + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_Z += valuePlus;
			scale_Y += valuePlus;
			scaleShape(scale_Z + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
		//scale theo 3 chiều
		else
		{
			float valueBack = 1 - (scale_Z / (scale_Z + 1.0));
			scaleShape(valueBack, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
			scale_X += valuePlus;
			scale_Y += valuePlus;
			scale_Z += valuePlus;
			scaleShape(scale_Z + 1.0, modelEditStyle, itemsChoice,
				centerObjectOrVertices, centerObjectOrVerticesSymmetry,
				positionVerticesChoice, whichArrowChoice, whichQuadChoice,
				symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
				symmetryVertices, symmetryObjects,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
				cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
				torusArray, pictureArray, objectCustom0Array);
		}
	}
}
//hàm chỉnh sửa các giá tri bằng circle
void changeValueByCircle(int x, int y, GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	int lastPosition = itemRotate.itemChoiceNow;
	getPositionForRotate(x, y, tool_circleSize,
		modelMatrix, projectMatrix, viewport, itemRotate, centerObjectOrVertices);
	//nếu nhấn lần đầu tiên thì k0 được xoay
	if (itemRotate.firstItemChoice != itemRotate.itemChoiceNow) {
		//tính toán giá trị để rotate
		//tính ra 2 giá trị(lấy cái trước trừ cái sau và ngược lại để xe cái nào nhỏ hơn thì lấy cái đó)
		int value1, value2;
		value1 = itemRotate.itemChoiceNow - lastPosition;
		//nếu 2 điểm này nằm ở 2 bên nửa đường tròn thì phải tính cách khác
		if (itemRotate.itemChoiceNow >= 0 && itemRotate.itemChoiceNow <= 180 && lastPosition >= 180 && lastPosition <= 360) {
			value2 = itemRotate.itemChoiceNow + (360 - lastPosition);
		}
		else if (lastPosition >= 0 && lastPosition <= 180 && itemRotate.itemChoiceNow >= 180 && itemRotate.itemChoiceNow <= 360) {
			value2 = -lastPosition - (360 - itemRotate.itemChoiceNow);
		}
		else
		{
			value2 = value1;
		}

		//giá trị tuyệt đối cái nào nhỏ hơn lấy cái đó
		if (abs(value2) > abs(value1)) {
			//lấy giá trị value2
			//vì ở chế độ xoay chỉnh sửa thuộc tính chỉ dùng vòng tròn y nên k0 lo cái ở trên(trục x)
			if (mouseModel == 4) {
				rotateShape(value1, itemRotate.whichCircleChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice,
					modelEditStyle, positionVerticesChoice,
					symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

				//chỉnh giá trị để thêm chuyện đổi vào txt
				if (itemRotate.whichCircleChoice == 0) {
					rotate_X += value1;
				}
				else if (itemRotate.whichCircleChoice == 1)
				{
					rotate_Y += value1;
				}
				else
				{
					rotate_Z += value1;
				}
			}
			else
			{
				EditAttributeAboutDeg(value1, itemRotate, itemsChoice, sphereArray, coneArray, cylinderArray, emptyCylinderArray);
			}
		}
		else
		{
			//lấy giá trị value2
			//vì ở chế độ xoay chỉnh sửa thuộc tính chỉ dùng vòng tròn y nên k0 lo cái ở trên(trục x)
			if (mouseModel == 4) {
				rotateShape(value2, itemRotate.whichCircleChoice,
					centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice,
					modelEditStyle, positionVerticesChoice,
					symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
					symmetryVertices, symmetryObjects,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

				//chỉnh giá trị để thêm chuyện đổi vào txt
				if (itemRotate.whichCircleChoice == 0) {
					rotate_X += value2;
				}
				else if (itemRotate.whichCircleChoice == 1)
				{
					rotate_Y += value2;
				}
				else
				{
					rotate_Z += value2;
				}
			}
			else
			{
				EditAttributeAboutDeg(value2, itemRotate, itemsChoice, sphereArray, coneArray, cylinderArray, emptyCylinderArray);
			}
		}
	}
}
//hàm dịch chuyển vertex bằng cách di chuyển chuột khi đang ở chế độ chọn
void moveVertexByMouseMove(int x, int y, GLdouble *modelMatrix, GLdouble *projectMatrix, GLint *viewport) {
	float valuePlus1, valuePlus2, valuePlus3;
	bool good;
	//dịch chuyển nhờ vị trí các vertex của các hình đã xác định sẵn
	if (tool_isRemind) {
		float xPosition, yPosition, zPosition;
		good = getPositionByVertexExist(x, y, xPosition, yPosition, zPosition,
			modelMatrix, projectMatrix, viewport,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
			objectCustom0Array);
		if (good) {
			valuePlus1 = xPosition - centerObjectOrVertices.x;
			valuePlus2 = yPosition - centerObjectOrVertices.y;
			valuePlus3 = zPosition - centerObjectOrVertices.z;

			firstTouch.x += valuePlus1;
			firstTouch.y += valuePlus2;
			firstTouch.z += valuePlus3;
		}
	}
	//tính toán nhờ vị trí x,y và độ sâu
	else
	{
		if (modelEditStyle == 0) {
			drawObjectNotGetChoice();
		}
		good = caculatorPlusQuad(centerObjectOrVertices, firstTouch, x, y, valuePlus1, valuePlus2, valuePlus3,
			modelMatrix, projectMatrix, viewport);
	}

	//nếu bị lỗi trong quá trình xem tìm giá trị tăng lên thì bỏ qua để tính lại
	if (!good) {
		return;
	}
	moveShape(valuePlus1, valuePlus2, valuePlus3, modelEditStyle, whichArrowChoice, whichQuadChoice,
		centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
		symmetry_translateX, symmetry_translateY, symmetry_translateZ,
		symmetryVertices, symmetryObjects,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
		coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
	//đặt các giá trị dịch chuyển để lưu vào tệp txt
	move_X += valuePlus1;
	move_Y += valuePlus2;
	move_Z += valuePlus3;
}

//lấy hình ảnh cho texture dùng cho menu
void loadPictureForMenu() {
	char pathTitleImage[][30] = {
		{ "D://picture/menu_title0.png" },{ "D://picture/menu_title1.png" },{ "D://picture/menu_title2.png" },
		{ "D://picture/menu_title3.png" }
	};
	char pathAppImage[][30] = {
		{ "D://picture/menu_app0.png" },{ "D://picture/menu_app1.png" },{ "D://picture/menu_app2.png" },
		{ "D://picture/menu_app3.png" },{ "D://picture/menu_app4.png" }
	};
	char pathMouseImage[][30] = {
		{ "D://picture/menu_mouse0.png" },{ "D://picture/menu_mouse1.png" },{ "D://picture/menu_mouse2.png" },{ "D://picture/menu_mouse3.png" },
		{ "D://picture/menu_mouse4.png" },{ "D://picture/menu_mouse5.png" },{ "D://picture/menu_mouse6.png" },{ "D://picture/menu_mouse7.png" },
		{ "D://picture/menu_mouse8.png" }
	};
	char pathStyleDrawImage[][40] = {
		{ "D://picture/menu_style_draw0.png" },{ "D://picture/menu_style_draw1.png" }
	};
	char pathDrawImage[][30] = {
		{ "D://picture/menu_draw0.png" },{ "D://picture/menu_draw1.png" },{ "D://picture/menu_draw2.png" },
		{ "D://picture/menu_draw3.png" },{ "D://picture/menu_draw4.png" },{ "D://picture/menu_draw5.png" }
	};
	char pathPickImage[][30] = {
		{ "D://picture/menu_pick0.png" },{ "D://picture/menu_pick1.png" },{ "D://picture/menu_pick2.png" },
		{ "D://picture/menu_pick3.png" },{ "D://picture/menu_pick4.png" },{ "D://picture/menu_pick5.png" },
		{ "D://picture/menu_pick6.png" },{ "D://picture/menu_pick7.png" },{ "D://picture/menu_pick8.png" },
		{ "D://picture/menu_pick10.png" },{ "D://picture/menu_pick11.png" }
	};
	char pathEditStyleImage[][30] = {
		{ "D://picture/edit_style0.png" },{ "D://picture/edit_style1.png" },{ "D://picture/edit_style2.png" },
		{ "D://picture/edit_style3.png" }
	};
	char pathEditImage[][30] = {
		{ "D://picture/menu_edit0.png" },{ "D://picture/menu_edit1.png" },{ "D://picture/menu_edit2.png" },
		{ "D://picture/menu_edit3.png" },{ "D://picture/menu_edit4.png" },{ "D://picture/menu_edit5.png" },
		{ "D://picture/menu_edit6.png" },{ "D://picture/menu_edit7.png" }
	};
	char pathSpaceImage[][30] = {
		{ "D://picture/menu_space0.png" },{ "D://picture/menu_space1.png" },{ "D://picture/menu_space2.png" }
	};

	//biến tên liên kết hình ảnh
	GLuint image;

	//tải hình ảnh cho color_picker
	image = LoadImage("D://picture/color_picker.jpg");
	if (image != -1)
	{
		/* gán dữ liệu hình ảnh vào kết cấu  */
		glGenTextures(1, &colorPicker); /* tạo tên liên kết kết cấu */
		glBindTexture(GL_TEXTURE_2D, colorPicker); /* liên kết tên kết cấu */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
			0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	}

	//load các hình ảnh cho các menu
	for (int i = 0; i < 11; i++) {
		if (i < 9) {
			image = LoadImage(pathMouseImage[i]);
			if (image != -1)
			{
				/* gán dữ liệu hình ảnh vào kết cấu  */
				glGenTextures(1, &menuMouse[i]); /* tạo tên liên kết kết cấu */
				glBindTexture(GL_TEXTURE_2D, menuMouse[i]); /* liên kết tên kết cấu */
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
					0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
			}
			if (i < 8) {
				image = LoadImage(pathEditImage[i]);
				if (image != -1)
				{
					/* gán dữ liệu hình ảnh vào kết cấu  */
					glGenTextures(1, &menuEdit[i]); /* tạo tên liên kết kết cấu */
					glBindTexture(GL_TEXTURE_2D, menuEdit[i]); /* liên kết tên kết cấu */
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
						0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
				}
				if (i < 6) {
					image = LoadImage(pathDrawImage[i]);
					if (image != -1)
					{
						/* gán dữ liệu hình ảnh vào kết cấu  */
						glGenTextures(1, &menuDraw[i]); /* tạo tên liên kết kết cấu */
						glBindTexture(GL_TEXTURE_2D, menuDraw[i]); /* liên kết tên kết cấu */
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
						glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
							0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
					}
					if (i < 5) {

						image = LoadImage(pathAppImage[i]);
						if (image != -1)
						{
							/* gán dữ liệu hình ảnh vào kết cấu  */
							glGenTextures(1, &menuApp[i]); /* tạo tên liên kết kết cấu */
							glBindTexture(GL_TEXTURE_2D, menuApp[i]); /* liên kết tên kết cấu */
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
							glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
							glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
								0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
						}
						if (i < 4) {
							image = LoadImage(pathTitleImage[i]);
							if (image != -1)
							{
								/* gán dữ liệu hình ảnh vào kết cấu  */
								glGenTextures(1, &menuTitle[i]); /* tạo tên liên kết kết cấu */
								glBindTexture(GL_TEXTURE_2D, menuTitle[i]); /* liên kết tên kết cấu */
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
									0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
							}

							image = LoadImage(pathEditStyleImage[i]);
							if (image != -1)
							{
								/* gán dữ liệu hình ảnh vào kết cấu  */
								glGenTextures(1, &menuEditStyle[i]); /* tạo tên liên kết kết cấu */
								glBindTexture(GL_TEXTURE_2D, menuEditStyle[i]); /* liên kết tên kết cấu */
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
								glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
								glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
									0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
							}
							if (i < 3) {
								image = LoadImage(pathSpaceImage[i]);
								if (image != -1)
								{
									/* gán dữ liệu hình ảnh vào kết cấu  */
									glGenTextures(1, &menuSpace[i]); /* tạo tên liên kết kết cấu */
									glBindTexture(GL_TEXTURE_2D, menuSpace[i]); /* liên kết tên kết cấu */
									glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
									glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
									glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
										0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
								}
								if (i < 2) {
									image = LoadImage(pathStyleDrawImage[i]);
									if (image != -1)
									{
										/* gán dữ liệu hình ảnh vào kết cấu  */
										glGenTextures(1, &menuStyleDraw[i]); /* tạo tên liên kết kết cấu */
										glBindTexture(GL_TEXTURE_2D, menuStyleDraw[i]); /* liên kết tên kết cấu */
										glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
										glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
										glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
											0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
									}
								}
							}
						}
					}
				}
			}
		}

		image = LoadImage(pathPickImage[i]);
		if (image != -1)
		{
			/* gán dữ liệu hình ảnh vào kết cấu  */
			glGenTextures(1, &menuPick[i]); /* tạo tên liên kết kết cấu */
			glBindTexture(GL_TEXTURE_2D, menuPick[i]); /* liên kết tên kết cấu */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
				0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		}
	}
	/* Bởi vì chúng tôi đã sao chép dữ liệu hình ảnh vào dữ liệu kết cấu, chúng tôi có thể phát hành bộ nhớ được sử dụng bởi hình ảnh. */
	ilDeleteImages(1, &image);
}
//vẽ các thanh menu mô phỏng window(vì ta đã tắt title bar của window)
//chỉ các phần tìm kiếm,còn phần có texture thì hiện trong phần texture cho nhanh rồi
void drawTitleBar() {
	/*glColor3f(0.5f, 0.55f, 0.56f);
	glBegin(GL_LINES);
	glVertex2f(0.0, 38.0);
	glVertex2f(window_width, 38.0);
	glEnd();*/
}
//vẽ ô hiện các database có thể sử dụng
void drawToolBoxDataBase() {
	glColor3f(0.4f, 0.45f, 0.46f);
	if (!isOpenChoiceForder) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(2.0, 42.0);
		glVertex2f(2.0, 70.0);
		glVertex2f(127.0, 42.0);
		glVertex2f(127.0, 70.0);
		glEnd();

	}
	else
	{
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(2.0, 42.0);
		glVertex2f(2.0, 112.0);
		glVertex2f(127.0, 42.0);
		glVertex2f(127.0, 112.0);
		glEnd();
	}
	
	glColor3f(1.0, 1.0, 1.0);
	if (!isOpenChoiceForder) {
		//nếu không phải đang mở thì vẽ tam giác chỉ xuống
		glBegin(GL_TRIANGLES);
		glVertex2f(112.0, 52.0);
		glVertex2f(117.0, 60.0);
		glVertex2f(122.0, 52.0);
		glEnd();
	}
	else
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(122.0, 58.0);
		glVertex2f(117.0, 50.0);
		glVertex2f(112.0, 58.0);

		glVertex2f(125.0, 76.0);
		glVertex2f(121.0, 72.0);
		glVertex2f(117.0, 76.0);

		glVertex2f(117.0, 106.0);
		glVertex2f(121.0, 110.0);
		glVertex2f(125.0, 106.0);
		glEnd();
	}
	
	glBegin(GL_LINES);
	glVertex2f(108.0, 42.0);
	glVertex2f(108.0, 70.0);

	if (isOpenChoiceForder) {
		glVertex2f(2.0, 70.0);
		glVertex2f(127, 70.0);

		glVertex2f(2.0, 92.0);
		glVertex2f(115, 92.0);

		glVertex2f(115.0, 70.0);
		glVertex2f(115.0, 142.0);

		glVertex2f(127.0, 70.0);
		glVertex2f(127.0, 112.0);

		glVertex2f(115.0, 79.0);
		glVertex2f(127.0, 79.0);

		glVertex2f(115.0, 104.0);
		glVertex2f(127.0, 104.0);
	}
	glEnd();
	if (whichDataChoice == 0) {
		drawText(24, 60, "Data Base", "helvetica", 12);
	}
	else if (whichDataChoice == 1) {
		drawText(23, 60, "Opengl1.txt", "helvetica", 12);
	}
	else {
		drawText(23, 60, "Opengl2.txt", "helvetica", 12);
	}
	
	if (isOpenChoiceForder) {
		if (whichDataChoice == 0) {
			drawText(23, 84, "Opengl1.txt", "helvetica", 12);
			drawText(23, 105, "Opengl2.txt", "helvetica", 12);
		}
		else {
			drawText(24, 84, "Data Base", "helvetica", 12);
			if (whichDataChoice == 1) {
				drawText(23, 105, "Opengl2.txt", "helvetica", 12);
			}
			else
			{
				drawText(23, 105, "Opengl1.txt", "helvetica", 12);
			}
		}
		
	}
}
//vẽ menu
void showMenuPicture() {
	glDisable(GL_LIGHTING);

	glColor3f(0.6, 0.6, 0.7);
	glBegin(GL_LINES);
	glVertex2f(2.0, 73.0);
	glVertex2f(window_width*0.8, 73.0);

	glVertex2f(495, 43);
	glVertex2f(495, 68);

	glVertex2f(623, 43);
	glVertex2f(623, 68);

	glVertex2f(390, 43);
	glVertex2f(390, 68);

	if (modelStyleDraw == 1) {
		glVertex2f(430, 76);
		glVertex2f(430, 112);
	}
	
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(391, 49);
	glVertex2f(396, 55);
	glVertex2f(391, 61);

	glEnd();

	//hủy trộn màu(dùng làm mượt răng cưa)
	glDisable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);

	//xác định kiểu kết hợp màu kết cấu và đỉnh là cộng dồn
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);

	//vẽ menuStyleDraw(do chỉ có 1 hình đặt vào 1 vị trí nên không cần vòng lặp for)
	glColor3f(0.34f, 0.39f, 0.4f);
	glBindTexture(GL_TEXTURE_2D, menuStyleDraw[modelStyleDraw]);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0); glVertex2f(0, 73);
	glTexCoord2f(0.0, 1.0); glVertex2f(0, 113);
	glTexCoord2f(1.0, 1.0); glVertex2f(50, 113);
	glTexCoord2f(1.0, 0.0); glVertex2f(50, 73);
	glEnd();

	for (int i = 0; i < 11; i++) {
		if (i < 9) {
			//hiện mouseModel
			if (mouseModel == i) {
				glColor3f(0.6, 0.6, 0.8);
			}
			else
			{
				glColor3f(0.24f, 0.29f, 0.3f);
			}
			glBindTexture(GL_TEXTURE_2D, menuMouse[i]);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuMouse[i][0], positionMenuMouse[i][1]);
			glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuMouse[i][0], positionMenuMouse[i][1] + 40);
			glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuMouse[i][0] + 40, positionMenuMouse[i][1] + 40);
			glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuMouse[i][0] + 40, positionMenuMouse[i][1]);
			glEnd();
			if (i < 8) {
				//vẽ menuEdit
				if (modelEdit == i) {
					glColor3f(0.6, 0.6, 0.8);
				}
				else
				{
					glColor3f(0.24f, 0.29f, 0.3f);
				}
				glBindTexture(GL_TEXTURE_2D, menuEdit[i]);
				glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuEdit[i][0], positionMenuEdit[i][1]);
				glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuEdit[i][0], positionMenuEdit[i][1] + 30);
				glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuEdit[i][0] + 30, positionMenuEdit[i][1] + 30);
				glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuEdit[i][0] + 30, positionMenuEdit[i][1]);
				glEnd();

				if (i < 6) {
					//nếu modelStyleDraw=0 là hiện các menu draw ở vị trí trên cùng để chọn
					if (modelStyleDraw == 0) {
						//vẽ menu trên
						if (modelTop == i) {
							glColor3f(0.6, 0.6, 0.8);
						}
						else
						{
							glColor3f(0.34f, 0.39f, 0.4f);
						}
						glBindTexture(GL_TEXTURE_2D, menuDraw[i]);
						glBegin(GL_TRIANGLE_FAN);
						glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuTop[i][0], positionMenuTop[i][1]);
						glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuTop[i][0], positionMenuTop[i][1] + 40);
						glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuTop[i][0] + 40, positionMenuTop[i][1] + 40);
						glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuTop[i][0] + 40, positionMenuTop[i][1]);
						glEnd();
					}

					if (i < 5) {
						//vẽ menuApp
						//nếu đang ở 2 nút lùi lại và tiến lên load các thông tin đã lưu thì phải kiểm
						//tra xem có thông tin có thể load không thì mới hiện màu
						if ((i == 3 && offsetTxtUsing == -1) ||
							(i == 4 && (txtUsing.empty() || txtUsing.size() - 1 == offsetTxtUsing))) {

							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
							glColor3f(0.20f, 0.25f, 0.26f);

							glBindTexture(GL_TEXTURE_2D, menuApp[i]);
							glBegin(GL_TRIANGLE_FAN);
							glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuApp[i][0], positionMenuApp[i][1]);
							glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuApp[i][0], positionMenuApp[i][1] + 30);
							glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuApp[i][0] + 30, positionMenuApp[i][1] + 30);
							glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuApp[i][0] + 30, positionMenuApp[i][1]);
							glEnd();

							glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
						}
						else
						{
							if (modelApp == i) {
								glColor3f(0.5, 0.51, 0.5);
							}
							else
							{
								glColor3f(0.20f, 0.25f, 0.26f);
							}
							glBindTexture(GL_TEXTURE_2D, menuApp[i]);
							glBegin(GL_TRIANGLE_FAN);
							glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuApp[i][0], positionMenuApp[i][1]);
							glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuApp[i][0], positionMenuApp[i][1] + 30);
							glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuApp[i][0] + 30, positionMenuApp[i][1] + 30);
							glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuApp[i][0] + 30, positionMenuApp[i][1]);
							glEnd();
						}
						
						if (i < 4) {
							//vẽ menuTitle
							if (i == 0) {
								glColor3f(0.2f, 0.25f, 0.26f);

								glBindTexture(GL_TEXTURE_2D, menuTitle[i]);
								glBegin(GL_TRIANGLE_FAN);
								glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuTitle[i][0], positionMenuTitle[i][1]);
								glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuTitle[i][0], positionMenuTitle[i][1] + 40);
								glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuTitle[i][0] + 150, positionMenuTitle[i][1] + 40);
								glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuTitle[i][0] + 150, positionMenuTitle[i][1]);
								glEnd();
							}
							else
							{
								if (modelTitleApp == i) {
									glColor3f(0.6, 0.6, 0.8);
								}
								else
								{
									glColor3f(0.2f, 0.25f, 0.26f);
								}
								glBindTexture(GL_TEXTURE_2D, menuTitle[i]);
								glBegin(GL_TRIANGLE_FAN);
								glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuTitle[i][0], positionMenuTitle[i][1]);
								glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuTitle[i][0], positionMenuTitle[i][1] + 25);
								glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuTitle[i][0] + 50, positionMenuTitle[i][1] + 25);
								glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuTitle[i][0] + 50, positionMenuTitle[i][1]);
								glEnd();
							}

							//vẽ menuEditStyle
							if (modelEditStyle == i) {
								glColor3f(0.6, 0.6, 0.8);
							}
							else
							{
								glColor3f(0.24f, 0.29f, 0.3f);
							}
							glBindTexture(GL_TEXTURE_2D, menuEditStyle[i]);
							glBegin(GL_TRIANGLE_FAN);
							glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuEditStyle[i][0], positionMenuEditStyle[i][1]);
							glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuEditStyle[i][0], positionMenuEditStyle[i][1] + 30);
							glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuEditStyle[i][0] + 30, positionMenuEditStyle[i][1] + 30);
							glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuEditStyle[i][0] + 30, positionMenuEditStyle[i][1]);
							glEnd();
						}
					}
				}
			}
		}
		//nếu modelStyleDraw=1 là hiện các menu pick ở vị trí trên cùng để chọn
		if (modelStyleDraw == 1) {
			//vẽ menu trên
			if (modelTop == i) {
				glColor3f(0.6, 0.6, 0.8);
			}
			else
			{
				glColor3f(0.34f, 0.39f, 0.4f);
			}
			glBindTexture(GL_TEXTURE_2D, menuPick[i]);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuTop[i][0], positionMenuTop[i][1]);
			glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuTop[i][0], positionMenuTop[i][1] + 40);
			glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuTop[i][0] + 40, positionMenuTop[i][1] + 40);
			glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuTop[i][0] + 40, positionMenuTop[i][1]);
			glEnd();
		}
	}

	//xác định kiểu kết hợp màu kết cấu và đỉnh là trung bình 2 màu (mặc định)
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	for (int i = 0; i < 3; i++) {
		//vẽ menuSpace
		if (modelSpace == i) {
			glColor3f(0.3, 0.3, 0.4);
		}
		else
		{
			glColor3f(1.0f, 1.0f, 1.0f);
		}
		glBindTexture(GL_TEXTURE_2D, menuSpace[i]);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0, 0.0); glVertex2f(positionMenuSpace[i][0], positionMenuSpace[i][1]);
		glTexCoord2f(0.0, 1.0); glVertex2f(positionMenuSpace[i][0], positionMenuSpace[i][1] + 40);
		glTexCoord2f(1.0, 1.0); glVertex2f(positionMenuSpace[i][0] + 40, positionMenuSpace[i][1] + 40);
		glTexCoord2f(1.0, 0.0); glVertex2f(positionMenuSpace[i][0] + 40, positionMenuSpace[i][1]);
		glEnd();
	}


	glDisable(GL_TEXTURE_2D);

	//vẽ thanh title bar
	drawTitleBar();

	//vẽ ô hiện các database
	drawToolBoxDataBase();

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}
//hàm kiểm tra xem chọn trúng ô mở các tệp lưu trữ không
bool isChoiceOpenFileData(int x,int y) {
	//kiệm tra xem có chọn trúng ô hiện các tệp để lưu không
	if (x > 108 && x < 127 && y>42 && y < 70) {
		isOpenChoiceForder = !isOpenChoiceForder;
		return true;
	}
	if (!isOpenChoiceForder) {
		if (x > 2 && x < 127 && y>42 && y < 70) {
			
			return true;
		}
	}
	else
	{
		if (x > 2 && x < 127 && y>42 && y < 112) {
			//kiểm tra xem có nhấp trúng hộp chọn 1 không
			if (x > 2 && x < 115 && y>70 && y < 92) {
				if (whichDataChoice == 0) {
					whichDataChoice = 1;
				}
				else
				{
					whichDataChoice = 0;
				}
				isOpenChoiceForder = false;
			}
			//kiểm tra xem có nhấp trúng hộp chọn 2 không
			if (x > 2 && x < 115 && y>92 && y < 112) {
				if (whichDataChoice == 0 || whichDataChoice == 1) {
					whichDataChoice = 2;
				}
				else
				{
					whichDataChoice = 1;
				}
				isOpenChoiceForder = false;
			}
			//kiểm tra xem có nhấp trúng mũi tên dịch chuyển lên không 115 127,30 39 

			//kiểm tra xem có nhấp trúng mũi tên dịch chuyển xuống không 115 127,72 64

			return true;
		}
	}

	return false;
}


//hàm kiểm tra xem có chọn trúng mục nào của title app không
bool checkIsChoiceTitleApp(int x, int y) {
	//kiểm tra xem có chọn trúng vùng title không
	if (y < 40) {
		for (int i = 1; i < 4; i++) {
			if (x > positionMenuTitle[i][0] && x<(positionMenuTitle[i][0] + 50)
				&& y>positionMenuTitle[i][1] && y < (positionMenuTitle[i][1] + 25))
			{
				modelTitleApp = i;
				if (i == 1) {
					//ẩn window hiện tại thành icon phía dưới thanh taskbar của window
					glutIconifyWindow();
				}
				else if (i == 2) {
					//nếu đang ở trạng thái full màn hình thì chuyển về trạng thái thường
					//nếu không thì ngược lại
					if (isFullScreen) {
						window_width = 1700;
						window_height = 900;
						window_top = 10;
						window_left = 10;

						glutSetWindow(window);
						glutPositionWindow(window_top, window_left);
						glutReshapeWindow(window_width, window_height);
						changeSizeWindow(window_width, window_height);

						isFullScreen = false;
					}
					else
					{
						window_width = glutGet(GLUT_SCREEN_WIDTH);
						window_height = glutGet(GLUT_SCREEN_HEIGHT) - 1;
						window_top = 0;
						window_left = 0;

						glutSetWindow(window);
						glutPositionWindow(window_top, window_left);
						glutReshapeWindow(window_width, window_height);
						changeSizeWindow(window_width, window_height);

						isFullScreen = true;
					}
				}
				//nếu là nhấn phím thoát thì hiện hộp thông báo có lưu lại thông tin không
				//sau rồi mới thoát
				else if (i == 3) {
					//còn thiếu hộp lưu thông tin ở đây
					HWND hWnd = GetForegroundWindow();
					//hiện hộp thông báo với 2 nút Ok và cancel
					//text 1 chứa dòng text phía trong hộp
					//text 2 chứa dòng test trên thanh tiêu đề
					//biến sau cùng chứa kiểu thông báo và biểu tượng thông báo
					const int isSave = MessageBox(hWnd, "Save information before close", "Notification",
						MB_YESNOCANCEL | MB_ICONQUESTION);
					//lưu thông tin rồi mới thoát
					if (isSave == IDYES) {
						//khi thoát thì lưu thông tin vào data base cho chắc ăn
						whichDataChoice = 0;

						//dùng 2 thread để 1 thread save thuộc tính app,1 thread load object đã lưu
						thread t1(saveAttributeInDataChoice), t2(saveObjectInDataChoice);
						if (t1.joinable())
						{
							t1.join();
						}
						if (t2.joinable())
						{
							t2.join();
						}

						glutDestroyWindow(window);
						exit(0);
					}
					//thoát luôn mà không lưu thông tin
					else if (isSave == IDNO) {
						glutDestroyWindow(window);
						exit(0);
					}
					//không làm gì cả(không thoát mà cũng không lưu thông tin)
					else
					{
						
					}
				}
				//dù là nhấn trúng item nào trong 3 item thì sau đó chuột cũng không nằm ở trên item đó nữa nên
				//để modelTitleApp = -1 luôn
				modelTitleApp = -1;
				return true;
			}
		}

		//nếu không chọn trúng bất kỳ mục nào ở trên thì đặt modelTitle=0 để kéo dịch chuyển áp
		modelTitleApp = 0;
		return true;
	}
	return false;
}
//kiểm tra xem có vừa nhấn chọn menu k0
bool checkIsChoiceMenu(int x, int y) {
	//kiểm tra xem chọn trúng hộp mở file data không không
	if (isChoiceOpenFileData(x, y)) {
		return true;
	}
	else
	{
		//nếu không nhấn trúng bất kỳ mục nào của hộp dữ liệu thì đóng hộp dữ liệu lại nếu nó đang mở
		isOpenChoiceForder = false;
	}
	//kiểm tra xem có chọn trúng title app không
	if (checkIsChoiceTitleApp(x, y)) {
		return true;
	}
	
	//do modelStyleDraw chỉ có 1 item nên không cần đặt vào vòng lặp for
	if (x > 0 && x< 50 && y>73 && y < 113)
	{
		if (modelStyleDraw == 0) {
			modelStyleDraw = 1;
		}
		else if (modelStyleDraw == 1) {
			modelStyleDraw = 0;
		}
		//đặt về không vẽ hình nào cả
		modelTop = -1;
		return true;
	}

	for (int i = 0; i < 11; i++) {
		if (i < 9) {
			//kiểm tra mouseModel
			if (x > positionMenuMouse[i][0] && x<(positionMenuMouse[i][0] + 40) && y>positionMenuMouse[i][1] && y < (positionMenuMouse[i][1] + 40))
			{
				//nếu đang ở chế độ xoay,dịch chuyển,scale,thay đối thuộc tính thì tính tâm của cùng điều chỉnh
				if (i >= 3 && i <= 6) {
					if (!itemsChoice.empty()) {
						if (modelEditStyle == 0) {
							//lấy vị trí tâm của object đầu tiên và tâm object đối xứng với nó(nếu có)
							//trong số các object đang được chọn
							getCenterObjectChoice(itemsChoice.at(0),
								centerObjectOrVertices, centerObjectOrVerticesSymmetry,
								symmetryObjects,
								triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
								coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
								objectCustom0Array);
						}
						else if (!positionVerticesChoice.empty())
						{
							//lấy vị trí tâm của các vertex đang được chọn,lấy tâm cho các vertexSymmetry và objectSymmetry(nếu có)
							getCenterVertexsForScale(itemsChoice.at(0), positionVerticesChoice,
								centerObjectOrVertices, centerObjectOrVerticesSymmetry,
								symmetryVertices, symmetryObjects,
								triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
								coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
								objectCustom0Array);
						}
					}
				}

				if (i <= 2)
				{
					mouseModel = i;
				}
				//Từ chế độ dịch chuyển trở đi thì phải có vật đang được chọn(khi đang ở chế độ vật)
				//còn nếu ở chế độ khác thì đòi hỏi có vertex đang được chọn mới cho chuyển sang
				else if (!itemsChoice.empty() && (modelEditStyle == 0 || !positionVerticesChoice.empty()))
				{
					mouseModel = i;
					//nếu là chế độ chỉnh sửa thuộc tính thì bất cụm menu chỉnh sửa thuộc tính lên luôn
					if (mouseModel == 6) {
						modelMenuGroup2 = 1;
					}
				}

				//đặt modelTop=-1 để không vẽ gì
				modelTop = -1;
				return true;
			}
			if (i < 8) {
				if (x > positionMenuEdit[i][0] && x<(positionMenuEdit[i][0] + 30)
					&& y>positionMenuEdit[i][1] && y < (positionMenuEdit[i][1] + 30))
				{
					modelEdit = i;
					if (i == 0) {
						if (!itemsChoice.empty()) {
							MakeVertexSameX(itemsChoice.at(0), positionVerticesChoice,
								triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
								coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
								objectCustom0Array);
						}
					}
					else if (i == 1) {
						if (!itemsChoice.empty()) {
							MakeVertexSameY(itemsChoice.at(0), positionVerticesChoice,
								triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
								coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
								objectCustom0Array);
						}
					}
					else if (i == 2) {
						if (!itemsChoice.empty()) {
							MakeVertexSameZ(itemsChoice.at(0), positionVerticesChoice,
								triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
								coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
								objectCustom0Array);
						}
					}
					else if (i == 3) {
						copyObjectsChoice(itemsChoice, idsUsing,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
							cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
						//lưu lại thông tin vật vừa được tạo
						SaveObjectCreatOrDelete(3);
					}
					else if (i == 4) {
						copyInverseObjectChoice(0, itemsChoice, idsUsing,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
							cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
						//lưu lại thông tin vật vừa được tạo
						SaveObjectCreatOrDelete(3);
					}
					else if (i == 5) {
						copyInverseObjectChoice(1, itemsChoice, idsUsing,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
							cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
						//lưu lại thông tin vật vừa được tạo
						SaveObjectCreatOrDelete(3);
					}
					else if (i == 6) {
						copyInverseObjectChoice(2, itemsChoice, idsUsing,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
							cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
						//lưu lại thông tin vật vừa được tạo
						SaveObjectCreatOrDelete(3);
					}
					else if (i == 7) {
						isMoveCenterRotate = !isMoveCenterRotate;
					}

					//đặt modelTop=-1 để không vẽ gì
					modelTop = -1;
					return true;
				}
				if (i < 6) {
					//nếu modelStyleDraw=0 nghĩa là chế độ vẽ vật có 6 item
					if (modelStyleDraw == 0) {
						if (x > positionMenuTop[i][0] && x<(positionMenuTop[i][0] + 40) && y>positionMenuTop[i][1] && y < (positionMenuTop[i][1] + 40))
						{
							modelTop = i;
							mouseModel = 0;
							//nếu bật chế độ vẽ (hay đặt vật) thì xóa hết các hình đang chọn
							//tất nhiên là nếu không phải đang ở hiện thử
							if (isAgreePossition) {
								itemsChoice.clear();

							}

							if (modelTop == 3 || modelTop == 4 || modelTop == 5) {
								vertexLeftToDraw = 3;
								totalVertexOfShape = 3;
							}

							//nếu là chế độ đặt trước vẽ sau thì thêm vật hay vertex ở vị trí (0,0,0)
							//tất nhiên là chế độ vẽ trước đã kết thúc thì mới chọn lại được
							if (tool_isShowBeforeDraw && isAgreePossition) {
								drawObjectPickAndDraw(0.0, 0.0, 0.0, true);
								isAgreePossition = false;
							}
							return true;
						}
					}

					if (i < 5) {
						if (x > positionMenuApp[i][0] && x<(positionMenuApp[i][0] + 30) && y>positionMenuApp[i][1] && y < (positionMenuApp[i][1] + 30))
						{
							modelApp = i;
							//nếu chọn trúng menu save thì lưu dữ liệu lại
							if (modelApp == 0) {
								thread t1(saveAttributeInDataChoice), t2(saveObjectInDataChoice);
								if (t1.joinable())
								{
									t1.join();
								}
								if (t2.joinable())
								{
									t2.join();
								}
								modelApp = -1;
							}
							else if (modelApp == 1) {
								//dùng 2 thread để 1 thread load thuộc tính app,1 thread load object
								thread t1(loadAttributeInDataChoice), t2(loadObjectInDataChoice);
								if (t1.joinable())
								{
									t1.join();
								}
								if (t2.joinable())
								{
									t2.join();
								}
								modelApp = -1;

							}
							else if (modelApp == 2)
							{
								saveDataToTxt(triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray,
									cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray,
									torusArray, pictureArray,
									objectCustom0Array);
								modelApp = -1;
							}
							else if (modelApp == 3) {
								returnChange(false);
							}
							else if (modelApp == 4) {
								returnChange(true);
							}

							//đặt mouseModel về 0 để đề phòng trường hợp xoa hình
							mouseModel = 0;
							//đặt modelTop=-1 để không vẽ gì
							modelTop = -1;
							return true;
						}
						if (i < 4) {
							if (x > positionMenuEditStyle[i][0] && x<(positionMenuEditStyle[i][0] + 30) && y>positionMenuEditStyle[i][1] && y < (positionMenuEditStyle[i][1] + 30))
							{
								//nếu nhấn vào chế độ nào khác ngoài chế độ chọn vật thì bắt buộc phải có vật đang được chọn
								//(tất nhiên là không phải đang có vertex hay hình ở chế độ show trước vẽ sau)
								if (i == 0 || (!itemsChoice.empty() && isAgreePossition)) {
									modelEditStyle = i;
									//chuyển chế độ chuột về 0
									mouseModel = 0;
									//đặt lại chuỗi vertex đang được chọn
									positionChoiceRowOrColumn.clear();
									//xóa hết vertex đang chọn
									positionVerticesChoice.clear();
									//xóa hết các face đang chọn 
									positionFacesChoice.clear();

									//đặt modelTop=-1 để không vẽ gì
									modelTop = -1;
								}
								return true;
							}
							if (i < 3) {
								if (x > positionMenuSpace[i][0] && x<(positionMenuSpace[i][0] + 40) && y>positionMenuSpace[i][1] && y < (positionMenuSpace[i][1] + 40))
								{
									//nếu trước đó là kiểu 2 giờ là kiểu khác,hoăc
									//nếu trước đó là kiểu khác giờ là kiểu 2 thì thay dổi lại kích thước cửa sổ
									if ((modelSpace == 2 && i != 2) || i == 2 && modelSpace != 2) {
										modelSpace = i;
										changeSizeWindow(window_width, window_height);
									}
									else
									{
										modelSpace = i;
									}
									zoomCamera = -20;
									//nếu chọn trúng 2D thì để zoomObject mặc định khác với 3D
									if (i == 0) {
										//biến thông báo vị trí camera
										changeRotateFor2D++;
										if (changeRotateFor2D == 4) {
											changeRotateFor2D = 0;
										}

										rotateCameraX = 0;
										if (changeRotateFor2D == 0) {
											rotateCameraY = 0;
										}
										else if (changeRotateFor2D == 1) {
											rotateCameraY = 270;
										}
										else if (changeRotateFor2D == 2) {
											rotateCameraY = 180;
										}
										else if (changeRotateFor2D == 3) {
											rotateCameraY = 90;
										}
									}
									else
									{
										zoomCamera = -10;
										changeRotateFor2D = -1;
									}
									//lấy ma trận cho projection
									getMatrixForProjection(modelSpace, screen_width, screen_height,
										projectMatrix, projectMatrixArrow);

									//đặt modelTop=-1 để không vẽ gì
									modelTop = -1;
									return true;
								}
							}
						}
					}
				}
			}
		}
		
		//nếu modelStyleDraw=1 nghĩa là chế độ đặt vật có 9 item
		if (modelStyleDraw == 1) {
			if (x > positionMenuTop[i][0] && x<(positionMenuTop[i][0] + 40) && y>positionMenuTop[i][1] && y < (positionMenuTop[i][1] + 40))
			{
				modelTop = i;
				mouseModel = 0;
				//nếu bật chế độ vẽ (hay đặt vật) thì xóa hết các hình đang chọn
				//tất nhiên là nếu không phải đang ở hiện thử
				if (isAgreePossition) {
					itemsChoice.clear();

				}

				//nếu là chế độ đặt trước vẽ sau thì thêm vật hay vertex ở vị trí (0,0,0)
				//tất nhiên là chế độ vẽ trước đã kết thúc thì mới chọn lại được
				if (tool_isShowBeforeDraw && isAgreePossition) {
					drawObjectPickAndDraw(0.0, 0.0, 0.0,true);
					isAgreePossition = false;
				}

				return true;
			}
		}
		
	}

	return false;
}

//hàm load ban đầu cho ứng dụng
void init_window(){
	//load các hình ảnh kết cấu dùng cho gán kết cấu vào vật(phải load kết cấu trước do khi load kết cấu lầm cho các biến 
	//bị biến đổi sai,không hiểu vì sao)
	loadTextureForObject(itemTextureWindow);
	//tải các hình ảnh cho menu
	loadPictureForMenu();
	//dùng 2 thread để 1 thread khởi tạo các giá trị mặc định(và load thuộc tính app(nếu có)),1 thread load object đã lưu(nếu có)
	thread t1(initializationDefaulValue), t2(loadObjectInDataChoice);
	if (t1.joinable())
	{
		t1.join();
	}
	if (t2.joinable())
	{
		t2.join();
	}
}

//các hàm của window
//window chỉ có 1 chức năng duy nhất là chứa các subwwindow nên ngoại trừ việc đó
//nó không cần phải làm gì khác
void window_display() {
	//window chính không làm gì cả,cần hiển thị gì thì cứ dụng các window con là được
}
void window_reshape(int width, int height)
{
	window_width = width;
	window_height = height;

	changeSizeWindow(width, height);

	//tính toán lại ví trí cho menu mỗi lần thay đổi kích thước của sổ
	int leftM = window_width * 0.8;
	positionMenuEditStyle[0][0] = leftM - 123;
	positionMenuEditStyle[1][0] = leftM - 92;
	positionMenuEditStyle[2][0] = leftM - 61;
	positionMenuEditStyle[3][0] = leftM - 30;

	positionMenuTitle[1][0] = window_width - 150;
	positionMenuTitle[2][0] = window_width - 100;
	positionMenuTitle[3][0] = window_width - 50;

	//tính toán vị trí cụm menu 1
	positionMenu1[0] = leftM + 2;
	positionMenu1[1] = window_width - 2;
	positionMenu1[2] = 40;
	positionMenu1[3] = 410 - 2;

	//tính toán vị trí cụm menu 2
	positionMenu2[0] = leftM + 2;
	positionMenu2[1] = window_width - 2;
	positionMenu2[2] = 410;
	positionMenu2[3] = window_height - 43;

}



//các hàm của subwindow

void init_subwindow() {
	glClearColor(0.2f, 0.25f, 0.26f, 1.0f);
	glShadeModel(GL_FLAT);

	//glCullFace xác định xem các đa giác mặt trước hoặc mặt sau có bị hủy hay không (mặc định là mặt sau bị hủy)
	//việc này để đỡ tốn ram vẽ mặt sau
	glEnable(GL_CULL_FACE);
	//tắt không vẽ mặt sau để đỡ tốn cpu
	glCullFace(GL_BACK);

	//làm mịn vết răng cưa
	/*glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);*/
}
void subwindow_display() {
	glClear(GL_COLOR_BUFFER_BIT);
	//load projecMatrix và modelMatrix cho window
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrixWindow);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//hiện cụm menu1 phía bên phải
	showMenuGroup1(colorDefaul,modelMenuGroup1,colorPicker,
		positionMenu1[0], positionMenu1[1], positionMenu1[2], positionMenu1[3]);
	//hiện cụm menu2 phía bên phải
	showMenuGroup2(positionMenu2[0], positionMenu2[1], positionMenu2[2], positionMenu2[3]);

	//vẽ menu
	showMenuPicture();

	glutSwapBuffers();
}
void subwindow_reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	glGetDoublev(GL_PROJECTION_MATRIX, projectMatrixWindow);
}

//hàm kiểm tra nhấn chuột cho window
void subwindow_mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		//kiểm tra có chọn menu
		if (state == GLUT_DOWN) {
			lastTouchX = x;
			lastTouchY = y;

			//lưu lại kiểu hình đang vẽ để lát kiểm tra nếu đang vẽ dở mà nhấn vào bất kỳ menu nào thì hủy bỏ
			int lastDraw = modelTop, lastStyleDraw = modelStyleDraw;
			//nếu chọn trúng menu thì k0 thực hiện hàm dưới nữa
			bool i = checkIsChoiceMenu(x, y);
			if (i == true) {
				//nếu có bất kỳ nút menu nào được nhấn thì xóa hình đặt trước trong chế độ hiện trước vẽ sau
				//và xóa itemsChoice đi vì nó chứa vị trí hình đang chửa bị bị xóa
				if (tool_isShowBeforeDraw && !isAgreePossition && lastDraw !=-1 &&
					(modelTop==-1 || lastDraw != modelTop)) {

					//xóa đi vật sau cùng hay vertex sau cùng(đây chỉ là vật hay vertex đặt thử nên giờ không cần dùng nữa)
					if(lastStyleDraw == 0){
						clearLastVertexDraw(itemsChoice.back(), triaStripArray, triaFanArray);
					}
					else
					{
						deleteModelChoice(itemsChoice, positionVerticesChoice, modelEditStyle, idsUsing,
							symmetryVertices, symmetryObjects,
							triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray,
							cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
					}

					//sau khi đã xóa vật(hay vertex) sau cùng thì nếu vẫn đang chọn menu top thì thêm vật thử mới
					//còn nếu không thì đặt isAgreePosition thành true
					if (modelTop != -1) {
						if (modelTop == 3 || modelTop == 4 || modelTop == 5) {
							vertexLeftToDraw = 3;
							totalVertexOfShape = 3;
						}

						drawObjectPickAndDraw(0.0, 0.0, 0.0, true);
					}
					else
					{
						isAgreePossition = true;
					}
				}

				//đối với các hình vẽ bằng cách thêm từng vertex thì kiểm tra xem số vertex còn lại
				//có đủ hình thành hình không,nếu không thì xóa object đó đi
				if (lastStyleDraw == 0 && lastDraw != modelTop) {
					i = clearLastDrawNotDone(lastDraw, idsUsing,
						triaStripArray, triaFanArray);
					//nếu xóa không đủ vertex nên cần phải xóa thì xóa itemsChoice luôn
					if (i) {
						itemsChoice.clear();
					}
				}
				
			}
			else
			{
				//kiểm tra vị trí nhấn chuột xem có nằm trong vùng của menuGroup1
				if (x > positionMenu1[0] && x<positionMenu1[1] &&
					y>positionMenu1[2] && y < positionMenu1[3]) {
					//kiểm tra xem có chọn trúng các menu trong hộp chọn màu không
					checkChoiceMenuGroup1(x, y, isChoiceColorPicker, modelMenuGroup1,
						positionMenu1[0], positionMenu1[1], positionMenu1[2], positionMenu1[3]);
				}
				//kiểm tra vị trí nhấn chuột xem có nằm trong vùng của menuGroup2
				else if (x > positionMenu2[0] && x<positionMenu2[1] &&
					y>positionMenu2[2] && y < positionMenu2[3]) {

					bool last_isShowBeforeDraw = tool_isShowBeforeDraw;
					//kiểm tra các cụm menu xem có chọn trúng cụm menu nào không
					checkChoiceMenuGroup2(x, y,
						positionMenu2[0], positionMenu2[1], positionMenu2[2], positionMenu2[3]);
					//nếu chọn trúng isShowBeforDraw thì xem xét đặt vật hiện hay vertex hiện
					if (last_isShowBeforeDraw != tool_isShowBeforeDraw) {
						//nếu trước đó không ở chế độ hiện trước mà giờ bất chế độ hiện trước
						//thì xác định hiện hình hay vertex để xem trước
						if (tool_isShowBeforeDraw) {
							if (modelTop != -1) {
								drawObjectPickAndDraw(0.0, 0.0, 0.0, true);
								isAgreePossition = false;
							}
						}
						//nếu trước đó chọn chế độ hiện trước vẽ sau mà giờ bỏ chọn thì
						//nếu có vertex hay hình hiện trước nào đang tồn tại thì xóa đi
						else 
						{
							//nếu đang có object hay vertex đang hiện thử
							if (!isAgreePossition) {
								if (modelStyleDraw == 0) {
									clearLastVertexDraw(itemsChoice.back(), triaStripArray, triaFanArray);

									//kiểm tra xem có đủ vertex không để xóa
									i = clearLastDrawNotDone(lastDraw, idsUsing,
										triaStripArray, triaFanArray);
									//nếu xóa không đủ vertex nên cần phải xóa thì xóa itemsChoice luôn
									if (i) {
										itemsChoice.clear();
									}
								}
								else
								{
									deleteModelChoice(itemsChoice, positionVerticesChoice, modelEditStyle, idsUsing,
										symmetryVertices, symmetryObjects,
										triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray,
										cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
										objectCustom0Array);
								}
								isAgreePossition = true;
							}
						}

					}
				}
			}
			//làm mới toàn bộ
			redisplay_all();
		}
		else
		{
			//ngay khi thả chột ra khỏi menu custom thì sẽ mắt màu chọn vì đay là các thuộc tính dùng luôn chứ k0 dùng lâu dài
			modelEdit = -1;
			modelApp = -1;
			//đặt vị trí chạm chuột cuối cụng về -1
			lastTouchX = -1;
			lastTouchY = -1;
			isChoiceColorPicker = false;

			//làm mới chỉ subwindow(chứa các icon)
			redisplay_subWindow();
		}
	}
}
//theo dõi sự dịch chuyển của chuột(khi có nút chuột được nhấn)
void subwindow_mouseMoveWhenMouseDown(int x, int y) {
	//đầu tiên kiểm tra xem có đang chọn trúng title để dịch chuyển áp không
	if (modelTitleApp == 0) {
		//phải đặt vị trí khung cần lấy là window(do ta đang ở trung hàm quản lý bởi subWindow)
		glutSetWindow(window);

		window_left = glutGet(GLUT_WINDOW_X) + (x - lastTouchX);
		window_top = glutGet(GLUT_WINDOW_Y) + (y - lastTouchY);
		
		//nếu left hoặc top của chuột so với window bằng 0 thì đặt fullscreen luôn nếu không thì chỉ dịch chuyển
		if (window_left + lastTouchX == 0 || window_top + lastTouchY == 0) {
			if (isFullScreen) {
				window_top = 0;
				window_left = 0;
			}
			else
			{
				window_width = glutGet(GLUT_SCREEN_WIDTH);
				window_height = glutGet(GLUT_SCREEN_HEIGHT) - 1;
				window_top = 0;
				window_left = 0;
				glutPositionWindow(window_top, window_left);
				glutReshapeWindow(window_width, window_height);
				changeSizeWindow(window_width, window_height);

				isFullScreen = true;
			}
		}
		else
		{
			//nếu đang ở chế độ full màn hình thì hủy chế độ full màn hình đi mới bắt đầu kéo được
			if (isFullScreen) {
				window_width = 1700;
				window_height = 900;

				glutReshapeWindow(window_width, window_height);
				changeSizeWindow(window_width, window_height);

				isFullScreen = false;
			}

			glutPositionWindow(window_left, window_top);
		}
	}
	else if (isChoiceColorPicker) {
		if (x > positionMenu1[0] + 10 && x < positionMenu1[1] - 10 && y>positionMenu1[2] + 50 && y < positionMenu1[2] + 260) {
			int yColorPicker = window_height - y;
			
			//nếu đang ở chế độ chọn màu cho màu screen thì chuyển giá trị cho màu screen
			if (modelMenuGroup1 == 0) {
				glReadPixels(x, yColorPicker, 1, 1, GL_RGB, GL_FLOAT, colorScreen);
				glutSetWindow(screen1);
				glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
				glutSetWindow(screen2);
				glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
				glutSetWindow(screen);
				glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
			}
			//nếu đang ở chế độ chọn màu cho vật thì đặt màu cho vật luôn
			else
			{
				glReadPixels(x, yColorPicker, 1, 1, GL_RGB, GL_FLOAT, colorDefaul);
				setColorForModelChoice(itemsChoice, colorDefaul,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray,
					cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
			
			//làm mới tất cả screen
			redisplay_screens();
		}
	}
}

//keyboard dùng cho subwindow
void subwindow_keyboard(unsigned char key, int x, int y) {
	keyboardForApp(key);
}

//bắt sự kiện di chuyển chuột khi không có nút nào được nhấn
void subwindow_mouseMoveWhenMouseUp(int x, int y) {
	modelTitleApp = -1;
	modelApp = -1;
	
	for (int i = 0; i < 5; i++) {
		if (x > positionMenuApp[i][0] && x<(positionMenuApp[i][0] + 30) &&
			y>positionMenuApp[i][1] && y < (positionMenuApp[i][1] + 30))
		{
			modelApp = i;
			break;
		}
		if (i < 4) {
			if (x > positionMenuTitle[i][0] && x<positionMenuTitle[i][0] + 50 &&
				y>positionMenuTitle[i][1] && y < positionMenuTitle[i][1] + 30) {
				modelTitleApp = i;
				break;
			}
		}
	}

	glutPostRedisplay();
}


//các hàm của screen

void init_screen() {
	glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// bật GL_COLOR_MATERIAL sẽ cho phép dùng glColor() để thay đổi màu vật liệu của vật
	//hàm phía dưới cho phép đặt màu ánh xạ và môi trường của vật liệu theo màu được đặt bởi glColor()
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	float white[3] = { 1.0,1.0,1.0 };
	//đặt màu phản xạ cho tất cả vật liệu là màu trắng
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

	//phải dùng toán tử new vì đây là biến cục bộ,phải dùng new để thêm 1 stack mới,nếu k0 sau khi hết hàm này sẽ mất giá trị
	//và con trỏ sẽ trỏ đến 1 giá trị đã bị xóa
	//TriangleAttribute *tri = new TriangleAttribute(2.0f, 2.0f, -1.0f, 0.0f, 2.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.4f, 0.8f, 0.5f, 1.0f, 12.0f,0);
	//triangleArray.push_back(tri);

	//glCullFace xác định xem các đa giác mặt trước hoặc mặt sau có bị hủy hay không (mặc định là mặt sau bị hủy)
	//việc này để đỡ tốn ram vẽ mặt sau
	//glEnable(GL_CULL_FACE);

	//làm mịn vết răng cưa
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void screen_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	getModelMatrix(modelMatrix, modelMatrixArrow,
		translateCameraX, translateCameraY, translateCameraZ,
		zoomCamera, rotateCameraX, rotateCameraY, modelSpace);
	
	//vẽ mũi tên chỉ hướng
	drawArrow(projectMatrixArrow,modelMatrixArrow);

	//Đặt lại phép chiếu phối cảnh để vẽ hình
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrix);

	//đặt vị trí của ánh sáng theo vị trí xoay màn hình
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


	//vẽ vật
	//nếu chế độ chọn mặt thì không vẽ vật,để chế độ chọn mặt vẽ vật
	if (modelEditStyle != 3) {
		drawObject(GL_RENDER);
	}

	//nếu đang chế độ sửa hình(thì hiện các đường kẻ trên hình) còn chế độ kia thì vẽ các chấm lên các vertex
	drawObjectLineOrPoint(GL_RENDER, modelEditStyle, itemsChoice, positionVerticesChoice, positionFacesChoice, positionChoiceRowOrColumn,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray,
		emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

	//vẽ lưới(vẽ sau để khi ta dùng chuột để chọn độ sâu bằng lưới này thì khi có cùng độ sâu,vật vẽ trước sẽ nằm ở trên )
	if (tool_isDrawNet) {
		drawNet();
	}

	//hàm vẽ đường tròn chọn,hình chữ nhật chọn và hình chữ nhật đối xứng
	drawCircleRectangleAndRectangleSymmetry();


	//vẽ mũi tên chỉ hướng cho vật đang được chọn(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	DrawArrowOfChoice(changeRotateFor2D); 
	//vẽ các hình chữ nhật chỉnh sửa cùng lúc 2 chiều tương ứng với nó
	DrawQuadsOfChoice();

	//vẽ hình tròn để xoay vật(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	drawCircleRotateForObject(GL_RENDER, false);
	//vẽ đường tròn để chỉnh sửa thuộc tính liên quan đến góc độ của vật
	drawCircleForDivideDegrees(GL_RENDER, false);

	glutSwapBuffers();

	/*
	Cách chọn vật bằng cách chiếu tia: dùng các như phần chọn vị trí trong không gian lúc nãy nhứng theo cách sau
	chọn 1 điểm với z=0.0 và 1 điểm z=1.0 để có 1 tia từ camera tới vô cùng,và xem xét tia này chạm đa giác nào
	gần hơn thì lấy điểm chạm đó
	*/
}
void screen_reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glGetIntegerv(GL_VIEWPORT, viewport);
	//hàm lấy các ma trận project
	getMatrixForProjection(modelSpace, w, h,
		projectMatrix, projectMatrixArrow);

}

//bắt sự kiện mouse down và mouse up
void screen_mouse(int button, int state, int x, int y) {
	if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			lastMouseModel = mouseModel;
			lastTouchX = x;
			lastTouchY = y;
			//nếu =-1 là chế độ xoay màn hình bằng chuột phải
			mouseModel = -1;
		}
		else {
			mouseModel = lastMouseModel;
			lastMouseModel = 0;
		}
		redisplay_all();
	}else if (button == GLUT_LEFT_BUTTON) {
		//phải chuyển đổi lại tọa độ y vì window lấy gốc tọa độ ở trên bên trái 
		//trong khi openGL lấy gốc tọa độ dưới trái
		//nếu dùng LWJGL thay cho glut thì nó sẽ chuyển đổi sẵn cho ta và bước này k0 cần thiết
		int yPosition = screen_height - y;
		if (state == GLUT_DOWN) {
			
			lastTouchX = x;
			lastTouchY = y;
			mouseDownX = x;
			mouseDownY = yPosition;
			//kiểm tra xem nhấn vào mouseModel nào để đặt phương án xử lý
			switch (mouseModel)
			{
			case 0: {
				if (modelTop != -1) {
					//nếu đang không ở chế độ bo vật thì mới cho đặt
					if (!isRoundCorner) {
						//khi đặt vật(hay xác định chính xác chỗ đặt vật) thì hiện attribute của vật ra
						modelMenuGroup2 = 1;


						//nếu là chế độ đặt trước vẽ sau thì khi nhấn chuột chỉ đơn giản là xác nhận vị trí hiện tại thôi
						if (tool_isShowBeforeDraw) {
							if (modelTop != -1) {
								//nếu là chế độ đặt vật thì chuyển modelTop về -1
								if (modelStyleDraw == 1) {
									modelTop = -1;
									isAgreePossition = true;
									//khi đã xác định được vị trí chính xác cần đặt vật thì lưu lại thông tin vật tạo mơi
									SaveObjectCreatOrDelete(3);
								}
								//còn nếu là chế độ đặt vertex thì giảm số vertex cần vẽ xuống
								//vì đây mới chính thức đặt vertex
								else
								{
									//khi đã xác định vertex thì giảm vertex left xuống
									if (modelTop == 3) {
										vertexLeftToDraw--;
										//bang 0 la ve xong 1 hinh
										if (vertexLeftToDraw == 0) {
											vertexLeftToDraw = totalVertexOfShape;
										}
									}
									else
									{
										if (vertexLeftToDraw > 0) {
											vertexLeftToDraw--;
										}
									}

									//bằng 2 vì phía trên là nó lùi đi 1 rồi
									if (vertexLeftToDraw == 2) {
										SaveObjectCreatOrDelete(3);
									}
									else if (vertexLeftToDraw < 2)
									{
										SaveVertexCreatOrDelete(6);
									}

									//rồi ta lại hiện thử 1 vertex mới vào điểm hiện tại
									drawObjectPickAndDraw(x, yPosition,true);
								}
							}
						}
						else
						{
							//gọi hàm xử lý các chức năng vẽ vật
							drawObjectPickAndDraw(x, yPosition, false);
						}
					}
				}
				//nếu không phải chế độ vẽ hay đặt vật thì
				else
				{
					//kiểm tra xem vị trí nhấn chuột có chọn trúng vật hay vertex nào không
					if (modelEditStyle == 0 || modelEditStyle == 1) {
						//nếu là chế độ chọn vật thì vẽ ra để lấy
						if (modelEditStyle == 0) {
							checkIdChoiceByMouseDown(x, yPosition, modelMatrix, projectMatrix, viewport);
						}
						//còn chế độ chọn vertex thì so sánh khoảng cách giữa điểm chọn và các vertex
						else if (modelEditStyle == 1) {
							isChoiceVertexNow = getVertexByMouseDown(x, yPosition, modelMatrix, projectMatrix, viewport);
							//điều kiện nữa là tool_isRemind bằng true thì mới dịch chuyển vertex bằng kéo chuột
							if (!tool_isRemind) {
								isChoiceVertexNow = false;
							}
						}

						//nếu vừa chọ trúng vertex bằng mouseDown thì không vẽ hình chữ nhật nữa
						//mà dịch chuyển như thể whichQuadChoice=3
						if (isChoiceVertexNow) {
							whichQuadChoice = 3;
						}
						else
						{
							//tính toán hình chữ nhật chọn
							caculatorPlaneTopAndLeft(x, yPosition, modelMatrix, projectMatrix, viewport);
						}
					}
					//kiểm tra xem chọn trúng chuỗi vertex nào không
					else if (modelEditStyle == 2 && !itemsChoice.empty()) {
						checkToChoiceRowVertexInObject(itemsChoice, x, yPosition, false,
							modelMatrix, projectMatrix, viewport, itemTextureWindow,
							positionChoiceRowOrColumn, positionVerticesChoice,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
							objectCustom0Array);
					}
					//kiểm tra xem có chọn trúng face nào của vật không
					else if (modelEditStyle == 3 && !itemsChoice.empty()) {
						checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
							modelMatrix, projectMatrix, viewport,
							triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray,
							objectCustom0Array);
					}
				}
			}
					break;
			//chế độ chọn bằng vùng chọn không đồng đều(chưa có)
			case 1: {

			}
					break;
			//chế độ chọn bằng vùng chọn hình cầu
			case 2: {
				//nếu ở chế độ chọn vertex
				if (modelEditStyle == 1) {
					getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);

				}
				//nếu ở chế độ chọn face
				else if (modelEditStyle == 3) {
					//kiểm tra xem các mặt được chọn bằng vùng chọn
					getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
				areaChoice.isChoice = true;
			}
					break;
			//chế độ dịch chuyển,scale hoặc chỉnh sửa thuộc tính hình(hiện mũi tên và quad)
			case 3:
			case 5:{
				checkIsChoiceArrow(x, yPosition, modelMatrix, projectMatrix, viewport);
				checkIsChoiceQuad(x, yPosition, modelMatrix, projectMatrix, viewport);
			}
					break;
			//chế độ xoay hình
			case 4: {
				checkIsChoiceCircleRotate(x, yPosition, modelMatrix, projectMatrix, viewport);
			}
					break;
			//chế độ chỉnh sửa vertex
			case 6: {
				checkIsChoiceArrow(x, yPosition, modelMatrix, projectMatrix, viewport);
				checkIsChoiceCircleRotate(x, yPosition, modelMatrix, projectMatrix, viewport);
			}
					break;
			//chế độ thêm chuỗi vertex
			case 7: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì thêm 1 vertex vào điểm nhấp chuột
				if (item.object<10) {
					addVertexInObjectChoice(item, x, yPosition);
				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta thêm 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ vẽ 1 day vertex dọc,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ vẽ 1 dãy nằm ngang)
				//khi nhấn vào và xác định được các vertex thì cho phép kéo để dịch chuyển các vertex
				//khi thả chuột ra mới thêm vào
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToCreatRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrix, projectMatrix, viewport,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionAddRowOrColumn,
						symmetryVertices,symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
			//chế độ xóa chuỗi vertex
			case 8: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì xóa 1 vertex ở điểm nhấp chuột
				if (item.object<10) {

				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta xóa 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ xóa 1 day vertex ngang,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ xóa 1 dãy nằm dọc)
				//khi nhấn vào và xác định được các vertex sẽ vẽ đen cả dãy vertex đó,
				//khi thả chuột ra mới xóa dãy vertex đó
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrix, projectMatrix, viewport,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionDeleteRowOrColumn,
						symmetryVertices,symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
			default:
				break;
			}
		}
		else if (state == GLUT_UP) {
			//Nếu không phải đang là chế độ đặt vật hay vertex thì mới làm các việc khác
			if (modelTop == -1) {
				//kiểm tra xem có dịch chuyển,xoay hay scale không,nếu có thì lưu vào tệp txt
				if (move_X != 0.0 || move_Y != 0.0 || move_Z != 0.0
					|| rotate_X != 0.0 || rotate_Y != 0.0 || rotate_Z != 0.0
					|| scale_X != 0.0 || scale_Y != 0.0 || scale_Z != 0.0) {

					//hàm này sẽ kiểm tra các giá trị dịch chuyển,scale,rotate để xem biến đổi nào để lưu
					SaveInformationTransform();
				}
				//khi thả chuột ra nếu ở chế độ chọn mặt thì lấy ra các vertex gắn với các mặt được chọn
				else if (modelEditStyle == 3 && !itemsChoice.empty() && !positionFacesChoice.empty()) {
					getVertexByFace(positionVerticesChoice, positionFacesChoice, itemsChoice.at(0), triaStripArray, triaFanArray, sphereArray,
						cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray,
						objectCustom0Array);
				}
				//nếu có di chuyển chuột và đang ở chế độ chọn thì mới chọn bằng vùng chọn
				else if (x != mouseDownX && yPosition != mouseDownY && mouseModel == 0
					&& (modelEditStyle == 0 || modelEditStyle == 1) && !isChoiceVertexNow) {
					checkIdsChoiceByRectangle(x, yPosition, true, modelSpace, modelMatrix, projectMatrix, viewport);
				}
				//nếu đang ở chế độ thêm hàng vertex thì thêm vào
				else if (mouseModel == 7 && (positionAddRowOrColumn.positionRow != -1 ||
					positionAddRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

					addRowVertexInObject(itemsChoice, positionAddRowOrColumn,
						positionChoiceRowOrColumn, positionVerticesChoice,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
					//sau khi thêm chuỗi vertex thì chuyển modelEditStyle=1 là chế độ vertex để hiện các vertex vừa thêm vào
					modelEditStyle = 2;

					//nếu dùng cho xóa hay thêm 1 số vertex thì dùng hàm riêng sẽ nhanh hơn và dễ hơn
					SaveVertexCreatOrDelete(6);

				}
				//nếu đang ở chế độ xóa hàng vertex thì xóa
				else if (mouseModel == 8 && (positionDeleteRowOrColumn.positionRow != -1 ||
					positionDeleteRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

					//hàm lấy ra row hay Column hiện tại và đối xứng đặt vào positionRowOrColumnChoice và
					//đặt tất cả các vertex hiện tại và đối xứng vào positionVerticesChocie
					//duy nhất chỉ xét của itemsChoice đầu tiên
					getItemAndItemSymmetryInPositionChoice();

					SaveVertexCreatOrDelete(7);
					//sau khi lấy xong thì xóa hết do vị trí đó đã bị xóa là không chọn gì cả
					positionChoiceRowOrColumn.clear();

					deleteRowVertexInObject(itemsChoice, positionDeleteRowOrColumn,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}

			//đặt lại biến thông báo vừa nhấn chuột trúng vertex thành false
			isChoiceVertexNow = false;
			//đặt lại đang không ở trong quá trình chọn bằng vùng chọn
			areaChoice.isChoice = false;
			//xóa hết các thông tin vẽ vẽ hình chữ nhật chọn hay hình chữ nhật thêm vertex
			vertexToDrawRectangle.clear();
			vertexToDrawRectangleSymmetry.clear();
			//đặt vị trí để thêm dãy vertex vào sau trở thành -1 để k0 làm gì cả
			positionAddRowOrColumn.positionRow = -1;
			positionAddRowOrColumn.positionColumn = -1;
			positionAddRowOrColumn.positionColumnOpposite = -1;
			//đặt vị trí để xóa dãy vertex trở về -1 để không làm gì cả
			positionDeleteRowOrColumn.positionRow = -1;
			positionDeleteRowOrColumn.positionColumn = -1;
			positionDeleteRowOrColumn.positionColumnOpposite = -1;
			//khi thả chuột ra thì xóa hết thông tin vầ vertex cũng như mũi tên đang chọn
			whichArrowChoice = -1;
			whichQuadChoice = -1;
			//khi thả chuột xóa hết thông tin về các giá trị xoay vật
			itemRotate.firstItemChoice = -1;
			itemRotate.itemChoiceNow = -1;
			itemRotate.whichCircleChoice = -1;
			itemRotate.isRotateLikeClockwise = true;

			offsetOfVertexInfor = 0;
			//đặt lại vị trí bắt đầu chạm
			lastTouchX = -1;
			lastTouchY = -1;
			mouseDownX = -1;
			mouseDownY = -1;
		}
		redisplay_all();
	}
};

//theo dõi sự di chuyển của chuột(khi chuột được nhấn)
void screen_mouseMoveWhenMouseDown(int x, int y)
{
	int yPosition = screen_height - y;

	//kiểm tra xem ở chế độ nào để chỉnh tương ứng
	switch (mouseModel)
	{
	//-1 là chế độ xoay
	case -1: {
		//chỉ ở chế độ 3D mới cho phép xoay
		if (modelSpace != 0) {
			rotateCameraX += (y - lastTouchY);
			rotateCameraY += (x - lastTouchX);
			if (rotateCameraX > 360) {
				rotateCameraX = rotateCameraX - 360;
			}
			else if (rotateCameraX<0)
			{
				rotateCameraX = 360 + rotateCameraX;
			}
			if (rotateCameraY > 360) {
				rotateCameraY = rotateCameraY - 360;
			}
			else if (rotateCameraY<0)
			{
				rotateCameraY = 360 + rotateCameraY;
			}
		}
	}
			 break;
	case 0: {
		if (modelEditStyle == 0 || modelEditStyle == 1) {
			if (mouseDownX != -1) {
				//nếu là vừa nhấp chuột chọn trúng vertex thì không vẽ hình chữ nhật chọn nữa mà dịch chuyển vertex bằng chuột
				if (isChoiceVertexNow) {
					moveVertexByMouseMove(x, yPosition, modelMatrix, projectMatrix, viewport);
				}
				else
				{
					double mouseX, mouseY, mouseZ;
					//xóa các giá trị cũ trước khi thêm lại
					vertexToDrawRectangle.clear();

					gluUnProject((GLdouble)mouseDownX, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrix, projectMatrix, viewport, &mouseX, &mouseY, &mouseZ);
					vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
					gluUnProject((GLdouble)mouseDownX, (GLdouble)yPosition, (GLdouble)0.1, modelMatrix, projectMatrix, viewport, &mouseX, &mouseY, &mouseZ);
					vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
					gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)0.1, modelMatrix, projectMatrix, viewport, &mouseX, &mouseY, &mouseZ);
					vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
					gluUnProject((GLdouble)x, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrix, projectMatrix, viewport, &mouseX, &mouseY, &mouseZ);
					vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				}
			}
		}
		else if (modelEditStyle == 3) {
			checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
				modelMatrix, projectMatrix, viewport,
				triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
				cylinderArray, emptyCylinderArray, torusArray,
				objectCustom0Array);
		}
	}
			break;
	case 1: {

	}
			break;
	case 2: {
		if (!itemsChoice.empty()) {
			//đặt lại vị trí tâm chọn
			GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
			float z;
			//lấy ra giá trị của mặt phẳng chứa hình tròn
			glReadPixels(x, yPosition, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
			gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
			areaChoice.centerArea = { (float)xDown,(float)yDown,(float)zDown };

			if (modelEditStyle == 1) {
				getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
			else if (modelEditStyle == 3) {
				//kiểm tra xem các mặt được chọn bằng vùng chọn
				getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
		}
	}
			break;
	case 3:
	case 5: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrix, projectMatrix, viewport);
		}
		//nếu chọn trúng quad
		else if (whichQuadChoice != -1) {
			changeValueByQuad(x, yPosition, modelMatrix, projectMatrix, viewport);
		}
	}
			break;
	case 4: {
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrix, projectMatrix, viewport);
		}
	}
			break;
	//chế độ chỉnh sửa thuộc tính hình
	case 6: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrix, projectMatrix, viewport);
		}
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrix, projectMatrix, viewport);
		}
	}
			break;
	case 7: {
		//nếu đang ở chế đọ thêm hàng vertex thì diều chỉnh vị trí thêm vertex
		checkToCreatRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrix, projectMatrix, viewport, 
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionAddRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	case 8: {
		checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrix, projectMatrix, viewport,
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionDeleteRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	default:
		break;
	}

	lastTouchX = x;
	lastTouchY = y;
	
	redisplay_screens();
}
//bắt sự kiện di chuyển chuột khi không có nút nào được nhấn
void mouseMoveNotClick(int x, int y) {
	if (mouseModel == 0) {
		//nếu đang ở chế độ hiển thị trước vẽ sau
		if (tool_isShowBeforeDraw && modelTop != -1) {
			moveObjectOrVertexNotDraw(x, screen_height - y,
				modelMatrix, projectMatrix, viewport);
			//nếu đang ở chế độ thêm vertex và có ít nhất 3 vertex đang tồn tại thì tính toán lại normal cuối cùng
			//vì khi dịch chuyển thì normal sẽ không đúng nữa
			if (modelStyleDraw == 0) {
				if (modelTop == 4) {
					TriangleStripAttribute *triaStrip = triaStripArray.back();
					int numberVertex = triaStrip->vertexArray.size();
					if (numberVertex > 2) {
						if (numberVertex % 2 == 0) {
							normcrossprod(triaStrip->vertexArray.at(numberVertex - 1), triaStrip->vertexArray.at(numberVertex - 2),
								triaStrip->vertexArray.at(numberVertex - 3), triaStrip->normalVector.back());
						}
						else
						{
							normcrossprod(triaStrip->vertexArray.at(numberVertex - 3), triaStrip->vertexArray.at(numberVertex - 2),
								triaStrip->vertexArray.at(numberVertex - 1), triaStrip->normalVector.back());
						}
						//nếu đang ở vertex thứ 3 thì đặt cùng normal cho 2 vertex đầu
						if (numberVertex == 3) {
							triaStrip->normalVector.at(0) = triaStrip->normalVector.at(2);
							triaStrip->normalVector.at(1) = triaStrip->normalVector.at(2);
						}
					}
				}
				else if (modelTop == 5) {
					TriangleFanAttribute *triaFan = triaFanArray.back();
					int numberVertex = triaFan->vertexArray.size();
					if (numberVertex > 2) {
						normcrossprod(triaFan->vertexArray.at(0), triaFan->vertexArray.at(numberVertex - 2),
							triaFan->vertexArray.at(numberVertex - 1), triaFan->normalVector.back());
						//nếu đang ở vertex thứ 3 thì đặt cùng normal cho 2 vertex đầu
						if (numberVertex == 3) {
							triaFan->normalVector.at(0) = triaFan->normalVector.at(2);
							triaFan->normalVector.at(1) = triaFan->normalVector.at(2);
						}
					}
				}
			}
			//vẽ lại màn hình
			glutSetWindow(screen);
			glutPostRedisplay();
		}
	}
	//nếu đang ở chế độ chọn bằng vùng chọn thì lấy ra vị trí chuột là tâm của vùng chọn
	else if (mouseModel == 2) {
		int yPosition = screen_height - y;
		GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
		float z;
		//lấy ra giá trị của mặt phẳng chứa hình tròn
		glReadPixels(x, yPosition + 4, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		//nếu z=-1 là ở vô cùng,ta không lấy
		if (z == 1) {
			//vậy nên ta không vẽ vòng tròn chọn
			areaChoice.isChoice = true;
			//vẽ lại màn hình hiện tại
			glutPostRedisplay();
			return;
		}
		gluUnProject((GLdouble)x, (GLdouble)yPosition + 4, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		areaChoice.v[0] = { (float)xDown,(float)yDown,(float)zDown };

		glReadPixels(x - 4, yPosition - 4, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		//nếu z=-1 là ở vô cùng,ta không lấy
		if (z == 1) {
			//vậy nên ta không vẽ vòng tròn chọn
			areaChoice.isChoice = true;

			//vẽ lại màn hình hiện tại
			glutPostRedisplay();
			return;
		}
		gluUnProject((GLdouble)x - 4, (GLdouble)yPosition - 4, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		areaChoice.v[1] = { (float)xDown,(float)yDown,(float)zDown };

		glReadPixels(x + 4, yPosition - 4, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
		//nếu z=-1 là ở vô cùng,ta không lấy
		if (z == 1) {
			//vậy nên ta không vẽ vòng tròn chọn
			areaChoice.isChoice = true;
			//vẽ lại màn hình
			glutSetWindow(screen);
			glutPostRedisplay();
			return;
		}
		gluUnProject((GLdouble)x + 4, (GLdouble)yPosition - 4, (GLdouble)z, modelMatrix, projectMatrix, viewport, &xDown, &yDown, &zDown);
		areaChoice.v[2] = { (float)xDown,(float)yDown,(float)zDown };


		//tính ra tâm của 3 điểm vừa tìm được,dùng nó làm tâm vùng chọn
		areaChoice.centerArea= getPointCenterVertexes(areaChoice.v, 3);
		areaChoice.isChoice = false;

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
	}
}
//bắt sự kiện cuộn nút giữa của chuột
void screen_mouseWheel(int button, int dir, int x, int y)
{
	//nếu là chế độ mouseModel bằng vùng bao thì cuộn chuột dùng để tăng giảm bán kính vùng bao
	if (mouseModel == 2) {
		float value;
		if (dir > 0) {
			value = -0.1f;
		}
		else
		{
			value = 0.1f;
		}
		areaChoice.radius += value;
		if (areaChoice.radius < 0.1f) {
			areaChoice.radius = 0.1f;
		}
	}
	//nếu không thì dùng để dịch chuyển camera xa hay gần
	else
	{
		//dir =1 là cuộn vào,=-1 là cuộn ra
		zoomCamera += dir;
		if (zoomCamera > 0.0f) {
			zoomCamera = 0.0f;
		}
	}
	
	glutPostRedisplay();
}
void screen_keyboard(unsigned char key, int x, int y) {

	//kiểm tra xem có chọn trúng key nào ở các key dùng chung cho toàn window không
	keyboardForApp(key);

	/*từ số 0 đến 9 có đại diện là 48 đến 57
	dấu . là 46*/
	//key==8 phim xoa
	//key=13 phim enter
	//key= 127 là delete
	//các hàm dịch chuyển cảnh
	switch (key)
	{
	case 'W':
	case 'w': {
		//khi nhấn nút lên là màn hình dịch chuyển lên(phải tính sang tọa độ 3D xem lúc đó cần
		//dịch chuyển X,Y hay Z để màn hình hiện lên như là camera đang dịch lên)

		//lấy vị trí tâm màn hình(2D) và dịch chuyển nó lên theo chiều X 1 khoảng mong muốn
		//sau đó chuyển nó sang tọa độ lúc chưa dịch chuyển và sau khi dịch chuyển sang tọa độ 3D mà không có vật gì đang được vẽ
		//để xem nó dịch chuyển trong 3D bao nhiêu(nhớ là Z trên màn hình phải bằng nhau,cho bằng 0.0 hết là chuẩn nhất)

		int x2D = screen_width / 2, y2D = screen_height / 2, z2D = 0.0;
		double x3DFirst, y3DFirst, z3DFirst,
			x3DLast, y3DLast, z3DLast;
		//ta lấy vị trí nằm ở giữa màn hình 2D(ở sát màn hình với z2D=0.0) và chuyển nó sang tọa độ 3D
		gluUnProject((GLdouble)x2D, (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DFirst, &y3DFirst, &z3DFirst);
		//ta tăng giá trị y2D lên và chuyển tiếp tọa độ 2D sang 3D
		gluUnProject((GLdouble)x2D, (GLdouble)(y2D + 800), (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DLast, &y3DLast, &z3DLast);

		//so sánh 2 giá trị 3D trước và sau để lấy ra khoảng cách dịch chuyển X,Y,Z
		translateCameraX += (x3DFirst - x3DLast);
		translateCameraY += (y3DFirst - y3DLast);
		translateCameraZ += (z3DFirst - z3DLast);

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
	}
		break;
	case 'S':
	case 's': {
		int x2D = screen_width / 2, y2D = screen_height / 2, z2D = 0.0;
		double x3DFirst, y3DFirst, z3DFirst,
			x3DLast, y3DLast, z3DLast;
		//ta lấy vị trí nằm ở giữa màn hình 2D(ở sát màn hình với z2D=0.0) và chuyển nó sang tọa độ 3D
		gluUnProject((GLdouble)x2D, (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DFirst, &y3DFirst, &z3DFirst);
		//ta giảm giá trị y2D xuống và chuyển tiếp tọa độ 2D sang 3D
		gluUnProject((GLdouble)x2D, (GLdouble)(y2D - 800), (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DLast, &y3DLast, &z3DLast);

		//so sánh 2 giá trị 3D trước và sau để lấy ra khoảng cách dịch chuyển X,Y,Z
		translateCameraX += (x3DFirst - x3DLast);
		translateCameraY += (y3DFirst - y3DLast);
		translateCameraZ += (z3DFirst - z3DLast);

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
	}
		break;
	case 'A':
	case 'a': {
		int x2D = screen_width / 2, y2D = screen_height / 2, z2D = 0.0;
		double x3DFirst, y3DFirst, z3DFirst,
			x3DLast, y3DLast, z3DLast;
		//ta lấy vị trí nằm ở giữa màn hình 2D(ở sát màn hình với z2D=0.0) và chuyển nó sang tọa độ 3D
		gluUnProject((GLdouble)x2D, (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DFirst, &y3DFirst, &z3DFirst);
		//ta giảm giá trị y2D xuống và chuyển tiếp tọa độ 2D sang 3D
		gluUnProject((GLdouble)(x2D - 800), (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DLast, &y3DLast, &z3DLast);

		//so sánh 2 giá trị 3D trước và sau để lấy ra khoảng cách dịch chuyển X,Y,Z
		translateCameraX += (x3DFirst - x3DLast);
		translateCameraY += (y3DFirst - y3DLast);
		translateCameraZ += (z3DFirst - z3DLast);

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
	}
		break;
	case 'D':
	case 'd': {
		int x2D = screen_width / 2, y2D = screen_height / 2, z2D = 0.0;
		double x3DFirst, y3DFirst, z3DFirst,
			x3DLast, y3DLast, z3DLast;
		//ta lấy vị trí nằm ở giữa màn hình 2D(ở sát màn hình với z2D=0.0) và chuyển nó sang tọa độ 3D
		gluUnProject((GLdouble)x2D, (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DFirst, &y3DFirst, &z3DFirst);
		//ta tăng giá trị y2D lên và chuyển tiếp tọa độ 2D sang 3D
		gluUnProject((GLdouble)(x2D + 800), (GLdouble)y2D, (GLdouble)z2D, modelMatrix, projectMatrix, viewport,
			&x3DLast, &y3DLast, &z3DLast);

		//so sánh 2 giá trị 3D trước và sau để lấy ra khoảng cách dịch chuyển X,Y,Z
		translateCameraX += (x3DFirst - x3DLast);
		translateCameraY += (y3DFirst - y3DLast);
		translateCameraZ += (z3DFirst - z3DLast);

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
	}
		break;
	default:
		break;
	}
	
}

//các hàm cho screen1
void init_screen1() {
	glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightOff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightOff);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// bật GL_COLOR_MATERIAL sẽ cho phép dùng glColor() để thay đổi màu vật liệu của vật
	//hàm phía dưới cho phép đặt màu ánh xạ và môi trường của vật liệu theo màu được đặt bởi glColor()
	/*glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	float white[3] = { 1.0,1.0,1.0 };
	//đặt màu phản xạ cho tất cả vật liệu là màu trắng
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);*/

	//làm mịn vết răng cưa
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void screen1_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	getModelMatrixOnly(modelMatrixImage1, translateCameraXImage1, translateCameraYImage1, zoomCameraImage1, 0, 0, 0);

	//hiện chữ thông báo vị trí nhìn
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screen2D_width, screen2D_height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glColor3f(1.0, 1.0, 1.0);
	drawText(10, 20, "FRONT :", "helvetica", 12);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	//Đặt lại phép chiếu phối cảnh để vẽ hình
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrixImage1);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrixImage1);

	//đặt vị trí của ánh sáng theo vị trí xoay màn hình
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionFront);
	
	glDisable(GL_DEPTH_TEST);
	//vẽ vật
	//nếu chế độ chọn mặt thì không vẽ vật,để chế độ chọn mặt vẽ vật
	if (modelEditStyle != 3) {
		drawObject(GL_RENDER);
	}
	glEnable(GL_DEPTH_TEST);

	//nếu đang chế độ sửa hình(thì hiện các đường kẻ trên hình) còn chế độ kia thì vẽ các chấm lên các vertex
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawObjectLineOrPoint(GL_RENDER, modelEditStyle, itemsChoice, positionVerticesChoice, positionFacesChoice, positionChoiceRowOrColumn,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray,
		emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	//vẽ lưới(vẽ sau để khi ta dùng chuột để chọn độ sâu bằng lưới này thì khi có cùng độ sâu,vật vẽ trước sẽ nằm ở trên )
	if (tool_isDrawNet) {
		drawNet();
	}

	//hàm vẽ đường tròn chọn,hình chữ nhật chọn và hình chữ nhật đối xứng
	drawCircleRectangleAndRectangleSymmetry();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//vẽ hình tròn để xoay vật(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	drawCircleRotateForObject(GL_RENDER, false);
	//vẽ đường tròn để chỉnh sửa thuộc tính liên quan đến góc độ của vật
	drawCircleForDivideDegrees(GL_RENDER, false);

	//vẽ mũi tên chỉ hướng cho vật đang được chọn(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	DrawArrowOfChoice(0);
	//vẽ các hình chữ nhật chỉnh sửa cùng lúc 2 chiều tương ứng với nó
	DrawQuadsOfChoice();
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	glutSwapBuffers();

}
void screen1_reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glGetIntegerv(GL_VIEWPORT, viewportImage1);
	//hàm lấy các ma trận project
	getMatrixForProjectionOnly(0, w, h, projectMatrixImage1);

}
void screen1_mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		//phải chuyển đổi lại tọa độ y vì window lấy gốc tọa độ ở trên bên trái 
		//trong khi openGL lấy gốc tọa độ dưới trái
		//nếu dùng LWJGL thay cho glut thì nó sẽ chuyển đổi sẵn cho ta và bước này k0 cần thiết
		int yPosition = screen2D_height - y;
		if (state == GLUT_DOWN) {
			lastTouchX = x;
			lastTouchY = y;
			mouseDownX = x;
			mouseDownY = yPosition;
			//kiểm tra xem nhấn vào mouseModel nào để đặt phương án xử lý
			switch (mouseModel)
			{
			case 0: {
				//nếu không phải chế độ vẽ hay đặt vật thì
				if(modelTop == -1)
				{
					//kiểm tra xem vị trí nhấn chuột có chọn trúng vật hay vertex nào không
					if (modelEditStyle == 0 || modelEditStyle == 1) {
						if (modelEditStyle == 0) {
							checkIdChoiceByMouseDown(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
						}
						//còn chế độ chọn vertex thì so sánh khoảng cách giữa điểm chọn và các vertex
						else if (modelEditStyle == 1) {
							getVertexByMouseDown(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
						}
						//đoạn này có thể nên có cái là nếu chọn trúng vật hay vertex bằng chuột thì không chọn bằng hình chữ
						//nhật chọn nữa,nếu không chọn trúng thì mới dùng hình chữ nhật chọn

						//tính toán hình chữ nhật chọn
						caculatorPlaneTopAndLeft(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
					}
					//kiểm tra xem chọn trúng chuỗi vertex nào không
					else if (modelEditStyle == 2 && !itemsChoice.empty()) {
						checkToChoiceRowVertexInObject(itemsChoice, x, yPosition, false,
							modelMatrixImage1, projectMatrixImage1, viewportImage1, itemTextureWindow, positionChoiceRowOrColumn, positionVerticesChoice,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
							objectCustom0Array);
					}
					//kiểm tra xem có chọn trúng face nào của vật không
					else if (modelEditStyle == 3 && !itemsChoice.empty()) {
						checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
							modelMatrixImage1, projectMatrixImage1, viewportImage1,
							triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray,
							objectCustom0Array);
					}
				}
			}
					break;
					//chế độ chọn bằng vùng chọn không đồng đều(chưa có)
			case 1: {

			}
					break;
					//chế độ chọn bằng vùng chọn hình cầu
			case 2: {
				//nếu ở chế độ chọn vertex
				if (modelEditStyle == 1) {
					getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);

				}
				//nếu ở chế độ chọn face
				else if (modelEditStyle == 3) {
					//kiểm tra xem các mặt được chọn bằng vùng chọn
					getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
				areaChoice.isChoice = true;
			}
					break;
					//chế độ dịch chuyển,scale hoặc chỉnh sửa thuộc tính hình(hiện mũi tên và quad)
			case 3:
			case 5:
			case 6: {
				checkIsChoiceArrow(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
				checkIsChoiceQuad(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
			}
					break;
					//chế độ xoay hình
			case 4: {
				checkIsChoiceCircleRotate(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
			}
					break;
					//chế độ thêm chuỗi vertex
			case 7: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì thêm 1 vertex vào điểm nhấp chuột
				if (item.object<10) {
					addVertexInObjectChoice(item, x, yPosition);
				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta thêm 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ vẽ 1 day vertex dọc,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ vẽ 1 dãy nằm ngang)
				//khi nhấn vào và xác định được các vertex thì cho phép kéo để dịch chuyển các vertex
				//khi thả chuột ra mới thêm vào
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToCreatRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrixImage1, projectMatrixImage1, viewportImage1,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionAddRowOrColumn,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
					//chế độ xóa chuỗi vertex
			case 8: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì xóa 1 vertex ở điểm nhấp chuột
				if (item.object<10) {

				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta xóa 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ xóa 1 day vertex ngang,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ xóa 1 dãy nằm dọc)
				//khi nhấn vào và xác định được các vertex sẽ vẽ đen cả dãy vertex đó,
				//khi thả chuột ra mới xóa dãy vertex đó
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrixImage1, projectMatrixImage1, viewportImage1,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionDeleteRowOrColumn,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
			default:
				break;
			}
		}
		else if (state == GLUT_UP) {
			//kiểm tra xem có dịch chuyển,xoay hay scale không,nếu có thì lưu vào tệp txt
			if (move_X != 0.0 || move_Y != 0.0 || move_Z != 0.0
				|| rotate_X != 0.0 || rotate_Y != 0.0 || rotate_Z != 0.0
				|| scale_X != 0.0 || scale_Y != 0.0 || scale_Z != 0.0) {

				SaveInformationTransform();
			}

			//khi thả chuột ra nếu ở chế độ chọn mặt thì lấy ra các vertex gắn với các mặt được chọn
			if (modelEditStyle == 3 && !itemsChoice.empty() && !positionFacesChoice.empty()) {
				getVertexByFace(positionVerticesChoice, positionFacesChoice, itemsChoice.at(0), triaStripArray, triaFanArray, sphereArray,
					cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray,
					objectCustom0Array);
			}
			//nếu có di chuyển chuột và đang ở chế độ chọn thì mới chọn bằng vùng chọn
			else if (x != mouseDownX && yPosition != mouseDownY && mouseModel == 0 
				&& (modelEditStyle == 0 || modelEditStyle == 1) && !isChoiceVertexNow) {
				checkIdsChoiceByRectangle(x, yPosition, false, 0, modelMatrixImage1, projectMatrixImage1, viewportImage1);
			}
			//nếu đang ở chế độ thêm hàng vertex thì thêm vào
			else if (mouseModel == 7 && (positionAddRowOrColumn.positionRow != -1 ||
				positionAddRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

				addRowVertexInObject(itemsChoice, positionAddRowOrColumn,
					positionChoiceRowOrColumn, positionVerticesChoice,
					vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
					symmetryVertices, symmetryObjects,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);

				//nếu dùng cho xóa hay thêm 1 số vertex thì dùng hàm riêng sẽ nhanh hơn và dễ hơn
				SaveVertexCreatOrDelete(6);
			}
			//nếu đang ở chế độ xóa hàng vertex thì xóa
			else if (mouseModel == 8 && (positionDeleteRowOrColumn.positionRow != -1 ||
				positionDeleteRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

				//đầu tiên đặt vị trí chọn là vị trí xóa,và lấy ra vị trí các vertex chuân bị xóa
				positionChoiceRowOrColumn.clear();
				positionChoiceRowOrColumn.push_back({ positionDeleteRowOrColumn.positionRow ,
					positionDeleteRowOrColumn.positionColumn, positionDeleteRowOrColumn.positionColumnOpposite });

				getVerticesFromRowOrColumn(itemsChoice.at(0),
					positionChoiceRowOrColumn, positionVerticesChoice,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);

				SaveVertexCreatOrDelete(7);
				//sau khi lấy xong thì xóa hết do vị trí đó đã bị xóa là không chọn gì cả
				positionChoiceRowOrColumn.clear();

				deleteRowVertexInObject(itemsChoice, positionDeleteRowOrColumn, 
					vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
					symmetryVertices, symmetryObjects,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);
			}

			//đặt lại đang không ở trong quá trình chọn bằng vùng chọn
			areaChoice.isChoice = false;
			//xóa hết các thông tin vẽ vẽ hình chữ nhật chọn hay hình chữ nhật thêm vertex
			vertexToDrawRectangle.clear();
			//đặt vị trí để thêm dãy vertex vào sau trở thành -1 để k0 làm gì cả
			positionAddRowOrColumn.positionRow = -1;
			positionAddRowOrColumn.positionColumn = -1;
			positionAddRowOrColumn.positionColumnOpposite = -1;
			//đặt vị trí để xóa dãy vertex trở về -1 để không làm gì cả
			positionDeleteRowOrColumn.positionRow = -1;
			positionDeleteRowOrColumn.positionColumn = -1;
			positionDeleteRowOrColumn.positionColumnOpposite = -1;
			//khi thả chuột ra thì xóa hết thông tin vầ vertex cũng như mũi tên đang chọn
			whichArrowChoice = -1;
			whichQuadChoice = -1;
			//khi thả chuột xóa hết thông tin về các giá trị xoay vật
			itemRotate.firstItemChoice = -1;
			itemRotate.itemChoiceNow = -1;
			itemRotate.whichCircleChoice = -1;
			itemRotate.isRotateLikeClockwise = true;

			offsetOfVertexInfor = 0;
			//đặt lại vị trí bắt đầu chạm
			lastTouchX = -1;
			lastTouchY = -1;
			mouseDownX = -1;
			mouseDownY = -1;
		}
		redisplay_all();
	}
};
//theo dõi sự di chuyển của chuột(khi chuột được nhấn)
void screen1_mouseMoveWhenMouseDown(int x, int y)
{
	int yPosition = screen2D_height - y;

	//kiểm tra xem ở chế độ nào để chỉnh tương ứng
	switch (mouseModel)
	{
	case 0: {
		if (modelEditStyle == 0 || modelEditStyle == 1) {
			if (mouseDownX != -1) {
				double mouseX, mouseY, mouseZ;
				//xóa các giá trị cũ trước khi thêm lại
				vertexToDrawRectangle.clear();

				gluUnProject((GLdouble)mouseDownX, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrixImage1, projectMatrixImage1, viewportImage1,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)mouseDownX, (GLdouble)yPosition, (GLdouble)0.1, modelMatrixImage1, projectMatrixImage1, viewportImage1,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)0.1, modelMatrixImage1, projectMatrixImage1, viewportImage1,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)x, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrixImage1, projectMatrixImage1, viewportImage1,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
			}
		}
		else if (modelEditStyle == 3) {
			checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
				modelMatrixImage1, projectMatrixImage1, viewportImage1,
				triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
				cylinderArray, emptyCylinderArray, torusArray,
				objectCustom0Array);
		}
	}
			break;
	case 1: {

	}
			break;
	case 2: {
		if (!itemsChoice.empty()) {
			//đặt lại vị trí tâm chọn
			GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
			float z;
			//lấy ra giá trị của mặt phẳng chứa hình tròn
			glReadPixels(x, yPosition, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
			gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)z, modelMatrixImage1, projectMatrixImage1, viewportImage1, &xDown, &yDown, &zDown);
			areaChoice.centerArea = { (float)xDown,(float)yDown,(float)zDown };

			if (modelEditStyle == 1) {
				getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
			else if (modelEditStyle == 3) {
				//kiểm tra xem các mặt được chọn bằng vùng chọn
				getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
		}
	}
			break;
	case 3:
	case 5: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
		}
		//nếu chọn trúng quad
		else if (whichQuadChoice != -1) {
			changeValueByQuad(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
		}
	}
			break;
	case 4: {
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
		}
	}
			break;
			//chế độ chỉnh sửa thuộc tính hình
	case 6: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
		}
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrixImage1, projectMatrixImage1, viewportImage1);
		}
	}
			break;
	case 7: {
		//nếu đang ở chế đọ thêm hàng vertex thì diều chỉnh vị trí thêm vertex
		checkToCreatRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrixImage1, projectMatrixImage1, viewportImage1,
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionAddRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	case 8: {
		checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrixImage1, projectMatrixImage1, viewportImage1,
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionDeleteRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	default:
		break;
	}

	lastTouchX = x;
	lastTouchY = y;

	//load lại tất cả screen
	redisplay_screens();
}
//bắt sự kiện cuộn nút giữa của chuột
void screen1_mouseWheel(int button, int dir, int x, int y)
{
	//dir =1 là cuộn vào,=-1 là cuộn ra
	zoomCameraImage1 += dir;
	if (zoomCameraImage1 > 0.0) {
		zoomCameraImage1 = 0.0;
	}
	
	glutPostRedisplay();
	return;
}
void screen1_keyboard(unsigned char key, int x, int y) {

	//kiểm tra xem có chọn trúng key nào ở các key dùng chung cho toàn window không
	keyboardForApp(key);

	/*từ số 0 đến 9 có đại diện là 48 đến 57
	dấu . là 46*/
	//key==8 phim xoa
	//key=13 phim enter
	//key= 127 là delete
	//các hàm dịch chuyển cảnh
	switch (key)
	{
	case 'W':
	case 'w':
		translateCameraYImage1 -= 0.4f;

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		translateCameraYImage1 += 0.4f;

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		translateCameraXImage1 += 0.4f;

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'D':
	case 'd':
		translateCameraXImage1 -= 0.4f;

		//vẽ lại màn hình hiện tại
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

//các hàm cho screen2
void init_screen2() {
	glClearColor(colorScreen[0], colorScreen[1], colorScreen[2], colorScreen[3]);
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 1.0);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightOff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightOff);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// bật GL_COLOR_MATERIAL sẽ cho phép dùng glColor() để thay đổi màu vật liệu của vật
	//hàm phía dưới cho phép đặt màu ánh xạ và môi trường của vật liệu theo màu được đặt bởi glColor()
	/*glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	float white[3] = { 1.0,1.0,1.0 };
	//đặt màu phản xạ cho tất cả vật liệu là màu trắng
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);*/

	//làm mịn vết răng cưa
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
}

void screen2_display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	getModelMatrixOnly(modelMatrixImage2, translateCameraXImage2, translateCameraYImage2, zoomCameraImage2, 0, 270, 0);
	
	//hiện chữ thông báo vị trí nhìn
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, screen2D_width, screen2D_height, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glColor3f(1.0, 1.0, 1.0);
	drawText(10, 20, "RIGHT :", "helvetica", 12);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);

	//Đặt lại phép chiếu phối cảnh để vẽ hình
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectMatrixImage2);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(modelMatrixImage2);

	//đặt vị trí của ánh sáng theo vị trí xoay màn hình
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositionLeft);

	glDisable(GL_DEPTH_TEST);
	//vẽ vật
	//nếu chế độ chọn mặt thì không vẽ vật,để chế độ chọn mặt vẽ vật
	if (modelEditStyle != 3) {
		drawObject(GL_RENDER);
	}
	glEnable(GL_DEPTH_TEST);

	//nếu đang chế độ sửa hình(thì hiện các đường kẻ trên hình) còn chế độ kia thì vẽ các chấm lên các vertex
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	drawObjectLineOrPoint(GL_RENDER, modelEditStyle, itemsChoice, positionVerticesChoice, positionFacesChoice, positionChoiceRowOrColumn,
		triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray,
		emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	//vẽ lưới(vẽ sau để khi ta dùng chuột để chọn độ sâu bằng lưới này thì khi có cùng độ sâu,vật vẽ trước sẽ nằm ở trên )
	if (tool_isDrawNet) {
		drawNet();
	}

	//hàm vẽ đường tròn chọn,hình chữ nhật chọn và hình chữ nhật đối xứng
	drawCircleRectangleAndRectangleSymmetry();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//vẽ hình tròn để xoay vật(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	drawCircleRotateForObject(GL_RENDER, false);
	//vẽ đường tròn để chỉnh sửa thuộc tính liên quan đến góc độ của vật
	drawCircleForDivideDegrees(GL_RENDER, false);

	//vẽ mũi tên chỉ hướng cho vật đang được chọn(phải vẽ sau tất cả các vật để nó có thể nhìn thấy xuyên qua tất cả các vật)
	DrawArrowOfChoice(1);
	//vẽ các hình chữ nhật chỉnh sửa cùng lúc 2 chiều tương ứng với nó
	DrawQuadsOfChoice();
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	glutSwapBuffers();

}
void screen2_reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glGetIntegerv(GL_VIEWPORT, viewportImage2);
	//hàm lấy các ma trận project
	getMatrixForProjectionOnly(0, w, h, projectMatrixImage2);
}

void screen2_mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		//phải chuyển đổi lại tọa độ y vì window lấy gốc tọa độ ở trên bên trái 
		//trong khi openGL lấy gốc tọa độ dưới trái
		//nếu dùng LWJGL thay cho glut thì nó sẽ chuyển đổi sẵn cho ta và bước này k0 cần thiết
		int yPosition = screen2D_height - y;
		if (state == GLUT_DOWN) {
			lastTouchX = x;
			lastTouchY = y;
			mouseDownX = x;
			mouseDownY = yPosition;
			//kiểm tra xem nhấn vào mouseModel nào để đặt phương án xử lý
			switch (mouseModel)
			{
			case 0: {
				//nếu không phải chế độ vẽ hay đặt vật thì
				if (modelTop == -1)
				{
					//kiểm tra xem vị trí nhấn chuột có chọn trúng vật hay vertex nào không
					if (modelEditStyle == 0 || modelEditStyle == 1) {
						if (modelEditStyle == 0) {
							checkIdChoiceByMouseDown(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
						}
						//còn chế độ chọn vertex thì so sánh khoảng cách giữa điểm chọn và các vertex
						else if (modelEditStyle == 1) {
							getVertexByMouseDown(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
						}
						//đoạn này có thể nên có cái là nếu chọn trúng vật hay vertex bằng chuột thì không chọn bằng hình chữ
						//nhật chọn nữa,nếu không chọn trúng thì mới dùng hình chữ nhật chọn

						//tính toán hình chữ nhật chọn
						caculatorPlaneTopAndLeft(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
					}
					//kiểm tra xem chọn trúng chuỗi vertex nào không
					else if (modelEditStyle == 2 && !itemsChoice.empty()) {
						checkToChoiceRowVertexInObject(itemsChoice, x, yPosition, false,
							modelMatrixImage2, projectMatrixImage2, viewportImage2, itemTextureWindow, positionChoiceRowOrColumn, positionVerticesChoice,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
							objectCustom0Array);
					}
					//kiểm tra xem có chọn trúng face nào của vật không
					else if (modelEditStyle == 3 && !itemsChoice.empty()) {
						checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
							modelMatrixImage2, projectMatrixImage2, viewportImage2,
							triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray,
							objectCustom0Array);
					}
				}
			}
					break;
					//chế độ chọn bằng vùng chọn không đồng đều(chưa có)
			case 1: {

			}
					break;
					//chế độ chọn bằng vùng chọn hình cầu
			case 2: {
				//nếu ở chế độ chọn vertex
				if (modelEditStyle == 1) {
					getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);

				}
				//nếu ở chế độ chọn face
				else if (modelEditStyle == 3) {
					//kiểm tra xem các mặt được chọn bằng vùng chọn
					getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
				areaChoice.isChoice = true;
			}
					break;
					//chế độ dịch chuyển,scale hoặc chỉnh sửa thuộc tính hình(hiện mũi tên và quad)
			case 3:
			case 5:
			case 6: {
				checkIsChoiceArrow(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
				checkIsChoiceQuad(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
			}
					break;
					//chế độ xoay hình
			case 4: {
				checkIsChoiceCircleRotate(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
			}
					break;
					//chế độ thêm chuỗi vertex
			case 7: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì thêm 1 vertex vào điểm nhấp chuột
				if (item.object<10) {
					addVertexInObjectChoice(item, x, yPosition);
				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta thêm 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ vẽ 1 day vertex dọc,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ vẽ 1 dãy nằm ngang)
				//khi nhấn vào và xác định được các vertex thì cho phép kéo để dịch chuyển các vertex
				//khi thả chuột ra mới thêm vào
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToCreatRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrixImage2, projectMatrixImage2, viewportImage2,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionAddRowOrColumn,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
					//chế độ xóa chuỗi vertex
			case 8: {
				itemChoice item = itemsChoice.at(0);
				//nếu đang là hình vẽ bằng cách thêm từng vertex thì xóa 1 vertex ở điểm nhấp chuột
				if (item.object<10) {

				}
				//nếu đang là hình vẽ bằng cách kéo thả thì ta xóa 1 dãy vertex
				//bằng cách nhấn vào cạnh của hình đó(nếu nhấn vào cạch nằm ngang thì thì sẽ xóa 1 day vertex ngang,nếu nhấn
				// vào 1 cạnh nằm dọc thì sẽ xóa 1 dãy nằm dọc)
				//khi nhấn vào và xác định được các vertex sẽ vẽ đen cả dãy vertex đó,
				//khi thả chuột ra mới xóa dãy vertex đó
				else {
					//khi nhấn chuột ta xem điểm được chọn nằm giữa các điểm nào
					checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, false,
						modelMatrixImage2, projectMatrixImage2, viewportImage2,
						vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
						itemTextureWindow, positionDeleteRowOrColumn,
						symmetryVertices, symmetryObjects,
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
						objectCustom0Array);
				}
			}
					break;
			default:
				break;
			}
		}
		else if (state == GLUT_UP) {
			//kiểm tra xem có dịch chuyển,xoay hay scale không,nếu có thì lưu vào tệp txt
			if (move_X != 0.0 || move_Y != 0.0 || move_Z != 0.0
				|| rotate_X != 0.0 || rotate_Y != 0.0 || rotate_Z != 0.0
				|| scale_X != 0.0 || scale_Y != 0.0 || scale_Z != 0.0) {

				SaveInformationTransform();
			}

			//khi thả chuột ra nếu ở chế độ chọn mặt thì lấy ra các vertex gắn với các mặt được chọn
			if (modelEditStyle == 3 && !itemsChoice.empty() && !positionFacesChoice.empty()) {
				getVertexByFace(positionVerticesChoice, positionFacesChoice, itemsChoice.at(0), triaStripArray, triaFanArray, sphereArray,
					cubeArray, cubeRoundArray, coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray,
					objectCustom0Array);
			}
			//nếu có di chuyển chuột và đang ở chế độ chọn thì mới chọn bằng vùng chọn
			else if (x != mouseDownX && yPosition != mouseDownY && mouseModel == 0 
				&& (modelEditStyle == 0 || modelEditStyle == 1) && !isChoiceVertexNow) {
				checkIdsChoiceByRectangle(x, yPosition, false, 0, modelMatrixImage2, projectMatrixImage2, viewportImage2);
			}
			//nếu đang ở chế độ thêm hàng vertex thì thêm vào
			else if (mouseModel == 7 && (positionAddRowOrColumn.positionRow != -1 ||
				positionAddRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

				addRowVertexInObject(itemsChoice, positionAddRowOrColumn,
					positionChoiceRowOrColumn, positionVerticesChoice,
					vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
					symmetryVertices, symmetryObjects,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);

				//nếu dùng cho xóa hay thêm 1 số vertex thì dùng hàm riêng sẽ nhanh hơn và dễ hơn
				SaveVertexCreatOrDelete(6);
			}
			//nếu đang ở chế độ xóa hàng vertex thì xóa
			else if (mouseModel == 8 && (positionDeleteRowOrColumn.positionRow != -1 ||
				positionDeleteRowOrColumn.positionColumn != -1) && !vertexToDrawRectangle.empty()) {

				//đầu tiên đặt vị trí chọn là vị trí xóa,và lấy ra vị trí các vertex chuân bị xóa
				positionChoiceRowOrColumn.clear();
				positionChoiceRowOrColumn.push_back({ positionDeleteRowOrColumn.positionRow ,
					positionDeleteRowOrColumn.positionColumn, positionDeleteRowOrColumn.positionColumnOpposite });

				getVerticesFromRowOrColumn(itemsChoice.at(0),
					positionChoiceRowOrColumn, positionVerticesChoice,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);

				SaveVertexCreatOrDelete(7);
				//sau khi lấy xong thì xóa hết do vị trí đó đã bị xóa là không chọn gì cả
				positionChoiceRowOrColumn.clear();

				deleteRowVertexInObject(itemsChoice, positionDeleteRowOrColumn,
					vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
					symmetryVertices, symmetryObjects,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
					objectCustom0Array);
			}

			//đặt lại đang không ở trong quá trình chọn bằng vùng chọn
			areaChoice.isChoice = false;
			//xóa hết các thông tin vẽ vẽ hình chữ nhật chọn hay hình chữ nhật thêm vertex
			vertexToDrawRectangle.clear();
			//đặt vị trí để thêm dãy vertex vào sau trở thành -1 để k0 làm gì cả
			positionAddRowOrColumn.positionRow = -1;
			positionAddRowOrColumn.positionColumn = -1;
			positionAddRowOrColumn.positionColumnOpposite = -1;
			//đặt vị trí để xóa dãy vertex trở về -1 để không làm gì cả
			positionDeleteRowOrColumn.positionRow = -1;
			positionDeleteRowOrColumn.positionColumn = -1;
			positionDeleteRowOrColumn.positionColumnOpposite = -1;
			//khi thả chuột ra thì xóa hết thông tin vầ vertex cũng như mũi tên đang chọn
			whichArrowChoice = -1;
			whichQuadChoice = -1;
			//khi thả chuột xóa hết thông tin về các giá trị xoay vật
			itemRotate.firstItemChoice = -1;
			itemRotate.itemChoiceNow = -1;
			itemRotate.whichCircleChoice = -1;
			itemRotate.isRotateLikeClockwise = true;

			offsetOfVertexInfor = 0;
			//đặt lại vị trí bắt đầu chạm
			lastTouchX = -1;
			lastTouchY = -1;
			mouseDownX = -1;
			mouseDownY = -1;
		}
		redisplay_all();
	}
};
//theo dõi sự di chuyển của chuột(khi chuột được nhấn)
void screen2_mouseMoveWhenMouseDown(int x, int y)
{
	int yPosition = screen2D_height - y;

	//kiểm tra xem ở chế độ nào để chỉnh tương ứng
	switch (mouseModel)
	{
	case 0: {
		if (modelEditStyle == 0 || modelEditStyle == 1) {
			if (mouseDownX != -1) {
				double mouseX, mouseY, mouseZ;
				//xóa các giá trị cũ trước khi thêm lại
				vertexToDrawRectangle.clear();

				gluUnProject((GLdouble)mouseDownX, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrixImage2, projectMatrixImage2, viewportImage2,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)mouseDownX, (GLdouble)yPosition, (GLdouble)0.1, modelMatrixImage2, projectMatrixImage2, viewportImage2,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)0.1, modelMatrixImage2, projectMatrixImage2, viewportImage2,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
				gluUnProject((GLdouble)x, (GLdouble)mouseDownY, (GLdouble)0.1, modelMatrixImage2, projectMatrixImage2, viewportImage2,
					&mouseX, &mouseY, &mouseZ);
				vertexToDrawRectangle.push_back({ (float)mouseX,(float)mouseY,(float)mouseZ });
			}
		}
		else if (modelEditStyle == 3) {
			checkToChoiceFaceInObject(itemsChoice.at(0), x, yPosition, positionFacesChoice,
				modelMatrixImage2, projectMatrixImage2, viewportImage2,
				triaStripArray, triaFanArray, sphereArray, cubeArray, coneArray,
				cylinderArray, emptyCylinderArray, torusArray,
				objectCustom0Array);
		}
	}
			break;
	case 1: {

	}
			break;
	case 2: {
		if (!itemsChoice.empty()) {
			//đặt lại vị trí tâm chọn
			GLdouble xDown = 0.0, yDown = 0.0, zDown = 0.0;
			float z;
			//lấy ra giá trị của mặt phẳng chứa hình tròn
			glReadPixels(x, yPosition, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &z);
			gluUnProject((GLdouble)x, (GLdouble)yPosition, (GLdouble)z, modelMatrixImage2, projectMatrixImage2, viewportImage2, &xDown, &yDown, &zDown);
			areaChoice.centerArea = { (float)xDown,(float)yDown,(float)zDown };

			if (modelEditStyle == 1) {
				getVertexByArea(itemsChoice.at(0), areaChoice, positionVerticesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
			else if (modelEditStyle == 3) {
				//kiểm tra xem các mặt được chọn bằng vùng chọn
				getFaceByArea(itemsChoice.at(0), areaChoice, positionFacesChoice,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
					objectCustom0Array);
			}
		}
	}
			break;
	case 3:
	case 5: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
		}
		//nếu chọn trúng quad
		else if (whichQuadChoice != -1) {
			changeValueByQuad(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
		}
	}
			break;
	case 4: {
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
		}
	}
			break;
			//chế độ chỉnh sửa thuộc tính hình
	case 6: {
		//nếu chọn trúng mũi tên
		if (whichArrowChoice != -1) {
			changeValueByArrow(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
		}
		//nếu chọn trúng hình tròn xoay
		if (itemRotate.whichCircleChoice != -1) {
			changeValueByCircle(x, yPosition, modelMatrixImage2, projectMatrixImage2, viewportImage2);
		}
	}
			break;
	case 7: {
		//nếu đang ở chế đọ thêm hàng vertex thì diều chỉnh vị trí thêm vertex
		checkToCreatRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrixImage2, projectMatrixImage2, viewportImage2,
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionAddRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	case 8: {
		checkToDeleteRowVertexInObject(itemsChoice, x, yPosition, true,
			modelMatrixImage2, projectMatrixImage2, viewportImage2,
			vertexToDrawRectangle, vertexToDrawRectangleSymmetry,
			itemTextureWindow, positionDeleteRowOrColumn,
			symmetryVertices, symmetryObjects,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
			objectCustom0Array);
	}
			break;
	default:
		break;
	}

	lastTouchX = x;
	lastTouchY = y;
	redisplay_screens();
}
//bắt sự kiện cuộn nút giữa của chuột
void screen2_mouseWheel(int button, int dir, int x, int y)
{
	//dir =1 là cuộn vào,=-1 là cuộn ra
	zoomCameraImage2 += dir;
	if (zoomCameraImage2 > 0.0) {
		zoomCameraImage2 = 0.0;
	}

	glutPostRedisplay();
	return;
}
void screen2_keyboard(unsigned char key, int x, int y) {

	//kiểm tra xem có chọn trúng key nào ở các key dùng chung cho toàn window không
	keyboardForApp(key);

	/*từ số 0 đến 9 có đại diện là 48 đến 57
	dấu . là 46*/
	//key==8 phim xoa
	//key=13 phim enter
	//key= 127 là delete
	//các hàm dịch chuyển cảnh
	switch (key)
	{
	case 'W':
	case 'w':
		translateCameraYImage2 -= 0.4f;
		
		//load lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		translateCameraYImage2 += 0.4f;

		//load lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		translateCameraXImage2 += 0.4f;

		//load lại màn hình hiện tại
		glutPostRedisplay();
		break;
	case 'D':
	case 'd':
		translateCameraXImage2 -= 0.4f;

		//load lại màn hình hiện tại
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_left, window_top);

	//Tạo cửa sổ để hiển thị hình
	window = glutCreateWindow("3D app");
	//cách lấy HWND của màn hình hiện tại HWND hThisWnd = GetForegroundWindow();
	//hàm này sẽ tạo full màn hình
	//glutFullScreen();

	//ẩn thanh title bar(sẽ bị nhấp nháy ở screen do không load kịp)

	HWND hWnd = GetForegroundWindow();
	SetWindowLong(hWnd, GWL_STYLE, 0); //remove all window styles, check MSDN for details
	ShowWindow(hWnd, SW_SHOW);

	//lấy thông tin để chia sẻ kết cấu,danh sách hiển thị,... giữa các subWindow
	HGLRC glrc1 = wglGetCurrentContext();


	//hiện hộp thông báo với 2 nút Ok và cancel
	//MessageBox(hWnd, "message", "caption", MB_OKCANCEL);

	/*hàm này là ẩn luôn window
	glutHideWindow()
	sẽ hiện của sổ bị ẩn
	glutShowWindow (void);*/

	/*hàm thay đổi tiêu đè và icon của của sổ
	void glutSetWindowTitle (tên char *);
	void glutSetIconTitle (tên char *);
	*/

	//ilInit() là hàm khởi tạo của thư viện tải ảnh il
	ilInit();
	//hàm khởi tạo các giá trị mặc định và load các item đã lưu
	init_window();
	glutDisplayFunc(window_display);
	glutReshapeFunc(window_reshape);


	//tạo cửa sổ con
	screen = glutCreateSubWindow(window, GAP, GAP, screen_width, screen_height);
	//chia sẻ kết cấu,dổ bóng,danh sách hiển thị,... giữa các subWindow
	HGLRC glrc2 = wglGetCurrentContext();
	wglShareLists(glrc1, glrc2);

	init_screen();
	glutDisplayFunc(screen_display);
	glutReshapeFunc(screen_reshape);
	glutMouseWheelFunc(screen_mouseWheel);
	glutMouseFunc(screen_mouse);
	glutMotionFunc(screen_mouseMoveWhenMouseDown);
	glutKeyboardFunc(screen_keyboard);
	//bắt sự kiện nhấn phím mũi tên
	glutSpecialFunc(ClickKeyArrowOnKeyboard);
	//sẽ lấy vị trí chuột khi k0 có nút chuột nào được nhấn
	glutPassiveMotionFunc(mouseMoveNotClick); 
	/*
	glutPassiveMotionFunc() sẽ lấy vị trí chuột khi k0 có nút chuột nào được nhấn còn
	glutMotionFunc() sẽ lấy vị trí chuột khi có 1 nút của chuột được nhấn
	*/

	screen1 = glutCreateSubWindow(window, GAP, GAP, screen2D_width, screen2D_height);
	//chia sẻ kết cấu,dổ bóng,danh sách hiển thị,... giữa các subWindow
	HGLRC glrc3 = wglGetCurrentContext();
	wglShareLists(glrc1, glrc3);

	init_screen1();
	glutDisplayFunc(screen1_display);
	glutReshapeFunc(screen1_reshape);
	glutMouseFunc(screen1_mouse);
	glutMotionFunc(screen1_mouseMoveWhenMouseDown);
	glutMouseWheelFunc(screen1_mouseWheel);
	glutKeyboardFunc(screen1_keyboard);
	//bắt sự kiện nhấn phím mũi tên
	glutSpecialFunc(ClickKeyArrowOnKeyboard);

	screen2 = glutCreateSubWindow(window, GAP, GAP, screen2D_width, screen2D_height);
	//chia sẻ kết cấu,dổ bóng,danh sách hiển thị,... giữa các subWindow
	HGLRC glrc4 = wglGetCurrentContext();
	wglShareLists(glrc1, glrc4);

	init_screen2();
	glutDisplayFunc(screen2_display);
	glutReshapeFunc(screen2_reshape);
	glutMouseFunc(screen2_mouse);
	glutMotionFunc(screen2_mouseMoveWhenMouseDown);
	glutMouseWheelFunc(screen2_mouseWheel);
	glutKeyboardFunc(screen2_keyboard);
	//bắt sự kiện nhấn phím mũi tên
	glutSpecialFunc(ClickKeyArrowOnKeyboard);
	
	//tạo subwindow để hiện các menu
	subwindow = glutCreateSubWindow(window, GAP, GAP, window_width, window_height);
	HGLRC glrc5 = wglGetCurrentContext();
	wglShareLists(glrc1, glrc5);

	init_subwindow();
	glutDisplayFunc(subwindow_display);
	glutReshapeFunc(subwindow_reshape);
	glutMouseFunc(subwindow_mouse);
	glutMotionFunc(subwindow_mouseMoveWhenMouseDown);
	glutKeyboardFunc(subwindow_keyboard);
	//bắt sự kiện nhấn phím mũi tên
	glutSpecialFunc(ClickKeyArrowOnKeyboard);
	glutPassiveMotionFunc(subwindow_mouseMoveWhenMouseUp);


	glutMainLoop();
	return 0;
}