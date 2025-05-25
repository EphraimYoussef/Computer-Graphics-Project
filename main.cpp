#include <Windows.h>



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    HDC hdc;
    HMENU mainMenu;

    switch (msg) {

        case WM_CREATE: {

            // ? command ID -> 1#
            HMENU BGColor = CreatePopupMenu();
            AppendMenu(BGColor, MF_STRING, 11, "White");
            AppendMenu(BGColor, MF_STRING, 12, "Black");

            //!=========================================================================================================

            // ? command ID -> 2#
            HMENU Cursor = CreatePopupMenu();
            AppendMenu(Cursor, MF_STRING, 21, "Arrow");
            AppendMenu(Cursor, MF_STRING, 22, "Cross");

            //!=========================================================================================================

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

            // ? command ID -> 4#
            HMENU Shape = CreatePopupMenu();
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)lineAlgorithms , "Line");
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)circleAlgorithms, "Circle");
            AppendMenu(Shape, MF_POPUP, (UINT_PTR)ellipseAlgorithms, "Ellipse");
            AppendMenu(Shape, MF_STRING, 44, "Cardinal Spline Curve ");

            //!=========================================================================================================

            // ? command ID -> 5#
            HMENU Filling = CreatePopupMenu();
            AppendMenu(Filling, MF_STRING, 51, "Filling Circle with lines");
            AppendMenu(Filling, MF_STRING, 52, "Filling Circle with circles");

            //!=========================================================================================================

            // ? command ID -> 10#
            mainMenu = CreateMenu();
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)BGColor, "Background Color");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Cursor, "Cursor");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)ShapeColor, "Shape Color");
            AppendMenu(mainMenu, MF_STRING, 101, "Clear");
            AppendMenu(mainMenu, MF_STRING, 102, "Save");
            AppendMenu(mainMenu, MF_STRING, 103, "Load");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Shape, "Choose Shape");
            AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Filling, "Filling");

            SetMenu(hwnd, mainMenu);
            break;
        }

        case WM_LBUTTONDOWN: {

            break;
        }

        case WM_LBUTTONUP: {

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
    wc.lpszClassName = "Task 1";
    wc.lpszMenuName = nullptr;
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance = hi;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("Task 1",
                             "Task 1",
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