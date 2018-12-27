
// \^o^/ 1171002076

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// macros.
#define _new(T)		((T*)malloc(sizeof(T)))
#define _delete		free
#define STR_SIZE	(128)
#define CHILD_LIMIT	(64)
#define QUEUE_SIZE	(128)

// structs.
struct file_node {
	char name[STR_SIZE];
	int child_count;
	int is_dir;
	struct file_node* childs[CHILD_LIMIT];
};

struct queue {
	void* arr[QUEUE_SIZE];
	int front;
	int back;
};

typedef struct file_node file_node;
typedef struct queue queue;

// utils.
file_node* file_node_new(const char* name, int is_dir) {
	file_node* ret = _new(file_node);
	strcpy(ret->name, name);
	ret->is_dir = is_dir;
	ret->child_count = 0;
	return ret;
}

file_node* file_node_add(file_node* n, const char* name, int is_dir) {
	file_node* ret = file_node_new(name, is_dir);
	n->childs[n->child_count++] = ret;
	return ret;
}

queue* queue_new() {
	queue* ret = _new(queue);
	ret->front = ret->back = 0;
	return ret;
}

void queue_push_back(queue* q, void* v) {
	q->arr[q->back++] = v;
	if (q->back == QUEUE_SIZE)
		q->back = 0;
}

void* queue_pop_front(queue* q) {
	void* ret = q->arr[q->front++];
	if (q->front == QUEUE_SIZE)
		q->front = 0;
	return ret;
}

int queue_empty(queue* q) {
	return q->front == q->back;
}

void readline(char* str, char stop_at, int includes) {
	while ((*(str++) = getchar()) != stop_at);
	if (!includes) str--;
	*str = '\0';
}

// global vars.
file_node* root;


// program.
void analyze_dir(queue* parents, char* str) {
	// parent queue.
	queue* new_parents = queue_new();
	file_node* current_parent = (file_node*)queue_pop_front(parents);

	char name[STR_SIZE];
	int len = 0;

	while (1) {
		if (*str == '(') {
			str++;
			continue;
		}
		if (*str == '\n')
			break;
		if (*str == ')' || *str == ' ') {
			name[len] = '\0';
			len = 0;
			if (strcmp(name, "") != 0) {
				// only when name is not empty.
				if (name[0] == '*') {
					// is a directory.
					// that is terrible.
					file_node* new_parent = file_node_add(current_parent, name, 1);
					queue_push_back(new_parents, new_parent);
				}
				else {
					// is a file.
					// very good.
					file_node_add(current_parent, name, 0);
				}
			}
			if (*str == ')') {
				// next dir belongs to next parent.
				current_parent = (file_node*)queue_pop_front(parents);
			}
		}
		else {
			name[len++] = *str;
		}
		str++;
	}

	if (!queue_empty(new_parents)) {
		char next_line[STR_SIZE];
		readline(next_line, '\n', 1);
		analyze_dir(new_parents, next_line);
	}
	_delete(new_parents);
}

void tab(int depth) {
	while (depth--)
		printf("%-12s", "|-");
}

void file_tree_print(file_node* root, int depth) {
	tab(depth);
	printf("%-12s\n", root->name);
	if (!root->is_dir)
		return;
	for (int i = 0; i < root->child_count; i++)
		file_tree_print(root->childs[i], depth + 1);
}

int interpret() {
	char str[STR_SIZE], *p = str;
	readline(str, '\n', 0);
	
	if (!strcmp(str, "**"))
		return 0;

	if (*p == '*') {
		// is a directory.
		file_node* parent = file_node_add(root, str, 1);
		queue* parents = queue_new();
		queue_push_back(parents, parent);

		char next_line[STR_SIZE];
		readline(next_line, '\n', 1);
		analyze_dir(parents, next_line);

		_delete(parents);
	}
	else {
		// is a file.
		file_node_add(root, str, 0);
	}
	return 1;
}

int main() {
	// init dir '/'.
	root = file_node_new("/", 1);
	while (interpret());
	// tab(1);
	printf("%-12s", "|-*");
	file_tree_print(root, 0);
	return 0;
}
