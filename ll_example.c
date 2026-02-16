#include "ll.h"

// 2) insert: เรียงลำดับตาม ID จากน้อยไปมาก
void insert(NodePtr *head, int id, char *name) {
    NodePtr newNode = (NodePtr)malloc(sizeof(node));
    if (newNode) {
        newNode->id = id;
        strcpy(newNode->name, name);
        newNode->next = NULL;
        newNode->prev = NULL;

        NodePtr current = *head;
        NodePtr previous = NULL;

        // วนหาตำแหน่งที่จะแทรก (id ใหม่ น้อยกว่า id ปัจจุบัน หรือไม่)
        while (current != NULL && id > current->id) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { 
            // กรณี 1: แทรกที่หัวแถว (List ว่าง หรือ id น้อยที่สุด)
            newNode->next = *head;
            if (*head != NULL) {
                (*head)->prev = newNode;
            }
            *head = newNode;
        } else {
            // กรณี 2: แทรกกลางหรือท้ายแถว
            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            if (current != NULL) {
                current->prev = newNode;
            }
        }
    }
}

// 3) delete: ลบตาม ID
void deleteNode(NodePtr *head, int id) {
    NodePtr current = *head;

    // วนหา Node ที่ต้องการลบ
    while (current != NULL && current->id != id) {
        current = current->next;
    }

    if (current != NULL) {
        // 
        // ถ้าเป็น Head ให้ขยับ Head ไปตัวถัดไป
        if (current == *head) {
            *head = current->next;
        }
        
        // เชื่อม Node ถัดไป กลับมาหา Node ก่อนหน้า
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
        
        // เชื่อม Node ก่อนหน้า ข้ามไปหา Node ถัดไป
        if (current->prev != NULL) {
            current->prev->next = current->next;
        }

        // *** จุดสำคัญ: ใช้ format เดียวกับ freeAll (delete %d) ***
        printf("delete %d\n", id);
        
        free(current);
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

// 4) ล้างลิสต์ทั้งหมด
void freeAll(NodePtr *head) {
    printf("Clear all nodes\n");
    NodePtr current = *head;
    while (current != NULL) {
        NodePtr temp = current;
        current = current->next;
        // Format ตรงนี้คือ "delete %d" ดังนั้น deleteNode ควรใช้ format นี้ด้วย
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
    while (scanf("%d", &choice) != EOF) {
        if (choice == 1) {
            // Insert
            if (scanf("%d %s", &id, name) == 2) {
                insert(&head, id, name);
                display(head);
            }
        } else if (choice == 2) {
            // Delete
            if (scanf("%d", &id) == 1) {
                deleteNode(&head, id);
                display(head);
            }
        } else if (choice == 3) {
            // Quit
            freeAll(&head);
            printf("End of run.\n");
            break;
        }
    }
    return 0;
}