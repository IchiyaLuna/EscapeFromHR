/*
2021 Yonsei Computer Programming Project (prof. Hyo Sang Lim)
[Game - Hard Rain Impact]

All code written by Sungha Choi

All rights reserved...
*/

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

#define CityHeight 20
#define CityWidth 12

#define CityTop 1
#define CityLeft 52

#define MaxHeight 4
#define PowerHeight 4
#define FactoryHeight 3
#define ResidenceHeight 2

#define DialogLength 63

enum { False, True };

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

enum {

	Back_Cyan = 191
};

enum BuildingType
{

	Blank,
	Power,
	Factory,
	Residence
};

enum PhaseState {

	BuildingPhase,
	EnterProductionPhase,
	ProductionPhase
};

enum ErrorCode {

	Canceled = -4,
	Confirm,
	NotingLeft,
	AlreadyOccupied
};

typedef struct {

	char UserName[11];
	char CityName[11];
}User;

typedef struct {

	short PowerLeft;
	short FactoryLeft;
	short ResidenceLeft;
}Buildings;

typedef struct {

	int EnergyState;
	int TechnologyState;
	int CapitalState;
}Resources;

typedef struct {

	User Usr;

	short UserPosition;

	Buildings Buil;

	short OccupyState[12];
	short Health[12];

	Resources Res;
}City;

typedef struct Rain{

	short IsStarExist[12];
	short StarHeight[12];
}Rain;

void SplashScreen(void);
void CharBlink(char toBlink, short show, short color);

void GameSetup(void);

void StoryDescriptor(void);

void PAC(void);
void CurPos(short x, short y);
void CursorView(short show);
void K_Putchar(char toPrint[], short index);
void StringColor(short color);
char GetKeyDown(void);
short ClockGenerator(short MilliSecond);

void TypeAnimation(char toPrint[]);
void DialogDisplay(char toPrint[]);

void UserInfo(char UserName[]);
void CityInfo(char CityName[]);

void GameInitialize(short GamePhase);
void BuildingHeight(void);
void AvailableBuilding(Buildings Buil);
void ResourceDisplayer(City City);
void SystemMessage(short MessageType);
void HardrainAlert(short Timer);

void UserPrint(short UserPosition);

short BuildingConfirm(short BuildingType);

void BuildingBuilder(City City);
void MakePower(short UserPosition, short Health);
void MakeFactory(short UserPosition, short Health);
void MakeResidence(short UserPosition, short Health);

void DisplayShield(short DamagePoint);
void MakeItRa1n(City* CityPtr, Rain* RainPtr);
void RaserBeam(City* CityPtr, Rain* RainPtr);

