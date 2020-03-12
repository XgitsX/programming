//#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void zkey(int n); //������� ����� �� 0 �� n.
void zline(int n); //�����.
void minput_rand(int **a, int n, int m, int da, int db); //���� ������������� ������� ���������� ������� � ��������� �� da �� db.
void moutput(int **a, int n, int m); //����� �������.
void transp(int **a, int n, int m); //���������������� �������.
void msumm(int **a, int **b, int **c, int n, int m); //�������� ������. ��������� � ������� c.
void multiplic(int **a, int **b, int **c, int n, int m, int n2, int m2); //��������� ������. ���������� ��������:
//���������� ����� 2� ������� ������ ��������������� ���������� �������� 1�.
void multiplic_vector(double **a, double *v, double *res, int n, int m); //��������� ������� �� ������.
int mmax(int **a, int n, int &max_n, int &max_m); //����. ������� ���� ������� ���������.
int mmin(int **a, int n, int &min_n, int &min_m); //���. ������� ���� ���� ����������.

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	cout << "������������ ������ #2. ������� 12.\n";
	int menu = 0;
	while(1){
		cout << "������� ����� ������� (1,2) ��� 0 - ��� ������: ";
		cin >> menu;
		switch(menu){
			case 0:
				cout << "�����.\n";
				return 0;
			break;
			case 1:
			{
				//������� 1.
				int n,da,db, min_n, min_m, max_n, max_m;
				cout << "n=";
				cin >> n;
				//m=n
				cout << "a=";
				cin >> da;
				cout << "b=";
				cin >> db;
				int** a = new int*[n];
                for(int i=0; i<n; i++) a[i] = new int[n];
                minput_rand(a, n, n, da, db);
                moutput(a, n, n);
                mmax(a, n, max_n, max_m);
                mmin(a, n, min_n, min_m);
                cout << "������������ ������������� ���� ������� ��������� (������������): " << a[max_n][max_m] << endl;
                cout << "����������� ������������� ���� ���� ���������� (������������): " << a[min_n][min_m] << endl;
				//����� ������� 1.
			}
			break;
			case 2:
			{
				//������� 2.
				//����� ������� 2.
			}
			break;
			default:
				cout << "������ ������� ���.\n";
		} //switch
		cout << endl;
	} //while
}

void minput_rand(int **a, int n, int m, int da, int db){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] = (rand()%(db-da+1)) + da;
		}
	}
}

void zkey(int n){
	for(int i=0; i<n; i++){
		printf("%6d", i);
	}
	printf("\n");
}
void zline(int n){
	for(int i=0; i<n; i++){
		printf("------");
	}
	printf("\n");
}

void moutput(int **a, int n, int m){
	printf("   "); zkey(m);
	printf("   "); zline(m);
	for(int i=0; i<n; i++){
		printf("%2d|", i);
		for(int j=0; j<m; j++){
			printf("%6d", a[i][j]);
		}
		printf("|\n");
	}
	printf("   "); zline(m);
	printf("\n");
}

void transp(int **a, int n, int m){
    int temp;
    for(int i=0; i<n; i++){
		for(int j=i; j<m; j++)
        {
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
        }
    }
}

void msumm(int **a, int **b, int **c, int n, int m){
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
             c[i][j]=a[i][j]+b[i][j];
        }
    }
}

void multiplic(int **a, int **b, int **c, int n, int m, int n2, int m2){
 for(int i = 0; i < n; ++i){
  for(int j = 0; j < m2; ++j){
   for(int k = 0; k < m; ++k){
    c[i][j] += a[i][k] * b[k][j];
   }
  }
 }
}

void multiplic_vector(double **a, double *v, double *res, int n, int m){
    for(int i=0; i<m; i++){
        float sum = 0;
        for(int j=0; j<n; j++){
            sum += a[i][j] * v[j];
        }
        res[i] = sum;
    }
}

void mmax(int **a, int n, int max_n, int max_m){
    //����. �����. ������� ���� ������� ���������.
    int max = a[0][0];
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            //cout << a[i][j] << ", ";      //���� �������. �������� ��� ������ ��������.
            if(a[i][j]<0 && a[i][j] > max) max = a[i][j];
        }
    }
}
void mmin(int **a, int n, int min_n, int min_m){
    //���. �����. ������� ���� ���� ����������.
    int min = a[0][0];
    int t;                                      //������� ��������, ����� j ������� �� ��������.
    for(int j=0; j<n; j++){                     //���������� �������, �������� �� ���.
        if(j<n/2+n%2)t=j; else t=(n-1)-j;       //�++ ��������� � ������� �������, ����� ����������. ��������.
        for(int i=(n-1); i>=(n-1)-t; i--){      //������� � ��������� ������. �������� j, ����� ����� j ��������� �������� - m-j.
            //cout << a[i][j] << ", ";          //���� �������. �������� ��� ������ ��������.
            if(a[i][j] >=0 && a[i][j] < min) min = a[i][j];
        }
    }
}
