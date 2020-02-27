#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>

using namespace std;

void write_file(int n);
	/* Cоздание файла с n случайными числами на каждой строке.
	Предусловие:
	 1) n - количество чисел/строк
	Постусловие: 
	1) Создает/перезаписывает файл file.txt в корневой директории проекта.
	Пишет в него n строк, каждая строка со случайным числом, лежащем в диапазоне от -100 до 100 и содержащем случайную дробную часть до одного знака.*/

void read_file(float **a, int &n, float k);
	/* Чтение файла и создание одномерного массива из его чисел, где каждый элемент больше k.
	Предусловие:
	1) a - это указатель на нулевой массив;
	2) n - любое число.
	Постусловие: 
	1) a - одномерный массив, состоящий из чисел (целых, дробных), больших k.
	Эти числа будут считаны из файла file.txt, который должен находится в корневой директории проекта.
	2) Переменная n изменилась на размер массива a, дибо на -1, если файл не был найден. */

void output(float *a, int n);
	/* Вывод одномерного массива с дробными числами.
	Предусловие:
	1) a - одномерный массив с дробными числами.
	2) n - размер массива a.
	Постусловие: 
	1) Выводит содержимое массива a на экран. */

void output_int(int *a, int n);
	/* Вывод одномерного массива с целыми числами.
	Предусловие:
	1) a - одномерный массив с целыми числами.
	2) n - размер массива a.
	Постусловие: 
	1) Выводит содержимое массива a на экран. */

void sort(float *a, int n);
	/* Сортировка массива в возрастающем порядке.
	Предусловие:
	1) a - одномерный массив с дробными числами.
	2) n - размер массива a.
	Постусловие: 
	1) Элементы в массиве a упорядочены в возрастающем порядке. */

void input_rand_advanced(int *a, int n, int da, int db);
	/*Заполняет массив случайными числами из интервала [da, db].
	Предусловие:
	1) a - одномерный целочисленный массив размерности n.
	2) da и db - интервал от da до db.
	Постусловие: 
	1) a содержит n случайных целых чисел из интервала [da, db]. */

void array_copy(int *a, int n, int *a2, int k);
	/*Копирует массив a в массив a2, добавляя в отрицательным элементам число k.
	Предусловие:
	1) a - одномерный целочисленный массив размерности n.
	2) a2 - одномерный целочисленный массив размерности n.
	3) k - любое целое число.
	Постусловие: 
	1) a2 - массив, элементы которые равны элементам в массиве a, но к отрицательным элементам еще добавлено число k. */


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
				//write_file(20); //- создать файл с 20 случайными числами
				float k;
				cout << "k = "; // выведет только те элементы массива a, которые больше k.
				cin >> k;
				float *a = NULL;
				int n = 0;
				read_file(&a, n, k);
				if(n==-1){
					cout << "Файл не найден.\n\n";
					continue;
				}
				sort(a, n);
				output(a, n);
				delete[] a;
				//Конец задания 1.
			}
			break;
			case 2:
			{
				//Задание 2.
				int n, da, db, k;
				cout << "n = "; //размер первого массива.
				cin >> n;
				if(n<=0){
					cout << "Размер массива должен быть больше 0.\n\n";
					continue;
				}
				cout << "a = "; //задается интервал [a, b] для случайных чисел.
				cin >> da;
				cout << "b = ";
				cin >> db;
				if(db<da){
					cout << "Неверно задан интервал.\n\n";
					continue;
				}
				cout << "k = "; //добавится после каждого отрицательного элемента.
				cin >> k;

				//создаем первый массив:
				int *a = new int[n];
				input_rand_advanced(a, n, da, db);
				cout << "\nПервый массив:\n\n";
				output_int(a, n);

				//создаем второй массив:
				int *a2 = new int[n];
				array_copy(a, n, a2, k);
				cout << "\nНовый массив:\n\n";
				output_int(a2, n);

				delete[] a;
				delete[] a2;
				//Конец задания 2.
			}
			break;
			default:
				cout << "Такого задания нет.\n";
		} //switch
		cout << endl;
	} //while
}

void output(float *a, int n){
	cout << "[";
	for(int i=0; i<n; i++){
		cout << a[i]; 
		if(i<n-1)cout << ", ";
	}
	cout << "]\n";
}

void write_file(int n){
	ofstream file;
	file.open("file.txt",ios::out);
	for(int i=0; i<n; i++){
		file << ((float)(rand()%2000-1000))/10 << endl; //вывод в файл
	}
	file.close();
}

void read_file(float **a, int &n, float k){
	*a = NULL; //массив a должен быть пустым.
	n=0;
	ifstream file;
	float out;
	file.open("file.txt", ios::in);
	if(!file){ //проверка на существование файла.
		n=-1;
		return;
	}
	while (!file.eof()) {
		file >> out; //ввод из файла
		if(out > k){ //по заданию, если число больше k.
			*a = (float*)realloc(*a, sizeof(float) * (n+1)); //массив a стал больше на 1 элемент float.
			(*a)[n] = out;
			n++;
		}
	}
	file.close();
}

void sort(float *a, int n){ //сортировка вставками.
	for(int i=1;i<n;i++){
		for(int j=i; j>0; j--){
			if(a[j-1] > a[j]){
				float tmp=a[j-1];
				a[j-1]=a[j];
				a[j]=tmp;
			}
		}
	}
}


void output_int(int *a, int n){
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

void array_copy(int *a, int n, int *a2, int k){
	for(int i=0; i<n; i++){
		if(a[i] < 0)a2[i]=a[i]+k; else a2[i]=a[i];
	}
}