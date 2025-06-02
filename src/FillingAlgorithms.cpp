#include <windows.h>
#include <bits/stdc++.h>
#include "../include/FillingAlgorithms.h"
#include "../include/LineAlgorithms.h"
#include "../include/CircleAlgorithms.h"
#include "../include/CurvesAlgorithms.h"
using namespace std;

const int maxHeight = 1080;

struct Entry{
    double xLeft , xRight;
};

typedef Entry edgeTableConvex[maxHeight];

void initEdgeTableConvex (edgeTableConvex t){
    for (int i = 0 ; i < maxHeight ; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}

void Edge2TableConvex (POINT p1 , POINT p2 , edgeTableConvex t){
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

void Polygon2TableConvex(vector<POINT>& p, edgeTableConvex t){
    POINT p1 = p.back();

    for (auto i: p) {
        POINT p2 = i;
        Edge2TableConvex(p1, p2, t);
        p1 = i;
    }
}

void Table2ScreenConvex(HDC hdc , edgeTableConvex t , COLORREF c){
    for (int y = 0; y < maxHeight; ++y) {
        if(t[y].xLeft < t[y].xRight) {
            ParametricLine(hdc, (int)(t[y].xLeft), y, (int)(t[y].xRight), y, c);
        }
    }
}

void ConvexFilling(HDC hdc , vector<POINT>& p , COLORREF c){
    edgeTableConvex t;
    initEdgeTableConvex(t);
    Polygon2TableConvex(p, t);
    Table2ScreenConvex(hdc, t, c);
}


//!=============================================================================================

struct node {
    double x,mInv;
    int yMax;
    node(double x, int yMax, double mInv) : x(x), mInv(mInv), yMax(yMax) {}
};

bool operator < (const node& a, const node& b) {
    return a.x < b.x;
}

typedef list<node> LinkedList;

typedef LinkedList edgeTableNonConvex[maxHeight];


void edg2TableNonConvex(POINT p1, POINT p2, edgeTableNonConvex t) {
    if(p1.y == p2.y){
        return;
    }
    if(p1.y > p2.y){
        swap(p1,p2);
    }
    double mInv = double(p2.x - p1.x) / (p2.y - p1.y);
    t[p1.y].emplace_back(p1.x,p2.y, mInv);
}

void polygon2tableNonConvex(vector<POINT>& p, edgeTableNonConvex t) {
    POINT p1 = p.back();
    for (auto i : p) {
        POINT p2 = i;
        edg2TableNonConvex(p1, p2, t);
        p1 = i;
    }
}

void NonConvexFilling(HDC hdc, vector<POINT>& p, COLORREF c) {
    edgeTableNonConvex t;
    polygon2tableNonConvex(p, t);
    int y = 0;
    while(t[y].empty()){
        y++;
    }
    LinkedList active = t[y];
    while(!active.empty()){

        // ? sort by x  ------> 1
        active.sort();

        // ? for every 2 nodes in active draw a line -------> 2
        auto itt = active.begin();
        while (itt != active.end()) {
            node n1 = *itt++;
            if (itt == active.end()) {
                break;
            }
            node n2 = *itt++;
            DDALine(hdc, (int)ceil(n1.x), y, (int)floor(n2.x), y, c);
        }

        // ? update y
        y++;

        // ? for any node we reached yMax remove it ------> 3
        for (auto it = active.begin(); it != active.end(); ) {
            if (it->yMax == y) {
                it = active.erase(it);
            }
            else {
                ++it;
            }
        }

        // ? update x for every node ------> 4
        for(auto & i : active){
            i.x += i.mInv;
        }

        // ? if t[y] is not empty add to active ------> 5
        if(!t[y].empty()){
            active.insert(active.end(), t[y].begin(), t[y].end());
        }
    }
}


//!=============================================================================================


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

//!============================================================================================

void FillQuarterCircleWithLines(HDC hdc, int xc, int yc, int r, COLORREF c) {
    MessageBox(NULL, "Enter the quarter you want to fill in the console", "Fill Quarter Circle With Lines", MB_OK);
    cout << "Enter Quarter (1-4): ";
    int k; cin >> k;

    int x = 0;
    int y = r;
    int d = 3 - 2 * r;
    if(k >= 1 && k <= 4){
        MidPointCircle(hdc, xc, yc, r, c);
    }
    else {
        MessageBox(NULL, "Invalid Quarter Number , Try again " ,"Invalid Input!", MB_OK ) ;
        return;
    }
    while (x <= y) {
        switch (k) {
            case 1: // Top-Right
                MidPointLine(hdc, xc, yc, xc + x, yc - y, c);
                MidPointLine(hdc, xc, yc, xc + y, yc - x, c);
                break;
            case 2: // Top-Left
                DDALine(hdc, xc, yc, xc - x, yc - y, c);
                DDALine(hdc, xc, yc, xc - y, yc - x, c);
                break;
            case 3: // Bottom-Left
                DDALine(hdc, xc, yc, xc - x, yc + y, c);
                DDALine(hdc, xc, yc, xc - y, yc + x, c);
                break;
            case 4: // Bottom-Right
                DDALine(hdc, xc, yc, xc + x, yc + y, c);
                DDALine(hdc, xc, yc, xc + y, yc + x, c);
                break;
            default:
                cout << "Invalid quarter!\n";
                return;
        }

        if (d < 0) {
            d += 2 * x + 2;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}


void FillQuarterCircleWithCircles(HDC hdc, int xc, int yc, int r, COLORREF c){
    MessageBox(NULL, "Enter the quarter you want to fill in the console", "Fill Quarter Circle With Circles", MB_OK);
    cout << "Enter Quarter (1-4): ";
    int k; cin >> k;
    if(k >= 1 && k <= 4){
        MidPointCircle(hdc, xc, yc, r, c);
    }
    else {
        MessageBox(NULL, "Invalid Quarter Number , Try again " ,"Invalid Input!", MB_OK ) ;
        return;
    }
    for (int ri = 1; ri <= r; ++ri) {
        int x = 0;
        int y = ri;
        int d = 3 - 2 * ri;

        while (x <= y) {
            // Plot quarter pixels based on user choice
            switch (k) {
                case 1: // Top-Right
                    SetPixel(hdc, xc + x, yc - y, c);
                    SetPixel(hdc, xc + y, yc - x, c);
                    break;
                case 2: // Top-Left
                    SetPixel(hdc, xc - x, yc - y, c);
                    SetPixel(hdc, xc - y, yc - x, c);
                    break;
                case 3: // Bottom-Left
                    SetPixel(hdc, xc - x, yc + y, c);
                    SetPixel(hdc, xc - y, yc + x, c);
                    break;
                case 4: // Bottom-Right
                    SetPixel(hdc, xc + x, yc + y, c);
                    SetPixel(hdc, xc + y, yc + x, c);
                    break;
                default:
                    cout << "Invalid quarter!\n";
                    return;
            }

            if (d < 0) {
                d += 4 * x + 6;
            } else {
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }


}

//!============================================================================================

void FillSquareWithHermiteVertical(HDC hdc, int x1, int y1, int size ,  COLORREF c) {
    MessageBox(NULL, "Enter the step for the curve", "Curve Step", MB_OK);
    cout << "Enter the Curve Step : " ;
    int stp = 1 ;
    cin >> stp ;
    if (stp < 1 ){
        MessageBox(NULL, "Step must be bigger than 1 ", "Invalid input", MB_OK);
        return;
    }
    for (int x = x1; x <= x1 + size; x += stp) {
        Vector2 P0(x, y1);
        Vector2 P1(x, y1 + size);
        Vector2 T0(0, 50), T1(0, 50);
        DrawHermiteCurve(hdc, P0, T0, P1, T1 , 500 , c );
    }
}

void FillRectangleWithBezierHorizontal(HDC hdc, int x1, int y1, int width, int height , COLORREF c) {
    MessageBox(NULL, "Enter the step for the curve", "Curve Step", MB_OK);
    cout << "Enter the Curve Step : " ;
    int stp = 1 ;
    cin >> stp ;
    if (stp < 1 ){
        MessageBox(NULL, "Step must be bigger than 1 ", "Invalid input", MB_OK);
        return;
    }
    for (int y = y1; y <= y1 + height; y += stp) {
        Vector2 P0(x1, y);
        Vector2 P1(x1 + width / 3, y - 50);
        Vector2 P2(x1 + 2 * width / 3, y + 50);
        Vector2 P3(x1 + width, y);
        DrawBezierCurve(hdc, P0, P1, P2, P3 , 500 , c  );
    }
}