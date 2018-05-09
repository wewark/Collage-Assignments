#include "stdafx.h"
#include "Circle.h"

#define _USE_MATH_DEFINES
#include <math.h>

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

void cartesianCircle(HDC hdc, int xc, int yc, int xr, int yr) {
	int R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	int R2 = R * R;

	int x = 0, y = R;
	while (x < y) {
		Draw8Points(hdc, xc, yc, x, y);
		x++;
		y = round(sqrt(R2 - x * x));
	}
}

void PolarCircle(HDC hdc, int xc, int yc, int xr, int yr) {
	double R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	double dtheta = 1.0 / R;

	double x, y;
	for (double theta = 0; theta < M_PI_4; theta += dtheta) {
		x = R * cos(theta);
		y = R * sin(theta);
		Draw8Points(hdc, xc, yc, x, y);
	}
}

void IterativePolarCircle(HDC hdc, int xc, int yc, int xr, int yr) {
	double R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	double dtheta = 1.0 / R;

	double ct = cos(dtheta);
	double st = sin(dtheta);

	double x = R, y = 0;
	double x1;
	while (x >= y) {
		Draw8Points(hdc, xc, yc, round(x), round(y));

		x1 = (x * ct) - (y * st);
		y = (x * st) + (y * ct);

		x = x1;
	}
}

void CircleMidPoint(HDC hdc, int xc, int yc, int xr, int yr) {
	double R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	int x = 0;
	int y = R;

	int d = 1 - R;
	int d1 = 3;
	int d2 = 5 - 2 * R;

	while (x <= y) {
		Draw8Points(hdc, xc, yc, x, y);

		if (d < 0) {
			d += d1;
			d2 += 2;
		}
		else {
			d += d2;
			y--;
			d2 += 4;
		}

		d1 += 2;
		x++;
	}
}
