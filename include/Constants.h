#ifndef PROJECT_CONSTANTS_H
#define PROJECT_CONSTANTS_H


namespace Constants {

    const int BG_WHITE = 11;
    const int BG_BLACK = 12;

    const int CURSOR_ARROW = 21;
    const int CURSOR_CROSS = 22;

    const int SHAPE_RED = 31;
    const int SHAPE_GREEN = 32;
    const int SHAPE_BLUE = 33;

    const int LINE_DDA = 411;
    const int LINE_MID_POINT = 412;
    const int LINE_PARAMETRIC = 413;

    const int CIRCLE_DIRECT = 421;
    const int CIRCLE_POLAR = 422;
    const int CIRCLE_ITERATIVE_POLAR = 423;
    const int CIRCLE_MID_POINT = 424;
    const int CIRCLE_MODIFIED_MID_POINT = 425;

    const int ELLIPSE_DIRECT = 431;
    const int ELLIPSE_POLAR = 432;
    const int ELLIPSE_MID_POINT = 433;

    const int CARDINAL_SPLINE = 44;

    const int FILL_CIRCLE_LINES = 51;
    const int FILL_CIRCLE_CIRCLES = 52;
    const int FILL_SQUARE_HERMITE_V = 53;
    const int FILL_RECT_BEZIER_H = 54;
    const int FILL_CONVEX = 55;
    const int FILL_NON_CONVEX = 56;
    const int FILL_RECURSIVE = 57;
    const int FILL_NON_RECURSIVE = 58;

    const int CLIP_RECT_POINT = 611;
    const int CLIP_RECT_LINE = 612;
    const int CLIP_RECT_POLYGON = 613;

    const int CLIP_SQR_POINT = 621;
    const int CLIP_SQR_LINE = 622;

    const int CLEAR = 101;
    const int SAVE = 102;
    const int LOAD = 103;

}



#endif //PROJECT_CONSTANTS_H
