#include <windows.h>
#include <bits/stdc++.h>
#include "../include/FillingAlgorithms.h"
#include "../include/LineAlgorithms.h"

using namespace std;

const int maxHeight = 1080;

struct Entry{
    double xLeft , xRight;
};

typedef Entry edgeTable[maxHeight];

void initEdgeTableConvex (edgeTable t){
    for (int i = 0 ; i < maxHeight ; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}

void Edge2TableConvex (POINT p1 , POINT p2 , edgeTable t){
    if(p1.y == p2.y) {
        return;
    }
    if(p1.y > p2.y) {
        swap(p1, p2);
    }

    int y =p1.y;
    double x = p1.x;
    double mInv =(double) (p2.x - p1.x) / (p2.y - p1.y);

    while(y < p2.y){
        if(x < t[y].xLeft) {
            t[y].xLeft = ceil(x);
        }
        if(x > t[y].xRight) {
            t[y].xRight = floor(x);
        }
        y++;
        x+=mInv;
    }
}

void Polygon2TableConvex(vector<POINT>& p, edgeTable t){
    POINT p1 = p.back();

    for (auto i: p) {
        POINT p2 = i;
        Edge2TableConvex(p1, p2, t);
        p1 = i;
    }
}

void Table2ScreenConvex(HDC hdc , edgeTable t , COLORREF c){
    for (int y = 0; y < maxHeight; ++y) {
        if(t[y].xLeft < t[y].xRight) {
            ParametricLine(hdc, (int)(t[y].xLeft), y, (int)(t[y].xRight), y, c);
        }
    }
}

void ConvexFilling(HDC hdc , vector<POINT>& p , COLORREF c){
    edgeTable t;
    initEdgeTableConvex(t);
    Polygon2TableConvex(p, t);
    Table2ScreenConvex(hdc, t, c);
}


void RecursiveFloodFill(HDC hdc, int x, int y, COLORREF fillColor, COLORREF bgColor) {
    COLORREF current = GetPixel(hdc, x, y);
    if (current != bgColor || current == fillColor) {
        return;
    }
    SetPixel(hdc, x, y, fillColor);
    RecursiveFloodFill(hdc, x + 1, y, fillColor, bgColor);
    RecursiveFloodFill(hdc, x - 1, y, fillColor, bgColor);
    RecursiveFloodFill(hdc, x, y + 1, fillColor, bgColor);
    RecursiveFloodFill(hdc, x, y - 1, fillColor, bgColor);
}

void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF fillColor, COLORREF bgColor) {
    stack<POINT> stk;
    stk.push({x, y});
    while (!stk.empty()){
        POINT p = stk.top();
        stk.pop();
        COLORREF current = GetPixel(hdc,p.x, p.y);
        if(current != bgColor || current == fillColor) {
            continue;
        }
        SetPixel(hdc, p.x, p.y, fillColor);
        stk.push({p.x + 1, p.y});
        stk.push({p.x - 1, p.y});
        stk.push({p.x, p.y + 1});
        stk.push({p.x, p.y - 1});
    }
}


// ? Optimized version


//void NonRecursiveFloodFill(HDC hdc, int x, int y, COLORREF fillColor, COLORREF bgColor) {
//    if (fillColor == bgColor) {
//        return;
//    }
//    stack<POINT> stk;
//    set<pair<int, int>> visited;
//
//    stk.push({x, y});
//    visited.insert({x, y});
//
//    while (!stk.empty()) {
//        POINT p = stk.top();
//        stk.pop();
//        COLORREF current = GetPixel(hdc, p.x, p.y);
//        if (current != bgColor) {
//            continue;
//        }
//        SetPixel(hdc, p.x, p.y, fillColor);
//        pair<int, int> neighbors[] = {
//                {p.x + 1, p.y},
//                {p.x - 1, p.y},
//                {p.x, p.y + 1},
//                {p.x, p.y - 1}
//        };
//
//        for (auto& np : neighbors) {
//            if (!visited.count(np)) {
//                stk.push({np.first, np.second});
//                visited.insert(np);
//            }
//        }
//    }
//}

