#ifndef PROJECT_LINEALGORITHMS_H
#define PROJECT_LINEALGORITHMS_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;


// ? Line Algorithms

void DDALine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

void MidPointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

void ParametricLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

#endif //PROJECT_LINEALGORITHMS_H
