/*
2021 Yonsei Computer Programming Project (prof. Hyo Sang Lim)
[Game - Hard Rain Impact]

All code written by Sungha Choi

All rights reserved...
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#define PowerHeight 3
#define FactoryHeight 3
#define ResidenceHeight 3

#define DialogLength 63

enum { 

	Black, 
	D_Blue, 
	D_Green, 
	D_Cyan, 
	D_Red, 
	D_Violet, 
	D_Yellow, 
	Gray, 
	D_Gray, 
	Blue, 
	Green, 
	Cyan, 
	Red, 
	Violet, 
	Yellow, 
	White 
};

struct User {

	char UserName[11];
	char CityName[11];
}U;

typedef struct {

	int PowerLeft;
	int FactoryLeft;
	int ResidenceLeft;
}Buildings;

void SplashScreen(void);
void CharBlink(char toBlink, short show, short color);

void GameSetup(void);

void StoryDescriptor(void);

void PAC(void);
void CurPos(short x, short y);
void CursorView(short show);
void K_Putchar(char toPrint[], short index);

void TypeAnimation(char toPrint[]);
void DialogDisplay(char toPrint[]);

void UserInfo(void);
void CityInfo(void);

void GameInitialize(void);
void BuildingHeight(void);
void AvailableBuilding(int AvailPower, int AvailFactory, int AvailResidence);
void SystemMessage(short MessageType);

void UserPrint(short UserPosition);

void MakePower(short UserPosition);
void MakeFactory(short UserPosition);
void MakeResidence(short UserPosition);

int main(void) {

	Buildings B = { .PowerLeft = 4,.FactoryLeft = 4,.ResidenceLeft = 4 };

	short OccupyState[12] = { 0 };
	
	short GameState = 0;
	short UserPosition = 0;
	short IsBuildingError = 0;
	char UserInput;

	system("title Hard Rain Impact v1.0");

	SplashScreen();
	
	GameSetup();

	UserInfo();
	CityInfo();

	GameInitialize();

	AvailableBuilding(B.PowerLeft, B.FactoryLeft, B.ResidenceLeft);
	SystemMessage(GameState);

	while (1) {

		IsBuildingError = 0;

		UserPrint(UserPosition);

		UserInput = _getch();

		if (UserInput == 'x') break;

		else if (UserInput == 'a') --UserPosition;
		else if (UserInput == 'd') ++UserPosition;

		else if (!GameState && UserInput == 'e') {

			if (OccupyState[UserPosition]) {

				SystemMessage(-1);
				IsBuildingError = 1;
			}
			else if (!B.PowerLeft) {

				SystemMessage(-2);
				IsBuildingError = 1;
			}

			if (!IsBuildingError) {

				MakePower(UserPosition);
				++OccupyState[UserPosition];
				--B.PowerLeft;
			}
		}
		else if (!GameState && UserInput == 't') {

			if (OccupyState[UserPosition]) {

				SystemMessage(-1);
				IsBuildingError = 1;
			}
			else if (!B.FactoryLeft) {

				SystemMessage(-2);
				IsBuildingError = 1;
			}

			if (!IsBuildingError) {

				MakeFactory(UserPosition);
				++OccupyState[UserPosition];
				--B.FactoryLeft;
			}
		}
		else if (!GameState && UserInput == 'm') {

			if (OccupyState[UserPosition]) {

				SystemMessage(-1);
				IsBuildingError = 1;
			}
			else if (!B.ResidenceLeft) {

				SystemMessage(-2);
				IsBuildingError = 1;
			}

			if (!IsBuildingError) {

				MakeResidence(UserPosition);
				++OccupyState[UserPosition];
				--B.ResidenceLeft;
			}
		}

		AvailableBuilding(B.PowerLeft, B.FactoryLeft, B.ResidenceLeft);

		if (!GameState && !B.PowerLeft && !B.FactoryLeft && !B.ResidenceLeft) ++GameState;
		if (!IsBuildingError) SystemMessage(GameState);

		if (UserPosition < 0) UserPosition = 0;
		else if (UserPosition > 11) UserPosition = 11;
	}

	DialogDisplay("°ÔÀÓÀ» Á¾·áÇÕ´Ï´Ù... ³ªÁß¿¡ ´Ù½Ã ºË°Ú½À´Ï´Ù »ç·É°ü´Ô.");
	return 0;
}

void SplashScreen(void) {

	CursorView(0);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);

	putchar('\n');
	puts(":::    :::     :::     :::::::::  :::::::::   :::::::::      :::     ::::::::::: ::::    :::");
	puts(":+:    :+:   :+: :+:   :+:    :+: :+:    :+:  :+:    :+:   :+: :+:       :+:     :+:+:   :+:");
	puts("+:+    +:+  +:+   +:+  +:+    +:+ +:+    +:+  +:+    +:+  +:+   +:+      +:+     :+:+:+  +:+");
	puts("+#++:++#++ +#++:++#++: +#++:++#:  +#+    +:+  +#++:++#:  +#++:++#++:     +#+     +#+ +:+ +#+");
	puts("+#+    +#+ +#+     +#+ +#+    +#+ +#+    +#+  +#+    +#+ +#+     +#+     +#+     +#+  +#+#+#");
	puts("#+#    #+# #+#     #+# #+#    #+# #+#    #+#  #+#    #+# #+#     #+#     #+#     #+#   #+#+#");
	puts("###    ### ###     ### ###    ### #########   ###    ### ###     ### ########### ###    ####");
	putchar('\n');
	puts("          ::::::::::: ::::    ::::  :::::::::      :::      ::::::::  :::::::::::");
	puts("              :+:     +:+:+: :+:+:+ :+:    :+:   :+: :+:   :+:    :+:     :+:    ");
	puts("              +:+     +:+ +:+:+ +:+ +:+    +:+  +:+   +:+  +:+            +:+    ");
	puts("              +#+     +#+  +:+  +#+ +#++:++#+  +#++:++#++: +#+            +#+    ");
	puts("              +#+     +#+       +#+ +#+        +#+     +#+ +#+            +#+    ");
	puts("              #+#     #+#       #+# #+#        #+#     #+# #+#    #+#     #+#    ");
	puts("          ########### ###       ### ###        ###     ###  ########      ###    ");

	for (int i = 0;; ++i) {

		CurPos(2, 10);
		CharBlink('+', i % 2, Red);

		CurPos(86, 12);
		CharBlink('+', i % 2, Red);

		CurPos(4, 14);
		CharBlink('*', i % 2, Red);

		CurPos(84, 14);
		CharBlink('*', i % 2, Red);

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Black);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

		CurPos(30, 17);
		puts("¢º Press Any Key to Start ¢¸");

		if (_kbhit())break;

		Sleep(500);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	char Dummy = _getch();
}

void CharBlink(char toBlink, short show, short color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	if (show) putchar(toBlink);
	else putchar(' ');
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
}

void GameSetup(void) {

	char UserInput;

	system("cls");

	puts("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	puts("¦­ ±ÇÀå È­¸é ºñÀ²À» »ç¿ëÇÏ½Ã°Ú½À´Ï±î? (¸Å¿ì ±ÇÀå!) [Y/N]¦­");
	puts("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') system("mode con:cols=67 lines=24");

	system("cls");

	puts("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	puts("¦­ ½ºÅä¸®¸¦ ½ÃÃ»ÇÏ½Ã°Ú½À´Ï±î? [Y/N]¦­");
	puts("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') StoryDescriptor();
}

void StoryDescriptor(void) {

	system("cls");

	DialogDisplay("SYSTEM : Incoming Message...");
	DialogDisplay("SYSTEM : ±ä±Þ ¸Þ½ÃÁöÀÔ´Ï´Ù.");
	DialogDisplay("Á¤Ã¼ºÒ¸íÀÇ ¿øÀÎ ¿¡ÀÌÀüÆ®(Agent)·Î ÀÎÇØ ´ÞÀÌ 7Á¶°¢À¸·Î ÂÉ°³Á³´Ù³×.");
	DialogDisplay("7Á¶°¢ÀÇ ´ÞÀº °¢ÀÚÀÇ Áß·ÂÀ¸·Î ÇÑµ¿¾È ±Ëµµ¸¦ À¯ÁöÇÏ¿´À¸³ª,");
	DialogDisplay("°ð ¼­·Î Ãæµ¹ÇÏ¿© ´õ ÀÛÀº Á¶°¢À¸·Î ³ª´µ¾îÁö±â ½ÃÀÛÇß³×.");
	DialogDisplay("µÎºê ¹Ú»çÀÇ ½Ã¹Ä·¹ÀÌ¼Ç¿¡ ÀÇÇÏ¸é ÀÌ·¯ÇÑ Ãæµ¹ Çö»óÀº ±âÇÏ±Þ¼öÀûÀ¸·Î °¡¼ÓµÉ °ÍÀÌ¸ç...");
	DialogDisplay("°ð Àü Áö±¸ ±Ëµµ°¡ ´ÞÀÇ ¾Ï¼® Á¶°¢À¸·Î µÚµ¤ÀÌ´Â È­ÀÌÆ® ½ºÄ«ÀÌ(White Sky) Çö»óÀÌ ¹ß»ýÇÒ °ÍÀÌ¶ó ÇÑ´Ù³×.");
	DialogDisplay("½Ã¹Ä·¹ÀÌ¼Ç °á°ú¿¡¼­ ´õ¿í ¾Ï¿ïÇÑ °ÍÀº È­ÀÌÆ® ½ºÄ«ÀÌ ¹ß»ý ÈÄ ¸î ³â ÀÌ³»¿¡...");
	DialogDisplay("¼ö Á¶ °³¿¡ ´ÞÇÏ´Â ±Ëµµ »óÀÇ ´Þ ¾Ï¼® Á¶°¢µéÀÌ Áö±¸ Áß·Â¿¡ ÀÌ²ø·Á µ¿½Ã´Ù¹ßÀûÀ¸·Î Áö±¸·Î ½ñ¾ÆÁ® ³»¸®´Â...");
	DialogDisplay("ÇÏµå·¹ÀÎ(Hard Rain) Çö»óÀÌ ½ÃÀÛµÇ¾î ¾à 5,000³â °£ Áö¼ÓµÈ´Ù´Â °ÍÀÌ³×. ");
	DialogDisplay("¿ì¸® ÀÎ·ù´Â Á¾¸»À» ¸ñÀü¿¡ µÎ°í ÀÖ³×...");
	DialogDisplay("ÀÚ³×´Â ÀÌ·¯ÇÑ Àý¸ÁÀûÀÎ »óÈ²¿¡¼­ µµ½Ã¸¦ °Ç¼³ÇÏ°í ÀÎ·ùÀÇ ¸¶Áö¸· Èñ¸ÁÀÎ ¿ìÁÖ¼±...");
	DialogDisplay("Å¬¶ó¿ìµå¾ÆÅ©(Cloud Ark)¸¦ °ÇÁ¶ÇÏ¿© ¹ß»çÇÒ ¶§ ±îÁö »ì¾Æ³²´Â ¹Ì¼ÇÀ» ÁöÈÖÇÒ »ç·É°üÀ¸·Î ÀÓ¸íµÇ¾ú³×.");
	DialogDisplay("ÀÎ·ùÀÇ ¹Ì·¡°¡ ±×´ëÀÇ ¾î±ú¿¡ ´Þ·ÁÀÖ³×...");
	DialogDisplay("»ç·É°ü...");
	DialogDisplay("°ÇÅõ¸¦ ºñ³×.");
	DialogDisplay("SYSTEM : Åë½ÅÀÌ Á¾·áµÇ¾ú½À´Ï´Ù.");
}

void PAC(void) {

	for (int i = 0;; ++i) {

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Black);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

		CurPos(22, 20);
		puts("¢º Press Any Key ¢¸");

		if (_kbhit())break;

		Sleep(500);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	char Dummy = _getch();
}

void CurPos(short x, short y) {

	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(short show) {

	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void K_Putchar(char toPrint[], short index) {

	putchar(toPrint[index]);
	if (toPrint[index + 1]) putchar(toPrint[index + 1]);
}

void TypeAnimation(char toPrint[]) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cyan);

	for (short i = 0; toPrint[i]; i += 2) {

		if (toPrint[i] != ' ') {

			K_Putchar(toPrint, i);
			Sleep(25);
		}
		else {

			putchar(' ');
			--i;
		}

		if (!toPrint[i + 1]) break;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
}

void DialogDisplay(char toPrint[]) {

	char LineCutA[DialogLength + 1];
	char LineCutB[DialogLength + 1];

	short Line = 1;
	short StrLen = (short)strlen(toPrint);

	if (StrLen > DialogLength) {

		strncpy_s(LineCutA, sizeof(LineCutA), toPrint, DialogLength);

		for (short i = 0; i < StrLen - DialogLength; ++i) LineCutB[i] = toPrint[i + DialogLength];

		LineCutB[StrLen - DialogLength] = 0;

		++Line;
	}

	system("cls");

	CurPos(0, 0);

	printf("¦®");

	if (Line < 2) {

		for (short i = 0; i < DialogLength; ++i) printf("¦¬");

		printf("¦¬¦¯\n¦­\n¦±");

		for (short i = 0; i < DialogLength; ++i) printf("¦¬");

		printf("¦¬¦°");

		CurPos(DialogLength + 2, 1);
		printf("¦­");

		CurPos(2, 1);
		TypeAnimation(toPrint);
	}
	else {

		for (short i = 0; i < DialogLength; ++i) printf("¦¬");

		printf("¦¬¦¯\n¦­\n¦­\n¦±");

		for (short i = 0; i < DialogLength; ++i) printf("¦¬");

		printf("¦¬¦°");

		CurPos(DialogLength + 2, 1);
		printf("¦­");
		CurPos(DialogLength + 2, 2);
		printf("¦­");

		CurPos(2, 1);
		TypeAnimation(LineCutA);

		CurPos(2, 2);
		TypeAnimation(LineCutB);
	}
	CurPos(0, 2);

	PAC();
}

void UserInfo(void) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char CharBuffer;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(1);

	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
	printf("¦­ ´ç½ÅÀÇ ÀÌ¸§Àº? (ÃÖ´ë ¿µ¹® 10ÀÚ, °ø¹é ºÒ°¡)¦­           ¦­\n");
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n");

	CurPos(46, 1);

	while (1) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("³²Àº ±ÛÀÚ ¼ö : %-24d", 56 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(1);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 55 || CharBuffer == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : ÀÌ¸§Àº ¹Ýµå½Ã ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù.");

				CurPos(curInfo.dwCursorPosition.X, 1);
				Index = 0;

				Sleep(500);
			}
			else {
			
				strcpy_s(U.UserName, sizeof(U.UserName), StringBuffer);
				break;
			}
		}

		else if (CharBuffer == 8 && curInfo.dwCursorPosition.X > 46) {

			Index -= 2;
			if (Index > -1) StringBuffer[Index] = 0;
			putchar(' ');
			CurPos(curInfo.dwCursorPosition.X - 1, 1);
		}
		else if (CharBuffer == 8 && curInfo.dwCursorPosition.X == 46) {

			Index = 0;
			CurPos(curInfo.dwCursorPosition.X, 1);
		}

		Sleep(50);
	}

	CursorView(0);

	CurPos(1, 3);

	printf("SYSTEM : %s »ç·É°ü´Ô, ÀÔ·ÂÇÏ½Å ÀÌ¸§ÀÌ ¸Â½À´Ï±î? [Y/N]", U.UserName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo();
}

void CityInfo(void) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char Dummy;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(1);

	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
	printf("¦­ ¹æ¾îÇÒ µµ½ÃÀÇ ÀÌ¸§Àº? (ÃÖ´ë ¿µ¹® 10ÀÚ, °ø¹é ºÒ°¡)¦­           ¦­\n");
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n");

	CurPos(53, 1);

	while (1) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("³²Àº ±ÛÀÚ ¼ö : %-29d", 63 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(1);

		Dummy = _getche();
		if (Dummy > 32) StringBuffer[Index] = Dummy;
		++Index;

		if (curInfo.dwCursorPosition.X == 62 || Dummy == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : µµ½Ã ÀÌ¸§Àº ¹Ýµå½Ã ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù.");

				CurPos(curInfo.dwCursorPosition.X, 1);
				Index = 0;

				Sleep(500);
			}
			else {

				strcpy_s(U.CityName, sizeof(U.CityName), StringBuffer);
				break;
			}
		}

		else if (Dummy == 8 && curInfo.dwCursorPosition.X > 53) {

			Index -= 2;
			if(Index > -1) StringBuffer[Index] = 0;
			putchar(' ');
			CurPos(curInfo.dwCursorPosition.X - 1, 1);
		}
		else if (Dummy == 8 && curInfo.dwCursorPosition.X == 53) {

			Index = 0;
			CurPos(curInfo.dwCursorPosition.X, 1);
		}

		Sleep(50);
	}

	CursorView(0);

	CurPos(1, 3);

	printf("SYSTEM : »ç·É°ü´Ô, ÀÔ·ÂÇÏ½Å µµ½ÃÀÇ ÀÌ¸§ÀÌ %s ÀÔ´Ï±î? [Y/N]", U.CityName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void GameInitialize(void) {

	system("cls");

	CursorView(0);

	CurPos(1, 0);
	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯"); CurPos(1, 1);
	printf("¦­ "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);
	  printf("¹ßÀü¼Ò"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	        printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : e¦­"); CurPos(1, 2);
	printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´"); CurPos(1, 3);
	printf("¦­ "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
	  printf("°ø  Àå"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	        printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : t¦­"); CurPos(1, 4);
	printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´"); CurPos(1, 5);
	printf("¦­ "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
	  printf("ÁÖ°ÅÁö"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	        printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : m¦­"); CurPos(1, 6);
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°"); CurPos(1, 7);
	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯"); CurPos(1, 8);
	printf("¦­ SYSTEM :                                  ¦­"); CurPos(1, 9);
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°"); CurPos(1, 10);
	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯"); CurPos(1, 11);
	printf("¦­                                           ¦­"); CurPos(1, 12);
	printf("¦­                <ÀÓ½Ã µµ¿ò¸»>              ¦­"); CurPos(1, 13);
	printf("¦­                                           ¦­"); CurPos(1, 14);
	printf("¦­  À§ ¸Þ´ºÀÇ °Ç¼³Å°¸¦ ´©¸£¸é °Ç¹°À» Áþ´Â´Ù. ¦­"); CurPos(1, 15);
	printf("¦­                                           ¦­"); CurPos(1, 16);
	printf("¦­      ÇöÁ¦ Á¦ÀÛ ´Ü°è : °Ç¹° °Ç¼³ ±¸Çö      ¦­"); CurPos(1, 17);
	printf("¦­                                           ¦­"); CurPos(1, 18);
	printf("¦­                                           ¦­"); CurPos(1, 19);
	printf("¦­                                           ¦­"); CurPos(1, 20);
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°"); CurPos(1, 21);
	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯"); CurPos(1, 22);
	printf("¦­ ÀÌ  µ¿¦­ ¿ÞÂÊ : a ¿À¸¥ÂÊ : d¦­ °ÔÀÓ Á¾·á : x¦­"); CurPos(1, 23);
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°"); 

	BuildingHeight();

	CurPos(50, 0);
	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯"); CurPos(50, 1);
	for (short i = 2; i < 22; ++i) {
		printf("¦­             ¦­"); CurPos(50, i);
	}
	printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´"); CurPos(50, 22);
	printf("¦­             ¦­"); CurPos(50, 23);
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
}

void BuildingHeight(void) {

	CurPos(16, 1);
	printf("%d", PowerHeight); CurPos(16, 3);
	printf("%d", FactoryHeight); CurPos(16, 5);
	printf("%d", ResidenceHeight);
}

void AvailableBuilding(int AvailPower, int AvailFactory, int AvailResidence) {

	CurPos(34, 1);

	if (!AvailPower) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
	printf("%d", AvailPower); CurPos(34, 3);
	if (!AvailPower) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	if (!AvailFactory) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
	printf("%d", AvailFactory); CurPos(34, 5);
	if (!AvailFactory) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	if (!AvailResidence) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
	printf("%d", AvailResidence);
	if (!AvailResidence) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
}

void SystemMessage(short MessageType) {

	CurPos(12, 8);
	for (short i = 0; i < 33; ++i)putchar(' ');

	CurPos(12, 8);

	switch (MessageType) {
	
	case 0:

		printf("°Ç¹° °Ç¼³À» ÁøÇàÇØÁÖ¼¼¿ä.");
		break;

	case 1:

		printf("%s µµ½Ã¸¦ ¹æ¾îÇÏ¶ó!", U.CityName);
		break;

	case -1:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("ÀÌ¹Ì °Ç¹°À» Áö¾îÁø °ø°£ÀÔ´Ï´Ù.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case -2:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("³²Àº °Ç¹°ÀÌ ¾ø½À´Ï´Ù.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	default:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("Error, Someting Went Wrong");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;
	}
}

void UserPrint(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cyan);

	for (short i = 0; i < 12; ++i) {
		
		CurPos(52 + i, 22);

		if (i == UserPosition) putchar('*');
		else putchar(' ');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	CurPos(0, 23);
}

void MakePower(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);

	for (short i = 20; i > 20 - PowerHeight; --i) {
	
		CurPos(52 + UserPosition, i);
		putchar('E');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	CurPos(0, 23);
}

void MakeFactory(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);

	for (short i = 20; i > 20 - FactoryHeight; --i) {

		CurPos(52 + UserPosition, i);
		putchar('T');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	CurPos(0, 23);
}

void MakeResidence(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);

	for (short i = 20; i > 20 - ResidenceHeight; --i) {

		CurPos(52 + UserPosition, i);
		putchar('M');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
	CurPos(0, 23);
}