int main(void) {

	City CityStr = { .UserPosition = 0,
		.Buil.PowerLeft = 4, .Buil.FactoryLeft = 4, .Buil.ResidenceLeft = 4,
		.OccupyState = { Blank },
		.Res.EnergyState = 0, .Res.TechnologyState = 0, .Res.CapitalState = 0 };

	City* CityPtr = &CityStr;

	Rain RainStr = { .IsStarExist = { Blank }, .StarHeight = { Blank } };

	Rain* RainPtr = &RainStr;

	short GameState = BuildingPhase;
	short MilliSecond = 0;
	short RainCounter = 0;
	short IsBuildingError;
	char UserInput;

	srand((unsigned int)time(NULL));

	system("title Hard Rain Impact v1.0");

	SplashScreen();

	GameSetup();

	UserInfo(CityStr.Usr.UserName);
	CityInfo(CityStr.Usr.CityName);

	GameInitialize(GameState);
	AvailableBuilding(CityStr.Buil);

	SystemMessage(BuildingPhase);

	while (True) {

		UserInput = GetKeyDown();

		if (UserInput == 'x') break;

		else if (UserInput == 'a') --CityStr.UserPosition;
		else if (UserInput == 'd') ++CityStr.UserPosition;

		if (CityStr.UserPosition < 0) {

			CityStr.UserPosition = 0;
			continue;
		}
		if (CityStr.UserPosition > 11) {

			CityStr.UserPosition = 11;
			continue;
		}

		UserPrint(CityStr.UserPosition);
		//SystemMessage(GameState);

		if (!(UserInput == False || UserInput == 'a' || UserInput == 'd') && GameState == BuildingPhase) {

			IsBuildingError = False;

			if (UserInput == 'e') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					SystemMessage(AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.PowerLeft) {

					SystemMessage(NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Power)) {

						CityStr.OccupyState[CityStr.UserPosition] = Power;
						CityStr.Health[CityStr.UserPosition] = PowerHeight;
						--CityStr.Buil.PowerLeft;
					}
					else {

						SystemMessage(Canceled);
						IsBuildingError = True;
					}
				}
			}
			else if (UserInput == 't') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					SystemMessage(AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.FactoryLeft) {

					SystemMessage(NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Factory)) {

						CityStr.OccupyState[CityStr.UserPosition] = Factory;
						CityStr.Health[CityStr.UserPosition] = FactoryHeight;
						--CityStr.Buil.FactoryLeft;
					}
					else {

						SystemMessage(Canceled);
						IsBuildingError = True;
					}
				}
			}
			else if (UserInput == 'm') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					SystemMessage(AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.ResidenceLeft) {

					SystemMessage(NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Residence)) {

						CityStr.OccupyState[CityStr.UserPosition] = Residence;
						CityStr.Health[CityStr.UserPosition] = ResidenceHeight;
						--CityStr.Buil.ResidenceLeft;
					}
					else {

						SystemMessage(Canceled);
						IsBuildingError = True;
					}
				}
			}

			AvailableBuilding(CityStr.Buil);

			if (IsBuildingError == False) SystemMessage(GameState);

			BuildingBuilder(CityStr);

			if (!CityStr.Buil.PowerLeft && !CityStr.Buil.FactoryLeft && !CityStr.Buil.ResidenceLeft) {

				SystemMessage(EnterProductionPhase);
				GameInitialize(ProductionPhase);
				ResourceDisplayer(CityStr);
				GameState = ProductionPhase;
			}
		}
		else if (GameState == ProductionPhase) {
		
			HardrainAlert(10 - RainCounter);

			if (UserInput == ' ') {

				RaserBeam(CityPtr, RainPtr);
			}

			if (MilliSecond == 1000) {

				if (CityStr.OccupyState[CityStr.UserPosition] == Power) CityStr.Res.EnergyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Factory) CityStr.Res.TechnologyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Residence) CityStr.Res.CapitalState += CityStr.Health[CityStr.UserPosition];

				if (RainCounter < 10) {

					++RainCounter;
				}
				if (RainCounter == 10) {

					MakeItRa1n(CityPtr, RainPtr);
				}
				
			}
			
			ResourceDisplayer(CityStr);
			BuildingBuilder(CityStr);
		}

		MilliSecond = ClockGenerator(MilliSecond);
	}

	DialogDisplay("°ÔÀÓÀ» Á¾·áÇÕ´Ï´Ù... ³ªÁß¿¡ ´Ù½Ã ºË°Ú½À´Ï´Ù »ç·É°ü´Ô.");

	return 0;
}

void SplashScreen(void) {

	system("mode con:cols=92 lines=24");

	CursorView(False);

	StringColor(Red);

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

		if (i % 2) StringColor(Black);
		else StringColor(White);

		CurPos(30, 20);
		puts("¢º Press Any Key to Start ¢¸");

		if (_kbhit())break;

		Sleep(500);
	}

	StringColor(White);

	char Dummy = _getch();
}

void CharBlink(char toBlink, short show, short color) {

	StringColor(color);
	if (show) putchar(toBlink);
	else putchar(' ');
	StringColor(White);
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

		if (i % 2) StringColor(Black);
		else StringColor(White);

		CurPos(22, 20);
		puts("¢º Press Any Key ¢¸");

		if (_kbhit())break;

		Sleep(500);
	}

	StringColor(White);

	char Dummy = _getch();
}

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

void K_Putchar(char toPrint[], short index) {

	putchar(toPrint[index]);
	if (toPrint[index + 1]) putchar(toPrint[index + 1]);
}

