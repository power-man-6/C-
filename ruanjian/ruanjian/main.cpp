#define _CRT_SECURE_NO_WARNINGS  // 禁用不安全函数警告
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <richedit.h>
#include <shellapi.h>
#include <string>
#include <vector>
#include <memory>

// 确保Windows头文件正确配置
#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

// 确保commctrl.h使用正确版本
#define _WIN32_IE 0x0600

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "riched20.lib")

// 控件ID定义
#define IDC_EDIT          1001
#define IDC_STATUSBAR     1002

// 菜单命令ID定义
#define IDM_FILE_NEW      40001
#define IDM_FILE_OPEN     40002
#define IDM_FILE_SAVE     40003
#define IDM_FILE_SAVEAS   40004
#define IDM_FILE_EXIT     40005

#define IDM_EDIT_CUT      40010
#define IDM_EDIT_COPY     40011
#define IDM_EDIT_PASTE    40012

#define IDM_DRAW_RED      40020
#define IDM_DRAW_BLUE     40021
#define IDM_DRAW_GREEN    40022
#define IDM_DRAW_THIN     40023
#define IDM_DRAW_MEDIUM   40024
#define IDM_DRAW_THICK    40025

#define IDM_HELP_ABOUT    40030

// 全局变量
HWND hMainWnd, hEdit, hStatusBar;
HINSTANCE hInst;
HMENU hMenu;
HBITMAP hBitmap = NULL;
HDC hdcMem = NULL;
int nWidth, nHeight;
POINT ptLast;
bool bDrawing = false;
COLORREF crPenColor = RGB(0, 0, 0);
int nPenWidth = 2;
std::wstring currentFilePath;

// 函数声明
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CreateMenus(HWND hWnd);
void CreateControls(HWND hWnd);
void InitializeDrawing(HWND hWnd);
void SaveFile(HWND hWnd);
void OpenFile(HWND hWnd);
void AboutDialog(HWND hWnd);
void CreateStatusBar(HWND hWnd);
void UpdateStatusBar(int part, const wchar_t* text);

