/ infotest1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>

using namespace std;

void main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	hf=FindFirstFile("c:\\*", &FindFileData);
	if (hf!=INVALID_HANDLE_VALUE)
	{
		do
		{
			cout << FindFileData.cFileName << endl;
		}
		while (FindNextFile(hf,&FindFileData)!=0);
		FindClose(hf);
	}
}
