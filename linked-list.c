#include <stdio.h>
#include <stdlib.h>

struct edge;

struct vertex {
	int value;
	struct edge *edgelist;
};

// linked list which stores pointers to the vertices;
struct edge {
	struct vertex *node;
	struct edge *next;
};

// gives you the length of edge list
int length(struct edge *head) {
	struct edge *temp;
	int out;
	for (temp = head, out = 0; temp != NULL; temp = temp->next, out++)
		;
	return out;
}

// add vertex2 to the edge list vertex1
void add_edge(struct vertex *vert1, struct vertex *vert2) {
	struct edge *temp;
	if (vert1->edgelist == NULL) {
		temp = (struct edge *)malloc(sizeof(struct edge));
		vert1->edgelist = temp;
		vert1->edgelist->node = vert2;
	} else {
		for (temp = vert1->edgelist; temp->next != NULL; temp = temp->next)
			;
		temp->next = (struct edge *)malloc(sizeof(struct edge));
		temp->next->node = vert2;
	}
}

// create a new vertex with value 'val'
struct vertex *new_vertex(int val) {
	struct vertex *temp;
	temp = (struct vertex *)malloc(sizeof(struct vertex));
	temp->value = val;
	return temp;
}

// create a bi-directional edge between vert1 and vert2
void new_edge(struct vertex *vert1, struct vertex *vert2) {
	add_edge(vert1, vert2);
	add_edge(vert2, vert1);
}

// create a new vertex adjacent to 'vert' with value 'val'
struct vertex *new_vertex_to(struct vertex *vert, int val, int biedge) {
	struct vertex *temp;
	temp = new_vertex(val);
	if (biedge == 1)
		new_edge(vert, temp);
	else
		add_edge(vert, temp);
	return temp;
}

// display the value of adjacent vertices of a given vertex
void disp_adj_vert(struct vertex *vert) {
	int val;
	for (struct edge *temp = vert->edgelist; temp != NULL; temp = temp->next) {
		val = temp->node->value;
		printf("%d->", val);
	}
	printf("\b\b\n");
}

int main() {
	struct vertex *base, *v1, *v2;
	base = new_vertex(0);
	v1 = new_vertex(1);
	v2 = new_vertex(2);
	new_edge(base, v1);
	new_edge(v1, v2);
	new_edge(v2, base);
	disp_adj_vert(base);
	disp_adj_vert(v1);
	disp_adj_vert(v2);
	new_vertex_to(base, 3, 1);
	disp_adj_vert(base);
	return 0;
}
