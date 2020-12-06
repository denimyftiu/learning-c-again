#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

// pointer to a tree node.
typedef struct tnode *Treeptr;

// A tree node.
typedef struct tnode {
    char *word;     // 0b
    int  count;     // 8b
    Treeptr left;   // 12b
    Treeptr right;  // 20b
} Treenode;

Treeptr addtree(Treeptr, char *);
Treeptr talloc(void);
void treeprint(Treeptr);
void print_node(Treeptr);

int main(){

    Treeptr root;
    root = NULL;

    printf("SIZE OF TREE STRUCT: 0x%x\n", sizeof(Treenode));
    printf("SIZE OF TREE PTR: 0x%x\n", sizeof(Treeptr));
    printf("SIZE OF CHAR * : 0x%x\n", sizeof(char *));
    printf("SIZE OF INTEGER: 0x%x\n", sizeof(int));
    char word[MAXWORD];

    // while(scanf("%s", word) != EOF)
    //     if(isalpha(word[0]))
    //         root = addtree(root, word);

    // treeprint(root);
    return 0;
}

Treeptr addtree(Treeptr node, char *word){
    int cond;

    if (node == NULL) { 
        node = talloc();
        node->count = 1;
        node->word = strdup(word);
        node->left = node->right = NULL;
    } else if ((cond = strcmp(word, node->word)) == 0){
        node->count++;
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

