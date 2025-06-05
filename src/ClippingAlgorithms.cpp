#include <Windows.h>
#include <bits/stdc++.h>
#include "../include/ClippingAlgorithms.h"

using namespace std;

// Define region codes for Cohen-Sutherland algorithm
#define INSIDE 0 // 0000
#define LEFT 1   // 0001
#define RIGHT 2  // 0010
#define BOTTOM 4 // 0100
#define TOP 8    // 1000

// Rectangle helpers
int ClippingAlgorithms::computeCode(const Point &p, const struct Rectangle &rect) {
    int code = INSIDE;
    if (p.x < rect.topLeft.x)      // to the left of rectangle
        code |= LEFT;
    else if (p.x > rect.bottomRight.x) // to the right of rectangle
        code |= RIGHT;
    if (p.y < rect.topLeft.y)      // below the rectangle
        code |= BOTTOM;
    else if (p.y > rect.bottomRight.y) // above the rectangle
        code |= TOP;
    return code;
}

// Function to clip a point against a rectangle
bool ClippingAlgorithms::clipPointRectangle(Point &p, const struct Rectangle &rect) {
    return (p.x >= rect.topLeft.x && p.x <= rect.bottomRight.x &&
            p.y >= rect.topLeft.y && p.y <= rect.bottomRight.y);
}

// Function to clip a line using Cohen-Sutherland algorithm
bool ClippingAlgorithms::clipLineRectangle(Point &p1, Point &p2, const struct Rectangle &rect) {
    int code1 = computeCode(p1, rect);
    int code2 = computeCode(p2, rect);
    bool accept = false;

    while (true) {
        if (!(code1 | code2)) { // Both points inside
            accept = true;
            break;
        } else if (code1 & code2) { // Both points outside
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            Point p;
            if (codeOut & TOP) {
                p.x = p1.x + (p2.x - p1.x) * (rect.bottomRight.y - p1.y) / (p2.y - p1.y);
                p.y = rect.bottomRight.y;
            } else if (codeOut & BOTTOM) {
                p.x = p1.x + (p2.x - p1.x) * (rect.topLeft.y - p1.y) / (p2.y - p1.y);
                p.y = rect.topLeft.y;
            } else if (codeOut & RIGHT) {
                p.y = p1.y + (p2.y - p1.y) * (rect.bottomRight.x - p1.x) / (p2.x - p1.x);
                p.x = rect.bottomRight.x;
            } else if (codeOut & LEFT) {
                p.y = p1.y + (p2.y - p1.y) * (rect.topLeft.x - p1.x) / (p2.x - p1.x);
                p.x = rect.topLeft.x;
            }

            if (codeOut == code1) {
                p1 = p; // Move outside point to intersection point
                code1 = computeCode(p1, rect);
            } else {
                p2 = p; // Move outside point to intersection point
                code2 = computeCode(p2, rect);
            }
        }
    }

    return accept; // Return whether the line is accepted
}

// Sutherland-Hodgman polygon clipping for rectangle
Point ClippingAlgorithms::intersect(const Point &A, const Point &B, int edge, const struct Rectangle &rect) {
    Point res = {0, 0};
    float x1 = A.x, y1 = A.y, x2 = B.x, y2 = B.y;
    float m = (x2 != x1) ? (y2 - y1) / (x2 - x1) : 1e10f;
    switch (edge) {
        case LEFT:
            res.x = rect.topLeft.x;
            res.y = y1 + m * (rect.topLeft.x - x1);
            break;
        case RIGHT:
            res.x = rect.bottomRight.x;
            res.y = y1 + m * (rect.bottomRight.x - x1);
            break;
        case BOTTOM:
            res.y = rect.topLeft.y;
            res.x = x1 + (rect.topLeft.y - y1) / m;
            break;
        case TOP:
            res.y = rect.bottomRight.y;
            res.x = x1 + (rect.bottomRight.y - y1) / m;
            break;
    }
    return res;
}

