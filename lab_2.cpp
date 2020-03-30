#include "stdafx.h"
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
void moutput2(int **a, int n, int m); //вывод матрицы (для игр "Жизнь" и "Крестики-нолики").
void mmax(int **a, int n, int &max_n, int &max_m); //Макс. элемент выше главной диагонали.
void mmin(int **a, int n, int &min_n, int &min_m); //Мин. элемент ниже всех диагоналей.
void life_tick(int **a, int n, int m, bool &change); //Смена одного поколения.
int islife(int **a, int n, int m, int i, int j); //Будет ли жить указанная клетка в следующем поколении.
int game(int **a, int n); //Один ход в игре "Крестики-нолики".
bool isWin(int **a, int n, int player); //Выиграл ли игрок (1) или компьютер (2) на этом поле.
bool fastWin(int **a, int n); //Атака и защита компьютера в игре "Крестики-нолики".
bool noWin(int **a, int n); //Проверка на ничью.

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	cout << "Лабораторная работа #2. Вариант 12.\n";
	int menu = 0;
	while(1){
		cout << "1 - игра Жизнь;\n2 - метод Гаусса (не реализовано);\n3 - первое задание 12-ого варианта;\n4 - второе (не реализовано);\n5 - крестики-нолики.\nВведите номер задания (1-5) или 0 - для выхода: \n";
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
				int n = 20;
                int** a = new int*[n];
                for(int i=0; i<n; i++) a[i] = new int[n];
                minput_rand(a, n, n, 0, 1);
				system("cls");
                moutput2(a, n, n);
				while(1){
                    int c;
                    cout << "Сколько шагов нужно сделать? (0 - назад в меню): ";
                    cin >> c;
                    if(c==0) break;
                    c += time; //c - до какого шага нужно идти.
                    bool change;
                    while(time < c){
                        time++;
                        change = false;
                        life_tick(a, n, n, change);
                        system("cls");
                        moutput2(a, n, n);
                        cout << "Поколение №" << time << "\nОсталось шагов: " << (c-time) <<endl;
                        if(change)Sleep(220); else break; //Если поле не изменилось, выходим.
                    }
                    if(change == false){
                        cout << "Поколение не изменилось. Игра окончена.\n";
                        break;
                    }
				}
				//Конец задания 1.
			}
			break;
			case 2:
			{
				//Задание 2.
				//Конец задания 2.
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
				if(max_n==-1)cout << "Отрицательных элементов нет.\n";
				 else cout << "Максимальный отрицательный выше главной диагонали (включительно): " << a[max_n][max_m] << endl;
				if(min_n==-1)cout << "Положительных элементов нет.\n";
				 else cout << "Минимальный положительный ниже всех диагоналей (включительно): " << a[min_n][min_m] << endl;
				if(max_n!=-1 && min_n!=-1){
					int temp = a[max_n][max_m];
					a[max_n][max_m] = a[min_n][min_m];
					a[min_n][min_m] = temp;
					moutput(a, n, n);
				}else cout << "Переставить местами невозможно.\n";
				//Конец задания 3.
			}
			break;
			case 4:
			{
				//Задание 4.
				//Конец задания 4.
			}
			break;
			case 5:
			{
				//Игра "Крестики-нолики".
				//Крестик в матрице - 1, нолик - 2.
				int n = 3;
                int** a = new int*[n];
				for(int i=0; i<n; i++){
					a[i] = new int[n];
					for(int j=0; j<n; j++)a[i][j]=0;
				}
				system("cls");
                moutput2(a, n, n);
				cout << "Помощь: Чтобы сделать ход, укажите число от 1 до 9.\n(1 - верхний левый угол, 9 - правый нижний).\n";
				while(1){
					int turn;
					while(1){
						cout << "Ваш ход: ";
						cin >> turn; turn--;
						if(turn<0 || turn>8 || a[turn/3][turn%3]>0){
							cout << "Либо клетка уже занята, либо вы ввели неправильное число.\n";
							continue;
						}
						a[turn/3][turn%3]=1;
						break;
					}
					int gamestate = game(a, n);
					system("cls");
					moutput2(a, n, n);
					if(gamestate == 1){
						cout << "Вы победили!\n";
						break;
					}else if(gamestate == 2){
						cout << "Вы проиграли.\n";
						break;
					}else if(gamestate == 3){
						cout << "Ничья.\n";
						break;
					}
				}
				//Конец задания 5.
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

void moutput2(int **a, int n, int m){
	for(int i=0; i<n; i++){
		printf("|");
		for(int j=0; j<m; j++){
			if(a[i][j]==1)printf("%2c", 'X'); else if(a[i][j]==2)printf("%2c", 'O'); else printf("%2c", ' ');
		}
		printf("|\n");
	}
	printf("\n");
}

void mmax(int **a, int n, int &max_n, int &max_m){
    //Макс. отриц. элемент выше главной диагонали.
    max_n = -1; max_m = -1;
    for(int i=0; i<n; i++){
        for(int j=i; j<n; j++){
            //cout << a[i][j] << ", ";          //Тест успешен. Выделены все нужные элементы.
			if(a[i][j]<0 && (max_n == -1 || a[i][j] > a[max_n][max_m])){
                max_n = i;
                max_m = j;
            }
        }
    }
}
void mmin(int **a, int n, int &min_n, int &min_m){
    //Мин. полож. элемент ниже всех диагоналей.
    min_n = -1; min_m = -1;
    int t;
    for(int j=0; j<n; j++){                     //Перебираем столбцы, выделяя их все.
        if(j<n/2+n%2)t=j; else t=(n-1)-j;       //С++ округляет в меньшую сторону, нужна наибольшая.
        for(int i=(n-1); i>=(n-1)-t; i--){      //Считаем с последней строки. Отнимаем j, потом когда j достигает середины - m-j.
            //cout << a[i][j] << ", ";          //Тест успешен. Выделены все нужные элементы.
            if(a[i][j] >=0 && (min_n == -1 || a[i][j] < a[min_n][min_m])){
                min_n = i;
                min_m = j;
            }
        }
    }
}

void life_tick(int **a, int n, int m, bool &change){
    int** a2 = new int*[n];
    for(int i=0; i<n; i++) a2[i] = new int[m];
    //Решаем, быть ли клетке в следующем поколении. Задаем специальную функкцию isLife.
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
                a2[i][j] = islife(a, n, m, i, j);
        }
    }
    //Новое поколение создано. Копируем массив a2 в a:
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
                if(a[i][j] != a2[i][j]) change = true; //Поле изменилось. Есть смысл продолжать смену поколений после вихода из этой функции.
                a[i][j] = a2[i][j];
        }
    }
}

