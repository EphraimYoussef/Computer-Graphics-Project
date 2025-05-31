#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ProgramState.h"
#include "../include/Constants.h"
#include "../include/HandleLBDown.h"
#include "../include/LineAlgorithms.h"
#include "../include/CircleAlgorithms.h"
#include "../include/EllipseAlgorithms.h"
#include "../include/FillingAlgorithms.h"

using namespace std;
using namespace Constants;

void HandleLBDown(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , ProgramState &state){

    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints , &nonConvexPoints = state.nonConvexPoints;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;

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
            convexPoints.push_back({x, y});
            break;
        }

        // ? Non-Convex Filling
        case FILL_NON_CONVEX: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            nonConvexPoints.push_back({x, y});
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

}
