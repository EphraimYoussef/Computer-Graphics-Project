#ifndef PROJECT_CURVESALGORITHMS_H
#define PROJECT_CURVESALGORITHMS_H
//Bezier
#include <Windows.h>
#include <cmath>


struct Vector2
{
    double x,y;
    Vector2(double a=0,double b=0)
    {
        x=a; y=b;
    }
};
class Vector4
{
    double v[4];
public:
    Vector4(double a=0,double b=0,double c=0,double d=0)
    {
        v[0]=a; v[1]=b; v[2]=c; v[3]=d;
    }
    Vector4(double a[])
    {
        memcpy(v,a,4*sizeof(double));
    }
    double& operator[](int i)
    {
        return v[i];
    }
};
class Matrix4
{
    Vector4 M[4];
public:
    Matrix4(double A[])
    {
        memcpy(M,A,16*sizeof(double));
    }
    Vector4& operator[](int i)
    {
        return M[i];
    }
};

Vector4 operator*(Matrix4 M,Vector4& b); // right multiplication of M by b

double DotProduct(Vector4& a,Vector4& b) ;


void DrawHermiteCurve (HDC hdc,Vector2& P0,Vector2& T0,Vector2& P1,Vector2& T1 ,int
numpoints ,COLORREF c);

void DrawBezierCurve(HDC hdc,Vector2& P0,Vector2& P1,Vector2& P2,Vector2& P3,int
numpoints ,COLORREF c);


#endif //PROJECT_CURVESALGORITHMS_H
