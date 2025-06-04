#include "../include/SaveAndLoad.h"
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

void SaveWindow(HWND hwnd) {
    char filename[MAX_PATH] = "";
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bitmap Files (*.bmp)\0*.bmp\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "bmp";

    if (!GetSaveFileName(&ofn)) {
        return;
    }

    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right;
    int height = rect.bottom;

    HDC hdcWindow = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdcWindow);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    SelectObject(hdcMem, hBitmap);
    BitBlt(hdcMem, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    int rowSize = ((width * 3 + 3) & ~3);
    int dataSize = rowSize * height;
    BYTE* pixels = new BYTE[dataSize];
    GetDIBits(hdcMem, hBitmap, 0, height, pixels, &bmi, DIB_RGB_COLORS);

    // ? Save compressed .bmp version ( for loading )
    ofstream file(filename, ios::binary);
    file.write((char*)&width, sizeof(int));
    file.write((char*)&height, sizeof(int));
    file.write((char*)pixels, dataSize);
    file.close();

    // ? Save uncompressed .bmp version ( for saving as image )
    string photoName = string(filename) + "_photo.bmp";
    BITMAPFILEHEADER bfh = {};
    bfh.bfType = 0x4D42;
    bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    ofstream bmpFile(photoName, ios::binary);
    bmpFile.write((char*)&bfh, sizeof(bfh));
    bmpFile.write((char*)&bmi.bmiHeader, sizeof(BITMAPINFOHEADER));
    bmpFile.write((char*)pixels, dataSize);
    bmpFile.close();

    delete[] pixels;
    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcWindow);

    MessageBox(hwnd, "Window saved successfully.", "Saved", MB_OK);
}


void LoadWindow(HWND hwnd) {
    char filename[MAX_PATH] = "";
    OPENFILENAME ofn = {};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Bitmap Files (*.bmp)\0*.bmp\0All Files\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "bmp";

    if (!GetOpenFileName(&ofn)) {
        return;
    }

    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        MessageBox(hwnd, "Failed to open file.", "Error", MB_OK);
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
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    StretchDIBits(
            hdcWindow,
            0, 0, width, height,
            0, 0, width, height,
            pixels,
            &bmi,
            DIB_RGB_COLORS,
            SRCCOPY
    );

    delete[] pixels;
    ReleaseDC(hwnd, hdcWindow);

    MessageBox(hwnd, "Window loaded successfully.", "Loaded", MB_OK);
}
