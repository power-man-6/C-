#include <windows.h>

// 窗口过程函数声明
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 注册窗口类
    const wchar_t CLASS_NAME[] = L"WindowClass";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // 创建主窗口
    HWND hMainWnd = CreateWindowEx(
        0,                          // 扩展样式
        CLASS_NAME,                 // 窗口类名
        L"主窗口",                   // 窗口标题
        WS_OVERLAPPEDWINDOW,        // 基本样式
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,  // 位置和大小
        NULL,                       // 父窗口
        NULL,                       // 菜单
        hInstance,                  // 实例句柄
        NULL                        // 附加参数
    );

    if (hMainWnd == NULL) {
        MessageBox(NULL, L"窗口创建失败", L"错误", MB_OK | MB_ICONERROR);
        return 0;
    }

    // 创建子窗口（编辑框）
    HWND hEdit = CreateWindowEx(
        WS_EX_CLIENTEDGE,           // 扩展样式：下沉边框
        L"Edit",                    // 窗口类名：编辑框
        L"我的输入框",                // 窗口标题
        WS_VISIBLE | WS_CHILD,      // 可见的子窗口
        10, 10, 200, 30,            // 位置和大小
        hMainWnd,                   // 父窗口句柄
        NULL,                       // 无菜单
        hInstance,                  // 应用程序实例句柄
        NULL                        // 无附加参数
    );

    // 操作窗口
    ShowWindow(hEdit, SW_SHOW);     // 显示窗口
    SetWindowText(hEdit, L"新文本");  // 修改窗口文本

    // 显示主窗口
    ShowWindow(hMainWnd, nCmdShow);

    // 消息循环
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
