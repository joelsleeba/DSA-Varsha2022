#include <stdio.h>
#include <stdlib.h>

struct vertex;
struct vertexList;
struct Graph;

int length(struct vertexList *head);
struct vertexList *tail(struct vertexList *head);
struct vertexList *append(struct vertexList *head1, struct vertexList *head2);
struct vertexList *enqueue(struct vertexList *head, struct vertex *vert);
struct vertex *dequeue(struct vertexList *head);
int is_vertex_in(struct vertex *vert, struct vertexList * head);
int is_adjacent(struct vertex *vert1, struct vertex *vert2);
void add_edge(struct vertex *vert1, struct vertex *vert2);
struct vertex *new_vertex(int val);
void new_edge(struct vertex *vert1, struct vertex *vert2);
struct vertex *new_vertex_to(struct vertex *vert, int val, int biedge);
int BFS(struct vertex *vert1, struct vertex *vert2);

// vertex of a graph
struct vertex {
	int value;
	struct vertexList *adjacentList;
};

// linked list which stores pointers to the vertices;
struct vertexList {
	struct vertex *node;
	struct vertexList *next;
};

// Graph
struct Graph {
	int order;
	struct vertexList *vertices;
};

// gives you the length of edge list
int length(struct vertexList *head) {
	struct vertexList *temp;
	int out;
	for (temp = head, out = 0; temp != NULL; temp = temp->next, out++)
		;
	return out;
}

// returns the tail of a linked list
struct vertexList *tail(struct vertexList *head) {
	struct vertexList *temp;
	for (temp = head; temp->next != NULL; temp = temp->next)
		;
	return temp;
}

// append 'head2' to 'head1' and return the start of the list
struct vertexList *append(struct vertexList *head1, struct vertexList *head2) {
	struct vertexList *temp;
	temp = tail(head1);
	temp->next = head2;
	return head1;
}

// enqueue into the linked list which stores the vertices
struct vertexList *enqueue(struct vertexList *head, struct vertex *vert) {
	struct vertexList *temp, *end;
	temp = (struct vertexList *)malloc(sizeof(struct vertexList));
	temp->node = vert;
	if (head == NULL) {
		head = temp;
	} else {
	    tail(head)->next = temp;
	}
	return head;
}

// dequeue from the linked list which stores the vertices
struct vertex *dequeue(struct vertexList *head) {
	struct vertexList *temp;
	struct vertex *vert;
	temp = head;
	vert = temp->node;
	head = head->next;
	free(temp);
	return vert;
}

// check if a given vertex 'vert' is in a linked list starting at 'head'
int is_vertex_in(struct vertex *vert, struct vertexList * head) {
	struct vertexList *temp;
	for (temp = head; temp != NULL; temp = temp->next) {
		if (temp->node == vert) {
			return 1;
		}
	}
	return 0;
}

// check if two vertices are connnected
int is_adjacent(struct vertex *vert1, struct vertex *vert2) {
	return is_vertex_in(vert2, vert1->adjacentList);
}

// add vertex2 to the edge list vertex1
void add_edge(struct vertex *vert1, struct vertex *vert2) {
	struct vertexList *temp;
	if (vert1->adjacentList == NULL) {
		temp = (struct vertexList *)malloc(sizeof(struct vertexList));
		vert1->adjacentList = temp;
		vert1->adjacentList->node = vert2;
	} else {
		for (temp = vert1->adjacentList; temp->next != NULL; temp = temp->next)
			;
		temp->next = (struct vertexList *)malloc(sizeof(struct vertexList));
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
	for (struct vertexList *temp = vert->adjacentList; temp != NULL; temp = temp->next) {
		val = temp->node->value;
		printf("%d->", val);
	}
	printf("\b\b\n");
}

// do a Breadth First Search for the given vertex starting from a given vertex
// Returns 1 if 'vert2' is a descendent of 'vert1'
int BFS(struct vertex *vert1, struct vertex *vert2) {
	struct vertexList *visited, *path, *tempList1, *tempList2;
	struct vertex *tempNode1, *tempNode2;
	enqueue(visited, vert1);
	for(tempList1 = visited; tempList1 != NULL; tempList1 = tempList1->next){
		tempNode1 = tempList1->node;
		for(tempList2 = tempNode1->adjacentList; tempList2 != NULL; tempList2 = tempList2->next){
			tempNode2 = tempList2->node;
			if (tempNode2 == vert2){
				return 1;
			}
			if (!is_vertex_in(tempNode2, visited)){
				enqueue(visited, tempNode2);
			}
		}
	}
	return 0;
}

int main() {
	struct vertex *base, *v1, *v2, *v3;

	// create vertices
	base = new_vertex(0);
	v1 = new_vertex(1);
	v2 = new_vertex(2);
	v3 = new_vertex(33);

	// connect the vertices
	new_edge(base, v1);
	new_edge(v1, v2);
	new_edge(v2, base);
	new_edge(v1, v3);

	// display the adjacents vertices
	disp_adj_vert(base);
	disp_adj_vert(v1);
	disp_adj_vert(v2);

	// testing new method to create vertices
	new_vertex_to(base, 3, 1);
	disp_adj_vert(base);

	// check the functions
	int temp;
	temp = is_adjacent(base, v1);
	printf("Is 'base' and 'v1' adjacent?: %d\n", temp);
	temp = is_adjacent(v2, v1);
	printf("Is 'v1' and 'v2' adjacent?: %d\n", temp);
	temp = is_adjacent(v2, base);
	printf("Is 'v2' and 'base' adjacent?: %d\n", temp);
	
	//struct vertexList * tempList45;
	tail(base->adjacentList);
	//printf("%d\n", tempList45->node->value);
	
	temp = BFS(v2, v3);
	printf("Is 'v2' and 'v3' connected?: %d\n", temp);
	return 0;
}
