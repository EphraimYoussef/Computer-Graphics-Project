#ifndef PROJECT_CLIPPINGALGORITHMS_H
#define PROJECT_CLIPPINGALGORITHMS_H

#include <vector>
using namespace std;

struct Point {
    float x, y;
};

struct Rectangle {
    Point topLeft;
    Point bottomRight;
};

struct Square {
    Point topLeft;
    float side;
};

struct Circle {
    Point center;
    float radius;
};

class ClippingAlgorithms {
public:
    // Rectangle clipping
    static bool clipPointRectangle(Point& p, const struct Rectangle& rect);
    static bool clipLineRectangle(Point& p1, Point& p2, const struct Rectangle& rect);
    static void clipPolygonRectangle(vector<Point>& polygon, const struct Rectangle& rect);

    // Square clipping
    static bool clipPointSquare(Point& p, const Square& square);
    static bool clipLineSquare(Point& p1, Point& p2, const Square& square);

    // Circle clipping
    static bool isPointInsideCircle(const Point &p, const Circle &circle);
    static bool clipLineCircle(Point& p1, Point& p2, const Circle& circle);

private:
    static int computeCode(const Point &p, const struct Rectangle &rect);
    static Point intersect(const Point &A, const Point &B, int edge, const struct Rectangle &rect);
    static bool inside(const Point &p, int edge, const struct Rectangle &rect);
    static struct Rectangle squareToRect(const Square &square);
};

#endif //PROJECT_CLIPPINGALGORITHMS_H
