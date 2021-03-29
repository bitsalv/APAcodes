#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

#import "menu.h"

typedef struct BSTnode* link;
typedef pMenu Item;

struct BSTnode { Item item; link p; link l; link  r; int N; } ;

struct binarysearchtree { link root;  link z; };

static link NEW(Item item, link p, link l, link r, int N);
static void treeFree(link h, link z);
static int  countR(link h, link z);
static link insertR(link h, Item x, link z);
static link insertT(link h, Item x, link z);
static Item maxR(link h, link z);
static link rotR(link h);
static link rotL(link h);
//static void treePrintR(link h, link z, int strategy, PIATTO *piatti);


static link NEW(Item item, link p, link l, link r, int N) {
  link x = malloc(sizeof *x);
  x->item = item; x->p = p; x->l = l; x->r = r; x->N = N;
  return x;
}

BST BSTinit( ) {
  BST bst = malloc(sizeof *bst) ;
  bst->root = ( bst->z = NEW(ITEMsetNull(), NULL, NULL, NULL, 0));
  return bst;
}

void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  treeFree(bst->root, bst->z);
  free(bst->z);
  free(bst);
}

static void treeFree(link h, link z) {
  if (h == z)
    return;
  treeFree(h->l, z);
  treeFree(h->r, z);
  free(h);
}

static int countR(link h, link z) {
 if (h == z)
   return 0;
 return countR(h->l, z) + countR(h->r, z) +1;
}

int BSTcount(BST bst) {
  return countR(bst->root, bst->z);
}

int BSTempty(BST bst) {
  if (BSTcount(bst) == 0)
    return 1;
  return 0;
}


static link insertR(link h, Item x, link z) {
  if (h == z)
    return NEW(x, NULL, z, z, 0);
  if (menuCompare(x,h->item)==-1)
    h->l = insertR(h->l, x, z);
  else
    h->r = insertR(h->r, x, z);
  return h;
}

void BSTinsert_leafR(BST bst, Item x) {
  bst->root = insertR(bst->root, x, bst->z);
}

link rotR(link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

link rotL(link h) {
  link x = h->r;
  h->r = x->l;
  x->l = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

static link insertT(link h, Item x, link z) {
  if ( h == z)
    return NEW(x, NULL, z, z, 0);
  if (menuCompare(x, h->item)==-1) {
    h->l = insertT(h->l, x, z);
    h = rotR(h);
  }
  else {
    h->r = insertT(h->r, x, z);
    h = rotL(h);
  }
  return h;
}

void BSTinsert_root(BST bst, Item x) {
  bst->root = insertT(bst->root, x, bst->z);
}


static Item maxR(link h, link z) {
  if (h == z)
    return ITEMsetNull();
  if (h->r == z)
    return (h->item);
  return maxR(h->r, z);
}

Item BSTmax(BST bst) {
  return maxR(bst->root, bst->z);
}

/*non implementata in aula
static void treePrintR(link h, link z, int strategy, PIATTO *piatti) {
    if (h == z)
        return;

    if (strategy == PREORDER)
        menuPrint(&h->item,piatti);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        menuPrint(&h->item,piatti);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        menuPrint(&h->item,piatti);
}

void BSTvisit(BST bst, int strategy, PIATTO *piatti) {
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy,piatti);
}

*/








