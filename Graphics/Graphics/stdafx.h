// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here

extern COLORREF color;

POINT makePOINT(int x, int y);

#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
using namespace std;

#include "Line.h"
#include "Circle.h"
#include "Filling.h"
#include "Clipping.h"
#include "Curve.h"
