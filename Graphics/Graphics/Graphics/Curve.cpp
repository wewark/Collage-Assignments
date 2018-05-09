#include "stdafx.h"
#include "Curve.h"

void Hermite(HDC hdc, int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4) {
	int a1, b1, c1, d1;
	a1 = 2 * x1 + x2 - 2 * x3 + x4;
	b1 = -3 * x1 - 2 * x2 + 3 * x3 - x4;
	c1 = x2;
	d1 = x1;

	int a2, b2, c2, d2;
	a2 = 2 * y1 + y2 - 2 * y3 + y4;
	b2 = -3 * y1 - 2 * y2 + 3 * y3 - y4;
	c2 = y2;
	d2 = y1;

	double x, y;
	for (double t = 0; t <= 1; t += 0.0001) {
		x = a1 * (t*t*t) + b1 * (t*t) + c1 * (t) + d1;
		y = a2 * (t*t*t) + b2 * (t*t) + c2 * (t) + d2;
		SetPixel(hdc, round(x), round(y), color);
	}
}

void Bezier(HDC hdc, int x1, int y1, int x2, int y2,
	int x3, int y3, int x4, int y4) {
	double x, y;
	for (double t = 0; t <= 1; t += 0.0001) {
		x = ((1 - t)*(1 - t)*(1 - t)*x1)
			+ (3 * (1 - t)*(1 - t)*t*x2)
			+ (3 * (1 - t)*t*t*x3) + (t*t*t*x4);
		y = ((1 - t)*(1 - t)*(1 - t)*y1)
			+ (3 * (1 - t)*(1 - t)*t*y2)
			+ (3 * (1 - t)*t*t*y3) + (t*t*t*y4);
		SetPixel(hdc, round(x), round(y), color);
	}
}
