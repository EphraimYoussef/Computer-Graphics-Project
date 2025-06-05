#ifndef PROJECT_PROGRAMSTATE_H
#define PROJECT_PROGRAMSTATE_H

#include <windows.h>
#include <bits/stdc++.h>
#include "CurvesAlgorithms.h"
#include "ClippingAlgorithms.h"

using namespace std;

struct ProgramState {
    HBRUSH BGBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
    COLORREF c = RGB(255, 0, 0);
    int currentTool = 0;
    int x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0;
    int xc = 0 , yc = 0 , a = 0 , b = 0;
    int r = 0 , x = 0 , y = 0;
    vector<POINT> convexPoints , nonConvexPoints ;
    vector<Vector2> splinePoints;
    vector<Point> clipPoints;
    struct Rectangle rectangleWindow;
    struct Circle circleWindow;
    struct Square squareWindow;
    bool rectClipActive = false , circleClipActive = false , sqrClipActive = false;
};

#endif //PROJECT_PROGRAMSTATE_H
