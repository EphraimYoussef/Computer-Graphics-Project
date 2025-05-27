# 2D Drawing Program in C++

This is a 2D drawing application built in **C++** using the **Win32 API (`Windows.h`)**. It supports an interactive GUI with menus, mouse-only input, and classic computer graphics algorithms for drawing and filling shapes.

## Features

### GUI & Window Features
- Custom mouse pointer
- White background
- Mouse-only interaction (no keyboard required)
- Integration with console output for status/debugging

### Drawing Capabilities
- **Lines**:
  - DDA Algorithm
  - Midpoint Algorithm
  - Parametric Equation
- **Circles**:
  - Direct Method
  - Polar Method
  - Iterative Polar
  - Midpoint Circle
  - Modified Midpoint Circle
- **Ellipses**:
  - Direct Method
  - Polar Method
  - Midpoint Algorithm
- **Curves**:
  - Hermite Curve (used to fill squares vertically)
  - Bezier Curve (used to fill rectangles horizontally)
  - Cardinal Spline Curve

### Filling Algorithms
- Circle filling (with lines or circles) based on user-defined quarter
- Convex and Non-Convex polygon filling
- Flood Fill (Recursive and Non-Recursive)

### Clipping Algorithms
- **Rectangle clipping**: Points, Lines, Polygons
- **Square clipping**: Points, Lines

### File Operations
- Save current screen data to a file
- Load screen data from a file

### Screen Management
- Clear all shapes from the screen

## How to Use

1. Launch the application.
2. Use the mouse to:
   - Select shapes and colors from the dropdown menus.
   - Draw directly on the window canvas.
   - Save/load drawings using the menu.

