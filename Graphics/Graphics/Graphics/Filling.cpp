#include "stdafx.h"
#include "Filling.h"

bool validPoint(int x, int y, int width, int height) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

void fillingDFS(HWND hWnd, HDC hdc, int x, int y) {
	stack<POINT> points;
	points.push(makePOINT(x, y));
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };

	RECT rect;
	int width, height;
	if (GetClientRect(hWnd, &rect)) {
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	while (!points.empty()) {
		POINT cur = points.top(); points.pop();
		if (!validPoint(cur.x, cur.y, width, height)) continue;
		if (GetPixel(hdc, cur.x, cur.y) == color) continue;

		SetPixel(hdc, cur.x, cur.y, color);
		for (int i = 0; i < 4; i++)
			points.push({ cur.x + dx[i], cur.y + dy[i] });
	}
}

void fillingBFS(HWND hWnd, HDC hdc, int x, int y) {
	queue<POINT> points;
	points.push(makePOINT(x, y));
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };

	RECT rect;
	int width, height;
	if (GetClientRect(hWnd, &rect)) {
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	while (!points.empty()) {
		POINT cur = points.front(); points.pop();
		if (!validPoint(cur.x, cur.y, width, height)) continue;
		if (GetPixel(hdc, cur.x, cur.y) == color) continue;

		SetPixel(hdc, cur.x, cur.y, color);
		for (int i = 0; i < 4; i++)
			points.push({ cur.x + dx[i], cur.y + dy[i] });
	}
}
