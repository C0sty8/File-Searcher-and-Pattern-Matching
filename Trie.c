#include "Trie.h"
#include "RBT.h"

/**
 * Functia creeaza si returneaza un nod nou Trie
 * @param val Valoarea noului nod
 * @return Un nod Trie
 */
TNode* createTrieNode(char val) {
    TNode *newNode = malloc(sizeof(TNode));
    newNode->isWord = false;
    newNode->value = val;
    newNode->childrens = createRBTree();
    newNode->failLink = NULL;

    return newNode;
}

/**
 * Functie pentru crearea unui arbore Trie nou 
 * @return Un arbore Trie
 */
TrieTree* createTrieTree() {
    TrieTree* newTree = malloc(sizeof(TrieTree));
    newTree->root = createTrieNode('$');

    return newTree;
}

void addFailLinks(TrieTree *t);

/**
 * Functie pentru adaugarea unui string intr-un arbore Trie
 * @param t Arborele in care se va adauga noul string
 * @param str Stringul care se va adauga
 */
void addString(TrieTree *t, char str[]) {
    int len = strlen(str);
    int i;
    TNode *p = t->root;

    for (i = 0; i < len; i++) {
        RBNode *next = findNode(p->childrens, str[i]);

        if (next == p->childrens->NIL)
            break;

        p = next->val;
    }

    for (;i < len; i++) {
        TNode *newNode = createTrieNode(str[i]);

        addRBTree(p->childrens, newNode);

        p = newNode;
    }

    p->isWord = true;

    addFailLinks(t);
}

void traverseRBTAndTrie(RBTree *t, RBNode *node, char *buffer, int depth);

/**
 * Functie pentru afisarea cuvintelor dintr-un trie
 * @param n Nodul curent din Trie
 * @param buffer Vectorul in care construim cuvantul
 * @param depth Urmatorul spatiu liber din buffer
 */
void printTrie(TNode *n, char *buffer, int depth) {
    if (n == NULL) return;

    if (n->isWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    if (n->childrens != NULL && n->childrens->root != n->childrens->NIL) {
        traverseRBTAndTrie(n->childrens, n->childrens->root, buffer, depth);
    }
}

/**
 * Functia care se ocupa de parcurgerea nodurilor frati din RBT
 * @param t Arborele RB care are fratii
 * @param node Nodul de la care incepe
 * @param buffer Buffer care ne va ajuta la construirea cuvintelor
 * @param depth Contor care indica urmatoarea pozitie libera din buffer
 */
void traverseRBTAndTrie(RBTree *t, RBNode *node, char *buffer, int depth) {
    if (node == t->NIL) return;

    traverseRBTAndTrie(t, node->left, buffer, depth);

    buffer[depth] = node->val->value;

    printTrie(node->val, buffer, depth + 1);

    traverseRBTAndTrie(t, node->right, buffer, depth);
}

/**
 * Functia care se ocupa de adaugarea in coada
 * @param q Coada in care se va adauga
 * @param node Valoarea noului element care va fi adaugat in coada
 */
void addToQueue(TrieQueue *q, TNode *node) {
    TrieQueueNode *newQNode = malloc(sizeof(TrieQueueNode));
    newQNode->node = node;
    newQNode->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = newQNode;

        return;
    }

    q->tail->next = newQNode;
    q->tail = newQNode;
}

/**
 * Functie pentru stergerea si obtinerea primului element din coada
 * @param q Coada din care se face stergerea si extractia
 * @return Primul element din coada
 */
TNode* pop(TrieQueue *q) {
    if (q->head == NULL)
        return NULL;

    TrieQueueNode *tmp = q->head;
    TNode *res = tmp->node;
    q->head = q->head->next;

    if (q->head == NULL) q->tail = NULL;

    free(tmp);
    return res;
}

/**
 * Functie pentru a pune fiii radacinii in coada si a le seta fail linkul catre root
 * @param t Arborele RB ale carui noduri vor fi adaugate in coada
 * @param n Nodul curent
 * @param root Referinta la rootul arborelui trie
 * @param q Coada in care vor fi adaugate nodurile
 */
void initRootChildren(RBTree *t, RBNode *n, TNode *root, TrieQueue *q) {
    if (n == t->NIL)
        return;
    
    initRootChildren(t, n->left, root, q);

    n->val->failLink = root;
    addToQueue(q, n->val);

    initRootChildren(t, n->right, root, q);
}

/**
 * Functie pentru calcularea fail linkurilor copiilor unui nod
 * @param t Arborele RB in care se vor adauga fail linkurile
 * @param n Nodul curent din RB
 * @param current Nodul curent din Trie
 * @param root Referinta la rootul arborelui Trie principal
 * @param q Coada cu nodurile care urmeaza sa-si primeasca fail linkurile
 */
void processNodeChildren(RBTree *t, RBNode *n, TNode *current, TNode *root, TrieQueue *q) {
    if (n == t->NIL) return;
    
    processNodeChildren(t, n->left, current, root, q);

    TNode *child = n->val;
    char ch = child->value;

    TNode *fail = current->failLink;
    RBNode *found = t->NIL;
    
    while (fail != root) {
        found = findNode(fail->childrens, ch);
        if (found != fail->childrens->NIL) {
            break;
        }
        fail = fail->failLink;
    }

    if (fail != NULL && fail->childrens != NULL) {
        found = findNode(fail->childrens, ch);
        
        if (found != fail->childrens->NIL && found->val != child) {
            child->failLink = found->val;
        } else {
            child->failLink = root;
        }
    } else {
        child->failLink = root;
    }

    addToQueue(q, child);

    processNodeChildren(t, n->right, current, root, q);
}

/**
 * Functie pentru adaugarea fail linkurilor la noduri
 * @param t Arborele in care se vor adauga fail linkuri
 */
void addFailLinks(TrieTree *t) {
    if (t == NULL || t->root == NULL) return;

    t->root->failLink = t->root;
    TrieQueue q = {NULL, NULL};

    if (t->root->childrens != NULL) {
        initRootChildren(t->root->childrens, t->root->childrens->root, t->root, &q);
    }

    while (q.head != NULL) {
        TNode *current = pop(&q);

        if (current->childrens != NULL) {
            processNodeChildren(current->childrens, current->childrens->root, current, t->root, &q);
        }
    }
}

/**
 * Functia invalideaza un string
 * @param t Arborele din care va fi invalidat un string
 * @param str Stringul care va fi invalidat
 */
void deleteString(TrieTree *t, char str[]) {
    if (t == NULL || t->root == NULL || str == NULL)
        return;

    int len = strlen(str);
    TNode *p = t->root;

    for (int i = 0; i < len; i++) {
        RBNode *next = findNode(p->childrens, str[i]);

        if (next == p->childrens->NIL) {
            printf("Cuvantul '%s' nu exista in Trie.\n", str);
            return;
        }

        p = next->val;
    }

    if (p->isWord == true) {
        p->isWord = false;
    }
}
