#include "ll.h"

// 2) insert: เรียงลำดับตาม ID
void insert(NodePtr *head, int id, char *name) {
    NodePtr newNode = (NodePtr)malloc(sizeof(node));
    if (newNode) {
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->next = NULL;
        newNode->prev = NULL;

        NodePtr current = *head;
        NodePtr previous = NULL;

        while (current != NULL && id > current->id) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { 
            newNode->next = *head;
            if (*head != NULL) (*head)->prev = newNode;
            *head = newNode;
        } else {
            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            if (current != NULL) current->prev = newNode;
        }
    }
}

// 3) delete: ลบตาม ID
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

// แสดงผล 2 บรรทัด (Forward และ Backward)
void display(NodePtr head) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    printf("The list is:\n");
    NodePtr current = head;
    NodePtr last = NULL;

    // ขาไป (Forward)
    while (current != NULL) {
        printf("%d %s --> ", current->id, current->name);
        if (current->next == NULL) last = current;
        current = current->next;
    }
    printf("NULL\n");

    // ขากลับ (Backward)
    current = last;
    while (current != NULL) {
        printf("%d %s --> ", current->id, current->name);
        current = current->prev;
    }
    printf("NULL\n");
}

// 3) ถ้ากด 3 ให้ล้างลิสต์ที่เหลือทั้งหมด
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

    // รับค่า choice ไปเรื่อยๆ จนกว่าจะจบไฟล์ หรือเลือก 3
    // ตัด printf ประโยคคำถามออกเพื่อให้ Autograder ไม่งง
    while (scanf("%d", &choice) != EOF) {
        if (choice == 1) {
            if (scanf("%d %s", &id, name) == 2) {
                insert(&head, id, name);
                display(head);
            }
        } else if (choice == 2) {
            if (scanf("%d", &id) == 1) {
                deleteNode(&head, id);
                display(head);
            }
        } else if (choice == 3) {
            freeAll(&head);
            printf("End of run.\n");
            break;
        }
    }
    return 0;
}