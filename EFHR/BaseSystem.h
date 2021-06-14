#pragma once
#include "StructSet.h"

void CurPos(short x, short y);
void CursorView(short show);
void CharBlink(char toBlink, short show, short color);
void K_Putchar(char toPrint[], short index);
void StringColor(short color);
char GetKeyDown(void);
short ClockGenerator(short MilliSecond);
unsigned int _stdcall BeepPlayer(void* Sound);
void TypeAnimation(char toPrint[]);
char ParityMaker(int toTest);
void RankingRecorder(City CityPtr);