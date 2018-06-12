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

VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect)
{
	VertexList OutList;
	if (p.empty()) return OutList;
	Vertex v1 = p[p.size() - 1];
	bool v1_in = In(v1, edge);
	for (int i = 0; i < (int)p.size(); i++)
	{
		Vertex v2 = p[i];
		bool v2_in = In(v2, edge);
		if (!v1_in && v2_in)
		{
			OutList.push_back(Intersect(v1, v2, edge));
			OutList.push_back(v2);
		}
		else if (v1_in && v2_in) OutList.push_back(v2);
		else if (v1_in) OutList.push_back(Intersect(v1, v2, edge));
		v1 = v2;
		v1_in = v2_in;
	}
	return OutList;
}
bool InLeft(Vertex& v, int edge)
{
	return v.x >= edge;
}
bool InRight(Vertex& v, int edge)
{
	return v.x <= edge;
}
bool InTop(Vertex& v, int edge)
{
	return v.y >= edge;
}
bool InBottom(Vertex& v, int edge)
{
	return v.y <= edge;
}

Vertex VIntersect(Vertex& v1, Vertex& v2, int xedge)
{
	Vertex res;
	res.x = xedge;
	res.y = v1.y + (xedge - v1.x)*(v2.y - v1.y) / (v2.x - v1.x);
	return res;
}

Vertex HIntersect(Vertex& v1, Vertex& v2, int yedge)
{
	Vertex res;
	res.y = yedge;
	res.x = v1.x + (yedge - v1.y)*(v2.x - v1.x) / (v2.y - v1.y);
	return res;
}

void PolygonClip(HDC hdc, vector<POINT>& p, int xleft, int ytop, int xright, int ybottom)
{
	VertexList vlist;
	for (int i = 0; i < p.size(); i++)
		vlist.push_back(Vertex(p[i].x, p[i].y));
	vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
	vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
	vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
	vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);

	p.clear();
	if (vlist.empty()) return;
	Vertex v1 = vlist[vlist.size() - 1];
	
	for (int i = 0; i < (int)vlist.size(); i++)
	{
		p.push_back(POINT{ (int)vlist[i].x, (int)vlist[i].y });
		Vertex v2 = vlist[i];
		DrawDDA(hdc, round(v1.x), round(v1.y), round(v2.x), round(v2.y));
		v1 = v2;
	}
}

