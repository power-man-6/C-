#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// 游戏窗口尺寸
const int WIDTH = 40;
const int HEIGHT = 20;

// 玩家飞机结构体
struct Player {
    int x, y;
    int hp;
} player;

// 子弹结构体
struct Bullet {
    int x, y;
    bool active;
};

// 敌机结构体
struct Enemy {
    int x, y;
    bool active;
};

vector<Bullet> bullets;
vector<Enemy> enemies;
int score = 0;
bool gameOver = false;

// 隐藏控制台光标
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

// 设置控制台光标位置
void GotoXY(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 初始化游戏
void InitGame() {
    srand(time(0));
    player.x = WIDTH / 2;
    player.y = HEIGHT - 1;
    player.hp = 100;
    bullets.clear();
    enemies.clear();
    score = 0;
    gameOver = false;
}

// 绘制游戏界面
void Draw() {
    GotoXY(0, 0);
    // 绘制顶部边界
    for (int i = 0; i < WIDTH; i++) cout << "-";
    cout << endl;

    // 绘制游戏区域
    for (int y = 1; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            bool drawn = false;

            // 绘制玩家飞机
            if (x == player.x && y == player.y) {
                cout << "A";
                drawn = true;
            }

            // 绘制子弹
            for (auto& b : bullets) {
                if (b.active && b.x == x && b.y == y) {
                    cout << "|";
                    drawn = true;
                    break;
                }
            }

            // 绘制敌机
            for (auto& e : enemies) {
                if (e.active && e.x == x && e.y == y) {
                    cout << "V";
                    drawn = true;
                    break;
                }
            }

            if (!drawn) cout << " ";
        }
        cout << endl;
    }

    // 绘制底部信息
    for (int i = 0; i < WIDTH; i++) cout << "-";
    cout << endl;
    cout << "HP: " << player.hp << "  Score: " << score << "  按ESC退出";
}

// 处理输入
void Input() {
    if (_kbhit()) {
        char key = _getch();
        switch (key) {
        case 'a': if (player.x > 1) player.x--; break;
        case 'd': if (player.x < WIDTH - 2) player.x++; break;
        case ' ':  // 发射子弹
            bullets.push_back({ player.x, player.y - 1, true });
            break;
        case 27:  // ESC键
            gameOver = true;
            break;
        }
    }
}

// 更新游戏逻辑
void Update() {
    // 更新子弹位置
    for (auto& b : bullets) {
        if (b.active) {
            b.y--;
            if (b.y < 1) b.active = false;  // 子弹超出屏幕
        }
    }

    // 生成敌机（每10帧生成一次）
    if (rand() % 10 == 0) {
        enemies.push_back({ rand() % (WIDTH - 2) + 1, 1, true });
    }

    // 更新敌机位置
    for (auto& e : enemies) {
        if (e.active) {
            e.y++;
            if (e.y >= HEIGHT - 1) {  // 敌机到达底部
                e.active = false;
                player.hp--;  // 玩家扣血
                if (player.hp <= 0) gameOver = true;
            }
        }
    }

    // 碰撞检测（子弹与敌机）
    for (auto& b : bullets) {
        if (b.active) {
            for (auto& e : enemies) {
                if (e.active && b.x == e.x && b.y == e.y) {
                    b.active = false;
                    e.active = false;
                    score += 10;
                    break;
                }
            }
        }
    }

    // 清理无效对象
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return !b.active;
        }), bullets.end());

    enemies.erase(remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) {
        return !e.active;
        }), enemies.end());
}

int main() {
    HideCursor();
    InitGame();

    while (!gameOver) {
        Draw();
        Input();
        Update();
        Sleep(50);  // 控制游戏速度
    }

    GotoXY(WIDTH / 2 - 5, HEIGHT / 2);
    cout << "游戏结束！得分: " << score << endl;
    GotoXY(0, HEIGHT + 2);
    return 0;
}
