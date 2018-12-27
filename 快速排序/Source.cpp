
// \^o^/ 1171002076

#define _CRT_SECURE_NO_WARNINGS

#define tpok main

#include <stdio.h>
#include <stdlib.h>

int* arr;
int n;

void swap(int& a, int& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

void array_print(int* arr, int n) {
	while (n--)
		printf("%4d", *(arr++));
	putchar('\n');
}

void quick_sort(int l, int r) {
	if (l > r)
		return;
	int key = arr[l];
	if (l != r)
	 	printf("%4d", key);
	int lp = l, rp = r;
	while (lp < rp) {
		while (lp < rp && arr[rp] >= key)
			rp--;
		arr[lp] = arr[rp]; // to adapt problem.
		while (lp < rp && arr[lp] <= key)
			lp++;
		arr[rp] = arr[lp];
	}
	arr[lp] = key;
	quick_sort(l, lp - 1);
	quick_sort(lp + 1, r);
}

int tpok() {
	scanf("%d", &n);
	arr = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		scanf("%d", arr + i);
	quick_sort(0, n - 1);
	putchar('\n');
	for (int i = 0; i < n; i++)
		printf("%4d", arr[i]);
	free(arr);
	return 0;
}
