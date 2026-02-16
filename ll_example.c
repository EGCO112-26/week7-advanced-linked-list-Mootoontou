#include "ll.h"

void insert(NodePtr *head, int id, char *name) {
    NodePtr newNode = (NodePtr)malloc(sizeof(node));
    if (newNode) {
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->next = NULL;
        newNode->prev = NULL;

        NodePtr current = *head;
        NodePtr previous = NULL;

        // วนหาตำแหน่งที่เหมาะสม (เรียงตาม ID)
        while (current != NULL && id > current->id) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { // แทรกหน้าสุด
            newNode->next = *head;
            if (*head != NULL) (*head)->prev = newNode;
            *head = newNode;
        } else { // แทรกกลางหรือท้าย
            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            if (current != NULL) current->prev = newNode;
        }
    }
}

void deleteNode(NodePtr *head, int id) {
    NodePtr current = *head;

    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current != NULL) {
        if (current == *head) *head = current->next;
        if (current->next != NULL) current->next->prev = current->prev;
        if (current->prev != NULL) current->prev->next = current->next;

        free(current);
        printf("%d deleted.\n", id);
    } else {
        printf("%d not found.\n", id);
    }
}

void display(NodePtr head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("The list is:\n");
    NodePtr current = head;
    NodePtr last = NULL;

    // ขาไป
    while (current != NULL) {
        printf("%d %s --> ", current->id, current->name);
        if (current->next == NULL) last = current;
        current = current->next;
    }
    printf("NULL\n");

    // ขากลับ
    current = last;
    while (current != NULL) {
        printf("%d %s --> ", current->id, current->name);
        current = current->prev;
    }
    printf("NULL\n");
}

void freeAll(NodePtr *head) {
    printf("Clear all nodes\n");
    NodePtr current = *head;
    while (current != NULL) {
        NodePtr temp = current;
        current = current->next;
        printf("delete %d\n", temp->id);
        free(temp);
    }
    *head = NULL;
}

int main() {
    NodePtr head = NULL;
    int choice, id;
    char name[50];

    while (1) {
        printf("\nEnter your choice:\n");
        printf(" 1 to insert an element into the list.\n");
        printf(" 2 to delete an element from the list.\n");
        printf(" 3 to end.\n? ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter id and name: ");
            scanf("%d %s", &id, name);
            insert(&head, id, name);
            display(head);
        } else if (choice == 2) {
            printf("Enter number to be deleted: ");
            scanf("%d", &id);
            deleteNode(&head, id);
            display(head);
        } else if (choice == 3) {
            freeAll(&head);
            printf("End of run.\n");
            break;
        }
    }
    return 0;
}