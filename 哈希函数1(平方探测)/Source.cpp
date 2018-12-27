
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define EMPTY	(-393939)

typedef struct {
	int key;
} hash_cell;

typedef struct {
	hash_cell* cells;
	int count;
	int capacity;
} hash_table;

hash_table* hash_init(int size) {
	hash_table* ret = (hash_table*)malloc(sizeof(hash_table));
	hash_cell* cells = (hash_cell*)malloc(size * sizeof(hash_cell));
	ret->count = 0;
	ret->capacity = size;
	ret->cells = cells;
	for (int i = 0; i < size; i++)
		ret->cells[i].key = EMPTY;
	return ret;
}

int hash_calc(int key) {
	return key % 17;
}

int hash_find(hash_table* t, int key) {
	int p = hash_calc(key);
	int np = p;
	int d = 0;
	bool nod = true;
	// general search process.
	// for add, it returns an empty place.
	// for del, it returns an existing position.
	while (t->cells[np].key != EMPTY
		&& t->cells[np].key != key) {
		// need adjust.
		if (nod)
			np = (p + d * d) % t->capacity;
		else {
			np = (p - d * d) % t->capacity;
			d++;
		}
		nod = !nod;
	}
	return np;
}

bool hash_add(hash_table* t, int key) {
	int p = hash_find(t, key);

	if (t->cells[p].key != EMPTY) {
		// already exists.
		return false;
	}

	// perform add.
	t->cells[p].key = key;
	t->count++;
	return true;
}

bool hash_del(hash_table* t, int key) {
	int p = hash_find(t, key);

	if (t->cells[p].key == EMPTY) {
		// do not exist.
		return false;
	}

	// perform delete.
	t->cells[p].key = EMPTY;
	t->count--;
	return true;
}

void hash_print(hash_table* t) {
	for (int i = 0; i < t->capacity; i++) {
		if (t->cells[i].key != EMPTY)
			printf("%4d", t->cells[i].key);
		else
			printf("****");
	}
}

int main() {
	int n, x, t1, t2, y;

	scanf("%d", &n);

	int key;
	hash_table* table = hash_init(18);

	for (int i = 0; i < n; i++) {
		scanf("%d", &key);
		hash_add(table, key);
	}

	scanf("%d%d%d%d", &x, &t1, &t2, &y);

	int pos_x = hash_find(table, x);
	// is it an empty place?
	if (table->cells[pos_x].key == EMPTY)
		pos_x = -1;
	printf("%d\n", pos_x);

	hash_del(table, t1);
	hash_del(table, t2);
	hash_add(table, y);

	hash_print(table);

	return 0;
}
