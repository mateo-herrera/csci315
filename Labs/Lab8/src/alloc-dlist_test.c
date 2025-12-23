#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

void test_dlist_operations() {
    // Create doubly linked list
    struct dlist *list = dlist_create();

    // Test data
    int *data1 = malloc(sizeof(int));
    int *data2 = malloc(sizeof(int));
    int *data3 = malloc(sizeof(int));
    *data1 = 250;
    *data2 = 25;
    *data3 = 100;

    // Add nodes to the front and back of the list
    printf("Adding nodes to the list:\n");
    dlist_add_front(list, data1, sizeof(int));
    dlist_add_back(list, data2, sizeof(int));
    dlist_add_back(list, data3, sizeof(int));

    // Print the list
    dlist_print(list);

    // Remove a node from the front
    printf("\nRemoving node from the front:\n");
    free(dlist_remove_front(list));
    dlist_print(list);

    // Remove a node from the back
    printf("\nRemoving node from the back:\n");
    free(dlist_remove_back(list));
    dlist_print(list);

    // Add more nodes to the front and back
    printf("\nAdding more nodes to the list:\n");
    dlist_add_front(list, data2, sizeof(int));
    dlist_add_back(list, data3, sizeof(int));
    dlist_print(list);

    // Remove a node from the front and back again
    printf("\nFinal removal from front and back:\n");
    free(dlist_remove_front(list));
    free(dlist_remove_back(list));
    dlist_print(list);

    // Clean up
    printf("\nObliterating the list:\n");
    dlist_obliterate(list);
}

int main() {
    test_dlist_operations();
    return 0;
}

