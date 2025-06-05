#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ProgramState.h"
#include "../include/Constants.h"
#include "../include/HandleLBUP.h"
#include "../include/LineAlgorithms.h"
#include "../include/CircleAlgorithms.h"
#include "../include/EllipseAlgorithms.h"
#include "../include/FillingAlgorithms.h"

using namespace std;
using namespace Constants;

void HandleLBUP(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , ProgramState &state){
    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints;
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

        //!=============================================================================================================

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

        //!=============================================================================================================

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


        //!=============================================================================================================

        // ? Filling Algorithms
        case FILL_CIRCLE_LINES: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            r = (int)round(sqrt((x-xc)*(x-xc) + (y-yc)*(y-yc)));
            FillQuarterCircleWithLines(hdc, xc, yc, r, c);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case FILL_CIRCLE_CIRCLES: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            r = (int)round(sqrt((x-xc)*(x-xc) + (y-yc)*(y-yc)));
            FillQuarterCircleWithCircles(hdc, xc, yc, r, c);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case FILL_SQUARE_HERMITE_V: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            int size = abs(x2 - x1) ;
            FillSquareWithHermiteVertical (hdc , x1 , y1 , size , c );
            ReleaseDC(hwnd, hdc);

            break;
        }
        case FILL_RECT_BEZIER_H: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            int h = abs (y2 - y1 ) , w= abs(x2 - x1) ;
            FillRectangleWithBezierHorizontal(hdc , x1 , y1 , w , h , c );
            ReleaseDC(hwnd, hdc);

            break;
        }

        //!=============================================================================================================

        // ? Set Clipping Window
        case CLIP_RECT_WINDOW: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            rectWin.topLeft.x = float(x1) , rectWin.topLeft.y = float(y1) ,
            rectWin.bottomRight.x = float(x2) , rectWin.bottomRight.y = float(y2);
            rectClipActive = true;
            // ? Draw the rectangle window
            MidPointLine(hdc , x1 , y1 , x2 , y1 , c);
            MidPointLine(hdc , x1 , y1 , x1 , y2 , c);
            MidPointLine(hdc , x2 , y1 , x2 , y2 , c);
            MidPointLine(hdc , x1 , y2 , x2 , y2 , c);
            ReleaseDC(hwnd, hdc);
            break;
        }
        case CLIP_SQR_WINDOW: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            squareWin.topLeft.x = float(x1) , squareWin.topLeft.y = float(y1);
            int width = abs(x2 - x1);
            squareWin.side = float(width);
            // ? Draw the square window
            MidPointLine(hdc , x1 , y1 , x1 + width , y1 , c);
            MidPointLine(hdc , x1 , y1 , x1 , y1 + width , c);
            MidPointLine(hdc , x1 + width , y1 , x1 + width , y1 + width , c);
            MidPointLine(hdc , x1 , y1 + width , x1 + width , y1 + width , c);
            squareClipActive = true;
            ReleaseDC(hwnd, hdc);
            break;
        }
        case CLIP_CIRCLE_WINDOW: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            circleWin.center.x = float(xc) , circleWin.center.y = float(yc);
            r = (int)round(sqrt((x-xc)*(x-xc) + (y-yc)*(y-yc)));
            circleWin.radius = float(r);
            // ? Draw the circle window
            MidPointCircle(hdc , xc , yc , r , c);
            circleClipActive = true;
            ReleaseDC(hwnd, hdc);
            break;
        }

        case CLIP_RECT_LINE:{
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            Point p1{} , p2{};
            p1.x = float(x1) , p1.y = float(y1);
            p2.x = float(x2) , p2.y = float(y2);

            bool res = ClippingAlgorithms::clipLineRectangle(p1 , p2 , rectWin);
            if (res) {
                // ? Draw the clipped line
                MidPointLine(hdc , p1.x , p1.y , p2.x , p2.y , c);
            }
            ReleaseDC(hwnd, hdc);
            break;
        }
        case CLIP_SQR_LINE: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            hdc = GetDC(hwnd);
            Point p1{} , p2{};
            p1.x = float(x1) , p1.y = float(y1);
            p2.x = float(x2) , p2.y = float(y2);
            bool res = ClippingAlgorithms::clipLineSquare(p1 , p2 , squareWin);
            if (res) {
                // ? Draw the clipped line
                MidPointLine(hdc , p1.x , p1.y , p2.x , p2.y , c);
            }
            ReleaseDC(hwnd, hdc);
            break;
        }
        case CLIP_CIRCLE_LINE: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            hdc = GetDC(hwnd);
            Point p1{} , p2{};
            p1.x = float(xc) , p1.y = float(yc);
            p2.x = float(x) , p2.y = float(y);
            bool res = ClippingAlgorithms::clipLineCircle(p1 , p2 , circleWin);
            if (res) {
                // ? Draw the clipped line
                MidPointLine(hdc , p1.x , p1.y , p2.x , p2.y , c);
            }
            ReleaseDC(hwnd, hdc);
            break;
        }


        default: {
            break;
        }
    }

}