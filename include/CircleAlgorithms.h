#ifndef PROJECT_CIRCLEALGORITHMS_H
#define PROJECT_CIRCLEALGORITHMS_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void PolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void IterativePolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void MidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void ModifiedMidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

#endif //PROJECT_CIRCLEALGORITHMS_H
