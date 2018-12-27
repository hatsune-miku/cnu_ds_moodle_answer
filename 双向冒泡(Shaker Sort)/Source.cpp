
// cnuw234 - maze alter solution
// 1171002076 \^o^/

#define _CRT_SECURE_NO_WARNINGS

#define tpok main

#include <stdio.h>
#include <stdlib.h>

void swap(int& a, int& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void shaker_sort(int* arr, int n, int* t) {
	int l = 0, r = n - 1, last = 0;
	while (l < r) {
		for (int i = l; i < r; i++) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				(*t)++;
				last = i;
			}
		}
		r = last;
		for (int i = r - 1; i >= l; i--) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				(*t)++;
				last = i;
			}
		}
		l = last;
	}
}

int tpok() {
	int* arr;
	int n, t = 0;
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);
	shaker_sort(arr, n, &t);
	printf("%4d\n", t);
	for (int i = 0; i < n; i++)
		printf("%4d", arr[i]);
	free(arr);

	return 0;
}
