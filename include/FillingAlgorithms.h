#ifndef PROJECT_FILLINGALGORITHMS_H
#define PROJECT_FILLINGALGORITHMS_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;


// ? Filling Algorithms

void ConvexFilling(HDC hdc , vector<POINT>& p , COLORREF c);

void NonConvexFilling(HDC hdc, vector<POINT>& p, COLORREF c);

void RecursiveFloodFill(HDC hdc , int x , int y , COLORREF fillColor , COLORREF bgColor);

void NonRecursiveFloodFill(HDC hdc , int x , int y , COLORREF fillColor , COLORREF bgColor);

void FillQuarterCircleWithLines(HDC hdc, int xc, int yc, int r, COLORREF c);

void FillQuarterCircleWithCircles(HDC hdc, int xc, int yc, int r, COLORREF c);

void FillSquareWithHermiteVertical(HDC hdc, int x1, int y1, int size ,COLORREF c) ;



void FillRectangleWithBezierHorizontal(HDC hdc, int x1, int y1, int width, int height, COLORREF c) ;


#endif //PROJECT_FILLINGALGORITHMS_H