void StringColor(short color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

char GetKeyDown(void) {

	if (_kbhit()) return _getch();

	else return False;
}

short ClockGenerator(short MilliSecond) {

	if (MilliSecond == 1000) MilliSecond = 0;
	Sleep(50);
	MilliSecond += 50;

	return MilliSecond;
}

void TypeAnimation(char toPrint[]) {

	StringColor(Cyan);

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

	StringColor(White);
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

	PAC();
}

void UserInfo(char UserName[]) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char CharBuffer;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(True);

	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
	printf("¦­ ´ç½ÅÀÇ ÀÌ¸§Àº? (ÃÖ´ë ¿µ¹® 10ÀÚ, °ø¹é ºÒ°¡)¦­           ¦­\n");
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n");

	CurPos(46, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("³²Àº ±ÛÀÚ ¼ö : %-24d", 56 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

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

				strcpy_s(UserName, 11, StringBuffer);
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

	printf("SYSTEM : %s »ç·É°ü´Ô, ÀÔ·ÂÇÏ½Å ÀÌ¸§ÀÌ ¸Â½À´Ï±î? [Y/N]", UserName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo(UserName);
}

void CityInfo(char CityName[]) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char CharBuffer;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(True);

	printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯\n");
	printf("¦­ ¹æ¾îÇÒ µµ½ÃÀÇ ÀÌ¸§Àº? (ÃÖ´ë ¿µ¹® 10ÀÚ, °ø¹é ºÒ°¡)¦­           ¦­\n");
	printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°\n");

	CurPos(53, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("³²Àº ±ÛÀÚ ¼ö : %-29d", 63 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 62 || CharBuffer == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : µµ½Ã ÀÌ¸§Àº ¹Ýµå½Ã ÀÔ·ÂÇØ¾ß ÇÕ´Ï´Ù.");

				CurPos(curInfo.dwCursorPosition.X, 1);
				Index = 0;

				Sleep(500);
			}
			else {

				strcpy_s(CityName, 11, StringBuffer);
				break;
			}
		}

		else if (CharBuffer == 8 && curInfo.dwCursorPosition.X > 53) {

			Index -= 2;
			if (Index > -1) StringBuffer[Index] = 0;
			putchar(' ');
			CurPos(curInfo.dwCursorPosition.X - 1, 1);
		}
		else if (CharBuffer == 8 && curInfo.dwCursorPosition.X == 53) {

			Index = 0;
			CurPos(curInfo.dwCursorPosition.X, 1);
		}

		Sleep(50);
	}

	CursorView(0);

	CurPos(1, 3);

	printf("SYSTEM : »ç·É°ü´Ô, ÀÔ·ÂÇÏ½Å µµ½ÃÀÇ ÀÌ¸§ÀÌ %s ÀÔ´Ï±î? [Y/N]", CityName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo(CityName);
}

void GameInitialize(short GamePhase) {

	if (GamePhase == BuildingPhase) {

		system("cls");

		CursorView(False);

		CurPos(1, 0); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 1); printf("¦­ "); StringColor(Yellow);
		printf("¹ßÀü¼Ò"); StringColor(White);
		printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : e¦­");
		CurPos(1, 2); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 3); printf("¦­ "); StringColor(Red);
		printf("°ø  Àå"); StringColor(White);
		printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : t¦­");
		CurPos(1, 4); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 5); printf("¦­ "); StringColor(Green);
		printf("ÁÖ°ÅÁö"); StringColor(White);
		printf("¦­ ³ôÀÌ 0¦­ °Ç¼³ °¡´É ¼ö : 0¦­ °Ç¼³ : m¦­");
		CurPos(1, 6); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
		CurPos(1, 7); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 8); printf("¦­ SYSTEM :                                  ¦­");
		CurPos(1, 9); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
		CurPos(1, 10); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 11); printf("¦­                                           ¦­");
		CurPos(1, 12); printf("¦­         <½ÅÀÔ »ç·É°üÀ» À§ÇÑ ¸Þ¸ð>         ¦­");
		CurPos(1, 13); printf("¦­                                           ¦­");
		CurPos(1, 14); printf("¦­           ÃëÀÓÀ» È¯¿µÇÏ³× »ç·É°ü          ¦­");
		CurPos(1, 15); printf("¦­  À§ ¸Þ´º¸¦ Âü°íÇÏ¿© µµ½Ã °Ç¼³À» ÁøÇàÇÏ°Ô  ¦­");
		CurPos(1, 16); printf("¦­     °¢ °Ç¹°Àº °íÀ¯ÀÇ ÀÚ¿øÀ» »ý»êÇÑ´Ù³×    ¦­");
		CurPos(1, 17); printf("¦­        ÀÌÈÄ »ý»ê ´Ü°è¿¡¼­´Â ÇÑ ¹ø¿¡       ¦­");
		CurPos(1, 18); printf("¦­      ÇÑ Á¾·ùÀÇ ÀÚ¿ø¸¸ »ý»êÀÌ °¡´ÉÇÏ³×     ¦­");
		CurPos(1, 19); printf("¦­      ±×·¯´Ï Çö¸íÇÏ°Ô °Ç¼³À» ÁøÇàÇÏ°Ô      ¦­");
		CurPos(1, 20); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
		CurPos(1, 21); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 22); printf("¦­ ÀÌ  µ¿¦­ ¿ÞÂÊ : a ¿À¸¥ÂÊ : d¦­ °ÔÀÓ Á¾·á : x¦­");
		CurPos(1, 23); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		BuildingHeight();

		CurPos(50, 0); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		for (short i = 1; i < 21; ++i) {
			CurPos(50, i);
			printf("¦­             ¦­");
		}
		CurPos(50, 21); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(50, 22); printf("¦­             ¦­");
		CurPos(50, 23); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		UserPrint(0);

		CurPos(0, 23);
	}
	else if (GamePhase == ProductionPhase) {


		CurPos(1, 0); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 1); printf("¦­ "); StringColor(Yellow);
		printf("¹ßÀü¼Ò"); StringColor(White);
		printf("¦­ "); StringColor(D_Yellow);
		printf("¿¡³ÊÁö"); StringColor(White);
		printf("¦­ EEEEEEEEEEEEEE16¦­ ¿À ·ù ÀÓ¦­");
		CurPos(1, 2); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 3); printf("¦­ "); StringColor(Red);
		printf("°ø  Àå"); StringColor(White);
		printf("¦­ "); StringColor(D_Red);
		printf("±â  ¼ú"); StringColor(White);
		printf("¦­ EEEEEEEEEEEEEE16¦­ ¿À ·ù ÀÓ¦­");
		CurPos(1, 4); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 5); printf("¦­ "); StringColor(Green);
		printf("ÁÖ°ÅÁö"); StringColor(White);
		printf("¦­ "); StringColor(D_Green);
		printf("ÀÚ  º»"); StringColor(White);
		printf("¦­ EEEEEEEEEEEEEE16¦­ ¿À ·ù ÀÓ¦­");
		CurPos(1, 6); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
		CurPos(1, 10); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 11); printf("¦­                                           ¦­");
		CurPos(1, 12); printf("¦­         <½ÅÀÔ »ç·É°üÀ» À§ÇÑ ¸Þ¸ð>         ¦­");
		CurPos(1, 13); printf("¦­                                           ¦­");
		CurPos(1, 14); printf("¦­    ¹æ±Ý °Ç¼³ÀÌ ¿Ï·áµÆ´Ù´Â ¼Ò½ÄÀ» µé¾ú³×   ¦­");
		CurPos(1, 15); printf("¦­          ÀÚ³×°¡ ÁÂ¿ì·Î ¿òÁ÷ÀÌ¸é           ¦­");
		CurPos(1, 16); printf("¦­         µµÂøÇÑ ±¸¿ªÀÇ °Ç¹°·ÎºÎÅÍ          ¦­");
		CurPos(1, 17); printf("¦­       °íÀ¯ÇÑ ÀÚ¿øÀ» È¹µæÇÒ ¼ö ÀÖ³×        ¦­");
		CurPos(1, 18); printf("¦­    ÇÊ¿äÇÑ ÀÚ¿øÀ» È¿À²ÀûÀ¸·Î ¸ð¾Æº¸°Ô      ¦­");
		CurPos(1, 19); printf("¦­                                           ¦­");
		CurPos(1, 20); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		CurPos(0, 23);
	}
}

