#include "SqlServerConnect.h"

//hàm in lỗi khi kết nối
void extract_error(char *fn, SQLHANDLE handle, SQLSMALLINT type) {
	SQLINTEGER   i = 0;
	SQLINTEGER   native;
	SQLCHAR      state[7];
	SQLCHAR      text[256];
	SQLSMALLINT  len;
	SQLRETURN    ret;

	fprintf(stderr,
		"\n"
		"The driver reported the following diagnostics whilst running "
		"%s\n\n",
		fn);

	do
	{
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			printf("%s:%ld:%ld:%s\n", state, i, native, text);
	} while (ret == SQL_SUCCESS);
}
//hàm kết nối và lưu dữ liệu vào cơ sở dữ liệu
void saveDataBase(vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	SQLHENV env;
	SQLHDBC dbc;
	SQLRETURN ret; /* ODBC API return status */
	SQLWCHAR outstr[1024];
	SQLSMALLINT outstrlen;
	SQLHANDLE stmt_handle;

	//Phân bổ một xử lý môi trường
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	//Chúng tôi muốn hỗ trợ ODBC 3
	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
	// Phân bổ xử lý kết nối
	SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
	// Kết nối với DSN
	ret = SQLDriverConnectW(dbc, NULL, L"DSN=DataGame;", SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_COMPLETE);
	if (SQL_SUCCEEDED(ret)) {
		printf("Connected\n");

		if (ret == SQL_SUCCESS_WITH_INFO) {
			printf("Driver reported the following diagnostics\n");
			extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
		}
		printf("Working . . . \n");
		//lấy ra 1 luồng dùng để try cập thông tin
		SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt_handle);
		//thực hiện lệnh cho sql server
		
		//đầu tiên phải xóa hết toàn bộ dữ liệu đã lưu lần trước để lưu lại
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ConeAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeRoundAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CylinderAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from EmptyCylinderAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ObjectCustom0Attribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PictureAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PyramidAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from SphereAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TorusAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleFanAttribute", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleStripAttribute", SQL_NTS);
		//xóa hết vertex array và normal array để thêm lại
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ConeVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeRoundVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CylinderVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from EmptyCylinderVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ObjectCustom0Vertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PictureVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PyramidVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from SphereVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TorusVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleFanVertex", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleStripVertex", SQL_NTS);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ConeNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CubeRoundNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from CylinderNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from EmptyCylinderNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from ObjectCustom0Normal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PictureNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from PyramidNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from SphereNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TorusNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleFanNormal", SQL_NTS);
		SQLExecDirect(stmt_handle, (SQLCHAR*)"delete from TriangleStripNormal", SQL_NTS);

		//lưu các giá trị vào data base
		char charInsert[2000], number[20];
		int numberObject;
		std::string stringValue;
		//lưu các thuộc tính(vertex array với normal lưu phần sau)
		numberObject = triaArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleAttribute *tria = triaArray.at(i);
			stringValue.append("insert into TriangleAttribute values(");
			
			snprintf(number, sizeof number, "%f", tria->centerObject.x);
			stringValue+=number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", tria->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", tria->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = triaStripArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			stringValue.append("insert into TriangleStripAttribute values(");

			snprintf(number, sizeof number, "%f", triaStrip->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaStrip->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", triaStrip->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", triaStrip->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = triaFanArray.size();
		for (int i = 0; i < numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			stringValue.append("insert into TriangleFanAttribute values(");

			snprintf(number, sizeof number, "%f", triaFan->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", triaFan->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", triaFan->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", triaFan->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = sphereArray.size();
		for (int i = 0; i < numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			stringValue.append("insert into SphereAttribute values(");

			snprintf(number, sizeof number, "%f", sphere->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->degreeLongitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->degreeLatitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->radius);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", sphere->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", sphere->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = cubeArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			stringValue.append("insert into CubeAttribute values(");

			snprintf(number, sizeof number, "%f", cube->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->numberVertexInAxisX);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->numberVertexInAxisY);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->numberVertexInAxisZ);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = cubeRoundArray.size();
		for (int i = 0; i < numberObject; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);
			stringValue.append("insert into CubeRoundAttribute values(");

			snprintf(number, sizeof number, "%f", cube->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->radiusRound);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->xLength);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->yLength);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->zLength);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cube->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cube->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = coneArray.size();
		for (int i = 0; i < numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);
			stringValue.append("insert into ConeAttribute values(");

			snprintf(number, sizeof number, "%f", cone->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->height);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->radius);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->degreeLongitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->degreeLatitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cone->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cone->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = cylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			stringValue.append("insert into CylinderAttribute values(");

			snprintf(number, sizeof number, "%f", cylinder->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->height);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusUp);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusDown);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->degreeLongitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->degreeLatitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = pyrArray.size();
		for (int i = 0; i < numberObject; i++) {
			PyramidAttribute *pyr = pyrArray.at(i);
			stringValue.append("insert into PyramidAttribute values(");

			snprintf(number, sizeof number, "%f", pyr->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", pyr->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", pyr->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", pyr->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i < numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			stringValue.append("insert into EmptyCylinderAttribute values(");

			snprintf(number, sizeof number, "%f", cylinder->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->height);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusUpIn);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusDownIn);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusUpOut);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->radiusDownOut);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->degreeLongitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->degreeLatitudeLimit);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", cylinder->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", cylinder->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = torusArray.size();
		for (int i = 0; i < numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			stringValue.append("insert into TorusAttribute values(");

			snprintf(number, sizeof number, "%f", torus->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->radiusCake);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->radiusRoundCake);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->widthCake);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", torus->depthCake);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", torus->depthRoundCake);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", torus->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", torus->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", torus->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = pictureArray.size();
		for (int i = 0; i < numberObject; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			stringValue.append("insert into PictureAttribute values(");

			snprintf(number, sizeof number, "%f", picture->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", picture->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", picture->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", picture->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", picture->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = objectCustom0Array.size();
		for (int i = 0; i < numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			stringValue.append("insert into ObjectCustom0Attribute values(");

			snprintf(number, sizeof number, "%f", object->centerObject.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->centerObject.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->centerObject.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->lengthBetween2Row);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->lengthBetween2Column);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", object->numberLongitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", object->numberLatitude);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->colorR);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->colorG);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->colorB);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->colorA);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", object->mShiness);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", object->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", object->idTexture);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}

		//lưu các vertex và normal vector vào trong database
		int numberItem = 0;
		numberObject = triaArray.size();
		for(int i=0;i<numberObject;i++){
			TriangleAttribute *tria = triaArray.at(i);
			for (int j = 0; j < 3; j++) {
				stringValue.append("insert into TriangleVertex values(");

				snprintf(number, sizeof number, "%f", tria->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", tria->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", tria->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", tria->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			stringValue.append("insert into TriangleNormal values(");

			snprintf(number, sizeof number, "%f", tria->normalVector.x);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->normalVector.y);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%f", tria->normalVector.z);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", tria->id);
			stringValue += number;
			stringValue.push_back(',');
			snprintf(number, sizeof number, "%d", 0);
			stringValue += number;
			stringValue.push_back(')');
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
		}
		numberObject = triaStripArray.size();
		for (int i = 0; i<numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			numberItem = triaStrip->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TriangleStripVertex values(");

				snprintf(number, sizeof number, "%f", triaStrip->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaStrip->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaStrip->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", triaStrip->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = triaStrip->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TriangleStripNormal values(");

				snprintf(number, sizeof number, "%f", triaStrip->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaStrip->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaStrip->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", triaStrip->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = triaFanArray.size();
		for (int i = 0; i<numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			numberItem = triaFan->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TriangleFanVertex values(");

				snprintf(number, sizeof number, "%f", triaFan->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaFan->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaFan->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", triaFan->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = triaFan->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TriangleFanNormal values(");

				snprintf(number, sizeof number, "%f", triaFan->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaFan->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", triaFan->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", triaFan->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = sphereArray.size();
		for (int i = 0; i<numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			numberItem = sphere->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into SphereVertex values(");

				snprintf(number, sizeof number, "%f", sphere->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", sphere->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", sphere->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", sphere->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = sphere->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into SphereNormal values(");

				snprintf(number, sizeof number, "%f", sphere->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", sphere->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", sphere->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", sphere->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = cubeArray.size();
		for (int i = 0; i<numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			numberItem = cube->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CubeVertex values(");

				snprintf(number, sizeof number, "%f", cube->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cube->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = cube->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CubeNormal values(");

				snprintf(number, sizeof number, "%f", cube->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cube->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = cubeRoundArray.size();
		for (int i = 0; i<numberObject; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);
			numberItem = cube->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CubeRoundVertex values(");

				snprintf(number, sizeof number, "%f", cube->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cube->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = cube->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CubeRoundNormal values(");

				snprintf(number, sizeof number, "%f", cube->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cube->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cube->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = coneArray.size();
		for (int i = 0; i<numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);
			numberItem = cone->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into ConeVertex values(");

				snprintf(number, sizeof number, "%f", cone->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cone->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cone->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cone->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = cone->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into ConeNormal values(");

				snprintf(number, sizeof number, "%f", cone->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cone->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cone->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cone->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = cylinderArray.size();
		for (int i = 0; i<numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			numberItem = cylinder->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CylinderVertex values(");

				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cylinder->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = cylinder->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into CylinderNormal values(");

				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cylinder->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = pyrArray.size();
		for (int i = 0; i<numberObject; i++) {
			PyramidAttribute *pyr = pyrArray.at(i);
			for (int j = 0; j < 5; j++) {
				stringValue.append("insert into PyramidVertex values(");

				snprintf(number, sizeof number, "%f", pyr->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", pyr->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", pyr->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", pyr->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			for (int j = 0; j < 6; j++) {
				stringValue.append("insert into PyramidNormal values(");

				snprintf(number, sizeof number, "%f", pyr->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", pyr->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", pyr->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", pyr->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i<numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			numberItem = cylinder->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into EmptyCylinderVertex values(");

				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cylinder->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = cylinder->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into EmptyCylinderNormal values(");

				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", cylinder->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", cylinder->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = torusArray.size();
		for (int i = 0; i<numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			numberItem = torus->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TorusVertex values(");

				snprintf(number, sizeof number, "%f", torus->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", torus->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", torus->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", torus->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = torus->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into TorusNormal values(");

				snprintf(number, sizeof number, "%f", torus->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", torus->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", torus->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", torus->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}
		numberObject = pictureArray.size();
		for (int i = 0; i<numberObject; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			for (int j = 0; j < 4; j++) {
				stringValue.append("insert into PictureVertex values(");

				snprintf(number, sizeof number, "%f", picture->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", picture->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", picture->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", picture->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			for (int j = 0; j < 4; j++) {
				stringValue.append("insert into PictureNormal values(");

				snprintf(number, sizeof number, "%f", picture->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", picture->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", picture->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", picture->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}

		numberObject = objectCustom0Array.size();
		for (int i = 0; i<numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			numberItem = object->vertexArray.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into ObjectCustom0Vertex values(");

				snprintf(number, sizeof number, "%f", object->vertexArray[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", object->vertexArray[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", object->vertexArray[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", object->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
			numberItem = object->normalVector.size();
			for (int j = 0; j < numberItem; j++) {
				stringValue.append("insert into ObjectCustom0Normal values(");

				snprintf(number, sizeof number, "%f", object->normalVector[j].x);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", object->normalVector[j].y);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%f", object->normalVector[j].z);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", object->id);
				stringValue += number;
				stringValue.push_back(',');
				snprintf(number, sizeof number, "%d", j);
				stringValue += number;
				stringValue.push_back(')');
				//chuyển string sang mảng array
				strcpy_s(charInsert, 2000, stringValue.c_str());
				SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
				//sau khi dùng xong xóa hết để dùng lần sau
				stringValue.clear();
			}
		}

		printf("DONE");
		//ngắt kết nối khỏi trình điều khiển(việc truy cập,cũng như sửa đổi thông tin phải được thực 
		//hiện trước khi ngắt kết nối,nếu không sẽ không có gì trả về)
		SQLDisconnect(dbc);
	}
	else {
		fprintf(stderr, "Failed to connect\n");
		extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
	}

	//giải phóng xử lý phân bổ
	SQLFreeHandle(SQL_HANDLE_DBC, dbc);
	SQLFreeHandle(SQL_HANDLE_ENV, env);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
}

//hàm kết nối và lấy dữ liệu từ cơ sở dữ liệu
void loadDataBase(vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing) {

	//đầu tiên làm sạch các mảng trước khi bỏ phần tử vào
	triaArray.clear();
	triaStripArray.clear();
	triaFanArray.clear();
	sphereArray.clear();
	cubeArray.clear();
	cubeRoundArray.clear();
	coneArray.clear();
	cylinderArray.clear();
	pyrArray.clear();
	emptyCylinderArray.clear();
	torusArray.clear();
	pictureArray.clear();
	objectCustom0Array.clear();


	SQLHENV env;
	SQLHDBC dbc;
	SQLRETURN ret; /* ODBC API return status */
	SQLWCHAR outstr[1024];
	SQLSMALLINT outstrlen;
	SQLHANDLE stmt_handle;

	//Phân bổ một xử lý môi trường
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	//Chúng tôi muốn hỗ trợ ODBC 3
	SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
	// Phân bổ xử lý kết nối
	SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
	// Kết nối với DSN
	ret = SQLDriverConnectW(dbc, NULL, L"DSN=DataGame;", SQL_NTS, outstr, sizeof(outstr), &outstrlen, SQL_DRIVER_COMPLETE);
	if (SQL_SUCCEEDED(ret)) {
		printf("Connected\n");

		if (ret == SQL_SUCCESS_WITH_INFO) {
			printf("Driver reported the following diagnostics\n");
			extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
		}
		printf("Working . . . \n");
		//lấy ra 1 luồng dùng để try cập thông tin
		SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt_handle);
		//thực hiện lệnh cho sql server

		//lấy các thuộc tính(vertex array với normal lấy phần sau)
		float center_X, center_Y, center_Z,
			colorR, colorG, colorB, colorA, mShiness,
			numberFloat1,numberFloat2,numberFloat3,
			numberFloat4, numberFloat5;
		int id, idTexture, number1, number2, number3, number4;

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from TriangleAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &idTexture, 0, NULL);

			TriangleAttribute *tria = new TriangleAttribute();
			tria->centerObject = { center_X,center_Y,center_Z };
			tria->insertColor(colorR, colorG, colorB, colorA);
			tria->mShiness = mShiness;
			tria->id = id;
			tria->idTexture = idTexture;
			triaArray.push_back(tria);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from TriangleStripAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &idTexture, 0, NULL);

			TriangleStripAttribute *triaStrip = new TriangleStripAttribute();
			triaStrip->centerObject = { center_X,center_Y,center_Z };
			triaStrip->insertColor(colorR, colorG, colorB, colorA);
			triaStrip->mShiness = mShiness;
			triaStrip->id = id;
			triaStrip->idTexture = idTexture;
			triaStripArray.push_back(triaStrip);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from TriangleFanAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &idTexture, 0, NULL);

			TriangleFanAttribute *triaFan = new TriangleFanAttribute();
			triaFan->centerObject = { center_X,center_Y,center_Z };
			triaFan->insertColor(colorR, colorG, colorB, colorA);
			triaFan->mShiness = mShiness;
			triaFan->id = id;
			triaFan->idTexture = idTexture;
			triaFanArray.push_back(triaFan);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from SphereAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_LONG, &number3, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_LONG, &number4, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_LONG, &idTexture, 0, NULL);

			SphereAttribute *sphere = new SphereAttribute();
			sphere->centerObject = { center_X,center_Y,center_Z };
			sphere->numberLongitude = number1;
			sphere->numberLatitude = number2;
			sphere->degreeLongitudeLimit = number3;
			sphere->degreeLatitudeLimit = number4;
			sphere->radius = numberFloat1;
			sphere->insertColor(colorR, colorG, colorB, colorA);
			sphere->mShiness = mShiness;
			sphere->id = id;
			sphere->idTexture = idTexture;
			sphereArray.push_back(sphere);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from CubeAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_LONG, &number3, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_LONG, &idTexture, 0, NULL);

			CubeAttribute *cube = new CubeAttribute();
			cube->centerObject = { center_X,center_Y,center_Z };
			cube->numberVertexInAxisX = number1;
			cube->numberVertexInAxisY = number2;
			cube->numberVertexInAxisZ = number3;
			cube->insertColor(colorR, colorG, colorB, colorA);
			cube->mShiness = mShiness;
			cube->id = id;
			cube->idTexture = idTexture;
			cubeArray.push_back(cube);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from CubeRoundAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &numberFloat3, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_FLOAT, &numberFloat4, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 16, SQL_C_LONG, &idTexture, 0, NULL);

			CubeRoundAttribute *cube = new CubeRoundAttribute();
			cube->centerObject = { center_X,center_Y,center_Z };
			cube->numberLongitude = number1;
			cube->numberLatitude = number2;
			cube->radiusRound = numberFloat1;
			cube->xLength = numberFloat2;
			cube->yLength = numberFloat3;
			cube->zLength = numberFloat4;
			cube->insertColor(colorR, colorG, colorB, colorA);
			cube->mShiness = mShiness;
			cube->id = id;
			cube->idTexture = idTexture;
			cubeRoundArray.push_back(cube);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from ConeAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_LONG, &number3, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &number4, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 16, SQL_C_LONG, &idTexture, 0, NULL);

			ConeAttribute *cone = new ConeAttribute();
			cone->centerObject = { center_X,center_Y,center_Z };
			cone->height = numberFloat1;
			cone->radius = numberFloat2;
			cone->numberLongitude = number1;
			cone->numberLatitude = number2;
			cone->degreeLongitudeLimit = number3;
			cone->degreeLatitudeLimit = number4;
			cone->insertColor(colorR, colorG, colorB, colorA);
			cone->mShiness = mShiness;
			cone->id = id;
			cone->idTexture = idTexture;
			coneArray.push_back(cone);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from CylinderAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &numberFloat3, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &number3, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &number4, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 16, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 17, SQL_C_LONG, &idTexture, 0, NULL);

			CylinderAttribute *cylinder = new CylinderAttribute();
			cylinder->centerObject = { center_X,center_Y,center_Z };
			cylinder->height = numberFloat1;
			cylinder->radiusUp = numberFloat2;
			cylinder->radiusDown = numberFloat3;
			cylinder->numberLongitude = number1;
			cylinder->numberLatitude = number2;
			cylinder->degreeLongitudeLimit = number3;
			cylinder->degreeLatitudeLimit = number4;
			cylinder->insertColor(colorR, colorG, colorB, colorA);
			cylinder->mShiness = mShiness;
			cylinder->id = id;
			cylinder->idTexture = idTexture;
			cylinderArray.push_back(cylinder);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from PyramidAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &idTexture, 0, NULL);

			PyramidAttribute *pyr = new PyramidAttribute();
			pyr->centerObject = { center_X,center_Y,center_Z };
			pyr->insertColor(colorR, colorG, colorB, colorA);
			pyr->mShiness = mShiness;
			pyr->id = id;
			pyr->idTexture = idTexture;
			pyrArray.push_back(pyr);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from EmptyCylinderAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &numberFloat3, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_FLOAT, &numberFloat4, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &numberFloat5, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_LONG, &number3, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_LONG, &number4, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 16, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 17, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 18, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 19, SQL_C_LONG, &idTexture, 0, NULL);

			EmptyCylinderAttribute *cylinder = new EmptyCylinderAttribute();
			cylinder->centerObject = { center_X,center_Y,center_Z };
			cylinder->height = numberFloat1;
			cylinder->radiusUpIn = numberFloat2;
			cylinder->radiusDownIn = numberFloat3;
			cylinder->radiusUpOut = numberFloat4;
			cylinder->radiusDownOut = numberFloat5;
			cylinder->numberLongitude = number1;
			cylinder->numberLatitude = number2;
			cylinder->degreeLongitudeLimit = number3;
			cylinder->degreeLatitudeLimit = number4;
			cylinder->insertColor(colorR, colorG, colorB, colorA);
			cylinder->mShiness = mShiness;
			cylinder->id = id;
			cylinder->idTexture = idTexture;
			emptyCylinderArray.push_back(cylinder);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from TorusAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &numberFloat3, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 15, SQL_C_LONG, &idTexture, 0, NULL);

			TorusAttribute *torus = new TorusAttribute();
			torus->centerObject = { center_X,center_Y,center_Z };
			torus->radiusCake = numberFloat1;
			torus->radiusRoundCake = numberFloat2;
			torus->widthCake = numberFloat3;
			torus->depthCake = number1;
			torus->depthRoundCake = number2;
			torus->insertColor(colorR, colorG, colorB, colorA);
			torus->mShiness = mShiness;
			torus->id = id;
			torus->idTexture = idTexture;
			torusArray.push_back(torus);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from PictureAttribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_LONG, &idTexture, 0, NULL);

			PictureAttribute *picture = new PictureAttribute();
			picture->centerObject = { center_X,center_Y,center_Z };
			picture->id = id;
			picture->idTexture = idTexture;
			pictureArray.push_back(picture);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);

		SQLExecDirect(stmt_handle, (SQLCHAR*)"select * from ObjectCustom0Attribute", SQL_NTS);
		while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
			SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &center_X, 0, NULL);
			SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &center_Y, 0, NULL);
			SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &center_Z, 0, NULL);
			SQLGetData(stmt_handle, 4, SQL_C_FLOAT, &numberFloat1, 0, NULL);
			SQLGetData(stmt_handle, 5, SQL_C_FLOAT, &numberFloat2, 0, NULL);
			SQLGetData(stmt_handle, 6, SQL_C_LONG, &number1, 0, NULL);
			SQLGetData(stmt_handle, 7, SQL_C_LONG, &number2, 0, NULL);
			SQLGetData(stmt_handle, 8, SQL_C_FLOAT, &colorR, 0, NULL);
			SQLGetData(stmt_handle, 9, SQL_C_FLOAT, &colorG, 0, NULL);
			SQLGetData(stmt_handle, 10, SQL_C_FLOAT, &colorB, 0, NULL);
			SQLGetData(stmt_handle, 11, SQL_C_FLOAT, &colorA, 0, NULL);
			SQLGetData(stmt_handle, 12, SQL_C_FLOAT, &mShiness, 0, NULL);
			SQLGetData(stmt_handle, 13, SQL_C_LONG, &id, 0, NULL);
			SQLGetData(stmt_handle, 14, SQL_C_LONG, &idTexture, 0, NULL);

			ObjectCustom0Attribute *object = new ObjectCustom0Attribute();
			object->centerObject = { center_X,center_Y,center_Z };
			object->lengthBetween2Row = numberFloat1;
			object->lengthBetween2Column = numberFloat2;
			object->numberLongitude = number1;
			object->numberLatitude = number2;
			object->insertColor(colorR, colorG, colorB, colorA);
			object->mShiness = mShiness;
			object->id = id;
			object->idTexture = idTexture;

			objectCustom0Array.push_back(object);
			//đặt các id của vật vào mảng các id được chọn
			idsUsing.push_back(id);
		}
		//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
		SQLFreeStmt(stmt_handle, SQL_CLOSE);


		//lấy ra các vertex và normal cho các hình đã định nghĩa
		char charInsert[2000], number[20];
		std::string stringValue;
		int numberNow = 0,numberObject;

		numberObject = triaArray.size();
		for(int i=0;i<numberObject;i++){
			TriangleAttribute *tria = triaArray.at(i);
			numberNow = 0;

			stringValue.append("select * from TriangleVertex where id=");
			snprintf(number, sizeof number, "%d", tria->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				tria->vertexArray[numberNow] = { numberFloat1,numberFloat2,numberFloat3 };
				numberNow++;
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

			stringValue.append("select * from TriangleNormal where id=");
			snprintf(number, sizeof number, "%d", tria->id);
			stringValue += number;
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				tria->normalVector = { numberFloat1,numberFloat2,numberFloat3 };
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = triaStripArray.size();
		for (int i = 0; i<numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);

			stringValue.append("select * from TriangleStripVertex where id=");
			snprintf(number, sizeof number, "%d", triaStrip->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				triaStrip->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from TriangleStripNormal where id=");
			snprintf(number, sizeof number, "%d", triaStrip->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				triaStrip->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = triaFanArray.size();
		for (int i = 0; i<numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);

			stringValue.append("select * from TriangleFanVertex where id=");
			snprintf(number, sizeof number, "%d", triaFan->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				triaFan->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from TriangleFanNormal where id=");
			snprintf(number, sizeof number, "%d", triaFan->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				triaFan->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = sphereArray.size();
		for (int i = 0; i<numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);

			stringValue.append("select * from SphereVertex where id=");
			snprintf(number, sizeof number, "%d", sphere->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				sphere->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from SphereNormal where id=");
			snprintf(number, sizeof number, "%d", sphere->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				sphere->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = cubeArray.size();
		for (int i = 0; i<numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);

			stringValue.append("select * from CubeVertex where id=");
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cube->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

			stringValue.append("select * from CubeNormal where id=");
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cube->normalVector.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = cubeRoundArray.size();
		for (int i = 0; i<numberObject; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);

			stringValue.append("select * from CubeRoundVertex where id=");
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cube->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from CubeRoundNormal where id=");
			snprintf(number, sizeof number, "%d", cube->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cube->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = coneArray.size();
		for (int i = 0; i<numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);

			stringValue.append("select * from ConeVertex where id=");
			snprintf(number, sizeof number, "%d", cone->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cone->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from ConeNormal where id=");
			snprintf(number, sizeof number, "%d", cone->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cone->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = cylinderArray.size();
		for (int i = 0; i<numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);

			stringValue.append("select * from CylinderVertex where id=");
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cylinder->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from CylinderNormal where id=");
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cylinder->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = pyrArray.size();
		for (int i = 0; i<numberObject; i++) {
			PyramidAttribute *pyr = pyrArray.at(i);
			numberNow = 0;

			stringValue.append("select * from PyramidVertex where id=");
			snprintf(number, sizeof number, "%d", pyr->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				pyr->vertexArray[numberNow] = { numberFloat1,numberFloat2,numberFloat3 };
				numberNow++;
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			numberNow = 0;
			stringValue.append("select * from PyramidNormal where id=");
			snprintf(number, sizeof number, "%d", pyr->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				pyr->normalVector[numberNow] = { numberFloat1,numberFloat2,numberFloat3 };
				numberNow++;
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = emptyCylinderArray.size();
		for (int i = 0; i<numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);

			stringValue.append("select * from EmptyCylinderVertex where id=");
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cylinder->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from EmptyCylinderNormal where id=");
			snprintf(number, sizeof number, "%d", cylinder->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				cylinder->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = torusArray.size();
		for (int i = 0; i<numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);

			stringValue.append("select * from TorusVertex where id=");
			snprintf(number, sizeof number, "%d", torus->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				torus->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from TorusNormal where id=");
			snprintf(number, sizeof number, "%d", torus->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				torus->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}
		numberObject = pictureArray.size();
		for (int i = 0; i<numberObject; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			numberNow = 0;

			stringValue.append("select * from PictureVertex where id=");
			snprintf(number, sizeof number, "%d", picture->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				picture->vertexArray[numberNow] = { numberFloat1,numberFloat2,numberFloat3 };
				numberNow++;
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			numberNow = 0;
			stringValue.append("select * from PictureNormal where id=");
			snprintf(number, sizeof number, "%d", picture->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				picture->normalVector[numberNow] = { numberFloat1,numberFloat2,numberFloat3 };
				numberNow++;
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}

		numberObject = objectCustom0Array.size();
		for (int i = 0; i<numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);

			stringValue.append("select * from ObjectCustom0Vertex where id=");
			snprintf(number, sizeof number, "%d", object->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				object->vertexArray.push_back({ numberFloat1, numberFloat2, numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);


			stringValue.append("select * from ObjectCustom0Normal where id=");
			snprintf(number, sizeof number, "%d", object->id);
			stringValue += number;
			stringValue += " order by position asc";
			//chuyển string sang mảng array
			strcpy_s(charInsert, 2000, stringValue.c_str());
			SQLExecDirect(stmt_handle, (SQLCHAR*)charInsert, SQL_NTS);
			//sau khi dùng xong xóa hết để dùng lần sau
			stringValue.clear();
			while (SQLFetch(stmt_handle) == SQL_SUCCESS) {
				SQLGetData(stmt_handle, 1, SQL_C_FLOAT, &numberFloat1, 0, NULL);
				SQLGetData(stmt_handle, 2, SQL_C_FLOAT, &numberFloat2, 0, NULL);
				SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &numberFloat3, 0, NULL);

				object->normalVector.push_back({ numberFloat1,numberFloat2,numberFloat3 });
			}
			//giải phóng dữ liệu đã cấp phát cho luồng để sử dụng lại
			SQLFreeStmt(stmt_handle, SQL_CLOSE);

		}

		printf("DONE");
		//ngắt kết nối khỏi trình điều khiển(việc truy cập,cũng như sửa đổi thông tin phải được thực 
		//hiện trước khi ngắt kết nối,nếu không sẽ không có gì trả về)
		SQLDisconnect(dbc);
	}
	else {
		fprintf(stderr, "Failed to connect\n");
		extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
	}

	//giải phóng xử lý phân bổ
	SQLFreeHandle(SQL_HANDLE_DBC, dbc);
	SQLFreeHandle(SQL_HANDLE_ENV, env);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
}
//hàm lưu lại các thông tin về các đối tượng trên app vào .txt
void saveObjectsInTxt(char *nameTxt,
	vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	string stringPath;
	int numberElement, numberVertex;

	//ghi các thông tin vào tệp txt
	ofstream myfile(nameTxt);
	if (myfile.is_open()) {
		numberElement = triaArray.size();
		for (int i = 0; i < numberElement; i++) {
			TriangleAttribute *tria = triaArray.at(i);
			//đàu tiên in ra số đại diện cho tam giác
			myfile << "O 3" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << tria->centerObject.x << " " << tria->centerObject.y << " " << tria->centerObject.z << " "
				<< tria->colorR << " " << tria->colorG << " " << tria->colorB << " " << tria->colorA << " "
				<< tria->mShiness << " " << tria->id << " " << tria->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			myfile << "V {";
			for (int j = 0; j < 3; j++) {
				myfile << "{" << tria->vertexArray[j].x << "," << tria->vertexArray[j].y << "," << tria->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			myfile << "N {{" << tria->normalVector.x << "," << tria->normalVector.y << "," << tria->normalVector.z << "}}\n";
		}
		numberElement = triaStripArray.size();
		for (int i = 0; i < numberElement; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			//đàu tiên in ra số đại diện cho triangle strip
			myfile << "O 4" << "\n";
			//tiếp theo in ra các thuôc tínhc theo thứ tự
			myfile << "A " << triaStrip->centerObject.x << " " << triaStrip->centerObject.y << " " << triaStrip->centerObject.z << " "
				<< triaStrip->colorR << " " << triaStrip->colorG << " " << triaStrip->colorB << " " << triaStrip->colorA << " "
				<< triaStrip->mShiness << " " << triaStrip->id << " " << triaStrip->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = triaStrip->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << triaStrip->vertexArray[j].x << "," << triaStrip->vertexArray[j].y << "," << triaStrip->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = triaStrip->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << triaStrip->normalVector[j].x << "," << triaStrip->normalVector[j].y
					<< "," << triaStrip->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = triaFanArray.size();
		for (int i = 0; i < numberElement; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			//đàu tiên in ra số đại diện cho triangle fan
			myfile << "O 5" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << triaFan->centerObject.x << " " << triaFan->centerObject.y << " " << triaFan->centerObject.z << " "
				<< triaFan->colorR << " " << triaFan->colorG << " " << triaFan->colorB << " " << triaFan->colorA << " "
				<< triaFan->mShiness << " " << triaFan->id << " " << triaFan->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = triaFan->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << triaFan->vertexArray[j].x << "," << triaFan->vertexArray[j].y << "," << triaFan->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = triaFan->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << triaFan->normalVector[j].x << "," << triaFan->normalVector[j].y
					<< "," << triaFan->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = sphereArray.size();
		for (int i = 0; i < numberElement; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 10" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << sphere->centerObject.x << " " << sphere->centerObject.y << " " << sphere->centerObject.z << " "
				<< sphere->numberLongitude << " " << sphere->numberLatitude << " "
				<< sphere->degreeLongitudeLimit << " " << sphere->degreeLatitudeLimit << " " << sphere->radius << " "
				<< sphere->colorR << " " << sphere->colorG << " " << sphere->colorB << " " << sphere->colorA << " "
				<< sphere->mShiness << " " << sphere->id << " " << sphere->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = sphere->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << sphere->vertexArray[j].x << "," << sphere->vertexArray[j].y << "," << sphere->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = sphere->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << sphere->normalVector[j].x << "," << sphere->normalVector[j].y
					<< "," << sphere->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = cubeArray.size();
		for (int i = 0; i < numberElement; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			//đàu tiên in ra số đại diện cho cube
			myfile << "O 11" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
				<< cube->numberVertexInAxisX << " " << cube->numberVertexInAxisY << " " << cube->numberVertexInAxisZ << " "
				<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
				<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = cube->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cube->vertexArray[j].x << "," << cube->vertexArray[j].y << "," << cube->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = cube->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cube->normalVector[j].x << "," << cube->normalVector[j].y
					<< "," << cube->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = cubeRoundArray.size();
		for (int i = 0; i < numberElement; i++) {
			CubeRoundAttribute *cube = cubeRoundArray.at(i);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 12" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
				<< cube->numberLongitude << " " << cube->numberLatitude << " " << cube->radiusRound << " "
				<< cube->xLength << " " << cube->yLength << " " << cube->zLength << " "
				<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
				<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = cube->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cube->vertexArray[j].x << "," << cube->vertexArray[j].y << "," << cube->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = cube->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cube->normalVector[j].x << "," << cube->normalVector[j].y
					<< "," << cube->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = coneArray.size();
		for (int i = 0; i < numberElement; i++) {
			ConeAttribute *cone = coneArray.at(i);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 13" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cone->centerObject.x << " " << cone->centerObject.y << " " << cone->centerObject.z << " "
				<< cone->height << " " << cone->radius << " "
				<< cone->numberLongitude << " " << cone->numberLatitude << " "
				<< cone->degreeLongitudeLimit << " " << cone->degreeLatitudeLimit << " "
				<< cone->colorR << " " << cone->colorG << " " << cone->colorB << " " << cone->colorA << " "
				<< cone->mShiness << " " << cone->id << " " << cone->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = cone->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cone->vertexArray[j].x << "," << cone->vertexArray[j].y << "," << cone->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = cone->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cone->normalVector[j].x << "," << cone->normalVector[j].y
					<< "," << cone->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = cylinderArray.size();
		for (int i = 0; i < numberElement; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			//đàu tiên in ra số đại diện cho cylinder
			myfile << "O 14" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
				<< cylinder->height << " " << cylinder->radiusUp << " " << cylinder->radiusDown << " "
				<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
				<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
				<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
				<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = cylinder->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cylinder->vertexArray[j].x << "," << cylinder->vertexArray[j].y << "," << cylinder->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = cylinder->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cylinder->normalVector[j].x << "," << cylinder->normalVector[j].y
					<< "," << cylinder->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = emptyCylinderArray.size();
		for (int i = 0; i < numberElement; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			//đàu tiên in ra số đại diện cho empty cylinder
			myfile << "O 16" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
				<< cylinder->height << " " << cylinder->radiusUpIn << " " << cylinder->radiusDownIn << " "
				<< cylinder->radiusUpOut << " " << cylinder->radiusDownOut << " "
				<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
				<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
				<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
				<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = cylinder->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cylinder->vertexArray[j].x << "," << cylinder->vertexArray[j].y << "," << cylinder->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = cylinder->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << cylinder->normalVector[j].x << "," << cylinder->normalVector[j].y
					<< "," << cylinder->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = torusArray.size();
		for (int i = 0; i < numberElement; i++) {
			TorusAttribute *torus = torusArray.at(i);
			//đàu tiên in ra số đại diện cho empty cylinder
			myfile << "O 17" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << torus->centerObject.x << " " << torus->centerObject.y << " " << torus->centerObject.z << " "
				<< torus->radiusCake << " " << torus->radiusRoundCake << " " << torus->widthCake << " "
				<< torus->depthCake << " " << torus->depthRoundCake << " "
				<< torus->colorR << " " << torus->colorG << " " << torus->colorB << " " << torus->colorA << " "
				<< torus->mShiness << " " << torus->id << " " << torus->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = torus->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << torus->vertexArray[j].x << "," << torus->vertexArray[j].y << "," << torus->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = torus->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << torus->normalVector[j].x << "," << torus->normalVector[j].y
					<< "," << torus->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = pictureArray.size();
		for (int i = 0; i < numberElement; i++) {
			PictureAttribute *picture = pictureArray.at(i);
			//đàu tiên in ra số đại diện cho tam giác
			myfile << "O 18" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << picture->centerObject.x << " " << picture->centerObject.y << " " << picture->centerObject.z << " "
				<< picture->id << " " << picture->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			myfile << "V {";
			for (int j = 0; j < 4; j++) {
				myfile << "{" << picture->vertexArray[j].x << "," << picture->vertexArray[j].y << "," << picture->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			myfile << "N {";
			for (int j = 0; j < 4; j++) {
				myfile << "{" << picture->normalVector[j].x << "," << picture->normalVector[j].y << "," << picture->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		numberElement = objectCustom0Array.size();
		for (int i = 0; i < numberElement; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			//đàu tiên in ra số đại diện cho ObjectCustom0
			myfile << "O 19" << "\n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << object->centerObject.x << " " << object->centerObject.y << " " << object->centerObject.z << " "
				<< object->lengthBetween2Row << " " << object->lengthBetween2Column << " "
				<< object->numberLongitude << " " << object->numberLatitude << " "
				<< object->colorR << " " << object->colorG << " " << object->colorB << " " << object->colorA << " "
				<< object->mShiness << " " << object->id << " " << object->idTexture << " "
				<< "\n";
			//in ra các vertex theo thứ tự
			numberVertex = object->vertexArray.size();
			myfile << "V {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << object->vertexArray[j].x << "," << object->vertexArray[j].y << "," << object->vertexArray[j].z << "}";
			}
			myfile << "}\n";
			//in ra normal vector
			numberVertex = object->normalVector.size();
			myfile << "N {";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{" << object->normalVector[j].x << "," << object->normalVector[j].y
					<< "," << object->normalVector[j].z << "}";
			}
			myfile << "}\n";
		}
		myfile.close();
	}
}

//hàm lưu các thông tin về thuộc tính của ứng dụng vào tệp .txt
void saveAttributeApp(char *nameTxt,
	vector<int> positionVerticesChoice, vector<int> positionFacesChoice,
	vector<PositionRowOrColumn> positionChoiceRowOrColumn,
	point centerObjectOrVertices, point centerObjectOrVerticesSymmetry,
	vector<itemChoice> itemsChoice, int mouseModel, int modelStyleDraw, int modelTop,
	int modelEditStyle, int modelSpace, int modelMenuGroup1, int modelMenuGroup2,
	int whichStyleRound, int numberVertexRound2Side, int numberVertexRoundHorizontal,int numberVertexRoundVertical,
	float radiusRound2Side, float radiusRoundHorizontal, float radiusRoundVertical,
	int menu_whichTransform, float menu_translateX, float menu_translateY, float menu_translateZ,
	float menu_rotateX, float menu_rotateY, float menu_rotateZ,
	float menu_scaleX, float menu_scaleY, float menu_scaleZ,
	bool symmetryVertexOrObject, int whichStyleSymmetry, int whichItemSymmetry,
	bool symmetry_translateX,bool symmetry_translateY,bool symmetry_translateZ,
	bool symmetry_rotateX,bool symmetry_rotateY,bool symmetry_rotateZ,
	bool symmetry_scaleX,bool symmetry_scaleY,bool symmetry_scaleZ,
	vector<SymmetryVertices> symmetryVertices, vector<SymmetryObjects> symmetryObjects,
	int *startAndEndSymmetry1, int *startAndEndSymmetry2,
	bool isGetSymmetryLikeClockwise1, bool isGetSymmetryLikeClockwise2,
	bool tool_isShowBeforeDraw, bool tool_isRemind, bool tool_isDrawNet,
	float tool_arrowSize, float tool_circleSize) {

	int numberElement, numberElement2, elementCheck;
	PositionRowOrColumn rowOrColumnCheck;
	SymmetryVertices symmetryVerticesCheck;
	SymmetryObjects symmetryObjectsCheck;
	itemChoice itemCheck;
	ofstream myfile(nameTxt);
	if (myfile.is_open()){
		numberElement = positionVerticesChoice.size();
		if (numberElement > 0) {
			myfile << "A ";
			for (int i = 0; i < numberElement; i++) {
				myfile << positionVerticesChoice.at(i) << " " ;
			}
			myfile << "\n";
		}
		numberElement = positionFacesChoice.size();
		if (numberElement > 0) {
			myfile << "B ";
			for (int i = 0; i < numberElement; i++) {
				myfile << positionFacesChoice.at(i) << " ";
			}
			myfile << "\n";
		}
		numberElement = positionChoiceRowOrColumn.size();
		if (numberElement > 0) {
			myfile << "C ";
			for (int i = 0; i < numberElement; i++) {
				rowOrColumnCheck = positionChoiceRowOrColumn.at(i);
				myfile << "{" << rowOrColumnCheck.positionRow << ","
					<< rowOrColumnCheck.positionColumn << ","
					<< rowOrColumnCheck.positionColumnOpposite << "}";
			}
			myfile << "\n";
		}
		myfile << "D {" << centerObjectOrVertices.x << ","
			<< centerObjectOrVertices.y << ","
			<< centerObjectOrVertices.z << "}"
			<< "{" << centerObjectOrVerticesSymmetry.x << ","
			<< centerObjectOrVerticesSymmetry.y << ","
			<< centerObjectOrVerticesSymmetry.z << "}\n";

		numberElement = itemsChoice.size();
		if (numberElement > 0) {
			myfile << "E ";
			for (int i = 0; i < numberElement; i++) {
				itemCheck = itemsChoice.at(i);
				myfile << "{" << itemCheck.object << ","
					<< itemCheck.id << ","
					<< itemCheck.positionOfChoice << "}";
			}
			myfile << "\n";
		}
		myfile << "F " << mouseModel << " " << modelStyleDraw << " " << modelTop << " "
			<< modelEditStyle << " " << modelSpace << " " << modelMenuGroup1 << " " << modelMenuGroup2 << " "
			<< whichStyleRound << " " << numberVertexRound2Side << " " << numberVertexRoundHorizontal << " "
			<< numberVertexRoundVertical << " \n";
		myfile << "G " << radiusRound2Side << " " << radiusRoundHorizontal << " " << radiusRoundVertical << " "
			<< menu_whichTransform << " " << menu_translateX << " " << menu_translateY << " " << menu_translateZ << " "
			<< menu_rotateX << " " << menu_rotateY << " " << menu_rotateZ << " "
			<< menu_scaleX << " " << menu_scaleY << " " << menu_scaleZ << " \n";
		myfile << "H " << symmetryVertexOrObject << " " << whichStyleSymmetry << " " << whichItemSymmetry << " "
			<< symmetry_translateX << " " << symmetry_translateY << " " << symmetry_translateZ << " "
			<< symmetry_rotateX << " " << symmetry_rotateY << " " << symmetry_rotateZ << " "
			<< symmetry_scaleX << " " << symmetry_scaleY << " " << symmetry_scaleZ << " \n";

		numberElement = symmetryVertices.size();
		if (numberElement > 0) {
			myfile << "I ";
			for (int i = 0; i < numberElement; i++) {
				symmetryVerticesCheck = symmetryVertices.at(i);
				myfile << symmetryVerticesCheck.object << " >"
					<< symmetryVerticesCheck.positionInArray << " >";
				//load mảng các positionROrC1
				numberElement2 = symmetryVerticesCheck.positionROrC1.size();
				for (int j = 0; j < numberElement2; j++) {
					rowOrColumnCheck = symmetryVerticesCheck.positionROrC1.at(j);
					myfile << "{" << rowOrColumnCheck.positionRow << ","
						<< rowOrColumnCheck.positionColumn << ","
						<< rowOrColumnCheck.positionColumnOpposite << "}";
				}
				myfile << ">";
				//load mảng các positionROrC2
				numberElement2 = symmetryVerticesCheck.positionROrC2.size();
				for (int j = 0; j < numberElement2; j++) {
					rowOrColumnCheck = symmetryVerticesCheck.positionROrC2.at(j);
					myfile << "{" << rowOrColumnCheck.positionRow << ","
						<< rowOrColumnCheck.positionColumn << ","
						<< rowOrColumnCheck.positionColumnOpposite << "}";
				}
				myfile << ">";
				//load mảng các positionVertices1
				numberElement2 = symmetryVerticesCheck.positionVertices1.size();
				for (int j = 0; j < numberElement2; j++) {
					myfile << symmetryVerticesCheck.positionVertices1.at(j) << " ";
				}
				myfile << ">";
				//load mảng các positionVertices2
				numberElement2 = symmetryVerticesCheck.positionVertices2.size();
				for (int j = 0; j < numberElement2; j++) {
					myfile << symmetryVerticesCheck.positionVertices2.at(j) << " ";
				}
				//dấu này là kết thúc đọc củ 1 phần tử trong symmetryVertices
				myfile << "<";
			}
			myfile << "\n";
		}

		numberElement = symmetryObjects.size();
		if (numberElement > 0) {
			myfile << "J ";
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectsCheck = symmetryObjects.at(i);
				myfile << symmetryObjectsCheck.object1 << " >"
					<< symmetryObjectsCheck.positionInArray1 << " >"
					<< symmetryObjectsCheck.object2 << " >"
					<< symmetryObjectsCheck.positionInArray2 << " >"
					<< symmetryObjectsCheck.isInvertedItemsInRow << " >"
					<< symmetryObjectsCheck.numberItemInRow << " ";

				//dấu này là kết thúc đọc củ 1 phần tử trong symmetryObjects
				myfile << "<";
			}
			myfile << "\n";
		}

		myfile << "K " << startAndEndSymmetry1[0] << " " << startAndEndSymmetry1[1] << " "
			<< startAndEndSymmetry2[0] << " " << startAndEndSymmetry2[1] << " "
			<< isGetSymmetryLikeClockwise1 << " " << isGetSymmetryLikeClockwise2 << " "
			<< tool_isShowBeforeDraw << " " << tool_isRemind << " " << tool_isDrawNet << " "
			<< tool_arrowSize << " " << tool_circleSize << " \n";
	}
}
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
	float &tool_arrowSize, float &tool_circleSize){

	//làm sạch các giá trị là vector
	positionVerticesChoice.clear();
	positionFacesChoice.clear();
	positionChoiceRowOrColumn.clear();
	itemsChoice.clear();
	symmetryVertices.clear();
	symmetryObjects.clear();

	string stringPath;
	//các biến lưu giá trị cho thuộc tính
	int numberElement1, startOffset, offsetGetValue;
	char charNumber[20];

	ifstream myfile(nameTxt);
	if (myfile.is_open()) {
		while (getline(myfile, stringPath))
		{
			switch (stringPath[0])
			{
			case 'A': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						positionVerticesChoice.push_back(atoi(charNumber));
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
					}
				}
			}
					  break;
			case 'B': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						positionFacesChoice.push_back(atoi(charNumber));
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
					}
				}
			}
					  break;
			case 'C': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '{') {
						startOffset = i + 1;
						offsetGetValue = 0;
					}
					else if (stringPath[i] == ',' || stringPath[i] == '}') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						if (offsetGetValue == 0) {
							positionChoiceRowOrColumn.push_back({ atoi(charNumber),-1,-1 });
						}else if (offsetGetValue == 1) {
							positionChoiceRowOrColumn.back().positionColumn = atoi(charNumber);
						}
						else {
							positionChoiceRowOrColumn.back().positionColumnOpposite = atoi(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'D': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '{') {
						startOffset = i + 1;
					}
					else if (stringPath[i] == ',' || stringPath[i] == '}') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						if (offsetGetValue == 0) {
							centerObjectOrVertices.x = atof(charNumber);
						}
						else if (offsetGetValue == 1) {
							centerObjectOrVertices.y = atof(charNumber);
						}
						else if (offsetGetValue == 2) {
							centerObjectOrVertices.z = atof(charNumber);
						}
						else if (offsetGetValue == 3) {
							centerObjectOrVerticesSymmetry.x = atof(charNumber);
						}
						else if (offsetGetValue == 4) {
							centerObjectOrVerticesSymmetry.y = atof(charNumber);
						}
						else {
							centerObjectOrVerticesSymmetry.z = atof(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'E': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '{') {
						startOffset = i + 1;
						offsetGetValue = 0;
					}
					else if (stringPath[i] == ',' || stringPath[i] == '}') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						if (offsetGetValue == 0) {
							itemsChoice.push_back({ atoi(charNumber),-1,-1 });
						}
						else if (offsetGetValue == 1) {
							itemsChoice.back().id = atoi(charNumber);
						}
						else {
							itemsChoice.back().positionOfChoice = atoi(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'F': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						if (offsetGetValue == 0) {
							mouseModel = atoi(charNumber);
						}
						else if (offsetGetValue == 1) {
							modelStyleDraw = atoi(charNumber);
						}
						else if (offsetGetValue == 2) {
							modelTop = atoi(charNumber);
						}
						else if (offsetGetValue == 3) {
							modelEditStyle = atoi(charNumber);
						}
						else if (offsetGetValue == 4) {
							modelSpace = atoi(charNumber);
						}
						else if (offsetGetValue == 5) {
							modelMenuGroup1 = atoi(charNumber);
						}
						else if (offsetGetValue == 6) {
							modelMenuGroup2 = atoi(charNumber);
						}
						else if (offsetGetValue == 7) {
							whichStyleRound = atoi(charNumber);
						}
						else if (offsetGetValue == 8) {
							numberVertexRound2Side = atoi(charNumber);
						}
						else if (offsetGetValue == 9) {
							numberVertexRoundHorizontal = atoi(charNumber);
						}
						else {
							numberVertexRoundVertical = atoi(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'G': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						if (offsetGetValue == 0) {
							radiusRound2Side = atof(charNumber);
						}
						else if (offsetGetValue == 1) {
							radiusRoundHorizontal = atof(charNumber);
						}
						else if (offsetGetValue == 2) {
							radiusRoundVertical = atof(charNumber);
						}
						else if (offsetGetValue == 3) {
							menu_whichTransform = atof(charNumber);
						}
						else if (offsetGetValue == 4) {
							menu_translateX = atof(charNumber);
						}
						else if (offsetGetValue == 5) {
							menu_translateY = atof(charNumber);
						}
						else if (offsetGetValue == 6) {
							menu_translateZ = atof(charNumber);
						}
						else if (offsetGetValue == 7) {
							menu_rotateX = atof(charNumber);
						}
						else if (offsetGetValue == 8) {
							menu_rotateY = atof(charNumber);
						}
						else if (offsetGetValue == 9) {
							menu_rotateZ = atof(charNumber);
						}
						else if (offsetGetValue == 10) {
							menu_scaleX = atof(charNumber);
						}
						else if (offsetGetValue == 11) {
							menu_scaleY = atof(charNumber);
						}
						else {
							menu_scaleZ = atof(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'H': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						if (offsetGetValue == 0) {
							symmetryVertexOrObject = atoi(charNumber);
						}
						else if (offsetGetValue == 1) {
							whichStyleSymmetry = atoi(charNumber);
						}
						else if (offsetGetValue == 2) {
							whichItemSymmetry = atoi(charNumber);
						}
						else if (offsetGetValue == 3) {
							symmetry_translateX = atoi(charNumber);
						}
						else if (offsetGetValue == 4) {
							symmetry_translateY = atoi(charNumber);
						}
						else if (offsetGetValue == 5) {
							symmetry_translateZ = atoi(charNumber);
						}
						else if (offsetGetValue == 6) {
							symmetry_rotateX = atoi(charNumber);
						}
						else if (offsetGetValue == 7) {
							symmetry_rotateY = atoi(charNumber);
						}
						else if (offsetGetValue == 8) {
							symmetry_rotateZ = atoi(charNumber);
						}
						else if (offsetGetValue == 9) {
							symmetry_scaleX = atoi(charNumber);
						}
						else if (offsetGetValue == 10) {
							symmetry_scaleY = atoi(charNumber);
						}
						else {
							symmetry_scaleZ = atoi(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			case 'I': {
				//biến này thông báo lấy các biến khác nhau trong 1 item symmtry
				int offsetSymmetry = 0;
				numberElement1 = stringPath.size();
				startOffset = 2;
				//biến này thông báo lấy các item khác nhau trong các mảng phía trong
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if(stringPath[i] == '>'){
						offsetSymmetry++;

						startOffset = i + 1;
					}
					else if (stringPath[i] == '<'){
						offsetSymmetry = 0;

						startOffset = i + 1;
					}
					else
					{
						//nếu đang đọc object
						if (offsetSymmetry == 0) {
							if (stringPath[i] == ' ') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								//tạo 1 đối tượng mới để bỏ vào
								SymmetryVertices sym;
								sym.object = atoi(charNumber);
								symmetryVertices.push_back(sym);
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
							}
						}
						//nếu đang đọc vị trí positionInArray
						else if (offsetSymmetry == 1) {
							if (stringPath[i] == ' ') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								symmetryVertices.back().positionInArray = atoi(charNumber);
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
							}
						}
						//nếu đang đọc positionROrC1
						else if (offsetSymmetry == 2) {
							if (stringPath[i] == '{'){
								startOffset = i + 1;
								offsetGetValue = 0;
							}
							else if (stringPath[i] == ',' || stringPath[i] == '}') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								if (offsetGetValue == 0) {
									symmetryVertices.back().positionROrC1.push_back({ atoi(charNumber),-1,-1 });
								}else if(offsetGetValue==1){
									symmetryVertices.back().positionROrC1.back().positionColumn = atoi(charNumber);
								}
								else {
									symmetryVertices.back().positionROrC1.back().positionColumnOpposite = atoi(charNumber);
								}
								
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
								startOffset = i + 1;
								offsetGetValue++;
							}
						}
						//nếu đang đọc positionROrC2
						else if (offsetSymmetry == 3) {
							if (stringPath[i] == '{') {
								startOffset = i + 1;
								offsetGetValue = 0;
							}
							else if (stringPath[i] == ',' || stringPath[i] == '}') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								if (offsetGetValue == 0) {
									symmetryVertices.back().positionROrC2.push_back({ atoi(charNumber),-1,-1 });
								}
								else if (offsetGetValue == 1) {
									symmetryVertices.back().positionROrC2.back().positionColumn = atoi(charNumber);
								}
								else {
									symmetryVertices.back().positionROrC2.back().positionColumnOpposite = atoi(charNumber);
								}

								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
								startOffset = i + 1;
								offsetGetValue++;
							}
						}
						//nếu đang đọc positionVertices1
						else if (offsetSymmetry == 4) {
							if (stringPath[i] == ' ') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								symmetryVertices.back().positionVertices1.push_back(atoi(charNumber));
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
								startOffset = i + 1;
							}
						}
						//nếu đang đọc positionVertices2
						else if (offsetSymmetry == 5) {
							if (stringPath[i] == ' ') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								symmetryVertices.back().positionVertices2.push_back(atoi(charNumber));
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
								startOffset = i + 1;
							}
						}
					}
				}
			}
					  break;
			case 'J':{
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '>') {
						offsetGetValue++;

						startOffset = i + 1;
					}
					else if (stringPath[i] == '<') {
						offsetGetValue = 0;

						startOffset = i + 1;
					}
					else if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						if (offsetGetValue == 0) {
							//tạo 1 phần tử mới và gán giá trị
							SymmetryObjects newSymmetry;
							newSymmetry.object1 = atoi(charNumber);

							symmetryObjects.push_back(newSymmetry);
						}
						else if (offsetGetValue == 1) {
							symmetryObjects.back().positionInArray1 = atoi(charNumber);
						}
						else if (offsetGetValue == 2) {
							symmetryObjects.back().object2 = atoi(charNumber);
						}
						else if (offsetGetValue == 3) {
							symmetryObjects.back().positionInArray2 = atoi(charNumber);
						}
						else if (offsetGetValue == 4) {
							symmetryObjects.back().isInvertedItemsInRow = atoi(charNumber);
						}
						else if (offsetGetValue == 5) {
							symmetryObjects.back().numberItemInRow = atoi(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
					}
				}
			}
					 break;
			case 'K': {
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ' ') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						if (offsetGetValue == 0) {
							startAndEndSymmetry1[0] = atoi(charNumber);
						}
						else if (offsetGetValue == 1) {
							startAndEndSymmetry1[1] = atoi(charNumber);
						}
						else if (offsetGetValue == 2) {
							startAndEndSymmetry2[0] = atoi(charNumber);
						}
						else if (offsetGetValue == 3) {
							startAndEndSymmetry2[1] = atoi(charNumber);
						}
						else if (offsetGetValue == 4) {
							isGetSymmetryLikeClockwise1 = atoi(charNumber);
						}
						else if (offsetGetValue == 5) {
							isGetSymmetryLikeClockwise2 = atoi(charNumber);
						}
						else if (offsetGetValue == 6) {
							tool_isShowBeforeDraw = atoi(charNumber);
						}
						else if (offsetGetValue == 7) {
							tool_isRemind = atoi(charNumber);
						}
						else if (offsetGetValue == 8) {
							tool_isDrawNet = atoi(charNumber);
						}
						else if (offsetGetValue == 9) {
							tool_arrowSize = atof(charNumber);
						}
						else {
							tool_circleSize = atof(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						offsetGetValue++;
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

//hàm ghi các dữ liệu đỉnh và hình vào tệp .txt
void saveDataToTxt(vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//mở file .txt (hoặc khởi tạo nếu chưa có)
	ofstream myfile("D://openGL_txt//a_opengl_object.txt");
	//hàm kiểm tra xem có gặp trục trặc gì khi mở hay khởi tạo không
	if (myfile.is_open())
	{
		//điền các thông tin về các đối tượng có trong hình
		int numberObject, numberVertex;
		//điền các triangle
		numberObject = triaArray.size();
		myfile << "Triangle Object : "<< numberObject <<" Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			TriangleAttribute *tria = triaArray.at(i);
			myfile << "Triangle "<<i<<" :\n";
			for (int j = 0; j < 3; j++) {
				myfile << "{";
				myfile << " "<<tria->vertexArray[j].x<<" ,";
				myfile << " " << tria->vertexArray[j].y << " ,";
				myfile << " " << tria->vertexArray[j].z << " ";
				myfile << "}";
				if (j != 2) {
					myfile << ",";
				}
			}
			myfile << "\n\n";
			myfile << "Number normal : " << 1 << " \n";
			myfile << "{";
			myfile << " " << tria->normalVector.x << " ,";
			myfile << " " << tria->normalVector.y << " ,";
			myfile << " " << tria->normalVector.z << " ";
			myfile << "}";

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các triangle strip
		numberObject = triaStripArray.size();
		myfile << "Triangle Strip Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			TriangleStripAttribute *triaStrip = triaStripArray.at(i);
			myfile << "Triangle Strip " << i << " :\n";
			numberVertex = triaStrip->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << triaStrip->vertexArray[j].x << " ,";
				myfile << " " << triaStrip->vertexArray[j].y << " ,";
				myfile << " " << triaStrip->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex-1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = triaStrip->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << triaStrip->normalVector[j].x << " ,";
				myfile << " " << triaStrip->normalVector[j].y << " ,";
				myfile << " " << triaStrip->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các triangle fan
		numberObject = triaFanArray.size();
		myfile << "Triangle Fan Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			TriangleFanAttribute *triaFan = triaFanArray.at(i);
			myfile << "Triangle Fan " << i << " :\n";
			numberVertex = triaFan->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << triaFan->vertexArray[j].x << " ,";
				myfile << " " << triaFan->vertexArray[j].y << " ,";
				myfile << " " << triaFan->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = triaFan->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << triaFan->normalVector[j].x << " ,";
				myfile << " " << triaFan->normalVector[j].y << " ,";
				myfile << " " << triaFan->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các sphere
		numberObject = sphereArray.size();
		myfile << "Sphere Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			SphereAttribute *sphere = sphereArray.at(i);
			myfile << "Sphere " << i << " :\n";
			numberVertex = sphere->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << sphere->vertexArray[j].x << " ,";
				myfile << " " << sphere->vertexArray[j].y << " ,";
				myfile << " " << sphere->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = sphere->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << sphere->normalVector[j].x << " ,";
				myfile << " " << sphere->normalVector[j].y << " ,";
				myfile << " " << sphere->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các cube
		numberObject = cubeArray.size();
		myfile << "Cube Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			CubeAttribute *cube = cubeArray.at(i);
			myfile << "Cube " << i << " :\n";
			numberVertex = cube->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cube->vertexArray[j].x << " ,";
				myfile << " " << cube->vertexArray[j].y << " ,";
				myfile << " " << cube->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = cube->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cube->normalVector[j].x << " ,";
				myfile << " " << cube->normalVector[j].y << " ,";
				myfile << " " << cube->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các cone
		numberObject = coneArray.size();
		myfile << "Cone Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			ConeAttribute *cone = coneArray.at(i);
			myfile << "Cone " << i << " :\n";
			numberVertex = cone->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cone->vertexArray[j].x << " ,";
				myfile << " " << cone->vertexArray[j].y << " ,";
				myfile << " " << cone->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = cone->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cone->normalVector[j].x << " ,";
				myfile << " " << cone->normalVector[j].y << " ,";
				myfile << " " << cone->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các cylinder
		numberObject = cylinderArray.size();
		myfile << "Cylinder Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			CylinderAttribute *cylinder = cylinderArray.at(i);
			myfile << "Cylinder " << i << " :\n";
			numberVertex = cylinder->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cylinder->vertexArray[j].x << " ,";
				myfile << " " << cylinder->vertexArray[j].y << " ,";
				myfile << " " << cylinder->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = cylinder->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cylinder->normalVector[j].x << " ,";
				myfile << " " << cylinder->normalVector[j].y << " ,";
				myfile << " " << cylinder->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các empty cylinder
		numberObject = emptyCylinderArray.size();
		myfile << "Empty Cylinder Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(i);
			myfile << "Empty Cylinder " << i << " :\n";
			numberVertex = cylinder->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cylinder->vertexArray[j].x << " ,";
				myfile << " " << cylinder->vertexArray[j].y << " ,";
				myfile << " " << cylinder->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = cylinder->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << cylinder->normalVector[j].x << " ,";
				myfile << " " << cylinder->normalVector[j].y << " ,";
				myfile << " " << cylinder->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các torus
		numberObject = torusArray.size();
		myfile << "Torus Object : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			TorusAttribute *torus = torusArray.at(i);
			myfile << "Torus " << i << " :\n";
			numberVertex = torus->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << torus->vertexArray[j].x << " ,";
				myfile << " " << torus->vertexArray[j].y << " ,";
				myfile << " " << torus->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = torus->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << torus->normalVector[j].x << " ,";
				myfile << " " << torus->normalVector[j].y << " ,";
				myfile << " " << torus->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}

			myfile << "\n";
		}
		myfile << "\n\n";

		//điền các ObjectCustom0
		numberObject = objectCustom0Array.size();
		myfile << "ObjectCustom0 : " << numberObject << " Object \n \n";
		for (int i = 0; i < numberObject; i++) {
			ObjectCustom0Attribute *object = objectCustom0Array.at(i);
			myfile << "Object " << i << " :\n";
			numberVertex = object->vertexArray.size();
			myfile << "Number vertex : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << object->vertexArray[j].x << " ,";
				myfile << " " << object->vertexArray[j].y << " ,";
				myfile << " " << object->vertexArray[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n\n";

			numberVertex = object->normalVector.size();
			myfile << "Number normal : " << numberVertex << " \n";
			for (int j = 0; j < numberVertex; j++) {
				myfile << "{";
				myfile << " " << object->normalVector[j].x << " ,";
				myfile << " " << object->normalVector[j].y << " ,";
				myfile << " " << object->normalVector[j].z << " ";
				myfile << "}";
				if (j != numberVertex - 1) {
					myfile << ",";
				}
			}
			myfile << "\n";
		}
		myfile << "\n\n";

		myfile.close();
	}
	else cout << "Unable to open file";
}
//hàm lấy tên để đặt tiếp cho txt và thay đổi giá trị trong mảng txtUsing và biến offsetTxtUsing(nếu cần)
void getNameTxtForSave(vector<int> &txtUsing, int &offsetTxtUsing,
	char *pathObjectTxt, char *pathAttributeTxt) {
	//nếu đang chưa có tệp txt nào đang được dùng thì để mặc định là 0
	//nếu có rồi thì lấy giá trị tiếp theo của phần tử cuối cùng
	int nameTxt = 0, numberTxt = txtUsing.size();
	if (!txtUsing.empty()) {
		//kiểm tra xem vị trí của offsetTxtUsing có đang nằm ở cuối tệp không,
		//nếu có thì thêm tiếp phần tử như thường.
		//nếu không thì xóa hết các phần tử phía sau off set và thêm như thường
		if (offsetTxtUsing == -1) {
			//nếu phần tử nằm ở vị trí đầu tiên thì xóa hết
			txtUsing.clear();
		}
		else if (offsetTxtUsing < numberTxt - 1) {
			txtUsing.erase(txtUsing.begin() + offsetTxtUsing + 1, txtUsing.begin() + numberTxt);
		}

		if (offsetTxtUsing != -1) {
			nameTxt = txtUsing.back();
			if (nameTxt != 99) {
				nameTxt++;
			}
			else
			{
				nameTxt = 0;
			}
		}
	}
	//thêm tệp txt sẽ dùng bây giờ vào mảng các txt đang dùng
	txtUsing.push_back(nameTxt);
	//tính lại số phần tử trong mảng
	numberTxt = txtUsing.size();
	//nếu có hơn 100 phần tử thì xóa đi phần tử đầu tiên
	if (numberTxt>100) {
		txtUsing.erase(txtUsing.begin());
	}

	//tăng vị trí của offsetTxtUsing (nếu chưa phải nó nằm ở cuối cùng)
	if (offsetTxtUsing != 99) {
		//con trỏ không cho viết kiểu *offsetTxtUsing++;
		offsetTxtUsing+=1;
	}

	//lấy ra tên txt để lưu object và tên txt để lưu attribute
	string stringPath;
	stringPath = std::to_string(nameTxt);
	stringPath = "D://openGL_txt//object" + stringPath;
	stringPath = stringPath + ".txt";
	strcpy_s(pathObjectTxt, 40, stringPath.c_str());

	stringPath = std::to_string(nameTxt);
	stringPath = "D://openGL_txt//attribute" + stringPath;
	stringPath = stringPath + ".txt";
	strcpy_s(pathAttributeTxt, 40, stringPath.c_str());
	
}
//hàm lấy tên txt từ vị trí
void getNameTxt(int position,
	char *pathObjectTxt, char *pathAttributeTxt) {
	//lấy ra tên txt để lưu object và tên txt để lưu attribute
	string stringPath;
	stringPath = std::to_string(position);
	stringPath = "D://openGL_txt//object" + stringPath;
	stringPath = stringPath + ".txt";
	strcpy_s(pathObjectTxt, 40, stringPath.c_str());

	stringPath = std::to_string(position);
	stringPath = "D://openGL_txt//attribute" + stringPath;
	stringPath = stringPath + ".txt";
	strcpy_s(pathAttributeTxt, 40, stringPath.c_str());

}

//hàm lưu các thông tin dịch chuyển vào tệp txt để khi cần thì trở lại dịch chuyển trước
//hay tiến lên dịch chuyển tiếp theo
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void saveInformationChange(char *nameTxt,
	int whichEffect ,float value1,float value2,float value3) {
	//đối với whichEffect thì 0 là move,1 là rotate,2 là scale,3 là delete Object
	//tùy theo các kiểu mà lưu các thông tin khác nhau

	//ghi các thông tin vào tệp txt
	ofstream myfile(nameTxt);
	if (myfile.is_open())
	{
		//số ở hàng thứ 1 là ký hiệu cho move(0) hoặc rotate(1) hoặc scale(2) hoặc deleteObject(3)
		myfile << "E " << whichEffect << "\n";
		//các giá trị move, rotate hay scale
		myfile << "V " << value1 << "," << value2 << "," << value3 << " \n";

		myfile.close();
	}
	else cout << "Unable to open file";

}
// lưu lại toàn bộ thông tin của các vật vừa được thay đổi, để lát đặt lại(nếu cần) sau khi bị xóa
//đối với whichEffect thì 0 là move,1 là rotate,2 là scale
//còn 3 là tạo mới vật,4 là xóa vật,5 là thay đổi numberLongitude hay latitude của vật(chỉ lưu lại số vertex sau khi thay đổi)
//,6 là tạo mới các vertex,7 là xóa các vertex
void saveInformationObject(char *nameTxt, int whichEffect,vector<itemChoice> itemsChoice,
	vector<TriangleAttribute*> triaArray, vector<TriangleStripAttribute*> triaStripArray,
	vector<TriangleFanAttribute*> triaFanArray, vector<SphereAttribute*> sphereArray,
	vector<CubeAttribute*> cubeArray, vector<CubeRoundAttribute*> cubeRoundArray,
	vector<ConeAttribute*> coneArray, vector<CylinderAttribute*> cylinderArray,
	vector<PyramidAttribute*> pyrArray, vector<EmptyCylinderAttribute*> emptyCylinderArray,
	vector<TorusAttribute*> torusArray, vector<PictureAttribute*> pictureArray,
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	itemChoice item,itemCheck;
	
	//sắp xếp các phần tử trong itemsChoice,nếu cùng 1 kiểu phần tử thì các phần tử có thứ tự trong mảng nhỏ hơn đứng trước
	//(thấp đến cao hay cao về thấp cũng như nhau,nhưng mà thấp đến cao thì thường đỡ phải sắp xếp nếu
	//chỉ chọn 1 lần bằng cách bao vùng chữ nhật)
	ArrangeOrderFromSmallToLarge(itemsChoice);

	//ghi các thông tin vào tệp txt
	ofstream myfile(nameTxt);
	if (myfile.is_open()) {
		int numberVertex,numberItemChoice,numberItemBefore;

		//int ra whichEffect để biết là bây giờ thay thế hay thêm vào
		myfile << "E " << whichEffect << "\n";

		//lưu vào thông tin của các object đang được chọn
		numberItemChoice = itemsChoice.size();
		for (int k = 0; k < numberItemChoice; k++) {
			item = itemsChoice.at(k);
			//tìm ra số phần tử cùng kiểu và đứng trước phần tử này(vì đã sắp xếp các phần tử cùng mảng
			//theo thứ tự từ nhỏ đến lớn nên các phần tử nhỏ hơn sẽ năm trước phần tử hiện tại trong itemsChoice)
			numberItemBefore = 0;
			for (int j = 0; j < k; j++) {
				itemCheck = itemsChoice.at(j);
				if (itemCheck.object == item.object && itemCheck.positionOfChoice < item.positionOfChoice) {
					numberItemBefore++;
				}
			}

			switch (item.object)
			{
			case 3: {
				TriangleAttribute *tria = triaArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho tam giác
				myfile << "O 3" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << tria->centerObject.x << " " << tria->centerObject.y << " " << tria->centerObject.z << " "
					<< tria->colorR << " " << tria->colorG << " " << tria->colorB << " " << tria->colorA << " "
					<< tria->mShiness << " " << tria->id << " " << tria->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				myfile << "V ";
				for (int j = 0; j < 3; j++) {
					myfile << "{" << tria->vertexArray[j].x << "," << tria->vertexArray[j].y << "," << tria->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				myfile << "N {" << tria->normalVector.x << "," << tria->normalVector.y << "," << tria->normalVector.z << "}\n";
			}
					break;
			case 4: {
				TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho triangle strip
				myfile << "O 4" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tínhc theo thứ tự
				myfile << "A " << triaStrip->centerObject.x << " " << triaStrip->centerObject.y << " " << triaStrip->centerObject.z << " "
					<< triaStrip->colorR << " " << triaStrip->colorG << " " << triaStrip->colorB << " " << triaStrip->colorA << " "
					<< triaStrip->mShiness << " " << triaStrip->id << " " << triaStrip->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = triaStrip->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << triaStrip->vertexArray[j].x << "," << triaStrip->vertexArray[j].y << "," << triaStrip->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = triaStrip->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << triaStrip->normalVector[j].x << "," << triaStrip->normalVector[j].y
						<< "," << triaStrip->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					break;
			case 5: {
				TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho triangle fan
				myfile << "O 5" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << triaFan->centerObject.x << " " << triaFan->centerObject.y << " " << triaFan->centerObject.z << " "
					<< triaFan->colorR << " " << triaFan->colorG << " " << triaFan->colorB << " " << triaFan->colorA << " "
					<< triaFan->mShiness << " " << triaFan->id << " " << triaFan->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = triaFan->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << triaFan->vertexArray[j].x << "," << triaFan->vertexArray[j].y << "," << triaFan->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = triaFan->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << triaFan->normalVector[j].x << "," << triaFan->normalVector[j].y
						<< "," << triaFan->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					break;
			case 10: {
				SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho sphere
				myfile << "O 10" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << sphere->centerObject.x << " " << sphere->centerObject.y << " " << sphere->centerObject.z << " "
					<< sphere->numberLongitude << " " << sphere->numberLatitude << " "
					<< sphere->degreeLongitudeLimit << " " << sphere->degreeLatitudeLimit << " " << sphere->radius << " "
					<< sphere->colorR << " " << sphere->colorG << " " << sphere->colorB << " " << sphere->colorA << " "
					<< sphere->mShiness << " " << sphere->id << " " << sphere->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = sphere->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << sphere->vertexArray[j].x << "," << sphere->vertexArray[j].y << "," << sphere->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = sphere->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << sphere->normalVector[j].x << "," << sphere->normalVector[j].y
						<< "," << sphere->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 11: {
				CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho cube
				myfile << "O 11" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
					<< cube->numberVertexInAxisX << " " << cube->numberVertexInAxisY << " " << cube->numberVertexInAxisZ << " "
					<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
					<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = cube->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cube->vertexArray[j].x << "," << cube->vertexArray[j].y << "," << cube->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = cube->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cube->normalVector[j].x << "," << cube->normalVector[j].y
						<< "," << cube->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 12: {
				CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho sphere
				myfile << "O 12" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
					<< cube->numberLongitude << " " << cube->numberLatitude << " " << cube->radiusRound << " "
					<< cube->xLength << " " << cube->yLength << " " << cube->zLength << " "
					<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
					<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = cube->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cube->vertexArray[j].x << "," << cube->vertexArray[j].y << "," << cube->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = cube->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cube->normalVector[j].x << "," << cube->normalVector[j].y
						<< "," << cube->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 13: {
				ConeAttribute *cone = coneArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho sphere
				myfile << "O 13" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << cone->centerObject.x << " " << cone->centerObject.y << " " << cone->centerObject.z << " "
					<< cone->height << " " << cone->radius << " "
					<< cone->numberLongitude << " " << cone->numberLatitude << " "
					<< cone->degreeLongitudeLimit << " " << cone->degreeLatitudeLimit << " "
					<< cone->colorR << " " << cone->colorG << " " << cone->colorB << " " << cone->colorA << " "
					<< cone->mShiness << " " << cone->id << " " << cone->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = cone->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cone->vertexArray[j].x << "," << cone->vertexArray[j].y << "," << cone->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = cone->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cone->normalVector[j].x << "," << cone->normalVector[j].y
						<< "," << cone->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 14: {
				CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho cylinder
				myfile << "O 14" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
					<< cylinder->height << " " << cylinder->radiusUp << " " << cylinder->radiusDown << " "
					<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
					<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
					<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
					<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = cylinder->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cylinder->vertexArray[j].x << "," << cylinder->vertexArray[j].y << "," << cylinder->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = cylinder->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cylinder->normalVector[j].x << "," << cylinder->normalVector[j].y
						<< "," << cylinder->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 16: {
				EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho empty cylinder
				myfile << "O 16" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
					<< cylinder->height << " " << cylinder->radiusUpIn << " " << cylinder->radiusDownIn << " "
					<< cylinder->radiusUpOut << " " << cylinder->radiusDownOut << " "
					<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
					<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
					<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
					<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = cylinder->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cylinder->vertexArray[j].x << "," << cylinder->vertexArray[j].y << "," << cylinder->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = cylinder->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << cylinder->normalVector[j].x << "," << cylinder->normalVector[j].y
						<< "," << cylinder->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 17: {
				TorusAttribute *torus = torusArray.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho empty cylinder
				myfile << "O 17" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << torus->centerObject.x << " " << torus->centerObject.y << " " << torus->centerObject.z << " "
					<< torus->radiusCake << " " << torus->radiusRoundCake << " " << torus->widthCake << " "
					<< torus->depthCake << " " << torus->depthRoundCake << " "
					<< torus->colorR << " " << torus->colorG << " " << torus->colorB << " " << torus->colorA << " "
					<< torus->mShiness << " " << torus->id << " " << torus->idTexture << " "
					<< "\n";
				//in ra các vertex theo thứ tự
				numberVertex = torus->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << torus->vertexArray[j].x << "," << torus->vertexArray[j].y << "," << torus->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = torus->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << torus->normalVector[j].x << "," << torus->normalVector[j].y
						<< "," << torus->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			case 19: {
				ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
				//đàu tiên in ra số đại diện cho ObjectCustom0
				myfile << "O 19" << "\n";
				//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
				myfile << "P " << item.positionOfChoice << "_" << numberItemBefore << " \n";
				//tiếp theo in ra các thuôc tính theo thứ tự
				myfile << "A " << object->centerObject.x << " " << object->centerObject.y << " " << object->centerObject.z << " "
					<< object->lengthBetween2Row << " " << object->lengthBetween2Column << " "
					<< object->numberLongitude << " " << object->numberLatitude << " "
					<< object->colorR << " " << object->colorG << " " << object->colorB << " " << object->colorA << " "
					<< object->mShiness << " " << object->id << " " << object->idTexture << " "
					<< "\n";
				
				//in ra các vertex theo thứ tự
				numberVertex = object->vertexArray.size();
				myfile << "V ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << object->vertexArray[j].x << "," << object->vertexArray[j].y
						<< "," << object->vertexArray[j].z << "}";
				}
				myfile << "\n";
				//in ra normal vector
				numberVertex = object->normalVector.size();
				myfile << "N ";
				for (int j = 0; j < numberVertex; j++) {
					myfile << "{" << object->normalVector[j].x << "," << object->normalVector[j].y
						<< "," << object->normalVector[j].z << "}";
				}
				myfile << "\n";
			}
					 break;
			default:
				break;
			}

		}

		myfile.close();
	}
}
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
	vector<ObjectCustom0Attribute*> objectCustom0Array) {

	//ghi các thông tin vào tệp txt
	ofstream myfile(nameTxt);
	if (myfile.is_open()) {
		int numberVerticesChoice = positionVerticesChoice.size(), position, numberVertexBefore, numberElement;
		PositionRowOrColumn pNow;
		SymmetryObjects symmetryObjectCheck;

		//sắp xếp lại theo thứ tự lớn đến nhỏ(theo vị trí trong mảng) các vertex đang được chọn
		//(để lát xóa hay thêm từ sau ra trước)
		//việc thay đổi thứ tự này không ảnh hưởng đến mảng này ở ngoài hàm chính vì đây chỉ là bản sao của mảng
		ArrangeOrderFromSmallToLarge(positionVerticesChoice);

		//int ra whichEffect để biết là bây giờ thay thế hay thêm vào
		myfile << "E " << whichEffect << "\n";

		//lưu thông tin các vertex được chọn(bị xóa)
		switch (item.object)
		{
		case 3: {
			TriangleAttribute *tria = triaArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho tam giác
			myfile << "O 3" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << tria->centerObject.x << " " << tria->centerObject.y << " " << tria->centerObject.z << " "
				<< tria->colorR << " " << tria->colorG << " " << tria->colorB << " " << tria->colorA << " "
				<< tria->mShiness << " " << tria->id << " " << tria->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << tria->vertexArray[position].x << ","
					<< tria->vertexArray[position].y << "," << tria->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						tria = triaArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << tria->vertexArray[position].x << ","
								<< tria->vertexArray[position].y << "," << tria->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						tria = triaArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << tria->vertexArray[position].x << ","
								<< tria->vertexArray[position].y << "," << tria->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				break;
		case 4: {
			TriangleStripAttribute *triaStrip = triaStripArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho triangle strip
			myfile << "O 4" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tínhc theo thứ tự
			myfile << "A " << triaStrip->centerObject.x << " " << triaStrip->centerObject.y << " " << triaStrip->centerObject.z << " "
				<< triaStrip->colorR << " " << triaStrip->colorG << " " << triaStrip->colorB << " " << triaStrip->colorA << " "
				<< triaStrip->mShiness << " " << triaStrip->id << " " << triaStrip->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << triaStrip->vertexArray[position].x << ","
					<< triaStrip->vertexArray[position].y << "," << triaStrip->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << triaStrip->vertexArray[position].x << ","
								<< triaStrip->vertexArray[position].y << "," << triaStrip->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						triaStrip = triaStripArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << triaStrip->vertexArray[position].x << ","
								<< triaStrip->vertexArray[position].y << "," << triaStrip->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *triaFan = triaFanArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho triangle fan
			myfile << "O 5" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << triaFan->centerObject.x << " " << triaFan->centerObject.y << " " << triaFan->centerObject.z << " "
				<< triaFan->colorR << " " << triaFan->colorG << " " << triaFan->colorB << " " << triaFan->colorA << " "
				<< triaFan->mShiness << " " << triaFan->id << " " << triaFan->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << triaFan->vertexArray[position].x << ","
					<< triaFan->vertexArray[position].y << "," << triaFan->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << triaFan->vertexArray[position].x << ","
								<< triaFan->vertexArray[position].y << "," << triaFan->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						triaFan = triaFanArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << triaFan->vertexArray[position].x << ","
								<< triaFan->vertexArray[position].y << "," << triaFan->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				break;
		case 10: {
			SphereAttribute *sphere = sphereArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 10" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << sphere->centerObject.x << " " << sphere->centerObject.y << " " << sphere->centerObject.z << " "
				<< sphere->numberLongitude << " " << sphere->numberLatitude << " "
				<< sphere->degreeLongitudeLimit << " " << sphere->degreeLatitudeLimit << " " << sphere->radius << " "
				<< sphere->colorR << " " << sphere->colorG << " " << sphere->colorB << " " << sphere->colorA << " "
				<< sphere->mShiness << " " << sphere->id << " " << sphere->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << sphere->vertexArray[position].x << ","
					<< sphere->vertexArray[position].y << "," << sphere->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						sphere = sphereArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << sphere->vertexArray[position].x << ","
								<< sphere->vertexArray[position].y << "," << sphere->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						sphere = sphereArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << sphere->vertexArray[position].x << ","
								<< sphere->vertexArray[position].y << "," << sphere->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 11: {
			CubeAttribute *cube = cubeArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho cube
			myfile << "O 11" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
				<< cube->numberVertexInAxisX << " " << cube->numberVertexInAxisY << " " << cube->numberVertexInAxisZ << " "
				<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
				<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
					<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						cube = cubeArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
								<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						cube = cubeArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
								<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *cube = cubeRoundArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 12" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cube->centerObject.x << " " << cube->centerObject.y << " " << cube->centerObject.z << " "
				<< cube->numberLongitude << " " << cube->numberLatitude << " " << cube->radiusRound << " "
				<< cube->xLength << " " << cube->yLength << " " << cube->zLength << " "
				<< cube->colorR << " " << cube->colorG << " " << cube->colorB << " " << cube->colorA << " "
				<< cube->mShiness << " " << cube->id << " " << cube->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
					<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
								<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						cube = cubeRoundArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cube->vertexArray[position].x << ","
								<< cube->vertexArray[position].y << "," << cube->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 13: {
			ConeAttribute *cone = coneArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho sphere
			myfile << "O 13" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cone->centerObject.x << " " << cone->centerObject.y << " " << cone->centerObject.z << " "
				<< cone->height << " " << cone->radius << " "
				<< cone->numberLongitude << " " << cone->numberLatitude << " "
				<< cone->degreeLongitudeLimit << " " << cone->degreeLatitudeLimit << " "
				<< cone->colorR << " " << cone->colorG << " " << cone->colorB << " " << cone->colorA << " "
				<< cone->mShiness << " " << cone->id << " " << cone->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << cone->vertexArray[position].x << ","
					<< cone->vertexArray[position].y << "," << cone->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						cone = coneArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cone->vertexArray[position].x << ","
								<< cone->vertexArray[position].y << "," << cone->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						cone = coneArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cone->vertexArray[position].x << ","
								<< cone->vertexArray[position].y << "," << cone->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 14: {
			CylinderAttribute *cylinder = cylinderArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho cylinder
			myfile << "O 14" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
				<< cylinder->height << " " << cylinder->radiusUp << " " << cylinder->radiusDown << " "
				<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
				<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
				<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
				<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
					<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
								<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						cylinder = cylinderArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
								<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho empty cylinder
			myfile << "O 16" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << cylinder->centerObject.x << " " << cylinder->centerObject.y << " " << cylinder->centerObject.z << " "
				<< cylinder->height << " " << cylinder->radiusUpIn << " " << cylinder->radiusDownIn << " "
				<< cylinder->radiusUpOut << " " << cylinder->radiusDownOut << " "
				<< cylinder->numberLongitude << " " << cylinder->numberLatitude << " "
				<< cylinder->degreeLongitudeLimit << " " << cylinder->degreeLatitudeLimit << " "
				<< cylinder->colorR << " " << cylinder->colorG << " " << cylinder->colorB << " " << cylinder->colorA << " "
				<< cylinder->mShiness << " " << cylinder->id << " " << cylinder->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
					<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
								<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						cylinder = emptyCylinderArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << cylinder->vertexArray[position].x << ","
								<< cylinder->vertexArray[position].y << "," << cylinder->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 17: {
			TorusAttribute *torus = torusArray.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho empty cylinder
			myfile << "O 17" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << torus->centerObject.x << " " << torus->centerObject.y << " " << torus->centerObject.z << " "
				<< torus->radiusCake << " " << torus->radiusRoundCake << " " << torus->widthCake << " "
				<< torus->depthCake << " " << torus->depthRoundCake << " "
				<< torus->colorR << " " << torus->colorG << " " << torus->colorB << " " << torus->colorA << " "
				<< torus->mShiness << " " << torus->id << " " << torus->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << torus->vertexArray[position].x << ","
					<< torus->vertexArray[position].y << "," << torus->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						torus = torusArray.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << torus->vertexArray[position].x << ","
								<< torus->vertexArray[position].y << "," << torus->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						torus = torusArray.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << torus->vertexArray[position].x << ","
								<< torus->vertexArray[position].y << "," << torus->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(item.positionOfChoice);
			//đàu tiên in ra số đại diện cho ObjectCustom0
			myfile << "O 19" << "\n";
			//tiếp theo là vị trí của object và số phân tử được chọn đứng trước nó trong mảng các đối tượng cùng kiểu
			myfile << "P " << item.positionOfChoice << "_" << 0 << " \n";
			//tiếp theo in ra các thuôc tính theo thứ tự
			myfile << "A " << object->centerObject.x << " " << object->centerObject.y << " " << object->centerObject.z << " "
				<< object->lengthBetween2Row << " " << object->lengthBetween2Column << " "
				<< object->numberLongitude << " " << object->numberLatitude << " "
				<< object->colorR << " " << object->colorG << " " << object->colorB << " " << object->colorA << " "
				<< object->mShiness << " " << object->id << " " << object->idTexture << " "
				<< "\n";
			//in ra các vertex được chọn cùng vị trí của chúng trong mảng
			myfile << "V ";
			for (int j = 0; j < numberVerticesChoice; j++) {
				position = positionVerticesChoice[j];
				//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
				//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
				//phía sau là vị trí 3D của vertex
				myfile << "(" << position << "_" << j << ")" << "{" << object->vertexArray[position].x << ","
					<< object->vertexArray[position].y << "," << object->vertexArray[position].z << "}";
			}
			myfile << "\n";

			//kiểm tra nếu có object đối xứng thì ghi ra các vertices của object đối xứng vào tệp
			numberElement = symmetryObjects.size();
			for (int i = 0; i < numberElement; i++) {
				symmetryObjectCheck = symmetryObjects.at(i);
				if (symmetryObjectCheck.object1 == item.object) {
					if (symmetryObjectCheck.positionInArray1 == item.positionOfChoice) {
						object = objectCustom0Array.at(symmetryObjectCheck.positionInArray2);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << object->vertexArray[position].x << ","
								<< object->vertexArray[position].y << "," << object->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
					else if (symmetryObjectCheck.positionInArray2 == item.positionOfChoice) {
						object = objectCustom0Array.at(symmetryObjectCheck.positionInArray1);

						myfile << "S ";
						for (int j = 0; j < numberVerticesChoice; j++) {
							position = positionVerticesChoice[j];
							//vì đã sắp theo thứ tự nên số phần tử nằm trước bằng vị trí j
							//đầu tiên in ra vị trí vertex trong mảng và các vertex được chọn đứng trước nó,
							//phía sau là vị trí 3D của vertex
							myfile << "(" << position << "_" << j << ")" << "{" << object->vertexArray[position].x << ","
								<< object->vertexArray[position].y << "," << object->vertexArray[position].z << "}";
						}
						myfile << "\n";
						break;
					}
				}
			}
		}
				 break;
		default:
			break;
		}
		myfile.close();
	}
}
//hàm thêm các thuộc tính từ chuỗi string
void addAttributeFromString(string stringValue,int object,int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing) {

	int offsetGetValue = 0, startOffset = 2,numberElement1 = stringValue.size();
	char charNumber[20];
	//kiểm tra xem đối tượng hiện tại là gì để thêm thuộc tính
	switch (object)
	{
	case 3: {
		TriangleAttribute *tria;
		if (positionObject == -1) {
			tria = triaArray.back();
		}
		else
		{
			tria = triaArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					tria->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					tria->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					tria->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					tria->colorR = atof(charNumber);
				}
						break;
				case 4: {
					tria->colorG = atof(charNumber);
				}
						break;
				case 5: {
					tria->colorB = atof(charNumber);
				}
						break;
				case 6: {
					tria->colorA = atof(charNumber);
				}
						break;
				case 7: {
					tria->mShiness = atof(charNumber);
				}
						break;
				case 8: {
					tria->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(tria->id);
				}
						break;
				case 9: {
					tria->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 4: {
		TriangleStripAttribute *triaStrip;
		if (positionObject == -1) {
			triaStrip = triaStripArray.back();
		}
		else
		{
			triaStrip = triaStripArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					triaStrip->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					triaStrip->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					triaStrip->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					triaStrip->colorR = atof(charNumber);
				}
						break;
				case 4: {
					triaStrip->colorG = atof(charNumber);
				}
						break;
				case 5: {
					triaStrip->colorB = atof(charNumber);
				}
						break;
				case 6: {
					triaStrip->colorA = atof(charNumber);
				}
						break;
				case 7: {
					triaStrip->mShiness = atof(charNumber);
				}
						break;
				case 8: {
					triaStrip->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(triaStrip->id);
				}
						break;
				case 9: {
					triaStrip->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan;
		if (positionObject == -1) {
			triaFan = triaFanArray.back();
		}
		else
		{
			triaFan = triaFanArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					triaFan->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					triaFan->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					triaFan->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					triaFan->colorR = atof(charNumber);
				}
						break;
				case 4: {
					triaFan->colorG = atof(charNumber);
				}
						break;
				case 5: {
					triaFan->colorB = atof(charNumber);
				}
						break;
				case 6: {
					triaFan->colorA = atof(charNumber);
				}
						break;
				case 7: {
					triaFan->mShiness = atof(charNumber);
				}
						break;
				case 8: {
					triaFan->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(triaFan->id);
				}
						break;
				case 9: {
					triaFan->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere;
		if (positionObject == -1) {
			sphere = sphereArray.back();
		}
		else
		{
			sphere = sphereArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					sphere->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					sphere->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					sphere->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					sphere->numberLongitude = atoi(charNumber);
				}
						break;
				case 4: {
					sphere->numberLatitude = atoi(charNumber);
				}
						break;
				case 5: {
					sphere->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 6: {
					sphere->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 7: {
					sphere->radius = atof(charNumber);
				}
						break;
				case 8: {
					sphere->colorR = atof(charNumber);
				}
						break;
				case 9: {
					sphere->colorG = atof(charNumber);
				}
						break;
				case 10: {
					sphere->colorB = atof(charNumber);
				}
						 break;
				case 11: {
					sphere->colorA = atof(charNumber);
				}
						 break;
				case 12: {
					sphere->mShiness = atof(charNumber);
				}
						 break;
				case 13: {
					sphere->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(sphere->id);
				}
						 break;
				case 14: {
					sphere->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube;
		if (positionObject == -1) {
			cube = cubeArray.back();
		}
		else
		{
			cube = cubeArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cube->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cube->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cube->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cube->numberVertexInAxisX = atoi(charNumber);
				}
						break;
				case 4: {
					cube->numberVertexInAxisY = atoi(charNumber);
				}
						break;
				case 5: {
					cube->numberVertexInAxisZ = atoi(charNumber);
				}
						break;
				case 6: {
					cube->colorR = atof(charNumber);
				}
						break;
				case 7: {
					cube->colorG = atof(charNumber);
				}
						break;
				case 8: {
					cube->colorB = atof(charNumber);
				}
						break;
				case 9: {
					cube->colorA = atof(charNumber);
				}
						break;
				case 10: {
					cube->mShiness = atof(charNumber);
				}
						 break;
				case 11: {
					cube->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(cube->id);
				}
						 break;
				case 12: {
					cube->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *cube;
		if (positionObject == -1) {
			cube = cubeRoundArray.back();
		}
		else
		{
			cube = cubeRoundArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cube->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cube->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cube->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cube->numberLongitude = atoi(charNumber);
				}
						break;
				case 4: {
					cube->numberLatitude = atoi(charNumber);
				}
						break;
				case 5: {
					cube->radiusRound = atof(charNumber);
				}
						break;
				case 6: {
					cube->xLength = atof(charNumber);
				}
						break;
				case 7: {
					cube->yLength = atof(charNumber);
				}
						break;
				case 8: {
					cube->zLength = atof(charNumber);
				}
						break;
				case 9: {
					cube->colorR = atof(charNumber);
				}
						break;
				case 10: {
					cube->colorG = atof(charNumber);
				}
						 break;
				case 11: {
					cube->colorB = atof(charNumber);
				}
						 break;
				case 12: {
					cube->colorA = atof(charNumber);
				}
						 break;
				case 13: {
					cube->mShiness = atof(charNumber);
				}
						 break;
				case 14: {
					cube->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(cube->id);
				}
						 break;
				case 15: {
					cube->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone;
		if (positionObject == -1) {
			cone = coneArray.back();
		}
		else
		{
			cone = coneArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cone->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cone->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cone->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cone->height = atof(charNumber);
				}
						break;
				case 4: {
					cone->radius = atof(charNumber);
				}
						break;
				case 5: {
					cone->numberLongitude = atoi(charNumber);
				}
						break;
				case 6: {
					cone->numberLatitude = atoi(charNumber);
				}
						break;
				case 7: {
					cone->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 8: {
					cone->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 9: {
					cone->colorR = atof(charNumber);
				}
						break;
				case 10: {
					cone->colorG = atof(charNumber);
				}
						 break;
				case 11: {
					cone->colorB = atof(charNumber);
				}
						 break;
				case 12: {
					cone->colorA = atof(charNumber);
				}
						 break;
				case 13: {
					cone->mShiness = atof(charNumber);
				}
						 break;
				case 14: {
					cone->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(cone->id);
				}
						 break;
				case 15: {
					cone->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = cylinderArray.back();
		}
		else
		{
			cylinder = cylinderArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cylinder->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cylinder->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cylinder->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cylinder->height = atof(charNumber);
				}
						break;
				case 4: {
					cylinder->radiusUp = atof(charNumber);
				}
						break;
				case 5: {
					cylinder->radiusDown = atof(charNumber);
				}
						break;
				case 6: {
					cylinder->numberLongitude = atoi(charNumber);
				}
						break;
				case 7: {
					cylinder->numberLatitude = atoi(charNumber);
				}
						break;
				case 8: {
					cylinder->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 9: {
					cylinder->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 10: {
					cylinder->colorR = atof(charNumber);
				}
						 break;
				case 11: {
					cylinder->colorG = atof(charNumber);
				}
						 break;
				case 12: {
					cylinder->colorB = atof(charNumber);
				}
						 break;
				case 13: {
					cylinder->colorA = atof(charNumber);
				}
						 break;
				case 14: {
					cylinder->mShiness = atof(charNumber);
				}
						 break;
				case 15: {
					cylinder->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(cylinder->id);
				}
						 break;
				case 16: {
					cylinder->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = emptyCylinderArray.back();
		}
		else
		{
			cylinder = emptyCylinderArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cylinder->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cylinder->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cylinder->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cylinder->height = atof(charNumber);
				}
						break;
				case 4: {
					cylinder->radiusUpIn = atof(charNumber);
				}
						break;
				case 5: {
					cylinder->radiusDownIn = atof(charNumber);
				}
						break;
				case 6: {
					cylinder->radiusUpOut = atof(charNumber);
				}
						break;
				case 7: {
					cylinder->radiusDownOut = atof(charNumber);
				}
						break;
				case 8: {
					cylinder->numberLongitude = atoi(charNumber);
				}
						break;
				case 9: {
					cylinder->numberLatitude = atoi(charNumber);
				}
						break;
				case 10: {
					cylinder->degreeLongitudeLimit = atoi(charNumber);
				}
						 break;
				case 11: {
					cylinder->degreeLatitudeLimit = atoi(charNumber);
				}
						 break;
				case 12: {
					cylinder->colorR = atof(charNumber);
				}
						 break;
				case 13: {
					cylinder->colorG = atof(charNumber);
				}
						 break;
				case 14: {
					cylinder->colorB = atof(charNumber);
				}
						 break;
				case 15: {
					cylinder->colorA = atof(charNumber);
				}
						 break;
				case 16: {
					cylinder->mShiness = atof(charNumber);
				}
						 break;
				case 17: {
					cylinder->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(cylinder->id);
				}
						 break;
				case 18: {
					cylinder->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus;
		if (positionObject == -1) {
			torus = torusArray.back();
		}
		else
		{
			torus = torusArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					torus->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					torus->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					torus->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					torus->radiusCake = atof(charNumber);
				}
						break;
				case 4: {
					torus->radiusRoundCake = atof(charNumber);
				}
						break;
				case 5: {
					torus->widthCake = atof(charNumber);
				}
						break;
				case 6: {
					torus->depthCake = atoi(charNumber);
				}
						break;
				case 7: {
					torus->depthRoundCake = atoi(charNumber);
				}
						break;
				case 8: {
					torus->colorR = atof(charNumber);
				}
						break;
				case 9: {
					torus->colorG = atof(charNumber);
				}
						break;
				case 10: {
					torus->colorB = atof(charNumber);
				}
						 break;
				case 11: {
					torus->colorA = atof(charNumber);
				}
						 break;
				case 12: {
					torus->mShiness = atof(charNumber);
				}
						 break;
				case 13: {
					torus->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(torus->id);
				}
						 break;
				case 14: {
					torus->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object;
		if (positionObject == -1) {
			object = objectCustom0Array.back();
		}
		else
		{
			object = objectCustom0Array.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					object->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					object->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					object->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					object->lengthBetween2Row = atof(charNumber);
				}
						break;
				case 4: {
					object->lengthBetween2Column = atof(charNumber);
				}
						break;
				case 5: {
					object->numberLongitude = atoi(charNumber);
				}
						break;
				case 6: {
					object->numberLatitude = atoi(charNumber);
				}
						break;
				case 7: {
					object->colorR = atof(charNumber);
				}
						 break;
				case 8: {
					object->colorG = atof(charNumber);
				}
						 break;
				case 9: {
					object->colorB = atof(charNumber);
				}
						 break;
				case 10: {
					object->colorA = atof(charNumber);
				}
						 break;
				case 11: {
					object->mShiness = atof(charNumber);
				}
						 break;
				case 12: {
					object->id = atoi(charNumber);
					//thêm lại id vào mảng idsUsing
					idsUsing.push_back(object->id);
				}
						 break;
				case 13: {
					object->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	default:
		break;
	}

}

//hàm thay đổi các thuộc tính từ chuỗi string
//cái dùng để thay đổi các giá trị trong khi chỉnh sửa thuộc tính hay thay đổi các giá trị vertex
//vậy nên nó không được thay đổi id
void changeAttributeFromString(string stringValue, int object, int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	int offsetGetValue = 0, startOffset = 2, numberElement1 = stringValue.size();
	char charNumber[20];
	//kiểm tra xem đối tượng hiện tại là gì để thêm thuộc tính
	switch (object)
	{
	case 3: {
		TriangleAttribute *tria;
		if (positionObject == -1) {
			tria = triaArray.back();
		}
		else
		{
			tria = triaArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					tria->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					tria->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					tria->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					tria->colorR = atof(charNumber);
				}
						break;
				case 4: {
					tria->colorG = atof(charNumber);
				}
						break;
				case 5: {
					tria->colorB = atof(charNumber);
				}
						break;
				case 6: {
					tria->colorA = atof(charNumber);
				}
						break;
				case 7: {
					tria->mShiness = atof(charNumber);
				}
						break;
				case 8: {

				}
						break;
				case 9: {
					tria->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 4: {
		TriangleStripAttribute *triaStrip;
		if (positionObject == -1) {
			triaStrip = triaStripArray.back();
		}
		else
		{
			triaStrip = triaStripArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					triaStrip->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					triaStrip->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					triaStrip->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					triaStrip->colorR = atof(charNumber);
				}
						break;
				case 4: {
					triaStrip->colorG = atof(charNumber);
				}
						break;
				case 5: {
					triaStrip->colorB = atof(charNumber);
				}
						break;
				case 6: {
					triaStrip->colorA = atof(charNumber);
				}
						break;
				case 7: {
					triaStrip->mShiness = atof(charNumber);
				}
						break;
				case 8: {
					
				}
						break;
				case 9: {
					triaStrip->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan;
		if (positionObject == -1) {
			triaFan = triaFanArray.back();
		}
		else
		{
			triaFan = triaFanArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					triaFan->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					triaFan->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					triaFan->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					triaFan->colorR = atof(charNumber);
				}
						break;
				case 4: {
					triaFan->colorG = atof(charNumber);
				}
						break;
				case 5: {
					triaFan->colorB = atof(charNumber);
				}
						break;
				case 6: {
					triaFan->colorA = atof(charNumber);
				}
						break;
				case 7: {
					triaFan->mShiness = atof(charNumber);
				}
						break;
				case 8: {
					
				}
						break;
				case 9: {
					triaFan->idTexture = atoi(charNumber);
				}
						break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere;
		if (positionObject == -1) {
			sphere = sphereArray.back();
		}
		else
		{
			sphere = sphereArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					sphere->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					sphere->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					sphere->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					sphere->numberLongitude = atoi(charNumber);
				}
						break;
				case 4: {
					sphere->numberLatitude = atoi(charNumber);
				}
						break;
				case 5: {
					sphere->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 6: {
					sphere->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 7: {
					sphere->radius = atof(charNumber);
				}
						break;
				case 8: {
					sphere->colorR = atof(charNumber);
				}
						break;
				case 9: {
					sphere->colorG = atof(charNumber);
				}
						break;
				case 10: {
					sphere->colorB = atof(charNumber);
				}
						 break;
				case 11: {
					sphere->colorA = atof(charNumber);
				}
						 break;
				case 12: {
					sphere->mShiness = atof(charNumber);
				}
						 break;
				case 13: {
					
				}
						 break;
				case 14: {
					sphere->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube;
		if (positionObject == -1) {
			cube = cubeArray.back();
		}
		else
		{
			cube = cubeArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cube->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cube->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cube->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cube->numberVertexInAxisX = atoi(charNumber);
				}
						break;
				case 4: {
					cube->numberVertexInAxisY = atoi(charNumber);
				}
						break;
				case 5: {
					cube->numberVertexInAxisZ = atoi(charNumber);
				}
						break;
				case 6: {
					cube->colorR = atof(charNumber);
				}
						break;
				case 7: {
					cube->colorG = atof(charNumber);
				}
						break;
				case 8: {
					cube->colorB = atof(charNumber);
				}
						break;
				case 9: {
					cube->colorA = atof(charNumber);
				}
						break;
				case 10: {
					cube->mShiness = atof(charNumber);
				}
						 break;
				case 11: {
					
				}
						 break;
				case 12: {
					cube->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *cube;
		if (positionObject == -1) {
			cube = cubeRoundArray.back();
		}
		else
		{
			cube = cubeRoundArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cube->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cube->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cube->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cube->numberLongitude = atoi(charNumber);
				}
						break;
				case 4: {
					cube->numberLatitude = atoi(charNumber);
				}
						break;
				case 5: {
					cube->radiusRound = atof(charNumber);
				}
						break;
				case 6: {
					cube->xLength = atof(charNumber);
				}
						break;
				case 7: {
					cube->yLength = atof(charNumber);
				}
						break;
				case 8: {
					cube->zLength = atof(charNumber);
				}
						break;
				case 9: {
					cube->colorR = atof(charNumber);
				}
						break;
				case 10: {
					cube->colorG = atof(charNumber);
				}
						 break;
				case 11: {
					cube->colorB = atof(charNumber);
				}
						 break;
				case 12: {
					cube->colorA = atof(charNumber);
				}
						 break;
				case 13: {
					cube->mShiness = atof(charNumber);
				}
						 break;
				case 14: {
					
				}
						 break;
				case 15: {
					cube->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone;
		if (positionObject == -1) {
			cone = coneArray.back();
		}
		else
		{
			cone = coneArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cone->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cone->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cone->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cone->height = atof(charNumber);
				}
						break;
				case 4: {
					cone->radius = atof(charNumber);
				}
						break;
				case 5: {
					cone->numberLongitude = atoi(charNumber);
				}
						break;
				case 6: {
					cone->numberLatitude = atoi(charNumber);
				}
						break;
				case 7: {
					cone->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 8: {
					cone->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 9: {
					cone->colorR = atof(charNumber);
				}
						break;
				case 10: {
					cone->colorG = atof(charNumber);
				}
						 break;
				case 11: {
					cone->colorB = atof(charNumber);
				}
						 break;
				case 12: {
					cone->colorA = atof(charNumber);
				}
						 break;
				case 13: {
					cone->mShiness = atof(charNumber);
				}
						 break;
				case 14: {
					
				}
						 break;
				case 15: {
					cone->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = cylinderArray.back();
		}
		else
		{
			cylinder = cylinderArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cylinder->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cylinder->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cylinder->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cylinder->height = atof(charNumber);
				}
						break;
				case 4: {
					cylinder->radiusUp = atof(charNumber);
				}
						break;
				case 5: {
					cylinder->radiusDown = atof(charNumber);
				}
						break;
				case 6: {
					cylinder->numberLongitude = atoi(charNumber);
				}
						break;
				case 7: {
					cylinder->numberLatitude = atoi(charNumber);
				}
						break;
				case 8: {
					cylinder->degreeLongitudeLimit = atoi(charNumber);
				}
						break;
				case 9: {
					cylinder->degreeLatitudeLimit = atoi(charNumber);
				}
						break;
				case 10: {
					cylinder->colorR = atof(charNumber);
				}
						 break;
				case 11: {
					cylinder->colorG = atof(charNumber);
				}
						 break;
				case 12: {
					cylinder->colorB = atof(charNumber);
				}
						 break;
				case 13: {
					cylinder->colorA = atof(charNumber);
				}
						 break;
				case 14: {
					cylinder->mShiness = atof(charNumber);
				}
						 break;
				case 15: {
					
				}
						 break;
				case 16: {
					cylinder->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = emptyCylinderArray.back();
		}
		else
		{
			cylinder = emptyCylinderArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					cylinder->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					cylinder->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					cylinder->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					cylinder->height = atof(charNumber);
				}
						break;
				case 4: {
					cylinder->radiusUpIn = atof(charNumber);
				}
						break;
				case 5: {
					cylinder->radiusDownIn = atof(charNumber);
				}
						break;
				case 6: {
					cylinder->radiusUpOut = atof(charNumber);
				}
						break;
				case 7: {
					cylinder->radiusDownOut = atof(charNumber);
				}
						break;
				case 8: {
					cylinder->numberLongitude = atoi(charNumber);
				}
						break;
				case 9: {
					cylinder->numberLatitude = atoi(charNumber);
				}
						break;
				case 10: {
					cylinder->degreeLongitudeLimit = atoi(charNumber);
				}
						 break;
				case 11: {
					cylinder->degreeLatitudeLimit = atoi(charNumber);
				}
						 break;
				case 12: {
					cylinder->colorR = atof(charNumber);
				}
						 break;
				case 13: {
					cylinder->colorG = atof(charNumber);
				}
						 break;
				case 14: {
					cylinder->colorB = atof(charNumber);
				}
						 break;
				case 15: {
					cylinder->colorA = atof(charNumber);
				}
						 break;
				case 16: {
					cylinder->mShiness = atof(charNumber);
				}
						 break;
				case 17: {
					
				}
						 break;
				case 18: {
					cylinder->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus;
		if (positionObject == -1) {
			torus = torusArray.back();
		}
		else
		{
			torus = torusArray.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					torus->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					torus->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					torus->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					torus->radiusCake = atof(charNumber);
				}
						break;
				case 4: {
					torus->radiusRoundCake = atof(charNumber);
				}
						break;
				case 5: {
					torus->widthCake = atof(charNumber);
				}
						break;
				case 6: {
					torus->depthCake = atoi(charNumber);
				}
						break;
				case 7: {
					torus->depthRoundCake = atoi(charNumber);
				}
						break;
				case 8: {
					torus->colorR = atof(charNumber);
				}
						break;
				case 9: {
					torus->colorG = atof(charNumber);
				}
						break;
				case 10: {
					torus->colorB = atof(charNumber);
				}
						 break;
				case 11: {
					torus->colorA = atof(charNumber);
				}
						 break;
				case 12: {
					torus->mShiness = atof(charNumber);
				}
						 break;
				case 13: {
					
				}
						 break;
				case 14: {
					torus->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object;
		if (positionObject == -1) {
			object = objectCustom0Array.back();
		}
		else
		{
			object = objectCustom0Array.at(positionObject);
		}
		startOffset = 2;
		offsetGetValue = 0;
		for (int i = 2; i < numberElement1; i++) {
			if (stringValue[i] == ' ') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				switch (offsetGetValue)
				{
				case 0: {
					object->centerObject.x = atof(charNumber);
				}
						break;
				case 1: {
					object->centerObject.y = atof(charNumber);
				}
						break;
				case 2: {
					object->centerObject.z = atof(charNumber);
				}
						break;
				case 3: {
					object->lengthBetween2Row = atof(charNumber);
				}
						break;
				case 4: {
					object->lengthBetween2Column = atof(charNumber);
				}
						break;
				case 5: {
					object->numberLongitude = atoi(charNumber);
				}
						break;
				case 6: {
					object->numberLatitude = atoi(charNumber);
				}
						break;
				case 7: {
					object->colorR = atof(charNumber);
				}
						 break;
				case 8: {
					object->colorG = atof(charNumber);
				}
						 break;
				case 9: {
					object->colorB = atof(charNumber);
				}
						 break;
				case 10: {
					object->colorA = atof(charNumber);
				}
						 break;
				case 11: {
					object->mShiness = atof(charNumber);
				}
						 break;
				case 12: {

				}
						 break;
				case 13: {
					object->idTexture = atoi(charNumber);
				}
						 break;
				default:
					break;
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	default:
		break;
	}

}
//hàm đọc các giá trị vertex từ 1 hàng và đặt nó vào mảng vertex
void addVertexValueFromString(string stringValue, int object, int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberElement1 = stringValue.size(), startOffset = 0,
		offsetGetValue;
	char charNumber[20];

	//kiểm tra xem là hình nào và ví trí nào để lấy ra
	switch (object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip;
		if (positionObject == -1) {
			triaStrip = triaStripArray.back();
		}
		else {
			triaStrip = triaStripArray.at(positionObject);
		}

		//phải xóa hết vertex cũ ra
		triaStrip->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				
				if (offsetGetValue == 0) {
					triaStrip->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaStrip->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					triaStrip->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan;
		if (positionObject == -1) {
			triaFan = triaFanArray.back();
		}
		else {
			triaFan = triaFanArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		triaFan->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					triaFan->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaFan->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					triaFan->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere;
		if (positionObject == -1) {
			sphere = sphereArray.back();
		}
		else {
			sphere = sphereArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		sphere->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					sphere->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					sphere->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					sphere->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 11: {
		CubeAttribute *cube;
		if (positionObject == -1) {
			cube = cubeArray.back();
		}
		else {
			cube = cubeArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		cube->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					cube->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 12: {
		CubeRoundAttribute *cube;
		if (positionObject == -1) {
			cube = cubeRoundArray.back();
		}
		else {
			cube = cubeRoundArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		cube->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					cube->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 13: {
		ConeAttribute *cone;
		if (positionObject == -1) {
			cone = coneArray.back();
		}
		else {
			cone = coneArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		cone->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cone->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cone->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					cone->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 14: {
		CylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = cylinderArray.back();
		}
		else {
			cylinder = cylinderArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		cylinder->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					cylinder->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 16: {
		EmptyCylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = emptyCylinderArray.back();
		}
		else {
			cylinder = emptyCylinderArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		cylinder->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					cylinder->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus;
		if (positionObject == -1) {
			torus = torusArray.back();
		}
		else {
			torus = torusArray.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		torus->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					torus->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					torus->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					torus->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object;
		if (positionObject == -1) {
			object = objectCustom0Array.back();
		}
		else {
			object = objectCustom0Array.at(positionObject);
		}
		//phải xóa hết vertex cũ ra
		object->vertexArray.clear();
		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					object->vertexArray.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					object->vertexArray.back().y = atof(charNumber);
				}
				else
				{
					object->vertexArray.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	default:
		break;
	}

}
//hàm thêm các vertex vào các vị trí trong mảng
void addVertexAtPositionFromString(string stringValue, int object, int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	char charNumber[20];
	int numberElement1 = stringValue.size(), startOffset = 0, offsetGetValue = 0, positionAdd = 0;

	//kiểm tra xem là hình nào và ví trí nào để lấy ra
	switch (object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					triaStrip->vertexArray.insert(triaStrip->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaStrip->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					triaStrip->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					triaFan->vertexArray.insert(triaFan->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaFan->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					triaFan->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere = sphereArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					sphere->vertexArray.insert(sphere->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					sphere->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					sphere->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube = cubeArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->vertexArray.insert(cube->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					cube->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *cube = cubeRoundArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->vertexArray.insert(cube->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					cube->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone = coneArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cone->vertexArray.insert(cone->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cone->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					cone->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->vertexArray.insert(cylinder->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					cylinder->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->vertexArray.insert(cylinder->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					cylinder->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus = torusArray.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					torus->vertexArray.insert(torus->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					torus->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					torus->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(positionObject);

		offsetGetValue = 0;
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			else if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			//nếu trước đó là một dấu '}' và bây giờ cũng là dấu '}' thì là kết thúc lấy vertex array
			//nếu trước đó là dấu '}' thì numberElement2 sẽ bằng 0
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					object->vertexArray.insert(object->vertexArray.begin() + positionAdd, { (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					object->vertexArray.at(positionAdd).y = atof(charNumber);
				}
				else
				{
					object->vertexArray.at(positionAdd).z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	default:
		break;
	}

}
//hàm xóa các vertex tại các vị trí trong mảng
void deleteVertexAtPositionFromString(string stringValue, int object, int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	char charNumber[20];
	int numberElement1 = stringValue.size(), startOffset = 0, positionAdd = 0, numberVertexBefore = 0;

	//kiểm tra xem là hình nào và ví trí nào để lấy ra
	switch (object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip = triaStripArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				triaStrip->vertexArray.erase(triaStrip->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan = triaFanArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				triaFan->vertexArray.erase(triaFan->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere = sphereArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				sphere->vertexArray.erase(sphere->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube = cubeArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				cube->vertexArray.erase(cube->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *cube = cubeRoundArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				cube->vertexArray.erase(cube->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone = coneArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				cone->vertexArray.erase(cone->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder = cylinderArray.at(positionObject);
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				cylinder->vertexArray.erase(cylinder->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				cylinder->vertexArray.erase(cylinder->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus = torusArray.at(positionObject);

		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				torus->vertexArray.erase(torus->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object = objectCustom0Array.at(positionObject);
		startOffset = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu gặp đấu ( là bắt đầu đọc vị trí vertex
			if (stringValue[i] == '(') {
				startOffset = i + 1;
			}
			//nếu gặp dấu - là kết thúc đọc vị trí vertex
			else if (stringValue[i] == '_') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				positionAdd = atoi(charNumber);

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				startOffset = i + 1;
			}
			else if (stringValue[i] == ')') {
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}
				//đặt vị trí vertex cần thêm vào
				numberVertexBefore = atoi(charNumber);

				//xóa phần tử tại ví trí đã cho(phải giảm đi vị trí của các phần tử trước nó
				//do sắp sếp theo thứ tự tăng dần nên khi xóa các phần tử trước thì các phần tử sau bị trồi lên)
				object->vertexArray.erase(object->vertexArray.begin() + (positionAdd - numberVertexBefore));
			}
		}
	}
			 break;
	default:
		break;
	}

}
//hàm đọc các giá trị normal vector từ 1 hàng và đặt nó vào mảng normal vector
//lưu ý các giá trị normal vector có thể bị tràn xuống hàng dưới nên phải lưu lại trong mảng char trả về 
//các giá trị còn thừa của dãy trên và offsetGetValue và numberElementBefore để lát kết hợp với chuỗi dưới
void addNormalVectorFromString(string stringValue, int object, int positionObject,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	int numberElement1 = stringValue.size(), startOffset = 0, offsetGetValue = 0;
	char charNumber[20];
	//kiểm tra xem là hình nào và ví trí nào để lấy ra
	switch (object)
	{
	case 4: {
		TriangleStripAttribute *triaStrip;
		if (positionObject == -1) {
			triaStrip = triaStripArray.back();
		}else{
			triaStrip = triaStripArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		triaStrip->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					triaStrip->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaStrip->normalVector.back().y = atof(charNumber);
				}
				else
				{
					triaStrip->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 5: {
		TriangleFanAttribute *triaFan;
		if (positionObject == -1) {
			triaFan = triaFanArray.back();
		}
		else {
			triaFan = triaFanArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		triaFan->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					triaFan->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					triaFan->normalVector.back().y = atof(charNumber);
				}
				else
				{
					triaFan->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			break;
	case 10: {
		SphereAttribute *sphere;
		if (positionObject == -1) {
			sphere = sphereArray.back();
		}
		else {
			sphere = sphereArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		sphere->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					sphere->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					sphere->normalVector.back().y = atof(charNumber);
				}
				else
				{
					sphere->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 11: {
		CubeAttribute *cube;
		if (positionObject == -1) {
			cube = cubeArray.back();
		}
		else {
			cube = cubeArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		cube->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->normalVector.back().y = atof(charNumber);
				}
				else
				{
					cube->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 12: {
		CubeRoundAttribute *cube;
		if (positionObject == -1) {
			cube = cubeRoundArray.back();
		}
		else {
			cube = cubeRoundArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		cube->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cube->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cube->normalVector.back().y = atof(charNumber);
				}
				else
				{
					cube->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 13: {
		ConeAttribute *cone;
		if (positionObject == -1) {
			cone = coneArray.back();
		}
		else {
			cone = coneArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		cone->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cone->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cone->normalVector.back().y = atof(charNumber);
				}
				else
				{
					cone->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 14: {
		CylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = cylinderArray.back();
		}
		else {
			cylinder = cylinderArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		cylinder->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->normalVector.back().y = atof(charNumber);
				}
				else
				{
					cylinder->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 16: {
		EmptyCylinderAttribute *cylinder;
		if (positionObject == -1) {
			cylinder = emptyCylinderArray.back();
		}
		else {
			cylinder = emptyCylinderArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		cylinder->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					cylinder->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					cylinder->normalVector.back().y = atof(charNumber);
				}
				else
				{
					cylinder->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 17: {
		TorusAttribute *torus;
		if (positionObject == -1) {
			torus = torusArray.back();
		}
		else {
			torus = torusArray.at(positionObject);
		}
		//xóa đi normal vector cũ
		torus->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					torus->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					torus->normalVector.back().y = atof(charNumber);
				}
				else
				{
					torus->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	case 19: {
		ObjectCustom0Attribute *object;
		if (positionObject == -1) {
			object = objectCustom0Array.back();
		}
		else {
			object = objectCustom0Array.at(positionObject);
		}
		//xóa đi normal vector cũ
		object->normalVector.clear();

		startOffset = 0;
		offsetGetValue = 2;
		for (int i = 2; i < numberElement1; i++) {
			//nếu là gặp dấu { thì là chuẩn bị 1 vertex mới với 3 giá trị
			if (stringValue[i] == '{') {
				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue = 0;
			}
			else if (stringValue[i] == ',' || stringValue[i] == '}') {
				//chuyển chuỗi sang mảng char
				for (int j = startOffset; j < i; j++) {
					charNumber[j - startOffset] = stringValue[j];
				}

				if (offsetGetValue == 0) {
					object->normalVector.push_back({ (float)atof(charNumber),NULL,NULL });
				}
				else if (offsetGetValue == 1) {
					object->normalVector.back().y = atof(charNumber);
				}
				else
				{
					object->normalVector.back().z = atof(charNumber);
				}

				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đặt lại các giá trị
				startOffset = i + 1;
				offsetGetValue++;
			}
		}
	}
			 break;
	default:
		break;
	}
}
//hàm xóa các vật tại vị trí đã cho
void deleteObjectAtPosition(int object, int position,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	switch (object)
	{
		//trước khi xóa các con trỏ phải xóa các vùng nhớ mà nó trỏ đến nếu k0 sẽ bị rò rỉ bộ nhớ
	case 3:
		delete triaArray.at(position);
		triaArray.erase(triaArray.begin() + position);
		break;
	case 4:
		delete triaStripArray.at(position);
		triaStripArray.erase(triaStripArray.begin() + position);
		break;
	case 5:
		delete triaFanArray.at(position);
		triaFanArray.erase(triaFanArray.begin() + position);
		break;
	case 10:
		delete sphereArray.at(position);
		sphereArray.erase(sphereArray.begin() + position);
		break;
	case 11:
		delete cubeArray.at(position);
		cubeArray.erase(cubeArray.begin() + position);
		break;
	case 12:
		delete cubeRoundArray.at(position);
		cubeRoundArray.erase(cubeRoundArray.begin() + position);
		break;
	case 13:
		delete coneArray.at(position);
		coneArray.erase(coneArray.begin() + position);
		break;
	case 14:
		delete cylinderArray.at(position);
		cylinderArray.erase(cylinderArray.begin() + position);
		break;
	case 15:
		delete pyrArray.at(position);
		pyrArray.erase(pyrArray.begin() + position);
		break;
	case 16:
		delete emptyCylinderArray.at(position);
		emptyCylinderArray.erase(emptyCylinderArray.begin() + position);
		break;
	case 17:
		delete torusArray.at(position);
		torusArray.erase(torusArray.begin() + position);
		break;
	case 18:
		delete pictureArray.at(position);
		pictureArray.erase(pictureArray.begin() + position);
		break;
	case 19:
		delete objectCustom0Array.at(position);
		objectCustom0Array.erase(objectCustom0Array.begin() + position);
		break;
	default:
		break;
	}
}
//hàm thêm vật tại ví trí đã cho
void addObjectAtPosition(int object, int position,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {
	switch (object)
	{
		//thêm các vật vào mảng tại đúng vị trí lúc trước
	case 3:
	{
		TriangleAttribute *tria = new TriangleAttribute();
		if (position == -1) {
			triaArray.push_back(tria);
		}
		else
		{
			triaArray.insert(triaArray.begin() + position, tria);
		}
		
	}
		break;
	case 4:
	{
		TriangleStripAttribute *triaStrip = new TriangleStripAttribute();
		if (position == -1) {
			triaStripArray.push_back(triaStrip);
		}
		else
		{
			triaStripArray.insert(triaStripArray.begin() + position, triaStrip);
		}
		
	}
		break;
	case 5:
	{
		TriangleFanAttribute *triaFan = new TriangleFanAttribute();
		if (position == -1) {
			triaFanArray.push_back(triaFan);
		}
		else
		{
			triaFanArray.insert(triaFanArray.begin() + position, triaFan);
		}
		
	}
		break;
	case 10:
	{
		SphereAttribute *sphere = new SphereAttribute();
		if (position == -1) {
			sphereArray.push_back(sphere);
		}
		else
		{
			sphereArray.insert(sphereArray.begin() + position, sphere);
		}
		
	}
		break;
	case 11:
	{
		CubeAttribute *cube = new CubeAttribute();
		if (position == -1) {
			cubeArray.push_back(cube);
		}
		else
		{
			cubeArray.insert(cubeArray.begin() + position, cube);
		}
		
	}
		break;
	case 12:
	{
		CubeRoundAttribute *cube = new CubeRoundAttribute();
		if (position == -1) {
			cubeRoundArray.push_back(cube);
		}
		else
		{
			cubeRoundArray.insert(cubeRoundArray.begin() + position, cube);
		}
		
	}
		break;
	case 13:
	{
		ConeAttribute *cone = new ConeAttribute();
		if (position == -1) {
			coneArray.push_back(cone);
		}
		else
		{
			coneArray.insert(coneArray.begin() + position, cone);
		}
		
	}
		break;
	case 14:
	{
		CylinderAttribute *cylinder = new CylinderAttribute();
		if (position == -1) {
			cylinderArray.push_back(cylinder);
		}
		else
		{
			cylinderArray.insert(cylinderArray.begin() + position, cylinder);
		}
		
	}
		break;
	case 15:
	{
		PyramidAttribute *pyr = new PyramidAttribute();
		if (position == -1) {
			pyrArray.push_back(pyr);
		}
		else
		{
			pyrArray.insert(pyrArray.begin() + position, pyr);
		}
		
	}
		break;
	case 16:
	{
		EmptyCylinderAttribute *cylinder = new EmptyCylinderAttribute();
		if (position == -1) {
			emptyCylinderArray.push_back(cylinder);
		}
		else
		{
			emptyCylinderArray.insert(emptyCylinderArray.begin() + position, cylinder);
		}
		
	}
		break;
	case 17:
	{
		TorusAttribute *torus = new TorusAttribute();
		if (position == -1) {
			torusArray.push_back(torus);
		}
		else
		{
			torusArray.insert(torusArray.begin() + position, torus);
		}
		
	}
		break;
	case 18:
	{
		PictureAttribute *picture = new PictureAttribute();
		if (position == -1) {
			pictureArray.push_back(picture);
		}
		else
		{
			pictureArray.insert(pictureArray.begin() + position, picture);
		}
	}
		break;
	case 19:
	{
		ObjectCustom0Attribute *object = new ObjectCustom0Attribute();
		if (position == -1) {
			objectCustom0Array.push_back(object);
		}
		else
		{
			objectCustom0Array.insert(objectCustom0Array.begin() + position, object);
		}

	}
	break;
	default:
		break;
	}
}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing) {

	string stringPath;

	//các biến lưu giá trị cho thuộc tính
	int whichEffect, object, positionObject, numberElement1, startOffset;
	char charNumber[20];

	ifstream myfile(path);
	if (myfile.is_open()) {
		while (getline(myfile, stringPath))
		{
			switch (stringPath[0])
			{
				//lấy ra kiểu chỉnh sửa
			case 'E': {
				//đặt kiểu chỉnh sửa
				charNumber[0] = stringPath[2];
				whichEffect = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
					  break;
					  //lấy ra kiểu đối tượng
			case 'O': {
				//chuyển char về kiểu int
				numberElement1 = stringPath.size();
				for (int i = 2; i < numberElement1; i++) {
					charNumber[i - 2] = stringPath[i];
				}
				object = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
					  break;
					  //lấy ra vị trí của đối tượng trong mảng các đối tượng cùng kiểu
			case 'P': {
				int numberElementBefore;
				//chuyển char về kiểu int
				numberElement1 = stringPath.size();
				startOffset = 2;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '_') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						positionObject = atoi(charNumber);
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						break;
					}
				}
				
				//trường hợp này chỉ có whichEffect=3,4,5
				//trường hợp 5 thì không cần tạo mới hay xóa đi mà chỉ cần thay đổi các giá trị vertex và normal
				if (whichEffect != 5) {
					//nếu whichEffect là xóa(4) thì nếu isTurnUp là false thì khởi tạo đối tượng mới và thêm nó vào vị trí cần thêm
					//nếu isTurnUp là true thì xóa đi hình ở vị trí đó
					//nếu whichEffect là xóa(3) thì nếu isTurnUp là false thì xóa đi hình ở vị trí đó
					//nếu isTurnUp là true thì khởi tạo đối tượng mới và thêm nó vào vị trí cần thêm
					if ((!isTurnUp && whichEffect == 3) || (isTurnUp && whichEffect == 4)) {
						//đối với trường hợp xóa thì do mảng này ta lưu với thứ tự từ nhỏ đến lớn
						//vậy nên khi xóa với giá trị được lưu từ nhỏ đến lớn thì(vd: khi xóa 1 phần tử
						//trước thì phần thử phía sau nó phải giảm vị trí 1 đơn vị)

						//Lấy số phần tử cùng kiểu ở trước phần tử hiện tại(đã được tính trước và lưu trong tệp txt)
						for (int i = startOffset; i < numberElement1; i++) {
							if (stringPath[i] == ' ') {
								for (int j = startOffset; j < i; j++) {
									charNumber[j - startOffset] = stringPath[j];
								}
								numberElementBefore = atoi(charNumber);
								//xóa các giá trị trong mảng để dùng lại lần sau
								memset(charNumber, 0, sizeof(charNumber));
							}
						}
						deleteObjectAtPosition(object, (positionObject - numberElementBefore),
							triaArray, triaStripArray, triaFanArray, sphereArray,
							cubeArray, cubeRoundArray, coneArray, cylinderArray,
							pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
						//xóa luôn các vật đang được chọn trong itemsChoice vì các vật này đã được xóa
						itemsChoice.clear();
					}
					else
					{
						//thêm mới vật tại vị trí đã cho
						addObjectAtPosition(object, positionObject,
							triaArray, triaStripArray, triaFanArray, sphereArray,
							cubeArray, cubeRoundArray, coneArray, cylinderArray,
							pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
					}
				}
			}
					  break;
					  //lấy các vertex và đặt vào 
			case 'V': {
				//nếu là chế độ thêm hình mà dịch chuyển lên nghĩa là thêm lại hình hoặc
				//nếu là chế độ xóa hình mà lùi lại nghĩa là thêm lại hình vừa bị xóa
				//nếu = 5 là chế độ chỉnh sửa numberLong,numberlatitude và thay đổi số vertexArray và normalVector
				if ((isTurnUp && whichEffect == 3) || (!isTurnUp && whichEffect == 4) || whichEffect == 5) {
					//hàm thêm vertex từ 1 chuỗi string
					addVertexValueFromString(stringPath, object, positionObject,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				
			}
					  break;
					  //lấy các normal và đặt vào mảng
			case 'N': {
				//nếu là chế độ thêm hình mà dịch chuyển lên nghĩa là thêm lại hình hoặc
				//nếu là chế độ xóa hình mà lùi lại nghĩa là thêm lại hình vừa bị xóa
				//nếu = 5 là chế độ chỉnh sửa numberLong,numberlatitude và thay đổi số vertexArray và normalVector
				if ((isTurnUp && whichEffect == 3) || (!isTurnUp && whichEffect == 4) || whichEffect == 5) {
					//hàm thêm normal từ 1 chuỗi string
					addNormalVectorFromString(stringPath, object, positionObject,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}

			}
					  break;
					  //đặt các thuôc tính vào đối tượng
			case 'A': {
				//nếu là chế độ thêm hình mà dịch chuyển lên nghĩa là thêm lại hình hoặc
				//nếu là chế độ xóa hình mà lùi lại nghĩa là thêm lại hình vừa bị xóa
				//nếu = 5 là chế độ chỉnh sửa numberLong,numberlatitude và thay đổi số vertexArray và normalVector
				if ((isTurnUp && whichEffect == 3) || (!isTurnUp && whichEffect == 4) || whichEffect == 5) {
					//hàm thêm các thuộc tính từ chuỗi string
					//nếu là lùi lại là thêm vật,nhớ thêm lại id vào mảng idsUsing(đã đặt trong hàm phía dưới rồi)
					if (whichEffect == 5) {
						changeAttributeFromString(stringPath, object, positionObject,
							triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
							coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
					}
					else
					{
						addAttributeFromString(stringPath, object, positionObject,
							triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
							coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array, idsUsing);
					}
				}
				else
				{
					//nếu là xóa vật nhớ kiểm tra xem vật bị xóa có phải là vật nằm trong mảng chứa các vertex đối xứng không
					//nếu có thì xóa nó đi
					int numberSymmetry = symmetryVertices.size();
					SymmetryVertices symmetryVerticesCheck;
					//nếu là chế độ xóa vật thì kiểm tra nếu vật bị xóa nằm trong mảng xác đinh đối xứng thì xóa
					//vật đó ra khỏi mảng xác định các vật có đỉnh đối xứng
					for (int j = 0; j < numberSymmetry; j++) {
						symmetryVerticesCheck = symmetryVertices.at(j);
						if (symmetryVerticesCheck.object == object &&
							symmetryVerticesCheck.positionInArray == positionObject) {
							//xóa phần tử có đối tượng là đối tượng đối xứng
							symmetryVertices.erase(symmetryVertices.begin() + j);
							//đặt whichItemSymmetry về -1 luôn
							whichItemSymmetry = -1;
							break;
						}
					}
					//kiểm tra xem vật vừa xóa có thông tin nằm trong symmetryObject không
					numberSymmetry = symmetryObjects.size();
					SymmetryObjects symmetryObjectsCheck;
					//nếu là chế độ xóa vật thì kiểm tra nếu vật bị xóa nằm trong mảng xác đinh đối xứng thì xóa
					//vật đó ra khỏi mảng xác định các vật có đỉnh đối xứng
					for (int j = 0; j < numberSymmetry; j++) {
						symmetryObjectsCheck = symmetryObjects.at(j);
						if (symmetryObjectsCheck.object1 == object &&
							(symmetryObjectsCheck.positionInArray1 == positionObject ||
								symmetryObjectsCheck.positionInArray2 == positionObject)) {
							//xóa phần tử có đối tượng là đối tượng đối xứng
							symmetryObjects.erase(symmetryObjects.begin() + j);
							//đặt whichItemSymmetry về -1 luôn
							whichItemSymmetry = -1;
							break;
						}
					}


					//nếu tiến lên là xóa vật,nhớ xóa id ra khỏi mảng idsUsing
					int numberSpace = 0,id;
					numberElement1 = stringPath.size();
					//id bắt đầu từ khoảng trắng thứ 3 trong chuỗi từ sau ra trước
					for (int i = numberElement1; i>= 0; i--) {
						if (stringPath[i] == ' ') {
							numberSpace++;
							if (numberSpace == 3) {
								startOffset = i + 1;
								break;
							}
						}
					}
					//bắt đầu đọc id
					for (int i = startOffset; i < numberElement1; i++) {
						if (stringPath[i] == ' ') {
							for (int j = startOffset; j < i; j++) {
								charNumber[j - startOffset] = stringPath[j];
							}
							id = atoi(charNumber);
							//xóa các giá trị trong mảng để dùng lại lần sau
							memset(charNumber, 0, sizeof(charNumber));
							break;
						}
					}
					int numberId = idsUsing.size();
					//tìm kiếm id này trong mảng idsUsing để xóa đi
					for (int k = 0; k < numberId; k++) {
						if (idsUsing.at(k) == id) {
							//xóa id được chọn ra khỏi mảng idsUsing
							idsUsing.erase(idsUsing.begin() + k);
							break;
						}
					}
				}

			}
					  break;
			default: {

			}
					 break;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

}
//hàm load các thông tin về các vật đã lưu lần trước trong tệp txt
void loadObjectsInTxt(char *path,
	vector<TriangleAttribute*> &triaArray, vector<TriangleStripAttribute*> &triaStripArray,
	vector<TriangleFanAttribute*> &triaFanArray, vector<SphereAttribute*> &sphereArray,
	vector<CubeAttribute*> &cubeArray, vector<CubeRoundAttribute*> &cubeRoundArray,
	vector<ConeAttribute*> &coneArray, vector<CylinderAttribute*> &cylinderArray,
	vector<PyramidAttribute*> &pyrArray, vector<EmptyCylinderAttribute*> &emptyCylinderArray,
	vector<TorusAttribute*> &torusArray, vector<PictureAttribute*> &pictureArray,
	vector<ObjectCustom0Attribute*> &objectCustom0Array, vector<int> &idsUsing) {

	//đầu tiên làm sạch các mảng trước khi bỏ phần tử vào
	triaArray.clear();
	triaStripArray.clear();
	triaFanArray.clear();
	sphereArray.clear();
	cubeArray.clear();
	cubeRoundArray.clear();
	coneArray.clear();
	cylinderArray.clear();
	emptyCylinderArray.clear();
	torusArray.clear();

	string stringPath;

	//các biến lưu giá trị cho thuộc tính
	int object, numberElement1, numberElement2, offsetGetValue;
	char charNumber[20];

	ifstream myfile(path);
	if (myfile.is_open()) {
		while (getline(myfile, stringPath))
		{
			switch (stringPath[0])
			{
			//lấy ra kiểu đối tượng
			case 'O': {
				//chuyển char về kiểu int
				numberElement1 = stringPath.size();
				for (int i = 2; i < numberElement1; i++) {
					charNumber[i - 2] = stringPath[i];
				}
				object = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));

				//đầu tiên thêm đối tượng này vào mảng
				addObjectAtPosition(object, -1,
					triaArray, triaStripArray, triaFanArray, sphereArray,
					cubeArray, cubeRoundArray, coneArray, cylinderArray,
					pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
					  break;
			//lấy các vertex và đặt vào 
			case 'V': {
				addVertexValueFromString(stringPath, object, -1,
					triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
			}
					  break;
					  //lấy các normal và đặt vào mảng
			case 'N': {
				addNormalVectorFromString(stringPath, object, -1,
					triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);

			}
					  break;
					  //đặt các thuôc tính vào đối tượng
			case 'A': {
				//hàm thêm các thuộc tính từ chuỗi string
				addAttributeFromString(stringPath, object, -1,
					triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
					coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array
					, idsUsing);

			}
					  break;
			default: {
				
			}
					 break;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

}
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	string stringPath;

	//các biến lưu giá trị cho thuộc tính
	int whichEffect, objectChoice, positionObject, numberElement1, startOffset;
	char charNumber[20];

	//biến chứa vị trí trong mảng của object đối xứng với object đang được chọn
	int positionObjectSymmetry = -1;

	ifstream myfile(path);
	if (myfile.is_open()) {
		while (getline(myfile, stringPath))
		{
			switch (stringPath[0])
			{
				//lấy ra kiểu chỉnh sửa
			case 'E': {
				//đặt kiểu chỉnh sửa
				charNumber[0] = stringPath[2];
				whichEffect = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
					  break;
					  //lấy ra kiểu đối tượng
			case 'O': {
				//chuyển char về kiểu int
				numberElement1 = stringPath.size();
				for (int i = 2; i < numberElement1; i++) {
					charNumber[i - 2] = stringPath[i];
				}
				objectChoice = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
					  break;
					  //lấy ra vị trí của đối tượng trong mảng các đối tượng cùng kiểu
			case 'P': {
				//chuyển char về kiểu int
				numberElement1 = stringPath.size();
				startOffset = 2;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == '_') {
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}
						positionObject = atoi(charNumber);
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));
						startOffset = i + 1;
						break;
					}
				}

				//kiểm tra xem object đang chọn có object đối xứng không
				numberElement1 = symmetryObjects.size();
				SymmetryObjects symmetryObjectCheck;
				for (int i = 0; i < numberElement1; i++) {
					symmetryObjectCheck = symmetryObjects.at(i);
					if (symmetryObjectCheck.object1 == objectChoice) {
						if (symmetryObjectCheck.positionInArray1 == positionObject) {
							positionObjectSymmetry = symmetryObjectCheck.positionInArray2;
							break;
						}else if (symmetryObjectCheck.positionInArray2 == positionObject) {
							positionObjectSymmetry = symmetryObjectCheck.positionInArray1;
							break;
						}
					}
				}
			}
					  break;
					  //lấy các vertex và đặt vào 
			case 'V': {
				//nếu whichEffect=6 và isTurnUp là thêm các vertex
				//nếu whichEffect=7 và isTurnUp là xóa các vertex
				if ((isTurnUp && whichEffect == 6) || (!isTurnUp && whichEffect == 7)) {
					//hàm thêm vertex từ 1 chuỗi string
					addVertexAtPositionFromString(stringPath, objectChoice, positionObject,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
				//nếu là chế độ xóa các vertex thì sau khi xóa các vertex xong thì
				//tính lại normal dựa trên các vertex còn lại
				else
				{
					deleteVertexAtPositionFromString(stringPath, objectChoice, positionObject,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}

			}
					  break;
			//lấy cụm vertex dành cho object đối xứng nếu có 
			case 'S': {
				//nếu whichEffect=6 và isTurnUp là thêm các vertex
				//nếu whichEffect=7 và isTurnUp là xóa các vertex
				if ((isTurnUp && whichEffect == 6) || (!isTurnUp && whichEffect == 7)) {
					//hàm thêm vertex từ 1 chuỗi string
					addVertexAtPositionFromString(stringPath, objectChoice, positionObjectSymmetry,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
				//nếu là chế độ xóa các vertex thì sau khi xóa các vertex xong thì
				//tính lại normal dựa trên các vertex còn lại
				else
				{
					deleteVertexAtPositionFromString(stringPath, objectChoice, positionObjectSymmetry,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
				}
			}
					  break;
			//đặt các thuôc tính vào đối tượng
			case 'A': {
				//nếu whichEffect=6 và isTurnUp là thêm các vertex
				//nếu whichEffect=7 và isTurnUp là xóa các vertex
				if ((isTurnUp && whichEffect == 6) || (!isTurnUp && whichEffect == 7)) {
					//hàm thêm các thuộc tính từ chuỗi string
					//nếu là lùi lại là thêm vật,nhớ thêm lại id vào mảng idsUsing(đã đặt trong hàm phía dưới rồi)
					changeAttributeFromString(stringPath, objectChoice, positionObject,
						triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
						objectCustom0Array);
					//nếu có object đối xứng thì tính cho object đối xứng luôn
					if (positionObjectSymmetry != -1) {
						changeAttributeFromString(stringPath, objectChoice, positionObjectSymmetry,
							triaArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
							coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray,
							objectCustom0Array);
					}

				}
				//nếu là xóa các vertex thì lùi giá trị của số hàng hay số cột tương ứng
				else
				{
					if (!positionChoiceRowOrColumn.empty()) {
						//số phần tử trong positionChoiceRowOrColumn chính là số giá trị(row hay column) bị xóa
						int minusRowOrColumn = positionChoiceRowOrColumn.size();
						bool isChoiceRow = false;
						if (positionChoiceRowOrColumn.back().positionRow != -1) {
							isChoiceRow = true;
						}
						SymmetryVertices symmetryCheck;
						switch (objectChoice)
						{
						case 10: {
							SphereAttribute *object = sphereArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = sphereArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						case 11: {
							CubeAttribute *object = cubeArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberVertexInAxisY -= minusRowOrColumn;
							}
							else
							{
								//đối với cube nếu giảm theo cột thì phải kiểm tra xem vị trí giảm nằm ở trục X hay Z
								//để biết vị trí giảm
								if (positionChoiceRowOrColumn.back().positionColumn < object->numberVertexInAxisX) {
									object->numberVertexInAxisX -= minusRowOrColumn;
								}
								else
								{
									object->numberVertexInAxisZ -= minusRowOrColumn;
								}
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = cubeArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberVertexInAxisY -= minusRowOrColumn;
								}
								else
								{
									//đối với cube nếu giảm theo cột thì phải kiểm tra xem vị trí giảm nằm ở trục X hay Z
									//để biết vị trí giảm
									if (positionChoiceRowOrColumn.back().positionColumn < object->numberVertexInAxisX) {
										object->numberVertexInAxisX -= minusRowOrColumn;
									}
									else
									{
										object->numberVertexInAxisZ -= minusRowOrColumn;
									}
								}
							}
						}
								 break;
						case 12: {
							CubeRoundAttribute *object = cubeRoundArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = cubeRoundArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						case 13: {
							ConeAttribute *object = coneArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = coneArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						case 14: {
							CylinderAttribute *object = cylinderArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = cylinderArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						case 16: {
							EmptyCylinderAttribute *object = emptyCylinderArray.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = emptyCylinderArray.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						case 19: {
							ObjectCustom0Attribute *object = objectCustom0Array.at(positionObject);
							//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
							//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
							if (isChoiceRow) {
								object->numberLatitude -= minusRowOrColumn;
							}
							else
							{
								object->numberLongitude -= minusRowOrColumn;
							}

							//nếu có object đối xứng thì tính cho object đối xứng luôn
							if (positionObjectSymmetry != -1) {
								object = objectCustom0Array.at(positionObjectSymmetry);
								//xem hàng(row) hay cột(column) được chọn để giảm tương ứng
								//nếu là hàng thì giảm numberLatitude,còn nếu là cột(column) thì giảm numberLongitude
								if (isChoiceRow) {
									object->numberLatitude -= minusRowOrColumn;
								}
								else
								{
									object->numberLongitude -= minusRowOrColumn;
								}
							}
						}
								 break;
						default:
							break;
						}
						//nếu là thêm thì không cần lo về các vị trí trong positionROrC vì nó đã lưu lại trong thuộc
						//tính app và được load lên rước khi hàm này được gọi rồi
						//còn nếu là xóa thì ta phải xóa phần tử bị xóa ra khỏi cả 2 mảng và lùi giá trị các 
						//phần tử lớn hơn 2 phần tử đó(cứ lớn hơn mỗi phần tử ta trừ đi 1)

						//************đối với trường hợp đã có thông tin trong symmetryObject thì sẽ không có thông tin trong 
						//symmetryVertex,vậy nên nếu tìm được object đối xứng thì không không cần lo về symmetryVertex nữa
						if (positionObjectSymmetry == -1) {
							int positionVerticesSymmetry = -1, numberSymmetry = symmetryVertices.size(), numberItemSymmetry;
							SymmetryVertices *symmetryCheck;
							for (int i = 0; i < numberSymmetry; i++) {
								symmetryCheck = &symmetryVertices.at(i);
								if (symmetryCheck->object == objectChoice &&
									symmetryCheck->positionInArray == positionObject) {
									positionVerticesSymmetry = i;
								}
							}
							//nếu tìm thấy thông tin của object hiện tại trong symmetryVertices
							if (positionVerticesSymmetry != -1) {
								if (minusRowOrColumn == 1) {
									//đối với trường hợp có 1 phần tử bị xóa thì phải xem xem object hiện tại có thông tin trong symmetryVertices
									//không,nếu có thì phải lùi giá trị các phần tử lớn hơn phần tử bị xóa
									fixErrorWhenDeleteItemNotHaveItemSymmetry(positionChoiceRowOrColumn.at(0),
										*symmetryCheck);
								}
								else if (minusRowOrColumn == 2) {
									PositionRowOrColumn pos1 = positionChoiceRowOrColumn.at(0),
										pos2 = positionChoiceRowOrColumn.at(1);
									if (isChoiceRow) {
										//đầu tiên kiểm tra xem vị trí có phần tử bị xóa trong cả 2 mảng
										//và xóa nó ra khỏi cả 2 mảng
										numberItemSymmetry = symmetryCheck->positionROrC1.size()<symmetryCheck->positionROrC2.size() ?
											symmetryCheck->positionROrC1.size() : symmetryCheck->positionROrC2.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											if (pos1.positionRow == symmetryCheck->positionROrC1.at(j).positionRow ||
												pos2.positionRow == symmetryCheck->positionROrC1.at(j).positionRow) {

												//xóa phần tử bị xóa ra khỏi 2 mảng
												symmetryCheck->positionROrC1.erase(symmetryCheck->positionROrC1.begin() + j);
												symmetryCheck->positionROrC2.erase(symmetryCheck->positionROrC2.begin() + j);
												break;
											}
										}

										if (pos1.positionRow > pos2.positionRow) {
											//nếu pos1 lớn hơn thì lùi giá trị của pos1
											pos1.positionRow--;
										}
										else
										{
											//nếu pos2 lớn hơn thì lùi giá trị của pos2
											pos2.positionRow--;
										}
										//lùi các phần tử có giá trị lớn hơn
										numberItemSymmetry = symmetryCheck->positionROrC1.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											if (symmetryCheck->positionROrC1.at(j).positionRow > pos1.positionRow) {
												symmetryCheck->positionROrC1.at(j).positionRow--;
											}
											if (symmetryCheck->positionROrC1.at(j).positionRow > pos2.positionRow) {
												symmetryCheck->positionROrC1.at(j).positionRow--;
											}
										}
										numberItemSymmetry = symmetryCheck->positionROrC2.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											if (symmetryCheck->positionROrC2.at(j).positionRow > pos1.positionRow) {
												symmetryCheck->positionROrC2.at(j).positionRow--;
											}
											if (symmetryCheck->positionROrC2.at(j).positionRow > pos2.positionRow) {
												symmetryCheck->positionROrC2.at(j).positionRow--;
											}
										}
									}
									else
									{
										//đầu tiên kiểm tra xem vị trí có phần tử bị xóa trong cả 2 mảng
										//và xóa vị trí ra khỏi mảng
										numberItemSymmetry = symmetryCheck->positionROrC1.size()<symmetryCheck->positionROrC2.size() ?
											symmetryCheck->positionROrC1.size() : symmetryCheck->positionROrC2.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											if (pos1.positionColumn == symmetryCheck->positionROrC1.at(j).positionColumn ||
												pos2.positionColumn == symmetryCheck->positionROrC1.at(j).positionColumn) {

												//xóa phần tử bị xóa ra khỏi 2 mảng
												symmetryCheck->positionROrC1.erase(symmetryCheck->positionROrC1.begin() + j);
												symmetryCheck->positionROrC2.erase(symmetryCheck->positionROrC2.begin() + j);
												break;
											}
										}

										if (pos1.positionColumn > pos2.positionColumn) {
											//nếu pos1 lớn hơn thì lùi giá trị của pos1
											pos1.positionColumn--;
										}
										else
										{
											//nếu pos2 lớn hơn thì lùi giá trị của pos2
											pos2.positionColumn--;
										}
										numberItemSymmetry = symmetryCheck->positionROrC1.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											//do pos1 lớn hơn nên so sánh pos1 trước
											if (symmetryCheck->positionROrC1.at(j).positionColumn > pos1.positionColumn) {
												symmetryCheck->positionROrC1.at(j).positionColumn--;
											}
											if (symmetryCheck->positionROrC1.at(j).positionColumn > pos2.positionColumn) {
												symmetryCheck->positionROrC1.at(j).positionColumn--;
											}
										}
										numberItemSymmetry = symmetryCheck->positionROrC2.size();
										for (int j = 0; j < numberItemSymmetry; j++) {
											if (symmetryCheck->positionROrC2.at(j).positionColumn > pos1.positionColumn) {
												symmetryCheck->positionROrC2.at(j).positionColumn--;
											}
											if (symmetryCheck->positionROrC2.at(j).positionColumn > pos2.positionColumn) {
												symmetryCheck->positionROrC2.at(j).positionColumn--;
											}
										}
									}
								}
								//tính toán lại các vertex gắn với các hàng hay cột này
								getVerticesFromRowOrColumn({ objectChoice,-1,positionObject },
									symmetryVertices.at(positionVerticesSymmetry).positionROrC1,
									symmetryVertices.at(positionVerticesSymmetry).positionVertices1,
									sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
									objectCustom0Array);
								getVerticesFromRowOrColumn({ objectChoice,-1,positionObject },
									symmetryVertices.at(positionVerticesSymmetry).positionROrC2,
									symmetryVertices.at(positionVerticesSymmetry).positionVertices2,
									sphereArray, cubeArray, coneArray, cylinderArray, emptyCylinderArray,
									objectCustom0Array);
							}
						}

						//nếu xóa thì xóa luôn tất cả phần tử trong positionChoiceRowOrColumn luôn
						positionChoiceRowOrColumn.clear();
					}
				}
			}
					  break;
			default: {
				
			}
					 break;
			}

		}
		myfile.close();


		//sau khi tính ra vertex và thêm chúng vào các vị trí cần thêm rồi thì tính lại normal vector
		switch (objectChoice)
		{
		case 4: {
			TriangleStripAttribute *triaStrip = triaStripArray.at(positionObject);
			CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
			if (positionObjectSymmetry != -1) {
				triaStrip = triaStripArray.at(positionObjectSymmetry);
				CaculatorNormalForTriangleStrip(triaStrip->vertexArray, triaStrip->normalVector);
			}
		}
				break;
		case 5: {
			TriangleFanAttribute *triaFan = triaFanArray.at(positionObject);
			CaculatorNormalForTriangleStrip(triaFan->vertexArray, triaFan->normalVector);
			if (positionObjectSymmetry != -1) {
				triaFan = triaFanArray.at(positionObjectSymmetry);
				CaculatorNormalForTriangleStrip(triaFan->vertexArray, triaFan->normalVector);
			}
		}
				break;
		case 10: {
			SphereAttribute *sphere = sphereArray.at(positionObject);
			CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
				sphere->vertexArray, sphere->normalVector);
			if (positionObjectSymmetry != -1) {
				sphere = sphereArray.at(positionObjectSymmetry);
				CaculatorNormalForSphere(sphere->numberLongitude, sphere->numberLatitude,
					sphere->vertexArray, sphere->normalVector);
			}
		}
				 break;
		case 11: {
			CubeAttribute *cube = cubeArray.at(positionObject);
			CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ,
				cube->vertexArray, cube->normalVector);
			if (positionObjectSymmetry != -1) {
				cube = cubeArray.at(positionObjectSymmetry);
				CaculatorNormalForCube(cube->numberVertexInAxisX, cube->numberVertexInAxisY, cube->numberVertexInAxisZ,
					cube->vertexArray, cube->normalVector);
			}
		}
				 break;
		case 12: {
			CubeRoundAttribute *cube = cubeRoundArray.at(positionObject);
			CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude,
				cube->vertexArray, cube->normalVector);
			if (positionObjectSymmetry != -1) {
				cube = cubeRoundArray.at(positionObjectSymmetry);
				CaculatorNormalForCubeRound(cube->numberLongitude, cube->numberLatitude,
					cube->vertexArray, cube->normalVector);
			}
		}
				 break;
		case 13: {
			ConeAttribute *cone = coneArray.at(positionObject);
			CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
				cone->vertexArray, cone->normalVector);
			if (positionObjectSymmetry != -1) {
				cone = coneArray.at(positionObjectSymmetry);
				CaculatorNormalForCone(cone->numberLongitude, cone->numberLatitude,
					cone->vertexArray, cone->normalVector);
			}
		}
				 break;
		case 14: {
			CylinderAttribute *cylinder = cylinderArray.at(positionObject);
			CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
			if (positionObjectSymmetry != -1) {
				cylinder = cylinderArray.at(positionObjectSymmetry);
				CaculatorNormalForCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
		}
				 break;
		case 16: {
			EmptyCylinderAttribute *cylinder = emptyCylinderArray.at(positionObject);
			CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
				cylinder->vertexArray, cylinder->normalVector);
			if (positionObjectSymmetry != -1) {
				cylinder = emptyCylinderArray.at(positionObjectSymmetry);
				CaculatorNormalForEmptyCylinder(cylinder->numberLongitude, cylinder->numberLatitude,
					cylinder->vertexArray, cylinder->normalVector);
			}
		}
				 break;
		case 19: {
			ObjectCustom0Attribute *object = objectCustom0Array.at(positionObject);
			CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
				object->vertexArray, object->normalVector);
			if (positionObjectSymmetry != -1) {
				object = objectCustom0Array.at(positionObjectSymmetry);
				CaculatorNormalForObjectCustom0(object->numberLongitude, object->numberLatitude,
					object->vertexArray, object->normalVector);
			}
		}
				 break;
		default:
			break;
		}
	}
	else cout << "Unable to open file";

}
//hàm lấy ra thông tin về các lần dịch chuyển trước để dịch chuyển lại
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
	vector<ObjectCustom0Attribute*> &objectCustom0Array) {

	string stringPath;

	//các biến lưu giá trị cho thuộc tính
	int whichEffect = -1, numberElement1, startOffset, offsetGetValue = 0;
	//mảng chứa 3 giá trị thay đổi cho 3 chiều x,y,z
	float valueChange[3];
	char charNumber[20];

	ifstream myfile(path);

	if (myfile.is_open())
	{
		while (getline(myfile, stringPath))
		{
			switch (stringPath[0])
			{
				//lấy ra kiểu chỉnh sửa
			case 'E': {
				//đặt kiểu chỉnh sửa
				charNumber[0] = stringPath[2];
				whichEffect = atoi(charNumber);
				//xóa các giá trị trong mảng để dùng lại lần sau
				memset(charNumber, 0, sizeof(charNumber));
			}
					  break;
			case 'V': {
				//3 giá trị cho 3 chiều x,y,z
				numberElement1 = stringPath.size();
				startOffset = 2;
				offsetGetValue = 0;
				for (int i = 2; i < numberElement1; i++) {
					if (stringPath[i] == ',' || stringPath[i] == ' ') {
						//chuyển chuỗi sang mảng char
						for (int j = startOffset; j < i; j++) {
							charNumber[j - startOffset] = stringPath[j];
						}

						//đặt giá trị vừa nhận được vào mảng chứa các thuộc tính cho 3 chiều x,y,z
						if (offsetGetValue == 0) {
							valueChange[0] = atof(charNumber);
						}
						else if (offsetGetValue == 1) {
							valueChange[1] = atof(charNumber);
						}
						else
						{
							valueChange[2] = atof(charNumber);
						}
						//xóa các giá trị trong mảng để dùng lại lần sau
						memset(charNumber, 0, sizeof(charNumber));

						//đặt lại các giá trị
						startOffset = i + 1;
						offsetGetValue++;
					}
				}
			}
					  break;
			default:
				break;
			}
		}

		//kiểm tra kiểu chỉnh sửa là gì đê áp dụng các biến đổi cho chính xác
		if (whichEffect == 0) {
			//nếu là dịch chuyển tiếp thì tăng lên,nếu không thì giảm giá trị đó
			if (isTurnUp) {
				//duy nhất đối với chế độ dịch chuyển và khi dịch chuyển tiến lên thì tệp.txt này lưu lại
				//giá trị sau khi biến đổi nên tâm của nó cần dịch chuyển ngược lại với giá trị biến đổi trước
				centerObjectOrVertices.x -= valueChange[0];
				centerObjectOrVertices.y -= valueChange[1];
				centerObjectOrVertices.z -= valueChange[2];
				centerObjectOrVerticesSymmetry.x -= valueChange[0];
				centerObjectOrVerticesSymmetry.y -= valueChange[1];
				centerObjectOrVerticesSymmetry.z -= valueChange[2];
				if (modelEditStyle == 0) {
					moveObject(valueChange[0], valueChange[1], valueChange[2],
						itemsChoice, centerObjectOrVertices,
						symmetryObjects,
						symmetry_translateX, symmetry_translateY, symmetry_translateZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					moveVertex(valueChange[0], valueChange[1], valueChange[2],
						centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
						symmetry_translateX, symmetry_translateY, symmetry_translateZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
			else
			{
				if (modelEditStyle == 0) {
					moveObject(-valueChange[0], -valueChange[1], -valueChange[2],
						itemsChoice, centerObjectOrVertices,
						symmetryObjects,
						symmetry_translateX, symmetry_translateY, symmetry_translateZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					moveVertex(-valueChange[0], -valueChange[1], -valueChange[2],
						centerObjectOrVertices, centerObjectOrVerticesSymmetry, itemsChoice, positionVerticesChoice,
						symmetry_translateX, symmetry_translateY, symmetry_translateZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
		}
		else if (whichEffect == 1) {
			//nếu là dịch chuyển tiếp thì tăng lên,nếu không thì giảm giá trị đó
			if (isTurnUp) {
				if (modelEditStyle == 0) {
					rotateObject(valueChange[0], valueChange[1], valueChange[2],
						itemsChoice,
						symmetryObjects,
						symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					rotateVertex(valueChange[0], valueChange[1], valueChange[2],
						itemsChoice, positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
						symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
			else
			{
				if (modelEditStyle == 0) {
					rotateObject(-valueChange[0], -valueChange[1], -valueChange[2],
						itemsChoice,
						symmetryObjects,
						symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					rotateVertex(-valueChange[0], -valueChange[1], -valueChange[2],
						itemsChoice, positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
						symmetry_rotateX, symmetry_rotateY, symmetry_rotateZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
		}
		else if (whichEffect == 2) {
			//nếu là dịch chuyển tiếp thì tăng lên,nếu không thì giảm giá trị đó
			if (isTurnUp) {
				if (modelEditStyle == 0) {
					scaleObject(1.0 + valueChange[0], 1.0 + valueChange[1], 1.0 + valueChange[2], itemsChoice,
						symmetryObjects,
						symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					scaleVertex(1.0 + valueChange[0], 1.0 + valueChange[1], 1.0 + valueChange[2],
						itemsChoice, positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
						symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
			else
			{
				valueChange[0] = 1 - (valueChange[0] / (valueChange[0] + 1.0));
				valueChange[1] = 1 - (valueChange[1] / (valueChange[1] + 1.0));
				valueChange[2] = 1 - (valueChange[2] / (valueChange[2] + 1.0));
				if (modelEditStyle == 0) {
					scaleObject(valueChange[0], valueChange[1], valueChange[2], itemsChoice,
						symmetryObjects,
						symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
				else
				{
					scaleVertex(valueChange[0], valueChange[1], valueChange[2],
						itemsChoice, positionVerticesChoice, centerObjectOrVertices, centerObjectOrVerticesSymmetry,
						symmetry_scaleX, symmetry_scaleY, symmetry_scaleZ,
						symmetryVertices, symmetryObjects,
						triangleArray, triaStripArray, triaFanArray, sphereArray, cubeArray, cubeRoundArray,
						coneArray, cylinderArray, pyrArray, emptyCylinderArray, torusArray, pictureArray, objectCustom0Array);
				}
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

