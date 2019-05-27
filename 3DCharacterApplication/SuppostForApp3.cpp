#include "SuppostForApp3.h"


//các hàm xử lý cho menu app

//hàm đặt kết cấu cho các vật được chọn
void setTextureForObjectChoice(int whichTexture, vector<itemChoice> itemsChoice,
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
			TriangleAttribute *tria = triangleArray.at(item.positionOfChoice);
			tria->idTexture = whichTexture;
		}
		break;
		case 4:
		{
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			triaStrip->idTexture = whichTexture;
		}
		break;
		case 5:
		{
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			triaFan->idTexture = whichTexture;
		}
		break;
		case 10:
		{
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			sphere->idTexture = whichTexture;
		}
		break;
		case 11:
		{
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			cube->idTexture = whichTexture;
		}
		break;
		case 12:
		{
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			cube->idTexture = whichTexture;
		}
		break;
		case 13:
		{
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			cone->idTexture = whichTexture;
		}
		break;
		case 14:
		{
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			cylinder->idTexture = whichTexture;
		}
		break;
		case 15:
		{
			PyramidAttribute *pyr = pyrArray.at(item.positionOfChoice);
			pyr->idTexture = whichTexture;
		}
		break;
		case 16:
		{
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			cylinder->idTexture = whichTexture;
		}
		break;
		case 17:
		{
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			torus->idTexture = whichTexture;
		}
		break;
		case 18:
		{
			PictureAttribute *picture = pictureArray.at(item.positionOfChoice);
			picture->idTexture = whichTexture;
		}
		break;
		case 19:
		{
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			object->idTexture = whichTexture;
		}
		break;
		default:
			break;
		}
	}
}

//hàm kiểm tra xem có các lỗi nào trước khi bo tròn
//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo,
//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
int getErrorToRound(point v0, point v1, point v2, float radiusRound) {
	//lấy vector cho 2 đường thẳng
	point v0v1 = { v1.x - v0.x,v1.y - v0.y,v1.z - v0.z },
		v1v2 = { v2.x - v1.x,v2.y - v1.y,v2.z - v1.z };
	float distanceV0V1 = 0.0, distanceV1V2 = 0.0, degree = 0.0, multiplyTwoVector = 0.0;

	distanceV0V1 = sqrt(pow(v0v1.x, 2) + pow(v0v1.y, 2) + pow(v0v1.z, 2));
	if (isnan(distanceV0V1))
		distanceV0V1 = 0.0;

	distanceV1V2 = sqrt(pow(v1v2.x, 2) + pow(v1v2.y, 2) + pow(v1v2.z, 2));
	if (isnan(distanceV1V2))
		distanceV1V2 = 0.0;

	multiplyTwoVector = v0v1.x*v1v2.x + v0v1.y*v1v2.y + v0v1.z*v1v2.z;
	if (isnan(multiplyTwoVector))
		multiplyTwoVector = 0.0;

	//đối vơi các khoảng cách này phải cho phép sai số 0.001 vì chắc chắn các phép tính toán sẽ có 1 phép bị lệch dẫn đên sai toàn bộ
	if (distanceV0V1 == 0.0 && distanceV1V2 == 0.0) {
		//nếu cả 2 khoảng cách =0 nghĩa là bị chồng chéo cả 3 điểm
		return 3;
	}
	else if (distanceV0V1 == 0.0) {
		//bị chồng chéo 2 điểm đầu
		return 4;
	}
	else if (distanceV1V2 == 0.0) {
		//bị chồng chéo 2 điểm sau
		return 5;
	}
	//cho phép sai số nhỏ để 2 cạnh ngoài cùng kề nhau của 2 góc bo liền nhau không trùng vào nhau
	else if ((distanceV0V1 / 2 - 0.0001) > radiusRound && (distanceV1V2 / 2 - 0.0001) > radiusRound) {
		//tính ra tâm của 3 đường
		degree = (acos(multiplyTwoVector / (distanceV0V1*distanceV1V2)))*(180 / M_PI);
		if (isnan(degree))
			degree = 0.0;

		//đây đáng ra là degree == 0(tương đương với bằng 180 độ) nhưng phải cho phép sai số 0.00 bao nhiêu đó
		//hơn nữa với góc quá tù thì cũng không cần bo
		if (degree < 1.0) {
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		//tính ra tâm của 3 đường
		//nếu bỏ trong khối try catch sẽ tính toán chuẩn xác hơn
		degree = (acos(multiplyTwoVector / (distanceV0V1*distanceV1V2)))*(180 / M_PI);
		if (isnan(degree))
			degree = 0.0;

		//đây đáng ra là degree == 0(tương đương với bằng 180 độ) nhưng phải cho phép sai số 0.00 bao nhiêu đó
		//hơn nữa với góc quá tù thì cũng không cần bo
		if (degree < 1.0) {
			//mã lỗi vừ thiếu bán kính bo tròn,vừa có góc bo bằng 180 độ
			return 6;
		}
		else
		{
			return 2;
		}
	}
}
//hàm bo góc
void roundEdge(point A, point B, point C, float radiusRound, int numberVertexAdd, point *arrayVertex, int errorRound, int errorChange) {
	//mảng arrayVertex chứa các vertex ở giữa A và C(v0 và v1 ở trong đó và có thể có B ở trong đó nếu số vertex cần tìm là lẻ)
	//biến errorRound chứa các giá trị thông báo mã lỗi để có biện pháp bo phù hợp(0 là bình thường,1 là góc bằng 180,2 là không đủ khoảng cách bo,
	//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
	//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
	point v0, v1, H;
	float distanceBH = 0.0, distancev0H = 0.0;
	int halfNumberVertex = numberVertexAdd / 2, halfVertexNeedFind = halfNumberVertex - 1;
	//nếu lỗi errorChange =3 nghĩa là bị chồng điểm và không thể tìm điểm thay thế
	//thì chỉ cần đặt tất cả các điểm tại điểm B là xong
	if (errorChange == 3) {
		for (int i = 0; i < numberVertexAdd; i++) {
			arrayVertex[i] = B;
		}
	}
	else
	{
		//nếu lỗi là 2 hoặc 6 thì xác định lại bán kính bo tròn(bằng một nửa chiều dài của cạnh ngắn nhất trong 2 cạnh 2 bên góc)
		if (errorRound == 2 || errorChange == 2 || errorRound == 6 || errorChange == 6) {
			//nếu tính khoảng cách bị lỗi thì nghĩa là gần bằng 0 thì cho nó bằng 0 luôn
			float distanceBA = sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2)),
				distanceBC = sqrt(pow(C.x - B.x, 2) + pow(C.y - B.y, 2) + pow(C.z - B.z, 2));
			//kiểm tra xem khoảng cách nào ngắn nhất thì lấy gần một nửa khoảng cách đó làm bán kính bo tròn
			//(nếu lấy 1 nửa thì sẽ có 2 đỉnh kề nhau của 2 góc cần bo kiên tiếp trùng với nhau)
			radiusRound = distanceBA < distanceBC ? distanceBA * 0.45 : distanceBC * 0.45;
			if (isnan(radiusRound)) {
				//nếu tính giá trị bị lỗi thì nghĩa là khoảng cách quá nhỏ đặt về 0 luôn
				//và đặt tất cả các điểm cần tìm nằm đúng tại vị trí B
				for (int i = 0; i < numberVertexAdd; i++) {
					arrayVertex[i] = B;
				}
				//và dừng tìm các điểm luôn
				return;
			}
		}
		//tính ra v0,v1
		normalizeWithRadius(B, A, v0, radiusRound);
		normalizeWithRadius(B, C, v1, radiusRound);

		//nếu mã lỗi =1 hoặc 6 nghĩa là góc bằng 180 độ thì không cần tính điểm H cũng như bán kính vòng tròn bo
		if (errorRound != 1 && errorChange != 1 && errorRound != 6 && errorChange != 6) {
			//tính ra điểm H nằm giữa v0,v1(nếu bị lỗi gì thì đặt H=v0)
			H = { (v0.x + v1.x) / 2,(v0.y + v1.y) / 2 ,(v0.z + v1.z) / 2 };
			if (isnan(H.x) || isnan(H.y) || isnan(H.z)) {
				H = v0;
			}

			//nếu các hàm tính toán này gây ra lỗi gì thì bỏ qua
			try
			{
				//tính khoảng cách BH và v0H
				distanceBH = sqrt(pow(H.x - B.x, 2) + pow(H.y - B.y, 2) + pow(H.z - B.z, 2));
				distancev0H = sqrt(pow(H.x - v0.x, 2) + pow(H.y - v0.y, 2) + pow(H.z - v0.z, 2));
				if (isnan(distancev0H) || isnan(distanceBH)) {
					throw 1;
				}
				//nếu khoảng cách BH lớn hơn hoặc bằng 2*v0H thì lấy H là tâm xoay luôn(bán kính là v0H)
				//nếu không thì phải điều chỉnh vị trí của H sao cho BH = 2v0H
				//vị trí bo đẹp nhất là khi BH<=2v0H(tuy nhiên do tính toán bị sai số nhỏ nên phải thêm giá trị cho phép sai số vào)

				//phải đặt điều kiện này vì nếu góc nhỏ hơn góc đẹp nhất thì càng nhỏ càng khó tìm ra điểm bo đẹp(BH=2v0H) vậy nên cứ
				//để yên ở vị trí đó là bo đẹp rồi
				if (distanceBH < 2 * distancev0H + 0.0001) {
					//tính vector BH để dùng xác định đường thẳng đi qua B có vector chỉ phương BH
					point BH = { H.x - B.x,H.y - B.y ,H.z - B.z };
					float t = (-pow(B.x - v0.x, 2) - pow(B.y - v0.y, 2) - pow(B.z - v0.z, 2)) /
						(2 * BH.x*(B.x - v0.x) + 2 * BH.y*(B.y - v0.y) + 2 * BH.z*(B.z - v0.z) + pow(BH.x, 2) + pow(BH.y, 2) + pow(BH.z, 2));
					H = { B.x + BH.x*t,B.y + BH.y*t ,B.z + BH.z*t };
					if (isnan(H.x) || isnan(H.y) || isnan(H.z)) {
						H = v0;
					}
					//tính lại bán kính khi H thay đổi
					distancev0H = sqrt(pow(H.x - v0.x, 2) + pow(H.y - v0.y, 2) + pow(H.z - v0.z, 2));

					if (isnan(distancev0H)) {
						throw 1;
					}
				}
			}
			catch (...)
			{
				distancev0H = 0.0;
			}
		}

		//nếu tên lỗi ban đầu là 4 hoặc 5 nghĩa là bị trùng 2 vertex trước hoặc 2 vertex sau thì phải đặt cụm bị trùng vào vị trí B
		//mã lỗi 4 là bị trùng 2 điểm đầu
		//nếu tên lỗi là 3 nghĩa là bị trùng cả trước và sau(2 vertex A,C đều là vertex tìm thay thế để bo tròn)
		if (errorRound == 3) {
			//do bị trùng cả 2 bên nên đặt vertex ở tại điểm chính giữa
			for (int i = 0; i < numberVertexAdd; i++) {
				arrayVertex[i] = B;
			}
		}
		else if (errorRound == 4) {
			//do bị trùng 2 đỉnh đầu nên đặt tất cả các đỉnh bo tròn từ đầu đến B đều tại B hết
			for (int i = 0; i < halfNumberVertex; i++) {
				arrayVertex[i] = B;
			}
			//nếu số điểm là lẻ thì thêm điểm B vào
			if (numberVertexAdd % 2 != 0) {
				arrayVertex[halfNumberVertex] = B;
				findPointsBetweenTwoPoint(B, v1, halfVertexNeedFind, arrayVertex, halfNumberVertex + 1);
			}
			else
			{
				findPointsBetweenTwoPoint(B, v1, halfVertexNeedFind, arrayVertex, halfNumberVertex);
			}
			//cuối cùng thêm diểm v1 vào
			arrayVertex[numberVertexAdd - 1] = v1;
		}
		//mã lỗi 5 là bị trùng 2 điểm sau
		else if (errorRound == 5) {
			//đầu tiên thêm diểm v0 vào
			arrayVertex[0] = v0;
			//sau khi tính ra được H thì tính ra các điểm và cách H một khoảng bằng khoảng cách v0H
			findPointsBetweenTwoPoint(v0, B, halfVertexNeedFind, arrayVertex, 1);
			//nếu số điểm là lẻ thì thêm điểm B vào
			if (numberVertexAdd % 2 != 0) {
				arrayVertex[halfNumberVertex] = B;
				//do bị trùng 2 điểm sau nên tât cả các điểm từ B trở về sau đều đặt bằng B hết
				for (int i = halfNumberVertex + 1; i<numberVertexAdd; i++) {
					arrayVertex[i] = B;
				}
			}
			else
			{
				//do bị trùng 2 điểm sau nên tât cả các điểm từ B trở về sau đều đặt bằng B hết
				for (int i = halfNumberVertex; i<numberVertexAdd; i++) {
					arrayVertex[i] = B;
				}
			}

		}
		else
		{
			//đầu tiên thêm diểm v0 vào
			arrayVertex[0] = v0;
			//sau khi tính ra được H thì tính ra các điểm và cách H một khoảng bằng khoảng cách v0H
			findPointsBetweenTwoPoint(v0, B, halfVertexNeedFind, arrayVertex, 1);
			//nếu số điểm là lẻ thì thêm điểm B vào
			if (numberVertexAdd % 2 != 0) {
				arrayVertex[halfNumberVertex] = B;
				findPointsBetweenTwoPoint(B, v1, halfVertexNeedFind, arrayVertex, halfNumberVertex + 1);
			}
			else
			{
				findPointsBetweenTwoPoint(B, v1, halfVertexNeedFind, arrayVertex, halfNumberVertex);
			}
			//cuối cùng thêm diểm v1 vào
			arrayVertex[numberVertexAdd - 1] = v1;
		}

		//nếu mã lỗi =1 nghia là góc bằng 180 độ thì không thể,cũng như không cần bo
		if (errorRound != 1 && errorChange != 1 && errorRound != 6 && errorChange != 6) {
			for (int i = 0; i < numberVertexAdd; i++) {
				normalizeWithRadius(H, arrayVertex[i], distancev0H);
			}
		}
	}
}

