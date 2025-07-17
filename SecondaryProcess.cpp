#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include <conio.h>
#include <cmath>


using namespace std;


	CHAR lpFileShareName[] = 
     	"$info_time$";
	HANDLE hFileMapping;
	LPVOID lpFileMap;

double f(double x)
{
	return 1/(1+pow(x,4))-pow(x,2);
}


void onemetod(double a,double b)
{
double eps = 0.00001, c;
int iter = 0;
if (f(b)*f(a)<0)
{
    while (1)
    {
	c = (a+b)/2;
	iter++;	
    if (abs(f(c))>eps){
	    if (f(a)*f(c)<0) 
		{
		    b = c;
		}
		else
    	{
		    a = c;
	    }
	    cout<<"Первый метод: x = "<< c<<"\n";
    }
	else break;	
}
cout<<"\n"<<"Первый метод: кол-во итераций = "<< iter<<"\n"<<"\n";
}
else cout<<"Нечего вычислять "<<"\n";
return;
}

int main()
{
	
    setlocale(LC_ALL, "Russian");
    
#pragma warning(disable : 4996)
	char MappingName[] = "MappingName";
	HANDLE hMapping;
	DWORD Change = 0x9FF5E924;
	int *ptr;
	cout<< "В теле процесса - SecondaryProcess.exe" <<endl;
	hMapping = OpenFileMapping(
	FILE_MAP_ALL_ACCESS,
	TRUE,
	MappingName
	);
	if(!hMapping)
	{
		cerr << "Не удалось открыть файловое отображение \n" << endl;
		return GetLastError();
	}
	else
	{
		cout<<"Успешно открыли файловое отображение \n" << endl;
	}
	// Узнаем размер файла
	LONGLONG nFileLen = 0;
	WIN32_FILE_ATTRIBUTE_DATA fData;
	int res = GetFileAttributesEx("lr6.txt", GetFileExInfoStandard, &fData);
	if(res)
		nFileLen = (fData.nFileSizeHigh * (MAXDWORD + 1)) + fData.nFileSizeLow;
	
	LPVOID myFileMapView = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);
	char *myFileMemory = new char[nFileLen];
	
	CopyMemory(myFileMemory, myFileMapView, nFileLen); 
	
	double t1 = -0.9, t2 = -0.8;
	onemetod(t1,t2);
	sleep(4);
	
	CopyMemory(myFileMapView, myFileMemory, nFileLen); 

	

	hFileMapping = OpenFileMapping(
    FILE_MAP_READ | FILE_MAP_WRITE, FALSE, lpFileShareName);


  if(hFileMapping == NULL)
  {
    cout<<"OpenFileMapping: Error \n";
	return 0;
  }

  lpFileMap = MapViewOfFile(hFileMapping, 
    FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);


  if(lpFileMap == 0)
  {
    cout<<"MapViewOfFile: Error \n";
	return 0;
  }

	int chr = clock()/1000;
    *((wchar_t *)lpFileMap) = chr;	                            
    cout<<"\n"<<"Время работы : "<< chr << "\n";                   

	UnmapViewOfFile(lpFileMap);
    CloseHandle(hFileMapping);			 
                  	
	system("pause");
	return 0;
}
