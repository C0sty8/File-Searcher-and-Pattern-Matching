//
// Created by gvend on 5/26/2026.
//

#ifndef PATERNSEARCHERINFILES_RBT_H
#define PATERNSEARCHERINFILES_RBT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct TrieNode TNode;

/**
 * Enum pentru cele doua culori pe care un nod RB poate sa le aiba
 */
typedef enum Color {
    RED,
    BLACK
} Color;

/**
 * Structura pentru nodurile unui arbore RB
 */
typedef struct RBNode {
    TNode *val;
    Color color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

/**
 * Structura principala a unui arbore Red-Black
 */
typedef struct RBTree {
    RBNode *root;
    RBNode *NIL;
} RBTree;

RBTree* createRBTree();
RBNode* createRBNode (RBTree *t, TNode *value);
void addRBTree (RBTree *t, TNode *value);
RBNode* findNode (RBTree *t, char val);
void deleteNodeRBTree (RBTree *t, RBNode *z);
void printRBT (RBTree *t, RBNode *n);

#endif //PATERNSEARCHERINFILES_RBT_H