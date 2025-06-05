#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/HandleCommand.h"
#include "../include/Constants.h"
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
    static bool & rectClipActive = state.rectClipActive
    , & squareClipActive = state.sqrClipActive, & circleClipActive = state.circleClipActive;

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
            SaveWindow(hwnd);
            break;
        }
        case LOAD : {
            LoadWindow(hwnd);
            break;
        }

        //!=============================================================================================================

        // ? BG_COLOR
        case BG_WHITE: {
            BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_BLACK: {
            BGBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_GRAY: {
            BGBrush = (HBRUSH) GetStockObject(GRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_LT_GRAY: {
            BGBrush = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }
        case BG_DK_GRAY: {
            BGBrush = (HBRUSH) GetStockObject(DKGRAY_BRUSH);
            InvalidateRect(hwnd, nullptr, TRUE);
            break;
        }


        //!=============================================================================================================

        // ? CURSOR
        case CURSOR_ARROW: {
            HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
            SetCursor(hCursor);
            break;
        }
        case CURSOR_CROSS: {
            HCURSOR hCursor = LoadCursor(nullptr, IDC_CROSS);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
            SetCursor(hCursor);
            break;
        }
        case CURSOR_HAND: {
            HCURSOR hCursor = LoadCursor(nullptr, IDC_HAND);
            SetClassLongPtr(hwnd, GCLP_HCURSOR, (LONG_PTR)hCursor);
            SetCursor(hCursor);
            break;
        }

        //!=============================================================================================================

        // ? SHAPE_COLOR
        case SHAPE_RED: {
            c = RED;
            break;
        }
        case SHAPE_GREEN: {
            c = GREEN;
            break;
        }
        case SHAPE_BLUE: {
            c = BLUE;
            break;
        }
        case SHAPE_YELLOW: {
            c = YELLOW;
            break;
        }
        case SHAPE_MAGENTA: {
            c = MAGENTA;
            break;
        }
        case SHAPE_CYAN: {
            c = CYAN;
            break;
        }
        case SHAPE_ORANGE: {
            c = ORANGE;
            break;
        }
        case SHAPE_PURPLE: {
            c = PURPLE;
            break;
        }

        //!=============================================================================================================

        // ? Line
        case LINE_DDA: {
            currentTool = LINE_DDA;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a DDA Line.", "DDA Line", MB_OK);
            break;
        }
        case LINE_MID_POINT: {
            currentTool = LINE_MID_POINT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Line.", "Midpoint Line", MB_OK);
            break;
        }
        case LINE_PARAMETRIC: {
            currentTool = LINE_PARAMETRIC;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Parametric Line.", "Parametric Line", MB_OK);
            break;
        }

        //!=============================================================================================================

        // ? Circle
        case CIRCLE_DIRECT: {
            currentTool = CIRCLE_DIRECT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Direct Circle.", "Direct Circle", MB_OK);
            break;
        }
        case CIRCLE_POLAR: {
            currentTool = CIRCLE_POLAR;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Polar Circle.", "Polar Circle", MB_OK);
            break;
        }
        case CIRCLE_ITERATIVE_POLAR: {
            currentTool = CIRCLE_ITERATIVE_POLAR;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw an Iterative Polar Circle.", "Iterative Polar Circle", MB_OK);
            break;
        }
        case CIRCLE_MID_POINT: {
            currentTool = CIRCLE_MID_POINT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Circle.", "Midpoint Circle", MB_OK);
            break;
        }
        case CIRCLE_MODIFIED_MID_POINT: {
            currentTool = CIRCLE_MODIFIED_MID_POINT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Modified Midpoint Circle.", "Modified Midpoint Circle", MB_OK);
            break;
        }

        //!=============================================================================================================

        // ? Ellipse
        case ELLIPSE_DIRECT: {
            currentTool = ELLIPSE_DIRECT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Direct Ellipse.", "Direct Ellipse", MB_OK);
            break;
        }
        case ELLIPSE_POLAR: {
            currentTool = ELLIPSE_POLAR;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Polar Ellipse.", "Polar Ellipse", MB_OK);
            break;
        }
        case ELLIPSE_MID_POINT: {
            currentTool = ELLIPSE_MID_POINT;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Midpoint Ellipse.", "Midpoint Ellipse", MB_OK);
            break;
        }

        //!=============================================================================================================

        // ? Curve
        case CARDINAL_SPLINE:{
            currentTool = CARDINAL_SPLINE;
            MessageBox(hwnd, "Left-click to enter cardinal spline points. \n"
                             "When finished, right-click to start drawing the curve.", "Cardinal Spline Curve", MB_OK);
            break;
        }

        //!=============================================================================================================

        // ? Filling
        case FILL_CIRCLE_LINES: {
            currentTool = FILL_CIRCLE_LINES;
            MessageBox(hwnd, "1- Click and hold the left mouse button, then release it to draw a Filling quarter of the Circle with lines.\n\n"
                             "2- Input the quarter in the console for each draw ( 1 - 4 ).\n"
                             , "Filling Circle with lines", MB_OK);
            break;
        }
        case FILL_CIRCLE_CIRCLES: {
            currentTool = FILL_CIRCLE_CIRCLES;
            MessageBox(hwnd, "1- Click and hold the left mouse button, then release it to draw a Filling quarter of the Circle with circles.\n\n"
                             "2- Input the quarter in the console for each draw ( 1 - 4 ).\n"
                             , "Filling Circle with circles", MB_OK);
            break;
        }
        case FILL_SQUARE_HERMITE_V: {
            currentTool = FILL_SQUARE_HERMITE_V;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to determine the square side length based on the X axis"
                    , "Filling Square with Hermit Curve [Vertical]", MB_OK);
            break;
        }
        case FILL_RECT_BEZIER_H: {
            currentTool = FILL_RECT_BEZIER_H;
            MessageBox(hwnd, "Click and hold the left mouse button, then release it to determine the Rectangle width and height based on the X & Y axis"
                    , "Filling Rectangle with Bezier Curve [horizontal]", MB_OK);
            break;
        }
        case FILL_CONVEX:{
            MessageBox(hwnd, "Left-click to enter convexPoints. When finished, right-click to start Convex Filling.", "Convex Filling", MB_OK);
            currentTool = FILL_CONVEX;
            break;
        }
        case FILL_NON_CONVEX:{
            MessageBox(hwnd, "Left-click to enter nonConvexPoints. When finished, right-click to start Non-Convex Filling.", "Non-Convex Filling", MB_OK);
            currentTool = FILL_NON_CONVEX;
            break;
        }
        case FILL_RECURSIVE:{
            MessageBox(hwnd , "Click inside the shape to start Recursive Flood Fill.", "Recursive Flood Fill", MB_OK);
            currentTool = FILL_RECURSIVE;
            break;
        }
        case FILL_NON_RECURSIVE:{
            MessageBox(hwnd , "Click inside the shape to start Non-Recursive Flood Fill.", "Non-Recursive Flood Fill", MB_OK);
            currentTool = FILL_NON_RECURSIVE;
            break;
        }

        //!=============================================================================================================

        // ? CLIPPING RECTANGLE
        case CLIP_RECT_WINDOW: {
            currentTool = CLIP_RECT_WINDOW;
            MessageBox(hwnd, "Click in the top left corner and release it in the bottom right corner"
                             " to draw a Clipping Rectangle Window.", "Clipping Rectangle", MB_OK);
            break;
        }
        case CLIP_RECT_POINT:{
            if(rectClipActive){
                currentTool = CLIP_RECT_POINT;
                MessageBox(hwnd, "Click where you want to put the point to be clipped.", "Clipping Rectangle", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Rectangle Window first.", "Clipping Rectangle", MB_OK);
            }
            break;
        }
        case CLIP_RECT_LINE:{
            if(rectClipActive){
                currentTool = CLIP_RECT_LINE;
                MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Line to be clipped.", "Clipping Rectangle", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Rectangle Window first.", "Clipping Rectangle", MB_OK);
            }
            break;
        }
        case CLIP_RECT_POLYGON:{
            if(rectClipActive){
                currentTool = CLIP_RECT_POLYGON;
                MessageBox(hwnd, "Left-click to enter polygon points. When finished, right-click to start Clipping the Polygon.", "Clipping Rectangle", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Rectangle Window first.", "Clipping Rectangle", MB_OK);
            }
            break;
        }

        //!=============================================================================================================

        // ? CLIPPING SQUARE
        case CLIP_SQR_WINDOW: {
            currentTool = CLIP_SQR_WINDOW;
            MessageBox(hwnd, "Click in the top left corner and release it in the top right corner to determine the square side length"
                             " to draw a Clipping Square Window.", "Clipping Square", MB_OK);
            break;
        }
        case CLIP_SQR_POINT:{
            if(squareClipActive){
                currentTool = CLIP_SQR_POINT;
                MessageBox(hwnd, "Click where you want to put the point to be clipped.", "Clipping Square", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Square Window first.", "Clipping Square", MB_OK);
            }
            break;
        }
        case CLIP_SQR_LINE:{
            if(squareClipActive){
                currentTool = CLIP_SQR_LINE;
                MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Line to be clipped.", "Clipping Square", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Square Window first.", "Clipping Square", MB_OK);
            }
            break;
        }

        //!=============================================================================================================

        // ? CLIPPING CIRCLE
        case CLIP_CIRCLE_WINDOW: {
            currentTool = CLIP_CIRCLE_WINDOW;
            MessageBox(hwnd, "Click in the center and release it to determine the radius "
                             "to draw a Clipping Circle Window.", "Clipping Circle", MB_OK);
            break;
        }
        case CLIP_CIRCLE_POINT:{
            if(circleClipActive){
                currentTool = CLIP_CIRCLE_POINT;
                MessageBox(hwnd, "Click where you want to put the point to be clipped.", "Clipping Circle", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Circle Window first.", "Clipping Circle", MB_OK);
            }
            break;
        }
        case CLIP_CIRCLE_LINE:{
            if(circleClipActive){
                currentTool = CLIP_CIRCLE_LINE;
                MessageBox(hwnd, "Click and hold the left mouse button, then release it to draw a Line to be clipped.", "Clipping Circle", MB_OK);
            }
            else{
                MessageBox(hwnd, "You need to draw a Clipping Circle Window first.", "Clipping Circle", MB_OK);
            }
            break;
        }

        //!=============================================================================================================

        default:{
            break;
        }

    }

}