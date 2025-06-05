#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ProgramState.h"
#include "../include/Constants.h"
#include "../include/HandleLBDown.h"
#include "../include/LineAlgorithms.h"
#include "../include/CircleAlgorithms.h"
#include "../include/EllipseAlgorithms.h"
#include "../include/FillingAlgorithms.h"
#include "../include/ClippingAlgorithms.h"

using namespace std;
using namespace Constants;

void HandleLBDown(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , ProgramState &state){

    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints , &nonConvexPoints = state.nonConvexPoints ;
    static vector<Vector2>& splinePoints = state.splinePoints;
    static vector<Point>& clipPoints = state.clipPoints;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;
    static struct Rectangle &rectWin = state.rectangleWindow;
    static struct Square &squareWin = state.squareWindow;
    static struct Circle &circleWin = state.circleWindow;
    static bool & rectClipActive = state.rectClipActive
    , & squareClipActive = state.sqrClipActive, & circleClipActive = state.circleClipActive;

    switch (currentTool) {

        // ? Line Algorithms
        case LINE_DDA:
        case LINE_MID_POINT:
        case LINE_PARAMETRIC: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            DrawPoint(hwnd , x1, y1);
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
            DrawPoint(hwnd, xc, yc);
            break;
        }

        //!=========================================================================================================

        // ? Ellipse Algorithms
        case ELLIPSE_DIRECT:
        case ELLIPSE_POLAR:
        case ELLIPSE_MID_POINT: {
            xc = LOWORD(lp);
            yc = HIWORD(lp);
            DrawPoint(hwnd, xc, yc);
            break;
        }

        //!=========================================================================================================

        // ? Filling Algorithms
        case FILL_CONVEX: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            convexPoints.push_back({x, y});
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        }
        case FILL_NON_CONVEX: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            nonConvexPoints.push_back({x, y});
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        }
        case FILL_RECURSIVE: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            COLORREF bgColor = GetPixel(hdc, x, y);
            RecursiveFloodFill(hdc, x, y, c, bgColor);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case FILL_NON_RECURSIVE: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            COLORREF bgColor = GetPixel(hdc, x, y);
            NonRecursiveFloodFill(hdc, x, y, c, bgColor);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case FILL_CIRCLE_LINES:
        case FILL_CIRCLE_CIRCLES: {
            xc = LOWORD(lp);
            yc = HIWORD(lp);
            break;
        }
        case FILL_SQUARE_HERMITE_V:
        case FILL_RECT_BEZIER_H: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            break;
        }

        // !=========================================================================================================

        // ? Curve
        case CARDINAL_SPLINE: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            splinePoints.emplace_back(round(x), round(y));
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        }

        // !=========================================================================================================

        // ? Clipping
        case CLIP_RECT_WINDOW:
        case CLIP_SQR_WINDOW: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            DrawPoint(hwnd, x1, y1);
            break;
        }
        case CLIP_CIRCLE_WINDOW: {
            xc = LOWORD(lp);
            yc = HIWORD(lp);
            DrawPoint(hwnd, xc, yc);
            break;
        }

        case CLIP_RECT_POINT: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            Point p1{};
            p1.x = float(x1);
            p1.y = float(y1);
            bool res = ClippingAlgorithms::clipPointRectangle(p1, rectWin);
            if (res) {
                hdc = GetDC(hwnd);
                Ellipse(hdc, (int)round(p1.x) - 2, (int)round(p1.y) - 2, (int)round(p1.x) + 2, (int)round(p1.y) + 2);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        case CLIP_SQR_POINT: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            Point p1{};
            p1.x = float(x1);
            p1.y = float(y1);
            bool res = ClippingAlgorithms::clipPointSquare(p1, squareWin);
            if (res) {
                hdc = GetDC(hwnd);
                Ellipse(hdc, (int)round(p1.x) - 2, (int)round(p1.y) - 2, (int)round(p1.x) + 2, (int)round(p1.y) + 2);
                ReleaseDC(hwnd, hdc);
            }
            break;
        }
        case CLIP_CIRCLE_POINT: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            Point p1{};
            p1.x = float(x1);
            p1.y = float(y1);
            bool res = ClippingAlgorithms::isPointInsideCircle(p1, circleWin);
            if (res) {
                hdc = GetDC(hwnd);
                Ellipse(hdc, (int) round(p1.x) - 2, (int) round(p1.y) - 2, (int) round(p1.x) + 2,
                        (int) round(p1.y) + 2);
            }
        }

        case CLIP_RECT_LINE:
        case CLIP_SQR_LINE:
        case CLIP_CIRCLE_LINE: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            break;
        }

        case CLIP_RECT_POLYGON: {
            x1 = LOWORD(lp);
            y1 = HIWORD(lp);
            Point p{};
            p.x = float(x1);
            p.y = float(y1);
            clipPoints.push_back(p);
            InvalidateRect(hwnd, nullptr, FALSE);
            break;
        }

        default: {
            break;
        }
    }

}
