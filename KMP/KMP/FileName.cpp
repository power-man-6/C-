#include <iostream>
#include <string>
using namespace std;

// 图书结构体
struct Book {
  string isbn;
  string name;
  string author;
  double price;
};

// 链表结点
struct Node {
  Book book;
  Node* next;
  Node(const Book& b) : book(b), next(nullptr) {}
};

// 链表类
class LinkList {
private:
  Node* head;  // 头指针（带头结点）

public:
  LinkList() {
    head = new Node(Book());  // 头结点不存数据
    head->next = nullptr;
  }

  ~LinkList() {
    Node* p = head;
    while (p) {
      Node* q = p;
      p = p->next;
      delete q;
    }
  }

  // 按书号有序插入
  bool insertBook(const Book& b) {
    Node* p = head;
    // 查找插入位置并检查重复
    while (p->next && p->next->book.isbn < b.isbn) {
      p = p->next;
    }
    if (p->next && p->next->book.isbn == b.isbn) {
      cout << "书号已存在，插入失败！" << endl;
      return false;
    }
    Node* newNode = new Node(b);
    newNode->next = p->next;
    p->next = newNode;
    cout << "✓ 插入成功！" << endl;
    return true;
  }

  // 按书号查找（返回结点指针）
  Node* findByISBN(const string& isbn) {
    Node* p = head->next;
    while (p && p->book.isbn != isbn) {
      p = p->next;
    }
    return p;
  }

  // 按书号删除
  bool deleteByISBN(const string& isbn) {
    Node* p = head;
    while (p->next && p->next->book.isbn != isbn) {
      p = p->next;
    }
    if (p->next == nullptr) {
      cout << "未找到该书号！" << endl;
      return false;
    }
    Node* q = p->next;
    p->next = q->next;
    delete q;
    cout << "删除成功！" << endl;
    return true;
  }

  // 显示所有图书
  void displayAll() {
    Node* p = head->next;
    if (p == nullptr) {
      cout << "图书库为空！" << endl;
      return;
    }
    int count = 0;
    cout << "\n========== 图书列表（链表版）==========" << endl;
    while (p) {
      count++;
      cout << count << ". ISBN：" << p->book.isbn
        << " | 书名：" << p->book.name
        << " | 作者：" << p->book.author
        << " | 价格：" << p->book.price << endl;
      p = p->next;
    }
    cout << "========================================\n" << endl;
  }

  // 批量插入
  void batchInsert() {
    int n;
    cout << "请输入要插入的图书数量：";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++) {
      Book b;
      cout << "\n第" << i + 1 << "本书：" << endl;
      cout << "书号："; getline(cin, b.isbn);
      cout << "书名："; getline(cin, b.name);
      cout << "作者："; getline(cin, b.author);
      cout << "价格："; cin >> b.price;
      cin.ignore();
      insertBook(b);
    }
  }
};

// 主菜单
int main() {
  LinkList library;
  int choice;

  cout << "====== 图书管理系统（链表版） ======" << endl;
  cout << "1. 批量插入多本图书" << endl;
  cout << "2. 插入一本图书" << endl;
  cout << "3. 按书号查找" << endl;
  cout << "4. 按书号删除" << endl;
  cout << "5. 显示所有图书" << endl;
  cout << "0. 退出" << endl;

  do {
    cout << "\n请选择：";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
      library.batchInsert();
      break;
    case 2: {
      Book b;
      cout << "书号："; getline(cin, b.isbn);
      cout << "书名："; getline(cin, b.name);
      cout << "作者："; getline(cin, b.author);
      cout << "价格："; cin >> b.price;
      cin.ignore();
      library.insertBook(b);
      break;
    }
    case 3: {
      string isbn;
      cout << "请输入要查找的书号：";
      getline(cin, isbn);
      Node* found = library.findByISBN(isbn);
      if (found) {
        cout << "找到图书：ISBN：" << found->book.isbn
          << " | 书名：" << found->book.name
          << " | 作者：" << found->book.author
          << " | 价格：" << found->book.price << endl;
      }
      else {
        cout << "未找到该书！" << endl;
      }
      break;
    }
    case 4: {
      string isbn;
      cout << "请输入要删除的书号：";
      getline(cin, isbn);
      library.deleteByISBN(isbn);
      break;
    }
    case 5:
      library.displayAll();
      break;
    case 0:
      cout << "感谢使用！" << endl;
      break;
    default:
      cout << "输入错误，请重新选择！" << endl;
    }
  } while (choice != 0);

  return 0;
}
