#include <windows.h>
#include <iostream>
#include <time.h>
using namespace std;

// 定义7种俄罗斯方块形状（4x4矩阵）
wstring tetromino[7];
// 游戏区域尺寸（包含边界）
int nFieldWidth = 12;
int nFieldHeight = 18;
// 控制台屏幕尺寸
int nScreenWidth = 80;
int nScreenHeight = 30;

// 游戏区域数据（0=空，1-7=不同颜色的方块，9=边界）
unsigned char* pField = nullptr;

// 旋转计算函数（计算旋转后方块的位置）
int Rotate(int px, int py, int r) {
    switch (r % 4) {
    case 0: return py * 4 + px;          // 0度
    case 1: return 12 + py - (px * 4);   // 90度
    case 2: return 15 - (py * 4) - px;   // 180度
    case 3: return 3 - py + (px * 4);    // 270度
    }
    return 0;
}

// 碰撞检测函数
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {
    for (int px = 0; px < 4; px++)
        for (int py = 0; py < 4; py++) {
            // 获取旋转后方块的索引
            int pi = Rotate(px, py, nRotation);

            // 计算在游戏区域中的位置
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // 检查是否在游戏区域范围内
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth) {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight) {
                    // 检测碰撞（游戏区域已有方块）
                    if (tetromino[nTetromino][pi] != L'.' && pField[fi] != 0)
                        return false; // 碰撞
                }
            }
        }
    return true; // 无碰撞
}

int main() {
    // 初始化7种俄罗斯方块形状（4x4）
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x.");
    tetromino[0].append(L"..x."); // I型

    tetromino[1].append(L"....");
    tetromino[1].append(L".xx.");
    tetromino[1].append(L".xx.");
    tetromino[1].append(L"...."); // O型

    tetromino[2].append(L"....");
    tetromino[2].append(L".xx.");
    tetromino[2].append(L"..x.");
    tetromino[2].append(L"..x."); // J型

    tetromino[3].append(L"....");
    tetromino[3].append(L".xx.");
    tetromino[3].append(L".x..");
    tetromino[3].append(L".x.."); // L型

    tetromino[4].append(L"....");
    tetromino[4].append(L"..x.");
    tetromino[4].append(L".xxx");
    tetromino[4].append(L"...."); // T型

    tetromino[5].append(L"....");
    tetromino[5].append(L".x..");
    tetromino[5].append(L".xx.");
    tetromino[5].append(L"..x."); // S型

    tetromino[6].append(L"....");
    tetromino[6].append(L"..x.");
    tetromino[6].append(L".xx.");
    tetromino[6].append(L".x.."); // Z型

    // 初始化游戏区域
    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
        for (int y = 0; y < nFieldHeight; y++)
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

    // 初始化屏幕缓冲区
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    // 游戏状态变量
    bool bGameOver = false;
    int nCurrentPiece = rand() % 7;      // 当前方块类型
    int nCurrentRotation = 0;            // 当前旋转状态
    int nCurrentX = nFieldWidth / 2;     // 当前X位置
    int nCurrentY = 0;                   // 当前Y位置
    int nSpeed = 20;                     // 下落速度
    int nSpeedCount = 0;                 // 速度计数器
    bool bForceDown = false;             // 是否强制下落
    int nLinesCleared = 0;               // 消除的行数
    int nScore = 0;                      // 分数
    bool* bKey = new bool[4];            // 按键状态

    // 游戏主循环
    while (!bGameOver) {
        // 时间控制
        Sleep(50); // 控制游戏速度
        nSpeedCount++;
        bForceDown = (nSpeedCount == nSpeed);

        // 输入处理
        for (int k = 0; k < 4; k++)
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

        // 左右移动
        if (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY)) {
            nCurrentX++;
        }
        if (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY)) {
            nCurrentX--;
        }

        // 旋转
        if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY)) {
            nCurrentRotation++;
        }

        // 加速下落
        if (bKey[3]) {
            bForceDown = true;
        }

        // 自动下落
        if (bForceDown) {
            nSpeedCount = 0;
            // 检查是否可以下落
            if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1)) {
                nCurrentY++;
            }
            else {
                // 无法下落，固定方块到游戏区域
                for (int px = 0; px < 4; px++)
                    for (int py = 0; py < 4; py++)
                        if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
                            pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;

                // 检查是否有完整的行可以消除
                for (int py = 0; py < 4; py++) {
                    if (nCurrentY + py < nFieldHeight - 1) {
                        bool bLine = true;
                        for (int px = 1; px < nFieldWidth - 1; px++)
                            bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

                        if (bLine) {
                            // 清除当前行，并让上面的行下落
                            for (int px = 1; px < nFieldWidth - 1; px++)
                                pField[(nCurrentY + py) * nFieldWidth + px] = 8;

                            nLinesCleared++;
                            nScore += 100 * (1 + (nLinesCleared / 10)); // 每消除10行加速一次
                            if (nLinesCleared % 10 == 0 && nSpeed > 10)
                                nSpeed--;
                        }
                    }
                }

                // 生成新方块
                nCurrentX = nFieldWidth / 2;
                nCurrentY = 0;
                nCurrentRotation = 0;
                nCurrentPiece = rand() % 7;

                // 检查游戏是否结束（新方块无法放置）
                bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
            }
        }

        // 绘制游戏区域
        for (int x = 0; x < nFieldWidth; x++)
            for (int y = 0; y < nFieldHeight; y++)
                screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

        // 绘制当前活动方块
        for (int px = 0; px < 4; px++)
            for (int py = 0; py < 4; py++)
                if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
                    screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

        // 绘制分数
        swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);

        // 显示到控制台
        WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }

    // 游戏结束，显示信息
    CloseHandle(hConsole);
    cout << "Game Over! Score: " << nScore << endl;
    system("pause");

    // 释放资源
    delete[] pField;
    delete[] screen;
    delete[] bKey;
    return 0;
}
