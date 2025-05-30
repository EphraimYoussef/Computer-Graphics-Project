#ifndef PROJECT_PROGRAMSTATE_H
#define PROJECT_PROGRAMSTATE_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

struct ProgramState {
    HBRUSH BGBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    COLORREF c = RGB(255, 0, 0);
    int currentTool = 0;
    int x1 = 0 , y1 = 0 , x2 = 0 , y2 = 0;
    int xc = 0 , yc = 0 , a = 0 , b = 0;
    int r = 0 , x = 0 , y = 0;
    vector<POINT> points;
};

#endif //PROJECT_PROGRAMSTATE_H
