#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "MacroSet.h"
#include "StructSet.h"
#include "BaseSystem.h"

void CurPos(short x, short y) {

	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(short show) {

	HANDLE ConsoleHandle;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(ConsoleHandle, &ConsoleCursor);
}

void StringColor(short color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CharBlink(char toBlink, short show, short color) {

	StringColor(color);
	if (show) putchar(toBlink);
	else putchar(' ');
	StringColor(White);
}

void K_Putchar(char toPrint[], short index) {

	putchar(toPrint[index]);
	if (toPrint[index + 1]) putchar(toPrint[index + 1]);
}

char GetKeyDown(void) {

	if (_kbhit()) return _getch();

	else return False;
}

short ClockGenerator(short MilliSecond) {

	if (MilliSecond == Tic) MilliSecond = 0;
	Sleep(50);
	MilliSecond += 50;

	return MilliSecond;
}

unsigned int _stdcall BeepPlayer(void* arg) {

	Beep((DWORD)Morse, 100);

	_endthreadex(0);

	return 0;
}

void TypeAnimation(char toPrint[]) {

	HANDLE hThread[1];
	DWORD dwThreadID;

	StringColor(Cyan);

	for (short i = 0; toPrint[i]; i += 2) {

		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, BeepPlayer, NULL, 0, (unsigned*)&dwThreadID);

		if (hThread[0]) CloseHandle(hThread[0]);

		if (toPrint[i] != ' ' && toPrint[i] != '.') {

			K_Putchar(toPrint, i);
			Sleep(25);
		}
		else {

			putchar(toPrint[i]);
			--i;
		}

		if (!toPrint[i + 1]) break;
	}

	StringColor(White);
}