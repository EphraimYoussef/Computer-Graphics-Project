#include <windows.h>
#include "../include/Constants.h"
#include "../include/MainMenu.h"

using namespace Constants;

HMENU CreateMainMenu() {

    // ? BG_COLOR
    HMENU BGColor = CreatePopupMenu();
    AppendMenu(BGColor, MF_STRING, BG_WHITE, "White");
    AppendMenu(BGColor, MF_STRING, BG_LT_GRAY, "Light Gray");
    AppendMenu(BGColor, MF_STRING, BG_GRAY, "Gray");
    AppendMenu(BGColor, MF_STRING, BG_DK_GRAY, "Dark Gray");
    AppendMenu(BGColor, MF_STRING, BG_BLACK, "Black");

    //!=========================================================================================================

    // ? CURSOR_Change
    HMENU Cursor = CreatePopupMenu();
    AppendMenu(Cursor, MF_STRING, CURSOR_ARROW, "Arrow");
    AppendMenu(Cursor, MF_STRING, CURSOR_CROSS, "Cross");
    AppendMenu(Cursor, MF_STRING, CURSOR_HAND, "Hand");

    //!=========================================================================================================

    // ? SHAPE_COLOR
    HMENU ShapeColor = CreatePopupMenu();
    AppendMenu(ShapeColor, MF_STRING, SHAPE_RED, "Red");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_GREEN, "Green");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_BLUE, "Blue");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_YELLOW, "Yellow");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_MAGENTA, "Magenta");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_CYAN, "Cyan");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_ORANGE, "Orange");
    AppendMenu(ShapeColor, MF_STRING, SHAPE_PURPLE, "Purple");

    //!=========================================================================================================

    // ? LINE
    HMENU lineAlgorithms = CreatePopupMenu();
    AppendMenu(lineAlgorithms, MF_STRING, LINE_DDA, "DDA");
    AppendMenu(lineAlgorithms, MF_STRING, LINE_MID_POINT, "Mid point");
    AppendMenu(lineAlgorithms, MF_STRING, LINE_PARAMETRIC, "Parametric");

    //*=========================================================================================================

    // ? CIRCLE
    HMENU circleAlgorithms = CreatePopupMenu();
    AppendMenu(circleAlgorithms, MF_STRING, CIRCLE_DIRECT, "Direct");
    AppendMenu(circleAlgorithms, MF_STRING, CIRCLE_POLAR, "Polar");
    AppendMenu(circleAlgorithms, MF_STRING, CIRCLE_ITERATIVE_POLAR, "Iterative Polar");
    AppendMenu(circleAlgorithms, MF_STRING, CIRCLE_MID_POINT, "Mid point");
    AppendMenu(circleAlgorithms, MF_STRING, CIRCLE_MODIFIED_MID_POINT, "Modified Mid point");

    //*=========================================================================================================

    // ? ELLIPSE
    HMENU ellipseAlgorithms = CreatePopupMenu();
    AppendMenu(ellipseAlgorithms, MF_STRING, ELLIPSE_DIRECT, "Direct");
    AppendMenu(ellipseAlgorithms, MF_STRING, ELLIPSE_POLAR, "Polar");
    AppendMenu(ellipseAlgorithms, MF_STRING, ELLIPSE_MID_POINT, "Mid point");

    //*=========================================================================================================

    // ? SHAPE_MENU
    HMENU Shape = CreatePopupMenu();
    AppendMenu(Shape, MF_POPUP, (UINT_PTR)lineAlgorithms , "Line");
    AppendMenu(Shape, MF_POPUP, (UINT_PTR)circleAlgorithms, "Circle");
    AppendMenu(Shape, MF_POPUP, (UINT_PTR)ellipseAlgorithms, "Ellipse");
    AppendMenu(Shape, MF_STRING, CARDINAL_SPLINE, "Cardinal Spline Curve");

    //!=========================================================================================================

    // ? FILLING
    HMENU Filling = CreatePopupMenu();
    AppendMenu(Filling, MF_STRING, FILL_CIRCLE_LINES, "Filling Circle with lines");
    AppendMenu(Filling, MF_STRING, FILL_CIRCLE_CIRCLES, "Filling Circle with circles");
    AppendMenu(Filling, MF_STRING, FILL_SQUARE_HERMITE_V, "Filling Square with Hermit [Vertical]");
    AppendMenu(Filling, MF_STRING, FILL_RECT_BEZIER_H, "Filling Rectangle with Bezier [horizontal]");
    AppendMenu(Filling, MF_STRING, FILL_CONVEX, "Convex Filling");
    AppendMenu(Filling, MF_STRING, FILL_NON_CONVEX, "Non Convex Filling");
    AppendMenu(Filling, MF_STRING, FILL_RECURSIVE, "Recursive Flood Fill");
    AppendMenu(Filling, MF_STRING, FILL_NON_RECURSIVE, "Non Recursive Flood Fill");

    //!=========================================================================================================

    // ? CLIPPING_RECTANGLE
    HMENU clippingRect = CreatePopupMenu();
    AppendMenu(clippingRect, MF_STRING, CLIP_RECT_POINT, "Point");
    AppendMenu(clippingRect, MF_STRING, CLIP_RECT_LINE, "Line");
    AppendMenu(clippingRect, MF_STRING, CLIP_RECT_POLYGON, "Polygon");

    //*=========================================================================================================

    // ? CLIPPING_SQUARE
    HMENU clippingSquare = CreatePopupMenu();
    AppendMenu(clippingSquare, MF_STRING, CLIP_SQR_POINT, "Point");
    AppendMenu(clippingSquare, MF_STRING, CLIP_SQR_LINE, "Line");

    //*=========================================================================================================

    // ? CLIPPING
    HMENU clipping = CreatePopupMenu();
    AppendMenu(clipping, MF_POPUP, (UINT_PTR)clippingRect, "Clipping algorithms using Rectangle");
    AppendMenu(clipping, MF_POPUP, (UINT_PTR)clippingSquare, "Clipping algorithms using Square");

    //!=========================================================================================================

    // ? MAIN_MENU
    HMENU mainMenu = CreateMenu();
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)BGColor, "Background Color");
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Cursor, "Cursor");
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)ShapeColor, "Shape Color");
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Shape, "Choose Shape");
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)Filling, "Filling");
    AppendMenu(mainMenu, MF_POPUP, (UINT_PTR)clipping, "Clipping");
    AppendMenu(mainMenu, MF_STRING, CLEAR, "Clear");
    AppendMenu(mainMenu, MF_STRING, SAVE, "Save");
    AppendMenu(mainMenu, MF_STRING, LOAD, "Load");

    return mainMenu;
}