//hàm bo tròn các góc cạnh của triangle strip
void roundEdgeTriaStrip(TriangleStripAttribute *triaStrip, float radiusRound, int numberVertexAdd) {
	//đầu tiên phải xóa hêt vertexArrayRound
	triaStrip->vertexArrayRound.clear();

	//phải kiểm tra từng cặp cạnh nối nhau để xem nếu góc giữa chúng nhỏ hơn góc quy định thì 
	//bắt đầu thêm các điểm để bo tròn
	int numberVertex = triaStrip->vertexArray.size(),
		numberCorner = (numberVertex - 1) / 2 - 1, offset;
	//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo,
	//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
	//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
	int error1 = 2, error2 = 2;
	//nếu số vertex là chẵn nghĩa là phần cuối cũng có 1 cặp cạnh,nếu là lẻ thì chỉ có 1 cạnh
	bool isTwiceLastEdge = numberVertex % 2 == 0;
	point *arrayVertex0, *arrayVertex1;
	arrayVertex0 = new point[numberVertexAdd];
	arrayVertex1 = new point[numberVertexAdd];

	//bo tròn 2 góc ở đầu(nếu có đỉnh thứ 3(tức là có ít nhất 4 đỉnh))
	error1 = getErrorToRound(triaStrip->vertexArray.at(1), triaStrip->vertexArray.at(0),
		triaStrip->vertexArray.at(2), radiusRound);
	if (numberVertex >= 4) {
		error2 = getErrorToRound(triaStrip->vertexArray.at(0), triaStrip->vertexArray.at(1),
			triaStrip->vertexArray.at(3), radiusRound);
	}
	else
	{
		//đặt mã lỗi 5 là không có góc,cạnh để bo
		error2 = 5;
	}

	//nếu 1 trong 2 góc cần bo tròn thì bo tròn
	if ((error1 == 0 || error2 == 0) && error2 != 5) {
		//tính toán bo góc 1(phía dưới)
		roundEdge(triaStrip->vertexArray.at(1), triaStrip->vertexArray.at(0), triaStrip->vertexArray.at(2),
			radiusRound, numberVertexAdd, arrayVertex0, error1, -1);
		//tính toán bo góc 2(phía trên)
		roundEdge(triaStrip->vertexArray.at(0), triaStrip->vertexArray.at(1), triaStrip->vertexArray.at(3),
			radiusRound, numberVertexAdd, arrayVertex1, error2, -1);


		for (int j = 0; j < numberVertexAdd; j++) {
			//phải thêm thao kiểu ziczac do triaStrip là kiểu ziczac(và từ sau ra trước)
			triaStrip->vertexArrayRound.push_back(arrayVertex0[j]);
			triaStrip->vertexArrayRound.push_back(arrayVertex1[j]);
		}
	}
	else
	{
		//thêm vào 2 điểm đầu 
		triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(0));
		triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(1));
	}

	//bo tròn các góc ở giữa
	for (int i = 0; i < numberCorner; i++) {
		offset = i * 2;
		//kiểm tra xem các cạnh nối bằng các đỉnh chẵn xem có cần bo không
		error1 = getErrorToRound(triaStrip->vertexArray.at(offset), triaStrip->vertexArray.at(offset + 2),
			triaStrip->vertexArray.at(offset + 4), radiusRound);
		if (i == numberCorner - 1) {
			//nếu là cặp cạnh cuối cùng thì kiểm tra xem chỉ có 1 cạnh hay là 1 cặp cạnh
			if (isTwiceLastEdge) {
				error2 = getErrorToRound(triaStrip->vertexArray.at(offset + 1), triaStrip->vertexArray.at(offset + 3),
					triaStrip->vertexArray.at(offset + 5), radiusRound);
			}
			else
			{
				//đặt mã lỗi 5 là không có góc,cạnh để bo
				error2 = 5;
			}
		}
		else
		{
			error2 = getErrorToRound(triaStrip->vertexArray.at(offset + 1), triaStrip->vertexArray.at(offset + 3),
				triaStrip->vertexArray.at(offset + 5), radiusRound);
		}

		//nếu 1 trong 2 góc cần bo tròn
		if ((error1 == 0 || error2 == 0) && error2 != 5) {
			//tính toán bo góc 1(phía dưới)
			roundEdge(triaStrip->vertexArray.at(offset), triaStrip->vertexArray.at(offset + 2), triaStrip->vertexArray.at(offset + 4),
				radiusRound, numberVertexAdd, arrayVertex0, error1, -1);
			//tính toán bo góc 2(phía trên)
			roundEdge(triaStrip->vertexArray.at(offset + 1), triaStrip->vertexArray.at(offset + 3), triaStrip->vertexArray.at(offset + 5),
				radiusRound, numberVertexAdd, arrayVertex1, error2, -1);


			for (int j = 0; j < numberVertexAdd; j++) {
				//phải thêm thao kiểu ziczac do triaStrip là kiểu ziczac(và từ sau ra trước)
				triaStrip->vertexArrayRound.push_back(arrayVertex0[j]);
				triaStrip->vertexArrayRound.push_back(arrayVertex1[j]);
			}
		}
		else
		{
			triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(offset + 2));
			triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(offset + 3));
		}
	}

	//bo tròn 2 góc ở cuối
	error1 = getErrorToRound(triaStrip->vertexArray.at(numberVertex - 4), triaStrip->vertexArray.at(numberVertex - 2),
		triaStrip->vertexArray.at(numberVertex - 1), radiusRound);
	if (isTwiceLastEdge) {
		error2 = getErrorToRound(triaStrip->vertexArray.at(numberVertex - 3), triaStrip->vertexArray.at(numberVertex - 1),
			triaStrip->vertexArray.at(numberVertex - 2), radiusRound);
	}
	else
	{
		//đặt mã lỗi 5 là không có góc,cạnh để bo
		error2 = 5;
	}


	//nếu 1 trong 2 góc cần bo tròn
	if ((error1 == 0 || error2 == 0) && error2 != 5) {
		//tính toán bo góc 1(phía dưới)
		roundEdge(triaStrip->vertexArray.at(numberVertex - 4), triaStrip->vertexArray.at(numberVertex - 2), triaStrip->vertexArray.at(numberVertex - 1),
			radiusRound, numberVertexAdd, arrayVertex0, error1, -1);
		//tính toán bo góc 2(phía trên)
		roundEdge(triaStrip->vertexArray.at(numberVertex - 3), triaStrip->vertexArray.at(numberVertex - 1), triaStrip->vertexArray.at(numberVertex - 2),
			radiusRound, numberVertexAdd, arrayVertex1, error2, -1);


		for (int j = 0; j < numberVertexAdd; j++) {
			//phải thêm thao kiểu ziczac do triaStrip là kiểu ziczac(và từ sau ra trước)
			triaStrip->vertexArrayRound.push_back(arrayVertex0[j]);
			triaStrip->vertexArrayRound.push_back(arrayVertex1[j]);
		}
	}
	else
	{
		//thêm vào 2 điểm đầu 
		triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(numberVertex - 2));
		triaStrip->vertexArrayRound.push_back(triaStrip->vertexArray.at(numberVertex - 1));
	}

	//xóa mảng động sau khi đã dùng xong
	delete[] arrayVertex0;
	delete[] arrayVertex1;
	//tính toán normalVectorRound
	CaculatorNormalForTriangleStrip(triaStrip->vertexArrayRound, triaStrip->normalVectorRound);
}
//hàm bo góc cạnh dùng cho các hình có thuộc tính giống sphere như sphere,cone,cylinder
void roundEdgeForObject1(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//đầu tiên phải xóa hêt vertexArrayRound
	vertexArrayRound.clear();

	int maxItem = numberLongitude > numberLatitude ? numberLongitude : numberLatitude,
		maxVertexAdd = numberVertexAddHorizontal > numberVertexAddVertical ? numberVertexAddHorizontal : numberVertexAddVertical;
	//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo
	//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
	//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
	int *errorRound = new int[maxItem], errorChange
		, offset0, offset1, offset2, offsetChange1, offsetChange2;
	//nếu có 1 cái isCant ==true nghĩa là không thể bo,còn nếu nó bằng false và chỉ cần 1 cái isShould ==true thì bo tròn
	bool isShould = false;
	int halfLogitude = numberLongitude / 2;
	point **arrayVertex;
	arrayVertex = new point*[maxItem];
	for (int i = 0; i < maxItem; i++) {
		arrayVertex[i] = new point[maxVertexAdd];
	}

	//đầu tiên đặt numberLongitudeRound vầ numberLatitudeRound và vertexArrayRound như là của vertexArray,numberLongitude và numberLatitude
	numberLatitudeRound = numberLatitude;
	numberLongitudeRound = numberLongitude;
	vertexArrayRound = vertexArray;

	//sau đó kiểm tra theo chiều dọc trước xem có cần bo góc không

	for (int i = numberLatitude - 3; i >= 0; i--) {
		//mối lần kiểm tra cùng một vị trí ở trên 3 hàng liên tục xem có cần bo góc không
		offset0 = i*numberLongitude;
		offset1 = (i + 1)*numberLongitude;
		offset2 = (i + 2)*numberLongitude;
		isShould = false;
		for (int k = 0; k < numberLongitude; k++) {
			//lấy mã lỗi
			errorRound[k] = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
				vertexArray.at(offset2 + k), radiusRoundVertical);
			if (errorRound[k] != 1 && errorRound[k] != 6 && errorRound[k] != 3) {
				isShould = true;
			}
		}

		//kiểm tra xem có góc nào cần bo không và có góc nào không thể bo không
		if (isShould == true) {
			for (int k = 0; k < numberLongitude; k++) {
				//kiểm tra nếu mã lỗi bằng 4 hoặc 5 là bị trùng 2 trong 3 điểm,cần tìm điểm thay thế
				//nếu mà lỗi bằng 3 là bì trùng cả 3 điểm cần tìm 2 điểm thay thế nếu có
				if (errorRound[k] == 3) {
					errorChange = 3;
					offsetChange1 = offset0;
					offsetChange2 = offset2;
					for (int m = i - 1; m >= 0; m--) {
						//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						if (errorChange != 3) {
							offsetChange1 = m*numberLongitude;
							for (int n = i + 3; n < numberLatitude; n++) {
								errorChange = getErrorToRound(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k),
									vertexArray.at(n*numberLongitude + k), radiusRoundVertical);
								//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
								if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
									offsetChange2 = n*numberLongitude;
									break;
								}
								else
									errorChange = 3;
							}
						}
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 4) {
					//nếu bị trùng phía trước thì tìm các điểm trước đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset0;
					for (int m = i - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 5) {
					//nếu bị trùng phía sau thì tìm các điểm phía sau đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset2;
					for (int m = i + 3; m < numberLatitude; m++) {
						errorChange = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
							vertexArray.at(m*numberLongitude + k), radiusRoundVertical);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange1 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else
				{
					//nếu không bị trùng điểm thì bo góc như bình thường
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], -1);
				}
			}
			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//đầu tiên thay thế cụm vertex ở giữa bằng cụm arrayVertex cuối cùng để đỡ phải xóa
			for (int k = 0; k < numberLongitude; k++) {
				vertexArrayRound.at(offset1 + k) = arrayVertex[k][numberVertexAddVertical - 1];
			}

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int m = numberVertexAddVertical - 2; m >= 0; m--) {
				for (int k = numberLongitude - 1; k >= 0; k--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset1, arrayVertex[k][m]);
				}
			}

			//nhớ tăng numberLatitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
			numberLatitudeRound += (numberVertexAddVertical - 1);
		}
	}

	//kiểm tra xem tất các các góc ngang của tất cả các hàng xem có cần bo ít nhất 1 góc nào không(cũng như lấy mã lỗi của các góc)
	isShould = true;


	//********** Đối với các góc ngang thì để kiểm tra xem cần bo không thì phải kiểm tra hết toàn bộ các góc dọc theo góc đó để xem cần bo không
	//mà thường bề mặt ngang luôn cần bo nên việc này hơi tốn và thừa,để bữa sau xem sao


	//kiểm tra xem có góc nào cần bo không
	if (isShould == true) {
		//sau đó kiểm tra theo chiều ngang xem có cần bo góc không
		for (int i = numberLatitudeRound - 1; i >= 0; i--) {
			offset0 = i*numberLongitude;
			offset1 = (i + 1)*numberLongitude;
			//tính bo góc đỉnh cuối cùng,đầu tiên và thứ 2
			errorRound[0] = getErrorToRound(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
				vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
			if (errorRound[0] == 3) {
				//đây là góc đầu tiên nên bắt buộc phải bo tròn để các góc sau nếu bị trùng thì cũng dựa theo nó được
				errorChange = 3;
				offsetChange1 = offset1 - 1;
				offsetChange2 = offset0 + 1;
				for (int m = offset1 - 2; m > offset0 + 1; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					if (errorChange != 3) {
						offsetChange1 = m;
						for (int n = offset0 + 2; n < offset1 - 1; n++) {
							errorChange = getErrorToRound(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
								vertexArrayRound.at(n), radiusRoundHorizontal);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				//nếu cuối cùng lỗi vần bằng 3 thì đó là cụm điểm trùng nhau,đặt tất cả lại 1 chỗ
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offsetChange2), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[0], errorRound[0], errorChange);

			}
			else if (errorRound[0] == 4) {
				errorChange = 3;
				offsetChange1 = offset1 - 1;
				for (int m = offset1 - 2; m > offset0 + 1; m--) {
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], errorChange);
			}
			else if (errorRound[0] == 5) {
				errorChange = 3;
				offsetChange1 = offset0 + 1;
				for (int m = offset0 + 2; m < offset1 - 1; m++) {
					errorChange = getErrorToRound(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
						vertexArrayRound.at(m), radiusRoundHorizontal);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], errorChange);
			}
			else
			{
				roundEdge(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], -1);
			}

			//tính bo góc các góc trong
			for (int k = 0; k < numberLongitude - 2; k++) {
				errorRound[0] = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
					vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
				//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
				if (errorRound[0] == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[k + 1], 3, 3);
				}
				else if (errorRound[0] == 4) {
					errorChange = 3;
					offsetChange1 = k;
					for (int m = k - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + m), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + offsetChange1), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], errorRound[0], errorChange);
					}
				}
				else if (errorRound[0] == 5) {
					errorChange = 3;
					offsetChange1 = k + 2;
					for (int m = k + 3; m < numberLongitude; m++) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + m), radiusRoundHorizontal);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], errorRound[0], errorChange);
					}
				}
				else
				{
					roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
						vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[k + 1], errorRound[0], -1);
				}
			}
			//tính bo góc đỉnh gần cuối,đỉnh cuối cùng và đỉnh đầu tiên
			errorRound[0] = getErrorToRound(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
				vertexArrayRound.at(offset0), radiusRoundHorizontal);
			if (errorRound[0] == 3) {
				errorChange = 3;
				offsetChange1 = offset1 - 2;
				offsetChange2 = offset0;
				for (int m = offset1 - 3; m > offset0; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					if (errorChange != 3) {
						offsetChange1 = m;
						for (int n = offset0 + 1; n < offset1 - 3; n++) {
							errorChange = getErrorToRound(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
								vertexArrayRound.at(n), radiusRoundHorizontal);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset1 - 1),
					vertexArrayRound.at(offsetChange2), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
			}
			else if (errorRound[0] == 4) {
				errorChange = 3;
				offsetChange1 = offset1 - 2;
				for (int m = offset1 - 3; m > offset0; m--) {
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offset0), radiusRoundHorizontal);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				if (errorChange == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[numberLongitude - 2][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], 3, 3);
				}
				else {
					roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offset0), radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
				}
			}
			else if (errorRound[0] == 5) {
				errorChange = 3;
				offsetChange1 = offset0;
				for (int m = offset0 + 1; m < offset1 - 2; m++) {
					errorChange = getErrorToRound(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(m), radiusRoundHorizontal);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				if (errorChange == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[numberLongitude - 2][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], 3, 3);
				}
				else {
					roundEdge(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
				}
			}
			else
			{
				roundEdge(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
					vertexArrayRound.at(offset0), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[numberLongitude - 1], errorRound[0], -1);
			}


			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//xóa đi cụm vertex ta cần thay thế
			vertexArrayRound.erase(vertexArrayRound.begin() + offset0,
				vertexArrayRound.begin() + offset1);

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int k = numberLongitude - 1; k >= 0; k--) {
				for (int m = numberVertexAddHorizontal - 1; m >= 0; m--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset0, arrayVertex[k][m]);
				}
			}
		}
		//nhớ tăng numberLongitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
		numberLongitudeRound = numberVertexAddHorizontal*numberLongitude;
	}


	//xóa mảng động
	for (int i = 0; i < maxItem; i++)
	{
		delete[] arrayVertex[i];
	}
	delete[] arrayVertex;
	delete[] errorRound;
}
//hàm bo góc cạnh dùng cho các hình có thuộc tính giống empty cylinder(cụm đỉnh trên cùng và dưới cùng bị hở)
void roundEdgeForObject2(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//đầu tiên phải xóa hêt vertexArrayRound
	vertexArrayRound.clear();

	int maxItem = numberLongitude > numberLatitude ? numberLongitude : numberLatitude,
		maxVertexAdd = numberVertexAddHorizontal > numberVertexAddVertical ? numberVertexAddHorizontal : numberVertexAddVertical;
	//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo,
	//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
	//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
	int *errorRound = new int[maxItem], errorChange
		, offset0, offset1, offset2, offsetChange1, offsetChange2;
	//nếu có 1 cái isCant ==true nghĩa là không thể bo,còn nếu nó bằng false và chỉ cần 1 cái isShould ==true thì bo tròn
	bool isShould = false;


	point **arrayVertex;
	arrayVertex = new point*[maxItem];
	for (int i = 0; i < maxItem; i++) {
		arrayVertex[i] = new point[maxVertexAdd];
	}

	//đầu tiên đặt numberLongitudeRound vầ numberLatitudeRound và vertexArrayRound như là của vertexArray,numberLongitude và numberLatitude
	numberLatitudeRound = numberLatitude;
	numberLongitudeRound = numberLongitude;
	vertexArrayRound = vertexArray;

	//sau đó kiểm tra theo chiều dọc trước xem có cần bo góc không

	//bo góc đáy trên(chóp đáy hình trụ rỗng)
	isShould = false;
	offset0 = (numberLatitude - 1)*numberLongitude;
	offset1 = (numberLatitude - 2)*numberLongitude;
	//lấy mã lỗi của tất cả các góc đồng thời kiểm tra xem có ít nhất 1 góc nào cần bo không(góc khác 180 độ) thì mới bo
	for (int i = 0; i < numberLongitude; i++) {
		//lấy mã lỗi
		errorRound[i] = getErrorToRound(vertexArray.at(offset1 + i), vertexArray.at(offset0 + i),
			vertexArray.at(i), radiusRoundVertical);
		if (errorRound[i] != 1 && errorRound[i] != 6 && errorRound[i] != 3) {
			isShould = true;
		}
	}

	if (isShould) {
		for (int i = 0; i < numberLongitude; i++) {
			if (errorRound[i] == 3) {
				errorChange = 3;
				offsetChange1 = offset1;
				offsetChange2 = 0;
				for (int m = numberLatitude - 3; m >= 0; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + i), vertexArray.at(offset0 + i),
						vertexArray.at(i), radiusRoundVertical);
					if (errorChange != 3) {
						offsetChange1 = m*numberLongitude;
						for (int n = 1; n < numberLatitude - 1; n++) {
							errorChange = getErrorToRound(vertexArray.at(offsetChange1 + i), vertexArray.at(offset0 + i),
								vertexArray.at(n*numberLongitude + i), radiusRoundVertical);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n*numberLongitude;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				roundEdge(vertexArray.at(offsetChange1 + i), vertexArray.at(offset0 + i),
					vertexArray.at(offsetChange2 + i), radiusRoundVertical, numberVertexAddVertical, arrayVertex[i],
					errorRound[i], errorChange);
			}
			else if (errorRound[i] == 4) {
				errorChange = 3;
				offsetChange1 = offset1;
				for (int m = numberLatitude - 3; m >= 0; m--) {
					errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + i), vertexArray.at(offset0 + i),
						vertexArray.at(i), radiusRoundVertical);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m*numberLongitude;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArray.at(offsetChange1 + i), vertexArray.at(offset0 + i),
					vertexArray.at(i), radiusRoundVertical, numberVertexAddVertical, arrayVertex[i], errorRound[i], errorChange);
			}
			else if (errorRound[i] == 5) {
				errorChange = 3;
				offsetChange1 = 0;
				for (int m = 1; m < numberLatitude - 1; m++) {
					errorChange = getErrorToRound(vertexArray.at(offset1 + i), vertexArray.at(offset0 + i),
						vertexArray.at(m*numberLongitude + i), radiusRoundVertical);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m*numberLongitude;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArray.at(offset1 + i), vertexArray.at(offset0 + i),
					vertexArray.at(offsetChange1 + i), radiusRoundVertical, numberVertexAddVertical,
					arrayVertex[i], errorRound[i], errorChange);
			}
			else
			{
				roundEdge(vertexArray.at(offset1 + i), vertexArray.at(offset0 + i),
					vertexArray.at(i), radiusRoundVertical, numberVertexAddVertical, arrayVertex[i], errorRound[i], -1);
			}
		}

		//xóa đi cụm vertex ta cần thay thế
		vertexArrayRound.erase(vertexArrayRound.begin() + offset0,
			vertexArrayRound.begin() + (offset0 + numberLongitude));

		//thêm vào các dãy vertex các vertex cần thêm
		for (int i = numberVertexAddHorizontal - 1; i >= 0; i--) {
			for (int k = numberLongitude - 1; k >= 0; k--) {
				vertexArrayRound.insert(vertexArrayRound.begin() + offset0, arrayVertex[k][i]);
			}
		}
		numberLatitudeRound += (numberVertexAddVertical - 1);
	}

	//bo các góc ở giữa
	for (int i = numberLatitude - 3; i >= 0; i--) {
		//mối lần kiểm tra cùng một vị trí ở trên 3 hàng liên tục xem có cần bo góc không
		offset0 = i*numberLongitude;
		offset1 = (i + 1)*numberLongitude;
		offset2 = (i + 2)*numberLongitude;
		isShould = false;
		for (int k = 0; k < numberLongitude; k++) {
			//lấy mã lỗi
			errorRound[k] = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
				vertexArray.at(offset2 + k), radiusRoundVertical);
			if (errorRound[k] != 1 && errorRound[k] != 6 && errorRound[k] != 3) {
				isShould = true;
			}
		}

		//kiểm tra xem có góc nào cần bo không và có góc nào không thể bo không
		if (isShould == true) {
			for (int k = 0; k < numberLongitude; k++) {
				//kiểm tra nếu mã lỗi bằng 4 hoặc 5 là bị trùng 2 trong 3 điểm,cần tìm điểm thay thế
				//nếu mà lỗi bằng 3 là bì trùng cả 3 điểm cần tìm 2 điểm thay thế nếu có
				if (errorRound[k] == 3) {
					errorChange = 3;
					offsetChange1 = offset0;
					offsetChange2 = offset2;
					for (int m = i - 1; m >= 0; m--) {
						//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						if (errorChange != 3) {
							offsetChange1 = m*numberLongitude;
							for (int n = i + 3; n < numberLatitude; n++) {
								errorChange = getErrorToRound(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k),
									vertexArray.at(n*numberLongitude + k), radiusRoundVertical);
								//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
								if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
									offsetChange2 = n*numberLongitude;
									break;
								}
								else
									errorChange = 3;
							}
						}
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 4) {
					//nếu bị trùng phía trước thì tìm các điểm trước đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset0;
					for (int m = i - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 5) {
					//nếu bị trùng phía sau thì tìm các điểm phía sau đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset2;
					for (int m = i + 3; m < numberLatitude; m++) {
						errorChange = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
							vertexArray.at(m*numberLongitude + k), radiusRoundVertical);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange1 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else
				{
					//nếu không bị trùng điểm thì bo góc như bình thường
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], -1);
				}
			}
			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//đầu tiên thay thế cụm vertex ở giữa bằng cụm arrayVertex cuối cùng để đỡ phải xóa
			for (int k = 0; k < numberLongitude; k++) {
				vertexArrayRound.at(offset1 + k) = arrayVertex[k][numberVertexAddVertical - 1];
			}

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int m = numberVertexAddVertical - 2; m >= 0; m--) {
				for (int k = numberLongitude - 1; k >= 0; k--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset1, arrayVertex[k][m]);
				}
			}

			//nhớ tăng numberLatitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
			numberLatitudeRound += (numberVertexAddVertical - 1);
		}
	}

	//bo góc đáy dưới(chóp đáy hình cầu)
	offset0 = numberLongitude;
	offset1 = (numberLatitude - 1)*numberLongitude;
	isShould = false;
	for (int i = 0; i < numberLongitude; i++) {
		//lấy mã lỗi
		errorRound[i] = getErrorToRound(vertexArray.at(offset1 + i), vertexArray.at(i),
			vertexArray.at(offset0 + i), radiusRoundVertical);
		if (errorRound[i] != 1 && errorRound[i] != 6 && errorRound[i] != 3) {
			isShould = true;
		}
	}

	if (isShould) {
		for (int i = 0; i < numberLongitude; i++) {
			if (errorRound[i] == 3) {
				errorChange = 3;
				offsetChange1 = offset1;
				offsetChange2 = offset0;
				for (int m = numberLatitude - 2; m >= 0; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + i), vertexArray.at(offset0 + i),
						vertexArray.at(i), radiusRoundVertical);
					if (errorChange != 3) {
						offsetChange1 = m*numberLongitude;
						for (int n = 1; n < numberLatitude - 1; n++) {
							errorChange = getErrorToRound(vertexArray.at(offsetChange1 + i), vertexArray.at(offset0 + i),
								vertexArray.at(n*numberLongitude + i), radiusRoundVertical);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n*numberLongitude;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				roundEdge(vertexArray.at(offsetChange1 + i), vertexArray.at(i),
					vertexArray.at(offsetChange2 + i), radiusRoundVertical, numberVertexAddVertical,
					arrayVertex[i], errorRound[i], errorChange);
			}
			else if (errorRound[i] == 4) {
				errorChange = 3;
				offsetChange1 = offset1;
				for (int m = numberLatitude - 2; m >= 0; m--) {
					errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + i), vertexArray.at(i),
						vertexArray.at(offset0 + i), radiusRoundVertical);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m*numberLongitude;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArray.at(offsetChange1 + i), vertexArray.at(i),
					vertexArray.at(offset0 + i), radiusRoundVertical, numberVertexAddVertical, arrayVertex[i], errorRound[i], errorChange);
			}
			else if (errorRound[i] == 5) {
				errorChange = 3;
				offsetChange1 = offset0;
				for (int m = 1; m < numberLatitude - 1; m++) {
					errorChange = getErrorToRound(vertexArray.at(offset1 + i), vertexArray.at(i),
						vertexArray.at(m*numberLongitude + i), radiusRoundVertical);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m*numberLongitude;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArray.at(offset1 + i), vertexArray.at(i),
					vertexArray.at(offsetChange1 + i), radiusRoundVertical, numberVertexAddVertical,
					arrayVertex[i], errorRound[i], errorChange);
			}
			else
			{
				roundEdge(vertexArray.at(offset1 + i), vertexArray.at(i),
					vertexArray.at(offset0 + i), radiusRoundVertical, numberVertexAddVertical, arrayVertex[i], errorRound[i], -1);
			}
		}

		//xóa đi cụm vertex ta cần thay thế
		vertexArrayRound.erase(vertexArrayRound.begin(),
			vertexArrayRound.begin() + numberLongitude);

		//thêm vào các dãy vertex tiếp theo
		for (int i = numberVertexAddVertical - 1; i >= 0; i--) {
			for (int k = numberLongitude - 1; k >= 0; k--) {
				vertexArrayRound.insert(vertexArrayRound.begin(), arrayVertex[k][i]);
			}
		}
		numberLatitudeRound += (numberVertexAddVertical - 1);
	}

	//kiểm tra xem tất các các góc ngang của tất cả các hàng xem có cần bo ít nhất 1 góc nào không(cũng như lấy mã lỗi của các góc)
	isShould = true;


	//********** Đối với các góc ngang thì để kiểm tra xem cần bo không thì phải kiểm tra hết toàn bộ các góc dọc theo góc đó để xem cần bo không
	//mà thường bề mặt ngang luôn cần bo nên việc này hơi tốn và thừa,để bữa sau xem sao


	//kiểm tra xem có góc nào cần bo không
	if (isShould == true) {
		//sau đó kiểm tra theo chiều ngang xem có cần bo góc không
		for (int i = numberLatitudeRound - 1; i >= 0; i--) {
			offset0 = i*numberLongitude;
			offset1 = (i + 1)*numberLongitude;
			//tính bo góc đỉnh cuối cùng,đầu tiên và thứ 2
			errorRound[0] = getErrorToRound(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
				vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
			if (errorRound[0] == 3) {
				//đây là góc đầu tiên nên bắt buộc phải bo tròn để các góc sau nếu bị trùng thì cũng dựa theo nó được
				errorChange = 3;
				offsetChange1 = offset1 - 1;
				offsetChange2 = offset0 + 1;
				for (int m = offset1 - 2; m > offset0 + 1; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					if (errorChange != 3) {
						offsetChange1 = m;
						for (int n = offset0 + 2; n < offset1 - 1; n++) {
							errorChange = getErrorToRound(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
								vertexArrayRound.at(n), radiusRoundHorizontal);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				//nếu cuối cùng lỗi vần bằng 3 thì đó là cụm điểm trùng nhau,đặt tất cả lại 1 chỗ
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offsetChange2), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[0], errorRound[0], errorChange);

			}
			else if (errorRound[0] == 4) {
				errorChange = 3;
				offsetChange1 = offset1 - 1;
				for (int m = offset1 - 2; m > offset0 + 1; m--) {
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], errorChange);
			}
			else if (errorRound[0] == 5) {
				errorChange = 3;
				offsetChange1 = offset0 + 1;
				for (int m = offset0 + 2; m < offset1 - 1; m++) {
					errorChange = getErrorToRound(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
						vertexArrayRound.at(m), radiusRoundHorizontal);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				roundEdge(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], errorChange);
			}
			else
			{
				roundEdge(vertexArrayRound.at(offset1 - 1), vertexArrayRound.at(offset0),
					vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[0], errorRound[0], -1);
			}

			//tính bo góc các góc trong
			for (int k = 0; k < numberLongitude - 2; k++) {
				errorRound[0] = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
					vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
				//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
				if (errorRound[0] == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[k + 1], 3, 3);
				}
				else if (errorRound[0] == 4) {
					errorChange = 3;
					offsetChange1 = k;
					for (int m = k - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + m), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + offsetChange1), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], errorRound[0], errorChange);
					}
				}
				else if (errorRound[0] == 5) {
					errorChange = 3;
					offsetChange1 = k + 2;
					for (int m = k + 3; m < numberLongitude; m++) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + m), radiusRoundHorizontal);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k + 1], errorRound[0], errorChange);
					}
				}
				else
				{
					roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
						vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal, arrayVertex[k + 1], errorRound[0], -1);
				}
			}
			//tính bo góc đỉnh gần cuối,đỉnh cuối cùng và đỉnh đầu tiên
			errorRound[0] = getErrorToRound(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
				vertexArrayRound.at(offset0), radiusRoundHorizontal);
			if (errorRound[0] == 3) {
				errorChange = 3;
				offsetChange1 = offset1 - 2;
				offsetChange2 = offset0;
				for (int m = offset1 - 3; m > offset0; m--) {
					//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset0),
						vertexArrayRound.at(offset0 + 1), radiusRoundHorizontal);
					if (errorChange != 3) {
						offsetChange1 = m;
						for (int n = offset0 + 1; n < offset1 - 3; n++) {
							errorChange = getErrorToRound(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset0),
								vertexArrayRound.at(n), radiusRoundHorizontal);
							//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
							if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
								offsetChange2 = n;
								break;
							}
							else
								errorChange = 3;
						}
					}
				}
				roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset1 - 1),
					vertexArrayRound.at(offsetChange2), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
			}
			else if (errorRound[0] == 4) {
				errorChange = 3;
				offsetChange1 = offset1 - 2;
				for (int m = offset1 - 3; m > offset0; m--) {
					errorChange = getErrorToRound(vertexArrayRound.at(m), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offset0), radiusRoundHorizontal);
					//nếu mã lỗi khác 4 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 4) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				if (errorChange == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[numberLongitude - 2][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], 3, 3);
				}
				else {
					roundEdge(vertexArrayRound.at(offsetChange1), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offset0), radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
				}
			}
			else if (errorRound[0] == 5) {
				errorChange = 3;
				offsetChange1 = offset0;
				for (int m = offset0 + 1; m < offset1 - 2; m++) {
					errorChange = getErrorToRound(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(m), radiusRoundHorizontal);
					//nếu mã lỗi khác 5 và 3 thì chấp nhận
					if (errorChange != 3 && errorChange != 5) {
						offsetChange1 = m;
						break;
					}
					else
						errorChange = 3;
				}
				if (errorChange == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[numberLongitude - 2][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], 3, 3);
				}
				else {
					roundEdge(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
						vertexArrayRound.at(offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[numberLongitude - 1], errorRound[0], errorChange);
				}
			}
			else
			{
				roundEdge(vertexArrayRound.at(offset1 - 2), vertexArrayRound.at(offset1 - 1),
					vertexArrayRound.at(offset0), radiusRoundHorizontal, numberVertexAddHorizontal,
					arrayVertex[numberLongitude - 1], errorRound[0], -1);
			}


			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//xóa đi cụm vertex ta cần thay thế
			vertexArrayRound.erase(vertexArrayRound.begin() + offset0,
				vertexArrayRound.begin() + offset1);

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int k = numberLongitude - 1; k >= 0; k--) {
				for (int m = numberVertexAddHorizontal - 1; m >= 0; m--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset0, arrayVertex[k][m]);
				}
			}
		}
		//nhớ tăng numberLongitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
		numberLongitudeRound = numberVertexAddHorizontal*numberLongitude;
	}

	//xóa mảng động
	for (int i = 0; i < maxItem; i++)
	{
		delete[] arrayVertex[i];
	}
	delete[] arrayVertex;
	delete[] errorRound;
}

//hàm bo góc cạnh dùng cho các hình có thuộc tính giống ObjectCustom1
void roundEdgeForObject3(vector<point> vertexArray, vector<point> &vertexArrayRound, vector<point> &normalVectorRound,
	int numberLongitude, int numberLatitude, int &numberLongitudeRound, int &numberLatitudeRound,
	float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//đầu tiên phải xóa hêt vertexArrayRound
	vertexArrayRound.clear();

	int maxItem = numberLongitude > numberLatitude ? numberLongitude : numberLatitude,
		maxVertexAdd = numberVertexAddHorizontal > numberVertexAddVertical ? numberVertexAddHorizontal : numberVertexAddVertical;
	//0 là không lỗi gì,bo bình thường,1 là góc bằng 0 hay 180 độ,2 là không đủ chiều dài để bo
	//3 là bị chồng chéo điểm(cả 3 đỉnh đang xét đều bị chồng chéo lên nhau),4 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh trước bị chồng chéo),
	//5 là bị chống chéo đỉnh nhưng chỉ có 2 đỉnh sau bị chồng chéo),6 là vừa thiếu bán kính bo vừa góc bo bằng 180 độ
	int *errorRound = new int[maxItem], errorChange
		, offset0, offset1, offset2, offsetChange1, offsetChange2;
	//nếu có 1 cái isCant ==true nghĩa là không thể bo,còn nếu nó bằng false và chỉ cần 1 cái isShould ==true thì bo tròn
	bool isShould = false;
	int halfLogitude = numberLongitude / 2;
	point **arrayVertex;
	arrayVertex = new point*[maxItem];
	for (int i = 0; i < maxItem; i++) {
		arrayVertex[i] = new point[maxVertexAdd];
	}

	//đầu tiên đặt numberLongitudeRound vầ numberLatitudeRound và vertexArrayRound như là của vertexArray,numberLongitude và numberLatitude
	numberLatitudeRound = numberLatitude;
	numberLongitudeRound = numberLongitude;
	vertexArrayRound = vertexArray;

	//sau đó kiểm tra theo chiều dọc trước xem có cần bo góc không

	for (int i = numberLatitude - 3; i >= 0; i--) {
		//mối lần kiểm tra cùng một vị trí ở trên 3 hàng liên tục xem có cần bo góc không
		offset0 = i*numberLongitude;
		offset1 = (i + 1)*numberLongitude;
		offset2 = (i + 2)*numberLongitude;
		isShould = false;
		for (int k = 0; k < numberLongitude; k++) {
			//lấy mã lỗi
			errorRound[k] = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
				vertexArray.at(offset2 + k), radiusRoundVertical);
			if (errorRound[k] != 1 && errorRound[k] != 6 && errorRound[k] != 3) {
				isShould = true;
			}
		}

		//kiểm tra xem có góc nào cần bo không và có góc nào không thể bo không
		if (isShould == true) {
			for (int k = 0; k < numberLongitude; k++) {
				//kiểm tra nếu mã lỗi bằng 4 hoặc 5 là bị trùng 2 trong 3 điểm,cần tìm điểm thay thế
				//nếu mà lỗi bằng 3 là bì trùng cả 3 điểm cần tìm 2 điểm thay thế nếu có
				if (errorRound[k] == 3) {
					errorChange = 3;
					offsetChange1 = offset0;
					offsetChange2 = offset2;
					for (int m = i - 1; m >= 0; m--) {
						//đầu tiên tìm ra điểm đầu(nếu lỗi khác 3 nghĩa là đã tìm được)
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						if (errorChange != 3) {
							offsetChange1 = m*numberLongitude;
							for (int n = i + 3; n < numberLatitude; n++) {
								errorChange = getErrorToRound(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k),
									vertexArray.at(n*numberLongitude + k), radiusRoundVertical);
								//nếu không có bất kỳ lỗi nào thì đã tìm ra được 2 điểm thay thế
								if (errorChange != 3 && errorChange != 4 && errorChange != 5) {
									offsetChange2 = n*numberLongitude;
									break;
								}
								else
									errorChange = 3;
							}
						}
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 4) {
					//nếu bị trùng phía trước thì tìm các điểm trước đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset0;
					for (int m = i - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArray.at(m*numberLongitude + k), vertexArray.at(offset1 + k),
							vertexArray.at(offset2 + k), radiusRoundVertical);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offsetChange1 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else if (errorRound[k] == 5) {
					//nếu bị trùng phía sau thì tìm các điểm phía sau đó xem có điểm nào thay thế được không
					errorChange = 3;
					offsetChange1 = offset2;
					for (int m = i + 3; m < numberLatitude; m++) {
						errorChange = getErrorToRound(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k),
							vertexArray.at(m*numberLongitude + k), radiusRoundVertical);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m*numberLongitude;
							break;
						}
						//nếu không thì chuyển nó về 3 để xác định là không tìm được điểm thay thế
						else
							errorChange = 3;
					}
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offsetChange1 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], errorChange);
				}
				else
				{
					//nếu không bị trùng điểm thì bo góc như bình thường
					roundEdge(vertexArray.at(offset0 + k), vertexArray.at(offset1 + k), vertexArray.at(offset2 + k),
						radiusRoundVertical, numberVertexAddVertical, arrayVertex[k], errorRound[k], -1);
				}
			}
			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//đầu tiên thay thế cụm vertex ở giữa bằng cụm arrayVertex cuối cùng để đỡ phải xóa
			for (int k = 0; k < numberLongitude; k++) {
				vertexArrayRound.at(offset1 + k) = arrayVertex[k][numberVertexAddVertical - 1];
			}

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int m = numberVertexAddVertical - 2; m >= 0; m--) {
				for (int k = numberLongitude - 1; k >= 0; k--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset1, arrayVertex[k][m]);
				}
			}

			//nhớ tăng numberLatitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
			numberLatitudeRound += (numberVertexAddVertical - 1);
		}
	}

	//kiểm tra xem tất các các góc ngang của tất cả các hàng xem có cần bo ít nhất 1 góc nào không(cũng như lấy mã lỗi của các góc)
	isShould = true;


	//********** Đối với các góc ngang thì để kiểm tra xem cần bo không thì phải kiểm tra hết toàn bộ các góc dọc theo góc đó để xem cần bo không
	//mà thường bề mặt ngang luôn cần bo nên việc này hơi tốn và thừa,để bữa sau xem sao


	//kiểm tra xem có góc nào cần bo không
	if (isShould == true) {
		//sau đó kiểm tra theo chiều ngang xem có cần bo góc không
		for (int i = numberLatitudeRound - 1; i >= 0; i--) {
			offset0 = i*numberLongitude;
			offset1 = (i + 1)*numberLongitude;
			
			//tính bo góc các góc trong
			for (int k = 0; k < numberLongitude - 2; k++) {
				errorRound[0] = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
					vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
				//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
				if (errorRound[0] == 3) {
					roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
					{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[k], 3, 3);
				}
				else if (errorRound[0] == 4) {
					errorChange = 3;
					offsetChange1 = k;
					for (int m = k - 1; m >= 0; m--) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + m), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal);
						//nếu mã lỗi khác 4 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 4) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + offsetChange1), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k], errorRound[0], errorChange);
					}
				}
				else if (errorRound[0] == 5) {
					errorChange = 3;
					offsetChange1 = k + 2;
					for (int m = k + 3; m < numberLongitude; m++) {
						errorChange = getErrorToRound(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + m), radiusRoundHorizontal);
						//nếu mã lỗi khác 5 và 3 thì chấp nhận
						if (errorChange != 3 && errorChange != 5) {
							offsetChange1 = m;
							break;
						}
						else
							errorChange = 3;
					}
					//nếu lỗi bằng 3 thì đặt B là điểm vừa bo phía trước nó(điểm đã được bo)
					if (errorChange == 3) {
						roundEdge({ 0.0,0.0,0.0 }, arrayVertex[k][numberVertexAddHorizontal - 1],
						{ 0.0,0.0,0.0 }, radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k], 3, 3);
					}
					else {
						roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
							vertexArrayRound.at(offset0 + offsetChange1), radiusRoundHorizontal, numberVertexAddHorizontal,
							arrayVertex[k], errorRound[0], errorChange);
					}
				}
				else
				{
					roundEdge(vertexArrayRound.at(offset0 + k), vertexArrayRound.at(offset0 + k + 1),
						vertexArrayRound.at(offset0 + k + 2), radiusRoundHorizontal, numberVertexAddHorizontal,
						arrayVertex[k], errorRound[0], -1);
				}
			}
			


			//sau khi đã tính ra hết các đỉnh bo rồi thì thêm vào
			//xóa đi cụm vertex ta cần thay thế
			vertexArrayRound.erase(vertexArrayRound.begin() + offset0 + 1,
				vertexArrayRound.begin() + offset1 - 1);

			//sau đó thêm các cụm còn lại vào(nhớ là phải thêm từ sau ra trước)
			for (int k = numberLongitude - 3; k >= 0; k--) {
				for (int m = numberVertexAddHorizontal - 1; m >= 0; m--) {
					vertexArrayRound.insert(vertexArrayRound.begin() + offset0 + 1, arrayVertex[k][m]);
				}
			}
		}
		//nhớ tăng numberLongitudeRound lên(-1 là do trong số vertex thêm vào này có cả vertex ở giữa của cụm ban đầu nữa)
		numberLongitudeRound = numberVertexAddHorizontal*(numberLongitude - 2) + 2;
	}


	//xóa mảng động
	for (int i = 0; i < maxItem; i++)
	{
		delete[] arrayVertex[i];
	}
	delete[] arrayVertex;
	delete[] errorRound;
}

