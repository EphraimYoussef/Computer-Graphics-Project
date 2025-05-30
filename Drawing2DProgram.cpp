#include <Windows.h>
#include <bits/stdc++.h>
#include "include/ProgramState.h"
#include "include/Constants.h"
#include "include/MainMenu.h"
#include "include/HandleCommand.h"
#include "./include/LineAlgorithms.h"
#include "./include/CircleAlgorithms.h"
#include "./include/EllipseAlgorithms.h"
#include "./include/FillingAlgorithms.h"
#include "./include/ClippingAlgorithms.h"
#include "./include/CurvesAlgorithms.h"

using namespace std;
using namespace Constants;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    HMENU mainMenu;

    static ProgramState state;
    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& points = state.points;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;

    if(currentTool != FILL_CONVEX){
        points.clear();
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
            switch (currentTool) {

                // ? Line Algorithms
                case LINE_DDA:
                case LINE_MID_POINT:
                case LINE_PARAMETRIC: {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    break;
                }

            //!=========================================================================================================

                // ? Circle Algorithms
                case CIRCLE_DIRECT:
                case CIRCLE_POLAR:
                case CIRCLE_ITERATIVE_POLAR:
                case CIRCLE_MID_POINT:
                case CIRCLE_MODIFIED_MID_POINT: {
                    xc = LOWORD(lp);
                    yc = HIWORD(lp);
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse Algorithms
                case ELLIPSE_DIRECT:
                case ELLIPSE_POLAR:
                case ELLIPSE_MID_POINT: {
                    xc = LOWORD(lp);
                    yc = HIWORD(lp);
                    break;
                }

            //!=========================================================================================================

                // ? Convex Filling
                case FILL_CONVEX: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    points.push_back({x, y});
                    break;
                }

                // ? Recursive Flood Fill
                case FILL_RECURSIVE: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    COLORREF bgColor = GetPixel(hdc, x, y);
                    RecursiveFloodFill(hdc, x, y, c, bgColor);
                    ReleaseDC(hwnd, hdc);
                    break;
                }

                // ? Non-Recursive Flood Fill
                case FILL_NON_RECURSIVE: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    COLORREF bgColor = GetPixel(hdc, x, y);
                    NonRecursiveFloodFill(hdc, x, y, c, bgColor);
                    ReleaseDC(hwnd, hdc);
                    break;
                }

                default: {
                    break;
                }
            }

            break;
        }

        case WM_LBUTTONUP: {
            switch (currentTool) {

                // ? Line Algorithms
                case LINE_DDA:
                case LINE_MID_POINT:
                case LINE_PARAMETRIC: {
                    x2 = LOWORD(lp);
                    y2 = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    if(currentTool == LINE_DDA) {
                        DDALine(hdc, x1, y1, x2, y2, c);
                    }
                    if(currentTool == LINE_MID_POINT){
                        MidPointLine(hdc, x1, y1, x2, y2, c);
                    }
                    if(currentTool == LINE_PARAMETRIC){
                        ParametricLine(hdc, x1, y1, x2, y2, c);
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }

            //!=========================================================================================================

                // ? Circle Algorithms
                case CIRCLE_DIRECT:
                case CIRCLE_POLAR:
                case CIRCLE_ITERATIVE_POLAR:
                case CIRCLE_MID_POINT:
                case CIRCLE_MODIFIED_MID_POINT: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    r = (int)round(sqrt((x-xc)*(x-xc) + (y-yc)*(y-yc)));
                    if(currentTool == CIRCLE_DIRECT) {
                        DirectCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == CIRCLE_POLAR){
                        PolarCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == CIRCLE_ITERATIVE_POLAR){
                        IterativePolarCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == CIRCLE_MID_POINT){
                        MidPointCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == CIRCLE_MODIFIED_MID_POINT){
                        ModifiedMidPointCircle(hdc, xc, yc, r, c);
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse Algorithms
                case ELLIPSE_DIRECT:
                case ELLIPSE_POLAR:
                case ELLIPSE_MID_POINT: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    a = abs(x - xc), b = abs(y - yc);
                    if(currentTool == ELLIPSE_DIRECT) {
                        DirectEllipse(hdc, xc, yc, a, b, c);
                    }
                    if(currentTool == ELLIPSE_POLAR){
                        PolarEllipse(hdc, xc, yc, a, b, c);
                    }
                    if(currentTool == ELLIPSE_MID_POINT){
                        MidPointEllipse(hdc, xc, yc, a, b, c);
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }

                default: {
                    break;
                }
            }

            break;
        }


        case WM_RBUTTONDOWN: {
            switch (currentTool) {

                // ? Convex Filling
                case FILL_CONVEX: {
                    if(points.size() > 2) {
                        hdc = GetDC(hwnd);
                        ConvexFilling(hdc, points, c);
                        ReleaseDC(hwnd, hdc);
                        points.clear();
                    }
                    else{
                        MessageBox(hwnd, "At least 3 points are required to fill a convex polygon, "
                                         "please try again with new points", "Error", MB_OK);
                        points.clear();
                    }
                    break;
                }


                default: {
                    break;
                }

            }
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
