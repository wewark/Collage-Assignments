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

	CIRCLE_CARTESIAN,
	CIRCLE_POLAR,
	CIRCLE_POLAR_ITERATIVE,
	CIRCLE_MIDPOINT,
	
	LINE_CLIPPING,
	FILLING_DFS,
	FILLING_BFS
} drawingMethod;

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
		AppendMenu(HFile, MF_STRING, IDM_EXIT, "Exit");

		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HDrawLine, "Line");
		AppendMenu(HDrawLine, MF_POPUP, DDA, "DDA");
		AppendMenu(HDrawLine, MF_POPUP, MIDPOINTLINE, "Midpoint");

		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HDrawCircle, "Circle");
		AppendMenu(HDrawCircle, MF_POPUP, CIRCLE_CARTESIAN, "Cartisian");
		AppendMenu(HDrawCircle, MF_POPUP, CIRCLE_POLAR, "Polar");
		AppendMenu(HDrawCircle, MF_POPUP, CIRCLE_POLAR_ITERATIVE, "Iterative Polar");
		AppendMenu(HDrawCircle, MF_POPUP, CIRCLE_MIDPOINT, "Midpoint");

		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HLineClipping, "Clipping");
		AppendMenu(HLineClipping, MF_POPUP, LINE_CLIPPING, "Line Clipping");

		AppendMenu(HMenuBar, MF_POPUP, (UINT_PTR)HFilling, "Filling");
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
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
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
		//	case CIRCLE_CARTESIAN:
		//		cartesianCircle(hdc,
		//			clicks[0].first, clicks[0].second,
		//			clicks[1].first, clicks[1].second);
		//		break;
		//	}
		//}
		InvalidateRect(hWnd, NULL, FALSE);
		EndPaint(hWnd, &ps);
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

			case CIRCLE_CARTESIAN:
				cartesianCircle(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case CIRCLE_POLAR:
				PolarCircle(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case CIRCLE_POLAR_ITERATIVE:
				IterativePolarCircle(hdc,
					clicks[0].first, clicks[0].second,
					clicks[1].first, clicks[1].second);
				break;

			case CIRCLE_MIDPOINT:
				CircleMidPoint(hdc,
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
