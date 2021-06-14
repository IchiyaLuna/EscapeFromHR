#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "MacroSet.h"
#include "StructSet.h"
#include "DisplaySystem.h"
#include "BaseSystem.h"
#include "MenuSystem.h"

void SplashScreen(void) {

	short CursorPosition = 0;
	short IsSkipped = 0;
	char UserInput;

	system("mode con:cols=92 lines=24");

	CursorView(False);

	while (True) {

		CurPos(0, 0);

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

		for (int i = 0; !IsSkipped; ++i) {

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

			if (_kbhit()) {

				IsSkipped = 1;
				char Dummy = _getch();
			}

			Sleep(500);
		}

		StringColor(White);

		for (short i = 0; i < 28; ++i) {

			CurPos(30 + i, 20);
			putchar(' ');
		}

		if (_kbhit()) {

			UserInput = _getch();

			if (UserInput == 13) {

				switch (CursorPosition) {

				case 0:
					return;

				case 1:

					GameInfo();
					break;

				case 2:

					Ranking();
					break;

				case 3:

					Credit();
					break;

				case 4:

					exit(0);
					break;
				}
			}

			if (UserInput == -32) {

				UserInput = _getch();

				switch (UserInput) {

				case UP:

					if (CursorPosition > 0) --CursorPosition;
					break;

				case DOWN:

					if (CursorPosition < 4) ++CursorPosition;
					break;

				default:
					break;
				}
			}
		}

		MainMenu(CursorPosition);

		Sleep(50);
	}
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

	Beep((DWORD)_C, 100);

	StringColor(White);

	char Dummy = _getch();
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

void GameSetup(void) {

	char UserInput;

	system("cls");

	CurPos(16, 10); puts("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	CurPos(16, 11); puts("¦­ ±ÇÀå È­¸é ºñÀ²À» »ç¿ëÇÏ½Ã°Ú½À´Ï±î? (¸Å¿ì ±ÇÀå!) [Y/N]¦­");
	CurPos(16, 12); puts("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	while (True) {

		UserInput = _getch();

		Beep((DWORD)_C, 100);

		if (UserInput == 'Y' || UserInput == 'y') {

			system("mode con:cols=67 lines=24");
			break;
		}
		else if (UserInput == 'N' || UserInput == 'n') break;
	}

	system("cls");

	puts("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
	puts("¦­ ½ºÅä¸®¸¦ ½ÃÃ»ÇÏ½Ã°Ú½À´Ï±î? [Y/N]¦­");
	puts("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

	while (True) {

		UserInput = _getch();

		Beep((DWORD)_C, 100);

		if (UserInput == 'Y' || UserInput == 'y') {

			StoryDescriptor();
			break;
		}
		else if (UserInput == 'N' || UserInput == 'n') break;
	}
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

	while (True) {

		UserInput = _getch();

		Beep((DWORD)_C, 100);

		if (UserInput == 'Y' || UserInput == 'y') {

			return;
		}
		else if (UserInput == 'N' || UserInput == 'n') break;
	}

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

	while (True) {

		UserInput = _getch();

		Beep((DWORD)_C, 100);

		if (UserInput == 'Y' || UserInput == 'y') {

			return;
		}
		else if (UserInput == 'N' || UserInput == 'n') break;
	}

	CityInfo(CityName);
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

void UserInfoDisplayer(City CityStr) {

	CurPos(10, 17); printf("%-10s", CityStr.Usr.CityName);
	CurPos(33, 17); printf("%-10s", CityStr.Usr.UserName);
	CurPos(10, 19); printf("%-14d", CityStr.Score);
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
		CurPos(1, 15); printf("¦­           ÀÚ³×°¡ ÁÂ¿ì·Î ¿òÁ÷ÀÌ¸é          ¦­");
		CurPos(1, 16); printf("¦­          µµÂøÇÑ ±¸¿ªÀÇ °Ç¹°·ÎºÎÅÍ         ¦­");
		CurPos(1, 17); printf("¦­        °íÀ¯ÇÑ ÀÚ¿øÀ» È¹µæÇÒ ¼ö ÀÖ³×       ¦­");
		CurPos(1, 18); printf("¦­     ÇÊ¿äÇÑ ÀÚ¿øÀ» È¿À²ÀûÀ¸·Î ¸ð¾Æº¸°Ô     ¦­");
		CurPos(1, 19); printf("¦­        ÇÏµå·¹ÀÎÀÌ ¾ó¸¶ ³²Áö ¾Ê¾Ò³×...     ¦­");
		CurPos(1, 20); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");

		CurPos(0, 23);
	}
	else if (GamePhase == HardrainPhase) {

		CurPos(1, 10); printf("¦®¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¯");
		CurPos(1, 11); printf("¦­ ");
		StringColor(Cyan); printf("LASER"); StringColor(White);
		printf("¦­ ");
		StringColor(D_Yellow); printf("10 ¿¡³ÊÁö"); StringColor(White);
		printf("¦­ ÇÑ ÁÙ °ø°Ý¦­ ¹ß»ç¦­  Space¦­");
		CurPos(1, 12); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 13); printf("¦­ ");
		StringColor(Yellow); printf("PULSE"); StringColor(White);
		printf("¦­ ");
		StringColor(D_Green); printf("35 ÀÚ  º»"); StringColor(White);
		printf("¦­ °¡±î¿î 3°³¦­ ¹ß»ç¦­    p  ¦­");
		CurPos(1, 14); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 15); printf("¦­ ¼ö ¸®¦­ 15 ±â  ¼ú¦­ ÇÑ Ãþ ¼ö¸®¦­ ¼ö¸®¦­    f  ¦­");
		CurPos(1, 16); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦³¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 17); printf("¦­ µµ ½Ã¦­ 0000000000   ¦­ »ç·É°ü¦­ 0000000000  ¦­");
		CurPos(1, 18); printf("¦²¦¬¦¬¦¬¦¬¦¬¦¬¦¶¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦´");
		CurPos(1, 19); printf("¦­ Á¡ ¼ö¦­                                    ¦­");
		CurPos(1, 20); printf("¦±¦¬¦¬¦¬¦¬¦¬¦¬¦µ¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦¬¦°");
	}
}

void SystemMessage(short MessageType) {

	CurPos(12, 8);

	for (short i = 0; i < 33; ++i) putchar(' ');

	CurPos(12, 8);

	switch (MessageType) {

	case BuildingPhase:

		printf("°Ç¹° °Ç¼³À» ÁøÇàÇØÁÖ¼¼¿ä.");
		break;

	case EnterProductionPhase:

		for (int i = 0; i < 4; ++i) {

			CurPos(12, 8);

			for (short i = 0; i < 33; ++i) putchar(' ');

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

	for (short i = 0; i < 33; ++i) putchar(' ');

	CurPos(12, 8);

	StringColor(Red);

	if (Timer > 0)
		printf("HardRain ±îÁö %2dÃÊ ³²¾Ò½À´Ï´Ù.", Timer / 2);
	else
		printf("Hard Rain Impact");

	StringColor(White);

	CurPos(0, 23);
}