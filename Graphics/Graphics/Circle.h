#pragma once

void Draw8Points(HDC& hdc, int xc, int yc, int a, int b);

void cartesianCircle(HDC hdc, int xc, int yc, int xr, int yr);

void PolarCircle(HDC hdc, int xc, int yc, int xr, int yr);

void IterativePolarCircle(HDC hdc, int xc, int yc, int xr, int yr);

void CircleMidPoint(HDC hdc, int xc, int yc, int xr, int yr);
