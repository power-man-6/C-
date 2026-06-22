#include <iostream>
#include <windows.h>
#include <time.h>

// 定义方向
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

// 蛇的结构体
struct Snake {
    int x;
    int y;
    Snake* next;
};

// 游戏设置
const int width = 80;
const int height = 20;
int x, y, fruitX, fruitY, score;
Direction dir;
Snake* head;
Snake* tail;

// 初始化游戏
void Setup() {
    dir = STOP;
    score = 0;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;

    head = new Snake;
    head->x = x;
    head->y = y;
    head->next = nullptr;
    tail = head;
}

// 绘制游戏画面
void Draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == fruitY && j == fruitX)
                std::cout << "X";
            else {
                Snake* temp = head;
                bool isSnake = false;
                while (temp != nullptr) {
                    if (temp->x == j && temp->y == i) {
                        std::cout << "o";
                        isSnake = true;
                        break;
                    }
                    temp = temp->next;
                }
                if (!isSnake)
                    std::cout << " ";
            }
            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

// 获取用户输入
void Input() {
    if (GetAsyncKeyState(VK_UP) && dir != DOWN)
        dir = UP;
    else if (GetAsyncKeyState(VK_DOWN) && dir != UP)
        dir = DOWN;
    else if (GetAsyncKeyState(VK_LEFT) && dir != RIGHT)
        dir = LEFT;
    else if (GetAsyncKeyState(VK_RIGHT) && dir != LEFT)
        dir = RIGHT;
}

// 游戏逻辑更新
void Logic() {
    Snake* newHead = new Snake;
    newHead->next = head;
    switch (dir) {
    case UP:
        newHead->y = y - 1;
        newHead->x = x;
        break;
    case DOWN:
        newHead->y = y + 1;
        newHead->x = x;
        break;
    case LEFT:
        newHead->x = x - 1;
        newHead->y = y;
        break;
    case RIGHT:
        newHead->x = x + 1;
        newHead->y = y;
        break;
    default:
        break;
    }
    head = newHead;

    // 检测蛇身自碰撞
    Snake* check = head->next;
    while (check != nullptr) {
        if (check->x == head->x && check->y == head->y) {
            std::cout << "Game Over!" << std::endl;
            exit(0);
        }
        check = check->next;
    }

    if (head->x >= width || head->x < 0 || head->y >= height || head->y < 0) {
        std::cout << "Game Over!" << std::endl;
        exit(0);
    }

    if (head->x == fruitX && head->y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
    else {
        Snake* temp = tail;
        tail = tail->next;
        delete temp;
    }
    x = head->x;
    y = head->y;
}

int main() {
    srand(time(NULL));
    Setup();
    while (true) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}