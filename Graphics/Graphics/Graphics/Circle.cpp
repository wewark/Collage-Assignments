#include "stdafx.h"
#include "Circle.h"

void Draw8Points(HDC& hdc, int xc, int yc, int a, int b) {
	SetPixel(hdc, xc + a, yc + b, color);
	SetPixel(hdc, xc - a, yc + b, color);
	SetPixel(hdc, xc - a, yc - b, color);
	SetPixel(hdc, xc + a, yc - b, color);
	SetPixel(hdc, xc + b, yc + a, color);
	SetPixel(hdc, xc - b, yc + a, color);
	SetPixel(hdc, xc - b, yc - a, color);
	SetPixel(hdc, xc + b, yc - a, color);
}

void DrawCircle(HDC hdc, int xc, int yc, int xr, int yr) {
	int R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	int R2 = R * R;
	int x = 0, y = R;
	Draw8Points(hdc, xc, yc, x, y);
	while (x < y) {
		x++;
		y = round(sqrt((double)(R2 - x * x)));
		Draw8Points(hdc, xc, yc, x, y);
	}
}
