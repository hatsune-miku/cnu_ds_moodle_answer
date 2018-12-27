
// \^o^/ 1171002076

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 256
#define INF INT_MAX

class Graph {
private:
	bool* visited;
public:
	char** points;
	int** matrix;
	int size;
	void init(int size) {
		this->size = size;
		points = (char**)malloc(sizeof(char*) * size);
		matrix = (int**)malloc(sizeof(int*) * size);
		visited = (bool*)malloc(sizeof(bool*) * size);
		memset(visited, 0, sizeof(bool) * size);
		for (int i = 0; i < size; i++) {
			points[i] = (char*)malloc(sizeof(char) * STR_SIZE);
			matrix[i] = (int*)malloc(sizeof(int) * size);
		}
	}

	int firstPoint(int at) {
		return nextPoint(at, -1);
	}

	int nextPoint(int at, int offset) {
		for (int i = offset + 1; i < size; i++)
			if (matrix[at][i] == 0)
				return i;
		return -1;
	}

	void dfs(int at) {
		visited[at] = true;
		printf("%s ", points[at]);
		for (int p = 0; p < size; p++) {
			if (!visited[p] && matrix[at][p] != 0)
				dfs(p);
		}
	}

	void biu() {
		for (int i = 0; i < size; i++)
			visited[i] = false;
		for (int i = 0; i < size; i++) {
			if (!visited[i])
				dfs(i);
		}
	}

	void readPoints(FILE* from) {
		for (int i = 0; i < size; i++)
			fscanf(from, "%s%*c", points[i]);
	}

	void readMatrix(FILE* from) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				fscanf(from, "%d", matrix[i] + j);
	}

	void destruct() {
		if (points) {
			for (int i = 0; i < size; i++)
				free(points[i]);
			free(points);
		}
		if (matrix) {
			for (int i = 0; i < size; i++)
				free(matrix[i]);
			free(matrix);
		}
		points = NULL;
		matrix = NULL;
		visited = NULL;
	}
};

int main() {
	int size;
	Graph graph;

	scanf("%d", &size);

	graph.init(size);
	graph.readPoints(stdin);
	graph.readMatrix(stdin);
	graph.biu();

	graph.destruct();
	return 0;
}
