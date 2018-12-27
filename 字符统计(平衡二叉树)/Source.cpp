
#include <stdio.h>
#include <stdlib.h>

struct avl_tree {
	struct avl_tree* left;
	struct avl_tree* right;
	int height;
	char label;
	int value;
};

typedef struct avl_tree bin_tree;

int max(int x, int y) {
	return x > y ? x : y;
}

int height_of(avl_tree* t) {
	if (!t)
		return 0;
	return t->height;
}

void rr_rotate(avl_tree*& t) {
	// exchange nodes.
	avl_tree* t_right_backup = t->right;
	t->right = t->right->left;
	t_right_backup->left = t;

	// update height.
	t->height = max(height_of(t->left), height_of(t->right));
	t_right_backup->height = max(
		height_of(t_right_backup->right), height_of(t)
	);

	t = t_right_backup;
}

void ll_rotate(avl_tree*& t) {
	// exchange nodes.
	avl_tree* t_left_backup = t->left;
	t->left = t->left->right;
	t_left_backup->right = t;

	// update height.
	t->height = max(height_of(t->left), height_of(t->right));
	t_left_backup->height = max(
		height_of(t_left_backup->left), height_of(t)
		);

	t = t_left_backup;
}

void lr_rotate(avl_tree*& t) {
	rr_rotate(t->left);
	ll_rotate(t);
}

void rl_rotate(avl_tree*& t) {
	ll_rotate(t->right);
	rr_rotate(t);
}

void insert(avl_tree*& t, int label) {
	if (!t) {
		// new tree.
		t = (avl_tree*)malloc(sizeof(avl_tree));
		t->left = t->right = NULL;
		t->height = 0;
		t->label = label;
		t->value = 1;
		return;
	}
	if (label < t->label) {
		// left smaller.
		insert(t->left, label);
		if (height_of(t->left) - height_of(t->right) == 2) {
			// need left balance.
			if (label < t->left->label)
				ll_rotate(t);
			else
				lr_rotate(t);
		}
	}
	else if (label > t->label) {
		// right bigger.
		insert(t->right, label);
		if (height_of(t->right) - height_of(t->left) == 2) {
			// need right balance.
			if (label < t->left->label)
				rl_rotate(t);
			else
				rr_rotate(t);
		}
	}
	else if (label == t->label) {
		// already exists. value++.
		t->value++;
	}
	// finally update height.
	t->height = max(height_of(t->left), height_of(t->right)) + 1;
}

void in_order(avl_tree* t, void (*v)(avl_tree*)) {
	if (!t)
		return;
	in_order(t->left, v);
	v(t);
	in_order(t->right, v);
}

int main() {
	avl_tree* t = NULL;
	char c;
	while ((c = getchar()) != 13 && c != 10)
		insert(t, c);
	in_order(t, [](avl_tree* n) {
		printf("%c:%d\n", n->label, n->value);
	});
	return 0;
}
