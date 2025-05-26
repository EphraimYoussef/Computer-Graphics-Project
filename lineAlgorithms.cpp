#include <Windows.h>

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

