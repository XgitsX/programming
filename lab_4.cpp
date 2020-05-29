#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void input_rand_advanced(int *a, int n, int da, int db);
	/* Заполняет массив случайными числами из интервала [da, db].
	Предусловие:
	1) a - одномерный целочисленный массив размерности n.
	2) da и db - интервал от da до db.
	Постусловие: 
	1) a содержит n случайных целых чисел из интервала [da, db]. */

void output_arrayint(int *a, int n);
	/* Вывод одномерного массива с целыми числами.
	Предусловие:
	1) a - одномерный массив с целыми числами.
	2) n - размер массива a.
	Постусловие: 
	1) Выводит содержимое массива a на экран. */

int recursion_oddmax(int *a, int n, int index);
	/* Находит наибольший нечетный элемент массива.
	Предусловие:
	1) a - одномерный массив с целыми числами.
	2) n - размер массива a.
	3) index - с какого индекса начинать поиск (0).
	Постусловие: 
	1) Выводит наибольший нечетный элемент массива a, либо 0, если нечетных элементов нет.
	Примечание:
	1) Для работы требуется функция recursion_firstodd */

int recursion_firstodd(int *a, int n, int index);
	/* Поиск первого нечетного числа в одномерном массиве.
	Предусловие:
	1) a - одномерный массив с целыми числами.
	2) n - размер массива a.
	3) index - с какого индекса начинать поиск (0).
	Постусловие: 
	1) Выводит первое нечетное число в массиве a или 0, если таких чисел нет. */

int recursion_psum(int n, int a, int d, int index);
	/* Считает сумму арифметической прогрессии.
	Предусловие:
	1) n - количество членов арифметической прогрессии.
	2) a - значение текущего элемента (первый член).
	3) d - разность арифметической прогрессии.
	3) index - номер элемента, с которого начинать счет (1).
	Постусловие: 
	1) Вывод суммы арифметической прогрессии. */

int recursion_F(int n);
	//Алгоритм F(n), описанный в задаче 3.

int recursion_G(int n);
	//Алгоритм G(n), описанный в задаче 3.


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
				int n=3, da=-100, db=100;
				int *a = new int[n];
				input_rand_advanced(a, n, da, db);
				cout << "1. Напишите рекурсивную функцию, которая находит максимальный среди нечетных элементов массива.\nМассив: ";
				output_arrayint(a, n);

				int max = recursion_oddmax(a, n, 0);
				if(max == 0){ //число 0 - четное, поэтому здесь оно используется в качестве определителя ошибки.
					cout << "В массиве нет нечетных элементов.\n";
				}else cout << "Максимальный нечетный элемент: " << max << endl;

				//Конец задания 1.
			}
			break;
			case 2:
			{
				//Задание 2.
				int n, a, d;
				cout << "2. Вычислить сумму n первых членов арифметической прогрессии с первым членом а и разностью d.\nn=";
				cin >> n;
				cout << "a=";
				cin >> a;
				cout << "d=";
				cin >> d;
				cout << "Сумма: " << recursion_psum(n, a, d, 1) << endl;
				//Конец задания 2.
			}
			break;
			case 3:
			{
				//Задание 3.
				cout << "3. Через описанный алгоритм вычислите первые 10 значений F(i) и G(i), i = 1, 2, ... , 10. \n\n";
				for(int i=1; i<=10; i++){
					cout << "F(" << i << ") = " << recursion_F(i) << endl;
				}
				cout << endl;
				for(int i=1; i<=10; i++){
					cout << "G(" << i << ") = " << recursion_G(i) << endl;
				}
				//Конец задания 3.
			}
			break;
			default:
				cout << "Такого задания нет.\n";
		} //switch
		cout << endl;
	} //while
}


void output_arrayint(int *a, int n){
	cout << "[";
	for(int i=0; i<n; i++){
		cout << a[i]; 
		if(i<n-1)cout << ", ";
	}
	cout << "]\n";
}


void input_rand_advanced(int *a, int n, int da, int db){
	for(int i=0; i<n; i++){
		a[i] = (rand()%(db-da+1)) + da;
	}
}


int recursion_firstodd(int *a, int n, int index){
	if(abs(a[index]) % 2 == 1)return a[index];
	if(index+1 == n)return 0;
	return recursion_firstodd(a, n, index+1);
}


int recursion_oddmax(int *a, int n, int index){
	//Четные элементы пропускаем.
	if(abs(a[index]) % 2 == 0){
		// Если нечетных чисел нет, то пропускается все, кроме следующей строки, которая вернет 0 - определитель ошибки.
		if(index+1 == n) return recursion_firstodd(a, n, 0);
		return recursion_oddmax(a, n, index+1);
	}
	//Текущий элемент - нечетный.
	if(index+1 == n) return a[index];
	int fow = recursion_oddmax(a, n, index+1);
	//Сравниваем текущее число с следующим и выводим наибольшее.
	if(a[index] > fow)return a[index]; else return fow;
}


int recursion_psum(int n, int a, int d, int index){
	//n - кол-во членов, a - текущий член, d - разность, index - текущая позиция.
	if(index == n) return a;
	return a + recursion_psum(n, a+d, d, index+1);
}


int recursion_F(int n){
	if(n==1) return -5;
	return 4*recursion_F(n-1) + recursion_G(n-1);
}


int recursion_G(int n){
	if(n==1) return 1;
	return -2*recursion_F(n-1) + recursion_G(n-1);
}