//hàm bo tròn góc cạnh của sphere
void roundEdgeSphere(SphereAttribute *sphere, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//gọi hàm tính toán bo góc
	roundEdgeForObject1(sphere->vertexArray, sphere->vertexArrayRound, sphere->normalVectorRound, sphere->numberLongitude, sphere->numberLatitude,
		sphere->numberLongitudeRound, sphere->numberLatitudeRound, radiusRoundHorizontal, numberVertexAddHorizontal,
		radiusRoundVertical, numberVertexAddVertical);
	//tính toán normalVectorRound
	CaculatorNormalForSphere(sphere->numberLongitudeRound, sphere->numberLatitudeRound, sphere->vertexArrayRound, sphere->normalVectorRound);
}
//hàm bo tròn góc cạnh của cone
void roundEdgeCone(ConeAttribute *cone, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//gọi hàm tính toán bo góc
	roundEdgeForObject1(cone->vertexArray, cone->vertexArrayRound, cone->normalVectorRound, cone->numberLongitude, cone->numberLatitude,
		cone->numberLongitudeRound, cone->numberLatitudeRound, radiusRoundHorizontal, numberVertexAddHorizontal,
		radiusRoundVertical, numberVertexAddVertical);

	//tính toán normalVectorRound
	CaculatorNormalForCone(cone->numberLongitudeRound, cone->numberLatitudeRound, cone->vertexArrayRound, cone->normalVectorRound);
}
//hàm bo tròn góc cạnh của cylinder
void roundEdgeCylinder(CylinderAttribute *cylinder, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//gọi hàm tính toán bo góc
	roundEdgeForObject1(cylinder->vertexArray, cylinder->vertexArrayRound, cylinder->normalVectorRound, cylinder->numberLongitude, cylinder->numberLatitude,
		cylinder->numberLongitudeRound, cylinder->numberLatitudeRound, radiusRoundHorizontal, numberVertexAddHorizontal,
		radiusRoundVertical, numberVertexAddVertical);

	//tính toán normalVectorRound
	CaculatorNormalForCylinder(cylinder->numberLongitudeRound, cylinder->numberLatitudeRound, cylinder->vertexArrayRound, cylinder->normalVectorRound);
}
//hàm bo tròn góc cạnh của empty cylinder
void roundEdgeEmptyCylinder(EmptyCylinderAttribute *cylinder, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//gọi hàm tính toán bo góc
	roundEdgeForObject2(cylinder->vertexArray, cylinder->vertexArrayRound, cylinder->normalVectorRound, cylinder->numberLongitude, cylinder->numberLatitude,
		cylinder->numberLongitudeRound, cylinder->numberLatitudeRound, radiusRoundHorizontal, numberVertexAddHorizontal,
		radiusRoundVertical, numberVertexAddVertical);

	//tính toán normalVectorRound
	CaculatorNormalForEmptyCylinder(cylinder->numberLongitudeRound, cylinder->numberLatitudeRound,
		cylinder->vertexArrayRound, cylinder->normalVectorRound);
}
//hàm bo tròn góc cạnh của ObjectCustom0
void roundEdgeObjectCustom0(ObjectCustom0Attribute *object, float radiusRoundHorizontal, int numberVertexAddHorizontal,
	float radiusRoundVertical, int numberVertexAddVertical) {
	//gọi hàm tính toán bo góc
	roundEdgeForObject3(object->vertexArray, object->vertexArrayRound, object->normalVectorRound,
		object->numberLongitude, object->numberLatitude,
		object->numberLongitudeRound, object->numberLatitudeRound,
		radiusRoundHorizontal, numberVertexAddHorizontal,
		radiusRoundVertical, numberVertexAddVertical);

	//tính toán normalVectorRound
	CaculatorNormalForObjectCustom0(object->numberLongitudeRound, object->numberLatitudeRound,
		object->vertexArrayRound, object->normalVectorRound);
}

//hàm vẽ menu có nút tăng giảm
//vị trí các nút tăng giảm là (left+90 left+100,top top+10),(left+170 left+180,top top+10)
void drawMenuPlusMinus(char* text, float value, bool isChoice,
	int leftItem, int topItem) {
	//vẽ 2 hình tăng giảm
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftItem + 90, topItem + 5);
	glVertex2f(leftItem + 100, topItem + 10);
	glVertex2f(leftItem + 100, topItem);

	glVertex2f(leftItem + 180, topItem + 5);
	glVertex2f(leftItem + 170, topItem);
	glVertex2f(leftItem + 170, topItem + 10);
	glEnd();

	if (isChoice) {
		glColor3f(0.6, 0.6, 0.7);
	}
	else
	{
		glColor3f(0.3f, 0.3f, 0.4f);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 105, topItem - 2);
	glVertex2f(leftItem + 105, topItem + 12);
	glVertex2f(leftItem + 165, topItem - 2);
	glVertex2f(leftItem + 165, topItem + 12);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	//hiện tên của menu
	drawText(leftItem, topItem + 9, text, "helvetica", 12);
	//hiện giá trị hiện tại
	char charNumber[20];
	changeNumberFloatToCharArray(charNumber, value);
	if (value <= -100) {
		drawText(leftItem + 112, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value <= -10) {
		drawText(leftItem + 115, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 0)
	{
		drawText(leftItem + 118, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 10) {
		drawText(leftItem + 124, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 100) {
		drawText(leftItem + 119, topItem + 9, charNumber, "helvetica", 12);
	}
	else
	{
		drawText(leftItem + 116, topItem + 9, charNumber, "helvetica", 12);
	}
}
void drawMenuPlusMinus(char* text, int value, bool isChoice,
	int leftItem, int topItem) {
	//vẽ 2 hình tăng giảm
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftItem + 90, topItem + 5);
	glVertex2f(leftItem + 100, topItem + 10);
	glVertex2f(leftItem + 100, topItem);

	glVertex2f(leftItem + 180, topItem + 5);
	glVertex2f(leftItem + 170, topItem);
	glVertex2f(leftItem + 170, topItem + 10);
	glEnd();

	if (isChoice) {
		glColor3f(0.6, 0.6, 0.7);
	}
	else
	{
		glColor3f(0.3f, 0.3f, 0.4f);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 105, topItem - 2);
	glVertex2f(leftItem + 105, topItem + 12);
	glVertex2f(leftItem + 165, topItem - 2);
	glVertex2f(leftItem + 165, topItem + 12);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	//hiện tên của menu
	drawText(leftItem, topItem + 9, text, "helvetica", 12);
	//hiện giá trị hiện tại
	char charNumber[20];
	changeNumberIntToCharArray(charNumber, value);
	if (value <= -100) {
		drawText(leftItem + 122, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value <= -10) {
		drawText(leftItem + 125, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 0)
	{
		drawText(leftItem + 128, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 10) {
		drawText(leftItem + 132, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 100)
	{
		drawText(leftItem + 129, topItem + 9, charNumber, "helvetica", 12);
	}
	else
	{
		drawText(leftItem + 126, topItem + 8, charNumber, "helvetica", 12);
	}
}
void drawMenuPlusMinus(char* text, char* charValue,
	int leftItem, int topItem) {
	//vẽ 2 hình tăng giảm
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftItem + 90, topItem + 5);
	glVertex2f(leftItem + 100, topItem + 10);
	glVertex2f(leftItem + 100, topItem);

	glVertex2f(leftItem + 180, topItem + 5);
	glVertex2f(leftItem + 170, topItem);
	glVertex2f(leftItem + 170, topItem + 10);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 105, topItem - 2);
	glVertex2f(leftItem + 105, topItem + 12);
	glVertex2f(leftItem + 165, topItem - 2);
	glVertex2f(leftItem + 165, topItem + 12);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	//hiện tên của menu
	drawText(leftItem, topItem + 9, text, "helvetica", 12);
	//tính khoảng cách đặt phù hợp,nếu là dấu trừ thì khoảng cách khác,nếu là dấu . thì khoảng cách khác
	//mà nếu số thì khoảng cách khác
	int distance = 0;
	for (int i = 0; i < 7; i++) {
		if (charValue[i] != NULL) {
			if (charValue[i] == '-') {
				distance += 8;
			}
			else if (charValue[i] == '.') {
				distance += 3;
			}
			else
			{
				distance += 7;
			}
		}
		else
			break;
	}

	drawText(leftItem + 165 - distance, topItem + 9, charValue, "helvetica", 12);
}
//hàm vẽ menu Off/On
//vị trí điểm nhấn là (left + 110 left+150,top top+10)
void drawMenuOffOn(char* text, bool isOn,
	int leftItem, int topItem) {
	//kiểm tra xem có bật hay không để hiên nút
	if (isOn) {
		glColor3f(0.95f, 0.95f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftItem + 130, topItem - 2);
		glVertex2f(leftItem + 130, topItem + 12);
		glVertex2f(leftItem + 150, topItem - 2);
		glVertex2f(leftItem + 150, topItem + 12);
		glEnd();

		glColor3f(0.8f, 0.8f, 0.8f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftItem + 110, topItem);
		glVertex2f(leftItem + 110, topItem + 10);
		glVertex2f(leftItem + 130, topItem);
		glVertex2f(leftItem + 130, topItem + 10);
		glEnd();
	}
	else
	{
		glColor3f(0.95f, 0.95f, 1.0f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftItem + 110, topItem - 2);
		glVertex2f(leftItem + 110, topItem + 12);
		glVertex2f(leftItem + 130, topItem - 2);
		glVertex2f(leftItem + 130, topItem + 12);
		glEnd();

		glColor3f(0.1f, 0.1f, 0.1f);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftItem + 130, topItem);
		glVertex2f(leftItem + 130, topItem + 10);
		glVertex2f(leftItem + 150, topItem);
		glVertex2f(leftItem + 150, topItem + 10);
		glEnd();
	}

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(leftItem, topItem + 8, text, "helvetica", 12);
}
//hàm vẽ menu get value
//vị trí nut get(+65 +95,-2 +12) max(+100 +130,-2 +12)  min(+135 +165,-2 +12)
//vị trí ô hiện giá trị(0 +60,-2 +12)
void drawMenuGetValue(int value, bool isChoiceText,
	int leftItem, int topItem) {

	if (isChoiceText) {
		glColor3f(0.2f, 0.2f, 0.2f);
	}
	else
	{
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem, topItem - 2);
	glVertex2f(leftItem, topItem + 12);
	glVertex2f(leftItem + 60, topItem - 2);
	glVertex2f(leftItem + 60, topItem + 12);
	glEnd();

	glColor3f(0.1f, 0.3f, 0.2f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 65, topItem - 2);
	glVertex2f(leftItem + 65, topItem + 12);
	glVertex2f(leftItem + 95, topItem - 2);
	glVertex2f(leftItem + 95, topItem + 12);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 100, topItem - 2);
	glVertex2f(leftItem + 100, topItem + 12);
	glVertex2f(leftItem + 130, topItem - 2);
	glVertex2f(leftItem + 130, topItem + 12);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftItem + 135, topItem - 2);
	glVertex2f(leftItem + 135, topItem + 12);
	glVertex2f(leftItem + 165, topItem - 2);
	glVertex2f(leftItem + 165, topItem + 12);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);
	drawText(leftItem + 70, topItem + 9, "Get", "helvetica", 12);
	drawText(leftItem + 103, topItem + 9, "Max", "helvetica", 12);
	drawText(leftItem + 140, topItem + 9, "Min", "helvetica", 12);
	//hiện giá trị hiện tại
	char charNumber[20];
	changeNumberIntToCharArray(charNumber, value);
	if (value <= -100) {
		drawText(leftItem + 14, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value <= -10) {
		drawText(leftItem + 17, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 0)
	{
		drawText(leftItem + 20, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 10) {
		drawText(leftItem + 26, topItem + 9, charNumber, "helvetica", 12);
	}
	else if (value < 100)
	{
		drawText(leftItem + 22, topItem + 9, charNumber, "helvetica", 12);
	}
	else
	{
		drawText(leftItem + 19, topItem + 8, charNumber, "helvetica", 12);
	}
}

//hiện thông tin về các cài đặt của ứng dụng

//hiện hộp chọn màu
void showMenuGroup1(float *colorDefaul, int modelMenuGroup, GLint colorPicker,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	glDisable(GL_LIGHTING);
	//vẽ hình tứ giác bao cụm menu phía trên
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu, topMenu);
	glVertex2f(leftMenu, bottomMenu);
	glVertex2f(rightMenu, topMenu);
	glVertex2f(rightMenu, bottomMenu);
	glEnd();
	glColor3f(0.2f, 0.25f, 0.26f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 1, topMenu + 1);
	glVertex2f(leftMenu + 1, bottomMenu - 1);
	glVertex2f(rightMenu - 1, topMenu + 1);
	glVertex2f(rightMenu - 1, bottomMenu - 1);
	glEnd();

	//vẽ các hộp màu nhanh mà ta thường dùng ở phía trên để chọn nhanh
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 10, topMenu + 10);
	glVertex2f(leftMenu + 10, topMenu + 30);
	glVertex2f(leftMenu + 30, topMenu + 10);
	glVertex2f(leftMenu + 30, topMenu + 30);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 40, topMenu + 10);
	glVertex2f(leftMenu + 40, topMenu + 30);
	glVertex2f(leftMenu + 60, topMenu + 10);
	glVertex2f(leftMenu + 60, topMenu + 30);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 70, topMenu + 10);
	glVertex2f(leftMenu + 70, topMenu + 30);
	glVertex2f(leftMenu + 90, topMenu + 10);
	glVertex2f(leftMenu + 90, topMenu + 30);
	glEnd();
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 100, topMenu + 10);
	glVertex2f(leftMenu + 100, topMenu + 30);
	glVertex2f(leftMenu + 120, topMenu + 10);
	glVertex2f(leftMenu + 120, topMenu + 30);
	glEnd();
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 130, topMenu + 10);
	glVertex2f(leftMenu + 130, topMenu + 30);
	glVertex2f(leftMenu + 150, topMenu + 10);
	glVertex2f(leftMenu + 150, topMenu + 30);
	glEnd();

	//vẽ hình tứ giác để chọn màu
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, colorPicker);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.0, 0.0); glVertex2f(leftMenu + 10, topMenu + 50);
	glTexCoord2f(0.0, 1.0); glVertex2f(leftMenu + 10, topMenu + 260);
	glTexCoord2f(1.0, 1.0); glVertex2f(rightMenu - 10, topMenu + 260);
	glTexCoord2f(1.0, 0.0); glVertex2f(rightMenu - 10, topMenu + 50);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	//vẽ hộp khung bao ngoài hộp hiện màu môi trường mặc định
	if (modelMenuGroup == 0) {
		//nếu hộp được chọn thì hiện màu vàng
		glColor3f(0.8f, 0.8f, 0.4f);
	}
	else
	{
		glColor3f(0.5f, 0.5f, 0.5f);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 8, topMenu + 268);
	glVertex2f(leftMenu + 8, topMenu + 322);
	glVertex2f(leftMenu + 92, topMenu + 268);
	glVertex2f(leftMenu + 92, topMenu + 322);
	glEnd();
	//hiện màu môi trường mặc định
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.3f, 0.3f, 0.32f);
	glVertex2f(leftMenu + 10, topMenu + 270);
	glVertex2f(leftMenu + 10, topMenu + 320);
	glVertex2f(leftMenu + 90, topMenu + 270);
	glVertex2f(leftMenu + 90, topMenu + 320);
	glEnd();

	//hiện khung bao ngoài hộp hiện màu mặc định
	if (modelMenuGroup == 1) {
		//nếu hộp được chọn thì hiện màu vàng
		glColor3f(0.8f, 0.8f, 0.4f);
	}
	else
	{
		glColor3f(0.5f, 0.5f, 0.5f);
	}
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 48, topMenu + 298);
	glVertex2f(leftMenu + 48, topMenu + 352);
	glVertex2f(leftMenu + 132, topMenu + 298);
	glVertex2f(leftMenu + 132, topMenu + 352);
	glEnd();
	//hiện màu mặc định
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(colorDefaul[0], colorDefaul[1], colorDefaul[2]);
	glVertex2f(leftMenu + 50, topMenu + 300);
	glVertex2f(leftMenu + 50, topMenu + 350);
	glVertex2f(leftMenu + 130, topMenu + 300);
	glVertex2f(leftMenu + 130, topMenu + 350);
	glEnd();


	glEnable(GL_LIGHTING);
}
//kiểm tra xem chọn trúng mục nào của hộp chọn màu không
bool checkChoiceMenuGroup1(int x, int y, bool &isChoiceColorPicker, int &modelMenuGroup,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	//kiểm tra xem chọn trúng thanh trượt hay hộp chọn màu không
	if (x > leftMenu + 10 && x < rightMenu - 10 && y>topMenu + 50 && y < topMenu + 260) {
		isChoiceColorPicker = true;
		return true;
	}
	else if (x > leftMenu + 50 && x < leftMenu + 130 && y>topMenu + 300 && y < topMenu + 350) {
		modelMenuGroup = 1;
		return true;
	}
	else if (x > leftMenu + 10 && x < leftMenu + 90 && y>topMenu + 270 && y < topMenu + 320) {
		modelMenuGroup = 0;
		return true;
	}
	return false;
}

//hiện các texture cho thuộc tính texture
void showMenuTexture(itemTextureObject itemTexture,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	//tính toán xem nếu không có khoảng cách thì có bao nhiêu hình ảnh có thể đặt trên 1 hàng
	//kích thước hình ảnh là 40*60(dọc * ngang)

	//-10 ở widthMenu là trừ đi khoảng trắng mỗi 2 bên là 5
	//còn numberItemInRow đặt sẵn cho trường hợp 1 hàng có thể chứa hết menu luôn
	int widthMenu = rightMenu - leftMenu - 10, widthNow = 0, numberItemInRow = itemTexture.numberTexture;
	for (int i = 0; i < itemTexture.numberTexture; i++) {
		if (widthNow < widthMenu) {
			widthNow += 60;
		}
		else
		{
			numberItemInRow = i;
			break;
		}
	}
	float distanceBetweenItems = (widthMenu - numberItemInRow * 60) / (numberItemInRow - 1),
		positionL = 5.0, positionT = 20.0;
	int numberItemInRowNow = 0;

	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	//vẽ các texture lên menu
	for (int i = 0; i < itemTexture.numberTexture; i++) {
		//đặt kết cấu
		glBindTexture(GL_TEXTURE_2D, itemTexture.startNameTexture + i);
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0, 0.0); glVertex2f(leftMenu + positionL, topMenu + positionT);
		glTexCoord2f(0.0, 1.0); glVertex2f(leftMenu + positionL, topMenu + positionT + 40);
		glTexCoord2f(1.0, 1.0); glVertex2f(leftMenu + positionL + 60, topMenu + positionT + 40);
		glTexCoord2f(1.0, 0.0); glVertex2f(leftMenu + positionL + 60, topMenu + positionT);
		glEnd();

		numberItemInRowNow++;
		//kiểm tra nếu đã đủ số hàng thì xuống dòng
		if (numberItemInRowNow == numberItemInRow) {
			positionL = 5.0;
			positionT += 42;

			numberItemInRowNow = 0;
		}
		else
		{
			positionL += (60 + distanceBetweenItems);
		}
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
}
//hàm kiểm tra xem có chọn trúng texture nào không
bool checkToChoiceMenuTexture(int x, int y, itemTextureObject &itemTexture, vector<itemChoice> itemsChoice,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//tính toán xem nếu không có khoảng cách thì có bao nhiêu hình ảnh có thể đặt trên 1 hàng
	//kích thước hình ảnh là 40*60(dọc * ngang)

	//-10 ở widthMenu là trừ đi khoảng trắng mỗi 2 bên là 5
	//còn numberItemInRow đặt sẵn cho trường hợp 1 hàng có thể chứa hết menu luôn
	int widthMenu = rightMenu - leftMenu - 10, widthNow = 0, numberItemInRow = itemTexture.numberTexture;
	for (int i = 0; i < itemTexture.numberTexture; i++) {
		if (widthNow < widthMenu) {
			widthNow += 60;
		}
		else
		{
			numberItemInRow = i;
			break;
		}
	}
	float distanceBetweenItems = (widthMenu - numberItemInRow * 60) / (numberItemInRow - 1),
		positionL = 5.0, positionT = 20.0;
	int numberItemInRowNow = 0;

	//vẽ các texture lên menu
	for (int i = 0; i < itemTexture.numberTexture; i++) {
		//kiểm tra xem có chọn trúng kết cấu này không
		if (x > leftMenu + positionL && x < leftMenu + positionL + 60
			&& y>topMenu + positionT && y < topMenu + positionT + 40) {
			itemTexture.textureChoiceNow = i;

			//đặt kết cấu cho vật được chọn
			setTextureForObjectChoice(itemTexture.textureChoiceNow, itemsChoice,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
				objectCustom0Array);
			return true;
		}

		numberItemInRowNow++;
		//kiểm tra nếu đã đủ số hàng thì xuống dòng
		if (numberItemInRowNow == numberItemInRow) {
			positionL = 5.0;
			positionT += 42;

			numberItemInRowNow = 0;
		}
		else
		{
			positionL += (60 + distanceBetweenItems);
		}
	}
	return false;
}

