// 1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"

//void input(float *a, int n); //ручной ввод массива
void input_rand(float *a, int n); //ввод массива случайными числами
void output(float *a, int n); //вывод массива
void zkey(int n); //выводит ключи массива (от 0 до n)
void zline(int n); //линия
float array_sum(float *a, int n); //сумма всех элементов
float array_average(float *a, int n); //среднее значение всех элементов
int array_firstnegative(float *a, int n); //ключ первого отрицательного элемента
int array_min(float *a, int n); //ключ минимального элемента
int array_max(float *a, int n); //ключ максимального элемента

void minput_rand(int **a, int n, int m); //ввод целочисленной матрицы случайными числами
void moutput(int **a, int n, int m); //вывод матрицы
int parameter_string(int **a, int i, int m); //считает характеристику строки матрицы
int max_parameter_string(int **a, int n, int m); //находит номер строки с максимальной характеристикой
void work1(); //задание 1
void work2(); //задание 2

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0)); //делаем функцию rand зависимой от времени.
	printf("Лабораторная работа № 1 'Одномерные массивы'\nГруппа: 194-ФИТ\nСтудент: Безменов В.В.\nПреподаватель: Русакова Н.А.\n");
	work1();
	work2();

	return 0;
}


void work1(){
	int n;
	while(1){
		printf("1. Размер массива: ");
		scanf_s("%d", &n);
		if(n>1)break;
		printf("Размер должен быть больше 1\n");
	}
	float *a = new float[n];
	input_rand(a, n);
	output(a, n);

	printf("\na) Преобразовать исходный массив, вычитая из каждого элемента среднее значение.\n");
	float average = array_average(a, n);
	printf("Cреднее значение: %.2f\n", average);
	for(int i=0; i<n; i++){
		a[i] -= average;
	}
	printf("Итог:\n");
	output(a, n);

	printf("\nb) Поменять местами максимальный и первый отрицательный элементы массива.\n");
	int keyfirst = array_firstnegative(a, n), keymax = array_max(a, n);
	if(keyfirst != -1){ //-1 - отрицательных чисел нет.
		printf("Ключ первого отрицательного элемента: %d (%.2f)\nКлюч максимального элеманта: %d (%.2f)\n", keyfirst, a[keyfirst], keymax, a[keymax]);
		float temp = a[keyfirst];
		a[keyfirst] = a[keymax];
		a[keymax] = temp;
		printf("Итог:\n");
		output(a, n);
	}

	printf("\nc) Вычислить среднее значение элементов массива, отбросив минимальный и максимальный элементы.\n");
	int keymin = array_min(a, n);
	keymax = array_max(a, n);
	printf("Ключ минимального элемента: %d (%.2f)\nКлюч максимального элеманта: %d (%.2f)\n", keymin, a[keymin], keymax, a[keymax]);
	if(n-2 == 0)average = 0; else
	average = (array_sum(a, n)-a[keymin]-a[keymax])/(n-2);
	printf("Cреднее значение согласно условию: %.3f\n", average);
} //work1


void work2(){
	printf("\n2. Характеристикой строки целочисленной матрицы назовем сумму ее положительных четных элементов. Найти номер строки с максимальной характеристикой.\n");
	int n;
	while(1){
		printf("Введите количество строк: ");
		scanf_s("%d", &n);
		if(n>1)break;
		printf("Должно быть больше 1\n");
	}
	int m;
	while(1){
		printf("Введите количество столбцов: ");
		scanf_s("%d", &m);
		if(m>1)break;
		printf("Должно быть больше 1\n");
	}
	int** a = new int*[n];
	for(int i=0; i<n; i++) a[i] = new int[m];
	minput_rand(a, n, m);
	moutput(a, n, m);
	int maxp = max_parameter_string(a, n, m);
	printf("Номер строки с максимальной характеристикой (начиная с 0): %d\n\n", maxp);
} //work2


/*
void input(float *a, int n){
	for(int i=0; i<n; i++){
		printf("a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
}
*/

void input_rand(float *a, int n){
	for(int i=0; i<n; i++){
		a[i] = rand()%2000/100-10;
	}
}

void output(float *a, int n){
	zkey(n);
	zline(n);
	for(int i=0; i<n; i++){
		printf("%6.2f", a[i]);
	}
	printf("\n");
	zline(n);
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

float array_sum(float *a, int n){
	float sum = 0;
	for(int i=0; i<n; i++){
		sum+=a[i];
	}
	return sum;
}

float array_average(float *a, int n){
	float average = array_sum(a, n) / n;
	return average;
}

int array_firstnegative(float *a, int n){
	for(int i=0; i<n; i++){
		if(a[i] < 0){
			return i;
		}
	}
	printf("Отрицательных чисел не найдено.\n");
	return -1;
}

int array_min(float *a, int n){
	int keymin = 0;
	for(int i=1; i<n; i++){
		if(a[keymin] > a[i]){
			keymin = i;
		}
	}
	return keymin;
}

int array_max(float *a, int n){
	int keymax = 0;
	for(int i=1; i<n; i++){
		if(a[keymax] < a[i]){
			keymax = i;
		}
	}
	return keymax;
}

void minput_rand(int **a, int n, int m){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] = rand()%10000/100-50;
		}
	}
}

void moutput(int **a, int n, int m){
	printf("   "); zkey(m);
	printf("   "); zline(m);
	for(int i=0; i<n; i++){
		printf("%2d|", i);
		for(int j=0; j<m; j++){
			printf("%6d", a[i][j]);
		}
		//задача 2
		int p = parameter_string(a, i, m);
		printf("| = %d", p);
		printf("\n");
	}
	printf("   "); zline(m);
	printf("\n");
}

int parameter_string(int **a, int i, int m){
	int sum=0;
	for(int j=0; j<m; j+=2){
	if(a[i][j]>0)sum+=a[i][j];
	}
	return sum;
}
int max_parameter_string(int **a, int n, int m){
	int keyn = 0, maxp = parameter_string(a, 0, m);
	for(int i=1; i<n; i++){
		int p = parameter_string(a, i, m);
		if(maxp < p){
			keyn = i;
			maxp = p;
		}
	}
	printf("\n");
	return keyn;
}