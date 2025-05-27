#ifndef PROJECT_GRAPHICS_ALGORITHMS_H
#define PROJECT_GRAPHICS_ALGORITHMS_H

#include <windows.h>


// ? Line Algorithms

void DDALine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

void MidPointLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c);

//!=========================================================================================================

// ? Circle Algorithms

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void PolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void IterativePolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void MidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

void ModifiedMidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c);

#endif //PROJECT_GRAPHICS_ALGORITHMS_H
