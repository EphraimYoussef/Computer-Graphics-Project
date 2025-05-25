#include <Windows.h>



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    HMENU mainMenu;

    switch (msg) {

        case WM_CREATE: {

            // TODO:BG_COLOR
            // ? command ID -> 1#
            HMENU BGColor = CreatePopupMenu();
            AppendMenu(BGColor, MF_STRING, 11, "White");
            AppendMenu(BGColor, MF_STRING, 12, "Black");

            //!=========================================================================================================

            // TODO:CURSOR_Change
            // ? command ID -> 2#
            HMENU Cursor = CreatePopupMenu();
            AppendMenu(Cursor, MF_STRING, 21, "Arrow");
            AppendMenu(Cursor, MF_STRING, 22, "Cross");

            //!=========================================================================================================

            // TODO:SHAPE_COLOR
            // ? command ID -> 3#
            HMENU ShapeColor = CreatePopupMenu();
            AppendMenu(ShapeColor, MF_STRING, 31, "Red");
            AppendMenu(ShapeColor, MF_STRING, 32, "Green");
            AppendMenu(ShapeColor, MF_STRING, 33, "Blue");

            //!=========================================================================================================

            // TODO:LINE
            // ? command ID -> 41#
            HMENU lineAlgorithms = CreatePopupMenu();
            AppendMenu(lineAlgorithms, MF_STRING, 411, "DDA");
            AppendMenu(lineAlgorithms, MF_STRING, 412, "Mid point");
            AppendMenu(lineAlgorithms, MF_STRING, 413, "Parametric");

            //*=========================================================================================================

            // TODO:CIRCLE
            // ? command ID -> 42#
            HMENU circleAlgorithms = CreatePopupMenu();
            AppendMenu(circleAlgorithms, MF_STRING, 421, "Direct");
            AppendMenu(circleAlgorithms, MF_STRING, 422, "Polar");
            AppendMenu(circleAlgorithms, MF_STRING, 423, "Iterative Polar");
            AppendMenu(circleAlgorithms, MF_STRING, 424, "Mid point");
            AppendMenu(circleAlgorithms, MF_STRING, 425, "Modified Mid point");

            //*=========================================================================================================

            // TODO:ELLIPSE
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
            AppendMenu(Shape, MF_STRING, 44, "Cardinal Spline Curve ");

            //!=========================================================================================================

            // TODO:FILLING
            // ? command ID -> 5#
            HMENU Filling = CreatePopupMenu();
            AppendMenu(Filling, MF_STRING, 51, "Filling Circle with lines");
            AppendMenu(Filling, MF_STRING, 52, "Filling Circle with circles");
            AppendMenu(Filling, MF_STRING, 53, "Filling Square with Hermit [Vertical] ");
            AppendMenu(Filling, MF_STRING, 54, "Filling Rectangle with Bezier [horizontal] ");
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

            break;
        }

        case WM_LBUTTONDOWN: {

            // TODO: LBUTTONDOWN

            break;
        }

        case WM_LBUTTONUP: {

            // TODO: LBUTTONUP

            break;
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
    WNDCLASS wc = {};
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wc.lpszClassName = "2D drawing program";
    wc.lpszMenuName = nullptr;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hi;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("2D drawing program",
                             "2D drawing program",
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT,
                             CW_USEDEFAULT, nullptr, nullptr, hi, nullptr);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}