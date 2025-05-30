#include <Windows.h>
#include <bits/stdc++.h>
#include "include/Constants.h"
#include "include/MainMenu.h"
#include "./include/LineAlgorithms.h"
#include "./include/CircleAlgorithms.h"
#include "./include/EllipseAlgorithms.h"
#include "./include/FillingAlgorithms.h"
#include "./include/ClippingAlgorithms.h"
#include "./include/CurvesAlgorithms.h"

using namespace std;
using namespace Constants;

HBRUSH BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    HMENU mainMenu;
    static int x1 = 0, y1 = 0,
               x2 = 0, y2 = 0,
               xc = 0, yc = 0, r = 0 ,
               x = 0, y = 0;
    static vector<POINT> points;
    static int currentTool = 0;
    static COLORREF c = RGB(255, 0, 0);
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

            // TODO: WM_COMMAND

            switch (LOWORD(wp)) {

                // ? MAIN_MENU
                case CLEAR: {
                    // TODO: CLEAR
                    break;
                }
                case SAVE : {
                    // TODO: SAVE
                    break;
                }
                case LOAD : {
                    // TODO: LOAD
                    break;
                }

            //!=========================================================================================================

                // ? BG_COLOR
                case BG_WHITE: {
                    // ! BG_COLOR_WHITE
                    BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }
                case BG_BLACK: {
                    // ! BG_COLOR_BLACK
                    BGBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }

            //!=========================================================================================================

                case CURSOR_ARROW: {
                    // ! CURSOR_ARROW
                    HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                    SetCursor(hCursor);
                    break;
                }
                case CURSOR_CROSS: {
                    // ! CURSOR_CROSS
                    HCURSOR hCursor = LoadCursor(nullptr, IDC_CROSS);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                    SetCursor(hCursor);
                    break;
                }

            //!=========================================================================================================

                // ? SHAPE_COLOR
                case SHAPE_RED: {
                    // ! SHAPE_COLOR_RED
                    c = RGB(255, 0, 0);
                    break;
                }
                case SHAPE_GREEN: {
                    // ! SHAPE_COLOR_GREEN
                    c = RGB(0, 255, 0);
                    break;
                }
                case SHAPE_BLUE: {
                    // ! SHAPE_COLOR_BLUE
                    c = RGB(0, 0, 255);
                    break;
                }

            //!=========================================================================================================

                // ? Line
                case LINE_DDA: {
                    // ! DDA
                    currentTool = LINE_DDA;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a DDA Line.", "DDA Line", MB_OK);
                    break;
                }
                case LINE_MID_POINT: {
                    // ! Midpoint
                    currentTool = LINE_MID_POINT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Line.", "Midpoint Line", MB_OK);
                    break;
                }
                case LINE_PARAMETRIC: {
                    // ! Parametric
                    currentTool = LINE_PARAMETRIC;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Parametric Line.", "Parametric Line", MB_OK);
                    break;
                }

            //!=========================================================================================================

                // ? Circle
                case CIRCLE_DIRECT: {
                    // ! Direct
                    currentTool = CIRCLE_DIRECT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Direct Circle.", "Direct Circle", MB_OK);
                    break;
                }
                case CIRCLE_POLAR: {
                    // ! Polar
                    currentTool = CIRCLE_POLAR;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Polar Circle.", "Polar Circle", MB_OK);
                    break;
                }
                case CIRCLE_ITERATIVE_POLAR: {
                    // ! Iterative Polar
                    currentTool = CIRCLE_ITERATIVE_POLAR;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw an Iterative Polar Circle.", "Iterative Polar Circle", MB_OK);
                    break;
                }
                case CIRCLE_MID_POINT: {
                    // ! Midpoint
                    currentTool = CIRCLE_MID_POINT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Circle.", "Midpoint Circle", MB_OK);
                    break;
                }
                case CIRCLE_MODIFIED_MID_POINT: {
                    // ! Modified Midpoint
                    currentTool = CIRCLE_MODIFIED_MID_POINT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Modified Midpoint Circle.", "Modified Midpoint Circle", MB_OK);
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse
                case ELLIPSE_DIRECT: {
                    // ! Direct
                    currentTool = ELLIPSE_DIRECT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Direct Ellipse.", "Direct Ellipse", MB_OK);
                    break;
                }
                case ELLIPSE_POLAR: {
                    // ! Polar
                    currentTool = ELLIPSE_POLAR;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Polar Ellipse.", "Polar Ellipse", MB_OK);
                    break;
                }
                case ELLIPSE_MID_POINT: {
                    // ! Midpoint
                    currentTool = ELLIPSE_MID_POINT;
                    MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Ellipse.", "Midpoint Ellipse", MB_OK);
                    break;
                }

            //!=========================================================================================================

                case CARDINAL_SPLINE:{
                    // TODO: Cardinal_Spline_Curve
                    break;
                }

            //!=========================================================================================================

                // ? Filling
                case FILL_CIRCLE_LINES: {
                    // TODO: Filling Circle with lines
                    break;
                }
                case FILL_CIRCLE_CIRCLES: {
                    // TODO: Filling Circle with circles
                    break;
                }
                case FILL_SQUARE_HERMITE_V: {
                    // TODO: Filling Square with Hermit [Vertical]
                    break;
                }
                case FILL_RECT_BEZIER_H: {
                    // TODO: Filling Rectangle with Bezier [horizontal]
                    break;
                }
                case FILL_CONVEX:{
                    // ! Convex Filling
                    MessageBox(hwnd, "Left-click to enter points. When finished, right-click to start Convex Filling.", "Convex Filling", MB_OK);
                    currentTool = FILL_CONVEX;
                    break;
                }
                case FILL_NON_CONVEX:{
                    // TODO: Non-Convex Filling
                    break;
                }
                case FILL_RECURSIVE:{
                    // ! Recursive Flood Fill
                    MessageBox(hwnd , "Click inside the shape to start Recursive Flood Fill.", "Recursive Flood Fill", MB_OK);
                    currentTool = FILL_RECURSIVE;
                    break;
                }
                case FILL_NON_RECURSIVE:{
                    // ! Non-Recursive Flood Fill
                    MessageBox(hwnd , "Click inside the shape to start Non-Recursive Flood Fill.", "Non-Recursive Flood Fill", MB_OK);
                    currentTool = FILL_NON_RECURSIVE;
                    break;
                }

            //!=========================================================================================================

                // ? CLIPPING RECTANGLE
                case CLIP_RECT_POINT:{
                    // TODO: CLIPPING RECTANGLE POINT
                    break;
                }
                case CLIP_RECT_LINE:{
                    // TODO: CLIPPING RECTANGLE LINE
                    break;
                }
                case CLIP_RECT_POLYGON:{
                    // TODO: CLIPPING RECTANGLE POLYGON
                    break;
                }

            //!=========================================================================================================

                // ? CLIPPING SQUARE
                case CLIP_SQR_POINT:{
                    // TODO: CLIPPING SQUARE POINT
                    break;
                }
                case CLIP_SQR_LINE:{
                    // TODO: CLIPPING SQUARE LINE
                    break;
                }

            //!=========================================================================================================

                default:{
                    break;
                }

            }

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
                    int a = abs(x - xc), b = abs(y - yc);
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
