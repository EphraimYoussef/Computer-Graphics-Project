#include "../include/SaveAndLoad.h"
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;
void SaveWindowToFile(HWND hwnd, const char* filename) {
    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right;
    int height = rect.bottom;

    HDC hdcWindow = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdcWindow);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    SelectObject(hdcMem, hBitmap);

    BitBlt(hdcMem, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24; // RGB
    bmi.bmiHeader.biCompression = BI_RGB;

    int rowSize = ((width * 3 + 3) & ~3); // Row size with padding
    int dataSize = rowSize * height;
    BYTE* pixels = new BYTE[dataSize];

    GetDIBits(hdcMem, hBitmap, 0, height, pixels, &bmi, DIB_RGB_COLORS);

    ofstream file(filename, ios::binary);
    file.write((char*)&width, sizeof(int));
    file.write((char*)&height, sizeof(int));
    file.write((char*)pixels, dataSize);
    file.close();

    delete[] pixels;
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcWindow);

    cout << "Window pixels saved to: " << filename << endl;
}

void LoadImageToWindow(HWND hwnd, const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Cannot open file!\n";
        return;
    }

    int width, height;
    file.read((char*)&width, sizeof(int));
    file.read((char*)&height, sizeof(int));

    int rowSize = ((width * 3 + 3) & ~3);
    int dataSize = rowSize * height;
    BYTE* pixels = new BYTE[dataSize];
    file.read((char*)pixels, dataSize);
    file.close();

    HDC hdcWindow = GetDC(hwnd);
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
            hdcWindow,
            0, 0, width, height,     // Destination
            0, 0, width, height,     // Source
            pixels,
            &bmi,
            DIB_RGB_COLORS,
            SRCCOPY
    );

    delete[] pixels;
    ReleaseDC(hwnd, hdcWindow);

    cout << "Image loaded from: " << filename << endl;
}
