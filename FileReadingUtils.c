#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "../Structures/Trie.h"
#include "../Structures/RBT.h"

/**
 * Functia de potrivire a textului dintr-un fisier cu un arbore Trie,
 * la final afisand pathurile fisierelor si numarul de potriviri identificate
 * @param t Arborele trie dupa care se vor face potrivirile
 * @param path Pathul fisierului in care se vor cauta potriviri
 */
void searchInTextFile(TrieTree *t, char *path) {
    if (t == NULL || t->root == NULL) return;

    int matchCount = 0;

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Invalide file: '%s'.\n", path);
        return;
    }

    TNode *current = t->root;
    int c;

    while ((c = fgetc(file)) != EOF) {
        char ch = (char)c;

        RBNode *childNode = findNode(current->childrens, ch);

        while (childNode == current->childrens->NIL && current != t->root) {
            current = current->failLink;
            childNode = findNode(current->childrens, ch);
        }

        if (childNode != current->childrens->NIL) {
            current = childNode->val;
        } else {
            current = t->root;
        }

        TNode *tmp = current;
        while (tmp != t->root) {
            if (tmp->isWord) {
                matchCount++;
            }
            tmp = tmp->failLink;
        }
    }

    fclose(file);

    printf("Path: %s | Matches: %d\n", path, matchCount);
}

/**
 * Functia va potrivi textul din fisierele dintr-un director cu un arbore Trie,
 * la final afisand pathurile fisierelor si numarul de potriviri identificate
 * @param t Arborele trie dupa care se vor face potrivirile
 * @param dirPath Pathul directorului
 */
void searchInDirectory(TrieTree *t, char *dirPath) {
    char path[200];
    struct dirent *dp;
    struct stat statbuf;

    DIR *dir = opendir(dirPath);
    if (!dir) {
        printf("Invalide directory: '%s'.\n", dirPath);
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {

            snprintf(path, sizeof(path), "%s/%s", dirPath, dp->d_name);

            if (stat(path, &statbuf) == 0) {
                if (S_ISREG(statbuf.st_mode)) {
                    searchInTextFile(t, path);
                }
            }
        }
    }

    closedir(dir);
}