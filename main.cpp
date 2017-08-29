#include <stdio.h>
#include <windows.h>
#include <iostream>

void ex1()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf = FindFirstFile(L"c:\\*", &FindFileData);
	if (hf != INVALID_HANDLE_VALUE){
		do{
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
				printf("%s\n", FindFileData.cFileName);

		} while (FindNextFile(hf, &FindFileData));
		FindClose(hf);
	}
}

namespace ex2
{

	long int rez = 0;

	void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT);

	int ex2(){

		//��������� sPath � sExt � sEXT ��������� �� ���� ������� GetFileList, �� ����� ���� �� �������
		//�����������, �� � ��� �������. 
		char sPath[MAX_PATH] = "C:";

		//��������  �������� �� ������ �������!
		char sExt[10] = "txt";
		char sEXT[10] = "TXT";
		GetFileList(sPath, sExt, sEXT);
		//������ �� ����: ���� �������������� � ���� � �������, �� �����������, ��� � ������ ����� 
		//������ ��� ������ ������- ���,������� ������ � ����,������� ���������� "��� ���������� ������� �����
		//�������" � ��� ������� ������������ � ������ � ������ �� ����
		printf("rez= %d\n", rez);
		system("PAUSE");
		return 0;
	}

	void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT) {

		WIN32_FIND_DATA pFILEDATA;

		HANDLE hFile = FindFirstFile(strcat(sPath, "\\*.*"), &pFILEDATA);

		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!���������� ������ ����� ����������� ����� ����!!!!!!!!!!!!!!!!!!!!!!!
		sPath[strlen(sPath) - strlen(strstr(sPath, "*.*"))] = '\0';
		//���� �������� ����� if (��� ���������� ���), �� �����, ���� ����� ���������� �� ��������� ����������
		// ��� ����, �� FindFirstFile ���������� -1. �������������, ��, ��� ����������� �� �������
		//(hFile!=INVALID_HANDLE_VALUE) �� ��������� � � ���������, �� ����� ��������� ����� ������!
		//� ��� ������, ��� �� ������ ��  ����������� ������� GetFileList � ��� �����, ��� �� ���������������
		//�����, ��� ����� ������������� �����������
		if (hFile != INVALID_HANDLE_VALUE)    {
			char * chBuf;
			//sPath[strlen(sPath) - strlen(strstr(sPath,"*.*"))] = '\0';
			do {
				//���������� . � ..
				if (strlen(pFILEDATA.cFileName) == 1 && strchr(pFILEDATA.cFileName, '.') != NULL)
				if (FindNextFile(hFile, &pFILEDATA) == 0)
					break;
				if (strlen(pFILEDATA.cFileName) == 2 && strstr(pFILEDATA.cFileName, "..") != NULL)
				if (FindNextFile(hFile, &pFILEDATA) == 0)
					break;
				//���� ����� ����������, ��������� ����� � ��� ����������� �����
				if (pFILEDATA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					GetFileList(strcat(sPath, pFILEDATA.cFileName), sExt, sEXT);

					//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!���������� �������������� ������ ����................................     
					sPath[strlen(sPath) - strlen(pFILEDATA.cFileName) - 1] = '\0';
				}
				else {
					//��������� �� ����������� sExt ���������� pFILEDATA.cFileName
					if ((chBuf = strrchr(pFILEDATA.cFileName, '.'))) {
						if (strstr(chBuf + 1, sExt) || strstr(chBuf + 1, sEXT)) {
							//���� �� ����� ������������ CharToOem() �� �� ������ ������� ����� ���������� ������
							CharToOem(sPath, sPath);
							printf("%s", sPath);
							OemToChar(sPath, sPath);
							CharToOem(pFILEDATA.cFileName, pFILEDATA.cFileName);
							printf("%s\n", pFILEDATA.cFileName);
							rez++;
							FILE *out = fopen("booklist.txt", "a");
							fprintf(out, "%s\%s\n", sPath, pFILEDATA.cFileName);
						}
					}
				}
			} while (FindNextFile(hFile, &pFILEDATA));
		}
	}
}
using namespace std;
void ex3()
{
		WIN32_FIND_DATA FindFileData;
		HANDLE hf;
		hf = FindFirstFile(L"c:\\*", &FindFileData);
		if (hf != INVALID_HANDLE_VALUE)
		{
			do
			{
				cout << FindFileData.cFileName << endl;
			} while (FindNextFile(hf, &FindFileData) != 0);
			FindClose(hf);
		}
	}

