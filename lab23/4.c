#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
	int key;
	struct _node *left;
	struct _node *right;
} node;

node *make_node(int x) {
	node *n = (node*)malloc(sizeof(node));
	n->key = x;
	n->left = NULL;
	n->right = NULL;

	return n;
}

void free_node(node * n) {
	printf("free node with key %d\n", n->key);
	if (n->left) // or "if (n->left != NULL)"
		free_node(n->left);
	if (n->right)
		free_node(n->right);
	free(n);
}

void print_tree_beauty(node *n, int deep) {
	if (n->left)
		print_tree_beauty(n->left, deep + 1);
	for (int i = 0; i < deep; i++) {
		printf("\t");
	}
	printf("%d\n", n->key);
	if (n->right)
		print_tree_beauty(n->right, deep + 1);
}

void print_tree(node *n) {
	print_tree_beauty(n, 0);
}

int main() {
	
	node *a = make_node(10);
	node *b = make_node(5);
	node *c = make_node(15);
	a->left = b;
	a->right = c;
	print_tree(a);
	free_node(a);
	return 0;
}
