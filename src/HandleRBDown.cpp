#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ProgramState.h"
#include "../include/Constants.h"
#include "../include/HandleRBDown.h"
#include "../include/LineAlgorithms.h"
#include "../include/CircleAlgorithms.h"
#include "../include/EllipseAlgorithms.h"
#include "../include/FillingAlgorithms.h"

using namespace std;
using namespace Constants;

void HandleRBDown(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , ProgramState &state){

    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints , &nonConvexPoints = state.nonConvexPoints;
    static int& currentTool = state.currentTool;
    static COLORREF &c = state.c;

    switch (currentTool) {

        // ? Convex Filling
        case FILL_CONVEX: {
            if(convexPoints.size() > 2) {
                hdc = GetDC(hwnd);
                ConvexFilling(hdc, convexPoints, c);
                ReleaseDC(hwnd, hdc);
                convexPoints.clear();
            }
            else{
                MessageBox(hwnd, "At least 3 convexPoints are required to fill a convex polygon, "
                                 "please try again with new convexPoints", "Error", MB_OK);
                convexPoints.clear();
            }

            break;
        }

        // ? Non-Convex Filling
        case FILL_NON_CONVEX: {
            if(nonConvexPoints.size() > 2) {
                hdc = GetDC(hwnd);
                NonConvexFilling(hdc, nonConvexPoints, c);
                ReleaseDC(hwnd, hdc);
                nonConvexPoints.clear();
            }
            else{
                MessageBox(hwnd, "At least 3 non-convexPoints are required to fill a non-convex polygon, "
                                 "please try again with new non-convexPoints", "Error", MB_OK);
                nonConvexPoints.clear();
            }

            break;
        }

        default: {
            break;
        }

    }
}