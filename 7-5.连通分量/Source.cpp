
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR_SIZE 16
#define _new(T,N) ((T*)malloc(sizeof(T)*N))

class Graph {
private:
	// graph structure.
	int** matrix;
	char** names;
	int vertex_count;

	// for dfs.
	bool* visited;
	char** serial;
	int num;

	// dfs.
	void dfs(int at) {
		visited[at] = true;
		strcat(serial[num], names[at]);
		strcat(serial[num], " ");
		for (int i = 0; i < vertex_count; i++) {
			if (matrix[at][i] != 0 && !visited[i])
				dfs(i);
		}
	}
public:
	// Graph()
	void init(FILE* from) {
		// read num, names and matrix from file.
		fscanf(from, "%d", &vertex_count);

		names = _new(char*, vertex_count);
		for (int i = 0; i < vertex_count; i++) {
			names[i] = _new(char, STR_SIZE);
			fscanf(from, "%s%*c", names[i]);
		}

		matrix = _new(int*, vertex_count);

		for (int i = 0; i < vertex_count; i++) {
			matrix[i] = _new(int, vertex_count);
			for (int j = 0; j < vertex_count; j++)
				fscanf(from, "%d", matrix[i] + j);
		}
	}
	// public dfs.
	void dfs_traverse(char*** serial, int* num) {
		this->num = 0;
		this->serial = _new(char*, vertex_count);
		visited = _new(bool, vertex_count);
		for (int i = 0; i < vertex_count; i++) {
			visited[i] = false;
			// bigger size?
			this->serial[i] = _new(char, 4 * STR_SIZE);
			memset(this->serial[i], 0, 4 * STR_SIZE * sizeof(char));
		}

		while (true) {
			int i;
			// run dfs for those who is not visited.
			for (i = 0; i < vertex_count; i++)
				if (!visited[i])
					break;
			if (i == vertex_count)
				break;
			dfs(i);
			this->num++;
		}
		// returns serials and num.
		*serial = this->serial;
		*num = this->num;
	}
};

int main() {
	Graph g;
	g.init(stdin);

	char** serial;
	int num;
	g.dfs_traverse(&serial, &num);

	printf("%d\n", num);
	for (int i = 0; i < num; i++)
		printf("%s\n", serial[i]);

	return 0;
}
