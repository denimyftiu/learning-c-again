#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

static int freedword = 0;
static int wordcount = 0;
static int wordsdoubled = 0;

// pointer to a tree node.
typedef struct tnode *Treeptr;

// A tree node.
typedef struct tnode {
    char *word;
    int  count;
    Treeptr left;
    Treeptr right;
} Treenode;

Treeptr addtree(Treeptr, char *);
Treeptr talloc(void);
void treeprint(Treeptr);
void print_node(Treeptr);
void free_tree(Treeptr);
void tree_info();

int main(){

    printf("SIZE OF TREE STRUCT: 0x%lx\n", sizeof(Treenode));
    printf("SIZE OF TREE PTR: 0x%lx\n", sizeof(Treeptr));
    printf("SIZE OF CHAR * : 0x%lx\n", sizeof(char *));
    printf("SIZE OF INTEGER: 0x%lx\n", sizeof(int));

    Treeptr root;
    root = NULL;
    char word[MAXWORD];

    //before
    tree_info();
    while(scanf("%s", word) != EOF)
        if(isalpha(word[0]))
            root = addtree(root, word);

    treeprint(root);
    free_tree(root);
    // after
    tree_info();
    return 0;
}

Treeptr addtree(Treeptr node, char *word){
    int cond;

    if (node == NULL) { 
        wordcount++;
        node = talloc();
        node->count = 1;
        node->word = strdup(word);
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0){
        node->count++;
        wordsdoubled++;
    } else if (cond < 0) { 
        node->left = addtree(node->left, word);
    } else {
        node->right = addtree(node->right, word);
    }
    return node;
}

Treeptr talloc(void){
    return (Treeptr) malloc(sizeof(Treenode));
}

void treeprint(Treeptr tree){
    if (tree != NULL) {
        treeprint(tree->left);
        // printf("Count: %d -> %s\n", tree->count, tree->word);
        print_node(tree);
        treeprint(tree->right);
    }
}

void print_node(Treeptr node){
    if (node == NULL)
        printf("NULL\n");

    else{
        printf("WORD-> %s\n", node->word);
        printf("COUNT-> %d\n", node->count);

        if (node->right == NULL)
            printf("RIGHT -> NULL\n");
        else
            printf("RIGHT -> %s\n", node->right->word);

        if (node->left == NULL)
            printf("LEFT -> NULL\n");
        else
            printf("LEFT -> %s\n", node->left->word);
    }

    printf("\n");
}

void free_tree(Treeptr node) {
    // DFS for this so we free from bottom to top.
    if (node != NULL){
        free_tree(node->right);
        free_tree(node->left);
        printf("Freeing: %s.\n", node->word);
        freedword++;
        free(node);
    }
}

void tree_info() {
    printf("words in tree: %d\n", wordcount);
    printf("words freed from the tree: %d\n", freedword);
    printf("words wordsdoubled: %d\n", wordsdoubled);
}
