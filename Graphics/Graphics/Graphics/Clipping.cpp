#include "stdafx.h"
#include "Clipping.h"

OutCode GetOutCode(double x, double y,
	int xleft, int xright, int ybottom, int ytop) {
	OutCode result;
	result.All = 0;

	if (x < xleft)
		result.left = 1;
	else if (x > xright)
		result.right = 1;

	if (y > ybottom)
		result.bottom = 1;
	else if (y < ytop)
		result.top = 1;
	return result;
}

PointD Vintersect(double xs, double ys,
	double xe, double ye, int xedge) {
	PointD v;
	v.x = xedge;
	v.y = ((xedge - xs)*(ye - ys) / (double)(xe - xs)) + ys;
	return v;
}

PointD Hintersect(double xs, double ys,
	double xe, double ye, int yedge) {
	PointD v;
	v.y = yedge;
	v.x = ((yedge - ys)*(xe - xs) / (double)(ye - ys)) + xs;
	return v;
}

void LineClipping(HDC hdc, int& xs, int& ys, int& xe, int& ye,
	int xleft, int xright, int ytop, int ybottom) {
	OutCode out1 = GetOutCode(xs, ys, xleft, xright, ybottom, ytop);
	OutCode out2 = GetOutCode(xe, ye, xleft, xright, ybottom, ytop);

	while (((out1.All != 0 || out2.All != 0) && ((out1.All & out2.All) == 0))) {
		if (out1.All) {
			if (out1.left) {
				PointD v = Vintersect(xs, ys, xe, ye, xleft);
				xs = v.x;
				ys = v.y;
			}
			else if (out1.right) {
				PointD v = Vintersect(xs, ys, xe, ye, xright);
				xs = v.x;
				ys = v.y;
			}
			else if (out1.bottom) {
				PointD v = Hintersect(xs, ys, xe, ye, ybottom);
				xs = v.x;
				ys = v.y;
			}
			else if (out1.top) {
				PointD v = Hintersect(xs, ys, xe, ye, ytop);
				xs = v.x;
				ys = v.y;
			}

			out1 = GetOutCode(xs, ys, xleft, xright, ybottom, ytop);
		}
		else if (out2.All) {
			if (out2.left) {
				PointD v = Vintersect(xs, ys, xe, ye, xleft);
				xe = v.x;
				ye = v.y;
			}
			else if (out2.right) {
				PointD v = Vintersect(xs, ys, xe, ye, xright);
				xe = v.x;
				ye = v.y;
			}
			else if (out2.bottom) {
				PointD v = Hintersect(xs, ys, xe, ye, ybottom);
				xe = v.x;
				ye = v.y;
			}
			else if (out2.top) {
				PointD v = Hintersect(xs, ys, xe, ye, ytop);
				xe = v.x;
				ye = v.y;
			}

			out2 = GetOutCode(xe, ye, xleft, xright, ybottom, ytop);
		}
	}
	if (out1.All == 0 && out2.All == 0)
		DrawDDA(hdc, xs, ys, xe, ye);
}

