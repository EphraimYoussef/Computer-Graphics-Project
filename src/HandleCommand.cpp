#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/HandleCommand.h"
#include "../include/Constants.h"
#include "../include/ProgramState.h"
#include "../include/SaveAndLoad.h"

using namespace std;
using namespace Constants;

void HandleCommand(HWND hwnd, WPARAM wp, ProgramState& state) {

    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;

    switch (LOWORD(wp)) {

        // ? MAIN_MENU
        case CLEAR: {
            state.convexPoints.clear();
            state.nonConvexPoints.clear();
            state.currentTool = 0;
            InvalidateRect(hwnd, nullptr, TRUE);
            UpdateWindow(hwnd);
            break;
        }
        case SAVE : {
            // TODO: SAVE
            SaveWindowToFile(hwnd, "output.bmp");
            break;
        }
        case LOAD : {
            // TODO: LOAD
            LoadImageToWindow(hwnd, "output.bmp");
            break;
        }

        //!=============================================================================================================

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
        case BG_GRAY: {
            // ! BG_COLOR_GRAY
            BGBrush = (HBRUSH) GetStockObject(GRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_LT_GRAY: {
            // ! BG_COLOR_LIGHT_GRAY
            BGBrush = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_DK_GRAY: {
            // ! BG_COLOR_DARK_GRAY
            BGBrush = (HBRUSH) GetStockObject(DKGRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }


        //!=============================================================================================================

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
        case CURSOR_HAND: {
            // ! CURSOR_HAND
            HCURSOR hCursor = LoadCursor(nullptr, IDC_HAND);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
            SetCursor(hCursor);
            break;
        }

        //!=============================================================================================================

        // ? SHAPE_COLOR
        case SHAPE_RED: {
            // ! SHAPE_COLOR_RED
            c = RED;
            break;
        }
        case SHAPE_GREEN: {
            // ! SHAPE_COLOR_GREEN
            c = GREEN;
            break;
        }
        case SHAPE_BLUE: {
            // ! SHAPE_COLOR_BLUE
            c = BLUE;
            break;
        }
        case SHAPE_YELLOW: {
            // ! SHAPE_COLOR_YELLOW
            c = YELLOW;
            break;
        }
        case SHAPE_MAGENTA: {
            // ! SHAPE_COLOR_MAGENTA
            c = MAGENTA;
            break;
        }
        case SHAPE_CYAN: {
            // ! SHAPE_COLOR_CYAN
            c = CYAN;
            break;
        }
        case SHAPE_ORANGE: {
            // ! SHAPE_COLOR_ORANGE
            c = ORANGE;
            break;
        }
        case SHAPE_PURPLE: {
            // ! SHAPE_COLOR_PURPLE
            c = PURPLE;
            break;
        }

        //!=============================================================================================================

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

        //!=============================================================================================================

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

        //!=============================================================================================================

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

        //!=============================================================================================================

        case CARDINAL_SPLINE:{
            // TODO: Cardinal_Spline_Curve
            break;
        }

        //!=============================================================================================================

        // ? Filling
        case FILL_CIRCLE_LINES: {
            // TODO: Filling Circle with lines
            currentTool = FILL_CIRCLE_LINES;

            MessageBox(hwnd, "Input the quarter in the console\nClick and hold the left mouse button, then release it to draw a Filling the quarter of the Circle with lines.", "Filling Circle with lines", MB_OK);

            break;
        }
        case FILL_CIRCLE_CIRCLES: {
            // TODO: Filling Circle with circles
            currentTool = FILL_CIRCLE_CIRCLES;
            MessageBox(hwnd, "Input the quarter in the console\nClick and hold the left mouse button, then release it to draw a Filling the quarter of the Circle with Circles.", "Filling Circle with Circles", MB_OK);
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
            MessageBox(hwnd, "Left-click to enter convexPoints. When finished, right-click to start Convex Filling.", "Convex Filling", MB_OK);
            currentTool = FILL_CONVEX;
            break;
        }
        case FILL_NON_CONVEX:{
            // ! Non-Convex Filling
            MessageBox(hwnd, "Left-click to enter nonConvexPoints. When finished, right-click to start Non-Convex Filling.", "Non-Convex Filling", MB_OK);
            currentTool = FILL_NON_CONVEX;
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

        //!=============================================================================================================

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

        //!=============================================================================================================

        // ? CLIPPING SQUARE
        case CLIP_SQR_POINT:{
            // TODO: CLIPPING SQUARE POINT
            break;
        }
        case CLIP_SQR_LINE:{
            // TODO: CLIPPING SQUARE LINE
            break;
        }

        //!=============================================================================================================

        default:{
            break;
        }

    }

}