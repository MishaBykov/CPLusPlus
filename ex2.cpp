#include <windows.h>
#include <stdio.h>

long int rez = 0;

void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT);

int main(){

	//Поскольку sPath и sExt и sEXT одинаковы во всех вызовах GetFileList, их можно было бы сделать
	//глобальными, но я так оставил. 
	char sPath[MAX_PATH] = "C:";

	//Обратить  внимание на размер массива!
	char sExt[10] = "txt";
	char sEXT[10] = "TXT";
	GetFileList(sPath, sExt, sEXT);
	//Портит всё дело: Если перенаправлять в файл с консоли, то полуачается, что в консол ведут 
	//запись два разных потока- тот,который нужент и этот,который записывает "Для продлжения нажмите любую
	//клавишу" и эта надпись вклинивается в серёдку и портит всё дело
	printf("rez= %d\n", rez);
	system("PAUSE");
}

void GetFileList(LPTSTR sPath, LPTSTR sExt, LPTSTR sEXT) {

	WIN32_FIND_DATA pFILEDATA;

	HANDLE hFile = FindFirstFile(strcat(sPath, "\\*.*"), &pFILEDATA);

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!Необходимо именно здесь прописывать длину пути!!!!!!!!!!!!!!!!!!!!!!!
	sPath[strlen(sPath) - strlen(strstr(sPath, "*.*"))] = '\0';
	//Если пропишем после if (как предлагает Юра), то тогда, если вдруг натыкаемся на системную директорию
	// или файл, то FindFirstFile возвращает -1. Следовательно, всё, что выплнняется по условию
	//(hFile!=INVALID_HANDLE_VALUE) не выолнится и в частности, не будет поставлен конец строки!
	//А это значит, что по выходу из  рекурсивной функции GetFileList в том месте, где мы восстанавливаем
	//Длину, она будет восстановлена неправильно
	if (hFile != INVALID_HANDLE_VALUE)    {
		char * chBuf;
		//sPath[strlen(sPath) - strlen(strstr(sPath,"*.*"))] = '\0';
		do {
			//Пропускаем . и ..
			if (strlen(pFILEDATA.cFileName) == 1 && strchr(pFILEDATA.cFileName, '.') != NULL)
			if (FindNextFile(hFile, &pFILEDATA) == 0)
				break;
			if (strlen(pFILEDATA.cFileName) == 2 && strstr(pFILEDATA.cFileName, "..") != NULL)
			if (FindNextFile(hFile, &pFILEDATA) == 0)
				break;
			//Если нашли директорию, запускаем поиск в ней рекурсивный поиск
			if (pFILEDATA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				GetFileList(strcat(sPath, pFILEDATA.cFileName), sExt, sEXT);

				//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!оБЯЗАТЕЛЬН востанавливать дллину пути................................     
				sPath[strlen(sPath) - strlen(pFILEDATA.cFileName) - 1] = '\0';
			}
			else {
				//Проверяем на соотвествие sExt расширения pFILEDATA.cFileName
				if ((chBuf = strrchr(pFILEDATA.cFileName, '.'))) {
					if (strstr(chBuf + 1, sExt) || strstr(chBuf + 1, sEXT)) {
						//Если не будем использовать CharToOem() то на экране русский шрифт каракулями выйдет
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