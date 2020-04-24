/*
Файлы, которые необходимы для работы определенных заданий:
D:\text.txt - 2, 3. - текстовой файл с предложениями:
Do you like programming?
I love programming!
But sometimes i lose my head from love.
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

using namespace std;

int main(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(0));
	cout << "Практическая работа на тему 'строки':\n";
	int menu = 0;
	while(1){
		cout << "Введите номер задания (1-3) или 0 - для выхода:\n 1 - первое слово входного предложения,\n 2 - все слова текста, заканчивающиеся буквами o или g,\n 3 - обратный алфавитный порядок.\n";
		cin >> menu;
		cin.clear();
		cin.ignore();

		switch(menu){
			case 0:
				cout << "Выход.\n";
				return 0;
			break;


			case 1:	{
				cout << "1) Напишите функцию, которая возвращает первое слово входного предложения. Считаем, что слова разделены пробелами.\n";
					/*
						ввод: test
						вывод: длина строки равна 4 +
		
						ввод: Пятница
						вывод: длина строки равна 7 +
		
						ввод: 12312
						вывод: длина строки равна 5 +
					*/
				char* str = new char[255];
				cout << "Введите предложение длиной до 255 символов: ";
				cin.getline(str, 255);
				for (int i=0,j=strlen(str); i<j; i++){
					if (str[i] == ' ') break;;
					cout << str[i];
				}
			break;	}


			case 2:	{
				cout << "2) Выведите на экран все слова текста, заканчивающиеся буквами o или g.\n";
				ifstream  file("D:\\text.txt");
				if (!file){
					cout << "Ошибка при открытии файла.\n";
					break;
				}
				char s[255];
				bool input = true;
				char word[255];
				int wordint=0;
				while (file.getline(s, 255)){
					for (int i = 0; i < 255; i++){
						if(s[i] != '\0'){
							if(!input){
								if(isalpha(s[i])) input=true;
							}
							if(input){		
								if(s[i]==' ' || s[i]=='.'  || s[i]==',' || s[i]=='?' || s[i]=='!'){
									input=false;
									word[wordint] = '\0';
									if(word[wordint-1]=='o' || word[wordint-1]=='g') cout << word << endl;
									wordint=0; //строку обнулять не обязательно, т.к. нулевой байт.
								}else{
									word[wordint]=s[i];
									wordint++;
								}
							} //input
						}else break; //конец файла
					}//for
				}//while
			break;	}


			case 3:	{
				cout << "3) Упорядочите слова последнего предложения текста из задания 2 в порядке, обратном алфавитному.\n";
				ifstream  file("D:\\text.txt");
				if (!file){
					cout << "Ошибка при открытии файла.\n";
					break;
				}
				char s[255];
				bool input = false;
				char word[255];
				int wordint=0;
				int count_word = 0;
				char** words = (char**)malloc(sizeof(char*));
				int count = 2; //номер последнего предложения или того предложения, слова в котором надо переставить.
				char w; //точка или другой знак, который будет стоять в новом предложении.
				while (file.getline(s, 255)){
					for (int i = 0; i < 255; i++){
						if(s[i] != '\0'){
							if(count != 0)cout << s[i];
							if(s[i]=='.' || s[i]=='?' || s[i]=='!'){
								if(count != 0) cout << '\n'; else w=s[i];
								count--; }
							if(count != 0)continue;
							if(!input){
								if(isalpha(s[i])) input=true;
							}
							if(input){		
								if(s[i]==' ' || s[i]=='.' || s[i]==',' || s[i]=='?' || s[i]=='!'){
									input=false;
									word[wordint] = '\0';
									words = (char **)realloc(words, 255*(count_word+1)*sizeof(char*));
									words[count_word] = (char*)malloc(255*sizeof(char));
									for(int j=0; j<=wordint; j++)words[count_word][j] = word[j];
									count_word++;
									wordint=0; //строку обнулять не обязательно, т.к. нулевой байт.
								}else{
									word[wordint]=tolower(s[i]);
									wordint++;
								}
							} //input
						}else break; //конец файла
					}//for
				}//while

				for(int i = 0 ; i < count_word; i++){
					for(int j = i+1; j < count_word; j++){
						if(strcmp(words[i], words[j]) < 0){
				          char* tmp = words[i];
				          words[i] = words[j];
				          words[j] = tmp;
						}
				    }
				}
				words[0][0]=toupper(words[0][0]);
				for (int i = 0; i < count_word; i++) { 
					for(int j=0,len=strlen(words[i]); j<len; j++) cout << words[i][j];
					if(i==count_word-1) cout << w; else cout << ' ';
				}
			break;	}

		} //switch
		cout << endl;
	} //while
} //main