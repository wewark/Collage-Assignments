#include "stdafx.h"
#include "Line.h"

void DirectLine(HDC hdc, int xs, int ys, int xe, int ye) {
	int dx = xe - xs;
	int dy = ye - ys;

	double xInc = dx / fabs(dx);
	double yInc = dy / fabs(dx);
	double x = xs;
	double y = ys;
	while (x >= min(xs, xe) && x <= max(xs, xe)) {
		SetPixel(hdc, round(x), round(y), color);
		x += xInc;
		y += yInc;
	}
}

void DrawDDA(HDC& hdc, int x0, int y0, int x1, int y1) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	double xInc = dx / (double)steps;
	double yInc = dy / (double)steps;
	double x = x0;
	double y = y0;
	while (x >= min(x0, x1) && x <= max(x0, x1) &&
		y >= min(y0, y1) && y <= max(y0, y1)) {
		SetPixel(hdc, x, y, color);
		x += xInc;
		y += yInc;
	}
}

void DrawMidPointLine(HDC hdc, int xs, int ys, int xe, int ye) {
	int dx = xe - xs;
	int dy = ye - ys;
	if (abs(dy) <= abs(dx)) { // slope less than 1
		if (xe < xs) {
			swap(xe, xs);
			swap(ye, ys);
			dx = -dx;
			dy = -dy;
		}

		int d = dx - abs(2 * dy);
		int c1 = 2 * dx - abs(2 * dy);
		int c2 = -2 * abs(dy);
		int x = xs, y = ys;
		while (x <= xe) {
			SetPixel(hdc, x, y, RGB(0, 0, 0));
			if (d <= 0) {
				d += c1;
				//to check if y decrease or increase
				y += (dy > 0) ? 1 : -1;
			}
			else  d += c2;
			x++;
		}
	}
	else {
		if (dy < 0) {
			swap(ye, ys);
			swap(xe, xs);
			dy = -dy;
			dx = -dx;
		}

		int d = dy - abs(2 * dx);
		int c1 = 2 * dy - abs(2 * dx);
		int c2 = -2 * abs(dx);
		int y = ys;
		int x = xs;
		while (y <= ye) {
			SetPixel(hdc, x, y, RGB(0, 0, 0));
			if (d <= 0) {
				d += c1;
				x += (dx > 0) ? 1 : -1;
			}
			else  d += c2;
			y++;
		}
	}
}

void polygon(HDC hdc, vector<POINT> vertices) {
	POINT v1 = vertices.back();
	for (int i = 0; i < vertices.size(); i++) {
		POINT v2 = vertices[i];
		DrawDDA(hdc, v1.x, v1.y, v2.x, v2.y);
		v1 = v2;
	}
}
