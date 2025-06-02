#ifndef PROJECT_SAVEANDLOAD_H
#define PROJECT_SAVEANDLOAD_H
#include <windows.h>

void SaveWindowToFile(HWND hwnd, const char* filename);
void LoadImageToWindow(HWND hwnd, const char* filename);
#endif //PROJECT_SAVEANDLOAD_H

