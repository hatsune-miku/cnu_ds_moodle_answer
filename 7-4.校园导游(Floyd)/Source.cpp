
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

int n;
vertex v[VERTEX_LIMIT];
int matrix[VERTEX_LIMIT][VERTEX_LIMIT];

int floyd_biu(int src, int dst) {
	if (src == dst)
		return 0;
	
	// weight from src to A.
	int matrix_super[VERTEX_LIMIT][VERTEX_LIMIT];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix_super[i][j] = matrix[i][j];
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (matrix_super[i][j] >
					matrix_super[i][k] + matrix_super[k][j])
					matrix_super[i][j] =
					matrix_super[i][k] + matrix_super[k][j];
			}
		}
	}
	return matrix_super[src][dst];
}

int index_of(char* name) {
	for (int i = 0; i < n; i++)
		if (!strcmp(v[i].name, name))
			return i;
	return -1;
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

	char name_src[STR_SIZE], name_dst[STR_SIZE];
	scanf("%s%*c%s%*c", name_src, name_dst);

	// start prim from last vertex.
	int min_weight = floyd_biu(index_of(name_src), index_of(name_dst));

	printf("%d", min_weight);

	return 0;
}
