// 1.cpp: ���������� ����� ����� ��� ����������� ����������.
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
float array_sum(float *a, int n); //����� ���� ���������
float array_average(float *a, int n); //������� �������� ���� ���������
int array_firstnegative(float *a, int n); //���� ������� �������������� ��������
int array_min(float *a, int n); //���� ������������ ��������
int array_max(float *a, int n); //���� ������������� ��������

void minput_rand(int **a, int n, int m); //���� ������������� ������� ���������� �������
void moutput(int **a, int n, int m); //����� �������
int parameter_string(int **a, int i, int m); //������� �������������� ������ �������
int max_parameter_string(int **a, int n, int m); //������� ����� ������ � ������������ ���������������
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
		if(n>1)break;
		printf("������ ������ ���� ������ 1\n");
	}
	float *a = new float[n];
	input_rand(a, n);
	output(a, n);

	printf("\na) ������������� �������� ������, ������� �� ������� �������� ������� ��������.\n");
	float average = array_average(a, n);
	printf("C������ ��������: %.2f\n", average);
	for(int i=0; i<n; i++){
		a[i] -= average;
	}
	printf("����:\n");
	output(a, n);

	printf("\nb) �������� ������� ������������ � ������ ������������� �������� �������.\n");
	int keyfirst = array_firstnegative(a, n), keymax = array_max(a, n);
	if(keyfirst != -1){ //-1 - ������������� ����� ���.
		printf("���� ������� �������������� ��������: %d (%.2f)\n���� ������������� ��������: %d (%.2f)\n", keyfirst, a[keyfirst], keymax, a[keymax]);
		float temp = a[keyfirst];
		a[keyfirst] = a[keymax];
		a[keymax] = temp;
		printf("����:\n");
		output(a, n);
	}

	printf("\nc) ��������� ������� �������� ��������� �������, �������� ����������� � ������������ ��������.\n");
	int keymin = array_min(a, n);
	keymax = array_max(a, n);
	printf("���� ������������ ��������: %d (%.2f)\n���� ������������� ��������: %d (%.2f)\n", keymin, a[keymin], keymax, a[keymax]);
	if(n-2 == 0)average = 0; else
	average = (array_sum(a, n)-a[keymin]-a[keymax])/(n-2);
	printf("C������ �������� �������� �������: %.3f\n", average);
} //work1


void work2(){
	printf("\n2. ��������������� ������ ������������� ������� ������� ����� �� ������������� ������ ���������. ����� ����� ������ � ������������ ���������������.\n");
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
	int maxp = max_parameter_string(a, n, m);
	printf("����� ������ � ������������ ��������������� (������� � 0): %d\n\n", maxp);
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
	printf("������������� ����� �� �������.\n");
	return -1;
}

int array_min(float *a, int n){
	int keymin = 0;
	for(int i=1; i<n; i++){
		if(a[keymin] > a[i]){
			keymin = i;
		}
	}
	return keymin;
}

int array_max(float *a, int n){
	int keymax = 0;
	for(int i=1; i<n; i++){
		if(a[keymax] < a[i]){
			keymax = i;
		}
	}
	return keymax;
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
		//������ 2
		int p = parameter_string(a, i, m);
		printf("| = %d", p);
		printf("\n");
	}
	printf("   "); zline(m);
	printf("\n");
}

int parameter_string(int **a, int i, int m){
	int sum=0;
	for(int j=0; j<m; j+=2){
	if(a[i][j]>0)sum+=a[i][j];
	}
	return sum;
}
int max_parameter_string(int **a, int n, int m){
	int keyn = 0, maxp = parameter_string(a, 0, m);
	for(int i=1; i<n; i++){
		int p = parameter_string(a, i, m);
		if(maxp < p){
			keyn = i;
			maxp = p;
		}
	}
	printf("\n");
	return keyn;
}