int islife(int **a, int n, int m, int i, int j){
    //Считаем кол-во живых клеток вокруг определенной клетки:
    int life = 0;
    //Нужно 8 условий. Но мы сделаем с помощью цикла:
    for(int i2=-1; i2<=1; i2++){
      for(int j2=-1; j2<=1; j2++){
        if(i2==0&&j2==0)continue;						//Текущую клетку следует пропустить.
        if(i+i2<0||i+i2>=n||j+j2<0||j+j2>=m)continue;	//За границей поля только мертвые клетки.
        if(a[i+i2][j+j2]==1)life++;
      }
    }
    //Дальше идут условия из задачи:
    if(a[i][j]==1 && (life==2||life==3))return 1;
    if(a[i][j]==0 && life==3)return 1;
    return 0;
}

int game(int **a, int n){
	//Игрок сходил, проверка на выигрыш.
	if(isWin(a, n, 1))return 1;
	//А есть ли, куда ходить компьютеру?
	if(noWin(a, n))return 3;
	//Атака и защита - это функция fastWin.
	if(!fastWin(a, n)){
		//Если ничего нет, ставим на случайное свободное место.
		int k = 0; //Количество свободных мест.
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(a[i][j]==0)k++;
			}
		}
		int rnd = rand()%k + 1; //Номер свободной ячейки, куда сходит компьютер.
		k=0; //Считаем по порядку свободные ячейки.
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				if(a[i][j]==0){
					k++;
					if(k==rnd){a[i][j] = 2; k=-1; break;}
				}
			}
			if(k==-1)break;
		}
	}
	//Компьютер сходил, проверка на выигрыш.
	if(isWin(a, n, 2))return 2;
	return 0;
}

bool fastWin(int **a, int n){
	for(int i2=0; i2<n; i2++){
		for(int j2=0; j2<n; j2++){
			if(a[i2][j2]!=0)continue;
			int** a2 = new int*[n];
			for(int i=0; i<n; i++){
				a2[i] = new int[n];
				for(int j=0; j<n; j++)a2[i][j]=a[i][j];
			}
			a2[i2][j2] = 2;
			if(isWin(a2, n, 2)){a[i2][j2] = 2; return true; }
			a2[i2][j2] = 1;
			if(isWin(a2, n, 1)){a[i2][j2] = 2; return true; }
		}
	}
	return false;
}

bool noWin(int **a, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++)if(a[i][j]==0)return false;
	}
	return true;
}

bool isWin(int **a, int n, int pl){ 
	if((a[0][0]==pl && a[0][1]==pl && a[0][2]==pl)
		|| (a[1][0]==pl && a[1][1]==pl && a[1][2]==pl)
		|| (a[2][0]==pl && a[2][1]==pl && a[2][2]==pl)
		|| (a[0][0]==pl && a[1][0]==pl && a[2][0]==pl)
		|| (a[0][1]==pl && a[1][1]==pl && a[2][1]==pl)
		|| (a[0][2]==pl && a[1][2]==pl && a[2][2]==pl)
		|| (a[0][0]==pl && a[1][1]==pl && a[2][2]==pl)
		|| (a[0][2]==pl && a[1][1]==pl && a[2][0]==pl))return true;
	return false;
}