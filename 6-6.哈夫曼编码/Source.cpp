// \*^O^/  1171002076
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define _new(T,C) ((T*)malloc(sizeof(T)*C))
#define _delete free
#define INT_MAX (2147483647)

typedef struct {
	int weight;
	int left;
	int right;
	int parent;
} huffman_node;

void select(huffman_node* tree, int n, int* min0, int* min1) {
	int weight_min0 = INT_MAX, weight_min1 = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (tree[i].parent != 0)
			continue;
		if (tree[i].weight < weight_min0) {
			*min1 = *min0;
			weight_min1 = weight_min0;
			*min0 = i;
			weight_min0 = tree[i].weight;
		}
		else if (tree[i].weight < weight_min1) {
			*min1 = i;
			weight_min1 = tree[i].weight;
		}
	}
}

void huffman_new(huffman_node* tree, int* weights, int n) {
	int m = 2 * n - 1;

	for (int i = 0; i < n; i++)
		tree[i] = { weights[i], 0, 0, 0 };
	for (int i = n; i < m; i++)
		tree[i] = { 0, 0, 0, 0 };

	for (int i = n; i < m; i++) {
		int min0, min1;
		select(tree, i, &min0, &min1);
		tree[min0].parent = i;
		tree[min1].parent = i;
		tree[i].left = min0;
		tree[i].right = min1;
		tree[i].weight = tree[min0].weight + tree[min1].weight;
	}
}

void huffman_coding(huffman_node* tree, char* names, int n) {
	for (int i = 0; i < n; i++) {
		printf("%c:", *(names++));
		char* serial = _new(char, 16);
		int len = 0;
		for (
			int cur = i, parent = tree[cur].parent;
			parent != 0;
			cur = parent, parent = tree[parent].parent) {
			if (cur == tree[parent].left)
				serial[len++] = '0';
			else
				serial[len++] = '1';
		}
		for (int i = len - 1; i >= 0; i--)
			putchar(serial[i]);
		_delete(serial);
		putchar('\n');
	}
}

int main() {
	int n;
	scanf("%d", &n);
	huffman_node* tree = _new(huffman_node, 2 * n - 1);
	char* names = _new(char, n);
	int* weights = _new(int, n);

	for (int i = 0; i < n; i++)
		scanf("%d", weights + i);
	getchar();
	for (int i = 0; i < n; i++)
		scanf("%c", names + i);

	huffman_new(tree, weights, n);
	huffman_coding(tree, names, n);

	_delete(weights);
	_delete(names);
	_delete(tree);
	return 0;
}
