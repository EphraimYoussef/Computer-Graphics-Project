#include <windows.h>
#include <bits/stdc++.h>
#include "../include/CircleAlgorithms.h"

using namespace std;

void draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, xc + x, yc + y, c);
    SetPixel(hdc, xc - x, yc + y, c);
    SetPixel(hdc, xc + x, yc - y, c);
    SetPixel(hdc, xc - x, yc - y, c);
    SetPixel(hdc, xc + y, yc + x, c);
    SetPixel(hdc, xc - y, yc + x, c);
    SetPixel(hdc, xc + y, yc - x, c);
    SetPixel(hdc, xc - y, yc - x, c);
}

void DirectCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = 0 , y = r;
    draw8Points(hdc , xc , yc , x , y , c);
    while(x<r){
        x++;
        y = (int)round(sqrt(r*r - x*x));
        draw8Points(hdc , xc , yc , x , y , c);
    }
}

void PolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = r , y = 0;
    draw8Points(hdc , xc , yc , x , y , c);
    double theta = 0 , dTheta = 1.0 / r;
    while(y < x){
        theta += dTheta;
        x = (int)round( r * cos(theta) );
        y = (int)round( r * sin(theta) );
        draw8Points(hdc , xc , yc , x , y , c);
    }
}

void IterativePolarCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {
    double x = r , y = 0;
    draw8Points(hdc , xc , yc , r , 0 , c);
    double dTheta = 1.0 / r;
    double cosDTheta = cos(dTheta) , sinDTheta = sin(dTheta);
    while(y < x){
        double xTemp = x * cosDTheta - y * sinDTheta;
        y = x * sinDTheta + y * cosDTheta;
        x = xTemp;
        draw8Points(hdc , xc , yc , (int)round(x) , (int)round(y) , c);
    }
}

void MidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = 0 , y = r;
    draw8Points(hdc , xc , yc , x , y , c);
    while(x < y){
        double d = pow(x+1 , 2) + pow(y-0.5 , 2) - pow(r , 2);
        if(d < 0){
            x++;
        }
        else{
            x++;
            y--;
        }
        draw8Points(hdc , xc , yc , x , y , c);
    }
}

void ModifiedMidPointCircle(HDC hdc, int xc, int yc, int r, COLORREF c) {
    int x = 0 , y = r;
    int d = 1 - r, d1 = 3 , d2 = 5 - 2 * r;
    draw8Points(hdc , xc , yc , x , y , c);
    while(x < y){
        if(d < 0){
            d += d1;
            d1 += 2;
            d2 += 2;
            x++;
        }
        else{
            d += d2;
            d1 += 2;
            d2 += 4;
            x++;
            y--;
        }
        draw8Points(hdc , xc , yc , x , y , c);
    }
}