//hiện các nút tăng giảm và các giá trị thuộc tính liên quan như(depthRound,numberLongitude,...)
void showToolChangeAttribute(itemChoice item, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<SphereAttribute*> sphereArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<EmptyCylinderAttribute*> emptyCylinderArray, vector<TorusAttribute*> torusArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_LINES);
	glVertex2f(leftMenu + 2, topMenu + 37);
	glVertex2f(leftMenu + 15, topMenu + 37);

	glVertex2f(leftMenu + 115, topMenu + 37);
	glVertex2f(rightMenu - 2, topMenu + 37);
	glEnd();

	//hiện các thông tin về giá trị
	glColor3f(1.0, 1.0, 1.0);

	switch (item.object)
	{
	case 10: {
		drawText(leftMenu + 40, topMenu + 40, "Sphere", "helvetica", 12);
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num longitude", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num longitude", sphere->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num longitude", sphere->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num latitude", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num latitude", sphere->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num latitude", sphere->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}
		
		
		//các thuộc tính phụ khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Radius", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("Radius", sphere->radius, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("Radius", sphere->radius, false, leftMenu + 10, topMenu + 125);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLong Limit", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("DegLong Limit", sphere->degreeLongitudeLimit, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLong Limit", sphere->degreeLongitudeLimit, false, leftMenu + 10, topMenu + 145);
		}

		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLati Limit", menu_charNumberValue, leftMenu + 10, topMenu + 165);
			}
			else
			{
				drawMenuPlusMinus("DegLati Limit", sphere->degreeLatitudeLimit, true, leftMenu + 10, topMenu + 165);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLati Limit", sphere->degreeLatitudeLimit, false, leftMenu + 10, topMenu + 165);
		}
		
	}
			 break;
	case 11: {
		drawText(leftMenu + 44, topMenu + 40, "Cube", "helvetica", 12);

	}
			 break;
	case 12: {
		drawText(leftMenu + 26, topMenu + 40, "Cube Round", "helvetica", 12);
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num longitude", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num longitude", cube->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num longitude", cube->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num latitude", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num latitude", cube->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num latitude", cube->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}

	}
			 break;
	case 13: {
		drawText(leftMenu + 44, topMenu + 40, "Cone", "helvetica", 12);
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num longitude", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num longitude", cone->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num longitude", cone->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num latitude", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num latitude", cone->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num latitude", cone->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}

		//các thuộc tính phụ khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Height", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("Height", cone->height, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("Height", cone->height, false, leftMenu + 10, topMenu + 125);
		}
		
		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Radius", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("Radius", cone->radius, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("Radius", cone->radius, false, leftMenu + 10, topMenu + 145);
		}
		
		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLong Limit", menu_charNumberValue, leftMenu + 10, topMenu + 165);
			}
			else
			{
				drawMenuPlusMinus("DegLong Limit", cone->degreeLongitudeLimit, true, leftMenu + 10, topMenu + 165);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLong Limit", cone->degreeLongitudeLimit, false, leftMenu + 10, topMenu + 165);
		}
		
		if (item_choice_in_MenuGroup2 == 5) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLati Limit", menu_charNumberValue, leftMenu + 10, topMenu + 185);
			}
			else
			{
				drawMenuPlusMinus("DegLati Limit", cone->degreeLatitudeLimit, true, leftMenu + 10, topMenu + 185);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLati Limit", cone->degreeLatitudeLimit, false, leftMenu + 10, topMenu + 185);
		}
		
	}
			 break;
	case 14: {
		drawText(leftMenu + 35, topMenu + 40, "Cylinder", "helvetica", 12);
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num longitude", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num longitude", cylinder->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num longitude", cylinder->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num latitude", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num latitude", cylinder->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num latitude", cylinder->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}

		//các thuộc tính phụ khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Height", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("Height", cylinder->height, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("Height", cylinder->height, false, leftMenu + 10, topMenu + 125);
		}
		
		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusUp", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("RadiusUp", cylinder->radiusUp, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusUp", cylinder->radiusUp, false, leftMenu + 10, topMenu + 145);
		}
		
		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusDown", menu_charNumberValue, leftMenu + 10, topMenu + 165);
			}
			else
			{
				drawMenuPlusMinus("RadiusDown", cylinder->radiusDown, true, leftMenu + 10, topMenu + 165);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusDown", cylinder->radiusDown, false, leftMenu + 10, topMenu + 165);
		}
		
		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLong Limit", menu_charNumberValue, leftMenu + 10, topMenu + 185);
			}
			else
			{
				drawMenuPlusMinus("DegLong Limit", cylinder->degreeLongitudeLimit, true, leftMenu + 10, topMenu + 185);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLong Limit", cylinder->degreeLongitudeLimit, false, leftMenu + 10, topMenu + 185);
		}
		
		if (item_choice_in_MenuGroup2 == 5) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLati Limit", menu_charNumberValue, leftMenu + 10, topMenu + 205);
			}
			else
			{
				drawMenuPlusMinus("DegLati Limit", cylinder->degreeLatitudeLimit, true, leftMenu + 10, topMenu + 205);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLati Limit", cylinder->degreeLatitudeLimit, false, leftMenu + 10, topMenu + 205);
		}
	}
			 break;
	case 16: {
		drawText(leftMenu + 20, topMenu + 40, "Empty Cylinder", "helvetica", 12);
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num longitude", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num longitude", cylinder->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num longitude", cylinder->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num latitude", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num latitude", cylinder->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num latitude", cylinder->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}

		//các thuộc tính phụ khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Height", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("Height", cylinder->height, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("Height", cylinder->height, false, leftMenu + 10, topMenu + 125);
		}
		
		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusUpOut", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("RadiusUpOut", cylinder->radiusUpOut, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusUpOut", cylinder->radiusUpOut, false, leftMenu + 10, topMenu + 145);
		}

		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusDownOut", menu_charNumberValue, leftMenu + 10, topMenu + 165);
			}
			else
			{
				drawMenuPlusMinus("RadiusDownOut", cylinder->radiusDownOut, true, leftMenu + 10, topMenu + 165);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusDownOut", cylinder->radiusDownOut, false, leftMenu + 10, topMenu + 165);
		}

		if (item_choice_in_MenuGroup2 == 5) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusUpIn", menu_charNumberValue, leftMenu + 10, topMenu + 185);
			}
			else
			{
				drawMenuPlusMinus("RadiusUpIn", cylinder->radiusUpIn, true, leftMenu + 10, topMenu + 185);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusUpIn", cylinder->radiusUpIn, false, leftMenu + 10, topMenu + 185);
		}

		if (item_choice_in_MenuGroup2 == 6) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusDownIn", menu_charNumberValue, leftMenu + 10, topMenu + 205);
			}
			else
			{
				drawMenuPlusMinus("RadiusDownIn", cylinder->radiusDownIn, true, leftMenu + 10, topMenu + 205);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusDownIn", cylinder->radiusDownIn, false, leftMenu + 10, topMenu + 205);
		}

		if (item_choice_in_MenuGroup2 == 7) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLong Limit", menu_charNumberValue, leftMenu + 10, topMenu + 225);
			}
			else
			{
				drawMenuPlusMinus("DegLong Limit", cylinder->degreeLongitudeLimit, true, leftMenu + 10, topMenu + 225);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLong Limit", cylinder->degreeLongitudeLimit, false, leftMenu + 10, topMenu + 225);
		}

		if (item_choice_in_MenuGroup2 == 8) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("DegLati Limit", menu_charNumberValue, leftMenu + 10, topMenu + 245);
			}
			else
			{
				drawMenuPlusMinus("DegLati Limit", cylinder->degreeLatitudeLimit, true, leftMenu + 10, topMenu + 245);
			}
		}
		else
		{
			drawMenuPlusMinus("DegLati Limit", cylinder->degreeLatitudeLimit, false, leftMenu + 10, topMenu + 245);
		}
		
	}
			 break;
	case 17: {
		drawText(leftMenu + 42, topMenu + 40, "Torus", "helvetica", 12);
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Depth round", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Depth round", torus->depthRoundCake, false, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Depth round", torus->depthRoundCake, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Depth cake", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Depth cake", torus->depthCake, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Depth cake", torus->depthCake, false, leftMenu + 10, topMenu + 85);
		}
		
		
		//các thuộc tính khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusCake", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("RadiusCake", torus->radiusCake, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusCake", torus->radiusCake, false, leftMenu + 10, topMenu + 125);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusRoCake", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("RadiusRoCake", torus->radiusRoundCake, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusRoCake", torus->radiusRoundCake, false, leftMenu + 10, topMenu + 145);
		}

		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("WidthCake", menu_charNumberValue, leftMenu + 10, topMenu + 165);
			}
			else
			{
				drawMenuPlusMinus("WidthCake", torus->widthCake, true, leftMenu + 10, topMenu + 165);
			}
		}
		else
		{
			drawMenuPlusMinus("WidthCake", torus->widthCake, false, leftMenu + 10, topMenu + 165);
		}
	}
			 break;
	case 19: {
		drawText(leftMenu + 20, topMenu + 40, "Object Custom0", "helvetica", 12);
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num Long", menu_charNumberValue, leftMenu + 10, topMenu + 65);
			}
			else
			{
				drawMenuPlusMinus("Num Long", object->numberLongitude, true, leftMenu + 10, topMenu + 65);
			}
		}
		else
		{
			drawMenuPlusMinus("Num Long", object->numberLongitude, false, leftMenu + 10, topMenu + 65);
		}

		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Num lati", menu_charNumberValue, leftMenu + 10, topMenu + 85);
			}
			else
			{
				drawMenuPlusMinus("Num lati", object->numberLatitude, true, leftMenu + 10, topMenu + 85);
			}
		}
		else
		{
			drawMenuPlusMinus("Num lati", object->numberLatitude, false, leftMenu + 10, topMenu + 85);
		}

		//các thuộc tính phụ khác
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("LengthTwoRow", menu_charNumberValue, leftMenu + 10, topMenu + 125);
			}
			else
			{
				drawMenuPlusMinus("LengthTwoRow", object->lengthBetween2Row, true, leftMenu + 10, topMenu + 125);
			}
		}
		else
		{
			drawMenuPlusMinus("LengthTwoRow", object->lengthBetween2Row, false, leftMenu + 10, topMenu + 125);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("LengthTwoCol", menu_charNumberValue, leftMenu + 10, topMenu + 145);
			}
			else
			{
				drawMenuPlusMinus("LengthTwoCol", object->lengthBetween2Column, true, leftMenu + 10, topMenu + 145);
			}
		}
		else
		{
			drawMenuPlusMinus("LengthTwoCol", object->lengthBetween2Column, false, leftMenu + 10, topMenu + 145);
		}

		//hiện các nút để mở rộng hình theo 4 chiều(trên,dưới,trái,phải)
		drawText(rightMenu - 82, topMenu + 103, "Add", "helvetica", 12);
		glBegin(GL_TRIANGLES);
		//mũi tên trên
		glVertex2f(rightMenu - 70, topMenu + 70);
		glVertex2f(rightMenu - 85, topMenu + 80);
		glVertex2f(rightMenu - 55, topMenu + 80);

		//mũi tên trái
		glVertex2f(rightMenu - 95, topMenu + 85);
		glVertex2f(rightMenu - 105, topMenu + 100);
		glVertex2f(rightMenu - 95, topMenu + 115);

		//mũi tên dưới
		glVertex2f(rightMenu - 55, topMenu + 120);
		glVertex2f(rightMenu - 85, topMenu + 120);
		glVertex2f(rightMenu - 70, topMenu + 130);

		//mũi tên phải
		glVertex2f(rightMenu - 45, topMenu + 115);
		glVertex2f(rightMenu - 35, topMenu + 100);
		glVertex2f(rightMenu - 45, topMenu + 85);

		glEnd();
	}
			 break;
	default: {
		drawText(leftMenu + 35, topMenu + 40, "Object", "helvetica", 12);
	}
		break;
	}
}

//tìm ra số chia hết cho 360,dùng cho các hình như cone,cylinder,...
int findNumberDivisibleBy360(int valueStart, bool isPlus) {
	if (isPlus) {
		for (int i = valueStart + 1; i <= 360; i++) {
			if (360 % i == 0) {
				return i;
			}
		}
	}
	else
	{
		for (int i = valueStart - 1; i >= 2; i--) {
			if (360 % i == 0) {
				return i;
			}
		}
	}
	return 0;
}
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
bool appendCharArrayForValueAttribute(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	itemChoice item,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	//nếu đang ở chế độ chỉnh sửa bằng char thì áp dung char thành số và tắt chế độ chỉnh sửa
	if (menu_isChangeCharNumberValue) {
		bool isChange = false;

		switch (item.object)
		{
		case 10: {
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue= getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					sphere->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					sphere->numberLatitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					sphere->radius = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					sphere->degreeLongitudeLimit = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					sphere->degreeLatitudeLimit = intValue;
					isChange = true;
				}
			}
			//nếu có thay đổi trong thuộc tính của hình thì tính toán lại hình
			if (isChange) {
				sphere->vertexArray.clear();
				//tính toán lại
				CaculatorSphere(sphere->radius, sphere->numberLongitude, sphere->numberLatitude, sphere->centerObject,
					sphere->vertexArray);
				CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);
				return true;
			}

		}
				 break;
		case 11: {

		}
				 break;
		case 12: {
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cube->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cube->numberLatitude = intValue;
					isChange = true;
				}
			}

			if (isChange) {
				cube->vertexArray.clear();
				//tính toán lại
				CaculatorCubeRound(cube->xLength, cube->yLength, cube->zLength, cube->numberLongitude, cube->numberLatitude,
					cube->centerObject, cube->radiusRound, cube->vertexArray);
				CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);
				return true;
			}
		}
				 break;
		case 13: {
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cone->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cone->numberLatitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cone->height = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cone->radius = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cone->degreeLongitudeLimit = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cone->degreeLatitudeLimit = intValue;
					isChange = true;
				}
			}
			
			if (isChange) {
				cone->vertexArray.clear();
				caculatorCone(cone->centerObject, cone->radius, cone->height, cone->numberLongitude, cone->numberLatitude,
					cone->vertexArray);
				CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
				return true;
			}
		}
				 break;
		case 14: {
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->numberLatitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->height = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusUp = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusDown = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->degreeLongitudeLimit = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 6) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->degreeLatitudeLimit = intValue;
					isChange = true;
				}
			}

			if (isChange) {
				cylinder->vertexArray.clear();
				caculatorCylinder(cylinder->centerObject, cylinder->radiusUp, cylinder->radiusDown, cylinder->height,
					cylinder->numberLongitude, cylinder->numberLatitude, cylinder->vertexArray);
				CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
				return true;
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->numberLatitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->height = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusUpOut = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusDownOut = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusUpIn = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 6) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					cylinder->radiusDownIn = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 7) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->degreeLongitudeLimit = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 8) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					cylinder->degreeLatitudeLimit = intValue;
					isChange = true;
				}
			}
			
			if (isChange) {
				cylinder->vertexArray.clear();
				caculatorEmptyCylinder(cylinder->centerObject, cylinder->radiusUpOut, cylinder->radiusDownOut,
					cylinder->radiusUpIn, cylinder->radiusDownIn, cylinder->height, cylinder->numberLongitude,
					cylinder->numberLatitude, cylinder->vertexArray);
				CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
				return true;
			}
		}
				 break;
		case 17: {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					torus->depthRoundCake = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					torus->depthCake = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					torus->radiusCake = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					torus->radiusRoundCake = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					torus->widthCake = floatValue;
					isChange = true;
				}
			}

			if (isChange) {
				torus->vertexArray.clear();
				caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
					torus->centerObject, torus->vertexArray);
				CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
				return true;
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					object->numberLongitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				int intValue = getIntFromCharArray(menu_charNumberValue);
				if (intValue > 1 && intValue < 361) {
					object->numberLatitude = intValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					object->lengthBetween2Row = floatValue;
					isChange = true;
				}
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				float floatValue = getFloatFromCharArray(menu_charNumberValue);
				if (floatValue > 0.1 && floatValue < 1000.0) {
					object->lengthBetween2Column = floatValue;
					isChange = true;
				}
			}

			if (isChange) {
				object->vertexArray.clear();
				caculatorObjectCustom0(object->numberLongitude, object->numberLatitude, object->lengthBetween2Row, object->lengthBetween2Column,
					object->centerObject, object->vertexArray);
				CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
				return true;
			}
		}
				 break;
		default:
			break;
		}

		
		//đặt chế độ chỉnh về false
		menu_isChangeCharNumberValue = false;
	}
	return true;
}

//hàm lấy giá trị trong ô thuộc tính đang được chọn để chuyển thành mảng char
void getCharArrayFromValueAttribute(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	itemChoice item,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	//nếu không phải đang ở chế độ chỉnh sửa thì chuyển sang chế độ chỉnh sửa và lấy giá trị trong ô chuyển 
	//vào mảng menu_charNumberValue

	if (!menu_isChangeCharNumberValue) {

		switch (item.object)
		{
		case 10: {
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, sphere->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, sphere->numberLatitude);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, sphere->radius);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, sphere->degreeLongitudeLimit);
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, sphere->degreeLatitudeLimit);
			}
		}
				 break;
		case 11: {

		}
				 break;
		case 12: {
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cube->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cube->numberLatitude);
			}
		}
				 break;
		case 13: {
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cone->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cone->numberLatitude);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cone->height);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cone->radius);
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cone->degreeLongitudeLimit);
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cone->degreeLatitudeLimit);
			}
		}
				 break;
		case 14: {
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->numberLatitude);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->height);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusUp);
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusDown);
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->degreeLongitudeLimit);
			}
			else if (item_choice_in_MenuGroup2 == 6) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->degreeLatitudeLimit);
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->numberLatitude);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->height);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusUpOut);
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusDownOut);
			}
			else if (item_choice_in_MenuGroup2 == 5) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusUpIn);
			}
			else if (item_choice_in_MenuGroup2 == 6) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, cylinder->radiusDownIn);
			}
			else if (item_choice_in_MenuGroup2 == 7) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->degreeLongitudeLimit);
			}
			else if (item_choice_in_MenuGroup2 == 8) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, cylinder->degreeLatitudeLimit);
			}
		}
				 break;
		case 17: {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, torus->depthRoundCake);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, torus->depthCake);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, torus->radiusCake);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, torus->radiusRoundCake);
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, torus->widthCake);
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			if (item_choice_in_MenuGroup2 == 0) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, object->numberLongitude);
			}
			else if (item_choice_in_MenuGroup2 == 1) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberIntToCharArray(menu_charNumberValue, object->numberLatitude);
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, object->lengthBetween2Row);
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				//chuyển giá trị trong hộp sang mảng char
				changeNumberFloatToCharArray(menu_charNumberValue, object->lengthBetween2Column);
			}
		}
				 break;
		default:
			break;
		}


		//đặt chế độ chỉnh về true
		menu_isChangeCharNumberValue = true;
	}
}


