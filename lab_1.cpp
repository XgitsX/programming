#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void input_rand_advanced(int *a, int n, int da, int db);
	/*Заполняет массив случайными числами из интервала [da, db].
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
int recursion_max(int *a, int n, int index);


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

			}
			break;
			case 2:
			{
				//Задание 2.
				int n=10, da=-100, db=100, k;
				int *a = new int[n];
				input_rand_advanced(a, n, da, db);
				cout << "\nМассив:\n\n";
				output_int(a, n);
				cout << "\nМаксимальный элемент: ";
				recursion_max(a, n, 0);
				//Конец задания 2.
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


void recursion_max(int *a, int n, int index){
	if(index+1 == n) return a[index];
	int fow = recursion_max(a, n, index+1);
	if(a[index] > fow)return a[index]; else return fow;
}