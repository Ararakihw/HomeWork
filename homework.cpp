#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ShoppingItem {
    char name[50]; // ��Ʒ����
    int quantity; // ��Ʒ����
    struct ShoppingItem* next; // ָ����һ���ڵ��ָ��
};
struct ShoppingItem* shoppingList = NULL;
struct ShoppingItem* addItem(struct ShoppingItem* shopList, char itemName[], int itemQuantity) {//����������ͷ�巨
    
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name,itemName);
    newItem->quantity = itemQuantity;//�����������
    newItem->next = NULL;
    if(shopList == NULL){
        shopList = newItem;
    }else{
        newItem->next = shopList;
        shopList = newItem;
    }
    return shopList;
}

void removeItem(char itemName[]){
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* previous = NULL;
    while(current != NULL){
        if (strcmp(current->name, itemName) == 0){
            if (previous != NULL){
                previous->next = current->next;
            }else{
                shoppingList = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }
    return ;
}

void displayList() {
    struct ShoppingItem* current = shoppingList;
    printf("�����嵥:\n");
    if(current == NULL){
        printf("���޹����嵥��\n");
    }
    while (current != NULL) {
        printf("%s - ������%d\n", current->name, current->quantity);
        current = current->next;
    }
}

void updateQuantity(char itemName[], int newItemQuantity) {
    struct ShoppingItem* current = shoppingList;
    while(current != NULL){
        if (strcmp(current->name, itemName) == 0){
            current->quantity = newItemQuantity;
            break;
        }
        current = current->next;
    }
}

void clearList() {
    struct ShoppingItem* temp = NULL;
    while (shoppingList != NULL) {
        temp = shoppingList;
        shoppingList = shoppingList->next;
        free(temp);
    }
    return ;
}

int totalQuantity() {
    struct ShoppingItem* current = shoppingList;
    int total = 0;
    while(current != NULL){
        total += current->quantity;
        current = current->next;
    }
    return total;
}

void findItem(char itemName[]) {
    struct ShoppingItem* current = shoppingList;
    printf("������Ʒ \"%s\" :\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0){
        printf("%s - ������%d\n", current->name, current->quantity);
        return;
    }
        current = current->next;
    }
    printf("δ�ҵ���Ʒ \"%s\"��\n", itemName);
}

void sortList() {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* nextItem = NULL;
    char tempName[50];
    int tempQuantity;
    while (current != NULL) {
        nextItem = current->next;
        while (nextItem != NULL) {
            if (strcmp(current->name, nextItem->name) > 0) {
                // ������Ʒ��Ϣ
                strcpy(tempName, current->name);
                strcpy(current->name, nextItem->name);
                strcpy(nextItem->name, tempName);

                tempQuantity = current->quantity;
                current->quantity = nextItem->quantity;
                nextItem->quantity = tempQuantity;
            }
            nextItem = nextItem->next;
        }
        current = current->next;
    }
}

void mergeLists(struct ShoppingItem** list1, struct ShoppingItem** list2) {
    struct ShoppingItem* current = *list1;
    
    // ��������һ�������嵥��ĩβ
    while(current->next != NULL){
        current = current->next;
    }
    current->next = *list2;
    *list2 = NULL; // ��յڶ��������嵥��ͷָ�룬��ֹ����
}

void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // ���Ҫɾ�����ǵ�һ���ڵ�
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                if (!deleteAll) break;
            }else{
                // ���Ҫɾ���Ĳ��ǵ�һ���ڵ�
                while(strcmp(current->name, itemName) == 0){
                    struct ShoppingItem* temp = NULL;
                    temp = current;
                    current = current->next;
                    free(temp);
                    
                    if (!deleteAll || current == NULL) break;
                }
                prev->next = current;
                prev = current;
                if(current != NULL){
                    current = current->next;
                }
                if (!deleteAll) break;
            }
        } else {
        prev = current;
        current = current->next;
        }
    }
}

int main (void){
    
    printf("��ӭ�������繺��ƽ̨�� ����������Ҫ�Ĺ���: \n");
    while(1){
        char name[30];
        int quantity = 0;
        int o = 0;
        memset(name, 0, sizeof(name));
        printf("[1] �����Ʒ�������嵥\n");
        printf("[2] �ӹ����嵥���Ƴ���Ʒ\n");
        printf("[3] �鿴�����嵥\n");
        printf("[4] �޸Ĺ����嵥����Ʒ������\n");
        printf("[5] ��չ����嵥\n");
        printf("[6] ���㹺���嵥����Ʒ��������\n");
        printf("[7] ���ҹ����嵥�е���Ʒ\n");
        printf("[8] �������嵥\n");
        printf("[9] �ϲ������嵥\n");
        printf("[10] ɾ�������嵥�е���Ʒ\n");
        printf("[0] ����\n");

        scanf("%d",&o);
        if(o==1){
            printf("��������Ʒ���ƺ�����(����Ʒ��������[0]ʱ���������롣): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                shoppingList = addItem(shoppingList, name, quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("�嵥��\n");
            displayList();
            printf("\n");
        }else if(o==2){
            printf("��������Ҫ�Ƴ�����Ʒ����: \n");
            scanf("%s%*c",name);
            removeItem(name);
            printf("�Ƴ��ɹ����嵥��\n");
            displayList();
            printf("\n");
        }else if(o==3){
            displayList();
        }else if(o==4){
            printf("��������Ʒ���ƺ����޸�֮����: \n");
            scanf("%s%*c%d",name, &quantity);
            updateQuantity(name, quantity);
            printf("�޸ĳɹ����嵥��\n");
            displayList();
            printf("\n");
        }else if(o==5){
            clearList();
            printf("�����ϣ�\n");
        }else if(o==6){
            printf("ͳ����ϣ�������Ϊ��%d\n",totalQuantity());
        }else if(o==7){
            printf("������ҪѰ�ҵ���Ʒ��\n");
            scanf("%s%*c",name);
            findItem(name);
        }else if(o==8){
            sortList();
            printf("������ϣ��嵥��\n");
            displayList();
            printf("\n");
        }else if(o==9){
            struct ShoppingItem* list1 = NULL;
            struct ShoppingItem* list2 = NULL;
            printf("�嵥1\n");
            printf("��������Ʒ���ƺ�����(����Ʒ��������[0]ʱ���������롣): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                list1 = addItem(list1,name,quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("�嵥2\n");
            printf("��������Ʒ���ƺ�����(����Ʒ��������[0]ʱ���������롣): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                list2 = addItem(list2,name,quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("�뵥�����С���\n");
            clearList();
            mergeLists(&list1, &list2);
            shoppingList = list1;
            printf("����ɹ����嵥��\n");
            displayList();
            printf("\n");
        }else if(o==10){
            printf("������Ҫɾ������Ʒ��\n");
            int f;
            scanf("%s%*c",name);
            printf("�Ƿ�ȫ��ɾ������[1] ����[0]\n");
            scanf("%d",&f);
            deleteItem(name, f);
            printf("ɾ���ɹ����嵥��\n");
            displayList();
            printf("\n");
        }else if(o==0){
            break;
        }
    }
    
}