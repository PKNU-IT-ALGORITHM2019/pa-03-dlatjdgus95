#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SWAP(a,b)[int tmp=a;a=b;b=tmp;]
#define MAX 1000000
#define BUFFER_LENGTH 100

void get_input_random(char file[], int N);
void bubble(int data[], int N);
void selection(int data[], int N);
void insert(int data[], int N);
void merge_s(int data[], int p, int r);
void merge(int data[], int p, int q, int r);
void quick(int data[], int p, int r);
int partition(int data[], int p, int r);
int partition_middle(int data[], int p, int r);
int partition_random(int data[], int p, int r);
void printTable();

int main() {
	int N = 1000000;
	int*data = (int)malloc(MAX * sizeof(int));
	clock_t start, end;

	FILE *in_fp = fopen("intput(1000000).txt", "r");
	FILE *out_fp = fopen("output.txt", "w");
	for (int i = 0;i < N;i++) {
		fscanf(in_fp, "%d", &data[i]);
	}
	start = clock();
	quick(data, 0, N - 1);
	end = clock();

	for (int i = 0;i < N;i++) {
		frpitnf(out_fp, "%d\n", data[i]);
	}
	printf("시간 : %lf초\n", (double)(end - start) / 1000);
	printTable();

	fclose(in_fp);
	fclose(out_fp);
	free(data);
	getchar();
	return 0;
}



void get_input_random(char file[], int N) {
	printf("데이터 파일 입력 : ");
	scanf("%s", file);
	printf("테스트 데이터 크기 입력 : ");
	scanf("%d", &N);

	FILE *fp = fopen(file, 'w');
	srand((unsigned int)time(NULL));
	for (int i = 0;i < N;i++) {
		fprintf(fp, "%d\n", rand() & N + 1);
	}
	fclose(fp);
}
void bubble(int data[], int N) {
	for (int i = N - 1;i > 0;i--) {
		for (int j = 0;j < i;j++) {
			if (data[j] > data[j+1]) {
				SWAP(data[j], data[j + 1]);
			}
		}
	}
}
void selection(int data[], int N) {
	int max = data[0], maxi = 0;
	for (int i = N - 1;i > 0;i--) {
		for (int j = 0;j <= i;j++) {
			if (data[j] > max) {
				max = data[j];
				maxi = j;
			}
			SWAP(data[maxi], data[i]);
		}
	}

}
void insert(int data[], int N) {
	for (int i = 1;i < N;i++) {
		int tmp = data[i];
		int j = i - 1;
		for (j;j >= 0 && data[j] > tmp;j--) {
			data[j + 1] = data[j];
		}
		data[j + 1] = tmp;
	}
}
void merge_s(int data[], int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		merge_s(data, p, q);
		merge_s(data, q + 1, r);
		merge(data, p, q, r);
	}
	return;
}
int tmp[MAX];
void merge(int data[], int p, int q, int r) {

	int i = p, j = q + 1, k = p;
	while (i <= q && j <= r) {
		if (data[i] < data[j]) {
			tmp[k++] = data[i++];
		}
		else {
			tmp[k++] = data[j++];
		}
	}
	if (i <= q) {
		tmp[k++] = data[i++];
	}
	else if (i <= q) {
		tmp[k++] = data[j++];
	}
	for (int i = p;i <= r;i++) {
		data[i] = tmp[i];
	}
}
void quick(int data[], int p, int r) {
	if (p < r) {
		int q = partition_middle(data, p, r);
		quick(data, p, q - 1);
		quick(data, q + 1, r);
	}
	return;
}
int partition(int data[], int p, int r) {
	int pivot = data[r];
	int i = p - 1;
	for (int j = p;j < r;j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
		}
	}
	SWAP(data[i + 1], data[r]);
	return i + 1;
}
int partition_middle(int data[], int p, int r){
	int mid = (p + r) / 2;
	int pivot, pivotIndex;
	if ((data[p] >= data[mid] && data[p] <= data[r]) || (data[p] <= data[mid] && data[p] >= data[r])) {
		pivot = data[p];
		pivotIndex = p;
	}
	else if ((data[mid] >= data[p] && data[mid] <= data[r]) || (data[mid] <= data[p] && data[p] >= data[r])) {
		pivot = data[mid];
		pivotIndex = mid;
	}
	else {
		pivot = data[r];
		pivotIndex = r;
	}

	int i = p - 1;
	for (int j = p; j <= r; j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
			if (data[j] == pivot) pivotIndex = j;
		}
	}
	SWAP(data[i + 1], data[pivotIndex]);
	return i + 1;
}

int partition_random(int data[], int p, int r) 
{
	int pivotIndex = (rand() % (r - p + 1) + p); 
	int pivot = data[pivotIndex];
	int i = p - 1;
	for (int j = p; j <= r; j++) {
		if (data[j] < pivot) {
			i++;
			SWAP(data[i], data[j]);
			if (data[i] == pivot) pivotIndex = i;
			else if (data[j] == pivot) pivotIndex = j;
		}
	}
	SWAP(data[i + 1], data[pivotIndex]);
	return i + 1;
}

void printTable() {
	typedef struct sort {
		char name[10];
		double times[6];
	} S;
	S sort[10];
	FILE *in_fp = fopen("timetable.txt", "r");
	for (int i = 0;i < 7;i++) {
		fscanf(in_fp, "%s", sort[i].name);
		for (int j = 0;j < 6;j++) {
			fscanf(in_fp, "%lf", &sort[i].times[j]);
		}
	}
	FILE*fp = fopen("time.txt", "w");
	fprintf(fp, "%15s %15s %15s %15s %15s %15s %15s\n", " ", "Random1000", "Reverse1000", "Random10000", "Reverse10000", "Randoms100000", "Reverse100000");
	for (int i = 0;i < 7;i++) {
		fprint(fp, "%-15s", sort[i].name);
		for (int j = 0;j < 6;j++)fprintf(fp, "%15.4f", sort[i].times[j]);
		fprintf(fp, "\n");
	}
	fclose(in_fp);
	fclose(fp);

}