//hàm tăng giảm giá trị các thuộc tính của object tại vị trí
bool plusAttributeObject(bool isPlus, itemChoice item,
	int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	vector<SphereAttribute*> &sphereArray, vector<CubeAttribute*> &cubeArray,
	vector<CubeRoundAttribute*> &cubeRoundArray, vector<ConeAttribute*> &coneArray,
	vector<CylinderAttribute*> &cylinderArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	bool isChangeValue = false;
	switch (item.object)
	{
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				sphere->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (sphere->numberLongitude > 2) {
					sphere->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				sphere->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (sphere->numberLatitude > 2) {
					sphere->numberLatitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				sphere->radius += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1f
				if (sphere->radius > 0.1f) {
					sphere->radius -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (sphere->degreeLongitudeLimit < 360) {
					sphere->degreeLongitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (sphere->degreeLongitudeLimit > 0) {
					sphere->degreeLongitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 4) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (sphere->degreeLatitudeLimit < 360) {
					sphere->degreeLatitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (sphere->degreeLatitudeLimit > 0) {
					sphere->degreeLatitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		
		if (isChangeValue) {
			sphere->vertexArray.clear();
			//tính toán lại
			CaculatorSphere(sphere->radius, sphere->numberLongitude, sphere->numberLatitude, sphere->centerObject,
				sphere->vertexArray);
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude, sphere->vertexArray, sphere->normalVector);
			return true;
		}
	}
			 break;
	case 11: {

	}
			 break;
	case 12: {
		CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				cube->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cube->numberLongitude > 2) {
					cube->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				cube->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cube->numberLatitude > 2) {
					cube->numberLatitude--;
					isChangeValue = true;
				}
			}
		}

		if (isChangeValue) {
			cube->vertexArray.clear();
			//tính toán lại
			CaculatorCubeRound(cube->xLength, cube->yLength, cube->zLength, cube->numberLongitude, cube->numberLatitude,
				cube->centerObject, cube->radiusRound, cube->vertexArray);
			CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude, cube->vertexArray, cube->normalVector);
			return true;
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				cone->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cone->numberLongitude > 2) {
					cone->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				cone->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cone->numberLatitude > 2) {
					cone->numberLatitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				cone->height += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cone->height > 0.1) {
					cone->height -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				cone->radius += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cone->radius > 0.1) {
					cone->radius -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 4) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cone->degreeLongitudeLimit < 360) {
					cone->degreeLongitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cone->degreeLongitudeLimit > 0) {
					cone->degreeLongitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 5) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cone->degreeLatitudeLimit < 360) {
					cone->degreeLatitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cone->degreeLatitudeLimit > 0) {
					cone->degreeLatitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		
		if (isChangeValue) {
			cone->vertexArray.clear();
			caculatorCone(cone->centerObject, cone->radius, cone->height, cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray);
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude, cone->vertexArray, cone->normalVector);
			return true;
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				cylinder->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cylinder->numberLongitude > 2) {
					cylinder->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				cylinder->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cylinder->numberLatitude > 2) {
					cylinder->numberLatitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				cylinder->height += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->height > 0.1) {
					cylinder->height -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				cylinder->radiusUp += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusUp > 0.1) {
					cylinder->radiusUp -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 4) {
			if (isPlus) {
				cylinder->radiusDown += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusDown > 0.1) {
					cylinder->radiusDown -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 5) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cylinder->degreeLongitudeLimit < 360) {
					cylinder->degreeLongitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cylinder->degreeLongitudeLimit > 0) {
					cylinder->degreeLongitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 6) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cylinder->degreeLatitudeLimit < 360) {
					cylinder->degreeLatitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cylinder->degreeLatitudeLimit > 0) {
					cylinder->degreeLatitudeLimit--;
					isChangeValue = true;
				}
			}
		}

		if (isChangeValue) {
			cylinder->vertexArray.clear();
			caculatorCylinder(cylinder->centerObject, cylinder->radiusUp, cylinder->radiusDown, cylinder->height,
				cylinder->numberLongitude, cylinder->numberLatitude, cylinder->vertexArray);
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
			return true;
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				cylinder->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cylinder->numberLongitude > 2) {
					cylinder->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				cylinder->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (cylinder->numberLatitude > 2) {
					cylinder->numberLatitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				cylinder->height += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->height > 0.1) {
					cylinder->height -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				cylinder->radiusUpOut += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusUpOut > 0.1) {
					cylinder->radiusUpOut -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 4) {
			if (isPlus) {
				cylinder->radiusDownOut += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusDownOut > 0.1) {
					cylinder->radiusDownOut -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 5) {
			if (isPlus) {
				cylinder->radiusUpIn += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusUpIn > 0.1) {
					cylinder->radiusUpIn -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 6) {
			if (isPlus) {
				cylinder->radiusDownIn += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (cylinder->radiusDownIn > 0.1) {
					cylinder->radiusDownIn -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 7) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cylinder->degreeLongitudeLimit < 360) {
					cylinder->degreeLongitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cylinder->degreeLongitudeLimit > 0) {
					cylinder->degreeLongitudeLimit--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 8) {
			if (isPlus) {
				//điều kiện là không được lớn hơn 360
				if (cylinder->degreeLatitudeLimit < 360) {
					cylinder->degreeLatitudeLimit++;
					isChangeValue = true;
				}
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0
				if (cylinder->degreeLatitudeLimit > 0) {
					cylinder->degreeLatitudeLimit--;
					isChangeValue = true;
				}
			}
		}

		if (isChangeValue) {
			cylinder->vertexArray.clear();
			caculatorEmptyCylinder(cylinder->centerObject, cylinder->radiusUpOut, cylinder->radiusDownOut,
				cylinder->radiusUpIn, cylinder->radiusDownIn, cylinder->height, cylinder->numberLongitude,
				cylinder->numberLatitude, cylinder->vertexArray);
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
			return true;
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus = torusArray.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				torus->depthRoundCake++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (torus->depthRoundCake > 2) {
					torus->depthRoundCake--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				torus->depthCake++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (torus->depthCake > 2) {
					torus->depthCake--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				torus->radiusCake += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (torus->radiusCake > 0.1) {
					torus->radiusCake -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				torus->radiusRoundCake += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (torus->radiusRoundCake > 0.1) {
					torus->radiusRoundCake -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 4) {
			if (isPlus) {
				torus->widthCake += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (torus->widthCake > 0.1) {
					torus->widthCake -= 0.01;
					isChangeValue = true;
				}
			}
		}

		if (isChangeValue) {
			torus->vertexArray.clear();
			caculatorTorus(torus->radiusCake, torus->radiusRoundCake, torus->widthCake, torus->depthCake, torus->depthRoundCake,
				torus->centerObject, torus->vertexArray);
			CaculatorNormalForTorus(torus->depthRoundCake, torus->vertexArray, torus->normalVector);
			return true;
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (item_choice_in_MenuGroup2 == 0) {
			if (isPlus) {
				object->numberLongitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (object->numberLongitude > 2) {
					object->numberLongitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			if (isPlus) {
				object->numberLatitude++;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 2
				if (object->numberLatitude > 2) {
					object->numberLatitude--;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 2) {
			if (isPlus) {
				object->lengthBetween2Row += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (object->lengthBetween2Row > 0.1) {
					object->lengthBetween2Row -= 0.01;
					isChangeValue = true;
				}
			}
		}
		else if (item_choice_in_MenuGroup2 == 3) {
			if (isPlus) {
				object->lengthBetween2Column += 0.01;
				isChangeValue = true;
			}
			else
			{
				//điều kiện là không được nhỏ hơn 0.1
				if (object->lengthBetween2Column > 0.1) {
					object->lengthBetween2Column -= 0.01;
					isChangeValue = true;
				}
			}
		}

		if (isChangeValue) {
			object->vertexArray.clear();
			caculatorObjectCustom0(object->numberLongitude, object->numberLatitude, object->lengthBetween2Row, object->lengthBetween2Column,
				object->centerObject, object->vertexArray);
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude, object->vertexArray, object->normalVector);
			return true;
		}
	}
			 break;
	default:
		break;
	}
	return false;
}
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
	vector<TorusAttribute*> &torusArray, vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//mảng chứa vị trí các item để kiểm tra
	point2D positionItem[9] = {
		{ leftMenu + 10, topMenu + 65 },
		{ leftMenu + 10, topMenu + 85 },
		{ leftMenu + 10, topMenu + 125 },
		{ leftMenu + 10, topMenu + 145 },
		{ leftMenu + 10, topMenu + 165 },
		{ leftMenu + 10, topMenu + 185 },
		{ leftMenu + 10, topMenu + 205 },
		{ leftMenu + 10, topMenu + 225 },
		{ leftMenu + 10, topMenu + 245 },
	};

	int numberItem = 0;

	switch (item.object)
	{
	case 10: {
		numberItem = 5;
	}
			 break;
	case 11: {
		numberItem = 0;
	}
			 break;
	case 12: {
		numberItem = 2;
	}
			 break;
	case 13: {
		numberItem = 6;
	}
			 break;
	case 14: {
		numberItem = 7;
	}
			 break;
	case 16: {
		numberItem = 9;
	}
			 break;
	case 17: {
		numberItem = 5;
	}
			 break;
	case 19:{
		numberItem = 4;
		
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		//kiểm tra xem có nhấn trúng nút tăng giảm chuỗi vertex nào không
		if (x > rightMenu - 85 && x<rightMenu - 55 && y>topMenu + 70 && y < topMenu + 80) {
			//thêm điều kiện là nếu mouseModel ==0 do nếu bằng 3 là có thể vừa thêm và chuột bị nhảy 2 lần
			if (mouseModel == 0) {
				//nhấn trúng nút tăng chuỗi vertex trên cùng
				AddVerticesAroundObjectCustom0(0, object,
					positionVerticesChoice);

				//đặt modelEditStyle = 1 để hiện chọn các vertex vừa thêm
				modelEditStyle = 1;
				//đặt mouseModel=3 để dịch chuyển các vertex vừa thêm
				mouseModel = 3;
				//lấy tâm dịch chuyển các vertex đang chọn luôn
				centerObjectOrVertices = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);

				return true;
			}
		}
		else if (x > rightMenu - 105 && x<rightMenu - 95 && y>topMenu + 85 && y < topMenu + 115) {
			//thêm điều kiện là nếu mouseModel ==0 do nếu bằng 3 là có thể vừa thêm và chuột bị nhảy 2 lần
			if (mouseModel == 0) {
				//nhấn trúng nút tăng chuỗi vertex trên cùng
				AddVerticesAroundObjectCustom0(1, object,
					positionVerticesChoice);

				//đặt modelEditStyle = 1 để hiện chọn các vertex vừa thêm
				modelEditStyle = 1;
				//đặt mouseModel=3 để dịch chuyển các vertex vừa thêm
				mouseModel = 3;
				//lấy tâm dịch chuyển các vertex đang chọn luôn
				centerObjectOrVertices = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);

				return true;
			}
		}
		else if (x > rightMenu - 85 && x<rightMenu - 55 && y>topMenu + 120 && y < topMenu + 130) {
			//thêm điều kiện là nếu mouseModel ==0 do nếu bằng 3 là có thể vừa thêm và chuột bị nhảy 2 lần
			if (mouseModel == 0) {
				//nhấn trúng nút tăng chuỗi vertex trên cùng
				AddVerticesAroundObjectCustom0(2, object,
					positionVerticesChoice);

				//đặt modelEditStyle = 1 để hiện chọn các vertex vừa thêm
				modelEditStyle = 1;
				//đặt mouseModel=3 để dịch chuyển các vertex vừa thêm
				mouseModel = 3;
				//lấy tâm dịch chuyển các vertex đang chọn luôn
				centerObjectOrVertices = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);

				return true;
			}
		}
		else if (x > rightMenu - 45 && x<rightMenu - 35 && y>topMenu + 85 && y < topMenu + 115) {
			//thêm điều kiện là nếu mouseModel ==0 do nếu bằng 3 là có thể vừa thêm và chuột bị nhảy 2 lần
			if (mouseModel == 0) {
				//nhấn trúng nút tăng chuỗi vertex trên cùng
				AddVerticesAroundObjectCustom0(3, object,
					positionVerticesChoice);

				//đặt modelEditStyle = 1 để hiện chọn các vertex vừa thêm
				modelEditStyle = 1;
				//đặt mouseModel=3 để dịch chuyển các vertex vừa thêm
				mouseModel = 3;
				//lấy tâm dịch chuyển các vertex đang chọn luôn
				centerObjectOrVertices = getPointCenterVertexesAtPosition(object->vertexArray, positionVerticesChoice);

				return true;
			}
		}
	}
			break;
	default:
		break;
	}

	for (int i = 0; i < numberItem; i++) {
		if (y > positionItem[i].y && y < positionItem[i].y + 10) {
			//nhấn trúng mũi tên trái
			if (x > positionItem[i].x + 90 && x < positionItem[i].x + 100) {
				//nếu đang có bất kỳ ô nào ở chế độ chỉnh sửa thì áp dụng chỉnh sửa đó
				if (menu_isChangeCharNumberValue) {
					return appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						item,
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
				//nếu không thì giảm giá trị
				else {
					return plusAttributeObject(false, item,
						i,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
			}
			//nhấn trúng mũi tên phải
			else if (x > positionItem[i].x + 170 && x < positionItem[i].x + 180) {
				//nếu đang có bất kỳ ô nào ở chế độ chỉnh sửa thì áp dụng chỉnh sửa đó
				if (menu_isChangeCharNumberValue) {
					return appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						item,
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
				//nếu không thì tăng giá trị
				else {
					return plusAttributeObject(true, item,
						i,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
				return true;
			}
			//nhấn trúng ô thông tin ở giữa
			else if (x > positionItem[i].x + 95 && x < positionItem[i].x + 165) {
				//nếu đang có bất kỳ ô nào ở chế độ chỉnh sửa thì áp dụng chỉnh sửa đó
				if (menu_isChangeCharNumberValue) {
					return appendCharArrayForValueAttribute(item_choice_in_MenuGroup2,
						menu_charNumberValue, menu_isChangeCharNumberValue,
						item,
						sphereArray, cubeArray, cubeRoundArray, coneArray,
						cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
				}
				else
				{
					//nếu ô thông tin đang chọn không phải là hộp đang được chọn thì đặt nó là hộp được chọn
					if (item_choice_in_MenuGroup2 != i) {
						item_choice_in_MenuGroup2 = i;
					}
					//nếu đã là hộp được chọn mà nhấn chọn tiếp thì chuyển sang chế độ chỉnh sửa
					else {
						getCharArrayFromValueAttribute(item_choice_in_MenuGroup2,
							menu_charNumberValue, menu_isChangeCharNumberValue,
							item,
							sphereArray, cubeArray, cubeRoundArray, coneArray,
							cylinderArray, emptyCylinderArray, torusArray, objectCustom0Array);
					}
				}
			}
		}
	}

	return false;
}

//hàm hiện các thông tin cần thay đổi để xử lý bo tròn góc các vật
void showToolChangeRoundEffect(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	bool isRoundCorned, int whichStyleRound, int numberVertexRound2Side, float radiusRound2Side,
	int numberVertexRoundHorizontal, int numberVertexRoundVertical, float radiusRoundHorizontal, float radiusRoundVertical,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	//nếu cột dịch chuyển qua lại giữa các menu được chọn thì hiện dấu chọn
	if (item_choice_in_MenuGroup2 == 0) {
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftMenu + 20, topMenu + 29);
		glVertex2f(leftMenu + 20, topMenu + 43);
		glVertex2f(leftMenu + 115, topMenu + 29);
		glVertex2f(leftMenu + 115, topMenu + 43);
		glEnd();
	}
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftMenu + 5, topMenu + 36);
	glVertex2f(leftMenu + 15, topMenu + 41);
	glVertex2f(leftMenu + 15, topMenu + 31);

	glVertex2f(leftMenu + 130, topMenu + 36);
	glVertex2f(leftMenu + 120, topMenu + 41);
	glVertex2f(leftMenu + 120, topMenu + 31);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(leftMenu + 135, topMenu + 37);
	glVertex2f(rightMenu - 10, topMenu + 37);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);

	//nếu kiểu bo góc là cùng 1 giá trị cho cả 2 chiều
	if (whichStyleRound == 0) {
		drawText(leftMenu + 20, topMenu + 40, "Round Both Side", "helvetica", 12);

		//hiện các giá trị cho việc bo tròn
		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusRound", menu_charNumberValue, leftMenu + 10, topMenu + 60);
			}
			else
			{
				drawMenuPlusMinus("RadiusRound", radiusRound2Side, true, leftMenu + 10, topMenu + 60);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusRound", radiusRound2Side, false, leftMenu + 10, topMenu + 60);
		}
		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("NumberVertex", menu_charNumberValue, leftMenu + 10, topMenu + 80);
			}
			else
			{
				drawMenuPlusMinus("NumberVertex", numberVertexRound2Side, true, leftMenu + 10, topMenu + 80);
			}
		}
		else
		{
			drawMenuPlusMinus("NumberVertex", numberVertexRound2Side, false, leftMenu + 10, topMenu + 80);
		}
	}
	//nếu kiểu bo góc là mỗi chiều theo 1 giá trị riêng
	else if (whichStyleRound == 1) {
		drawText(leftMenu + 18, topMenu + 40, "Round Each Side", "helvetica", 12);

		//hiện các giá trị cho việc bo tròn
		drawText(leftMenu + 10, topMenu + 60, "Horizontal", "helvetica", 12);
		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusRound", menu_charNumberValue, leftMenu + 10, topMenu + 70);
			}
			else
			{
				drawMenuPlusMinus("RadiusRound", radiusRoundHorizontal, true, leftMenu + 10, topMenu + 70);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusRound", radiusRoundHorizontal, false, leftMenu + 10, topMenu + 70);
		}

		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("NumberVertex", menu_charNumberValue, leftMenu + 10, topMenu + 90);
			}
			else
			{
				drawMenuPlusMinus("NumberVertex", numberVertexRoundHorizontal, true, leftMenu + 10, topMenu + 90);
			}
		}
		else
		{
			drawMenuPlusMinus("NumberVertex", numberVertexRoundHorizontal, false, leftMenu + 10, topMenu + 90);
		}

		drawText(leftMenu + 10, topMenu + 120, "Vertical", "helvetica", 12);
		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("RadiusRound", menu_charNumberValue, leftMenu + 10, topMenu + 130);
			}
			else
			{
				drawMenuPlusMinus("RadiusRound", radiusRoundVertical, true, leftMenu + 10, topMenu + 130);
			}
		}
		else
		{
			drawMenuPlusMinus("RadiusRound", radiusRoundVertical, false, leftMenu + 10, topMenu + 130);
		}

		if (item_choice_in_MenuGroup2 == 4) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("NumberVertex", menu_charNumberValue, leftMenu + 10, topMenu + 150);
			}
			else
			{
				drawMenuPlusMinus("NumberVertex", numberVertexRoundVertical, true, leftMenu + 10, topMenu + 150);
			}
		}
		else
		{
			drawMenuPlusMinus("NumberVertex", numberVertexRoundVertical, false, leftMenu + 10, topMenu + 150);
		}
	}

	//vẽ nút để áp dụng round corner
	glColor3f(0.4f, 0.45f, 0.45f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(rightMenu - 140, bottomMenu - 50);
	glVertex2f(rightMenu - 140, bottomMenu - 20);
	glVertex2f(rightMenu - 15, bottomMenu - 50);
	glVertex2f(rightMenu - 15, bottomMenu - 20);
	glEnd();
	//nếu nút này đang được chọn bằng cách nhấn phím mũi tên thì hiện 1 vòng thông báo
	if ((item_choice_in_MenuGroup2 == 3 && whichStyleRound == 0) || (item_choice_in_MenuGroup2 == 5 && whichStyleRound == 1)) {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(rightMenu - 140, bottomMenu - 50);
		glVertex2f(rightMenu - 140, bottomMenu - 20);
		glVertex2f(rightMenu - 15, bottomMenu - 20);
		glVertex2f(rightMenu - 15, bottomMenu - 50);
		glEnd();
	}

	glColor3f(0.0, 0.0, 0.0);
	if (isRoundCorned) {
		drawText(rightMenu - 130, bottomMenu - 30, "UnAp Round");
	}
	else
	{
		drawText(rightMenu - 130, bottomMenu - 30, "Apply Round");
	}

}
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueRound(int &whichStyleRound, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	int &numberVertexRound2Side, float &radiusRound2Side,
	int &numberVertexRoundHorizontal, int &numberVertexRoundVertical,
	float &radiusRoundHorizontal, float &radiusRoundVertical) {
	//nếu đang ở chế độ chỉnh sửa bằng char thì áp dung char thành số và tắt chế độ chỉnh sửa
	if (menu_isChangeCharNumberValue) {
		float val = getFloatFromCharArray(menu_charNumberValue);
		//phải đề phòng trường hợp số từ 1000 trở lên sẽ không hiển thị được
		if (val >= 1000) {
			val = 999.99f;
		}

		if (whichStyleRound == 0) {
			if (item_choice_in_MenuGroup2 == 1) {
				radiusRound2Side = val;
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				numberVertexRound2Side = (int)val;
			}
		}
		else if (whichStyleRound == 1) {
			if (item_choice_in_MenuGroup2 == 1) {
				radiusRoundHorizontal = val;
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				numberVertexRoundHorizontal = (int)val;
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				radiusRoundVertical = val;
			}
			else if (item_choice_in_MenuGroup2 == 4) {
				numberVertexRoundVertical = (int)val;
			}
		}
		//đặt chế độ chỉnh về false
		menu_isChangeCharNumberValue = false;
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//đầu tiên phải kiểm tra điều kiện xem có sai phạm gì không
	//bán kính bo phải lớn hơn 0.01 && vertexAdd phải lớn hơn hoặc bằng 2
	if (whichStyleRound == 0) {
		if (radiusRound2Side < 0.01 || numberVertexRound2Side < 2)
			return;
	}
	else {
		if (radiusRoundHorizontal < 0.01 || numberVertexRoundHorizontal < 2 ||
			radiusRoundVertical < 0.01 || numberVertexRoundVertical < 2)
			return;
	}

	isRoundCorner = !isRoundCorner;
	int numberObject;
	if (isRoundCorner) {
		//bo tròn tất cả các triangle strip
		numberObject = triaStripArray.size();
		for (int i = 0; i < numberObject; i++) {
			//triaStrip chỉ có 1 hướng bo
			if (whichStyleRound == 0) {
				roundEdgeTriaStrip(triaStripArray.at(i), radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeTriaStrip(triaStripArray.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal);
			}
		}
		numberObject = sphereArray.size();
		for (int i = 0; i < numberObject; i++) {
			if (whichStyleRound == 0) {
				roundEdgeSphere(sphereArray.at(i), radiusRound2Side, numberVertexRound2Side,
					radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeSphere(sphereArray.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal,
					radiusRoundVertical, numberVertexRoundVertical);
			}
		}
		numberObject = coneArray.size();
		for (int i = 0; i < numberObject; i++) {
			if (whichStyleRound == 0) {
				roundEdgeCone(coneArray.at(i), radiusRound2Side, numberVertexRound2Side,
					radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeCone(coneArray.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal,
					radiusRoundVertical, numberVertexRoundVertical);
			}
		}
		numberObject = cylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			if (whichStyleRound == 0) {
				roundEdgeCylinder(cylinderArray.at(i), radiusRound2Side, numberVertexRound2Side,
					radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeCylinder(cylinderArray.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal,
					radiusRoundVertical, numberVertexRoundVertical);
			}
		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			if (whichStyleRound == 0) {
				roundEdgeEmptyCylinder(emptyCylinderArray.at(i), radiusRound2Side, numberVertexRound2Side,
					radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeEmptyCylinder(emptyCylinderArray.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal,
					radiusRoundVertical, numberVertexRoundVertical);
			}
		}
		numberObject = objectCustom0Array.size();
		for (int i = 0; i < numberObject; i++) {
			if (whichStyleRound == 0) {
				roundEdgeObjectCustom0(objectCustom0Array.at(i), radiusRound2Side, numberVertexRound2Side,
					radiusRound2Side, numberVertexRound2Side);
			}
			else
			{
				roundEdgeObjectCustom0(objectCustom0Array.at(i), radiusRoundHorizontal, numberVertexRoundHorizontal,
					radiusRoundVertical, numberVertexRoundVertical);
			}
		}

	}
	//nếu chuyển sang chế độ không bo tròn thì xóa hết các dữ liệu vertex và normalRound đi
	else
	{
		//xóa tất cả các vertexRound cũng như normalRoundcuar triangle strip
		numberObject = triaStripArray.size();
		for (int i = 0; i < numberObject; i++) {
			triaStripArray.at(i)->vertexArrayRound.clear();
			triaStripArray.at(i)->normalVectorRound.clear();
		}
		numberObject = sphereArray.size();
		for (int i = 0; i < numberObject; i++) {
			sphereArray.at(i)->vertexArrayRound.clear();
			sphereArray.at(i)->normalVectorRound.clear();
		}
		numberObject = coneArray.size();
		for (int i = 0; i < numberObject; i++) {
			coneArray.at(i)->vertexArrayRound.clear();
			coneArray.at(i)->normalVectorRound.clear();
		}
		numberObject = cylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			cylinderArray.at(i)->vertexArrayRound.clear();
			cylinderArray.at(i)->normalVectorRound.clear();
		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			emptyCylinderArray.at(i)->vertexArrayRound.clear();
			emptyCylinderArray.at(i)->normalVectorRound.clear();
		}
		numberObject = objectCustom0Array.size();
		for (int i = 0; i < numberObject; i++) {
			objectCustom0Array.at(i)->vertexArrayRound.clear();
			objectCustom0Array.at(i)->normalVectorRound.clear();
		}
	}
}
//hàm chọn các thông tin cũng như áp dụng bo tròn góc của tất cả các hình
bool checkToApplyRound(int x, int y, int &item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	bool &isRoundCorner, int &whichStyleRound,
	int &numberVertexRound2Side, float &radiusRound2Side,
	int &numberVertexRoundHorizontal, int &numberVertexRoundVertical, float &radiusRoundHorizontal, float &radiusRoundVertical,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu,
	vector<TriangleAttribute*> &triangleArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	//xác định có nhấn nút chuyển kiểu bo tròn không
	if (x > leftMenu + 5 && x< leftMenu + 15 && y > topMenu + 31 && y < topMenu + 41) {
		appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical,
			radiusRoundHorizontal, radiusRoundVertical);
		if (whichStyleRound == 0) {
			whichStyleRound = 1;
		}
		else if (whichStyleRound == 1) {
			whichStyleRound = 0;
		}
		item_choice_in_MenuGroup2 = -1;
		return true;
	}
	else if (x > leftMenu + 120 && x< leftMenu + 130 && y>topMenu + 31 && y < topMenu + 41) {
		appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical,
			radiusRoundHorizontal, radiusRoundVertical);
		if (whichStyleRound == 0) {
			whichStyleRound = 1;
		}
		else if (whichStyleRound == 1) {
			whichStyleRound = 0;
		}
		item_choice_in_MenuGroup2 = -1;
		return true;
	}
	else
	{
		//xác định nút được nhấn (tùy theo kiểu bo để xác định các nút nhấn khác nhau)
		if (whichStyleRound == 0) {
			//leftMenu + 10, topMenu + 60            leftMenu + 10, topMenu + 80
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRound2Side -= 0.01f;
				if (radiusRound2Side < 0.1f) {
					radiusRound2Side = 0.1f;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 60 && y < topMenu + 70) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRound2Side += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRound2Side -= 1;
				if (numberVertexRound2Side < 2) {
					numberVertexRound2Side = 2;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 80 && y < topMenu + 90) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRound2Side += 1;
				return true;
			}
		}
		else if (whichStyleRound == 1) {
			//leftMenu + 10, topMenu + 70        leftMenu + 10, topMenu + 90
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 70 && y < topMenu + 80) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRoundHorizontal -= 0.01f;
				if (radiusRoundHorizontal < 0.1f) {
					radiusRoundHorizontal = 0.1f;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 70 && y < topMenu + 80) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRoundHorizontal += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 90 && y < topMenu + 100) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRoundHorizontal -= 1;
				if (numberVertexRoundHorizontal < 2) {
					numberVertexRoundHorizontal = 2;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 90 && y < topMenu + 100) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRoundHorizontal += 1;
				return true;
			}
			//leftMenu + 10, topMenu + 130       leftMenu + 10, topMenu + 150
			if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 130 && y < topMenu + 140) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRoundVertical -= 0.01f;
				if (radiusRoundVertical < 0.1f) {
					radiusRoundVertical = 0.1f;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 130 && y < topMenu + 140) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				radiusRoundVertical += 0.01f;
				return true;
			}
			else if (x > leftMenu + 10 + 90 && x< leftMenu + 10 + 100 && y > topMenu + 150 && y < topMenu + 160) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRoundVertical -= 1;
				if (numberVertexRoundVertical < 2) {
					numberVertexRoundVertical = 2;
				}
				return true;
			}
			else if (x > leftMenu + 10 + 170 && x< leftMenu + 10 + 180 && y > topMenu + 150 && y < topMenu + 160) {
				appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
					menu_charNumberValue, menu_isChangeCharNumberValue,
					numberVertexRound2Side, radiusRound2Side,
					numberVertexRoundHorizontal, numberVertexRoundVertical,
					radiusRoundHorizontal, radiusRoundVertical);
				numberVertexRoundVertical += 1;
				return true;
			}
		}
	}

	//kiểm tra xem có nhấn trúng nút áp dụng bo tròn không
	if (x > rightMenu - 140 && x<rightMenu - 15 && y>bottomMenu - 50 && y < bottomMenu - 20) {
		appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical,
			radiusRoundHorizontal, radiusRoundVertical);
		appendRoundInMenu(isRoundCorner, whichStyleRound,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical, radiusRoundHorizontal, radiusRoundVertical,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

		return true;
	}
	//nếu không chọn trúng bất kỳ nút nào thì kiểm tra xem có chọn trúng các menu không
	if (x > leftMenu + 20 && x< leftMenu + 115 && y > topMenu + 31 && y < topMenu + 41) {
		appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			numberVertexRound2Side, radiusRound2Side,
			numberVertexRoundHorizontal, numberVertexRoundVertical,
			radiusRoundHorizontal, radiusRoundVertical);
		item_choice_in_MenuGroup2 = 0;
		return true;
	}
	if (whichStyleRound == 0) {
		if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 60 && y < topMenu + 70) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 1 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberFloatToCharArray(menu_charNumberValue, radiusRound2Side);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 1;
			return true;
		}
		else if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 80 && y < topMenu + 90) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 2 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberIntToCharArray(menu_charNumberValue, numberVertexRound2Side);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 2;
			return true;
		}
	}
	else if (whichStyleRound == 1) {
		if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 70 && y < topMenu + 80) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 1 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberFloatToCharArray(menu_charNumberValue, radiusRoundHorizontal);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 1;
			return true;
		}
		else if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 90 && y < topMenu + 100) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 2 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberIntToCharArray(menu_charNumberValue, numberVertexRoundHorizontal);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 2;
			return true;
		}
		else if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 130 && y < topMenu + 140) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 3 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberFloatToCharArray(menu_charNumberValue, radiusRoundVertical);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 3;
			return true;
		}
		else if (x > leftMenu + 10 + 95 && x< leftMenu + 10 + 165 && y > topMenu + 150 && y < topMenu + 160) {
			appendCharArrayForValueRound(whichStyleRound, item_choice_in_MenuGroup2,
				menu_charNumberValue, menu_isChangeCharNumberValue,
				numberVertexRound2Side, radiusRound2Side,
				numberVertexRoundHorizontal, numberVertexRoundVertical,
				radiusRoundHorizontal, radiusRoundVertical);
			//nếu trước đó đang chọn menu này thì bây giờ chuyển sang chế độ chỉnh sửa
			if (item_choice_in_MenuGroup2 == 4 && !menu_isChangeCharNumberValue) {
				//xóa các giá trị trong mảng để dùng lại
				memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
				changeNumberIntToCharArray(menu_charNumberValue, numberVertexRoundVertical);
				menu_isChangeCharNumberValue = true;
			}
			item_choice_in_MenuGroup2 = 4;
			return true;
		}
	}

	return false;
}

