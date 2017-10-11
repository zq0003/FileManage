//Edit by zq
//All right reserved
//zq0003@163.com
//Version 0.1t
//20170416
#if !defined(FileManage_CPP_H__ZQ0913__INCLUDED_)
#define	FileManage_CPP_H__ZQ0913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace ZQs_tools{
class CFileManage
{
public:
	CFileManage();
	~CFileManage();
	struct FileTypeInfo {
		char *pFileTypeSuffix;
		int HeaderByteNum;
		int TailerByteNum;
	}mFileTypeInfo;
	__int64 mFileLength;
	char GetFileLength(char * pFilePath);
	char GetFileType(char *pFilePath);
	char FileDivideInPartNum(char *pFilePath,__int64 PartNum);
	char FileDivideInPartLength(char *pFilePath, __int64 PartLength);
	char FileMerge(char *pFilePath);

protected:

private:
	__int64 mProcessBlockSize;
	const char *pmFilePartIndexp[100] =
	{ "000","001","002","003","004","005","006","007","008","009"
	,"010","011","012","013","014","015","016","017","018","019"
	,"020","021","022","023","024","025","026","027","028","029"
	,"030","031","032","033","034","035","036","037","038","039"
	,"040","041","042","043","044","045","046","047","048","049"
	,"050","051","052","053","054","055","056","057","058","059"
	,"060","061","062","063","064","065","066","067","068","069"
	,"070","071","072","073","074","075","076","077","078","079"
	,"080","081","082","083","084","085","086","087","088","089"
	,"090","091","092","093","094","095","096","097","098","099" };

};

}
#endif