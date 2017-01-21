#include<stdio.h>
#include<stdlib.h>


int* stack;
int n;
int size;

int max(int a, int b);
void push(int a);
int pop();
int** BuildSolution(int count, int maxWeight, int* w, int* v);
int FindAnswer(int count, int** D, int maxWeight, int* w);
void DeleteTable(int** D, int count);


int main() {
	n = 0;
	int count;
	int maxWeight;
	printf("Enter the max weight of knapsack: \n");
	scanf("%d", &maxWeight); 
	printf("Enter the count of things: \n");
	scanf("%d", &count);
	int* w = (int*)malloc((count + 1) * sizeof(int));
	int* v = (int*)malloc((count + 1) * sizeof(int));
	int i;
	printf("Enter weight and value of each thing: \n");
	for (i = 1; i <= count; i++) {
		scanf("%d %d", &w[i], &v[i]);
	}
	int** D = BuildSolution(count, maxWeight, w, v);
	int total_weight = FindAnswer(count, D, maxWeight, w);
	printf("Total value : %d\n", D[count][maxWeight]);
	printf("You should take following things: \n");
	int index;
	while (n > 0) {
		int index = pop();
		printf("%d %d\n", w[index], v[index]);
	}
	printf("Total weight : %d\n", total_weight);

	DeleteTable(D, count);
	free(stack);
	return 0;
}
void DeleteTable(int** D, int count) {
	int i;
	for (i = 0; i <= count; i++) {
		free(D[i]);
	}
	free(D);
}
int max(int a, int b) {
	return (a > b ? a : b);
}
int** BuildSolution(int count, int maxWeight, int* w, int* v) {
	int** D = (int**)calloc((count + 1), sizeof(int*));
	int i;
	for (i = 0; i <= count; i++) {
		D[i] = (int*)calloc(maxWeight + 1, sizeof(int));
	}
	int j;
	for (i = 1; i <= count; i++) {
		for (j = 1; j <= maxWeight; j++) {
			if (j >= w[i]) {
				D[i][j] = max(D[i - 1][j], D[i - 1][j - w[i]] + v[i]);
			} else {
				D[i][j] = D[i - 1][j];
			}
		}
	}
	return D;
}
int FindAnswer(int count, int** D, int maxWeight, int* w) {
	int total_weight = 0;
	size = 100;
	stack = (int *)malloc(size * sizeof(int));
	int i;
	for (i = count; i > 0; i--) {
		if (D[i][maxWeight] != D[i - 1][maxWeight]) {
			push(i);
			total_weight += w[i];
			maxWeight -= w[i];
		}
	}
	return total_weight;
}
void push(int a) {
	if (n + 1 > size) {
		size *= 2;
		stack = (int *)realloc(stack, size * sizeof(int));
	}
	stack[n++] = a;
}
int pop() {
	return stack[--n];
}