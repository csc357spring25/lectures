#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate(void) {
    List *lst = (List *)malloc(sizeof(List));

    lst->head = NULL;
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    /* NOTE: We cannot just free the list, otherwise we will lose access to the
     *       nodes within it, which will never be freed. */
    Node *node = lst->head;
    int i;

    for (i = 0; i < lst->size; i++) {
        Node *tmp = node->next;
        free(node);
        node = tmp;
    }

    free(lst);
}

/* lstget: Gets an element in a linked list. */
void *lstget(List *lst, int idx) {
    Node *node = lst->head;
    int i;

    for (i = 0; i < idx; i++) {
        node = node->next;
    }

    return node->val;
}

/* lstset: Sets an element in a linked list. */
int lstset(List *lst, int idx, void *val) {
    Node *node = lst->head;
    int i;

    for (i = 0; i < idx; i++) {
        node = node->next;
    }

    node->val = val;
    return 0;
}

/* lstadd: Adds an element to a linked list. */
int lstadd(List *lst, int idx, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (idx == 0) {
        node->next = lst->head;
        lst->head = node;
    }
    else {
        Node *tmp = lst->head;
        int i;

        for (i = 0; i < idx - 1; i++) {
            tmp = tmp->next;
        }

        node->next = tmp->next;
        tmp->next = node;
    }

    lst->size++;

    /* NOTE: By convention, an error code is returned to indicate whether or
     *       not something went wrong; for example, a 1 could be returned
     *       instead if the index were to be out-of-bounds. */

    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
