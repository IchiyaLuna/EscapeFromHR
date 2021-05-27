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

void UserPrint(short UserPosition);

short BuildingConfirm(short BuildingType);

void BuildingBuilder(City City);
void MakePower(short UserPosition, short Health);
void MakeFactory(short UserPosition, short Health);
void MakeResidence(short UserPosition, short Health);

void DisplayShield(short DamagePoint);
void MakeItRa1n(City* CityPtr, Rain* RainPtr);
void RaserBeam(City City, Rain* RainPtr);

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


			if (UserInput == ' ') {

				RaserBeam(CityStr, RainPtr);
			}

			if (MilliSecond == 1000) {

				if (CityStr.OccupyState[CityStr.UserPosition] == Power) CityStr.Res.EnergyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Factory) CityStr.Res.TechnologyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Residence) CityStr.Res.CapitalState += CityStr.Health[CityStr.UserPosition];

				if (RainCounter < 10) ++RainCounter;
				if (RainCounter == 10) {

					MakeItRa1n(CityPtr, RainPtr);
				}
			}
			
			ResourceDisplayer(CityStr);
			BuildingBuilder(CityStr);
		}

		MilliSecond = ClockGenerator(MilliSecond);
	}

	DialogDisplay("啪歜擊 謙猿м棲棻... 釭醞縑 棻衛 瞄啊蝗棲棻 餌滄婦椒.");

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
		puts("Ⅱ Press Any Key to Start ９");

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

	puts("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	puts("早 掏濰 �飛� 綠徽擊 餌辨ж衛啊蝗棲梱? (衙辦 掏濰!) [Y/N]早");
	puts("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') system("mode con:cols=67 lines=24");

	system("cls");

	puts("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	puts("早 蝶饜葬蒂 衛羶ж衛啊蝗棲梱? [Y/N]早");
	puts("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') StoryDescriptor();
}

void StoryDescriptor(void) {

	system("cls");

	DialogDisplay("SYSTEM : Incoming Message...");
	DialogDisplay("SYSTEM : 曹晝 詭衛雖殮棲棻.");
	DialogDisplay("薑羹碳貲曖 錳檣 縑檜瞪お(Agent)煎 檣п 殖檜 7褻陝戲煎 薺偃螺棻啻.");
	DialogDisplay("7褻陝曖 殖擎 陝濠曖 醞溘戲煎 и翕寰 捨紫蒂 嶸雖ж艘戲釭,");
	DialogDisplay("埠 憮煎 醱給ж罹 渦 濛擎 褻陝戲煎 釭斯橫雖晦 衛濛ц啻.");
	DialogDisplay("舒粽 夢餌曖 衛嘆溯檜暮縑 曖ж賊 檜楝и 醱給 ⑷鼻擎 晦ж晝熱瞳戲煎 陛樓腆 匙檜貊...");
	DialogDisplay("埠 瞪 雖掘 捨紫陛 殖曖 懍戮 褻陝戲煎 菴竣檜朝 �倣昄� 蝶蘋檜(White Sky) ⑷鼻檜 嫦儅й 匙檜塭 и棻啻.");
	DialogDisplay("衛嘆溯檜暮 唸婁縑憮 渦遵 懍選и 匙擎 �倣昄� 蝶蘋檜 嫦儅 �� 賃 喇 檜頂縑...");
	DialogDisplay("熱 褻 偃縑 殖ж朝 捨紫 鼻曖 殖 懍戮 褻陝菟檜 雖掘 醞溘縑 檜莊溥 翕衛棻嫦瞳戲煎 雖掘煎 踏嬴螳 頂葬朝...");
	DialogDisplay("ж萄溯檣(Hard Rain) ⑷鼻檜 衛濛腎橫 擒 5,000喇 除 雖樓脹棻朝 匙檜啻. ");
	DialogDisplay("辦葬 檣盟朝 謙蜓擊 跡瞪縑 舒堅 氈啻...");
	DialogDisplay("濠啻朝 檜楝и 瞰蜂瞳檣 鼻�窒□� 紫衛蒂 勒撲ж堅 檣盟曖 葆雖虞 �騆謊� 辦輿摹...");
	DialogDisplay("贗塭辦萄嬴觼(Cloud Ark)蒂 勒褻ж罹 嫦餌й 陽 梱雖 髦嬴陴朝 嘐暮擊 雖�秷� 餌滄婦戲煎 歜貲腎歷啻.");
	DialogDisplay("檣盟曖 嘐楚陛 斜渠曖 橫梟縑 殖溥氈啻...");
	DialogDisplay("餌滄婦...");
	DialogDisplay("勒癱蒂 綠啻.");
	DialogDisplay("SYSTEM : 鱔褐檜 謙猿腎歷蝗棲棻.");
}

void PAC(void) {

	for (int i = 0;; ++i) {

		if (i % 2) StringColor(Black);
		else StringColor(White);

		CurPos(22, 20);
		puts("Ⅱ Press Any Key ９");

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

	printf("旨");

	if (Line < 2) {

		for (short i = 0; i < DialogLength; ++i) printf("收");

		printf("收旬\n早\n曲");

		for (short i = 0; i < DialogLength; ++i) printf("收");

		printf("收旭");

		CurPos(DialogLength + 2, 1);
		printf("早");

		CurPos(2, 1);
		TypeAnimation(toPrint);
	}
	else {

		for (short i = 0; i < DialogLength; ++i) printf("收");

		printf("收旬\n早\n早\n曲");

		for (short i = 0; i < DialogLength; ++i) printf("收");

		printf("收旭");

		CurPos(DialogLength + 2, 1);
		printf("早");
		CurPos(DialogLength + 2, 2);
		printf("早");

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

	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收旬\n");
	printf("早 渡褐曖 檜葷擎? (譆渠 艙僥 10濠, 奢寥 碳陛)早           早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朴收收收收收收收收收收收旭\n");

	CurPos(46, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("陴擎 旋濠 熱 : %-24d", 56 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 55 || CharBuffer == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : 檜葷擎 奩萄衛 殮溘п撿 м棲棻.");

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

	printf("SYSTEM : %s 餌滄婦椒, 殮溘ж褐 檜葷檜 蜃蝗棲梱? [Y/N]", UserName);

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

	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收旬\n");
	printf("早 寞橫й 紫衛曖 檜葷擎? (譆渠 艙僥 10濠, 奢寥 碳陛)早           早\n");
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朴收收收收收收收收收收收旭\n");

	CurPos(53, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("陴擎 旋濠 熱 : %-29d", 63 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 62 || CharBuffer == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : 紫衛 檜葷擎 奩萄衛 殮溘п撿 м棲棻.");

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

	printf("SYSTEM : 餌滄婦椒, 殮溘ж褐 紫衛曖 檜葷檜 %s 殮棲梱? [Y/N]", CityName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo(CityName);
}

void GameInitialize(short GamePhase) {

	if (GamePhase == BuildingPhase) {

		system("cls");

		CursorView(False);

		CurPos(1, 0); printf("旨收收收收收收收有收收收收收收收有收收收收收收收收收收收收收收收收收有收收收收收收收收收旬");
		CurPos(1, 1); printf("早 "); StringColor(Yellow);
		printf("嫦瞪模"); StringColor(White);
		printf("早 堪檜 0早 勒撲 陛棟 熱 : 0早 勒撲 : e早");
		CurPos(1, 2); printf("曳收收收收收收收朱收收收收收收收朱收收收收收收收收收收收收收收收收收朱收收收收收收收收收朽");
		CurPos(1, 3); printf("早 "); StringColor(Red);
		printf("奢  濰"); StringColor(White);
		printf("早 堪檜 0早 勒撲 陛棟 熱 : 0早 勒撲 : t早");
		CurPos(1, 4); printf("曳收收收收收收收朱收收收收收收收朱收收收收收收收收收收收收收收收收收朱收收收收收收收收收朽");
		CurPos(1, 5); printf("早 "); StringColor(Green);
		printf("輿剪雖"); StringColor(White);
		printf("早 堪檜 0早 勒撲 陛棟 熱 : 0早 勒撲 : m早");
		CurPos(1, 6); printf("曲收收收收收收收朴收收收收收收收朴收收收收收收收收收收收收收收收收收朴收收收收收收收收收旭");
		CurPos(1, 7); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(1, 8); printf("早 SYSTEM :                                  早");
		CurPos(1, 9); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
		CurPos(1, 10); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(1, 11); printf("早                                           早");
		CurPos(1, 12); printf("早         <褐殮 餌滄婦擊 嬪и 詭賅>         早");
		CurPos(1, 13); printf("早                                           早");
		CurPos(1, 14); printf("早           鏃歜擊 �紊腎炡� 餌滄婦          早");
		CurPos(1, 15); printf("早  嬪 詭景蒂 霤堅ж罹 紫衛 勒撲擊 霞чж啪  早");
		CurPos(1, 16); printf("早     陝 勒僭擎 堅嶸曖 濠錳擊 儅骯и棻啻    早");
		CurPos(1, 17); printf("早        檜�� 儅骯 欽啗縑憮朝 и 廓縑       早");
		CurPos(1, 18); printf("早      и 謙盟曖 濠錳虜 儅骯檜 陛棟ж啻     早");
		CurPos(1, 19); printf("早      斜楝棲 ⑷貲ж啪 勒撲擊 霞чж啪      早");
		CurPos(1, 20); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
		CurPos(1, 21); printf("旨收收收收收收收有收收收收收收收收收收收收收收收收收收收收有收收收收收收收收收收收收收收旬");
		CurPos(1, 22); printf("早 檜  翕早 豭薹 : a 螃艇薹 : d早 啪歜 謙猿 : x早");
		CurPos(1, 23); printf("曲收收收收收收收朴收收收收收收收收收收收收收收收收收收收收朴收收收收收收收收收收收收收收旭");

		BuildingHeight();

		CurPos(50, 0); printf("旨收收收收收收收收收收收收收旬");
		for (short i = 1; i < 21; ++i) {
			CurPos(50, i);
			printf("早             早");
		}
		CurPos(50, 21); printf("曳收收收收收收收收收收收收收朽");
		CurPos(50, 22); printf("早             早");
		CurPos(50, 23); printf("曲收收收收收收收收收收收收收旭");

		UserPrint(0);

		CurPos(0, 23);
	}
	else if (GamePhase == ProductionPhase) {


		CurPos(1, 0); printf("旨收收收收收收收有收收收收收收收有收收收收收收收收收收收收收收收收收有收收收收收收收收收旬");
		CurPos(1, 1); printf("早 "); StringColor(Yellow);
		printf("嫦瞪模"); StringColor(White);
		printf("早 "); StringColor(D_Yellow);
		printf("縑傘雖"); StringColor(White);
		printf("早 EEEEEEEEEEEEEE16早 螃 盟 歜早");
		CurPos(1, 2); printf("曳收收收收收收收朱收收收收收收收朱收收收收收收收收收收收收收收收收收朱收收收收收收收收收朽");
		CurPos(1, 3); printf("早 "); StringColor(Red);
		printf("奢  濰"); StringColor(White);
		printf("早 "); StringColor(D_Red);
		printf("晦  獎"); StringColor(White);
		printf("早 EEEEEEEEEEEEEE16早 螃 盟 歜早");
		CurPos(1, 4); printf("曳收收收收收收收朱收收收收收收收朱收收收收收收收收收收收收收收收收收朱收收收收收收收收收朽");
		CurPos(1, 5); printf("早 "); StringColor(Green);
		printf("輿剪雖"); StringColor(White);
		printf("早 "); StringColor(D_Green);
		printf("濠  獄"); StringColor(White);
		printf("早 EEEEEEEEEEEEEE16早 螃 盟 歜早");
		CurPos(1, 6); printf("曲收收收收收收收朴收收收收收收收朴收收收收收收收收收收收收收收收收收朴收收收收收收收收收旭");
		CurPos(1, 10); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(1, 11); printf("早                                           早");
		CurPos(1, 12); printf("早         <褐殮 餌滄婦擊 嬪и 詭賅>         早");
		CurPos(1, 13); printf("早                                           早");
		CurPos(1, 14); printf("早    寞旎 勒撲檜 諫猿腑棻朝 模衝擊 菟歷啻   早");
		CurPos(1, 15); printf("早          濠啻陛 謝辦煎 遺霜檜賊           早");
		CurPos(1, 16); printf("早         紫雜и 掘羲曖 勒僭煎睡攪          早");
		CurPos(1, 17); printf("早       堅嶸и 濠錳擊 �僱磈� 熱 氈啻        早");
		CurPos(1, 18); printf("早    в蹂и 濠錳擊 �螃窕�戲煎 賅嬴爾啪      早");
		CurPos(1, 19); printf("早                                           早");
		CurPos(1, 20); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

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
		printf("儅 骯 醞");
	}
	else {

		StringColor(Red);
		printf("渠 晦 醞");
	}

	StringColor(White);

	CurPos(19, 3);

	printf("%-16d", City.Res.TechnologyState);

	CurPos(37, 3);

	if (City.OccupyState[City.UserPosition] == Factory) {

		StringColor(Green);
		printf("儅 骯 醞");
	}
	else {

		StringColor(Red);
		printf("渠 晦 醞");
	}

	StringColor(White);

	CurPos(19, 5);

	printf("%-16d", City.Res.CapitalState);

	CurPos(37, 5);

	if (City.OccupyState[City.UserPosition] == Residence) {

		StringColor(Green);
		printf("儅 骯 醞");
	}
	else {

		StringColor(Red);
		printf("渠 晦 醞"); CurPos(19, 3);
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

		printf("勒僭 勒撲擊 霞чп輿撮蹂.");
		break;

	case EnterProductionPhase:

		for (int i = 0; i < 4; ++i) {

			CurPos(12, 8);

			for (short i = 0; i < 33; ++i)putchar(' ');

			CurPos(12, 8);

			StringColor(Cyan);

			if (i % 2) printf("儅骯 欽啗縑 霞殮м棲棻.");
			else printf("Please Wait...");

			Sleep(500);
		}

		StringColor(White);
		CurPos(12, 8);
		printf("濠錳 儅骯擊 霞чп輿撮蹂.");
		break;

	case ProductionPhase:

		printf("濠錳 儅骯擊 霞чп輿撮蹂.");
		break;

	case AlreadyOccupied:

		StringColor(Red);
		printf("檜嘐 勒僭擊 雖橫霞 奢除殮棲棻.");
		StringColor(White);
		break;

	case NotingLeft:

		StringColor(Red);
		printf("陴擎 勒僭檜 橈蝗棲棻.");
		StringColor(White);
		break;

	case Confirm:

		StringColor(Green);
		printf("勒撲ж衛溥賊 и 廓 渦 揚楝輿撮蹂.");
		StringColor(White);
		break;

	case Canceled:

		StringColor(Red);
		printf("鏃模腎歷蝗棲棻.");
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

		printf("收");

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

void RaserBeam(City City, Rain* RainPtr) {

	if (City.Res.EnergyState < 10) return;
	City.Res.EnergyState -= 10;

	for (short i = CityTop; i < 15; ++i) {


	}
}