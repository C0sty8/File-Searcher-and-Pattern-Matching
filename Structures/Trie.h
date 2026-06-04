//
// Created by gvend on 6/1/2026.
//

#ifndef PATERNSEARCHERINFILES_TRIE_H
#define PATERNSEARCHERINFILES_TRIE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct RBTree RBTree;

/**
 * Structura pentru nodurile unui arbore Trie
 * cu un arbore RB pentru cautarea in nodurile copil
 */
typedef struct TrieNode {
    char value;
    RBTree *childrens;
    struct TrieNode *failLink;
    bool isWord;
}TNode;

/**
 * Structura principala pentru un arbore Trie
 */
typedef struct TrieTree {
    TNode *root;
}TrieTree;

/**
 * Structura pentru nodurile unei cozi
 */
typedef struct TrieQueueNode {
    TNode *node;
    struct TrieQueueNode *next;
} TrieQueueNode;

/**
 * Structura unei cozi
 */
typedef struct TrieQueue {
    TrieQueueNode *head;
    TrieQueueNode *tail;
} TrieQueue;

TNode* createTrieNode(char val);
TrieTree* createTrieTree();
void addString(TrieTree *t, char str[]);
void deleteString(TrieTree *t, char[]);
void printTrie(TNode *n, char *buffer, int depth);


#endif //PATERNSEARCHERINFILES_TRIE_H