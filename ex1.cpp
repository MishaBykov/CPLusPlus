#include <stdio.h>
#include <windows.h>
 
int main(){
        WIN32_FIND_DATA FindFileData;
        HANDLE hf = FindFirstFile("c:\\*",&FindFileData);
        if(hf != INVALID_HANDLE_VALUE){
                do{
                    if(FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
                        printf("%s\n",FindFileData.cFileName);
 
                }
                while(FindNextFile(hf,&FindFileData));
                FindClose(hf);
        }
        return 0;
}
