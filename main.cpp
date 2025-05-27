#include <Windows.h>
#include <bits/stdc++.h>
#include "GraphicsAlgorithms.h"

HBRUSH BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    HMENU mainMenu;
    static int x1 = 0, y1 = 0,
               x2 = 0, y2 = 0,
               xc = 0, yc = 0, r = 0 ,
               x = 0, y = 0;
    static int currentTool = 0;
    static COLORREF c = RGB(255, 0, 0);
    switch (msg) {

        case WM_CREATE: {

            // ! BG_COLOR
            // ? command ID -> 1#
            HMENU BGColor = CreatePopupMenu();
            AppendMenu(BGColor, MF_STRING, 11, "White");
            AppendMenu(BGColor, MF_STRING, 12, "Black");

            //!=========================================================================================================

            // ! CURSOR_Change
            // ? command ID -> 2#
            HMENU Cursor = CreatePopupMenu();
            AppendMenu(Cursor, MF_STRING, 21, "Arrow");
            AppendMenu(Cursor, MF_STRING, 22, "Cross");

            //!=========================================================================================================

            // ! SHAPE_COLOR
            // ? command ID -> 3#
            HMENU ShapeColor = CreatePopupMenu();
            AppendMenu(ShapeColor, MF_STRING, 31, "Red");
            AppendMenu(ShapeColor, MF_STRING, 32, "Green");
            AppendMenu(ShapeColor, MF_STRING, 33, "Blue");

            //!=========================================================================================================

            // ! LINE
            // ? command ID -> 41#
            HMENU lineAlgorithms = CreatePopupMenu();
            AppendMenu(lineAlgorithms, MF_STRING, 411, "DDA");
            AppendMenu(lineAlgorithms, MF_STRING, 412, "Mid point");
            AppendMenu(lineAlgorithms, MF_STRING, 413, "Parametric");

            //*=========================================================================================================

            // ! CIRCLE
            // ? command ID -> 42#
            HMENU circleAlgorithms = CreatePopupMenu();
            AppendMenu(circleAlgorithms, MF_STRING, 421, "Direct");
            AppendMenu(circleAlgorithms, MF_STRING, 422, "Polar");
            AppendMenu(circleAlgorithms, MF_STRING, 423, "Iterative Polar");
            AppendMenu(circleAlgorithms, MF_STRING, 424, "Mid point");
            AppendMenu(circleAlgorithms, MF_STRING, 425, "Modified Mid point");

            //*=========================================================================================================

            // ! ELLIPSE
            // ? command ID -> 43#
            HMENU ellipseAlgorithms = CreatePopupMenu();
            AppendMenu(ellipseAlgorithms, MF_STRING, 431, "Direct");
            AppendMenu(ellipseAlgorithms, MF_STRING, 432, "Polar");
            AppendMenu(ellipseAlgorithms, MF_STRING, 433, "Mid point");

            //*=========================================================================================================

            // TODO:SHAPE_MENU
            // ? command ID -> 4#
            HMENU Shape = CreatePopupMenu();
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)lineAlgorithms , "Line");
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)circleAlgorithms, "Circle");
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)ellipseAlgorithms, "Ellipse");
            AppendMenu(Shape, MF_STRING, 44, "Cardinal Spline Curve");

            //!=========================================================================================================

            // TODO:FILLING
            // ? command ID -> 5#
            HMENU Filling = CreatePopupMenu();
            AppendMenu(Filling, MF_STRING, 51, "Filling Circle with lines");
            AppendMenu(Filling, MF_STRING, 52, "Filling Circle with circles");
            AppendMenu(Filling, MF_STRING, 53, "Filling Square with Hermit [Vertical]");
            AppendMenu(Filling, MF_STRING, 54, "Filling Rectangle with Bezier [horizontal]");
            AppendMenu(Filling, MF_STRING, 55, "Convex Filling");
            AppendMenu(Filling, MF_STRING, 56, "Non Convex Filling");
            AppendMenu(Filling, MF_STRING, 57, "Recursive Flood Fill");
            AppendMenu(Filling, MF_STRING, 58, "Non Recursive Flood Fill");

            //!=========================================================================================================

            // TODO:CLIPPING_RECTANGLE
            // ? command ID -> 61#
            HMENU clippingRect = CreatePopupMenu();
            AppendMenu(clippingRect, MF_STRING, 611, "Point");
            AppendMenu(clippingRect, MF_STRING, 612, "Line");
            AppendMenu(clippingRect, MF_STRING, 613, "Polygon");

            //*=========================================================================================================

            // TODO:CLIPPING_SQUARE
            // ? command ID -> 62#
            HMENU clippingSquare = CreatePopupMenu();
            AppendMenu(clippingSquare, MF_STRING, 621, "Point");
            AppendMenu(clippingSquare, MF_STRING, 622, "Line");

            //*=========================================================================================================

            // TODO:CLIPPING
            // ? command ID -> 6#
            HMENU clipping = CreatePopupMenu();
            AppendMenu(clipping, MF_POPUP, (UINT_PTR)clippingRect, "Clipping algorithms using Rectangle");
            AppendMenu(clipping, MF_POPUP, (UINT_PTR)clippingSquare, "Clipping algorithms using Square");

            //!=========================================================================================================

            // TODO:MAIN_MENU
            // ? command ID -> 10#
            mainMenu = CreateMenu();
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)BGColor, "Background Color");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Cursor, "Cursor");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)ShapeColor, "Shape Color");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Shape, "Choose Shape");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Filling, "Filling");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)clipping, "Clipping");
            AppendMenu(mainMenu, MF_STRING, 101, "Clear");
            AppendMenu(mainMenu, MF_STRING, 102, "Save");
            AppendMenu(mainMenu, MF_STRING, 103, "Load");

            SetMenu(hwnd, mainMenu);
            break;
        }

        case WM_COMMAND: {

            // TODO: WM_COMMAND

            switch (LOWORD(wp)) {

                // ? MAIN_MENU
                case 101: {
                    // TODO: CLEAR
                    break;
                }
                case 102 : {
                    // TODO: SAVE
                    break;
                }
                case 103 : {
                    // TODO: LOAD
                    break;
                }

            //!=========================================================================================================

                // ? BG_COLOR
                case 11: {
                    // ! BG_COLOR_WHITE
                    BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }
                case 12: {
                    // ! BG_COLOR_BLACK
                    BGBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
                    InvalidateRect(hwnd, nullptr, TRUE);
                    break;
                }

            //!=========================================================================================================

                case 21: {
                    // ! CURSOR_ARROW
                    HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                    SetCursor(hCursor);
                    break;
                }
                case 22: {
                    // ! CURSOR_CROSS
                    HCURSOR hCursor = LoadCursor(nullptr, IDC_CROSS);
                    SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
                    SetCursor(hCursor);
                    break;
                }

            //!=========================================================================================================

                // ? SHAPE_COLOR
                case 31: {
                    // ! SHAPE_COLOR_RED
                    c = RGB(255, 0, 0);
                    break;
                }
                case 32: {
                    // ! SHAPE_COLOR_GREEN
                    c = RGB(0, 255, 0);
                    break;
                }
                case 33: {
                    // ! SHAPE_COLOR_BLUE
                    c = RGB(0, 0, 255);
                    break;
                }

            //!=========================================================================================================

                // ? Line
                case 411: {
                    // ! DDA
                    currentTool = 411;
                    break;
                }
                case 412: {
                    // ! Midpoint
                    currentTool = 412;
                    break;
                }
                case 413: {
                    // ! Parametric
                    currentTool = 413;
                    break;
                }

            //!=========================================================================================================

                // ? Circle
                case 421: {
                    // ! Direct
                    currentTool = 421;
                    break;
                }
                case 422: {
                    // ! Polar
                    currentTool = 422;
                    break;
                }
                case 423: {
                    // ! Iterative Polar
                    currentTool = 423;
                    break;
                }
                case 424: {
                    // ! Midpoint
                    currentTool = 424;
                    break;
                }
                case 425: {
                    // ! Modified Midpoint
                    currentTool = 425;
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse
                case 431: {
                    // ! Direct
                    currentTool = 431;
                    break;
                }
                case 432: {
                    // ! Polar
                    currentTool = 432;
                    break;
                }
                case 433: {
                    // ! Midpoint
                    currentTool = 433;
                    break;
                }

            //!=========================================================================================================

                case 44:{
                    // TODO: Cardinal_Spline_Curve
                    break;
                }

            //!=========================================================================================================

                // ? Filling
                case 51: {
                    // TODO: Filling Circle with lines
                    break;
                }
                case 52: {
                    // TODO: Filling Circle with circles
                    break;
                }
                case 53: {
                    // TODO: Filling Square with Hermit [Vertical]
                    break;
                }
                case 54: {
                    // TODO: Filling Rectangle with Bezier [horizontal]
                    break;
                }
                case 55:{
                    // TODO: Convex Filling
                    break;
                }
                case 56:{
                    // TODO: Non-Convex Filling
                    break;
                }
                case 57:{
                    // TODO: Recursive Flood Fill
                    break;
                }
                case 58:{
                    // TODO: Non-Recursive Flood Fill
                    break;
                }

            //!=========================================================================================================

                // ? CLIPPING RECTANGLE
                case 611:{
                    // TODO: CLIPPING RECTANGLE POINT
                    break;
                }
                case 612:{
                    // TODO: CLIPPING RECTANGLE LINE
                    break;
                }
                case 613:{
                    // TODO: CLIPPING RECTANGLE POLYGON
                    break;
                }

            //!=========================================================================================================

                // ? CLIPPING SQUARE
                case 621:{
                    // TODO: CLIPPING SQUARE POINT
                    break;
                }
                case 622:{
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
                case 411:
                case 412:
                case 413: {
                    x1 = LOWORD(lp);
                    y1 = HIWORD(lp);
                    break;
                }

            //!=========================================================================================================

                // ? Circle Algorithms
                case 421:
                case 422:
                case 423:
                case 424:
                case 425: {
                    xc = LOWORD(lp);
                    yc = HIWORD(lp);
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse Algorithms
                case 431:
                case 432:
                case 433: {
                    xc = LOWORD(lp);
                    yc = HIWORD(lp);
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
                case 411:
                case 412:
                case 413: {
                    x2 = LOWORD(lp);
                    y2 = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    if(currentTool == 411) {
                        DDALine(hdc, x1, y1, x2, y2, c);
                    }
                    if(currentTool == 412){
                        MidPointLine(hdc, x1, y1, x2, y2, c);
                    }
                    if(currentTool == 413){
                        ParametricLine(hdc, x1, y1, x2, y2, c);
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }

            //!=========================================================================================================

                // ? Circle Algorithms
                case 421:
                case 422:
                case 423:
                case 424:
                case 425: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    r = (int)round(sqrt((x-xc)*(x-xc) + (y-yc)*(y-yc)));
                    if(currentTool == 421) {
                        DirectCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == 422){
                        PolarCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == 423){
                        IterativePolarCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == 424){
                        MidPointCircle(hdc, xc, yc, r, c);
                    }
                    if(currentTool == 425){
                        ModifiedMidPointCircle(hdc, xc, yc, r, c);
                    }
                    ReleaseDC(hwnd, hdc);
                    break;
                }

            //!=========================================================================================================

                // ? Ellipse Algorithms
                case 431:
                case 432:
                case 433: {
                    x = LOWORD(lp);
                    y = HIWORD(lp);
                    hdc = GetDC(hwnd);
                    int a = abs(x - xc), b = abs(y - yc);
                    if(currentTool == 431) {
                        DirectEllipse(hdc, xc, yc, a, b, c);
                    }
                    if(currentTool == 432){
                        PolarEllipse(hdc, xc, yc, a, b, c);
                    }
                    if(currentTool == 433){
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
