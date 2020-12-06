# Back in time to learn C.
## Trying to understand the assembly created.
```bash
   gcc bintree.c
   objdump -M intel -d a.out
```
## Brouse the code.
```bash
    ctags -R .
    vim bintree.c
```
### Basic structures.
```C
// pointer to a tree node.
typedef struct tnode *Treeptr;

// A tree node.
typedef struct tnode {
    char *word;
    int  count;
    Treeptr left;
    Treeptr right;
} Treenode;

```