//hàm hiên thông tin về các biến đổi muốn áp dụng(translate,rotate,scale)
void showToolTransform(int whichTransform, int item_choice_in_MenuGroup2, char *menu_charNumberValue,
	bool menu_isChangeCharNumberValue,
	float translateX, float translateY, float translateZ, float rotateX,
	float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	//nếu cột dịch chuyển qua lại giữa các menu được chọn thì hiện dấu chọn
	if (item_choice_in_MenuGroup2 == 0) {
		glColor3f(0.2, 0.2, 0.2);
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(leftMenu + 20, topMenu + 29);
		glVertex2f(leftMenu + 20, topMenu + 43);
		glVertex2f(leftMenu + 115, topMenu + 29);
		glVertex2f(leftMenu + 115, topMenu + 43);
		glEnd();
	}
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftMenu + 5, topMenu + 36);
	glVertex2f(leftMenu + 15, topMenu + 41);
	glVertex2f(leftMenu + 15, topMenu + 31);

	glVertex2f(leftMenu + 130, topMenu + 36);
	glVertex2f(leftMenu + 120, topMenu + 41);
	glVertex2f(leftMenu + 120, topMenu + 31);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(leftMenu + 135, topMenu + 37);
	glVertex2f(rightMenu - 10, topMenu + 37);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//nếu kiểu bo góc là cùng 1 giá trị cho cả 2 chiều
	if (whichTransform == 0) {
		drawText(leftMenu + 40, topMenu + 40, "Translate", "helvetica", 12);

		//hiện các giá trị cho việc dịch chuyển
		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Translate X", menu_charNumberValue, leftMenu + 10, topMenu + 60);
			}
			else
			{
				drawMenuPlusMinus("Translate X", translateX, true, leftMenu + 10, topMenu + 60);
			}
		}
		else
		{
			drawMenuPlusMinus("Translate X", translateX, false, leftMenu + 10, topMenu + 60);
		}

		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Translate Y", menu_charNumberValue, leftMenu + 10, topMenu + 80);
			}
			else
			{
				drawMenuPlusMinus("Translate Y", translateY, true, leftMenu + 10, topMenu + 80);
			}
		}
		else
		{
			drawMenuPlusMinus("Translate Y", translateY, false, leftMenu + 10, topMenu + 80);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Translate Z", menu_charNumberValue, leftMenu + 10, topMenu + 100);
			}
			else
			{
				drawMenuPlusMinus("Translate Z", translateZ, true, leftMenu + 10, topMenu + 100);
			}
		}
		else
		{
			drawMenuPlusMinus("Translate Z", translateZ, false, leftMenu + 10, topMenu + 100);
		}
	}
	else if (whichTransform == 1) {
		drawText(leftMenu + 45, topMenu + 40, "Rotate", "helvetica", 12);

		//hiện các giá trị cho việc xoay
		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Rotate X", menu_charNumberValue, leftMenu + 10, topMenu + 60);
			}
			else
			{
				drawMenuPlusMinus("Rotate X", rotateX, true, leftMenu + 10, topMenu + 60);
			}
		}
		else
		{
			drawMenuPlusMinus("Rotate X", rotateX, false, leftMenu + 10, topMenu + 60);
		}

		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Rotate Y", menu_charNumberValue, leftMenu + 10, topMenu + 80);
			}
			else
			{
				drawMenuPlusMinus("Rotate Y", rotateY, true, leftMenu + 10, topMenu + 80);
			}
		}
		else
		{
			drawMenuPlusMinus("Rotate Y", rotateY, false, leftMenu + 10, topMenu + 80);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Rotate Z", menu_charNumberValue, leftMenu + 10, topMenu + 100);
			}
			else
			{
				drawMenuPlusMinus("Rotate Z", rotateZ, true, leftMenu + 10, topMenu + 100);
			}
		}
		else
		{
			drawMenuPlusMinus("Rotate Z", rotateZ, false, leftMenu + 10, topMenu + 100);
		}
	}
	else if (whichTransform == 2) {
		drawText(leftMenu + 47, topMenu + 40, "Scale", "helvetica", 12);
		glBegin(GL_LINES);
		glVertex2f(leftMenu + 135, topMenu + 37);
		glVertex2f(rightMenu - 10, topMenu + 37);
		glEnd();

		//hiện các giá trị cho việc scale
		if (item_choice_in_MenuGroup2 == 1) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Scale X", menu_charNumberValue, leftMenu + 10, topMenu + 60);
			}
			else
			{
				drawMenuPlusMinus("Scale X", scaleX, true, leftMenu + 10, topMenu + 60);
			}
		}
		else
		{
			drawMenuPlusMinus("Scale X", scaleX, false, leftMenu + 10, topMenu + 60);
		}

		if (item_choice_in_MenuGroup2 == 2) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Scale Y", menu_charNumberValue, leftMenu + 10, topMenu + 80);
			}
			else
			{
				drawMenuPlusMinus("Scale Y", scaleY, true, leftMenu + 10, topMenu + 80);
			}
		}
		else
		{
			drawMenuPlusMinus("Scale Y", scaleY, false, leftMenu + 10, topMenu + 80);
		}

		if (item_choice_in_MenuGroup2 == 3) {
			if (menu_isChangeCharNumberValue) {
				drawMenuPlusMinus("Scale Z", menu_charNumberValue, leftMenu + 10, topMenu + 100);
			}
			else
			{
				drawMenuPlusMinus("Scale Z", scaleZ, true, leftMenu + 10, topMenu + 100);
			}
		}
		else
		{
			drawMenuPlusMinus("Scale Z", scaleZ, false, leftMenu + 10, topMenu + 100);
		}
	}

	//vẽ nút để áp dụng biến đổi transform hiện tại
	glColor3f(0.4f, 0.45f, 0.45f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(rightMenu - 140, bottomMenu - 50);
	glVertex2f(rightMenu - 140, bottomMenu - 20);
	glVertex2f(rightMenu - 15, bottomMenu - 50);
	glVertex2f(rightMenu - 15, bottomMenu - 20);
	glEnd();
	//nếu nút này đang được chọn bằng cách nhấn phím mũi tên thì hiện 1 vòng thông báo
	if (item_choice_in_MenuGroup2 == 4) {
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(rightMenu - 140, bottomMenu - 50);
		glVertex2f(rightMenu - 140, bottomMenu - 20);
		glVertex2f(rightMenu - 15, bottomMenu - 20);
		glVertex2f(rightMenu - 15, bottomMenu - 50);
		glEnd();
	}

	glColor3f(0.0, 0.0, 0.0);
	drawText(rightMenu - 130, bottomMenu - 30, "Apply Trans");

}
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueTransform(int whichTransform, int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	float &translateX, float &translateY, float &translateZ, float &rotateX,
	float &rotateY, float &rotateZ, float &scaleX, float &scaleY, float &scaleZ) {
	//nếu đang ở chế độ chỉnh sửa bằng char thì áp dung char thành số và tắt chế độ chỉnh sửa
	if (menu_isChangeCharNumberValue) {
		float val = getFloatFromCharArray(menu_charNumberValue);
		//phải đề phòng trường hợp số từ 1000 trở lên sẽ không hiển thị được
		if (val >= 1000) {
			val = 999.99f;
		}

		if (whichTransform == 0) {
			if (item_choice_in_MenuGroup2 == 1) {
				translateX = val;
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				translateY = val;
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				translateZ = val;
			}
		}
		else if (whichTransform == 1) {
			if (item_choice_in_MenuGroup2 == 1) {
				rotateX = val;
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				rotateY = val;
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				rotateZ = val;
			}
		}
		else if (whichTransform == 2) {
			if (item_choice_in_MenuGroup2 == 1) {
				scaleX = val;
			}
			else if (item_choice_in_MenuGroup2 == 2) {
				scaleY = val;
			}
			else if (item_choice_in_MenuGroup2 == 3) {
				scaleZ = val;
			}
		}
		//đặt chế độ chỉnh về false
		menu_isChangeCharNumberValue = false;
	}
}
//hàm hiện thông tin cho symmetryVertices
void showInformationSymmetryVertices(int whichStyleSymmetry, int whichItemSymmetry,
	vector<SymmetryVertices> symmetryVertices,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {

	int topSymmetry2 = ((bottomMenu - 110) + (topMenu + 220)) / 2;
	//vẽ nút hiện whichItemSymmetry đang chọn
	glColor3f(0.4f, 0.45f, 0.45f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 82, topMenu + 72);
	glVertex2f(leftMenu + 82, topMenu + 83);
	glVertex2f(leftMenu + 247, topMenu + 72);
	glVertex2f(leftMenu + 247, topMenu + 83);
	glEnd();

	//vẽ các button cài đặt vertex symmetry 1
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topMenu + 225);
	glVertex2f(leftMenu + 5, topMenu + 242);
	glVertex2f(leftMenu + 55, topMenu + 225);
	glVertex2f(leftMenu + 55, topMenu + 242);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topMenu + 244);
	glVertex2f(leftMenu + 5, topMenu + 260);
	glVertex2f(leftMenu + 55, topMenu + 244);
	glVertex2f(leftMenu + 55, topMenu + 260);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topMenu + 262);
	glVertex2f(leftMenu + 5, topMenu + 279);
	glVertex2f(leftMenu + 55, topMenu + 262);
	glVertex2f(leftMenu + 55, topMenu + 279);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topMenu + 225);
	glVertex2f(leftMenu + 58, topMenu + 242);
	glVertex2f(leftMenu + 118, topMenu + 225);
	glVertex2f(leftMenu + 118, topMenu + 242);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topMenu + 244);
	glVertex2f(leftMenu + 58, topMenu + 260);
	glVertex2f(leftMenu + 118, topMenu + 244);
	glVertex2f(leftMenu + 118, topMenu + 260);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topMenu + 262);
	glVertex2f(leftMenu + 58, topMenu + 279);
	glVertex2f(leftMenu + 118, topMenu + 262);
	glVertex2f(leftMenu + 118, topMenu + 279);
	glEnd();
	//vẽ các button cài đặt vertex symmetry 2
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topSymmetry2 + 5);
	glVertex2f(leftMenu + 5, topSymmetry2 + 22);
	glVertex2f(leftMenu + 55, topSymmetry2 + 5);
	glVertex2f(leftMenu + 55, topSymmetry2 + 22);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topSymmetry2 + 24);
	glVertex2f(leftMenu + 5, topSymmetry2 + 40);
	glVertex2f(leftMenu + 55, topSymmetry2 + 24);
	glVertex2f(leftMenu + 55, topSymmetry2 + 40);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topSymmetry2 + 42);
	glVertex2f(leftMenu + 5, topSymmetry2 + 59);
	glVertex2f(leftMenu + 55, topSymmetry2 + 42);
	glVertex2f(leftMenu + 55, topSymmetry2 + 59);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topSymmetry2 + 5);
	glVertex2f(leftMenu + 58, topSymmetry2 + 22);
	glVertex2f(leftMenu + 118, topSymmetry2 + 5);
	glVertex2f(leftMenu + 118, topSymmetry2 + 22);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topSymmetry2 + 24);
	glVertex2f(leftMenu + 58, topSymmetry2 + 40);
	glVertex2f(leftMenu + 118, topSymmetry2 + 24);
	glVertex2f(leftMenu + 118, topSymmetry2 + 40);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 58, topSymmetry2 + 42);
	glVertex2f(leftMenu + 58, topSymmetry2 + 59);
	glVertex2f(leftMenu + 118, topSymmetry2 + 42);
	glVertex2f(leftMenu + 118, topSymmetry2 + 59);
	glEnd();
	//vẽ button lấy các item từ 2 item bắt đầu và item kết thúc
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(rightMenu - 110, bottomMenu - 95);
	glVertex2f(rightMenu - 110, bottomMenu - 65);
	glVertex2f(rightMenu - 10, bottomMenu - 95);
	glVertex2f(rightMenu - 10, bottomMenu - 65);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(rightMenu - 110, bottomMenu - 35);
	glVertex2f(rightMenu - 110, bottomMenu - 5);
	glVertex2f(rightMenu - 10, bottomMenu - 35);
	glVertex2f(rightMenu - 10, bottomMenu - 5);
	glEnd();


	int offset0 = 82 + (whichStyleSymmetry * 55),
		offset1 = 82 + ((whichStyleSymmetry + 1) * 55);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + offset0, topMenu + 70);
	glVertex2f(leftMenu + offset0, topMenu + 85);
	glVertex2f(leftMenu + offset1, topMenu + 70);
	glVertex2f(leftMenu + offset1, topMenu + 85);
	glEnd();

	drawText(leftMenu + 5, topMenu + 80, "Symmetry", "helvetica", 12);
	drawText(leftMenu + 92, topMenu + 62, "Vertex", "helvetica", 12);
	drawText(leftMenu + 150, topMenu + 62, "Row", "helvetica", 12);
	drawText(leftMenu + 198, topMenu + 62, "Column", "helvetica", 12);

	//hiện ra các item của symmetryVertice
	drawText(leftMenu + 6, topMenu + 175, "WhichItemSymmetry :", "helvetica", 12);
	//in ra các item có trong symmetryVertice và hiện ra hình chữ nhật chọn tại item 
	//mà có chứa thông tin về đối tượng đang được chọn(nếu có)
	int numberElement = symmetryVertices.size(), leftItemNow, topItemNow, maxRight, numberNow;
	char charNumber[10];
	leftItemNow = leftMenu + 128;
	topItemNow = topMenu + 177;
	maxRight = rightMenu - 20;
	for (int i = 0; i < numberElement; i++) {
		changeNumberIntToCharArray(charNumber, i);
		//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
		if (i < 10) {
			//tùy theo kích thước của chữ để vẽ hình chữ nhật bao phù hợp nếu item này là item được chọn
			if (i == whichItemSymmetry) {
				glColor3f(0.1, 0.1, 0.1);
				glBegin(GL_TRIANGLE_STRIP);
				glVertex2f(leftItemNow - 4, topItemNow - 11);
				glVertex2f(leftItemNow - 4, topItemNow + 2);
				glVertex2f(leftItemNow + 10, topItemNow - 11);
				glVertex2f(leftItemNow + 10, topItemNow + 2);
				glEnd();
				glColor3f(1.0, 1.0, 1.0);
			}
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 12;
		}
		else if (i < 100) {
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 20;
		}
		else if (i < 1000) {
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 28;
		}
		else
		{
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 36;
		}
	}

	//hiện các vị trí đối xứng và các menu chọn
	if (whichStyleSymmetry == 0) {
		drawText(leftMenu + 6, topMenu + 220, "Vertices Symmetry1:", "helvetica", 12);
		drawText(leftMenu + 6, topSymmetry2, "Vertices Symmetry2:", "helvetica", 12);
	}
	else if (whichStyleSymmetry == 1) {
		drawText(leftMenu + 6, topMenu + 220, "Row Symmetry1:", "helvetica", 12);
		drawText(leftMenu + 6, topSymmetry2, "Row Symmetry2:", "helvetica", 12);
	}
	else if (whichStyleSymmetry == 2) {
		drawText(leftMenu + 6, topMenu + 220, "Column Symmetry1:", "helvetica", 12);
		drawText(leftMenu + 6, topSymmetry2, "Column Symmetry2:", "helvetica", 12);
	}

	//hiện tên các menu cho vertices Symmetry 1
	drawText(leftMenu + 20, topMenu + 238, "Get", "helvetica", 12);
	drawText(leftMenu + 8, topMenu + 256, "Reverse", "helvetica", 12);
	drawText(leftMenu + 12, topMenu + 274, "Delete", "helvetica", 12);
	drawText(leftMenu + 59, topMenu + 238, "Arrange U", "helvetica", 12);
	drawText(leftMenu + 59, topMenu + 256, "Arrange D", "helvetica", 12);
	drawText(leftMenu + 61, topMenu + 274, "Delete All", "helvetica", 12);
	//hiện tên các menu cho vertices Symmetry 2
	drawText(leftMenu + 20, topSymmetry2 + 18, "Get", "helvetica", 12);
	drawText(leftMenu + 8, topSymmetry2 + 36, "Reverse", "helvetica", 12);
	drawText(leftMenu + 12, topSymmetry2 + 54, "Delete", "helvetica", 12);
	drawText(leftMenu + 59, topSymmetry2 + 18, "Arrange U", "helvetica", 12);
	drawText(leftMenu + 59, topSymmetry2 + 36, "Arrange D", "helvetica", 12);
	drawText(leftMenu + 61, topSymmetry2 + 54, "Delete All", "helvetica", 12);

	//hiện các thông tin về lấy cụm vertex,row hay column từ item đầu và cuối
	drawText(leftMenu + 8, bottomMenu - 110, "Symmetry1:", "helvetica", 12);
	drawText(leftMenu + 5, bottomMenu - 90, "Start:", "helvetica", 12);
	drawText(leftMenu + 5, bottomMenu - 70, "End:", "helvetica", 12);
	drawText(rightMenu - 80, bottomMenu - 77, "Get all", "helvetica", 12);
	drawMenuGetValue(startAndEndSymmetry1[0], false,
		leftMenu + 40, bottomMenu - 98);
	drawMenuGetValue(startAndEndSymmetry1[1], false,
		leftMenu + 40, bottomMenu - 78);
	drawMenuOffOn("GetLikeClockwise", isGetSymmetryLikeClockwise1,
		rightMenu - 160, bottomMenu - 117);

	drawText(leftMenu + 8, bottomMenu - 50, "Symmetry2:", "helvetica", 12);
	drawText(leftMenu + 5, bottomMenu - 30, "Start:", "helvetica", 12);
	drawText(leftMenu + 5, bottomMenu - 10, "End:", "helvetica", 12);
	drawText(rightMenu - 80, bottomMenu - 17, "Get all", "helvetica", 12);
	drawMenuGetValue(startAndEndSymmetry2[0], false,
		leftMenu + 40, bottomMenu - 38);
	drawMenuGetValue(startAndEndSymmetry2[1], false,
		leftMenu + 40, bottomMenu - 18);
	drawMenuOffOn("GetLikeClockwise", isGetSymmetryLikeClockwise2,
		rightMenu - 160, bottomMenu - 57);

	//whichItemSymetry phải khác -1
	if (whichItemSymmetry != -1) {
		SymmetryVertices symmeytryNow = symmetryVertices.at(whichItemSymmetry);

		//hiện tất cả vertex của Symmetry1
		leftItemNow = leftMenu + 124;
		topItemNow = topMenu + 220;
		maxRight = rightMenu - 20;
		if (whichStyleSymmetry == 0) {
			numberElement = symmeytryNow.positionVertices1.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
					//kiểm tra xem đã đến giới hạn dưới chưa,nếu chưa thì tiếp tụ còn nếu rồi thì 
					//in ra dấu 3 chấm và kết thúc vòng lặp
					if (topItemNow > topSymmetry2 - 40) {
						drawText(leftItemNow, topItemNow, ". . .", "helvetica", 12);
						break;
					}
				}
				numberNow = symmeytryNow.positionVertices1.at(i);
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}
		else if (whichStyleSymmetry == 1) {
			numberElement = symmeytryNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
				}
				numberNow = symmeytryNow.positionROrC1.at(i).positionRow;
				//nếu chỉ cần 1 item = -1 nghĩa là toàn bộ bằng -1 (giá trị được đặt cho column)
				if (numberNow == -1)
					break;
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}
		else if (whichStyleSymmetry == 2)
		{
			numberElement = symmeytryNow.positionROrC1.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
				}
				numberNow = symmeytryNow.positionROrC1.at(i).positionColumn;
				//nếu chỉ cần 1 item = -1 nghĩa là toàn bộ bằng -1 (giá trị được đặt cho row)
				if (numberNow == -1)
					break;
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}

		//hiện tất cả vertex của Symmetry2
		leftItemNow = leftMenu + 124;
		topItemNow = topSymmetry2;
		maxRight = rightMenu - 20;
		if (whichStyleSymmetry == 0) {
			numberElement = symmeytryNow.positionVertices2.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
					//kiểm tra xem đã đến giới hạn dưới chưa,nếu chưa thì tiếp tụ còn nếu rồi thì 
					//in ra dấu 3 chấm và kết thúc vòng lặp
					if (topItemNow > (bottomMenu - 150)) {
						drawText(leftItemNow, topItemNow, ". . .", "helvetica", 12);
						break;
					}
				}
				numberNow = symmeytryNow.positionVertices2.at(i);
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}
		else if (whichStyleSymmetry == 1) {
			numberElement = symmeytryNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
				}
				numberNow = symmeytryNow.positionROrC2.at(i).positionRow;
				//nếu chỉ cần 1 item = -1 nghĩa là toàn bộ bằng -1 (giá trị được đặt cho column)
				if (numberNow == -1)
					break;
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}
		else if (whichStyleSymmetry == 2)
		{
			numberElement = symmeytryNow.positionROrC2.size();
			for (int i = 0; i < numberElement; i++) {
				//nếu đến max item thì xuống dòng
				if (leftItemNow > maxRight) {
					leftItemNow = leftMenu + 124;
					topItemNow += 20;
				}
				numberNow = symmeytryNow.positionROrC2.at(i).positionColumn;
				//nếu chỉ cần 1 item = -1 nghĩa là toàn bộ bằng -1 (giá trị được đặt cho row)
				if (numberNow == -1)
					break;
				changeNumberIntToCharArray(charNumber, numberNow);
				drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
				//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
				if (numberNow < 10) {
					leftItemNow += 12;
				}
				else if (numberNow < 100) {
					leftItemNow += 20;
				}
				else if (numberNow < 1000) {
					leftItemNow += 28;
				}
				else
				{
					leftItemNow += 36;
				}
			}
		}
	}
}
//hàm lấy ra tên của các hình từ giá trị tên bằng số
void getCharNameByIntName(char *charArray, int object) {

	switch (object)
	{
	case 3: {
		strcpy_s(charArray, 20, "Triangle");
	}
			break;
	case 4: {
		strcpy_s(charArray, 20, "Triangle Strip");
	}
			break;
	case 5: {
		strcpy_s(charArray, 20, "Triangle Fan");
	}
			break;
	case 10: {
		strcpy_s(charArray, 20, "Sphere");
	}
			 break;
	case 11: {
		strcpy_s(charArray, 20, "Cube");
	}
			 break;
	case 12: {
		strcpy_s(charArray, 20, "Cube Round");
	}
			 break;
	case 13: {
		strcpy_s(charArray, 20, "Cone");
	}
			 break;
	case 14: {
		strcpy_s(charArray, 20, "Cylinder");
	}
			 break;
	case 15: {
		strcpy_s(charArray, 20, "Pyramid");
	}
			 break;
	case 16: {
		strcpy_s(charArray, 20, "Empty Cylinder");
	}
			 break;
	case 17: {
		strcpy_s(charArray, 20, "Torus");
	}
			 break;
	case 18: {
		strcpy_s(charArray, 20, "Picture");
	}
			 break;
	default: {
		strcpy_s(charArray, 20, "None Object");
	}
			 break;
	}
}

