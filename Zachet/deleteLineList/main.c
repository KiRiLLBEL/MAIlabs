#include <stdlib.h>
#include <stdio.h>

struct item {

    struct item* next;
    int data;
};

void add(struct item** head, int data, int k) {
    
    struct item* new = malloc(sizeof(struct item));
    new->next = NULL;
    new->data = data;

    if (head == NULL) {

        head = new;
        return;
    }

    if (k <= 1) {

        new->next = head;
        return;
    }

    struct item* tmp = head;

    for (int i = 2; i < k; ++i)
    {
        if (tmp->next == NULL) {

            tmp->next = new;            
            return;
        }

        tmp = tmp->next;
    }

    new->next = tmp->next;
    tmp->next = new;

    return;
}

void delete(struct item ** head) {
    if (head != NULL) {
        delete(head->next);
        free(head);
    }
}

int main() {
    
    struct item* list;

    add(&list, 15, 10);
    add(&list, 13, 1);
    add(&list, 12, 2);
    add(&list, 14, 10);

    delete(&list);

    return 0;
}
