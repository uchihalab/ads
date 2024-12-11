#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26 

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord; 
};


struct TrieNode* createNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }

    return node;
}


void insert(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';

        if (!current->children[index]) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }

   
    current->isEndOfWord = true;
}

bool search(struct TrieNode* root, const char* word) {
    struct TrieNode* current = root;

    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';

        if (!current->children[index]) {
            return false;
        }
        current = current->children[index];
    }

    return current->isEndOfWord;
}

bool hasChildren(struct TrieNode* node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            return true;
        }
    }
    return false;
}


bool deleteWord(struct TrieNode* root, const char* word, int depth) {
    if (!root) {
        return false;
    }

    if (depth == strlen(word)) {
       
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
        }

       
        if (!hasChildren(root)) {
            free(root);
            return true;
        }

        return false;
    }

    int index = word[depth] - 'a';
    if (deleteWord(root->children[index], word, depth + 1)) {
      
        root->children[index] = NULL;

        return !hasChildren(root) && !root->isEndOfWord;
    }

    return false;
}


void printWords(struct TrieNode* root, char* buffer, int depth) {
    if (root->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            buffer[depth] = 'a' + i;
            printWords(root->children[i], buffer, depth + 1);
        }
    }
}

int main() {
    struct TrieNode* root = createNode();
    char buffer[100];

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Display All Words\n5. Exit\nChoose an option: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            char word[100];
            printf("Enter word to insert: ");
            scanf("%s", word);
            insert(root, word);
            printf("'%s' inserted.\n", word);
        } else if (choice == 2) {
            char word[100];
            printf("Enter word to search: ");
            scanf("%s", word);
            if (search(root, word)) {
                printf("'%s' is found.\n", word);
            } else {
                printf("'%s' not found.\n", word);
            }
        } else if (choice == 3) {
            char word[100];
            printf("Enter word to delete: ");
            scanf("%s", word);
            if (deleteWord(root, word, 0)) {
                printf("'%s' deleted.\n", word);
            } else {
                printf("'%s' not found or could not be deleted.\n", word);
            }
        } else if (choice == 4) {
            printf("Words in the Trie:\n");
            printWords(root, buffer, 0);
        } else if (choice == 5) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