//hàm hiện thông tin cho symmetryObjects
void showInformationSymmetryObjects(int whichItemSymmetry, vector<SymmetryObjects> symmetryObjects,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu){

	int halfWidth = (rightMenu + leftMenu) / 2;

	glColor3f(0.4f, 0.45f, 0.45f);
	//hiện nút nhấn cho get và delete
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 5, topMenu + 290);
	glVertex2f(leftMenu + 5, topMenu + 307);
	glVertex2f(leftMenu + 50, topMenu + 290);
	glVertex2f(leftMenu + 50, topMenu + 307);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(leftMenu + 53, topMenu + 290);
	glVertex2f(leftMenu + 53, topMenu + 307);
	glVertex2f(leftMenu + 103, topMenu + 290);
	glVertex2f(leftMenu + 103, topMenu + 307);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);

	//hiện ra các item có trong symmetryObjects
	drawText(leftMenu + 6, topMenu + 175, "WhichItemSymmetry :", "helvetica", 12);
	//in ra các item có trong symmetryVertice và hiện ra hình chữ nhật chọn tại item 
	//mà có chứa thông tin về đối tượng đang được chọn(nếu có)
	int numberElement = symmetryObjects.size(), leftItemNow, topItemNow, maxRight, numberNow;
	char charNumber[10];
	leftItemNow = leftMenu + 128;
	topItemNow = topMenu + 177;
	maxRight = rightMenu - 20;
	for (int i = 0; i < numberElement; i++) {
		changeNumberIntToCharArray(charNumber, i);
		//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
		if (i < 10) {
			//tùy theo kích thước của chữ để vẽ hình chữ nhật bao phù hợp nếu item này là item được chọn
			if (i == whichItemSymmetry) {
				glColor3f(0.1, 0.1, 0.1);
				glBegin(GL_TRIANGLE_STRIP);
				glVertex2f(leftItemNow - 4, topItemNow - 11);
				glVertex2f(leftItemNow - 4, topItemNow + 2);
				glVertex2f(leftItemNow + 10, topItemNow - 11);
				glVertex2f(leftItemNow + 10, topItemNow + 2);
				glEnd();
				glColor3f(1.0, 1.0, 1.0);
			}
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 12;
		}
		else if (i < 100) {
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 20;
		}
		else if (i < 1000) {
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 28;
		}
		else
		{
			drawText(leftItemNow, topItemNow, charNumber, "helvetica", 12);
			leftItemNow += 36;
		}
	}

	drawText(leftMenu + 5, topMenu + 215, "Object1 :", "helvetica", 12);
	drawText(leftMenu + 5, topMenu + 235, "PositionInArray1 :", "helvetica", 12);
	
	drawText(halfWidth + 5, topMenu + 215, "Object2 :", "helvetica", 12);
	drawText(halfWidth + 5, topMenu + 235, "PositionInArray2 :", "helvetica", 12);

	//drawMenuOffOn("ReseverVertex", false, leftMenu + 5, topMenu + 250);
	drawText(leftMenu + 5, topMenu + 280, "NumberVertexInRow :", "helvetica", 12);

	drawText(leftMenu + 17, topMenu + 303, "Get", "helvetica", 12);
	drawText(leftMenu + 60, topMenu + 303, "Delete", "helvetica", 12);

	//hiện các thông tin nếu có item đang được chọn
	if (whichItemSymmetry != -1) {
		SymmetryObjects symmetryNow = symmetryObjects.at(whichItemSymmetry);

		char charArray[20];
		//hiện các thông tin object1
		getCharNameByIntName(charArray, symmetryNow.object1);
		drawText(leftMenu + 65, topMenu + 215, charArray, "helvetica", 12);
		changeNumberIntToCharArray(charArray, symmetryNow.positionInArray1);
		drawText(leftMenu + 110, topMenu + 235, charArray, "helvetica", 12);
		//hiện các thông tin object2
		getCharNameByIntName(charArray, symmetryNow.object2);
		drawText(halfWidth + 65, topMenu + 215, charArray, "helvetica", 12);
		changeNumberIntToCharArray(charArray, symmetryNow.positionInArray2);
		drawText(halfWidth + 110, topMenu + 235, charArray, "helvetica", 12);
		//hiện thông tin các hàm chung
		drawMenuOffOn("ReseverVertex", symmetryNow.isInvertedItemsInRow, leftMenu + 5, topMenu + 250);
		changeNumberIntToCharArray(charArray, symmetryNow.numberItemInRow);
		drawText(leftMenu + 150, topMenu + 280, charArray, "helvetica", 12);
	}
}
//hiên thông tin về cài đặt đối xứng
void showToolOfSymmetry(vector<itemChoice> itemsChoice, int item_choice_in_MenuGroup2,
	bool symmetryVertexOrObject, int whichStyleSymmetry, int whichItemSymmetry,
	bool symmetry_translateX, bool symmetry_translateY, bool symmetry_translateZ,
	bool symmetry_rotateX, bool symmetry_rotateY, bool symmetry_rotateZ,
	bool symmetry_scaleX, bool symmetry_scaleY, bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	
	//hiện menu bật tắt các biến đổi đối xứng
	drawMenuOffOn("Translate X", symmetry_translateX, leftMenu + 5, topMenu + 100);
	drawMenuOffOn("Translate Y", symmetry_translateY, leftMenu + 5, topMenu + 120);
	drawMenuOffOn("Translate Z", symmetry_translateZ, leftMenu + 5, topMenu + 140);

	drawMenuOffOn("Rotate X", symmetry_rotateX, rightMenu - 165, topMenu + 100);
	drawMenuOffOn("Rotate Y", symmetry_rotateY, rightMenu - 165, topMenu + 120);
	drawMenuOffOn("Rotate Z", symmetry_rotateZ, rightMenu - 165, topMenu + 140);

	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_TRIANGLES);
	glVertex2f(leftMenu + 5, topMenu + 36);
	glVertex2f(leftMenu + 15, topMenu + 41);
	glVertex2f(leftMenu + 15, topMenu + 31);

	glVertex2f(leftMenu + 130, topMenu + 36);
	glVertex2f(leftMenu + 120, topMenu + 41);
	glVertex2f(leftMenu + 120, topMenu + 31);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(leftMenu + 135, topMenu + 37);
	glVertex2f(rightMenu - 10, topMenu + 37);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	//hiện các hàm lấy ra chuỗi các đỉnh,row hay column từ 2 điểm bắt đầu
	if (symmetryVertexOrObject == 0) {
		drawText(leftMenu + 42, topMenu + 40, "Vertex", "helvetica", 12);

		showInformationSymmetryVertices(whichStyleSymmetry, whichItemSymmetry,
			symmetryVertices,
			startAndEndSymmetry1, startAndEndSymmetry2,
			isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
			leftMenu, rightMenu, topMenu, bottomMenu);
	}
	else
	{
		drawText(leftMenu + 42, topMenu + 40, "Object", "helvetica", 12);

		showInformationSymmetryObjects(whichItemSymmetry, symmetryObjects,
			leftMenu, rightMenu, topMenu, bottomMenu);
	}
}
//hàm sắp xếp vị trí vertex theo hàng(row)(dùng cho các hình vẽ giống như sphere)
void arrangedVertexWithRow(bool isValueUp, int numberLongitude, int numberLatitude, vector<int> &arrayIn) {
	int numberElement = arrayIn.size(), offset0, offset1, elementCheck0, elementCheck1;
	//ta cứ kiểm tra theo từng dòng,tùy theo isValueUp để sắp xếp các giá trị(kế tiếp nhau)
	//trong các hàng tăng lên hay giảm xuống 
	for (int i = 0; i < numberLatitude; i++) {
		offset0 = i*numberLongitude;
		offset1 = (i + 1)*numberLongitude;
		for (int m = 0; m < numberElement - 1; m++) {
			elementCheck0 = arrayIn.at(m);
			if (elementCheck0 >= offset0 && elementCheck0 < offset1) {
				for (int n = m + 1; n < numberElement; n++) {
					elementCheck1 = arrayIn.at(n);
					if (elementCheck1 >= offset0 && elementCheck1 < offset1) {
						//nếu 2 phần tử kế nhau nằm cùng 1 hàng thì nếu isValueUp=true thì giá trị nhỏ hơn sẽ đứng trước
						if (isValueUp) {
							if (elementCheck0 > elementCheck1) {
								arrayIn.at(m) = arrayIn.at(n);
								arrayIn.at(n) = elementCheck0;
								elementCheck0 = elementCheck1;
							}
						}
						else
						{
							if (elementCheck0 < elementCheck1) {
								arrayIn.at(m) = arrayIn.at(n);
								arrayIn.at(n) = elementCheck0;
								elementCheck0 = elementCheck1;
							}
						}
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}
//hàm sắp xếp vị trí vertex theo hàng(row)
void arrangedVertexWithRow(bool isValueUp, itemChoice item, vector<int> &positionVerticesChoice,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	switch (item.object)
	{
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		arrangedVertexWithRow(isValueUp, sphere->numberLongitude, sphere->numberLatitude, positionVerticesChoice);
	}
			 break;
			 /*case 11: {
			 CubeAttribute *cube = cubeArray.at(item.positionOfChoice);

			 }
			 break;*/
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		arrangedVertexWithRow(isValueUp, cone->numberLongitude, cone->numberLatitude, positionVerticesChoice);
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		arrangedVertexWithRow(isValueUp, cylinder->numberLongitude, cylinder->numberLatitude, positionVerticesChoice);
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		arrangedVertexWithRow(isValueUp, cylinder->numberLongitude, cylinder->numberLatitude, positionVerticesChoice);
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		arrangedVertexWithRow(isValueUp, object->numberLongitude, object->numberLatitude, positionVerticesChoice);
	}
			 break;
	default:
		break;
	}
}
//hàm lấy ra giá trị lớn nhất cho cả vertex,row,column của hình đang được chọn
//whichAttribute = 0 là vertex,1 là row,2 là column
int getMaxValueAttribute(int whichAttribute, itemChoice item,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	switch (item.object)
	{
	case 10: {
		SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
		if (whichAttribute == 0) {
			return sphere->vertexArray.size();
		}
		else if (whichAttribute == 1) {
			return sphere->numberLatitude;
		}
		else if (whichAttribute == 2) {
			return sphere->numberLongitude;
		}
	}
			 break;
			 /*case 11: {
			 CubeAttribute *cube = cubeArray.at(item.positionOfChoice);

			 }
			 break;*/
	case 13: {
		ConeAttribute *cone = coneArray.at(item.positionOfChoice);
		if (whichAttribute == 0) {
			return cone->vertexArray.size();
		}
		else if (whichAttribute == 1) {
			return cone->numberLatitude;
		}
		else if (whichAttribute == 2) {
			return cone->numberLongitude;
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
		if (whichAttribute == 0) {
			return cylinder->vertexArray.size();
		}
		else if (whichAttribute == 1) {
			return cylinder->numberLatitude;
		}
		else if (whichAttribute == 2) {
			return cylinder->numberLongitude;
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
		if (whichAttribute == 0) {
			return cylinder->vertexArray.size();
		}
		else if (whichAttribute == 1) {
			return cylinder->numberLatitude;
		}
		else if (whichAttribute == 2) {
			return cylinder->numberLongitude;
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
		if (whichAttribute == 0) {
			return object->vertexArray.size();
		}
		else if (whichAttribute == 1) {
			return object->numberLatitude;
		}
		else if (whichAttribute == 2) {
			return object->numberLongitude;
		}
	}
			 break;
	default:
		break;
	}
	return 0;
}
//hàm lấy ra các item(vertex,row hay column) từ 2 item đầu và cuối(hàm này dùng để lấy các item để xác định các đỉnh đối xứng)
void getAllItemCenterOfStartAndEnd(int whichStyleSymmetry, itemChoice item,
	bool &isGetSymmetryLikeClockwise, int *startAndEndSymmetry, int maxValue,
	vector<int> &positionVertex, vector<PositionRowOrColumn> &positionRowOrColumn,
	vector<SphereAttribute*> sphereArray, vector<CubeAttribute*> cubeArray, vector<ConeAttribute*> coneArray,
	vector<CylinderAttribute*> cylinderArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	if (whichStyleSymmetry == 0) {
		positionVertex.clear();
		if (isGetSymmetryLikeClockwise) {
			if (startAndEndSymmetry[0] < startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i <= startAndEndSymmetry[1]; i++) {
					positionVertex.push_back(i);
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i <= maxValue; i++) {
					positionVertex.push_back(i);
				}
				for (int i = 0; i <= startAndEndSymmetry[1]; i++) {
					positionVertex.push_back(i);
				}
			}
		}
		else
		{
			if (startAndEndSymmetry[0] > startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i >= startAndEndSymmetry[1]; i--) {
					positionVertex.push_back(i);
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i >= 0; i--) {
					positionVertex.push_back(i);
				}
				for (int i = maxValue; i >= startAndEndSymmetry[1]; i--) {
					positionVertex.push_back(i);
				}
			}
		}
		getRowOrColumnByVertices(item,
			positionVertex, positionRowOrColumn,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
	}
	else if (whichStyleSymmetry == 1) {
		positionRowOrColumn.clear();
		if (isGetSymmetryLikeClockwise) {
			if (startAndEndSymmetry[0] < startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i <= startAndEndSymmetry[1]; i++) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i <= maxValue; i++) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
				for (int i = 0; i <= startAndEndSymmetry[1]; i++) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
			}
		}
		else
		{
			if (startAndEndSymmetry[0] > startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i >= startAndEndSymmetry[1]; i--) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i >= 0; i--) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
				for (int i = maxValue; i >= startAndEndSymmetry[1]; i--) {
					positionRowOrColumn.push_back({ i,-1,-1 });
				}
			}
		}
		//lấy ra các vertex có trong hàng(row) này
		getVerticesFromRowOrColumn(item,
			positionRowOrColumn, positionVertex,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
	}
	else if (whichStyleSymmetry == 2) {
		positionRowOrColumn.clear();
		if (isGetSymmetryLikeClockwise) {
			if (startAndEndSymmetry[0] < startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i <= startAndEndSymmetry[1]; i++) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i <= maxValue; i++) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
				for (int i = 0; i <= startAndEndSymmetry[1]; i++) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
			}
		}
		else
		{
			if (startAndEndSymmetry[0] > startAndEndSymmetry[1]) {
				for (int i = startAndEndSymmetry[0]; i >= startAndEndSymmetry[1]; i--) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
			}
			else
			{
				for (int i = startAndEndSymmetry[0]; i >= 0; i--) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
				for (int i = maxValue; i >= startAndEndSymmetry[1]; i--) {
					positionRowOrColumn.push_back({ -1,i,-1 });
				}
			}
		}
		//lấy ra tất cả các vertex gắn với cột(column) này
		getVerticesFromRowOrColumn(item,
			positionRowOrColumn, positionVertex,
			sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
	}
}
//hàm lấy ra id của vật khi có object và positionInArray
int getIdOfObject(int object, int positionObject,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {
	switch (object)
	{
	case 3: {
		return triangleArray.at(positionObject)->id;
	}
			break;
	case 4: {
		return triaStripArray.at(positionObject)->id;
	}
			break;
	case 5: {
		return triaFanArray.at(positionObject)->id;
	}
			break;
	case 10: {
		return sphereArray.at(positionObject)->id;
	}
			 break;
	case 11: {
		return cubeArray.at(positionObject)->id;
	}
			 break;
	case 12: {
		return cubeRoundArray.at(positionObject)->id;
	}
			 break;
	case 13: {
		return coneArray.at(positionObject)->id;
	}
			 break;
	case 14: {
		return cylinderArray.at(positionObject)->id;
	}
			 break;
	case 15: {
		return pyrArray.at(positionObject)->id;
	}
			 break;
	case 16: {
		return emptyCylinderArray.at(positionObject)->id;
	}
			 break;
	case 17: {
		return torusArray.at(positionObject)->id;
	}
			 break;
	case 18: {
		return pictureArray.at(positionObject)->id;
	}
			 break;
	case 19: {
		return objectCustom0Array.at(positionObject)->id;
	}
			 break;
	default:
		break;
	}
	return -1;
}
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
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	int offset0, offset1, topSymmetry2 = ((bottomMenu - 110) + (topMenu + 220)) / 2;
	//kiểm tra xem có nhấn trúng vị trí nào trên thanh whichStyleSymmetry không
	for (int i = 0; i < 3; i++) {
		offset0 = 82 + (i * 55);
		offset1 = 82 + ((i + 1) * 55);
		if (x > leftMenu + offset0 && x < leftMenu + offset1 && y > topMenu + 70 && y < topMenu + 85) {
			whichStyleSymmetry = i;

			startAndEndSymmetry1[0] = 0;
			startAndEndSymmetry1[1] = 0;
			startAndEndSymmetry2[0] = 0;
			startAndEndSymmetry2[1] = 0;
			return true;
		}
	}
	//điều kiện để nhấn được các button cũng như nut on/off phía dưới là chỉ có 1 object đang được chọn
	if (itemsChoice.size() == 1) {
		//kiểm tra xem có nhấn trúng button không
		//các button của item symmetry 1
		if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topMenu + 225 && y < topMenu + 242) {
			//button chọn
			if (whichStyleSymmetry == 0) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionVerticesChoice.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionVertices1 = positionVerticesChoice;
						//sau khi có tất cả các vertex đang được chọn thì kiểm tra xem có 
						//row hay coulumn nào có thể tạo từ các vertex này không
						getRowOrColumnByVertices(itemsChoice.at(0),
							symmetryNow->positionVertices1, symmetryNow->positionROrC1,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;
						newSymmetry.positionVertices1 = positionVerticesChoice;
						getRowOrColumnByVertices(itemsChoice.at(0),
							newSymmetry.positionVertices1, newSymmetry.positionROrC1,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}
			//sau đó nếu đang ở chế độ cột thì lấy tất cả các cột ra,nếu chế độ hàng thì lấy tất cả các hàng ra
			if (whichStyleSymmetry == 1) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionChoiceRowOrColumn.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionROrC1.clear();

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionRow != -1) {
									symmetryNow->positionROrC1.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								symmetryNow->positionROrC1, symmetryNow->positionVertices1,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionRow != -1) {
									newSymmetry.positionROrC1.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								newSymmetry.positionROrC1, newSymmetry.positionVertices1,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}

						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}
			else if (whichStyleSymmetry == 2) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionChoiceRowOrColumn.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionROrC1.clear();

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionColumn != -1) {
									symmetryNow->positionROrC1.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								symmetryNow->positionROrC1, symmetryNow->positionVertices1,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionColumn != -1) {
									newSymmetry.positionROrC1.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								newSymmetry.positionROrC1, newSymmetry.positionVertices1,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}

						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}

			return true;
		}
		else if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topMenu + 244 && y < topMenu + 260) {
			//nếu object đang được chọn hiện tại cso giá trị đang được lưu trong mảng symmetryVertices
			//thì mới có phần tử để đảo ngược
			if (whichItemSymmetry != -1) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				//button đảo ngược vị trí các vertex trong mảng
				if (whichStyleSymmetry == 0) {
					reverseItemInVector(symmetryNow->positionVertices1);
				}
				else if (whichStyleSymmetry == 1 || whichStyleSymmetry == 2) {
					//nếu đang có vật đang được chọn thì mới lấy vị trí của vertex trong hình ra được
					if (!itemsChoice.empty()) {
						reverseItemInVector(symmetryNow->positionROrC1);
						//đối với chế độ row hay column thì sau khi đảo ngược vị trí các hàng
						//hay cột thì ta mới lấy lại các vertex đựa theo vị trí các hàng
						getVerticesFromRowOrColumn(itemsChoice.at(0),
							symmetryNow->positionROrC1, symmetryNow->positionVertices1,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topMenu + 262 && y < topMenu + 279) {
			//buton xóa chỉ 1 item đang được chọn

			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topMenu + 225 && y < topMenu + 242) {
			//button đảo ngược vị trí theo hàng và các phần tử trong hàng tăng lên
			//cái này chỉ dùng cho vertex
			if (whichItemSymmetry != -1 && whichStyleSymmetry == 0) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				arrangedVertexWithRow(true, itemsChoice.at(0), symmetryNow->positionVertices1,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
			}
			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topMenu + 244 && y < topMenu + 260) {
			//button đảo ngược vị trí theo hàng và các phần tử trong hàng giảm xuống
			//cái này chỉ dùng cho vertex
			if (whichItemSymmetry != -1 && whichStyleSymmetry == 0) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				arrangedVertexWithRow(false, itemsChoice.at(0), symmetryNow->positionVertices1,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
			}
			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topMenu + 262 && y < topMenu + 279) {
			//hàm xóa toàn bộ các item đang có
			if (whichItemSymmetry != -1) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				symmetryNow->positionROrC1.clear();
				symmetryNow->positionVertices1.clear();

				//nếu là nhấn xóa toàn bộ mảng đối xứng 1 thì kiểm tra xem mảng đối xứng 1 có bị rỗng không
				//nếu rỗng thì xóa vật này ra khỏi mảng đổi xứng luôn và đặt whichItemSymmetry về -1
				if (symmetryNow->positionVertices2.empty()) {
					symmetryVertices.erase(symmetryVertices.begin() + whichItemSymmetry);
					whichItemSymmetry = -1;
				}
			}
			return true;
		}

		//các button của item symmetry 2
		if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topSymmetry2 + 5 && y < topSymmetry2 + 22) {
			//button chọn
			if (whichStyleSymmetry == 0) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionVerticesChoice.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionVertices2 = positionVerticesChoice;
						//sau khi có tất cả các vertex đang được chọn thì kiểm tra xem có 
						//row hay coulumn nào có thể tạo từ các vertex này không
						getRowOrColumnByVertices(itemsChoice.at(0),
							symmetryNow->positionVertices2, symmetryNow->positionROrC2,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;
						newSymmetry.positionVertices2 = positionVerticesChoice;
						getRowOrColumnByVertices(itemsChoice.at(0),
							newSymmetry.positionVertices2, newSymmetry.positionROrC2,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}
			//sau đó nếu đang ở chế độ cột thì lấy tất cả các cột ra,nếu chế độ hàng thì lấy tất cả các hàng ra
			if (whichStyleSymmetry == 1) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionChoiceRowOrColumn.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionROrC2.clear();

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionRow != -1) {
									symmetryNow->positionROrC2.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								symmetryNow->positionROrC2, symmetryNow->positionVertices2,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionRow != -1) {
									newSymmetry.positionROrC2.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								newSymmetry.positionROrC2, newSymmetry.positionVertices2,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}

						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}
			else if (whichStyleSymmetry == 2) {
				//nếu mảng nhập vào không rỗng thì mới cho nhập vào
				if (!positionChoiceRowOrColumn.empty()) {
					//nếu hình hiên tại đã có item trong symmetryVertex để lưu lại các giá trị thì thay đổi các giá trị đó
					if (whichItemSymmetry != -1) {
						SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
						symmetryNow->positionROrC2.clear();

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionColumn != -1) {
									symmetryNow->positionROrC2.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								symmetryNow->positionROrC2, symmetryNow->positionVertices2,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}
					}
					//nếu hình hiện tại chưa có item trong symmetryVertex để lưu các giá trị thì tạo mới
					else
					{
						//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
						int numberSymmetry = symmetryObjects.size();
						itemChoice item = itemsChoice.back();
						SymmetryObjects symmetryObjectCheck;
						for (int i = 0; i < numberSymmetry; i++) {
							symmetryObjectCheck = symmetryObjects.at(i);
							if (symmetryObjectCheck.object1 == item.object &&
								(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
									symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
								//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
								return true;
							}
						}

						SymmetryVertices newSymmetry;
						newSymmetry.object = itemsChoice.back().object;
						newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;

						PositionRowOrColumn testRow;
						int numberElement = positionChoiceRowOrColumn.size();
						if (numberElement > 0) {
							for (int i = 0; i < numberElement; i++) {
								testRow = positionChoiceRowOrColumn.at(i);
								if (testRow.positionColumn != -1) {
									newSymmetry.positionROrC2.push_back(testRow);
								}
							}
							//tính toán ra vertex dựa vào các hàng đã chọn
							getVerticesFromRowOrColumn(itemsChoice.at(0),
								newSymmetry.positionROrC2, newSymmetry.positionVertices2,
								sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
						}

						//sau khi đã gán các giá trị xong thì đặt nó vào mảng
						symmetryVertices.push_back(newSymmetry);
						//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
						whichItemSymmetry = symmetryVertices.size() - 1;
					}
				}
			}

			return true;
		}
		else if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topSymmetry2 + 24 && y < topSymmetry2 + 40) {
			//nếu object đang được chọn hiện tại cso giá trị đang được lưu trong mảng symmetryVertices
			//thì mới có phần tử để đảo ngược
			if (whichItemSymmetry != -1) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				//button đảo ngược vị trí các vertex trong mảng
				if (whichStyleSymmetry == 0) {
					reverseItemInVector(symmetryNow->positionVertices2);
				}
				else if (whichStyleSymmetry == 1 || whichStyleSymmetry == 2) {
					//nếu đang có vật đang được chọn thì mới lấy vị trí của vertex trong hình ra được
					if (!itemsChoice.empty()) {
						reverseItemInVector(symmetryNow->positionROrC2);
						//đối với chế độ row hay column thì sau khi đảo ngược vị trí các hàng
						//hay cột thì ta mới lấy lại các vertex đựa theo vị trí các hàng
						getVerticesFromRowOrColumn(itemsChoice.at(0),
							symmetryNow->positionROrC2, symmetryNow->positionVertices2,
							sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 5 && x < leftMenu + 55
			&& y > topSymmetry2 + 42 && y < topSymmetry2 + 59) {
			//hàm xóa chỉ 1 item đang chọn
			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topSymmetry2 + 5 && y < topSymmetry2 + 22) {
			//button đảo ngược vị trí theo hàng và các phần tử trong hàng tăng lên
			//cái này chỉ dùng cho vertex
			if (whichItemSymmetry != -1 && whichStyleSymmetry == 0) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				arrangedVertexWithRow(true, itemsChoice.at(0), symmetryNow->positionVertices2,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
			}
			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topSymmetry2 + 24 && y < topSymmetry2 + 40) {
			//button đảo ngược vị trí theo hàng và các phần tử trong hàng tăng lên
			//cái này chỉ dùng cho vertex
			if (whichItemSymmetry != -1 && whichStyleSymmetry == 0) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				arrangedVertexWithRow(false, itemsChoice.at(0), symmetryNow->positionVertices2,
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array);
			}
			return true;
		}
		else if (x > leftMenu + 58 && x < leftMenu + 118
			&& y > topSymmetry2 + 42 && y < topSymmetry2 + 59) {
			//hàm xóa toàn bộ các item đang có
			if (whichItemSymmetry != -1) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				symmetryNow->positionROrC2.clear();
				symmetryNow->positionVertices2.clear();

				//nếu là nhấn xóa toàn bộ mảng đối xứng 1 thì kiểm tra xem mảng đối xứng 1 có bị rỗng không
				//nếu rỗng thì xóa vật này ra khỏi mảng đổi xứng luôn và đặt whichItemSymmetry về -1
				if (symmetryNow->positionVertices1.empty()) {
					symmetryVertices.erase(symmetryVertices.begin() + whichItemSymmetry);
					whichItemSymmetry = -1;
				}
			}
			return true;
		}

		//kiểm tra nhấn trúng menu bật tắt lấy theo chiều kim đồng hồ
		//rightMenu - 160, bottomMenu - 117            rightMenu - 160, bottomMenu - 57
		if (x > rightMenu - 160 + 110 && x < rightMenu - 160 + 150
			&& y > bottomMenu - 117 && y < bottomMenu - 117 + 10) {
			isGetSymmetryLikeClockwise1 = !isGetSymmetryLikeClockwise1;
			return true;
		}
		else if (x > rightMenu - 160 + 110 && x < rightMenu - 160 + 150
			&& y > bottomMenu - 57 && y < bottomMenu - 57 + 10) {
			isGetSymmetryLikeClockwise2 = !isGetSymmetryLikeClockwise2;
			return true;
		}
		//kiểm tra xem có nhấn trúng nút lấy điểm bắt đầu hay kết thúc không
		//leftMenu + 40, bottomMenu - 98      leftMenu + 40, bottomMenu - 78
		if (x > leftMenu + 40 + 65 && x < leftMenu + 40 + 95
			&& y > bottomMenu - 98 - 2 && y < bottomMenu - 98 + 12) {
			//nếu chỉ có 1 item đang được chọn
			if (whichStyleSymmetry == 0 && positionVerticesChoice.size() == 1) {
				startAndEndSymmetry1[0] = positionVerticesChoice.back();
			}
			else if ((whichStyleSymmetry == 1 || whichStyleSymmetry == 2) && positionChoiceRowOrColumn.size() == 1) {
				if (whichStyleSymmetry == 1) {
					if (positionChoiceRowOrColumn.back().positionRow != -1) {
						startAndEndSymmetry1[0] = positionChoiceRowOrColumn.back().positionRow;
					}
				}
				else
				{
					if (positionChoiceRowOrColumn.back().positionColumn != -1) {
						startAndEndSymmetry1[0] = positionChoiceRowOrColumn.back().positionColumn;
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 40 + 100 && x < leftMenu + 40 + 130
			&& y > bottomMenu - 98 - 2 && y < bottomMenu - 98 + 12) {
			if (!itemsChoice.empty()) {
				startAndEndSymmetry1[0] = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
			}
			return true;
		}
		else if (x > leftMenu + 40 + 135 && x < leftMenu + 40 + 165
			&& y > bottomMenu - 98 - 2 && y < bottomMenu - 98 + 12) {
			startAndEndSymmetry1[0] = 0;
			return true;
		}
		else if (x > leftMenu + 40 + 65 && x < leftMenu + 40 + 95
			&& y > bottomMenu - 78 - 2 && y < bottomMenu - 78 + 12) {
			if (whichStyleSymmetry == 0 && positionVerticesChoice.size() == 1) {
				startAndEndSymmetry1[1] = positionVerticesChoice.back();
			}
			else if ((whichStyleSymmetry == 1 || whichStyleSymmetry == 2) && positionChoiceRowOrColumn.size() == 1) {
				if (whichStyleSymmetry == 1) {
					if (positionChoiceRowOrColumn.back().positionRow != -1) {
						startAndEndSymmetry1[1] = positionChoiceRowOrColumn.back().positionRow;
					}
				}
				else
				{
					if (positionChoiceRowOrColumn.back().positionColumn != -1) {
						startAndEndSymmetry1[1] = positionChoiceRowOrColumn.back().positionColumn;
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 40 + 100 && x < leftMenu + 40 + 130
			&& y > bottomMenu - 78 - 2 && y < bottomMenu - 78 + 12) {
			if (!itemsChoice.empty()) {
				startAndEndSymmetry1[1] = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
			}
			return true;
		}
		else if (x > leftMenu + 40 + 135 && x < leftMenu + 40 + 165
			&& y > bottomMenu - 78 - 2 && y < bottomMenu - 78 + 12) {
			startAndEndSymmetry1[1] = 0;
			return true;
		}
		//leftMenu + 40, bottomMenu - 38      leftMenu + 40, bottomMenu - 18
		else if (x > leftMenu + 40 + 65 && x < leftMenu + 40 + 95
			&& y > bottomMenu - 38 - 2 && y < bottomMenu - 38 + 12) {
			if (whichStyleSymmetry == 0 && positionVerticesChoice.size() == 1) {
				startAndEndSymmetry2[0] = positionVerticesChoice.back();
			}
			else if ((whichStyleSymmetry == 1 || whichStyleSymmetry == 2) && positionChoiceRowOrColumn.size() == 1) {
				if (whichStyleSymmetry == 1) {
					if (positionChoiceRowOrColumn.back().positionRow != -1) {
						startAndEndSymmetry2[0] = positionChoiceRowOrColumn.back().positionRow;
					}
				}
				else
				{
					if (positionChoiceRowOrColumn.back().positionColumn != -1) {
						startAndEndSymmetry2[0] = positionChoiceRowOrColumn.back().positionColumn;
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 40 + 100 && x < leftMenu + 40 + 130
			&& y > bottomMenu - 38 - 2 && y < bottomMenu - 38 + 12) {
			if (!itemsChoice.empty()) {
				startAndEndSymmetry2[0] = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
			}
			return true;
		}
		else if (x > leftMenu + 40 + 135 && x < leftMenu + 40 + 165
			&& y > bottomMenu - 38 - 2 && y < bottomMenu - 38 + 12) {
			startAndEndSymmetry2[0] = 0;
			return true;
		}
		else if (x > leftMenu + 40 + 65 && x < leftMenu + 40 + 95
			&& y > bottomMenu - 18 - 2 && y < bottomMenu - 18 + 12) {
			if (whichStyleSymmetry == 0 && positionVerticesChoice.size() == 1) {
				startAndEndSymmetry2[1] = positionVerticesChoice.back();
			}
			else if ((whichStyleSymmetry == 1 || whichStyleSymmetry == 2) && positionChoiceRowOrColumn.size() == 1) {
				if (whichStyleSymmetry == 1) {
					if (positionChoiceRowOrColumn.back().positionRow != -1) {
						startAndEndSymmetry2[1] = positionChoiceRowOrColumn.back().positionRow;
					}
				}
				else
				{
					if (positionChoiceRowOrColumn.back().positionColumn != -1) {
						startAndEndSymmetry2[1] = positionChoiceRowOrColumn.back().positionColumn;
					}
				}
			}
			return true;
		}
		else if (x > leftMenu + 40 + 100 && x < leftMenu + 40 + 130
			&& y > bottomMenu - 18 - 2 && y < bottomMenu - 18 + 12) {
			if (!itemsChoice.empty()) {
				startAndEndSymmetry2[1] = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
			}
			return true;
		}
		else if (x > leftMenu + 40 + 135 && x < leftMenu + 40 + 165
			&& y > bottomMenu - 18 - 2 && y < bottomMenu - 18 + 12) {
			startAndEndSymmetry2[1] = 0;
			return true;
		}
		//kiểm tra xem có nhấn trúng nút lấy các giá trị nằm giữa 2 giá trị bắt đầu và kết thúc không
		else if (x > rightMenu - 110 && x<rightMenu - 10 &&
			y>bottomMenu - 95 && y < bottomMenu - 65) {
			//điều kiện là hình đang được chọn phải có giá trị trong mảng symmetryVerices
			//và điểm bắt đầu và kết thúc phải khác nhau
			if (startAndEndSymmetry1[0] != startAndEndSymmetry1[1]) {
				if (whichItemSymmetry != -1) {
					SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
					//maxValue phải trừ đi 1 do ta tính bắt đầu từ 0
					int maxValue = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
					//lấy ra các item nằm giữa item bắt đầu và kết thúc
					getAllItemCenterOfStartAndEnd(whichStyleSymmetry, itemsChoice.at(0),
						isGetSymmetryLikeClockwise1, startAndEndSymmetry1, maxValue,
						symmetryNow->positionVertices1, symmetryNow->positionROrC1,
						sphereArray, cubeArray, coneArray,
						cylinderArray, emptyCylinderArray, objectCustom0Array);
				}
				//nếu object này chưa có giá trị trong symmetryVertex thì tạo mới
				else
				{
					//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
					int numberSymmetry = symmetryObjects.size();
					itemChoice item = itemsChoice.back();
					SymmetryObjects symmetryObjectCheck;
					for (int i = 0; i < numberSymmetry; i++) {
						symmetryObjectCheck = symmetryObjects.at(i);
						if (symmetryObjectCheck.object1 == item.object &&
							(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
								symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
							//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
							return true;
						}
					}

					SymmetryVertices newSymmetry;
					newSymmetry.object = itemsChoice.back().object;
					newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;
					//maxValue phải trừ đi 1 do ta tính bắt đầu từ 0
					int maxValue = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
						sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
					//lấy ra các item nằm giữa item bắt đầu và kết thúc
					getAllItemCenterOfStartAndEnd(whichStyleSymmetry, itemsChoice.at(0),
						isGetSymmetryLikeClockwise1, startAndEndSymmetry1, maxValue,
						newSymmetry.positionVertices1, newSymmetry.positionROrC1,
						sphereArray, cubeArray, coneArray,
						cylinderArray, emptyCylinderArray, objectCustom0Array);
					//thêm item vừa tạo vào mảng symmetryVertice
					symmetryVertices.push_back(newSymmetry);
					//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
					whichItemSymmetry = symmetryVertices.size() - 1;
				}
			}
			return true;
		}
		else if (x > rightMenu - 110 && x<rightMenu - 10 &&
			y>bottomMenu - 35 && y < bottomMenu - 5) {
			if (whichItemSymmetry != -1) {
				SymmetryVertices *symmetryNow = &symmetryVertices.at(whichItemSymmetry);
				//maxValue phải trừ đi 1 do ta tính bắt đầu từ 0
				int maxValue = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
				//lấy ra các item nằm giữa item bắt đầu và kết thúc
				getAllItemCenterOfStartAndEnd(whichStyleSymmetry, itemsChoice.at(0),
					isGetSymmetryLikeClockwise2, startAndEndSymmetry2, maxValue,
					symmetryNow->positionVertices2, symmetryNow->positionROrC2,
					sphereArray, cubeArray, coneArray,
					cylinderArray, emptyCylinderArray, objectCustom0Array);
			}
			//nếu object này chưa có giá trị trong symmetryVertex thì tạo mới
			else
			{
				//điều kiện để tạo mới là hình được chọn phải không có trong bất kỳ symmetryObject nào
				int numberSymmetry = symmetryObjects.size();
				itemChoice item = itemsChoice.back();
				SymmetryObjects symmetryObjectCheck;
				for (int i = 0; i < numberSymmetry; i++) {
					symmetryObjectCheck = symmetryObjects.at(i);
					if (symmetryObjectCheck.object1 == item.object &&
						(symmetryObjectCheck.positionInArray1 == item.positionOfChoice ||
							symmetryObjectCheck.positionInArray2 == item.positionOfChoice)) {
						//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
						return true;
					}
				}

				SymmetryVertices newSymmetry;
				newSymmetry.object = itemsChoice.back().object;
				newSymmetry.positionInArray = itemsChoice.back().positionOfChoice;
				//maxValue phải trừ đi 1 do ta tính bắt đầu từ 0
				int maxValue = getMaxValueAttribute(whichStyleSymmetry, itemsChoice.at(0),
					sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray, objectCustom0Array) - 1;
				//lấy ra các item nằm giữa item bắt đầu và kết thúc
				getAllItemCenterOfStartAndEnd(whichStyleSymmetry, itemsChoice.at(0),
					isGetSymmetryLikeClockwise2, startAndEndSymmetry2, maxValue,
					newSymmetry.positionVertices2, newSymmetry.positionROrC2,
					sphereArray, cubeArray, coneArray,
					cylinderArray, emptyCylinderArray, objectCustom0Array);
				//thêm item vừa tạo vào mảng symmetryVertice
				symmetryVertices.push_back(newSymmetry);
				//đặt whichItemSymmetry thành vị trí cuối cùng của symmetryVertex(phần tử vừa thêm vào)
				whichItemSymmetry = symmetryVertices.size() - 1;
			}
			return true;
		}

	}

	//kiểm tra xem có nhấn trúng item nào của symmetryVertex không
	int leftItemNow, topItemNow, maxRight,
		numberSymmetry = symmetryVertices.size();
	leftItemNow = leftMenu + 128;
	topItemNow = topMenu + 177;
	maxRight = rightMenu - 20;
	for (int i = 0; i < numberSymmetry; i++) {
		//kiêm tra xem có nhấn trúng item này không
		if (x>leftItemNow - 4 && x<leftItemNow + 10 &&
			y>topItemNow - 11 && y<topItemNow + 2) {
			//sau khi tìm được vị trí nhấn thì đặt whichItemSymmetry thành vị trí này đồng thời 
			//đặt itemsChoice là vật có chứa trong item hiện tại
			SymmetryVertices symmetryNow = symmetryVertices.at(i);
			int id = getIdOfObject(symmetryNow.object, symmetryNow.positionInArray,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			//xáo hết toàn bộ các thuộc tính có liên quan để đặt lại
			itemsChoice.clear();
			positionVerticesChoice.clear();
			positionChoiceRowOrColumn.clear();
			itemsChoice.push_back({ symmetryNow.object, id, symmetryNow.positionInArray });
			whichItemSymmetry = i;
		}
		//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
		if (i < 10) {
			leftItemNow += 12;
		}
		else if (i < 100) {
			leftItemNow += 20;
		}
		else if (i < 1000) {
			leftItemNow += 28;
		}
		else
		{
			leftItemNow += 36;
		}
	}

	//kiêm tra xem có nhấn trúng các item trong symmetry1 hay 2 không
	/*int leftItemChoice, topItemChoice, maxRight, numberElement;
	leftItemChoice = leftMenu + 124;
	topItemChoice = topMenu + 150;
	maxRight = rightMenu - 20;
	if (whichStyleSymmetry == 0) {
	numberElement = positionVertexSymmetry1.size();
	for (int i = 0; i < numberElement; i++) {
	//nếu đến max item thì xuống dòng
	if (leftItemChoice > maxRight) {
	leftItemChoice = leftMenu + 124;
	topItemChoice += 20;
	//kiểm tra xem đã đến giới hạn dưới chưa,nếu chưa thì tiếp tụ còn nếu rồi thì
	//in ra dấu 3 chấm và kết thúc vòng lặp
	if (topItemChoice > topMenu + 250) {
	break;
	}
	}
	else
	{

	}
	}
	}*/
}
//kiểm tra xem 2 hình được chọn có cùng chung thuộc tính(cùng loại và cùng numberLongitude và numberLatitude)
bool isSameAttribute(itemChoice item1,itemChoice item2,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array){
	//kiểm tra xem có phải cùng kiểu không
	if (item1.object != item2.object) {
		return false;
	}
	else
	{
		switch (item1.object)
		{
		case 3:
		case 15:
		case 18: {
			return true;
		}
				break;
		case 4: {
			if (triaStripArray.at(item1.positionOfChoice)->vertexArray.size() ==
				triaStripArray.at(item2.positionOfChoice)->vertexArray.size()) {
				return true;
			}
		}
				break;
		case 5: {
			if (triaFanArray.at(item1.positionOfChoice)->vertexArray.size() ==
				triaFanArray.at(item2.positionOfChoice)->vertexArray.size()) {
				return true;
			}
		}
				break;
		case 10: {
			if (sphereArray.at(item1.positionOfChoice)->numberLatitude == sphereArray.at(item2.positionOfChoice)->numberLatitude &&
				sphereArray.at(item1.positionOfChoice)->numberLongitude == sphereArray.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		case 11: {
			if (cubeArray.at(item1.positionOfChoice)->numberVertexInAxisX == cubeArray.at(item2.positionOfChoice)->numberVertexInAxisX &&
				cubeArray.at(item1.positionOfChoice)->numberVertexInAxisY == cubeArray.at(item2.positionOfChoice)->numberVertexInAxisY &&
				cubeArray.at(item1.positionOfChoice)->numberVertexInAxisZ == cubeArray.at(item2.positionOfChoice)->numberVertexInAxisZ) {
				return true;
			}
		}
				 break;
		case 12: {
			if (cubeRoundArray.at(item1.positionOfChoice)->numberLatitude == cubeRoundArray.at(item2.positionOfChoice)->numberLatitude &&
				cubeRoundArray.at(item1.positionOfChoice)->numberLongitude == cubeRoundArray.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		case 13: {
			if (coneArray.at(item1.positionOfChoice)->numberLatitude == coneArray.at(item2.positionOfChoice)->numberLatitude &&
				coneArray.at(item1.positionOfChoice)->numberLongitude == coneArray.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		case 14: {
			if (cylinderArray.at(item1.positionOfChoice)->numberLatitude == cylinderArray.at(item2.positionOfChoice)->numberLatitude &&
				cylinderArray.at(item1.positionOfChoice)->numberLongitude == cylinderArray.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		case 16: {
			if (emptyCylinderArray.at(item1.positionOfChoice)->numberLatitude == emptyCylinderArray.at(item2.positionOfChoice)->numberLatitude &&
				emptyCylinderArray.at(item1.positionOfChoice)->numberLongitude == emptyCylinderArray.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		case 17: {
			if (torusArray.at(item1.positionOfChoice)->vertexArray.size() ==
				torusArray.at(item2.positionOfChoice)->vertexArray.size()) {
				return true;
			}
		}
				break;
		case 19: {
			if (objectCustom0Array.at(item1.positionOfChoice)->numberLatitude == objectCustom0Array.at(item2.positionOfChoice)->numberLatitude &&
				objectCustom0Array.at(item1.positionOfChoice)->numberLongitude == objectCustom0Array.at(item2.positionOfChoice)->numberLongitude) {
				return true;
			}
		}
				 break;
		default:
			break;
		}
	}

	return false;
}
//hàm thêm các item vào symmetryObject
void addItemInSymmetryObject(vector<SymmetryObjects> &symmetryObjects, itemChoice item1, itemChoice item2,
	vector<TriangleAttribute*> triangleArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	SymmetryObjects newSymmetry;
	newSymmetry.object1 = item1.object;
	newSymmetry.positionInArray1 = item1.positionOfChoice;
	newSymmetry.object2 = item2.object;
	newSymmetry.positionInArray2 = item2.positionOfChoice;
	newSymmetry.isInvertedItemsInRow = false;

	switch (item1.object)
	{
	case 3:
	case 4:
	case 5:
	case 11:
	case 15:
	case 17:
	case 18: {
		newSymmetry.numberItemInRow = 0;
	}
			 break;
	case 10: {
		newSymmetry.numberItemInRow = sphereArray.at(item1.positionOfChoice)->numberLongitude;
	}
			break;
	case 12: {
		newSymmetry.numberItemInRow = cubeRoundArray.at(item1.positionOfChoice)->numberLongitude;
	}
			break;
	case 13: {
		newSymmetry.numberItemInRow = coneArray.at(item1.positionOfChoice)->numberLongitude;
	}
			break;
	case 14: {
		newSymmetry.numberItemInRow = cylinderArray.at(item1.positionOfChoice)->numberLongitude;
	}
			break;
	case 16: {
		newSymmetry.numberItemInRow = emptyCylinderArray.at(item1.positionOfChoice)->numberLongitude;
	}
			break;
	case 19: {
		newSymmetry.numberItemInRow = objectCustom0Array.at(item1.positionOfChoice)->numberLongitude;
	}
			 break;
	default:
		break;
	}

	//thêm item vừa tạo và gán giá trị vào mảng
	symmetryObjects.push_back(newSymmetry);
}
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
	vector<ObjectCustom0Attribute*> objectCustom0Array) {


	//kiểm tra xem có nhấn trúng các button không
	if (x > leftMenu + 5 && x < leftMenu + 50
		&& y > topMenu + 290 && y < topMenu + 307) {
		//button get
		//bắt buộc phải có 2 hình đang chọn để đặt vào 2 hình đối xứng
		if (itemsChoice.size() == 2) {
			itemChoice item1 = itemsChoice.at(0),
				item2 = itemsChoice.at(1);
			//phải kiểm tra các điều kiện
			//đầu tiên là 2 hình được chọn phải cùng loại và cùng numberLongitude và numberLatitude
			bool good = isSameAttribute(item1, item2,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			if (good) {
				//tiếp theo là 2 hình được chọn phải không có hình nào có thông tin trong bất kỳ item nào của symmetryObjects
				int numberSymmetry = symmetryObjects.size();
				SymmetryObjects symmetryObjectCheck;
				for (int i = 0; i < numberSymmetry; i++) {
					symmetryObjectCheck = symmetryObjects.at(i);
					if (symmetryObjectCheck.object1 == item1.object &&
						(symmetryObjectCheck.positionInArray1 == item1.positionOfChoice ||
							symmetryObjectCheck.positionInArray1 == item2.positionOfChoice ||
							symmetryObjectCheck.positionInArray2 == item1.positionOfChoice ||
							symmetryObjectCheck.positionInArray2 == item2.positionOfChoice)) {
						//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryObject thì bỏ qua
						return true;
					}
				}
				//2 hình được chọn phải không có hình nào có thông tin trong symmetryVertices
				numberSymmetry = symmetryVertices.size();
				SymmetryVertices symmetryVerticesCheck;
				for (int i = 0; i < numberSymmetry; i++) {
					symmetryVerticesCheck = symmetryVertices.at(i);
					if (symmetryVerticesCheck.object == item1.object &&
						(symmetryVerticesCheck.positionInArray == item1.positionOfChoice ||
							symmetryVerticesCheck.positionInArray == item2.positionOfChoice)) {
						//nếu chỉ cần có bất kỳ hình nào có thông tin trong bất kỳ item nào của symmetryVertices thì bỏ qua
						return true;
					}
				}

				//nếu đã đáp ứng được yêu cầu thì tạo mới và bỏ vào symmetryObject
				addItemInSymmetryObject(symmetryObjects, item1, item2,
					triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				//sau khi thêm item thì loại bỏ 1 hình trong itemsChoice(để bắt đầu dùng biến đổi đối xứng)
				itemsChoice.pop_back();
				//đặt item vừa thêm vào là item được chọn
				whichItemSymmetry = symmetryObjects.size() - 1;
			}
		}
		return true;
	}
	else if (x > leftMenu + 53 && x < leftMenu + 103
		&& y > topMenu + 290 && y < topMenu + 307) {
		//button delete
		//nếu object này đã có thuộc tính nằm trong mảng symmetryObjects
		if (whichItemSymmetry != -1) {
			symmetryObjects.erase(symmetryObjects.begin() + whichItemSymmetry);
			whichItemSymmetry = -1;
		}
		return true;
	}

	//kiểm tra xem có item nào được chọn không rồi kiểm tra xem có nhấn trúng buton bật tắt reseverVertex không
	if (whichItemSymmetry != -1) {
		//buton bật tắt ReseverVertex leftMenu + 5, topMenu + 280
		if (x > leftMenu + 5 + 110 && x < leftMenu + 5 + 150
			&& y > topMenu + 250 && y < topMenu + 260) {
			//nếu object này đã có thuộc tính nằm trong mảng symmetryObjects
			if (whichItemSymmetry != -1) {
				SymmetryObjects *symmetryNow = &symmetryObjects.at(whichItemSymmetry);
				symmetryNow->isInvertedItemsInRow = !symmetryNow->isInvertedItemsInRow;
			}
			return true;
		}
	}

	//kiểm tra xem có nhấn trúng item nào trong dãy WhichItemSymmetry không
	int numberElement = symmetryObjects.size(), leftItemNow, topItemNow, maxRight;
	leftItemNow = leftMenu + 128;
	topItemNow = topMenu + 177;
	maxRight = rightMenu - 20;
	for (int i = 0; i < numberElement; i++) {
		//kiểm tra nếu x,y nằm trong vị trí hình chữ nhật bao quanh điểm này thì lấy luôn
		if (x > leftItemNow - 4 && x<leftItemNow + 10 &&
			y>topItemNow - 11 && y < topItemNow + 2) {
			//khi tìm được thì đặt object1 thành vật được chọn
			SymmetryObjects symmetryNow = symmetryObjects.at(i);
			itemsChoice.clear();
			int id = getIdOfObject(symmetryNow.object1, symmetryNow.positionInArray1,
				triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
				coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			itemsChoice.push_back({ symmetryNow.object1,id,symmetryNow.positionInArray1 });

			//đặt whichItemSymmetry thành vị trí hiện tại
			whichItemSymmetry = i;
			break;
		}

		//đoạn này phải kiểm tra xem số có bào nhiều chữ số để tăng lên phù hợp
		if (i < 10) {
			leftItemNow += 12;
		}
		else if (i < 100) {
			leftItemNow += 20;
		}
		else if (i < 1000) {
			leftItemNow += 28;
		}
		else
		{
			leftItemNow += 36;
		}
	}
}
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
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//kiểm tra xem có chuyển qua lại giữa chế độ đối xứng vertex và object không
	if (((x > leftMenu + 5 && x< leftMenu + 15) || (x > leftMenu + 120 && x< leftMenu + 130))
		&& y > topMenu + 31 && y < topMenu + 41) {
		symmetryVertexOrObject = !symmetryVertexOrObject;
		//đặt whichItemSymmetry về -1 để tính lại nếu có ở chế độ mới(vertex hay object)
		whichItemSymmetry = -1;
		//khi nhấn nút chuyển thì phải kiểm tra xem nếu itemsChoice có 1 phần tử thì
		//kiểm tra tiếp xem ở chế độ hiện tại (vertex hay object) có item nào đang chứa
		//thông tin về đối tượng đang được chọn không.nếu có thì đặt whichItemChoice thành vị trí item đó
		if (itemsChoice.size() == 1) {
			itemChoice item = itemsChoice.back();
			if (symmetryVertexOrObject == 0) {
				int numberSymmetry = symmetryVertices.size();
				SymmetryVertices symmetryCheck;
				for (int i = 0; i < numberSymmetry; i++) {
					symmetryCheck = symmetryVertices.at(i);
					if (symmetryCheck.object == item.object &&
						symmetryCheck.positionInArray == item.positionOfChoice) {
						whichItemSymmetry = i;
						break;
					}
				}
			}
			else
			{
				int numberSymmetry = symmetryObjects.size();
				SymmetryObjects symmetryCheck;
				for (int i = 0; i < numberSymmetry; i++) {
					symmetryCheck = symmetryObjects.at(i);
					if ((symmetryCheck.object1 == item.object && symmetryCheck.positionInArray1 == item.positionOfChoice) ||
						(symmetryCheck.object2 == item.object && symmetryCheck.positionInArray2 == item.positionOfChoice)) {
						whichItemSymmetry = i;
						break;
					}
				}
			}
		}
		return true;
	}

	//kiểm tra xem có nhấn trúng các phím bật tắt không
	if (x > leftMenu + 5 + 120 && x < leftMenu + 5 + 150
		&& y > topMenu + 100 && y < topMenu + 110) {
		symmetry_translateX = !symmetry_translateX;
		return true;
	}
	else if (x > leftMenu + 5 + 110 && x < leftMenu + 5 + 150
		&& y > topMenu + 120 && y < topMenu + 130) {
		symmetry_translateY = !symmetry_translateY;
		return true;
	}
	else if (x > leftMenu + 5 + 110 && x < leftMenu + 5 + 150
		&& y > topMenu + 140 && y < topMenu + 150) {
		symmetry_translateZ = !symmetry_translateZ;
		return true;
	}else if (x > rightMenu - 165 + 110 && x < rightMenu - 165 + 150
		&& y > topMenu + 100 && y < topMenu + 110) {
		symmetry_rotateX = !symmetry_rotateX;
		return true;
	}
	else if (x > rightMenu - 165 + 110 && x < rightMenu - 165 + 150
		&& y > topMenu + 120 && y < topMenu + 130) {
		symmetry_rotateY = !symmetry_rotateY;
		return true;
	}
	else if (x > rightMenu - 165 + 110 && x < rightMenu - 165 + 150
		&& y > topMenu + 140 && y < topMenu + 150) {
		symmetry_rotateZ = !symmetry_rotateZ;
		return true;
	}

	if (symmetryVertexOrObject == 0) {
		//kiểm tra xem có chọn trúng item nào trong chế độ symmetryVertices không
		return checkToChoiceSymmetryVertices(x, y,
			whichStyleSymmetry, whichItemSymmetry,
			itemsChoice, positionChoiceRowOrColumn,
			positionVerticesChoice,
			symmetryVertices, symmetryObjects,
			startAndEndSymmetry1, startAndEndSymmetry2,
			isGetSymmetryLikeClockwise1, isGetSymmetryLikeClockwise2,
			leftMenu, rightMenu, topMenu, bottomMenu,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
	}
	else
	{
		//kiểm tra xem có chọn trúng item nào trong chế độ symmetryObjects không
		return checkToChoiceSymmetryObjects(x, y, whichItemSymmetry,itemsChoice,
			symmetryVertices, symmetryObjects,
			leftMenu, rightMenu, topMenu, bottomMenu,
			triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
			coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
	}

	return false;
}

//hiện thông tin về các cài đặt của ứng dụng
void showToolOfApp(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool menu_isChangeCharNumberValue,
	bool isRemind, bool isShowBeforeDraw, bool isDrawNet,
	float tool_arrowSize, float tool_circleSize,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	//hiện các đường kẻ
	glColor3f(0.5, 0.5, 0.6);
	glBegin(GL_LINES);
	glVertex2f(leftMenu + 2, topMenu + 37);
	glVertex2f(leftMenu + 15, topMenu + 37);

	glVertex2f(leftMenu + 95, topMenu + 37);
	glVertex2f(rightMenu - 2, topMenu + 37);

	glVertex2f(leftMenu + 2, topMenu + 197);
	glVertex2f(leftMenu + 15, topMenu + 197);

	glVertex2f(leftMenu + 115, topMenu + 197);
	glVertex2f(rightMenu - 2, topMenu + 197);

	glVertex2f(leftMenu + 2, topMenu + 297);
	glVertex2f(leftMenu + 15, topMenu + 297);

	glVertex2f(leftMenu + 115, topMenu + 297);
	glVertex2f(rightMenu - 2, topMenu + 297);
	glEnd();

	//hiện tên các group menu
	glColor3f(1.0, 1.0, 1.0);
	drawText(leftMenu + 20, topMenu + 40, "Custom tool", "helvetica", 12);
	drawText(leftMenu + 20, topMenu + 200, "Custom display", "helvetica", 12);
	drawText(leftMenu + 26, topMenu + 300, "Custom value", "helvetica", 12);

	//hiện các nút bật tắt thể hiện giá trị của các cài đặt tương ứng
	//hiện các cài đặt tùy chỉnh
	drawMenuOffOn("Remind", isRemind, leftMenu + 10, topMenu + 60);
	drawMenuOffOn("Show First", isShowBeforeDraw, leftMenu + 10, topMenu + 80);


	//hiện các cài đặt hiển thị
	drawMenuOffOn("Draw net", isDrawNet, leftMenu + 10, topMenu + 220);

	//hiện các thông tin về kích thước của mũi tên dịch chuyển và đường tròn xoay
	if (item_choice_in_MenuGroup2 == 0) {
		if (menu_isChangeCharNumberValue) {
			drawMenuPlusMinus("Arrow Size ", menu_charNumberValue, leftMenu + 10, topMenu + 320);
		}
		else
		{
			drawMenuPlusMinus("Arrow Size ", tool_arrowSize, true, leftMenu + 10, topMenu + 320);
		}
	}
	else
	{
		drawMenuPlusMinus("Arrow Size ", tool_arrowSize, false, leftMenu + 10, topMenu + 320);
	}

	if (item_choice_in_MenuGroup2 == 1) {
		if (menu_isChangeCharNumberValue) {
			drawMenuPlusMinus("Circle Size ", menu_charNumberValue, leftMenu + 10, topMenu + 340);
		}
		else
		{
			drawMenuPlusMinus("Circle Size ", tool_circleSize, true, leftMenu + 10, topMenu + 340);
		}
	}
	else
	{
		drawMenuPlusMinus("Circle Size ", tool_circleSize, false, leftMenu + 10, topMenu + 340);
	}
	
}
//hàm áp dụng giá trị trong menu_charNumberValue cho giá trị đang được chọn
void appendCharArrayForValueTool(int item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	float &tool_arrowSize, float &tool_circleSize) {
	//nếu đang ở chế độ chỉnh sửa bằng char thì áp dung char thành số và tắt chế độ chỉnh sửa
	if (menu_isChangeCharNumberValue) {
		float val = getFloatFromCharArray(menu_charNumberValue);
		//phải đề phòng trường hợp số từ 1000 trở lên sẽ không hiển thị được
		if (val >= 1000) {
			val = 999.99f;
		}

		if (item_choice_in_MenuGroup2 == 0) {
			tool_arrowSize = val;
		}
		else if (item_choice_in_MenuGroup2 == 1) {
			tool_circleSize = (int)val;
		}
		//đặt chế độ chỉnh về false
		menu_isChangeCharNumberValue = false;
	}
}

//hàm kiểm tra chọn ToolApp
bool checkToChoiceToolApp(int x, int y, int &item_choice_in_MenuGroup2,
	char *menu_charNumberValue, bool &menu_isChangeCharNumberValue,
	bool &isRemind, bool &isShowBeforeDraw, bool &isDrawNet,
	float &tool_arrowSize, float &tool_circleSize,
	int leftMenu, int rightMenu, int topMenu, int bottomMenu) {
	//kiểm tra các cài đặt tùy chỉnh
	if (x > leftMenu + 10 + 110 && x< leftMenu + 10 + 150 && y>topMenu + 60 && y < topMenu + 70) {
		isRemind = !isRemind;
		return true;
	}
	if (x > leftMenu + 10 + 110 && x< leftMenu + 10 + 150 && y>topMenu + 80 && y < topMenu + 90) {
		isShowBeforeDraw = !isShowBeforeDraw;
		return true;
	}
	//kiểm tra các cài đặt hiển thị
	if (x > leftMenu + 10 + 110 && x< leftMenu + 10 + 150 && y>topMenu + 220 && y < topMenu + 230) {
		isDrawNet = !isDrawNet;
		return true;
	}
	//kiểm tra xem có chọn trúng các giá trị chỉnh sửa arrow size không
	//kiểm tra nút giảm
	if (x > leftMenu + 10 + 90 && x < leftMenu + 10 + 100
		&& y > topMenu + 320 && y < topMenu + 330) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		tool_arrowSize -= 0.1f;
		return true;
	}
	//kiểm tra nút tăng
	if (x > leftMenu + 10 + 170 && x < leftMenu + 10 + 180
		&& y > topMenu + 320 && y < topMenu + 330) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		tool_arrowSize += 0.1f;
		return true;
	}
	//kiểm tra có nhấn trúng ô giá trị không
	if (x > leftMenu + 10 + 95 && x < leftMenu + 10 + 165
		&& y > topMenu + 320 && y < topMenu + 330) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		if (item_choice_in_MenuGroup2 == 0 && !menu_isChangeCharNumberValue) {
			//xóa các giá trị trong mảng để dùng lại
			memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
			changeNumberFloatToCharArray(menu_charNumberValue, tool_arrowSize);
			menu_isChangeCharNumberValue = true;
		}
		item_choice_in_MenuGroup2 = 0;
		return true;
	}


	//kiểm tra xem có chọn trúng các giá trị chỉnh sửa circle size không
	//kiểm tra nút giảm
	if (x > leftMenu + 10 + 90 && x < leftMenu + 10 + 100
		&& y > topMenu + 340 && y < topMenu + 350) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		tool_circleSize -= 0.1f;
		return true;
	}
	//kiểm tra nút tăng
	if (x > leftMenu + 10 + 170 && x < leftMenu + 10 + 180
		&& y > topMenu + 340 && y < topMenu + 350) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		tool_circleSize += 0.1f;
		return true;
	}
	//kiểm tra có nhấn trúng ô giá trị không
	if (x > leftMenu + 10 + 95 && x < leftMenu + 10 + 165
		&& y > topMenu + 340 && y < topMenu + 350) {
		appendCharArrayForValueTool(item_choice_in_MenuGroup2,
			menu_charNumberValue, menu_isChangeCharNumberValue,
			tool_arrowSize, tool_circleSize);

		if (item_choice_in_MenuGroup2 == 1 && !menu_isChangeCharNumberValue) {
			//xóa các giá trị trong mảng để dùng lại
			memset(menu_charNumberValue, 0, sizeof(menu_charNumberValue));
			changeNumberFloatToCharArray(menu_charNumberValue, tool_arrowSize);
			menu_isChangeCharNumberValue = true;
		}
		item_choice_in_MenuGroup2 = 1;
		return true;
	}

	return false;
}

