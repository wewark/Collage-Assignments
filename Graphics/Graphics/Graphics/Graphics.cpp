// WindowsProject1.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "Graphics.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GRAPHICS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHICS));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_GRAPHICS));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GRAPHICS);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void Draw8Points(HDC& hdc, int xc, int yc, int a, int b, COLORREF color = RGB(0, 0, 0)) {
	SetPixel(hdc, xc + a, yc + b, color);
	SetPixel(hdc, xc - a, yc + b, color);
	SetPixel(hdc, xc - a, yc - b, color);
	SetPixel(hdc, xc + a, yc - b, color);
	SetPixel(hdc, xc + b, yc + a, color);
	SetPixel(hdc, xc - b, yc + a, color);
	SetPixel(hdc, xc - b, yc - a, color);
	SetPixel(hdc, xc + b, yc - a, color);
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

void DrawCircle(HDC hdc, int xc, int yc, int xr, int yr) {
	int R = sqrt((xr - xc) * (xr - xc) + (yr - yc) * (yr - yc));
	int R2 = R * R;
	int x = 0, y = R;
	Draw8Points(hdc, xc, yc, x, y, RGB(0, 0, 0));
	while (x < y) {
		x++;
		y = round(sqrt((double)(R2 - x * x)));
		Draw8Points(hdc, xc, yc, x, y, RGB(0, 0, 0));
	}
}

int x, y;
bool flag = true;
vector<pair<int, int>> clicks;

struct Line {
	int x1, y1, x2, y2;
};

// Lines drawn so far
vector<Line> lines;

enum Drawing {
	DDA,
	MIDPOINTLINE,
	CIRCLE,
	LINE_CLIPPING,
	FILLING_DFS,
	FILLING_BFS
} drawingMethod;

union OutCode {
	unsigned All : 4;
	struct { unsigned left : 1, right : 1, bottom : 1, top : 1; };
};

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

struct PointD {
	double x, y;
};

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

// FILLING

POINT makePOINT(int x, int y) {
	POINT point;
	point.x = x, point.y = y;
	return point;
}

bool validPoint(int x, int y, int width, int height) {
	return x >= 0 && x < width && y >= 0 && y < height;
}

void fillingDFS(HWND hWnd, HDC hdc, int x, int y) {
	stack<POINT> points;
	points.push(makePOINT(x, y));
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };

	while (!points.empty()) {
		RECT rect;
		int width, height;
		if (GetClientRect(hWnd, &rect)) {
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		POINT cur = points.top(); points.pop();
		if (!validPoint(cur.x, cur.y, width, height)) continue;
		if (GetPixel(hdc, cur.x, cur.y) == color) continue;

		SetPixel(hdc, cur.x, cur.y, color);
		for (int i = 0; i < 4; i++)
			points.push(makePOINT(cur.x + dx[i], cur.y + dy[i]));
	}
}