void BuildingHeight(void) {


	CurPos(16, 1); printf("%d", PowerHeight);
	CurPos(16, 3); printf("%d", FactoryHeight);
	CurPos(16, 5); printf("%d", ResidenceHeight);

	CurPos(0, 23);
}

void AvailableBuilding(Buildings Buil) {



	if (!Buil.PowerLeft) StringColor(Red);
	CurPos(34, 1); printf("%d", Buil.PowerLeft);
	if (!Buil.PowerLeft) StringColor(White);

	if (!Buil.FactoryLeft) StringColor(Red);
	CurPos(34, 3); printf("%d", Buil.FactoryLeft);
	if (!Buil.FactoryLeft) StringColor(White);

	if (!Buil.ResidenceLeft) StringColor(Red);
	CurPos(34, 5); printf("%d", Buil.ResidenceLeft);
	if (!Buil.ResidenceLeft) StringColor(White);

	CurPos(0, 23);
}

void ResourceDisplayer(City City) {


	CurPos(19, 1);

	printf("%-16d", City.Res.EnergyState);

	CurPos(37, 1);

	if (City.OccupyState[City.UserPosition] == Power) {

		StringColor(Green);
		printf("»ý »ê Áß");
	}
	else {

		StringColor(Red);
		printf("´ë ±â Áß");
	}

	StringColor(White);

	CurPos(19, 3);

	printf("%-16d", City.Res.TechnologyState);

	CurPos(37, 3);

	if (City.OccupyState[City.UserPosition] == Factory) {

		StringColor(Green);
		printf("»ý »ê Áß");
	}
	else {

		StringColor(Red);
		printf("´ë ±â Áß");
	}

	StringColor(White);

	CurPos(19, 5);

	printf("%-16d", City.Res.CapitalState);

	CurPos(37, 5);

	if (City.OccupyState[City.UserPosition] == Residence) {

		StringColor(Green);
		printf("»ý »ê Áß");
	}
	else {

		StringColor(Red);
		printf("´ë ±â Áß"); CurPos(19, 3);
	}

	StringColor(White);

	CurPos(0, 23);
}

