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

struct Vertex
{
	double x, y;
	Vertex(int x1 = 0, int y1 = 0)
	{
		x = x1;
		y = y1;
	}
};
typedef vector<Vertex> VertexList;
typedef bool(*IsInFunc)(Vertex& v, int edge);
typedef Vertex(*IntersectFunc)(Vertex& v1, Vertex& v2, int edge);

VertexList ClipWithEdge(VertexList p, int edge, IsInFunc In, IntersectFunc Intersect);

bool InLeft(Vertex& v, int edge);

bool InRight(Vertex& v, int edge);

bool InTop(Vertex& v, int edge);

bool InBottom(Vertex& v, int edge);

Vertex VIntersect(Vertex& v1, Vertex& v2, int xedge);

Vertex HIntersect(Vertex& v1, Vertex& v2, int yedge);

void PolygonClip(HDC hdc, vector<POINT>& p, int xleft, int ytop, int xright, int ybottom);

