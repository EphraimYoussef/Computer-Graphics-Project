#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ProgramState.h"
#include "../include/Constants.h"
#include "../include/HandleRBDown.h"
#include "../include/LineAlgorithms.h"
#include "../include/FillingAlgorithms.h"

using namespace std;
using namespace Constants;

void HandleRBDown(HWND hwnd, WPARAM wp , LPARAM lp , HDC hdc , ProgramState &state){

    static HBRUSH &BGBrush = state.BGBrush;
    static int &x1 = state.x1 , &y1 = state.y1, &x2 = state.x2, &y2 = state.y2 , &x = state.x, &y = state.y;
    static int &xc = state.xc, &yc = state.yc, &r = state.r, &a = state.a, &b = state.b;
    static vector<POINT>& convexPoints = state.convexPoints , &nonConvexPoints = state.nonConvexPoints ;
    static vector<Vector2>& splinePoints = state.splinePoints;
    static vector<Point>& clipPoints = state.clipPoints;
    static int& currentTool = state.currentTool;
    static struct Rectangle &rectWin = state.rectangleWindow;
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

        // ? Cardinal Spline
        case CARDINAL_SPLINE: {
            if(splinePoints.size() > 2) {
                hdc = GetDC(hwnd);
                CardinalSpline(hdc, splinePoints , 0.5 , c);
                ReleaseDC(hwnd, hdc);
                splinePoints.clear();
            }
            else{
                MessageBox(hwnd, "At least 3 points are required to fill a cardinal spline, "
                                 "please try again with new points", "Error", MB_OK);
                splinePoints.clear();
            }
            break;
        }

        // ? Clipping Rectangle
        case CLIP_RECT_POLYGON:{
            ClippingAlgorithms::clipPolygonRectangle(clipPoints, rectWin);
            Point p1 = clipPoints.back();
            hdc = GetDC(hwnd);
            for(auto p2 : clipPoints){
                MidPointLine(hdc , (int)round(p1.x) , (int)round(p1.y) , (int)round(p2.x) , (int)round(p2.y) , c );
                p1 = p2;
            }
            ReleaseDC(hwnd, hdc);
            clipPoints.clear();
            break;
        }

        default: {
            break;
        }

    }
}