void SystemMessage(short MessageType) {

	CurPos(12, 8);

	for (short i = 0; i < 33; ++i)putchar(' ');

	CurPos(12, 8);

	switch (MessageType) {

	case BuildingPhase:

		printf("°Ç¹° °Ç¼³À» ÁøÇàÇØÁÖ¼¼¿ä.");
		break;

	case EnterProductionPhase:

		for (int i = 0; i < 4; ++i) {

			CurPos(12, 8);

			for (short i = 0; i < 33; ++i)putchar(' ');

			CurPos(12, 8);

			StringColor(Cyan);

			if (i % 2) printf("»ý»ê ´Ü°è¿¡ ÁøÀÔÇÕ´Ï´Ù.");
			else printf("Please Wait...");

			Sleep(500);
		}

		StringColor(White);
		break;

	case ProductionPhase:

		printf("ÀÚ¿ø »ý»êÀ» ÁøÇàÇØÁÖ¼¼¿ä.");
		break;

	case AlreadyOccupied:

		StringColor(Red);
		printf("ÀÌ¹Ì °Ç¹°À» Áö¾îÁø °ø°£ÀÔ´Ï´Ù.");
		StringColor(White);
		break;

	case NotingLeft:

		StringColor(Red);
		printf("³²Àº °Ç¹°ÀÌ ¾ø½À´Ï´Ù.");
		StringColor(White);
		break;

	case Confirm:

		StringColor(Green);
		printf("°Ç¼³ÇÏ½Ã·Á¸é ÇÑ ¹ø ´õ ´­·¯ÁÖ¼¼¿ä.");
		StringColor(White);
		break;

	case Canceled:

		StringColor(Red);
		printf("Ãë¼ÒµÇ¾ú½À´Ï´Ù.");
		StringColor(White);
		break;

	default:

		StringColor(Red);
		printf("Error, Someting Went Wrong");
		StringColor(White);
		break;
	}

	CurPos(0, 23);
}

void HardrainAlert(short Timer) {

	CurPos(12, 8);

	for (short i = 0; i < 33; ++i)putchar(' ');

	CurPos(12, 8);

	StringColor(Red);

	if (Timer > 0)
		printf("HardRain ±îÁö %2d½Ã°£ ³²¾Ò½À´Ï´Ù.", Timer);
	else
		printf("HardRainÀÌ ¶³¾îÁý´Ï´Ù...");

	StringColor(White);

	CurPos(0, 23);
}