void fillingBFS(HWND hWnd, HDC hdc, int x, int y) {
	queue<POINT> points;
	points.push(makePOINT(x, y));
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };

	while (!points.empty()) {
		RECT rect;
		int width, height;
		if (GetClientRect(hWnd, &rect)) {
			width = rect.right - rect.left;
			height = rect.bottom - rect.top;
		}

		POINT cur = points.front(); points.pop();
		if (!validPoint(cur.x, cur.y, width, height)) continue;
		if (GetPixel(hdc, cur.x, cur.y) == color) continue;

		SetPixel(hdc, cur.x, cur.y, color);
		for (int i = 0; i < 4; i++)
			points.push(makePOINT(cur.x + dx[i], cur.y + dy[i]));
	}
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_CREATE:
	{
		HMENU HMenuBar = CreateMenu();
		HMENU HFile = CreateMenu();
		HMENU HDrawLine = CreateMenu();
		HMENU HDrawCircle = CreateMenu();
		HMENU HLineClipping = CreateMenu();
		HMENU HFilling = CreateMenu();

		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HFile, "File");
		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HDrawLine, "Draw Line");
		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HDrawCircle, "Draw Circle");
		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HLineClipping, "Clipping");
		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HFilling, "Filling");

		AppendMenu(HFile, MF_STRING, IDM_EXIT, "Exit");
		AppendMenu(HDrawLine, MF_POPUP, DDA, "Draw Line Using DDA ");
		AppendMenu(HDrawLine, MF_POPUP, MIDPOINTLINE, "Draw Line Using Midpoint ");
		AppendMenu(HDrawCircle, MF_POPUP, CIRCLE, "Draw Circle Using Cartisian ");
		AppendMenu(HLineClipping, MF_POPUP, LINE_CLIPPING, "Line Clipping");
		AppendMenu(HFilling, MF_POPUP, FILLING_BFS, "BFS");
		AppendMenu(HFilling, MF_POPUP, FILLING_DFS, "DFS");

		SetMenu(hWnd, HMenuBar);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		clicks.clear();

		// Parse the menu selections:
		switch (wmId)
		{
			//case 2:
			//	drawingMethod = DDA;
			//	break;
			//case 3:
			//	drawingMethod = MIDPOINTLINE;
			//	break;
			//case 4:
			//	drawingMethod = CIRCLE;
			//	break;
			//case 5:
			//	drawingMethod = LINE_CLIPPING;
			//	break;

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			drawingMethod = (Drawing)wmId;

			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		//PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);
		//// TODO: Add any drawing code that uses hdc here...

		//if (clicks.size() == 2) {
		//	switch (drawingMethod) {
		//	case DDA:
		//		DrawDDA(hdc,
		//			clicks[0].first, clicks[0].second,
		//			clicks[1].first, clicks[1].second);
		//		break;
		//	case MIDPOINTLINE:
		//		DrawMidPointLine(hdc,
		//			clicks[0].first, clicks[0].second,
		//			clicks[1].first, clicks[1].second);
		//		break;
		//	case CIRCLE:
		//		DrawCircle(hdc,
		//			clicks[0].first, clicks[0].second,
		//			clicks[1].first, clicks[1].second);
		//		break;
		//	}
		//}
		InvalidateRect(hWnd, NULL, FALSE);
		//EndPaint(hWnd, &ps);
		break;
	}
	case WM_LBUTTONDOWN: {
		if (clicks.size() < 2) {
			clicks.push_back({
				LOWORD(lParam),
				HIWORD(lParam) });
		}
		pair<int, int> curClick(LOWORD(lParam), HIWORD(lParam));


		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (clicks.size() == 2) {
			switch (drawingMethod) {
			case DDA:
				lines.push_back(Line{
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second });
				DrawDDA(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case MIDPOINTLINE:
				lines.push_back(Line{
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second });
				DrawMidPointLine(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case CIRCLE:
				DrawCircle(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case LINE_CLIPPING:
			{
				color = RGB(255, 255, 255);
				for (int i = 0; i < lines.size(); i++) {
					DrawDDA(hdc,
						lines[i].x1, lines[i].y1,
						lines[i].x2, lines[i].y2);
				}

				color = RGB(0, 0, 0);
				int xleft = min(clicks[0].first, clicks[1].first);
				int xright = max(clicks[0].first, clicks[1].first);
				int ytop = min(clicks[0].second, clicks[1].second);
				int ybot = max(clicks[0].second, clicks[1].second);

				for (int i = 0; i < lines.size(); i++) {
					LineClipping(hdc,
						lines[i].x1, lines[i].y1,
						lines[i].x2, lines[i].y2,
						xleft, xright, ytop, ybot);
				}
				break;
			}

			}
			clicks.clear();
		}

		switch (drawingMethod) {
		case FILLING_DFS:
			fillingDFS(hWnd, hdc,
				curClick.first, curClick.second);
			break;

		case FILLING_BFS:
			fillingBFS(hWnd, hdc,
				curClick.first, curClick.second);
			break;

		default:
			break;
		}


		InvalidateRect(hWnd, NULL, FALSE);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
