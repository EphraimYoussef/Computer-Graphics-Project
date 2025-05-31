#include <Windows.h>
#include <bits/stdc++.h>
#include "include/ProgramState.h"
#include "include/Constants.h"
#include "include/MainMenu.h"
#include "include/HandleCommand.h"
#include "include/HandleLBUP.h"
#include "include/HandleLBDown.h"
#include "include/HandleRBDown.h"

using namespace std;
using namespace Constants;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc = nullptr;
    HMENU mainMenu;

    static ProgramState state;
    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints , & nonConvexPoints = state.nonConvexPoints;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;

    if(currentTool != FILL_CONVEX){
        convexPoints.clear();
    }

    if(currentTool != FILL_NON_CONVEX){
        nonConvexPoints.clear();
    }

    switch (msg) {

        case WM_CREATE: {
            mainMenu = CreateMainMenu();
            SetMenu(hwnd, mainMenu);
            break;
        }

        case WM_COMMAND: {
            HandleCommand(hwnd, wp, state);
            break;
        }

        case WM_LBUTTONDOWN: {
            HandleLBDown(hwnd, wp, lp, hdc, state);
            break;
        }

        case WM_LBUTTONUP: {
            HandleLBUP(hwnd, wp, lp, hdc , state);
            break;
        }

        case WM_RBUTTONDOWN: {
            HandleRBDown(hwnd , wp , lp , hdc , state);
            break;
        }

        case WM_ERASEBKGND: {
            hdc = (HDC)wp;
            RECT rc;
            GetClientRect(hwnd, &rc);
            FillRect(hdc, &rc, BGBrush);
            return 1;
        }

        case WM_CLOSE: {
            DestroyWindow(hwnd);
            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default: {
            return DefWindowProc(hwnd, msg, wp, lp);
        }
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR cmd, int nsh) {
    const char* CLASS_NAME = "2D drawing program";

    WNDCLASS wc = {};
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.lpszClassName = CLASS_NAME;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hi;

    if (!RegisterClass(&wc)) {
        return -1;
    }

    HWND hwnd = CreateWindow(
                CLASS_NAME, CLASS_NAME,
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT,
                CW_USEDEFAULT, CW_USEDEFAULT,
                nullptr, nullptr, hi, nullptr);

    if (!hwnd) {
        return -1;
    }

    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
