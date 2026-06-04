#include <stdio.h>
#include "Structures/Trie.h"
#include "Utils/FileReadingUtils.h"

#define MAX_SIZE 200

/**
 * Functie pentru citirea unei propozitii de la tastatura.
 * @param str Variabila in care va fi memorata propozitia.
 */
void readString(char **str) {
    char tmp[MAX_SIZE];

    fgets(tmp, sizeof(tmp), stdin);
    fgets(tmp, sizeof(tmp), stdin);

    tmp[strlen(tmp)-1] = '\0';
    *str = malloc((strlen(tmp) + 1) * sizeof(char));
    strcpy(*str,tmp);
}

int main (void) {
    char *path = calloc(1, sizeof(char));
    char *tmp = calloc(1, sizeof(char));
    char buffer[MAX_SIZE];
    TrieTree *t = createTrieTree();

    printf("1. Set directory path\n"
           "2. Add string\n"
           "3. Delete String\n"
           "4. Search in file\n"
           "5. Search in directory\n"
           "6. Exit\n");

    while (1) {
        int choice;

        printf("Current path: %s\nStrings:\n", path);
        printTrie(t->root, buffer, 0);

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readString(&path);
                break;

            case 2:
                readString(&tmp);
                addString(t, tmp);
                free(tmp);
                break;

            case 3:
                readString(&tmp);
                deleteString(t, tmp);
                free(tmp);
                break;

            case 4:
                searchInTextFile(t, path);
                break;

            case 5:
                searchInDirectory(t, path);
                break;

            case 6:
                free(path);
                return 0;

            default:
                printf("TRY AGAIN!!!\n");
                break;
        }
    }
}