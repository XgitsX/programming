// 1.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void write_file(int n); //�������� ����� �� n ���������� �������
void sort(int *a, int n); //���������� ���������

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	write_file(10); //- ������� ���� � 10 ���������� �������

	int k;
	cout << "k = ";
	cin >> k;

	ifstream file;
	int out, n = 0;
	file.open("file.txt", ios::in);
	if(!file){
		cout << "����� �� ����������.\n";
		return 0;
	}

	int *a = NULL;
	while (!file.eof()) {
		file >> out; //���� �� �����
		if(out > k){
			a = (int *)realloc(a, sizeof(int) * (n+1));
			a[n] = out;
			n++;
		}
	}

	file.close();

	//����� �������.
	for(int i=0; i<n; i++)cout << a[i] << " ";
	sort(a, n);
	cout << "\n";
	for(int i=0; i<n; i++)cout << a[i] << " ";

	cout << "\n";
	return 0;
}

void write_file(int n){
	ofstream file;
	file.open("file.txt",ios::out);
	for(int i=0; i<n; i++){
		file << rand()%100 << endl; //����� � ����
	}
	file.close();
}

void sort(int* a,int n){
	for(int i=1;i<n;i++){
		for(int j=i; j>0; j--){
			if(a[j-1] > a[j]){
				int tmp=a[j-1];
				a[j-1]=a[j];
				a[j]=tmp;
			}
		}
	}
}