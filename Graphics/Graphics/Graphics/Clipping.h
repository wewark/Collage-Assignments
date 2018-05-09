#pragma once
union OutCode {
	unsigned All : 4;
	struct { unsigned left : 1, right : 1, bottom : 1, top : 1; };
};

OutCode GetOutCode(double x, double y,
	int xleft, int xright, int ybottom, int ytop);

struct PointD {
	double x, y;
};

PointD Vintersect(double xs, double ys,
	double xe, double ye, int xedge);

PointD Hintersect(double xs, double ys,
	double xe, double ye, int yedge);

void LineClipping(HDC hdc, int& xs, int& ys, int& xe, int& ye,
	int xleft, int xright, int ytop, int ybottom);

