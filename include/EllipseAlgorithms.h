#ifndef PROJECT_ELLIPSEALGORITHMS_H
#define PROJECT_ELLIPSEALGORITHMS_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;


// ? Ellipse Algorithms

void DirectEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

void PolarEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

void MidPointEllipse(HDC hdc, int xc, int yc, int a, int b, COLORREF c);

#endif //PROJECT_ELLIPSEALGORITHMS_H
