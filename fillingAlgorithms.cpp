#include <windows.h>
#include <math.h>
#include <stack>
#include "GraphicsAlgorithms.h"
using namespace std;
struct Entry{
    double xLeft , xRight;
};
typedef Entry edgeTable[1080];
struct Point{
    int x , y  ;
};

void init (edgeTable t)
{
    for (int i = 0; i <1080; ++i) {
        t[i].xLeft = INT_MAX;
        t[i].xRight = INT_MIN;
    }
}

void Edge2Table (Point p1 , Point p2 , edgeTable t)
{
    if(p1.y == p2.y)
        return;
    if(p1.y > p2.y)
        swap(p1, p2);

    int y =p1.y;
    double x = p1.x;
    double mInv =(double) (p2.x - p1.x) / (p2.y - p1.y);
    while(y < p2.y)
    {
        if(x < t[y].xLeft)
            t[y].xLeft = ceil(x);
        if(x > t[y].xRight)
            t[y].xRight = floor(x);
        y++;
        x+=mInv;
    }
}

void Polygon2Table(Point p[], int n ,edgeTable t)
{
    Point p1 = p[n-1];

    for (int i = 0; i < n; ++i) {
        Point p2 = p[i];
        Edge2Table(p1,p2,t);
        p1 = p[i];
    }
}

void Table2Screen(HDC hdc , edgeTable t , COLORREF c)
{
    for (int y = 0; y < 1080; ++y) {
        if(t[y].xLeft < t[y].xRight)
            ParametricLine(hdc ,(int)(t[y].xLeft) ,y ,(int)(t[y].xRight) ,y ,c);
    }
}

void ConvexFill(HDC hdc , Point p[] , int n , COLORREF c)
{
    edgeTable  t;
    init(t);
    Polygon2Table(p , n ,t);
    Table2Screen(hdc , t ,c);
}
