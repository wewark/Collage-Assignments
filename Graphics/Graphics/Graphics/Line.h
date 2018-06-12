#pragma once

void DirectLine(HDC hdc, int xs, int ys, int xe, int ye);

void DrawDDA(HDC& hdc, int x0, int y0, int x1, int y1);

void DrawMidPointLine(HDC hdc, int xs, int ys, int xe, int ye);

void polygon(HDC hdc, vector<POINT> vertices);
