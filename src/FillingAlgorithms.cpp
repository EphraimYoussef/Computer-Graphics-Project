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

void init (edgeTable t){
    for (int i = 0 ; i < maxHeight ; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}

void Edge2Table (POINT p1 , POINT p2 , edgeTable t){
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

void Polygon2Table(vector<POINT>& p,edgeTable t){
    POINT p1 = p.back();

    for (auto i: p) {
        POINT p2 = i;
        Edge2Table(p1,p2,t);
        p1 = i;
    }
}

void Table2Screen(HDC hdc , edgeTable t , COLORREF c){
    for (int y = 0; y < maxHeight; ++y) {
        if(t[y].xLeft < t[y].xRight) {
            ParametricLine(hdc, (int)(t[y].xLeft), y, (int)(t[y].xRight), y, c);
        }
    }
}

void ConvexFilling(HDC hdc , vector<POINT>& p , COLORREF c){
    edgeTable t;
    init(t);
    Polygon2Table(p,t);
    Table2Screen(hdc , t ,c);
}
