#ifndef BST_H
#define BST_H

#define PREORDER  -1
#define INORDER    0
#define POSTORDER  1

#include "menu.h"

typedef struct  binarysearchtree *BST;
typedef pMenu Item;

BST  BSTinit(void);
void BSTfree(BST bst);
int  BSTcount(BST bst);
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
Item BSTmax(BST bst);
//void BSTvisit(BST bst, int strategy, PIATTO *piatti);


#endif



