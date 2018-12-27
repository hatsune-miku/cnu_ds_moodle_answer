
// \^o^/ 1171002076

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF INT_MAX
#define VERTEX_SIZE 20
#define ARC_SIZE 40
#define STR_SIZE 20

template <typename T>
class queue {
private:
	T* q;
	int front;
	int rear;
public:
	void init() {
		q = (T*)malloc(sizeof(T) * 3939);
		front = rear = 0;
	}
	void enq(T value) {
		q[rear++] = value;
	}
	T deq() {
		return q[front++];
	}
	bool empty() {
		return front == rear;
	}
};

typedef struct ArcNode {
	int adj;
	struct ArcNode* next;
} ArcNode;

typedef struct ArcPair {
	char key[STR_SIZE];
	char value[STR_SIZE];
} ArcPair;

typedef struct VertexNode {
	char value[STR_SIZE];
	ArcNode* first;
} VertexNode;

class MGraphNG {
private:
	VertexNode vertexList[VERTEX_SIZE];
	int nVertex;
	int nArc;
	int locateArcNode(char* key) {
		for (int i = 0; i < nVertex; i++)
			if (!strcmp(this->vertexList[i].value, key))
				return i;
		return 0;
	}
	ArcNode* newArcNode(int adj) {
		ArcNode* node = (ArcNode*)malloc(sizeof(ArcNode));
		node->adj = adj;
		node->next = NULL;
		return node;
	}
public:
	void ___biu___(void (*callback)(char*)) {
		queue<int> q;
		q.init();
		bool visited[VERTEX_SIZE] = { false };
		for (int i = 0; i < this->nVertex; i++) {
			if (!visited[i]) {
				visited[i] = true;
				callback(this->vertexList[i].value);
				q.enq(i);
				while (!q.empty()) {
					int u = q.deq();
					for (
						ArcNode* v = this->vertexList[u].first;
						v;
						v = v->next) {
						if (v->adj > 0 && !visited[v->adj]) {
							visited[v->adj] = true;
							callback(this->vertexList[v->adj].value);
							q.enq(v->adj);
						}
					}
				}
			}
		}
	}
	void init(
		int nVertex,
		int nArc,
		char vertex[VERTEX_SIZE][STR_SIZE],
		ArcPair arcs[ARC_SIZE]) {
		this->nVertex = nVertex;
		this->nArc = nArc;
		for (int i = 0; i < nVertex; i++) {
			strcpy(this->vertexList[i].value, vertex[i]);
			this->vertexList[i].first = NULL;
		}
		for (int i = 0; i < nArc; i++) {
			int index = locateArcNode(arcs[i].key);
			int adj = locateArcNode(arcs[i].value);
			ArcNode* node = newArcNode(adj);
			// concat
			if (!this->vertexList[index].first)
				this->vertexList[index].first = node;
			else {
				node->next = this->vertexList[index].first;
				this->vertexList[index].first = node;
			}
		}
	}
};

int main() {
	char vertex[VERTEX_SIZE][STR_SIZE];
	ArcPair pair[ARC_SIZE];
	int nVertex, nArc;
	
	scanf("%d%d", &nVertex, &nArc);
	for (int i = 0; i < nVertex; i++)
		scanf("%s%*c", vertex[i]);
	for (int i = 0; i < nArc; i++)
		scanf("%s %s%*c", pair[i].key, pair[i].value);

	MGraphNG g;
	g.init(nVertex, nArc, vertex, pair);
	g.___biu___([](char* value) {
		printf("%s ", value);
	});
	return 0;
}