// 应用程序入口点
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 初始化公共控件
    INITCOMMONCONTROLSEX icc;
    icc.dwSize = sizeof(icc);
    icc.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icc);

    // 初始化RichEdit控件
    LoadLibrary(TEXT("riched20.dll"));

    hInst = hInstance;

    // 注册窗口类
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"Win32AppClass";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        MessageBox(NULL, L"窗口注册失败!", L"错误", MB_ICONERROR);
        return 1;
    }

    // 创建主窗口
    hMainWnd = CreateWindowEx(
        0,
        L"Win32AppClass",
        L"多功能桌面应用",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInstance, NULL
    );

    if (!hMainWnd) {
        MessageBox(NULL, L"窗口创建失败!", L"错误", MB_ICONERROR);
        return 1;
    }

    // 创建菜单和控件
    CreateMenus(hMainWnd);
    CreateControls(hMainWnd);
    CreateStatusBar(hMainWnd);

    // 显示和更新窗口
    ShowWindow(hMainWnd, nCmdShow);
    UpdateWindow(hMainWnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 清理资源
    if (hdcMem) DeleteDC(hdcMem);
    if (hBitmap) DeleteObject(hBitmap);

    return (int)msg.wParam;
}

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;

    switch (message) {
    case WM_CREATE:
        InitializeDrawing(hWnd);
        break;

    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        // 分析菜单选择
        switch (wmId) {
        case IDM_FILE_NEW:
            SetWindowText(hEdit, L"");
            currentFilePath.clear();
            UpdateStatusBar(0, L"新文件");
            break;

        case IDM_FILE_OPEN:
            OpenFile(hWnd);
            break;

        case IDM_FILE_SAVE:
            SaveFile(hWnd);
            break;

        case IDM_FILE_SAVEAS:
            currentFilePath.clear();
            SaveFile(hWnd);
            break;

        case IDM_FILE_EXIT:
            DestroyWindow(hWnd);
            break;

        case IDM_EDIT_CUT:
            SendMessage(hEdit, WM_CUT, 0, 0);
            break;

        case IDM_EDIT_COPY:
            SendMessage(hEdit, WM_COPY, 0, 0);
            break;

        case IDM_EDIT_PASTE:
            SendMessage(hEdit, WM_PASTE, 0, 0);
            break;

        case IDM_DRAW_RED:
            crPenColor = RGB(255, 0, 0);
            UpdateStatusBar(1, L"画笔颜色: 红色");
            break;

        case IDM_DRAW_BLUE:
            crPenColor = RGB(0, 0, 255);
            UpdateStatusBar(1, L"画笔颜色: 蓝色");
            break;

        case IDM_DRAW_GREEN:
            crPenColor = RGB(0, 255, 0);
            UpdateStatusBar(1, L"画笔颜色: 绿色");
            break;

        case IDM_DRAW_THIN:
            nPenWidth = 2;
            UpdateStatusBar(2, L"画笔粗细: 细");
            break;

        case IDM_DRAW_MEDIUM:
            nPenWidth = 5;
            UpdateStatusBar(2, L"画笔粗细: 中");
            break;

        case IDM_DRAW_THICK:
            nPenWidth = 10;
            UpdateStatusBar(2, L"画笔粗细: 粗");
            break;

        case IDM_HELP_ABOUT:
            AboutDialog(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;

    case WM_SIZE:
        nWidth = LOWORD(lParam);
        nHeight = HIWORD(lParam);

        // 调整编辑控件和状态栏大小
        MoveWindow(hEdit, 0, 0, nWidth, nHeight - 25, TRUE);
        SendMessage(hStatusBar, WM_SIZE, 0, 0);

        // 重新创建位图以匹配窗口大小
        if (hdcMem) DeleteDC(hdcMem);
        if (hBitmap) DeleteObject(hBitmap);
        InitializeDrawing(hWnd);
        break;

    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        if (hBitmap) {
            BitBlt(hdc, 0, 0, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:
        bDrawing = true;
        ptLast.x = LOWORD(lParam);
        ptLast.y = HIWORD(lParam);
        SetCapture(hWnd);
        break;

    case WM_MOUSEMOVE:
        if (bDrawing && (wParam & MK_LBUTTON)) {
            HDC hdc = GetDC(hWnd);
            HPEN hPen = CreatePen(PS_SOLID, nPenWidth, crPenColor);
            HPEN hOldPen = (HPEN)SelectObject(hdcMem, hPen);

            MoveToEx(hdcMem, ptLast.x, ptLast.y, NULL);
            LineTo(hdcMem, LOWORD(lParam), HIWORD(lParam));

            SelectObject(hdcMem, hOldPen);
            DeleteObject(hPen);

            // 更新屏幕
            BitBlt(hdc, ptLast.x, ptLast.y,
                LOWORD(lParam) - ptLast.x, HIWORD(lParam) - ptLast.y,
                hdcMem, ptLast.x, ptLast.y, SRCCOPY);

            ReleaseDC(hWnd, hdc);

            ptLast.x = LOWORD(lParam);
            ptLast.y = HIWORD(lParam);
        }
        break;

    case WM_LBUTTONUP:
        bDrawing = false;
        ReleaseCapture();
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 创建菜单
void CreateMenus(HWND hWnd) {
    hMenu = CreateMenu();

    // 文件菜单
    HMENU hFileMenu = CreateMenu();
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, L"新建");
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"打开");
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, L"保存");
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, L"另存为");
    AppendMenu(hFileMenu, MF_SEPARATOR, 0, NULL);
    AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"退出");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"文件");

    // 编辑菜单
    HMENU hEditMenu = CreateMenu();
    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, L"剪切");
    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, L"复制");
    AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, L"粘贴");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEditMenu, L"编辑");

    // 绘图菜单
    HMENU hDrawMenu = CreateMenu();

    HMENU hColorMenu = CreateMenu();
    AppendMenu(hColorMenu, MF_STRING, IDM_DRAW_RED, L"红色");
    AppendMenu(hColorMenu, MF_STRING, IDM_DRAW_BLUE, L"蓝色");
    AppendMenu(hColorMenu, MF_STRING, IDM_DRAW_GREEN, L"绿色");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hColorMenu, L"颜色");

    HMENU hWidthMenu = CreateMenu();
    AppendMenu(hWidthMenu, MF_STRING, IDM_DRAW_THIN, L"细");
    AppendMenu(hWidthMenu, MF_STRING, IDM_DRAW_MEDIUM, L"中");
    AppendMenu(hWidthMenu, MF_STRING, IDM_DRAW_THICK, L"粗");
    AppendMenu(hDrawMenu, MF_POPUP, (UINT_PTR)hWidthMenu, L"粗细");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hDrawMenu, L"绘图");

    // 帮助菜单
    HMENU hHelpMenu = CreateMenu();
    AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, L"关于");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, L"帮助");

    SetMenu(hWnd, hMenu);
}

