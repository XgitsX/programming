	/*
	Файлы, которые необходимы для работы определенных заданий:
	D:\word.txt - 2. Артиклы, глаголы, существительные и предлоги. Слова отделяются пробелом, смена типа слова - через символ "/".
	D:\text.txt - 4. Текст, в котором необходимо посчитать слова и предложения.
	*/

#include "stdafx.h"
#include "locale.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "iostream"
#include "ctype.h"
#include "string.h"
#include "fstream"
#include "windows.h"

int length(char* s); // Функция, определяющая длину строки.
bool palindrom(char* text); // Функция, определяющая является ли строка палиндромом.
int rand(int max); // функция, генерирующая случайные числа до от 0 до max-1.

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	cout << "Практическая работа на тему 'строки':\n";
	int menu = 0;
	while(1){
		cout << "Введите номер задания (1-4) или 0 - для выхода:\n 1 - вычислить длину строки,\n 2 - предложения из случайных слов,\n 3 - палиндром,\n 4 - количество слов и предложений в текстовом файле.\n";
		cin >> menu;
		cin.clear();
		cin.ignore();

		switch(menu){
			case 0:
				cout << "Выход.\n";
				return 0;
			break;


			case 1:	{
				cout << "1) Написать функцию вычисления длины строки.\n";
					/*
						ввод: test
						вывод: длина строки равна 4 +
		
						ввод: Пятница
						вывод: длина строки равна 7 +
		
						ввод: 12312
						вывод: длина строки равна 5 +
					*/
				char* s = new char[80];
				cout << "Введите строку: ";
				cin.getline(s, 255);
				cout << "Длина строки равна " << length(s) << endl;
			break;	}


			case 2:	{
				cout << "2) Написать программу, которая использует генератор случайных чисел.\nПрограмма должна создавать предложения, выбирая случайным образом слова из массивов.\n";
					/*	Вывод:
						The dog ran over an town.
						A girl drove over an boy.
						The girl ran to the dog.
					*/
				char** article = (char**)malloc(sizeof(char*));
				char** noun = (char**)malloc(sizeof(char*));
				char** verb = (char**)malloc(sizeof(char*));
				char** prep = (char**)malloc(sizeof(char*));

				int article_size;
				int noun_size;
				int verb_size;
				int prep_size;

				ifstream  file("D:\\word.txt");
				if (!file){
					cout << "Ошибка при открытии файла.\n";
					break;
				}
				int current_array = 0;
				int current_word = 0;
				int current_symbol = 0;
				article[0] = (char*)malloc(255*sizeof(char));
				char s[255];
				while (file.getline(s, 255)){
					for (int i = 0; i < 255; i++){
							if(s[i] != '\0'){
								if(s[i] == '/'){
									/* Переход к следующему массиву:
									1) Заканчиваем текущую строку в текущем массиве.
									2) Закрепляем размер массива в памяти для использования далее.
									3) Выделяем место в памяти первому элементу следующего массива. */
									current_array++;
									switch(current_array){
										case 1:
											article[current_word][current_symbol] = '\0';
											article_size = current_word + 1;
											noun[0]=(char*)malloc(255*sizeof(char));
											break;
										case 2:
											noun[current_word][current_symbol] = '\0';
											noun_size = current_word + 1;
											verb[0]=(char*)malloc(255*sizeof(char));
											break;
										default:
											verb[current_word][current_symbol] = '\0';
											verb_size = current_word + 1;
											prep[0]=(char*)malloc(255*sizeof(char));
									}
									current_word = 0;
									current_symbol = 0;
								}else if(s[i] == ' '){
									/* Переход к следующему слову:
									1) Заканчиваем текущую строку в текущем массиве.
									2) Удлиняем текущий массив на 255 байт.
									3) Выделяем 255 байт для новой строки. */
									switch(current_array){
										case 0:
											article[current_word][current_symbol] = '\0';
											current_word++;
											article = (char **)realloc(article, 255*(current_word+1)*sizeof(char*));
											article[current_word]=(char*)malloc(255*sizeof(char));
											break;
										case 1:
											noun[current_word][current_symbol] = '\0';
											current_word++;
											noun = (char **)realloc(noun, 255*(current_word+1)*sizeof(char*));
											noun[current_word]=(char*)malloc(255*sizeof(char));
											break;
										case 2:
											verb[current_word][current_symbol] = '\0';
											current_word++;
											verb = (char **)realloc(verb, 255*(current_word+1)*sizeof(char*));
											verb[current_word]=(char*)malloc(255*sizeof(char));
											break;
										default:
											prep[current_word][current_symbol] = '\0';
											prep = (char **)realloc(prep, 255*(current_word+1)*sizeof(char*));
											prep[current_word]=(char*)malloc(255*sizeof(char));
									}
									current_symbol = 0;
								}else{
									/* Переход к следующему символу:
									1) Назначаем текущему массиву в текущем слове текущий символ.*/
									switch(current_array){
										case 0:
											article[current_word][current_symbol] = s[i];
											break;
										case 1:
											noun[current_word][current_symbol] = s[i];
											break;
										case 2:
											verb[current_word][current_symbol] = s[i];
											break;
										default:
											prep[current_word][current_symbol] = s[i];
									}
									current_symbol++;
								}
							}else break;
					} //for
				} //while
				//Сделаем то, то еще не сделали:
				prep[current_word][current_symbol] = '\0';
				prep_size = current_word + 1;

				int offer_count;
				cout << "Количество предложений: ";
				cin >> offer_count;

				for (int i = 0; i < offer_count; ++i){
					char offer[255];
						//sprintf_s() аналог printf(), но вывод делается в массив:
					sprintf_s(offer, "%s %s %s %s %s %s.",
						article[rand(article_size)], noun[rand(noun_size)], verb[rand(verb_size)],
						prep[rand(prep_size)], article[rand(article_size)], noun[rand(noun_size)]
					); 	
					offer[0] = toupper(offer[0]); //toupper() преобразует строчную букву в заглавную 
					cout << offer << endl;
				}
			break;	}


			case 3:	{
				cout << "3) Написать функцию palindrom.\nНа результат проверки не должны влиять знаки препинания, пробелы и разный регистр букв.\n";
					/*
						ввод: город дорог
						вывод: палиндром +
	
						ввод: А роза упала на лапу Азора
						вывод: палиндром +
		
						ввод: горох хорог
						вывод: палиндром +
		
						ввод: Волга
						вывод: не палиндром +
	
						ввод: Palindrom
						вывод: не палиндром +
					*/
				char* str = new char[255];
				cout << "Введите строку длиной до 255 символов: ";
				cin.getline(str, 255);
				if (palindrom(str))
					cout << "Палиндром\n";
				else
					cout << "Не палиндром\n";
			break;	}


			case 4:	{
				cout << "4) Подсчитать количество слов и предложений в текстовом файле.\n";
					/*
						ввод: По степи, не успевшей остыть за ночь, уже тянет опять тёплый ветер.
						вывод: Слов: 12, предложений: 1 +
	
						ввод: Лёд, неокрепший на речке студёной, словно как тающий сахар, лежит... Луна взошла багровая и хмурая, звезды тоже хмурились.
						вывод: Слов: 18, предложений: 2 +
					*/

				int count_a = 0, count_b = 0;
				ifstream  file("D:\\text.txt");
				if (!file){
					cout << "Ошибка при открытии файла.\n";
					break;
				}
				char s[255];
				while (file.getline(s, 255)){
					for (int i = 0; i < 255; i++){
						if(s[i] != '\0'){
							if (s[i] == ' ' && s[i-1] != '-'){
								count_a++;
							}
							if (s[i] == '.' || s[i] == '!' || s[i] == '?'){
								count_b++;
								i+=2; //+3 смещение, так как не может быть предложения из одного символа. А вот многоточия и подобное могут стоять в этом смещении. 
							}
						}else break; //конец файла
					}//for
				}//while
				
				count_a++; //Количество слов на +1 больше кол-ва пробелов.
				cout << "Количество слов в тексте равно " << count_a << endl;
				cout << "Количество предложений в тексте равно " << count_b << endl;
			break;	}

		} //switch
		cout << endl;
	} //while
} //main


int length(char* s){
	int i = 0;
	for (; s[i] != '\0'; i++);
	return i;
} //length


int rand(int max){
	return rand() % max;
} //rand


bool palindrom(char* text){
	for (int i = 0, j = strlen(text) - 1; i < j;)
	{
		if (isalpha((char) text[i]))
		{
			if (isalpha((char) text[j]))
			{
				if (tolower(text[i]) != tolower(text[j]))
					return 0;

				i++;
				j--;
			}
			else
				j--;
		}
		else
			i++; 
	}
	return 1;
} //palindrom