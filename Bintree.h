#ifndef BINTREE_H
#define BINTREE_H

typedef struct Node {
    char name[50];
    int count;
    struct Node *left;
    struct Node *right;
} Node;

/* Perustoiminnot */
Node* bintree_create_node(const char *name, int count);
Node* bintree_insert(Node *root, const char *name, int count);
void bintree_free(Node *root);
Node* bintree_read_file(Node *root, const char *filename);

/* Tulostus- ja hakutoiminnot */
void bintree_write_in_order(Node *root, const char *filename);
int bintree_depth_search(Node *root, int target, const char *filename);
int bintree_breadth_search(Node *root, const char *target, const char *filename);

#endif // BINTREE_H