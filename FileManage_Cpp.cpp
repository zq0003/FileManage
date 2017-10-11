//Edit by zq
//All right reserved
//zq0003@163.com
//Version 0.1t
//20170416
#include "stdafx.h"
//#include "afx.h"
#include <iostream>
#include <fstream>
#include "MemAllot_Cpp.h"
#include "FileManage_Cpp.h"
//#include "stdlib.h"

using namespace std;
namespace ZQs_tools{
CFileManage::CFileManage()
{
	mProcessBlockSize = 100000000;// ~=100M
}
CFileManage::~CFileManage()
{
}	
//======================================================================
//    Function: GetFileLength
//    in: 
//        char * pFilePath
//    out:
//    return: 
//        0x00 success
//        0x01 file open failed
//======================================================================
char CFileManage::GetFileLength(char *pFilePath) 
{
	ifstream o_InF;
	string o_s(pFilePath);
	o_InF.open(pFilePath, ios::in | ios::binary);
	if (!o_InF.is_open()) {
		cout << "Error: open" << pFilePath << " failed.\n";
		return 0x01;
	}
	o_InF.seekg(0, ios::end);
	mFileLength = (__int64)o_InF.tellg();
	o_InF.close();
	return 0x00;
}
//======================================================================
//    Function: GetFileType
//    in: 
//        char * pFilePath
//    out:
//    return: 
//        0x00 success
//        0x01 file open failed
//======================================================================
char CFileManage::GetFileType(char *pFilePath)
{
	int i;
	ifstream o_InF;
	string o_s(pFilePath);
	o_InF.open(pFilePath, ios::in | ios::binary);
	if (!o_InF.is_open()) {
		cout << "Error: open" << pFilePath << " failed.\n";
		return 0x01;
	}
	i=o_s.rfind(".", o_s.length());//get the begin position of the type suffix 
	mFileTypeInfo.pFileTypeSuffix = pFilePath + i;//make pointer point to the begin position of the type suffix
	o_s.assign((const char *)mFileTypeInfo.pFileTypeSuffix);
	i = o_s.length();
	mFileTypeInfo.HeaderByteNum = 0;
	mFileTypeInfo.TailerByteNum = 0;
	if(i==3){
		if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".rm")) {
			mFileTypeInfo.HeaderByteNum = 4;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".et")) {
			mFileTypeInfo.HeaderByteNum = 516;
			mFileTypeInfo.TailerByteNum = 16;
		}
	}
	else if(i==4) {
		if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".txt")) {
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".doc")) {
			mFileTypeInfo.HeaderByteNum = 512;
			mFileTypeInfo.TailerByteNum = 48;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".xls")) {
			mFileTypeInfo.HeaderByteNum = 512;
			mFileTypeInfo.TailerByteNum = 8;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".wps")) {
			mFileTypeInfo.HeaderByteNum = 528;
			mFileTypeInfo.TailerByteNum = 8;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".pdf") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".rar")) {
			mFileTypeInfo.HeaderByteNum = 7;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".zip")) {
			mFileTypeInfo.HeaderByteNum = 7;
			mFileTypeInfo.TailerByteNum = 2;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".avi") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".dwg") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".mid") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".mov") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".mpg") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".psd") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".pst") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".pwl") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".qdf") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".ram") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".tif") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".wav") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".wpd")
			) {
			mFileTypeInfo.HeaderByteNum = 4;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".bmp")) {
			mFileTypeInfo.HeaderByteNum = 2;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".gif")) {
			mFileTypeInfo.HeaderByteNum = 4;
			mFileTypeInfo.TailerByteNum = 2;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".jpe")\
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".jpg")) {
			mFileTypeInfo.HeaderByteNum = 3;
			mFileTypeInfo.TailerByteNum = 2;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".png")) {
			mFileTypeInfo.HeaderByteNum = 4;
			mFileTypeInfo.TailerByteNum = 4;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".asf") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".dbx")) {
			mFileTypeInfo.HeaderByteNum = 8;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".eml")) {
			mFileTypeInfo.HeaderByteNum = 14;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".mdb")) {
			mFileTypeInfo.HeaderByteNum = 10;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".rtf") \
			|| !strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".xml")) {
			mFileTypeInfo.HeaderByteNum = 5;
		}
		else {};
	}
	else if(i==5){
		if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".docx")) {
			mFileTypeInfo.HeaderByteNum = 437;
			mFileTypeInfo.TailerByteNum = 4;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".xlsx")) {
			mFileTypeInfo.HeaderByteNum = 48;
			mFileTypeInfo.TailerByteNum = 4;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".html")) {
			mFileTypeInfo.HeaderByteNum = 5;
		}
		else if (!strcmp((const char *)mFileTypeInfo.pFileTypeSuffix, ".jpeg")) {
			mFileTypeInfo.HeaderByteNum = 3;
			mFileTypeInfo.TailerByteNum = 2;
		}
		else {};
	}
	else {};
	o_InF.close();
	return 0x00;
}
//=================================================================
//	Function: FileDivideInPartNum
//		Divide file into Num Parts.
//	in: 
//		char *pFilePath
//		__int64 PartNum
//	out:
//	return:
//		0x00 success
//		0x01 error file open failed
//      0x02 error PartNum <=1
//=====================================================================
char CFileManage::FileDivideInPartNum(char *pInFilePath, __int64 PartNum) 
{
	__int64 i, j, k;
	__int64 FilePartLen, FileTailPartLen;
	__int64 BloNum1, TailBloLen1, BloNum2, TailBloLen2, FileNameStrLen;
	ifstream o_InF;
	ofstream o_OutF;
	string o_s(pInFilePath);
	char *pOutFilePath,*pBuf;

	if (PartNum <= 1) { return 0x02; }//error PartNum <=1
	if (PartNum > 100) { PartNum = 100; };//now 100 is the max support divide part number

	//---------------open file---------------------
	o_InF.open(pInFilePath, ios::in | ios::binary);
	if (!o_InF.is_open()) {
		cout << "Error: open" << pInFilePath << " failed.\n";
		return 0x01;
	}
	//------------------------------------------

	//-------get file length-----------------
	o_InF.seekg(0, ios::end);
	mFileLength = (__int64)o_InF.tellg();
	o_InF.seekg(0, ios::beg);
	//----------------------------------------

	//---------get FilePartLen,FileTailPartLen---------------------
	for (i = 0;i < PartNum;i++) {
		if ((__int64)(mFileLength+i)%(__int64)PartNum == 0) {
			FilePartLen = (__int64)(mFileLength + i) / (__int64)PartNum;
			if (i == 0) { FileTailPartLen = FilePartLen; }
			else { FileTailPartLen = (__int64)(FilePartLen - i); }
			break;
		}
	}
	//-------------------------------------------------------------

	//----------get BloNum,TailBloLen---------------------------
	BloNum1 = (FilePartLen -1) / mProcessBlockSize;
	TailBloLen1 = FilePartLen%mProcessBlockSize;
	if (TailBloLen1 == 0) {
		TailBloLen1 = mProcessBlockSize;
	}
	BloNum2 = (FileTailPartLen - 1) / mProcessBlockSize;
	TailBloLen2 = FileTailPartLen%mProcessBlockSize;
	if (TailBloLen2 == 0) {
		TailBloLen2 = mProcessBlockSize;
	}
	//------------------------------------------------------

	//MemAllot_New_1D(pBuf, mProcessBlockSize, char);
	pBuf = new char[mProcessBlockSize];
	k = o_s.rfind(".", o_s.length());
	FileNameStrLen = o_s.length();
	for (i = 0;i < PartNum - 1; i++) {
		if (i > 0) {
			if (k >= 0) { o_s.erase(k, 3); }//find "."
			else { o_s.erase(FileNameStrLen, 3); }
		}
		if (k >= 0) { o_s.insert(k, pmFilePartIndexp[i]); }//name the part file
		else { o_s.append(pmFilePartIndexp[i]); }
		pOutFilePath = (char *)o_s.c_str();
		o_OutF.open(pOutFilePath, ios::out | ios::binary);
		for (j = 0;j < BloNum1;j++) {
			o_InF.read(pBuf, mProcessBlockSize);
			o_OutF.write(pBuf, mProcessBlockSize);
		}
		o_InF.read(pBuf, TailBloLen1);
		o_OutF.write(pBuf, TailBloLen1);
		o_OutF.close();
	}

	//-------------last Part File--------------------------------------------- 
	if (k >= 0) {
		o_s.erase(k, 3);
		o_s.insert(k, pmFilePartIndexp[i]);
	}
	else {
		o_s.erase(FileNameStrLen, 3);
		o_s.append(pmFilePartIndexp[i]);
	}
	pOutFilePath = (char *)o_s.c_str();
	o_OutF.open(pOutFilePath, ios::out | ios::binary);
	for (j = 0;j < BloNum2;j++) {
		o_InF.read(pBuf, mProcessBlockSize);
		o_OutF.write(pBuf, mProcessBlockSize);
	}
	o_InF.read(pBuf, TailBloLen2);
	o_OutF.write(pBuf, TailBloLen2);
	o_OutF.close();
	//---------------------------------------------------------------------
	
	o_InF.close();
	MemAllot_Del_1D(pBuf)
	return 0x00;
}
//=================================================================
//	Function: FileDivideInPartLength
//		Divide file into files which the biggest one length is PartLenInMB.
//	in: 
//		char *pFilePath
//		__int64 PartLenInMB: File length in M Bytes
//	out:
//	return:
//		0x00 success
//		0x01 error file open failed
//      0x02 error PartLenInMB <=1, now the smallest part file support is >1M Bytes
//		0x03 error PartLenInMB >= FileLength, No need to divide
//=====================================================================
char CFileManage::FileDivideInPartLength(char *pInFilePath, __int64 PartLenInMB)
{
	__int64 i, j, k, PartNum;
	__int64 FilePartLen, FileTailPartLen;
	__int64 BloNum1, TailBloLen1, BloNum2, TailBloLen2;
	__int64 FileNameStrLen;
	ifstream o_InF;
	ofstream o_OutF;
	string o_s(pInFilePath);
	char *pOutFilePath, *pBuf;
	//MemAllot_New_1D(pBuf,mProcessBlockSize,char)
	pBuf = new char[mProcessBlockSize];

	if (PartLenInMB <= 1) { 
		cout << "Error: For now, only support file large than 1MB.\n";
		return 0x02; }//error PartLenInMB <=1

	//--------------open file----------------------------------
	o_InF.open(pInFilePath, ios::in | ios::binary);
	if (!o_InF.is_open()) {
		cout << "Error: open" << pInFilePath << " failed.\n";
		return 0x01;//error open failed
	}
	//---------------------------------------------------------

	//------------------get file length--------------------------
	o_InF.seekg(0, ios::end);
	mFileLength = (__int64)o_InF.tellg();
	o_InF.seekg(0, ios::beg);
	if ((__int64)PartLenInMB >= (__int64)mFileLength/ (__int64)1048576) {
		o_InF.close();
		cout << "Error: No need to divide.\n";
		return 0x03;//error PartLenInMB >= FileLength, no need to divide 
	}
	//------------------------------------------------------------

	//-----------get PartNum,FileTailPartLen---------------------------
	FilePartLen = (__int64)PartLenInMB*(__int64)1048576;
	PartNum= (mFileLength - 1) / FilePartLen;
	FileTailPartLen = mFileLength%FilePartLen;
	if (FileTailPartLen == 0) {
		FileTailPartLen = FilePartLen;
	}
	//-----------------------------------------------------------

	//------------get BloNum,TailBloLen-----------------------
	BloNum1 = (FilePartLen - 1) / mProcessBlockSize;
	TailBloLen1 = FilePartLen%mProcessBlockSize;
	if (TailBloLen1 == 0) {
		TailBloLen1 = mProcessBlockSize;
	}
	BloNum2 = (FileTailPartLen - 1) / mProcessBlockSize;
	TailBloLen2 = FileTailPartLen%mProcessBlockSize;
	if (TailBloLen2 == 0) {
		TailBloLen2 = mProcessBlockSize;
	}
	//------------------------------------------------------

	FileNameStrLen = o_s.length();
	k = o_s.rfind(".", FileNameStrLen);
	for (i = 0;i < PartNum ; i++) {
		if (i > 0) {
			if (k >= 0) { o_s.erase(k, 3); }//find "."
			else { o_s.erase(FileNameStrLen, 3); }//hadnt find "."
		}
		if (k >= 0) { o_s.insert(k, pmFilePartIndexp[i]); }//name the part file
		else { o_s.append(pmFilePartIndexp[i]); }
		pOutFilePath = (char *)o_s.c_str();
		o_OutF.open(pOutFilePath, ios::out | ios::binary);
		for (j = 0;j < BloNum1;j++) {
			o_InF.read(pBuf, mProcessBlockSize);
			o_OutF.write(pBuf, mProcessBlockSize);
		}
		o_InF.read(pBuf, TailBloLen1);
		o_OutF.write(pBuf, TailBloLen1);
		o_OutF.close();
	}
	if (k >= 0) { 
		o_s.erase(k, 3);
		o_s.insert(k, pmFilePartIndexp[i]); 
	}
	else {
		o_s.erase(FileNameStrLen, 3);
		o_s.append(pmFilePartIndexp[i]); 
	}
	pOutFilePath = (char *)o_s.c_str();
	o_OutF.open(pOutFilePath, ios::out | ios::binary);
	for (j = 0;j < BloNum2;j++) {
		o_InF.read(pBuf, mProcessBlockSize);
		o_OutF.write(pBuf, mProcessBlockSize);
	}
	o_InF.read(pBuf, TailBloLen2);
	o_OutF.write(pBuf, TailBloLen2);
	o_OutF.close();
	
	o_InF.close();
	MemAllot_Del_1D(pBuf)
	return 0x00;
}
//===================================================================
//	Function: FileMerge
//	in:
//		char *pInFilePath
//	out:
//	return:
//		0x00 success
//		0x01 error file open failed
//		0x02 error FileNameStrLen<=3
//		0x03 error File Part Num > 100
//===========================================================
char CFileManage::FileMerge(char *pInFilePath) 
{
	__int64 i, j, k, FileNameStrLen;
	__int64 BloNum, TailBloLen;
	ifstream o_InF;
	ofstream o_OutF;
	string o_s(pInFilePath);
	char *pOutFilePath, *pBuf;
	//MemAllot_New_1D(pBuf,mProcessBlockSize,char)
	pBuf = new char[mProcessBlockSize];

	FileNameStrLen = o_s.length();
	k = o_s.rfind(".", FileNameStrLen);
	if (k > 3) { o_s.erase(k - 3, 3);}//find "."
	else if(FileNameStrLen > 3) { o_s.erase(FileNameStrLen - 3, 3);}//Didnt find "."
	else {
		return 0x02;//error: FileNameStrLen<=3
	}
	pOutFilePath=(char *)o_s.c_str();
	o_OutF.open(pOutFilePath, ios::out | ios::binary);
	FileNameStrLen -= 3;
	k -= 3;

	for (i = 0; i<100; i++) {//now the max part support is 100
		if (i > 0) {
			if (k > 0) { o_s.erase(k, 3); }//find "."
			else { o_s.erase(FileNameStrLen, 3); }
		}
		if (k > 0) {o_s.insert(k, pmFilePartIndexp[i]); }//name the part file
		else { o_s.append(pmFilePartIndexp[i]); }
		pInFilePath = (char *)o_s.c_str();
		o_InF.open(pInFilePath, ios::in | ios::binary);
		if (!o_InF.is_open()) {
			if (i == 0) {
				cout << "Error: open" << pInFilePath << " failed.\n";
				return 0x01;//error open failed
			}
			else {
				o_OutF.close();
				return 0x00;
			}
		}
		o_InF.seekg(0, ios::end);
		mFileLength = (__int64)o_InF.tellg();
		o_InF.seekg(0, ios::beg);

		//----------------------------------------------------
		//	caculate BloNum,TailBlo
		BloNum = (mFileLength - 1) / mProcessBlockSize;
		TailBloLen = mFileLength%mProcessBlockSize;
		if (TailBloLen == 0) {
			TailBloLen = mProcessBlockSize;
		}
		//------------------------------------------------------
		for (j = 0;j < BloNum;j++) {
			o_InF.read(pBuf, mProcessBlockSize);
			o_OutF.write(pBuf, mProcessBlockSize);
		}
		o_InF.read(pBuf, TailBloLen);
		o_OutF.write(pBuf, TailBloLen);
		o_InF.close();
	}
	o_OutF.close();
	return 0x03;//error File Part Num > 100
}

}