void UserPrint(short UserPosition) {

	StringColor(Cyan);

	for (short i = 0; i < 12; ++i) {

		CurPos(CityLeft + i, 22);

		if (i == UserPosition) putchar('*');
		else putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

short BuildingConfirm(short BuildingType) {

	char UserInput;


	SystemMessage(Confirm);

	UserInput = _getch();

	if ((BuildingType == Power && UserInput == 'e') ||
		(BuildingType == Factory && UserInput == 't') ||
		(BuildingType == Residence && UserInput == 'm')) {

		return True;
	}

	return False;
}

void BuildingBuilder(City City) {

	for (short i = 0; i < CityWidth; ++i) {

		if (!City.OccupyState[i]) continue;
		if (City.OccupyState[i] == Power) MakePower(i, City.Health[i]);
		else if (City.OccupyState[i] == Factory) MakeFactory(i, City.Health[i]);
		else if (City.OccupyState[i] == Residence) MakeResidence(i, City.Health[i]);
	}
}

void MakePower(short UserPosition, short Health) {

	StringColor(Yellow);

	for (short i = CityHeight; i > CityHeight - MaxHeight; --i) {

		CurPos(CityLeft + UserPosition, i);

		if (i > CityHeight - Health)
			putchar('E');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void MakeFactory(short UserPosition, short Health) {

	StringColor(Red);

	for (short i = CityHeight; i > CityHeight - MaxHeight; --i) {

		CurPos(CityLeft + UserPosition, i);

		if (i > CityHeight - Health)
			putchar('T');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void MakeResidence(short UserPosition, short Health) {

	StringColor(Green);

	for (short i = CityHeight; i > CityHeight - MaxHeight; --i) {

		CurPos(CityLeft + UserPosition, i);

		if (i > CityHeight - Health)
			putchar('M');
		else
			putchar(' ');
	}

	StringColor(White);

	CurPos(0, 23);
}

void DisplayShield(short DamagePoint) {

	for (short i = 0; i < 12; ++i) {

		if (i == DamagePoint) StringColor(Red);
		else StringColor(Cyan);

		CurPos(CityLeft + i, CityHeight - 4);

		printf("¦¬");

		StringColor(White);
	}

	CurPos(0, 23);
}

void MakeItRa1n(City* CityPtr, Rain* RainPtr) {

	short RandomPercent;
	short RandomPosition = -1;
	short IsBlankSpaceExist = False;
	short IsBuildingDestroyed = False;

	RandomPercent = rand() % 100;

	if (RandomPercent < 30) {

		for (short i = 0; i < 12; ++i) {
			
			if (!RainPtr->IsStarExist[i]) {

				IsBlankSpaceExist = True;
				break;
			}
		}

		if (IsBlankSpaceExist) {

			while (True) {

				RandomPosition = rand() % 12;
				if (!RainPtr->IsStarExist[RandomPosition]) break;
			}

			RainPtr->IsStarExist[RandomPosition] = True;
			RainPtr->StarHeight[RandomPosition] = 0;
		}
	}

	for (short i = 0; i < 12; ++i) {

		if (i == RandomPosition) continue;

		if (RainPtr->IsStarExist[i]) ++RainPtr->StarHeight[i];

		if (RainPtr->StarHeight[i] > 14) {

			RainPtr->StarHeight[i] = 0;
			RainPtr->IsStarExist[i] = False;

			--CityPtr->Health[i];

			IsBuildingDestroyed = True;

			CurPos(CityLeft + i, 15);
			putchar(' ');

			DisplayShield(i);
		}
	}
	if (!IsBuildingDestroyed) DisplayShield(-1);

	for (short i = 0; i < 12; ++i) {

		if (RainPtr->StarHeight[i]) {

			CurPos(CityLeft + i, RainPtr->StarHeight[i]);
			putchar(' ');
		}

		CurPos(CityLeft + i, CityTop + RainPtr->StarHeight[i]);

		StringColor(D_Red);
		if (RainPtr->IsStarExist[i]) putchar('*');
		StringColor(White);
	}

	CurPos(0, 23);
}

void RaserBeam(City* CityPtr, Rain* RainPtr) {

	if (CityPtr->Res.EnergyState < 10) return;
	CityPtr->Res.EnergyState -= 10;

	for (short i = CityTop; i < 16; ++i) {

		CurPos(CityLeft + CityPtr->UserPosition, i);
		StringColor(Back_Cyan);
		putchar(' ');
	}

	Sleep(100);

	for (short i = CityTop; i < 16; ++i) {

		CurPos(CityLeft + CityPtr->UserPosition, i);
		StringColor(White);
		putchar(' ');
	}

	RainPtr->IsStarExist[CityPtr->UserPosition] = False;
	RainPtr->StarHeight[CityPtr->UserPosition] = 0;

	CurPos(0, 23);
}