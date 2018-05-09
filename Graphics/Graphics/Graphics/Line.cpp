#include "stdafx.h"
#include "Line.h"

void DrawDDA(HDC& hdc, int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	double xInc = dx / (double)steps;
	double yInc = dy / (double)steps;
	double x = x0;
	double y = y0;
	while (x >= min(x0, x1) && x <= max(x0, x1)) {
		SetPixel(hdc, x, y, color);
		x += xInc;
		y += yInc;
	}
}

void midPoint(HDC& hdc, int X1, int Y1, int X2, int Y2) {
	int dx = X2 - X1;
	int dy = Y2 - Y1;

	int d = dy - (dx / 2);
	int x = X1, y = Y1;

	SetPixel(hdc, x, y, RGB(0, 0, 0));

	while (x < X2) {
		x++;

		if (d < 0) // above line, choose E
			d += dy;
		else { // below line, choose NE
			d += (dy - dx);
			y++;
		}

		SetPixel(hdc, x, y, RGB(0, 0, 0));
	}
}
