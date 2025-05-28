#ifndef PROJECT_FILLINGALGORITHMS_H
#define PROJECT_FILLINGALGORITHMS_H

#include <windows.h>
#include <bits/stdc++.h>

using namespace std;


// ? Filling Algorithms

void ConvexFilling(HDC hdc , vector<POINT>& p , COLORREF c);

void RecursiveFloodFill(HDC hdc , int x , int y , COLORREF fillColor , COLORREF bgColor);

void NonRecursiveFloodFill(HDC hdc , int x , int y , COLORREF fillColor , COLORREF bgColor);

#endif //PROJECT_FILLINGALGORITHMS_H