bool ClippingAlgorithms::inside(const Point &p, int edge, const struct Rectangle &rect) {
    switch (edge) {
        case LEFT:
            return p.x >= rect.topLeft.x;
        case RIGHT:
            return p.x <= rect.bottomRight.x;
        case BOTTOM:
            return p.y >= rect.topLeft.y;
        case TOP:
            return p.y <= rect.bottomRight.y;
    }
    return false;
}

void ClippingAlgorithms::clipPolygonRectangle(vector<Point> &polygon, const struct Rectangle &rect) {
    vector<int> edges = {LEFT, RIGHT, BOTTOM, TOP};
    vector<Point> input = polygon;
    for (int edge: edges) {
        vector<Point> output;
        if (input.empty()) break;
        Point S = input.back();
        for (const Point &E: input) {
            if (inside(E, edge, rect)) {
                if (!inside(S, edge, rect)) {
                    output.push_back(intersect(S, E, edge, rect));
                }
                output.push_back(E);
            } else if (inside(S, edge, rect)) {
                output.push_back(intersect(S, E, edge, rect));
            }
            S = E;
        }
        input = output;
    }
    polygon = input;
}

struct Rectangle ClippingAlgorithms::squareToRect(const Square &square) {
    struct Rectangle rect;
    rect.topLeft = square.topLeft;
    rect.bottomRight = Point{square.topLeft.x + square.side, square.topLeft.y + square.side};
    return rect;
}

bool ClippingAlgorithms::clipPointSquare(Point &p, const Square &square) {
    struct Rectangle rect = squareToRect(square);
    return clipPointRectangle(p, rect);
}

bool ClippingAlgorithms::clipLineSquare(Point &p1, Point &p2, const Square &square) {
    struct Rectangle rect = squareToRect(square);
    return clipLineRectangle(p1, p2, rect);
}

bool ClippingAlgorithms::isPointInsideCircle(const Point &p, const Circle &circle) {
    float dx = p.x - circle.center.x;
    float dy = p.y - circle.center.y;
    return (dx * dx + dy * dy) <= (circle.radius * circle.radius);
}

bool ClippingAlgorithms::clipLineCircle(Point &p1, Point &p2, const Circle &circle) {
    if(p1.y<p2.y) {
        swap(p1, p2);
    }
    else if (p1.y == p2.y) {
        return false;
    }
    float x1 = p1.x - circle.center.x;
    float y1 = p1.y - circle.center.y;
    float x2 = p2.x - circle.center.x;
    float y2 = p2.y - circle.center.y;
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dr2 = dx * dx + dy * dy;
    float D = x1 * y2 - x2 * y1;
    float r2 = circle.radius * circle.radius;
    float discriminant = r2 * dr2 - D * D;
    if (discriminant < 0) return false; // No intersection
    float sqrtDisc = sqrt(discriminant);
    float sign_dy = (dy < 0) ? -1 : 1;
    float abs_dy = fabs(dy);
    // Find intersection points (may be outside segment)
    float ix1 = (D * dy + sign_dy * dx * sqrtDisc) / dr2;
    float iy1 = (-D * dx + abs_dy * sqrtDisc) / dr2;
    float ix2 = (D * dy - sign_dy * dx * sqrtDisc) / dr2;
    float iy2 = (-D * dx - abs_dy * sqrtDisc) / dr2;
    // Convert back to original coordinates
    Point inter1 = {ix1 + circle.center.x, iy1 + circle.center.y};
    Point inter2 = {ix2 + circle.center.x, iy2 + circle.center.y};
    // Clamp to segment
    auto onSegment = [](const Point &a, const Point &b, const Point &p) {
        return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
               min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
    };
    bool found = false;
    if (isPointInsideCircle(p1, circle) && isPointInsideCircle(p2, circle)) {
        found = true;
    } else {
        if (onSegment(p1, p2, inter1)) {
            p1 = inter1;
            found = true;
        }
        if (onSegment(p1, p2, inter2)) {
            p2 = inter2;
            found = true;
        }
    }
    return found;
}