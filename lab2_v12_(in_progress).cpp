//#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void zkey(int n); //выводит числа от 0 до n.
void zline(int n); //линия.
void minput_rand(int **a, int n, int m, int da, int db); //ввод целочисленной матрицы случайными числами в интервале от da до db.
void moutput(int **a, int n, int m); //вывод матрицы.
void transp(int **a, int n, int m); //транспонирование матрицы.
void msumm(int **a, int **b, int **c, int n, int m); //сложение матриц. Результат в матрице c.
void multiplic(int **a, int **b, int **c, int n, int m, int n2, int m2); //Умножение матриц. Необходима проверка:
//Количество строк 2й матрицы должно соответствовать количеству столбцов 1й.
void multiplic_vector(double **a, double *v, double *res, int n, int m); //Умножение матрицы на вектор.
int mmax(int **a, int n, int &max_n, int &max_m); //Макс. элемент выше главной диагонали.
int mmin(int **a, int n, int &min_n, int &min_m); //Мин. элемент ниже всех диагоналей.

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	cout << "Лабораторная работа #2. Вариант 12.\n";
	int menu = 0;
	while(1){
		cout << "Введите номер задания (1,2) или 0 - для выхода: ";
		cin >> menu;
		switch(menu){
			case 0:
				cout << "Выход.\n";
				return 0;
			break;
			case 1:
			{
				//Задание 1.
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
                cout << "Максимальный отрицательный выше главной диагонали (включительно): " << a[max_n][max_m] << endl;
                cout << "Минимальный положительный ниже всех диагоналей (включительно): " << a[min_n][min_m] << endl;
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
    //Макс. отриц. элемент выше главной диагонали.
    int max = a[0][0];
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            //cout << a[i][j] << ", ";      //Тест успешен. Выделены все нужные элементы.
            if(a[i][j]<0 && a[i][j] > max) max = a[i][j];
        }
    }
}
void mmin(int **a, int n, int min_n, int min_m){
    //Мин. полож. элемент ниже всех диагоналей.
    int min = a[0][0];
    int t;                                      //Создает инверсию, когда j доходит до середины.
    for(int j=0; j<n; j++){                     //Перебираем столбцы, выделяем их все.
        if(j<n/2+n%2)t=j; else t=(n-1)-j;       //С++ округляет в меньшую сторону, нужна наибольшая. Инверсия.
        for(int i=(n-1); i>=(n-1)-t; i--){      //Считаем с последней строки. Отнимаем j, потом когда j достигает середины - m-j.
            //cout << a[i][j] << ", ";          //Тест успешен. Выделены все нужные элементы.
            if(a[i][j] >=0 && a[i][j] < min) min = a[i][j];
        }
    }
}
