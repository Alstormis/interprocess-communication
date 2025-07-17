#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>

#define INVALID_HANDLE_VALUE (( HANDLE )( LONG_PTR )- 1 )


using namespace std;

    CHAR lpFileShareName[] = "$info_time$";
	HANDLE hFileMapping;
	LPVOID lpFileMap;
	
	CHAR lpFileShareName3[] = "$info_time_3$";
	HANDLE hFileMapping3;
	LPVOID lpFileMap3;

int main()
{
    setlocale(LC_ALL, "Russian");
    DWORD GetLastError();
    
    char MappingName[] = "MappingName";
    
    HANDLE hMapping;
	
	hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE,
  		NULL, PAGE_READWRITE, 0, 100, lpFileShareName);
	if(hFileMapping == NULL){
		cout<<"CreateFileMapping: Error \n";
		return 0;
	}

	lpFileMap = MapViewOfFile(hFileMapping, 
	  FILE_MAP_WRITE, 0, 0, 0);
	if(lpFileMap == 0){
		cout<<"MapViewOfFile: Error \n";
		return 0;
	}

    // первый процесс
    HANDLE myFile = CreateFile("lr6.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
    printf("Дискриптор файла = %d", myFile);
    
    DWORD myFileSize = GetFileSize(myFile, NULL);
    printf("\nРазмер файла = %d", myFileSize);

    HANDLE myFileMapping = CreateFileMapping(myFile, NULL, PAGE_READWRITE, 0, 0, MappingName);
    printf("\nДискриптор файлового отображения  = %d\n", myFileMapping);
    
    char lpszAppName[] = "SecondaryProcess.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    //Запускаем процесс
    if(!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
    {
    	cout<<"\n" << "Не удалось создать новый процесс" << endl;
    	return GetLastError();
	};
	
	
	// второй процесс
	
	hFileMapping3 = CreateFileMapping(INVALID_HANDLE_VALUE,
	NULL, PAGE_READWRITE, 0, 100, lpFileShareName3);
	if(hFileMapping3 == NULL){
		cout<<"CreateFileMapping: Error \n";
		return 0;
	}

	lpFileMap3 = MapViewOfFile(hFileMapping3, 
	  FILE_MAP_WRITE, 0, 0, 0);
	if(lpFileMap3 == 0){
		cout<<"MapViewOfFile: Error \n";
		return 0;
	}
    
    char lpszAppName3[] = "ThirdProcess.exe";
    STARTUPINFO si3;
    PROCESS_INFORMATION piApp3;
    ZeroMemory(&si3, sizeof(STARTUPINFO));
    si3.cb = sizeof(STARTUPINFO);
    //Запускаем процесс
    if(!CreateProcess(lpszAppName3, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si3, &piApp3))
    {
    	cout<<"\n" << "Не удалось создать новый процесс" << endl;
    	return GetLastError();
	};
	// Ждем завершение второго процесса
	WaitForSingleObject(piApp3.hProcess, INFINITE);
	// Ждем завершение первого процесса
	WaitForSingleObject(piApp.hProcess, INFINITE);


	cout<<"\nВремя работы первого процесса: "<<*((wchar_t *)lpFileMap)<<"\n";
	cout<<"\nВремя работы второго процесса: "<<*((wchar_t *)lpFileMap3)<<"\n";
	
	UnmapViewOfFile(lpFileMap);


    CloseHandle(hFileMapping);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	
	LPVOID myFileMapView = MapViewOfFile(myFileMapping, FILE_MAP_WRITE, 0, 0, 0);

	if(!UnmapViewOfFile(myFileMapView))
	    cout<<"\n"<<"Ошибка: не удалось освободить отобраение!"<<"\n";
	else 
	    cout<<"\n"<<"Отображенние успешно освобождено."<<"\n";
	
	if(!CloseHandle(myFileMapping))
	    cout<<"Ошибка: не удалось закрыть файловое отоброжение!"<<"\n";
	else 
	    cout<<"Файловое отобрадение успешно закрыто."<<"\n";
	
	if(!CloseHandle(myFile))
	    cout<<"Ошибка: не удалось закрыть файл!"<<"\n";
	else 
	    cout<<"Файл успешно закрыт."<<"\n";
	

	UnmapViewOfFile(lpFileMap3);
    CloseHandle(hFileMapping3);
	CloseHandle(piApp3.hThread);
	CloseHandle(piApp3.hProcess);


	return 0;

	
}
