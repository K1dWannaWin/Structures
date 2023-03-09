#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_LEN 50


// Описание структуры записи в файле
typedef struct {
    char name[MAX_LEN];
    char gender[MAX_LEN];
    int age;
    char sports[MAX_LEN];
    int height;
} Record;

// Описание элемента односвязного списка
typedef struct ListNode {
    Record data;
    struct ListNode* next;
} ListNode;

// Функция для создания нового элемента списка
ListNode* createNode(Record data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->data = data;
    node->next = NULL;
    return node;
}

// Функция для добавления элемента в конец списка
void appendNode(ListNode** headRef, Record data) {
    ListNode* node = createNode(data);
    if (*headRef == NULL) {
        *headRef = node;
    }
    else {
        ListNode* tail = *headRef;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = node;
    }
}

// Функция для удаления последнего элемента из списка
void removeLastNode(ListNode** headRef) {
    if (*headRef == NULL) {
        return;
    }
    if ((*headRef)->next == NULL) {
        free(*headRef);
        *headRef = NULL;
        return;
    }
    ListNode* prev = NULL;
    ListNode* curr = *headRef;
    while (curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    free(curr);
}

void printData (ListNode* curr)
{
  printf("%s\t\t%s\t%s\t\t%d\t\t%d\n", curr->data.name, curr->data.gender,
            curr->data.sports, curr->data.age,curr->data.height);
        curr = curr->next;

}

// Функция для вывода списка на экран в табличном виде
void printList(ListNode* head) {
    printf("Lastname\tGender\tSports\t\tYearOfBirth\tHeight\n");
    printf("-----------------------------------------------------------\n");
    ListNode* curr = head;
    while (curr != NULL) {
        printf("%s\t\t%s\t%s\t\t%d\t\t%d\n", curr->data.name, curr->data.gender,
            curr->data.sports, curr->data.age,curr->data.height);
        curr = curr->next;
    }
    printf("\n");
}

// Функция для поиска элемента по возрасту
ListNode* findNodeByAge(ListNode* head, int age) {
    ListNode* curr = head;
    while (curr != NULL) {
        if (age-curr->data.age>13&&age-curr->data.age<18) {
                 if (strcmp(curr->data.gender, "f")==0)
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

 //Функция для поиска самого выского плавца
ListNode* findNodeByHeight(ListNode* head, char* sports) {
    ListNode* curr = head;
    int maxHeight=0;
    ListNode* max=NULL;
    while (curr != NULL) {
        if (strcmp(curr->data.sports, sports) == 0) {
            if (strcmp(curr->data.gender, "m")==0) {
                if (curr->data.height > maxHeight) {
                    maxHeight = curr->data.height;
                    max = curr;
                }
            }
        }
        curr = curr->next;
    }
    return max;
}

// Главная функция
int main(int argc, char* argv[]) {
    time_t now;
    time(&now);
    struct tm* local = localtime(&now);
    char* filename;
    if (argc < 2) {
        filename = "data.bin";
    }
    else {
        filename = argv[1];
    }
    // Чтение данных из файла и создание списка
    FILE* file = fopen(filename, "rb");
    ListNode* head = NULL;
    if (file != NULL)
    {
        Record data;
        while (fread(&data, sizeof(Record), 1, file) == 1) {
            appendNode(&head, data);
        }
        fclose(file);
    }

    int choice;
    do {
        printf("Menu:\n");
        printf("1. Add record\n");
        printf("2. View records\n");
        printf("3. Delete last record\n");
        printf("4. Find record by age\n");
        printf("5. Find highest by sports   \n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
        case 1: {  // Добавление записи
            Record data;
            printf("Enter lastname: ");
            scanf("%s", data.name);
            printf("Enter gender: ");
            scanf("%s", data.gender);
            printf("Enter sports: ");
            scanf("%s", &data.sports);
            printf("Enter year of birth: ");
            scanf("%d", &data.age);
            printf("Enter height: ");
            scanf("%d", &data.height);
            appendNode(&head, data);
            printf("Record added successfully.\n");
            break;
        }
        case 2:  // Просмотр списка
            printList(head);
            break;
        case 3:  // Удаление последней записи
            removeLastNode(&head);
            printf("Last record deleted successfully.\n");
            break;
        case 4: {  // Поиск по возрасту
            int year = local->tm_year + 1900;
            ListNode* node = findNodeByAge(head, year);
            printf("Lastname\tGender\tSports\t\tYearOfBirth\tHeight\n");
            printf("-----------------------------------------------------------\n");
            while (node != NULL) {
            printData(node);
            node = node->next;
            node = findNodeByAge(node, year);
            }
            break;
        }
        case 5: {  // Поиск самого высокого
            char sports[MAX_LEN];
            printf("Enter sports: ");
            scanf("%s", sports);
            ListNode* node = findNodeByHeight(head, sports);
            if (node != NULL) {
                printf("Record found:\n");
                printf("Lastname\tGender\tSports\t\tYearOfBirth\tHeight\n");
                printf("-----------------------------------------------------------\n");
             printData(node);
            }
            else {
                printf("Record not found.\n");
            }
            break;
        }
        case 6:  // Выход из программы
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
        printf("\n");
    } while (choice != 6);

    // Сохранение данных в файл
    file = fopen(filename, "wb");
    ListNode* curr = head;
    while (curr != NULL) {
        fwrite(&curr->data, sizeof(Record), 1, file);
        curr = curr->next;
    }
    fclose(file);

    // Очистка памяти, выделенной под список
    curr = head;
    while (curr != NULL) {
        ListNode* next = curr->next;
        free(curr);
        curr = next;
    }

    return 0;
}
