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

        default: {
            break;
        }
    }

}