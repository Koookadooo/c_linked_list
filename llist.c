#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

// Function to allocate a new struct node with a given value and NULL next pointer
struct node *node_alloc(int value) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// Function to free a node previously allocated with node_alloc
void node_free(struct node *n) {
    free(n);
}

// Function to insert a node at the head of the linked list
void llist_insert_head(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = n;
    } else {
        n->next = *head;
        *head = n;
    }
}

// Function to insert a node at the tail of the linked list
void llist_insert_tail(struct node **head, struct node *n) {
    if (*head == NULL) {
        *head = n;
    } else {
        struct node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = n;
    }
}

// Function to remove and return the node from the head of the linked list
struct node *llist_delete_head(struct node **head) {
    if (*head == NULL) {
        return NULL;
    }
    struct node *temp = *head;
    *head = (*head)->next;
    temp->next = NULL;
    return temp;
}

// Function to print the linked list to standard output
void llist_print(struct node *head) {
    if (head == NULL) {
        printf("[empty]\n");
    } else {
        printf("%d", head->value);
        head = head->next;

        while (head != NULL) {
            printf(" -> %d", head->value);
            head = head->next;
        }
        printf("\n");
    }
}

// Function to free the entire linked list
void llist_free(struct node **head) {
    while (*head != NULL) {
        struct node *temp = *head;
        *head = (*head)->next;
        node_free(temp);
    }
}

// Main function for testing
int main(int argc, char *argv[]) {
    struct node *head = NULL;
    char *commands[argc];  // Create an array to store commands

    // Store command line arguments in the commands array
    for (int i = 1; i < argc; i++) {
        commands[i - 1] = argv[i];
    }

    for (int i = 0; i < argc - 1; i++) {  // Iterate through the commands array
        if (strcmp(commands[i], "ih") == 0) {
            if (i + 1 < argc - 1) {
                int value = atoi(commands[i + 1]);
                struct node *new_node = node_alloc(value);
                llist_insert_head(&head, new_node);
                i++;  // Skip the next argument (value)
            }
        } else if (strcmp(commands[i], "it") == 0) {
            if (i + 1 < argc - 1) {
                int value = atoi(commands[i + 1]);
                struct node *new_node = node_alloc(value);
                llist_insert_tail(&head, new_node);
                i++;  // Skip the next argument (value)
            }
        } else if (strcmp(commands[i], "dh") == 0) {
            head = llist_delete_head(&head);
            node_free(head);
        } else if (strcmp(commands[i], "p") == 0) {
            llist_print(head);
        } else if (strcmp(commands[i], "f") == 0) {
            llist_free(&head);
        }
    }

    return 0;
}
