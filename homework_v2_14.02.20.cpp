// 2.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "locale.h"
#include "stdlib.h"
#include "time.h"

//void input(float *a, int n); //������ ���� �������
void input_rand(float *a, int n); //���� ������� ���������� �������
void output(float *a, int n); //����� �������
void zkey(int n); //������� ����� ������� (�� 0 �� n)
void zline(int n); //�����
float array_average(float *a, int n); //������� �������� ���� ���������
int min_rang(float *a, int n, int k); //������ ��������, �������� �������� �������� ������ � ��������� ����� k
int array_min_positive(float *a, int n); //���� ������������ �������� ����� ������������� ���������
float array_sum(float *a, int n); //����� ���� ��������� �� n
int array_firstnegative(float *a, int n); //���� ������� �������������� ��������

void minput_rand(int **a, int n, int m); //���� ������������� ������� ���������� �������
void moutput(int **a, int n, int m); //����� �������
int parameter_col(int **a, int j, int m); //������� �������������� ������� �������
int min_parameter_col(int **a, int n, int m); //������� ����� ������� � ������������ ���������������

void work1(); //������� 1
void work2(); //������� 2

int main(){
	setlocale(LC_ALL, "Russian");
	srand(time(0)); //������ ������� rand ��������� �� �������.
	printf("������������ ������ � 1 '���������� �������'\n������: 194-���\n�������: �������� �.�.\n�������������: �������� �.�.\n");
	work1();
	work2();

	return 0;
}


void work1(){
	int n;
	while(1){
		printf("1. ������ �������: ");
		scanf_s("%d", &n);
		if(n>0)break;
		printf("������ ������ ���� ������ 0\n");
	}
	float *a = new float[n];
	input_rand(a, n);
	output(a, n);

	printf("\na) ���������� ������ ��������, �������� �������� �������� ������ � �������� �������� ��������� �������.\n");
	float average = array_average(a, n);
	printf("C������ ��������: %.2f\n", average);
	int key = min_rang(a, n, average);
	printf("������ �������� �������� ������� � ����� �����: %d (%.2f)\n", key, a[key]);

	printf("\nb) ����� ����������� ������� ����� ������������� ��������� ��������� �������.\n");
	key = array_min_positive(a, n);
	if(key != -1){ //�������� �� ������������� ������������� ���������.
		printf("������ ������� ��������: %d (%.2f)\n", key, a[key]);
	}
	printf("\nc) ��������� ����� ��������� �������, ������������� �� ������� �������������� ��������.\n");
	int keyfirst = array_firstnegative(a, n); //���� ������� ��������������.
	if(keyfirst != -1){ //�������� �� ������������� ������������� ���������.
		float sum = array_sum(a, keyfirst); //������� �� keyfirst, �� ������ �������������
		printf("�����: %.2f\n", sum);
	}
} //work1


void work2(){
	printf("\n2. ��������������� ������� ������������� ������� ������� ����� ������� ��� ������������� �������� ���������. ����� ����� ������� � ����������� ���������������.\n");
	int n;
	while(1){
		printf("������� ���������� �����: ");
		scanf_s("%d", &n);
		if(n>1)break;
		printf("������ ���� ������ 1\n");
	}
	int m;
	while(1){
		printf("������� ���������� ��������: ");
		scanf_s("%d", &m);
		if(m>1)break;
		printf("������ ���� ������ 1\n");
	}
	int** a = new int*[n];
	for(int i=0; i<n; i++) a[i] = new int[m];
	minput_rand(a, n, m);
	moutput(a, n, m);
	int maxp = min_parameter_col(a, n, m);
	printf("\n����� ������� � ����������� ��������������� (������� � 0): %d\n\n", maxp);
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
	printf(" > ������������� ����� �� �������.\n");
	return -1;
}

int array_firstpositive(float *a, int n){
	for(int i=0; i<n; i++){
		if(a[i] >= 0){
			return i;
		}
	}
	printf(" > ������������� ����� �� �������.\n");
	return -1;
}

int min_rang(float *a, int n, int k){
	int keyminr = 0;
	for(int i=1; i<n; i++){
		if(abs(k - a[keyminr]) > abs(k - a[i])){
			keyminr = i;
		}
	}
	return keyminr;
}

int array_min_positive(float *a, int n){
	int keymin = array_firstpositive(a, n);
	if(keymin == -1) return -1;
	for(int i=keymin+1; i<n; i++){
		if(a[i] >= 0 && a[keymin] > a[i]){
			keymin = i;
		}
	}
	return keymin;
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
		printf("|\n");
	}
	printf("   "); zline(m);
	//������ 2
	printf("   ");
	for(int j=0; j<m; j++){
		int p = parameter_col(a, j, n);
		printf("%6d", p);
	}
	printf("\n");
}

int parameter_col(int **a, int j, int n){
	int sum=0;
	for(int i=1; i<n; i+=2){
	if(a[i][j]<0)sum+=abs(a[i][j]);
	}
	return sum;
}

int min_parameter_col(int **a, int n, int m){
	int keyn = 0, minp = parameter_col(a, 0, n);
	for(int j=1; j<m; j++){
		int p = parameter_col(a, j, n);
		if(minp > p){
			keyn = j;
			minp = p;
		}
	}
	return keyn;
}