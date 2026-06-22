#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct bookInfo
{
    char Name[50];      // 书名
    int Number;         // 编号
    float Price;        // 价格
    char Penster[50];   // 作者
    char S_Name[50];    // 借阅人
    char sex;           // 性别
    int S_ID;           // 学号
};

struct Node
{
    struct bookInfo data;
    struct Node* next;
};

// 创建表头
struct Node* createHead()
{
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    if (headNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    headNode->next = NULL;
    return headNode;
}

// 创建新节点
struct Node* createNode(struct bookInfo data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 头插法插入节点
void insertNodeByHead(struct Node* headNode, struct bookInfo data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

// 打印链表
void printList(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    printf("书名\t编号\t价格\t作者\t借阅人\t借阅人性别\t借阅人学号\n");

    while (pMove != NULL)
    {
        printf("%s\t%d\t%.1f\t%s\t%s\t%c\t%d\n",
            pMove->data.Name,
            pMove->data.Number,
            pMove->data.Price,
            pMove->data.Penster,
            pMove->data.S_Name,
            pMove->data.sex,
            pMove->data.S_ID);
        pMove = pMove->next;
    }
}

// 根据书名删除节点
void deleteNodeByData(struct Node* headNode, char* BookName)
{
    struct Node* posLeftNode = headNode;
    struct Node* posNode = headNode->next;

    while (posNode != NULL && strcmp(posNode->data.Name, BookName) != 0)
    {
        posLeftNode = posNode;
        posNode = posLeftNode->next;
    }

    if (posNode == NULL)
        return;
    else
    {
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode = NULL;
    }
}

// 菜单显示
void Menue()
{
    system("cls");
    system("title 图书管理系统");
    system("color 02");
    system("date /T");
    system("time /T");
    printf("------------------------------------------\n");
    printf("            欢迎使用图书管理系统          \n");
    printf("------------------------------------------\n");
    printf(" |               1.登记图书              | \n");
    printf(" |               2.浏览图书              | \n");
    printf(" |               3.查询图书              | \n");
    printf(" |               4.借阅图书              | \n");
    printf(" |               5.归还图书              | \n");
    printf(" |               6.书籍排序              | \n");
    printf(" |               7.删除书籍              | \n");
    printf(" |               0.退出系统              | \n");
    printf("-------------------------------------------\n");
    printf("       请输入数字0——7        :");
}

// 登记图书
void registerBook(struct Node* headNode)
{
    struct bookInfo newBook;

    printf("请输入书名: ");
    scanf("%s", newBook.Name);

    printf("请输入编号: ");
    scanf("%d", &newBook.Number);

    printf("请输入价格: ");
    scanf("%f", &newBook.Price);

    printf("请输入作者: ");
    scanf("%s", newBook.Penster);

    // 初始化借阅信息
    strcpy(newBook.S_Name, "未借出");
    newBook.sex = ' ';
    newBook.S_ID = 0;

    insertNodeByHead(headNode, newBook);
    printf("图书登记成功！\n");
}

// 查询图书
void queryBook(struct Node* headNode)
{
    char bookName[50];
    printf("请输入要查询的书名: ");
    scanf("%s", bookName);

    struct Node* pMove = headNode->next;
    int found = 0;

    while (pMove != NULL)
    {
        if (strcmp(pMove->data.Name, bookName) == 0)
        {
            printf("书名\t编号\t价格\t作者\t借阅人\t借阅人性别\t借阅人学号\n");
            printf("%s\t%d\t%.1f\t%s\t%s\t%c\t%d\n",
                pMove->data.Name,
                pMove->data.Number,
                pMove->data.Price,
                pMove->data.Penster,
                pMove->data.S_Name,
                pMove->data.sex,
                pMove->data.S_ID);
            found = 1;
            break;
        }
        pMove = pMove->next;
    }

    if (!found)
        printf("未找到该图书！\n");
}

// 借阅图书
void borrowBook(struct Node* headNode)
{
    char bookName[50];
    printf("请输入要借阅的书名: ");
    scanf("%s", bookName);

    struct Node* pMove = headNode->next;
    int found = 0;

    while (pMove != NULL)
    {
        if (strcmp(pMove->data.Name, bookName) == 0)
        {
            if (strcmp(pMove->data.S_Name, "未借出") != 0)
            {
                printf("该图书已被借出！\n");
            }
            else
            {
                printf("请输入借阅人姓名: ");
                scanf("%s", pMove->data.S_Name);

                printf("请输入借阅人性别(M/F): ");
                scanf(" %c", &pMove->data.sex);

                printf("请输入借阅人学号: ");
                scanf("%d", &pMove->data.S_ID);

                printf("借阅成功！\n");
            }
            found = 1;
            break;
        }
        pMove = pMove->next;
    }

    if (!found)
        printf("未找到该图书！\n");
}

// 归还图书
void returnBook(struct Node* headNode)
{
    char bookName[50];
    printf("请输入要归还的书名: ");
    scanf("%s", bookName);

    struct Node* pMove = headNode->next;
    int found = 0;

    while (pMove != NULL)
    {
        if (strcmp(pMove->data.Name, bookName) == 0)
        {
            if (strcmp(pMove->data.S_Name, "未借出") == 0)
            {
                printf("该图书未被借出！\n");
            }
            else
            {
                strcpy(pMove->data.S_Name, "未借出");
                pMove->data.sex = ' ';
                pMove->data.S_ID = 0;
                printf("归还成功！\n");
            }
            found = 1;
            break;
        }
        pMove = pMove->next;
    }

    if (!found)
        printf("未找到该图书！\n");
}

// 比较函数，用于qsort
int compareBooks(const void* a, const void* b)
{
    struct bookInfo* bookA = (struct bookInfo*)a;
    struct bookInfo* bookB = (struct bookInfo*)b;
    return bookA->Number - bookB->Number;
}

// 书籍排序
void sortBooks(struct Node* headNode)
{
    // 计算链表长度
    int count = 0;
    struct Node* pMove = headNode->next;
    while (pMove != NULL)
    {
        count++;
        pMove = pMove->next;
    }

    if (count <= 1)
    {
        printf("图书数量不足，无需排序！\n");
        return;
    }

    // 创建数组存储图书信息
    struct bookInfo* books = (struct bookInfo*)malloc(count * sizeof(struct bookInfo));
    if (books == NULL)
    {
        printf("内存分配失败！\n");
        return;
    }

    // 将链表中的图书信息复制到数组
    pMove = headNode->next;
    int i = 0;
    while (pMove != NULL)
    {
        books[i] = pMove->data;
        pMove = pMove->next;
        i++;
    }

    // 使用qsort排序
    qsort(books, count, sizeof(struct bookInfo), compareBooks);

    // 清空原链表
    while (headNode->next != NULL)
    {
        struct Node* temp = headNode->next;
        headNode->next = temp->next;
        free(temp);
    }

    // 将排序后的图书重新插入链表
    for (i = count - 1; i >= 0; i--)
    {
        insertNodeByHead(headNode, books[i]);
    }

    free(books);
    printf("图书排序成功！\n");
}

// 交互
void UserKey(struct Node* headNode)
{
    int userkey = 0;
    scanf("%d", &userkey);

    switch (userkey)
    {
    case 1:
        printf("【登记图书】\n");
        registerBook(headNode);
        break;
    case 2:
        printf("【浏览图书】\n");
        printList(headNode);
        break;
    case 3:
        printf("【查询图书】\n");
        queryBook(headNode);
        break;
    case 4:
        printf("【借阅图书】\n");
        borrowBook(headNode);
        break;
    case 5:
        printf("【归还图书】\n");
        returnBook(headNode);
        break;
    case 6:
        printf("【书籍排序】\n");
        sortBooks(headNode);
        break;
    case 7:
    {
        printf("【删除书籍】\n");
        char bookName[50];
        printf("请输入要删除的书名: ");
        scanf("%s", bookName);
        deleteNodeByData(headNode, bookName);
        printf("删除操作完成！\n");
        break;
    }
    case 0:
        printf("  退出成功\n");
        system("pause");
        exit(0);
        break;
    default:
        printf("输入无效，请输入0-7之间的数字！\n");
    }
}

int main()
{
    struct Node* head = createHead();

    while (1)
    {
        Menue();
        UserKey(head);
        system("pause");
        system("cls");
    }

    return 0;
}