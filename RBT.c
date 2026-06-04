#include "RBT.h"
#include "Trie.h"

/**
 * Functie pentru crearea unui nod RB
 * @param t Arborele pentru care se va crea nodul
 * @param value Valoarea pe care o va avea nodul
 * @return Un nod RB
 */
RBNode* createRBNode(RBTree *t, TNode *value) {
    RBNode *newNode = malloc(sizeof(RBNode));
    newNode->color = RED;
    newNode->val = value;
    newNode->left = t->NIL;
    newNode->right = t->NIL;
    newNode->parent = t->NIL;

    return newNode;
}

/**
 * Functie pentru crearea si initializarea unui arbore Red Black
 * @return Un arbore Red Black nou
 */
RBTree* createRBTree() {
    RBTree *t = (RBTree*) malloc(sizeof(RBTree));

    t->NIL = (RBNode*) malloc(sizeof(RBNode));
    t->NIL->color = BLACK;
    t->NIL->left = t->NIL;
    t->NIL->right = t->NIL;
    t->NIL->parent = t->NIL;
    t->root = t->NIL;

    return t;
}

/**
 * Functie pentru rotirea la stanga intr-un arbore RB
 * @param t Arborele in care se va efectua rotirea
 * @param x Nodul pe care va incepe rotirea
 */
void leftRotate(RBTree *t, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != t->NIL) {
        y->left->parent = x;
    }

    if (x->parent == t->NIL) {
        t->root = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    y->parent = x->parent;
    x->parent = y;
}

/**
 * Functie pentru rotirea la dreapta intr-un arbore RB
 * @param t Arborele in care se va efectua rotirea
 * @param x Nodul pe care va incepe rotirea
 */
void rightRotate(RBTree *t, RBNode *x) {
    RBNode *y = x->left;
    x->left = y->right;

    if (y->right != t->NIL) {
        y->right->parent = x;
    }

    if (x->parent == t->NIL) {
        t->root = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->right = x;
    y->parent = x->parent;
    x->parent = y;
}

/**
 * Functia cauta si returneaza nodul cu valoarea cea mai mica
 * @param t Arborele in care se va face cautarea
 * @param x Nodul de unde va incepe cautarea
 * @return Nodul cu valoarea minima
 */
RBNode* minNodeRBTree(RBTree *t, RBNode *x) {
    RBNode *minNode = x;

    while (x->left != t->NIL) {
        minNode = x;
        x = x->left;
    }

    return minNode;
}

/**
 * Functia cauta si returneaza succesorul unui nod
 * @param t Arborele in care se va face cautarea
 * @param x Nodul caruia i se va cauta successorul
 * @return Successorul nodului x
 */
RBNode* successorRBTree(RBTree *t, RBNode *x) {
    if (x->right != t->NIL) {
        return minNodeRBTree(t, x->right);
    }

    RBNode *curr = t->root;
    RBNode *succ = t->NIL;

    while (curr != t->NIL) {
        if (x->val->value < curr->val->value) {
            curr = curr->right;
        } else {
            succ = curr;
            curr = curr->left;
        }
    }

    return succ;
}

/**
 * Functie pentru a ne asigura ca toate regulile unui arbore RB sunt respectate dupa
 * realizarea unei inserari
 * @param t Arborele in care se va realiza fixupul dupa adaugare
 * @param x Nodul de la care va incepe fixupul
 */
void addFixupRBTree(RBTree *t, RBNode *x) {
    while (x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            RBNode *uncle = x->parent->parent->right;    

            if (uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    leftRotate(t, x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rightRotate(t, x->parent->parent);
            }
        } else {
            RBNode *uncle = x->parent->parent->left;

            if (uncle->color == RED) {
                x->parent->color = BLACK;
                uncle->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rightRotate(t, x);
                }

                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                leftRotate(t, x->parent->parent);
            }
        }
    }

    t->root->color = BLACK;
}

/**
 * Functia pentru inserarea unui nod intr-un arbore RB
 * @param t Arborele in care se va insera
 * @param value Valoarea pe care o va avea noul nod inserat
 */
void addRBTree(RBTree *t, TNode *value) {
    RBNode *newNode = createRBNode(t, value);
    RBNode *prev = t->NIL;
    RBNode *curr = t->root;

    while (curr != t->NIL) {
        prev = curr;

        if (newNode->val->value < curr->val->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    newNode->parent = prev;

    if (prev == t->NIL) {
        t->root = newNode;
    } else if (newNode->val->value < prev->val->value) {
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }

    addFixupRBTree(t, newNode);
}

/**
 * Functie pentru cautarea unui nod dupa o valoarea
 * @param t Arvorele in care se va cauta nodul
 * @param val Valoarea dupa care nodul o sa fie cautat
 * @return Nodul cautat sau NIL in cazul in care nu a fost gasit niciun nod cu acea valoare
 */
RBNode* findNode(RBTree *t, char val) {
    RBNode *p = t->root;

    while (p != t->NIL && p->val->value != val) {
        if (p->val->value > val) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    return p;
}

/**
 * Functie pentru a ne asugura ca toate regulile unui arbore RB sunt respectate
 * dupa stergere
 * @param t Arborele in care se va realiza fixupul dupa stergere
 * @param x Nodul de la care va incepe fixupul
 */
void deleteFixupRBTree(RBTree *t, RBNode *x) {
    while (x != t->root && x->color == BLACK) {
        RBNode *sibling = t->NIL;

        if (x == x->parent->left) {
            sibling = x->parent->right;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                leftRotate(t, x->parent);
                sibling = x->parent->right;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rightRotate(t, sibling);
                    sibling = x->parent->right;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->right->color = BLACK;
                leftRotate(t, x->parent);

                x = t->root;
            }
        } else {
            sibling = x->parent->left;

            if (sibling->color == RED) {
                sibling->color = BLACK;
                x->parent->color = RED;
                rightRotate(t, x->parent);
                sibling = x->parent->left;
            }

            if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
                sibling->color = RED;
                x = x->parent;
            } else {
                if (sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    leftRotate(t, sibling);
                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                sibling->left->color = BLACK;
                rightRotate(t, x->parent);

                x = t->root;
            }
        }
    }

    x->color = BLACK;
}

/**
 * Functie pentru steregrea unui nod dintr-un arbore RB
 * @param t Arborele in care se va sterge un nod
 * @param z Nodul care va fi sters
 */
void deleteNodeRBTree(RBTree *t, RBNode *z) {
    RBNode *x = t->NIL;
    RBNode *y = t->NIL;

    if (z->left == t->NIL || z->right == t->NIL) {
        y = z;
    } else {
        y = successorRBTree(t, z);
    }

    if (y->left != t->NIL) {
        x = y->left;
    } else {
        x = y->right;
    }

    x->parent = y->parent;

    if (y->parent == t->NIL) {
        t->root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if (y != z) {
        z->val = y->val;
    }

    if (y->color == BLACK) {
        deleteFixupRBTree(t, x);
    }

    free(y);
}

/**
 * Functie pentru afisarea unui arbore RB in inorder
 * @param t Arborele afisat
 * @param n Nodul de la care va incepe afisarea
 */
void printRBT(RBTree *t, RBNode *n) {
    if (n == t->NIL)
        return;

    printRBT(t, n->left);

    printf("%c", n->val->value);

    printRBT(t, n->right);
}