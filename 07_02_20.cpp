// 1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"

//void input(int *a, int n);
void input_rand(int *a, int n);
void output(int *a, int n);
void zkey(int *a, int n);
void zline(int n);
void create_new_array(int *a, int *a2, int n);
int array_max(int *a, int n);
void output_max(int *a, int *a2, int n, int max);

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int n;
	printf("Размер массива: ");
	scanf_s("%d", &n);
	int *a = new int[n];
	zkey(a, n);
	zline(n);
	input_rand(a, n);
	output(a, n);
	int *a2 = new int[n];
	create_new_array(a, a2, n);
	output(a2, n);
	zline(n);

	int max = array_max(a2, n);
	printf("Max: %d\n", max);
	printf("\n");
	output_max(a, a2, n, max);
	return 0;
}

/*
void input(int *a, int n){
	for(int i=0; i<n; i++){
		printf("a[%d] = ", i);
		scanf_s("%d", &a[i]);
	}
}
*/

void input_rand(int *a, int n){
	for(int i=0; i<n; i++){
		a[i] = rand()%100+10;
	}
}

void output(int *a, int n){
	for(int i=0; i<n; i++){
		printf("%4d ", a[i]);
	}
	printf("\n");
}

void zkey(int *a, int n){
	for(int i=0; i<n; i++){
		printf("%4d ", i);
	}
	printf("\n");
}
void zline(int n){
	for(int i=0; i<n; i++){
		printf("-----");
	}
	printf("\n");
}

void create_new_array(int *a, int *a2, int n){
	for(int i=0; i<n; i++){
		int c = a[i];
		for(a2[i]=0; c>0 ; c/=10) a2[i]+=c%10;
	}
}

int array_max(int *a, int n){
	int max = 0, key;
	for(int i=0; i<n; i++){
		if(max < a[i]){
			max = a[i];
		}
	}
	return max;
}

void output_max(int *a, int *a2, int n, int max){
	for(int i=0; i<n; i++){
		if(max == a2[i]){
			printf("%d  %d\n", a[i], i);
		}
	}
}