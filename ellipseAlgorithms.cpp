#include <Windows.h>
#include <bits/stdc++.h>

using namespace std;

void draw4Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
}

void DirectEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    for (int x = 0; x <= a; x++) {
        int y = (int)round(b * sqrt(1.0 - (x * x) / (double)(a * a)));
        draw4Points(hdc, xc, yc, x, y, c);
    }

    for (int y = 0; y <= b; y++) {
        int x = (int)round(a * sqrt(1.0 - (y * y) / (double)(b * b)));
        draw4Points(hdc, xc, yc, x, y, c);
    }
}

void PolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c){
    double step = 1.0 / max(a , b) , limit = 0.5 * M_PI;
    for (double theta = 0; theta <= limit ; theta += step) {
        int x = (int)round(a * cos(theta));
        int y = (int)round(b * sin(theta));
        draw4Points(hdc, xc, yc, x, y, c);
    }
}

void MidPointEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c) {
    int x = 0;
    int y = b;
    double a2 = a * a;
    double b2 = b * b;
    double d = b2 - a2 * b + 0.25 * a2;
    int dx = 2 * (int)b2 * x;
    int dy = 2 * (int)a2 * y;
    draw4Points(hdc, xc, yc, x, y, c);

    while (dx < dy) {
        if (d < 0) {
            x++;
            dx += 2 * b2;
            d += dx + b2;
        } else {
            x++;
            y--;
            dx += 2 * b2;
            dy -= 2 * a2;
            d += dx - dy + b2;
        }
        draw4Points(hdc, xc, yc, x, y, c);
    }

    d = b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 1) * (y - 1) - a2 * b2;
    while (y >= 0) {
        if (d > 0) {
            y--;
            dy -= 2 * a2;
            d += a2 - dy;
        } else {
            y--;
            x++;
            dx += 2 * b2;
            dy -= 2 * a2;
            d += dx - dy + a2;
        }
        draw4Points(hdc, xc, yc, x, y, c);
    }
}
