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

int length(char* s); // Функция, определяющая длину строки
bool palindrom(char* text); // Функция, определяющая является ли строка палиндромом.
int rand(int max); // функция, генерирующая случайные числа до от 0 до max-1

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
				char* article[] = {"the", "a", "an"}; // задание слов в одномерный массив article[] (артикли)
				int article_size = sizeof(article) / sizeof(article[0]);

				char* noun[] = {"cat", "dog", "boy", "girl", "town"}; // задание слов в одномерный массив noun[] (существительные)
				int noun_size = sizeof(noun) / sizeof(noun[0]);

				char* verb[] = {"skipped", "drove", "jumped", "ran", "walked"}; // задание в слов одномерный массив verb[] (глаголы)
				int verb_size = sizeof(verb) / sizeof(verb[0]);

				char* prep[] = {"to", "from", "over", "under"}; // задание слов в одномерный массив preposition[] (предлоги)
				int prep_size = sizeof(prep) / sizeof(prep[0]);

				int offer_count;
				cout << "Количество предложений: ";
				cin >> offer_count;
				for (int i = 0; i < offer_count; ++i){
					char offer[256];
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
				char s[255];
				int l, count = 0, k = 0;
				ifstream  file("D:\\text.txt");
				if (!file){
					cout << "Ошибка при открытии файла.\n";
					break;
				}
				while (file.getline(s, 255)){
					int i = 0;
					while (s[i] == ' ' && s[i] != '\0'){
						i++;
					}
					l = 0;
					while (s[i] != '\0'){
						if (s[i] != ' ' && l == 0 && s[i] != '-'){
							l = 1;
							count++;
						} else if (s[i] == ' ') l = 0;
						i++;
					}
				}
				cout << "Количество слов в тексте равно " << count << endl;

				for (int i = 0; i < 255; i++){
					if (s[i] == '.' || s[i] == '!' || s[i] == '?'){
						k++;
						i+=2; //+3 смещение, так как не может быть предложения из одного символа. А вот многоточия и подобное могут стоять в этом смещении. 
					}
				}
				cout << "Количество предложений в тексте равно " << k << endl;
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
		if (isalpha((unsigned char)text[i]))
		{
			if (isalpha((unsigned char)text[j]))
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