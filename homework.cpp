#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct ShoppingItem {
    char name[50]; // 商品名称
    int quantity; // 商品数量
    struct ShoppingItem* next; // 指向下一个节点的指针
};
struct ShoppingItem* shoppingList = NULL;
struct ShoppingItem* addItem(struct ShoppingItem* shopList, char itemName[], int itemQuantity) {//待插入链表，头插法
    
    struct ShoppingItem* newItem = (struct ShoppingItem*)malloc(sizeof(struct ShoppingItem));
    strcpy(newItem->name,itemName);
    newItem->quantity = itemQuantity;//购买的数量。
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
    printf("购物清单:\n");
    if(current == NULL){
        printf("暂无购物清单。\n");
    }
    while (current != NULL) {
        printf("%s - 数量：%d\n", current->name, current->quantity);
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
    printf("查找商品 \"%s\" :\n", itemName);
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0){
        printf("%s - 数量：%d\n", current->name, current->quantity);
        return;
    }
        current = current->next;
    }
    printf("未找到商品 \"%s\"。\n", itemName);
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
                // 交换商品信息
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
    
    // 遍历到第一个购物清单的末尾
    while(current->next != NULL){
        current = current->next;
    }
    current->next = *list2;
    *list2 = NULL; // 清空第二个购物清单的头指针，防止误用
}

void deleteItem(char itemName[], int deleteAll) {
    struct ShoppingItem* current = shoppingList;
    struct ShoppingItem* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->name, itemName) == 0) {
            if (prev == NULL) {
                // 如果要删除的是第一个节点
                struct ShoppingItem* temp = shoppingList;
                shoppingList = shoppingList->next;
                free(temp);
                if (!deleteAll) break;
            }else{
                // 如果要删除的不是第一个节点
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
    
    printf("欢迎来到长风购物平台！ 请输入你想要的功能: \n");
    while(1){
        char name[30];
        int quantity = 0;
        int o = 0;
        memset(name, 0, sizeof(name));
        printf("[1] 添加商品到购物清单\n");
        printf("[2] 从购物清单中移除商品\n");
        printf("[3] 查看购物清单\n");
        printf("[4] 修改购物清单中商品的数量\n");
        printf("[5] 清空购物清单\n");
        printf("[6] 计算购物清单中商品的总数量\n");
        printf("[7] 查找购物清单中的商品\n");
        printf("[8] 排序购物清单\n");
        printf("[9] 合并购物清单\n");
        printf("[10] 删除购物清单中的商品\n");
        printf("[0] 结束\n");

        scanf("%d",&o);
        if(o==1){
            printf("请输入商品名称和数量(当商品名称输入[0]时，结束输入。): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                shoppingList = addItem(shoppingList, name, quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("清单：\n");
            displayList();
            printf("\n");
        }else if(o==2){
            printf("请输入您要移除的商品名称: \n");
            scanf("%s%*c",name);
            removeItem(name);
            printf("移除成功！清单：\n");
            displayList();
            printf("\n");
        }else if(o==3){
            displayList();
        }else if(o==4){
            printf("请输入商品名称和欲修改之数量: \n");
            scanf("%s%*c%d",name, &quantity);
            updateQuantity(name, quantity);
            printf("修改成功！清单：\n");
            displayList();
            printf("\n");
        }else if(o==5){
            clearList();
            printf("清空完毕！\n");
        }else if(o==6){
            printf("统计完毕，总数量为：%d\n",totalQuantity());
        }else if(o==7){
            printf("请输入要寻找的商品：\n");
            scanf("%s%*c",name);
            findItem(name);
        }else if(o==8){
            sortList();
            printf("排序完毕！清单：\n");
            displayList();
            printf("\n");
        }else if(o==9){
            struct ShoppingItem* list1 = NULL;
            struct ShoppingItem* list2 = NULL;
            printf("清单1\n");
            printf("请输入商品名称和数量(当商品名称输入[0]时，结束输入。): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                list1 = addItem(list1,name,quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("清单2\n");
            printf("请输入商品名称和数量(当商品名称输入[0]时，结束输入。): \n");
            while(scanf("%s", name)){
                if(name[0] == '0'){
                    break;
                }
                scanf("%d",&quantity);
                list2 = addItem(list2,name,quantity);
                quantity = 0;
                memset(name, 0, sizeof(name));
            }
            printf("请单合体中……\n");
            clearList();
            mergeLists(&list1, &list2);
            shoppingList = list1;
            printf("合体成功！清单：\n");
            displayList();
            printf("\n");
        }else if(o==10){
            printf("请输入要删除的商品：\n");
            int f;
            scanf("%s%*c",name);
            printf("是否全部删除？是[1] 不是[0]\n");
            scanf("%d",&f);
            deleteItem(name, f);
            printf("删除成功！清单：\n");
            displayList();
            printf("\n");
        }else if(o==0){
            break;
        }
    }
    
}