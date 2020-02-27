#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void zkey(int n); //выводит числа от 0 до n
void zline(int n); //линия
void minput_rand(int **a, int n, int m); //ввод целочисленной матрицы случайными числами
void moutput(int **a, int n, int m); //вывод матрицы
void transp(int **a, int n, int m); //транспонирование матрицы
void msumm(int **a,int **b,int **c,int n,int m); //сложение матриц. Результат в матрице c.
void multiplic(int **a, int **b, int **c, int n, int m, int n2, int m2); //Умножение матриц. Необходима проверка:
//Количесвто строк 2й матрицы должно соответствовать количеству столбцов 1й.
void multiplic_vector(double **a, double *v, double *res, int n, int m); //Умножение матрицы на вектор.

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int menu = 0;
	while(1){
		cout << "Введите номер задания или 0 - для выхода: ";
		cin >> menu;
		switch(menu){
			case 0:
				cout << "Выход.\n";
				return 0;
			break;
			case 1: 
			{
				//Задание 1.
				//Конец задания 1.
			}
			break;
			case 2:
			{
				//Задание 2.
				//Конец задания 2.
			}
			break;
			default:
				cout << "Такого задания нет.\n";
		} //switch
		cout << endl;
	} //while
}

void minput_rand(int **a, int n, int m){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] = rand()%200-100;
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