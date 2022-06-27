#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include "Swiat.h"

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Swiat swiat;

	swiat.menu();

	while (1) {
		int ch = _getch();
		if (ch == M_KEY) {
			ch = swiat.menu();
		}
		if (ch == ARROW)
			_getch();
		if (ch == ESC) {
			break;
		}
		swiat.wykonajTure();
		swiat.rysujSwiat();
	}

	return 0;
}