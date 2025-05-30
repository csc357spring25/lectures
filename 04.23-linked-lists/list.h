/* Node: Represents an element in a linked list. */
typedef struct Node {
    void *val;
    struct Node *next;
} Node;

/* List: Represents a linked list. */
typedef struct List {
    Node *head;
    int size;
} List;

List *lstcreate(void);
void lstdestroy(List *);
void *lstget(List *, int);
int lstset(List *, int, void *);
int lstadd(List *, int, void *);
void *lstremove(List *, int);
