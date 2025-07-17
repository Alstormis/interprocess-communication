#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>
#include <conio.h>


using namespace std;


	CHAR lpFileShareName3[] = 
     	"$info_time_3$";
	HANDLE hFileMapping3;
	LPVOID lpFileMap3;

int main()
{
	
    setlocale(LC_ALL, "Russian");
    
#pragma warning(disable : 4996)
	char MappingName[] = "MappingName";
	HANDLE hMapping;
	int *ptr;
	cout<< "В теле процесса - ThirdProcess.exe" <<endl;

	
	int row1, row2, col1, col2;
	  double** a, ** b, ** c;
	  system("chcp 1251");
	  system("cls");
	  cout << "Введите количество строк первой матрицы: ";
	  cin >> row1;
	  cout << "Введиет количество столбцов первой матрицы: ";
	  cin >> col1;
	  cout << "Введите количество строк второй матрицы:  ";
	  cin >> row2;
	  cout << "Введиет количество столбцов второй матрицы: ";
	  cin >> col2;
	  if (col1 != row2)
	  {
	    cout << "Умножение невозможно!";
	    cin.get(); cin.get();
	  }
	  else{
	  
	  a = new double* [row1];
	  cout << "Введите элементы первой матрицы" << endl;
	  for (int i = 0; i < row1; i++)
	  {
	    a[i] = new double[col1];
	    for (int j = 0; j < col1; j++)
	    {
	      cout << "a[" << i << "][" << j << "]= ";
	      cin >> a[i][j];
	    }
	  }
	
	  for (int i = 0; i < row1; i++)
	  {
	    for (int j = 0; j < col1; j++)
	      cout << a[i][j] << " ";
	    cout << endl;
	  }
	
	  b = new double* [row2];
	  cout << "Введите элементы второй матрицы" << endl;
	  for (int i = 0; i < row2; i++)
	  {
	    b[i] = new double[col2];
	    for (int j = 0; j < col2; j++)
	    {
	      cout << "b[" << i << "][" << j << "]= ";
	      cin >> b[i][j];
	    }
	  }
	
	  for (int i = 0; i < row2; i++)
	  {
	    for (int j = 0; j < col2; j++)
	    {
	      cout << b[i][j] << " ";
	    }
	    cout << endl;
	  }
	
	  c = new double* [row1];
	  for (int i = 0; i < row1; i++)
	  {
	    c[i] = new double[col2];
	    for (int j = 0; j < col2; j++)
	    {
	      c[i][j] = 0;
	      for (int k = 0; k < col1; k++)
	        c[i][j] += a[i][k] * b[k][j];
	    }
	  }
	
	  cout << "Матрица произведение" << endl;
	  for (int i = 0; i < row1; i++)
	  {
	    for (int j = 0; j < col2; j++)
	      cout << c[i][j] << " ";
	    cout << endl;
	  }
	  cin.get(); cin.get();
	  }
  
	hFileMapping3 = OpenFileMapping(
	FILE_MAP_READ | FILE_MAP_WRITE, FALSE, lpFileShareName3);
	
	
	  if(hFileMapping3 == NULL)
	  {
	    cout<<"OpenFileMapping: Error \n";
		return 0;
	  }
	
	  lpFileMap3 = MapViewOfFile(hFileMapping3, 
	    FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	
	
	  if(lpFileMap3 == 0)
	  {
	    cout<<"MapViewOfFile: Error \n";
		return 0;
	  }
	
	
	int chr = clock()/1000;
	*((wchar_t *)lpFileMap3) = chr;	                            
	cout<<"\n"<<"Время работы : "<< chr << "\n";              
	
	
	UnmapViewOfFile(lpFileMap3);
	CloseHandle(hFileMapping3);			 
				                	
	system("pause");
	return 0;
}
