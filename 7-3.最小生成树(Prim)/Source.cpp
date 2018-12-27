
// \^o^/ 1171002076

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// macros.
#define INF				(999)
#define STR_SIZE		(16)
#define VERTEX_LIMIT	(32)

typedef struct {
	char name[STR_SIZE];
} vertex;

int n, nn;
vertex v[VERTEX_LIMIT];
int matrix[VERTEX_LIMIT][VERTEX_LIMIT];

void prim_biu(int from) {
	if (from < 0 || from >= n)
		return;

	// does the i-TH NODE visited?
	int visited[VERTEX_LIMIT];

	// min weight from CURRENT TREE to THE i-TH NODE.
	int distance[VERTEX_LIMIT];

	// which node has the min weight to the i-TH NODE?
	int parents[VERTEX_LIMIT];

	// init.
	for (int i = 0; i < n; i++) {
		distance[i] = matrix[from][i];
		parents[i] = from;
		visited[i] = 0;
	}
	visited[from] = 1;

	for (int i = 0; i < n; i++) {
		// where to go next?
		int next, min_weight = INF;
		for (int j = 0; j < n; j++) {
			if (visited[j] == 0
				&& distance[j] < min_weight) {
				min_weight = distance[j];
				next = j;
			}
		}
		if (min_weight == INF) {
			// constructed.
			return;
		}
		// go to next.
		visited[next] = 1;
		printf("%s %s\n", v[parents[next]].name, v[next].name);

		// the affect that next brought.
		for (int j = 0; j < n; j++) {
			if (visited[j] == 0
				&& matrix[next][j] < distance[j]) {
				parents[j] = next;
				distance[j] = matrix[next][j];
			}
		}
	}
}

int main() {
	// input vertex count.
	scanf("%d", &n);

	// input names.
	for (int i = 0; i < n; i++)
		scanf("%s%*c", v[i].name);

	// input matrix.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", matrix[i] + j);

	// start prim from last vertex.
	prim_biu(n - 1);

	return 0;
}
