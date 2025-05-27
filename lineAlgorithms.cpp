#include <Windows.h>
#include <bits/stdc++.h>

using namespace std;

void DDALine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x2 - x1, dy = y2 - y1;
    SetPixel(hdc, x1, y1, c);
    if(abs(dx) > abs(dy)) {
        int x = x1;
        double y = y1;
        double m = ((double)dy / (double)dx);
        while(x != x2) {
            x += (dx > 0) ? 1 : -1;
            y += (m * (dx > 0 ? 1 : -1));
            SetPixel(hdc, x, (int)round(y), c);
        }
    }
    else {
        double x = x1;
        int y = y1;
        double m = ((double)dx / (double)dy);
        while(y != y2) {
            y += (dy > 0) ? 1 : -1;
            x += (m * (dy > 0 ? 1 : -1));
            SetPixel(hdc, (int)round(x), y, c);
        }
    }
}

void MidPointLine(HDC hdc, int x1, int y1, int x2, int y2 , COLORREF c) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int xInc = (x2 >= x1) ? 1 : -1, yInc = (y2 >= y1) ? 1 : -1;
    int x = x1, y = y1;

    SetPixel(hdc , x , y , c);

    if (dx > dy) {
        int d = 2 * dy - dx;
        int d1 = 2 * (dy - dx);
        int d2 = 2 * dy;
        while (x != x2) {
            if (d >= 0) {
                d += d1;
                y += yInc;
            }
            else {
                d += d2;
            }
            x += xInc;
            SetPixel(hdc, x, y, c);
        }
    }
    else {
        int d = 2 * dx - dy;
        int d1 = 2 * (dx - dy);
        int d2 = 2 * dx;
        while (y != y2) {
            if (d >= 0) {
                d += d1;
                x += xInc;
            }
            else {
                d += d2;
            }
            y += yInc;
            SetPixel(hdc, x, y, c);
        }
    }
}

void ParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x2 - x1, dy = y2 - y1;
    double x = x1 , y = y1;
    SetPixel(hdc , x1 , y1 , c);
    double step = 1.0 / max(abs(dx) ,abs(dy));
    for( double t = 0 ; t <= 1 ; t += step ) {
        x = dx * t + x1;
        y = dy * t + y1;
        SetPixel(hdc , (int)round(x) , (int)round(y) , c);
    }
}