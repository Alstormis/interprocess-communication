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

    // ������ �������
    HANDLE myFile = CreateFile("lr6.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, 0);
    printf("���������� ����� = %d", myFile);
    
    DWORD myFileSize = GetFileSize(myFile, NULL);
    printf("\n������ ����� = %d", myFileSize);

    HANDLE myFileMapping = CreateFileMapping(myFile, NULL, PAGE_READWRITE, 0, 0, MappingName);
    printf("\n���������� ��������� �����������  = %d\n", myFileMapping);
    
    char lpszAppName[] = "SecondaryProcess.exe";
    STARTUPINFO si;
    PROCESS_INFORMATION piApp;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    //��������� �������
    if(!CreateProcess(lpszAppName, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
    {
    	cout<<"\n" << "�� ������� ������� ����� �������" << endl;
    	return GetLastError();
	};
	
	
	// ������ �������
	
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
    //��������� �������
    if(!CreateProcess(lpszAppName3, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si3, &piApp3))
    {
    	cout<<"\n" << "�� ������� ������� ����� �������" << endl;
    	return GetLastError();
	};
	// ���� ���������� ������� ��������
	WaitForSingleObject(piApp3.hProcess, INFINITE);
	// ���� ���������� ������� ��������
	WaitForSingleObject(piApp.hProcess, INFINITE);


	cout<<"\n����� ������ ������� ��������: "<<*((wchar_t *)lpFileMap)<<"\n";
	cout<<"\n����� ������ ������� ��������: "<<*((wchar_t *)lpFileMap3)<<"\n";
	
	UnmapViewOfFile(lpFileMap);


    CloseHandle(hFileMapping);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);
	
	LPVOID myFileMapView = MapViewOfFile(myFileMapping, FILE_MAP_WRITE, 0, 0, 0);

	if(!UnmapViewOfFile(myFileMapView))
	    cout<<"\n"<<"������: �� ������� ���������� ����������!"<<"\n";
	else 
	    cout<<"\n"<<"������������ ������� �����������."<<"\n";
	
	if(!CloseHandle(myFileMapping))
	    cout<<"������: �� ������� ������� �������� �����������!"<<"\n";
	else 
	    cout<<"�������� ����������� ������� �������."<<"\n";
	
	if(!CloseHandle(myFile))
	    cout<<"������: �� ������� ������� ����!"<<"\n";
	else 
	    cout<<"���� ������� ������."<<"\n";
	

	UnmapViewOfFile(lpFileMap3);
    CloseHandle(hFileMapping3);
	CloseHandle(piApp3.hThread);
	CloseHandle(piApp3.hProcess);


	return 0;

	
}