// 创建控件
void CreateControls(HWND hWnd) {
    // 创建RichEdit控件作为文本编辑区域
    hEdit = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"RICHEDIT50W",
        L"",
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        0, 0, 0, 0,
        hWnd, (HMENU)IDC_EDIT, hInst, NULL
    );
}

// 初始化绘图区域
void InitializeDrawing(HWND hWnd) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    nWidth = rect.right;
    nHeight = rect.bottom - 25; // 留出状态栏空间

    HDC hdc = GetDC(hWnd);
    hdcMem = CreateCompatibleDC(hdc);
    hBitmap = CreateCompatibleBitmap(hdc, nWidth, nHeight);
    SelectObject(hdcMem, hBitmap);

    // 用白色填充位图
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdcMem, &rect, hBrush);
    DeleteObject(hBrush);

    ReleaseDC(hWnd, hdc);
}

// 保存文件
void SaveFile(HWND hWnd) {
    OPENFILENAME ofn;
    wchar_t szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"文本文件 (*.txt)\0*.txt\0所有文件 (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (currentFilePath.empty()) {
        if (GetSaveFileName(&ofn) == FALSE)
            return;
        currentFilePath = szFile;
    }

    // 获取编辑框文本
    int textLength = GetWindowTextLength(hEdit);
    std::vector<wchar_t> textBuffer(textLength + 1);
    GetWindowText(hEdit, textBuffer.data(), textLength + 1);

    // 使用 _wfopen_s 替代 _wfopen
    FILE* file = nullptr;
    errno_t err = _wfopen_s(&file, currentFilePath.c_str(), L"w");
    if (err == 0 && file) {
        fwprintf(file, L"%ls", textBuffer.data());
        fclose(file);
        UpdateStatusBar(0, currentFilePath.c_str());
        MessageBox(hWnd, L"文件保存成功!", L"提示", MB_OK | MB_ICONINFORMATION);
    }
    else {
        MessageBox(hWnd, L"文件保存失败!", L"错误", MB_OK | MB_ICONERROR);
    }
}

// 打开文件
void OpenFile(HWND hWnd) {
    OPENFILENAME ofn;
    wchar_t szFile[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hWnd;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"文本文件 (*.txt)\0*.txt\0所有文件 (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn) == FALSE)
        return;

    currentFilePath = szFile;

    // 使用 _wfopen_s 替代 _wfopen
    FILE* file = nullptr;
    errno_t err = _wfopen_s(&file, currentFilePath.c_str(), L"r");
    if (err == 0 && file) {
        // 获取文件大小
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fseek(file, 0, SEEK_SET);

        // 读取内容
        std::vector<wchar_t> buffer(size / sizeof(wchar_t) + 1);
        fread(buffer.data(), sizeof(wchar_t), size / sizeof(wchar_t), file);
        buffer[size / sizeof(wchar_t)] = L'\0';

        // 设置编辑框文本
        SetWindowText(hEdit, buffer.data());

        fclose(file);
        UpdateStatusBar(0, currentFilePath.c_str());
    }
    else {
        MessageBox(hWnd, L"文件打开失败!", L"错误", MB_OK | MB_ICONERROR);
    }
}

// 关于对话框
void AboutDialog(HWND hWnd) {
    MessageBox(hWnd,
        L"多功能桌面应用 v1.0\n\n"
        L"一个基于Win32 API的Windows应用程序，\n"
        L"支持文本编辑和简单绘图功能。",
        L"关于",
        MB_OK | MB_ICONINFORMATION);
}

// 创建状态栏
void CreateStatusBar(HWND hWnd) {
    hStatusBar = CreateWindowEx(
        0, STATUSCLASSNAME, NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0, 0, 0,
        hWnd, (HMENU)IDC_STATUSBAR, hInst, NULL
    );

    // 设置状态栏分区
    int parts[3] = { 200, 400, -1 };
    SendMessage(hStatusBar, SB_SETPARTS, 3, (LPARAM)parts);

    UpdateStatusBar(0, L"新文件");
    UpdateStatusBar(1, L"画笔颜色: 黑色");
    UpdateStatusBar(2, L"画笔粗细: 中");
}

// 更新状态栏
void UpdateStatusBar(int part, const wchar_t* text) {
    SendMessage(hStatusBar, SB_SETTEXT, part, (LPARAM)text);
}