//#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include "windows.h"

using namespace std;

void zkey(int n); //выводит числа от 0 до n.
void zline(int n); //линия.
void minput_rand(int **a, int n, int m, int da, int db); //ввод целочисленной матрицы случайными числами в интервале от da до db.
void moutput(int **a, int n, int m); //вывод матрицы.
void moutput2(int **a, int n, int m, char c); //вывод матрицы.
void transp(int **a, int n, int m); //транспонирование матрицы.
void msumm(int **a, int **b, int **c, int n, int m); //сложение матриц. Результат в матрице c.
void multiplic(int **a, int **b, int **c, int n, int m, int n2, int m2); //Умножение матриц. Необходима проверка:
//Количество строк 2й матрицы должно соответствовать количеству столбцов 1й.
void multiplic_vector(double **a, double *v, double *res, int n, int m); //Умножение матрицы на вектор.
void mmax(int **a, int n, int &max_n, int &max_m); //Макс. элемент выше главной диагонали.
void mmin(int **a, int n, int &min_n, int &min_m); //Мин. элемент ниже всех диагоналей.
void live_tick(int **a, int n, int m, bool &change);
int isLive(int **a, int n, int m, int i, int j);

int main(){
	setlocale(LC_ALL, "Russian");

	srand(time(0));

	cout << "Лабораторная работа #2. Вариант 12.\n";
	int menu = 0;
	while(1){
		cout << "Введите номер задания (1-5) или 0 - для выхода: ";
		cin >> menu;
		switch(menu){
			case 0:
				cout << "Выход.\n";
				return 0;
			break;
			case 1:
			{
				//Задание 1. Игра жизнь.
				int time = 0; //Количество шагов игры.
				int n = 10;
                int** a = new int*[n];
                for(int i=0; i<n; i++) a[i] = new int[n];
                minput_rand(a, n, n, 0, 1);
                moutput2(a, n, n, 'X');
				while(1){
                    int c;
                    cout << "Сколько шагов нужно сделать? (0 - для выхода): ";
                    cin >> c;
                    if(c==0) break;
                    c += time; //c - до какого шага нужно идти.
                    bool change; //Т.к. нужно после блока while.
                    while(time < c){
                        time++;
                        change = false;
                        live_tick(a, n, n, change);
                        system("cls");
                        moutput2(a, n, n, 'X');
                        cout << "Поколение №" << time << "\nОсталось шагов: " << (c-time) <<endl;
                        if(change)Sleep(220); else break; //Если поле не изменилось, выходим.
                    }
                    if(change == false){
                        cout << "Поколение не изменилось. Игра окончена.\n";
                        cin.get();
                        break;
                    }
				}
				//Конец задания 1.
			}
			break;
			case 2:
			{
			    int n = 10;
                int** a = new int*[n];
                for(int i=0; i<n; i++) a[i] = new int[n];
                minput_rand(a, n, n, 0, 1);
			}
            break;
			case 3:
			{
				//Задание 3.
				int n, da, db, min_n, min_m, max_n, max_m;
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
                int temp = a[max_n][max_m];
                a[max_n][max_m] = a[min_n][min_m];
                a[min_n][min_m] = temp;
                moutput(a, n, n);
				//Конец задания 3.
			}
			break;
			case 4:
			{
				//Задание 4.
				//Конец задания 4.
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

void moutput2(int **a, int n, int m, char c){
	for(int i=0; i<n; i++){
		printf("%1d|", i);
		for(int j=0; j<m; j++){
			if(a[i][j])printf("%2c", c); else printf("%2c", ' ');
		}
		printf("|\n");
	}
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

void mmax(int **a, int n, int &max_n, int &max_m){
    //Макс. отриц. элемент выше главной диагонали.
    //TODO: Сделать проверку на отрицательность первого элемента.
    max_n = 0; max_m = 0;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            //cout << a[i][j] << ", ";          //Тест успешен. Выделены все нужные элементы.
            if(a[i][j]<0 && a[i][j] > a[max_n][max_m]){
                max_n = i;
                max_m = j;
            }
        }
    }
}
void mmin(int **a, int n, int &min_n, int &min_m){
    //Мин. полож. элемент ниже всех диагоналей.
    min_n = 0; min_m = 0;
    int t;                                      //Создает инверсию, когда j доходит до середины.
    for(int j=0; j<n; j++){                     //Перебираем столбцы, выделяя их все.
        if(j<n/2+n%2)t=j; else t=(n-1)-j;       //С++ округляет в меньшую сторону, нужна наибольшая. Инверсия.
        for(int i=(n-1); i>=(n-1)-t; i--){      //Считаем с последней строки. Отнимаем j, потом когда j достигает середины - m-j.
            //cout << a[i][j] << ", ";          //Тест успешен. Выделены все нужные элементы.
            if(a[i][j] >=0 && a[i][j] < a[min_n][min_m]){
                min_n = i;
                min_m = j;
            }
        }
    }
}

void live_tick(int **a, int n, int m, bool &change){
    int** a2 = new int*[n];
    for(int i=0; i<n; i++) a2[i] = new int[m];
    //Решаем, быть ли клетке в следующем поколении. Задаем специальную функкцию.
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
                a2[i][j] = isLive(a, n, m, i, j);
        }
    }
    //Новое поколение создано. Копируем массив a2 в a
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
                if(a[i][j] != a2[i][j]) change = true; //Поле изменилось. Есть смысл продолжать.
                a[i][j] = a2[i][j];
        }
    }
}

int isLive(int **a, int n, int m, int i, int j){
    //Считаем кол-во живых клеток вокруг определенной клетки и в конце возвращаем 0 или 1.
    int live = 0;
    //Неживых клеток вокруг естественно будет 8-life.
    //За границей поля только мертвые клетки. Нужно 8 условий. Но мы сделаем с помощью цикла.
    for(int i2=-1; i2<=1; i2++){
      for(int j2=-1; j2<=1; j2++){
        if(i2==0&&j2==0)continue; //Текущую клетку следует пропустить.
        if(i+i2<0||i+i2>=n||j+j2<0||j+j2>=m)continue;
        if(a[i+i2][j+j2]==1)live++;
      }
    }
    //Пошли условия из условия:
    if(a[i][j]==1 && (live==2||live==3))return 1;
    if(a[i][j]==0 && live==3)return 1;
    return 0;
}
