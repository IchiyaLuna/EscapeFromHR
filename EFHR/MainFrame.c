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

	User U;

	short UserPosition;

	Buildings B;

	short OccupyState[12];
	short Health[12];

	Resources R;
}City;

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

void UserInfo(char UserName[]);
void CityInfo(char CityName[]);

void GameInitialize(short GamePhase);
void BuildingHeight(void);
void AvailableBuilding(int AvailPower, int AvailFactory, int AvailResidence);
void ResourceDisplayer(int EnergyState, int TechnologyState, int CapitalState, short ResourceType);
void SystemMessage(char CityName[], short MessageType);

void UserPrint(short UserPosition);

short BuildingConfirm(short BuildingType);

void BuildingBuilder(short OccupyState[]);
void MakePower(short UserPosition, short Health);
void MakeFactory(short UserPosition, short Health);
void MakeResidence(short UserPosition, short Health);

int main(void) {

	City C = { .UserPosition = 0,
		.B.PowerLeft = 4, .B.FactoryLeft = 4, .B.ResidenceLeft = 4,
		.OccupyState = { Blank }, 
		.R.EnergyState = 0, .R.TechnologyState = 0, .R.CapitalState = 0 };
	
	short GameState = BuildingPhase;
	short IsBuildingError;
	char UserInput;

	system("title Hard Rain Impact v1.0");

	SplashScreen();
	
	GameSetup();

	UserInfo(C.U.UserName);
	CityInfo(C.U.CityName);

	GameInitialize(GameState);

	AvailableBuilding(C.B.PowerLeft, C.B.FactoryLeft, C.B.ResidenceLeft);
	UserPrint(C.UserPosition);
	SystemMessage(C.U.CityName, GameState);

	while (True) {

		UserInput = _getch();

		if (UserInput == 'x') break;

		else if (UserInput == 'a') --C.UserPosition;
		else if (UserInput == 'd') ++C.UserPosition;

		if (C.UserPosition < 0) {

			C.UserPosition = 0;
			continue;
		}
		if (C.UserPosition > 11) {

			C.UserPosition = 11;
			continue;
		}

		UserPrint(C.UserPosition);
		SystemMessage(C.U.CityName, GameState);

		if (!(UserInput == 'a' || UserInput == 'd') && GameState == BuildingPhase) {

			IsBuildingError = False;

			if (UserInput == 'e') {

				if (C.OccupyState[C.UserPosition]) {

					SystemMessage(C.U.CityName, AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!C.B.PowerLeft) {

					SystemMessage(C.U.CityName, NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Power)) {

						C.OccupyState[C.UserPosition] = Power;
						C.Health[C.UserPosition] = PowerHeight;
						--C.B.PowerLeft;
					}
					else GameState = Canceled;
				}
			}
			else if (UserInput == 't') {

				if (C.OccupyState[C.UserPosition]) {

					SystemMessage(C.U.CityName, AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!C.B.FactoryLeft) {

					SystemMessage(C.U.CityName, NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Factory)) {

						C.OccupyState[C.UserPosition] = Factory;
						C.Health[C.UserPosition] = FactoryHeight;
						--C.B.FactoryLeft;
					}
					else GameState = Canceled;
				}
			}
			else if (UserInput == 'm') {

				if (C.OccupyState[C.UserPosition]) {

					SystemMessage(C.U.CityName, AlreadyOccupied);
					IsBuildingError = True;
				}
				else if (!C.B.ResidenceLeft) {

					SystemMessage(C.U.CityName, NotingLeft);
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Residence)) {

						C.OccupyState[C.UserPosition] = Residence;
						C.Health[C.UserPosition] = ResidenceHeight;
						--C.B.ResidenceLeft;
					}
					else GameState = Canceled;
				}
			}

			AvailableBuilding(C.B.PowerLeft, C.B.FactoryLeft, C.B.ResidenceLeft);

			if (IsBuildingError == False) SystemMessage(C.U.CityName, GameState);
			if (GameState == Canceled) GameState = BuildingPhase;

			BuildingBuilder(C.OccupyState);

			if (!C.B.PowerLeft && !C.B.FactoryLeft && !C.B.ResidenceLeft) {

				SystemMessage(C.U.CityName, EnterProductionPhase);
				GameInitialize(ProductionPhase);
				ResourceDisplayer(C.R.EnergyState, C.R.TechnologyState, C.R.CapitalState, C.OccupyState[C.UserPosition]);
				GameState = ProductionPhase;
			}
		}
		else if (GameState == ProductionPhase) {

			if (C.OccupyState[C.UserPosition] == Power) ++C.R.EnergyState;
			else if (C.OccupyState[C.UserPosition] == Factory) ++C.R.TechnologyState;
			else if (C.OccupyState[C.UserPosition] == Residence) ++C.R.CapitalState;
			ResourceDisplayer(C.R.EnergyState, C.R.TechnologyState, C.R.CapitalState, C.OccupyState[C.UserPosition]);
		}
	}

	DialogDisplay("������ �����մϴ�... ���߿� �ٽ� �˰ڽ��ϴ� ��ɰ���.");

	return 0;
}

void SplashScreen(void) {

	system("mode con:cols=96 lines=24");

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
		puts("�� Press Any Key to Start ��");

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

	puts("����������������������������������������������������������������������������������������������������������������");
	puts("�� ���� ȭ�� ������ ����Ͻðڽ��ϱ�? (�ſ� ����!) [Y/N]��");
	puts("����������������������������������������������������������������������������������������������������������������");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') system("mode con:cols=67 lines=24");

	system("cls");

	puts("����������������������������������������������������������������������");
	puts("�� ���丮�� ��û�Ͻðڽ��ϱ�? [Y/N]��");
	puts("����������������������������������������������������������������������");

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') StoryDescriptor();
}

void StoryDescriptor(void) {

	system("cls");

	DialogDisplay("SYSTEM : Incoming Message...");
	DialogDisplay("SYSTEM : ��� �޽����Դϴ�.");
	DialogDisplay("��ü�Ҹ��� ���� ������Ʈ(Agent)�� ���� ���� 7�������� �ɰ����ٳ�.");
	DialogDisplay("7������ ���� ������ �߷����� �ѵ��� �˵��� �����Ͽ�����,");
	DialogDisplay("�� ���� �浹�Ͽ� �� ���� �������� ���������� �����߳�.");
	DialogDisplay("�κ� �ڻ��� �ùķ��̼ǿ� ���ϸ� �̷��� �浹 ������ ���ϱ޼������� ���ӵ� ���̸�...");
	DialogDisplay("�� �� ���� �˵��� ���� �ϼ� �������� �ڵ��̴� ȭ��Ʈ ��ī��(White Sky) ������ �߻��� ���̶� �Ѵٳ�.");
	DialogDisplay("�ùķ��̼� ������� ���� �Ͽ��� ���� ȭ��Ʈ ��ī�� �߻� �� �� �� �̳���...");
	DialogDisplay("�� �� ���� ���ϴ� �˵� ���� �� �ϼ� �������� ���� �߷¿� �̲��� ���ôٹ������� ������ ����� ������...");
	DialogDisplay("�ϵ巹��(Hard Rain) ������ ���۵Ǿ� �� 5,000�� �� ���ӵȴٴ� ���̳�. ");
	DialogDisplay("�츮 �η��� ������ ������ �ΰ� �ֳ�...");
	DialogDisplay("�ڳ״� �̷��� �������� ��Ȳ���� ���ø� �Ǽ��ϰ� �η��� ������ ����� ���ּ�...");
	DialogDisplay("Ŭ�����ũ(Cloud Ark)�� �����Ͽ� �߻��� �� ���� ��Ƴ��� �̼��� ������ ��ɰ����� �Ӹ�Ǿ���.");
	DialogDisplay("�η��� �̷��� �״��� ����� �޷��ֳ�...");
	DialogDisplay("��ɰ�...");
	DialogDisplay("������ ���.");
	DialogDisplay("SYSTEM : ����� ����Ǿ����ϴ�.");
}

void PAC(void) {

	for (int i = 0;; ++i) {

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Black);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

		CurPos(22, 20);
		puts("�� Press Any Key ��");

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

	printf("��");

	if (Line < 2) {

		for (short i = 0; i < DialogLength; ++i) printf("��");

		printf("����\n��\n��");

		for (short i = 0; i < DialogLength; ++i) printf("��");

		printf("����");

		CurPos(DialogLength + 2, 1);
		printf("��");

		CurPos(2, 1);
		TypeAnimation(toPrint);
	}
	else {

		for (short i = 0; i < DialogLength; ++i) printf("��");

		printf("����\n��\n��\n��");

		for (short i = 0; i < DialogLength; ++i) printf("��");

		printf("����");

		CurPos(DialogLength + 2, 1);
		printf("��");
		CurPos(DialogLength + 2, 2);
		printf("��");

		CurPos(2, 1);
		TypeAnimation(LineCutA);

		CurPos(2, 2);
		TypeAnimation(LineCutB);
	}
	CurPos(0, 2);

	PAC();
}

void UserInfo(char UserName[]) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char CharBuffer;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(1);

	printf("������������������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� �̸���? (�ִ� ���� 10��, ���� �Ұ�)��           ��\n");
	printf("������������������������������������������������������������������������������������������������������������������\n");

	CurPos(46, 1);

	while (1) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("���� ���� �� : %-24d", 56 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(1);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 55 || CharBuffer == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : �̸��� �ݵ�� �Է��ؾ� �մϴ�.");

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

	printf("SYSTEM : %s ��ɰ���, �Է��Ͻ� �̸��� �½��ϱ�? [Y/N]", UserName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo(UserName);
}

void CityInfo(char CityName[]) {

	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	char Dummy;
	char UserInput;
	char StringBuffer[11] = { 0 };

	int Index = 0;

	system("cls");

	CursorView(1);

	printf("��������������������������������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� ������ �̸���? (�ִ� ���� 10��, ���� �Ұ�)��           ��\n");
	printf("��������������������������������������������������������������������������������������������������������������������������������\n");

	CurPos(53, 1);

	while (1) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("���� ���� �� : %-29d", 63 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(1);

		Dummy = _getche();
		if (Dummy > 32) StringBuffer[Index] = Dummy;
		++Index;

		if (curInfo.dwCursorPosition.X == 62 || Dummy == 13) {

			if (StringBuffer[0] == 0) {

				CurPos(1, 3);
				printf("SYSTEM : ���� �̸��� �ݵ�� �Է��ؾ� �մϴ�.");

				CurPos(curInfo.dwCursorPosition.X, 1);
				Index = 0;

				Sleep(500);
			}
			else {

				strcpy_s(CityName, 11, StringBuffer);
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

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? [Y/N]", CityName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo(CityName);
}

void GameInitialize(short GamePhase) {

	if (GamePhase == BuildingPhase) {

		system("cls");

		CursorView(0);

		CurPos(1, 0);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 1);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);
		printf("������"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : e��"); CurPos(1, 2);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 3);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("��  ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : t��"); CurPos(1, 4);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 5);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�ְ���"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : m��"); CurPos(1, 6);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 7);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 8);
		printf("�� SYSTEM :                                  ��"); CurPos(1, 9);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 10);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 11);
		printf("��                                           ��"); CurPos(1, 12);
		printf("��         <���� ��ɰ��� ���� �޸�>         ��"); CurPos(1, 13);
		printf("��                                           ��"); CurPos(1, 14);
		printf("��           ������ ȯ���ϳ� ��ɰ�          ��"); CurPos(1, 15);
		printf("��  �� �޴��� �����Ͽ� ���� �Ǽ��� �����ϰ�  ��"); CurPos(1, 16);
		printf("��     �� �ǹ��� ������ �ڿ��� �����Ѵٳ�    ��"); CurPos(1, 17);
		printf("��      �׷��� �����ϰ� �Ǽ��� �����ϰ�      ��"); CurPos(1, 18);
		printf("��                                           ��"); CurPos(1, 19);
		printf("��                                           ��"); CurPos(1, 20);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 21);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 22);
		printf("�� ��  ���� ���� : a ������ : d�� ���� ���� : x��"); CurPos(1, 23);
		printf("������������������������������������������������������������������������������������������");

		BuildingHeight();

		CurPos(50, 0);
		printf("������������������������������"); CurPos(50, 1);
		for (short i = 2; i < 22; ++i) {
			printf("��             ��"); CurPos(50, i);
		}
		printf("������������������������������"); CurPos(50, 22);
		printf("��             ��"); CurPos(50, 23);
		printf("������������������������������");
	}
	else if (GamePhase == ProductionPhase) {

		CurPos(1, 0);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 1);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);
		printf("������"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), D_Yellow);
		printf("������"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� 1234567890123456�� �� �� �Ӧ�"); CurPos(1, 2);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 3);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("��  ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), D_Red);
		printf("��  ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� 1234567890123456�� �� �� �Ӧ�"); CurPos(1, 4);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 5);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�ְ���"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), D_Green);
		printf("��  ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		printf("�� 1234567890123456�� �� �� �Ӧ�"); CurPos(1, 6);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 10);
		printf("������������������������������������������������������������������������������������������"); CurPos(1, 11);
		printf("��                                           ��"); CurPos(1, 12);
		printf("��         <���� ��ɰ��� ���� �޸�>         ��"); CurPos(1, 13);
		printf("��                                           ��"); CurPos(1, 14);
		printf("��             ���ø� �� �Ǽ��߱�            ��"); CurPos(1, 15);
		printf("��           �¿�� �ڳװ� �����̸�          ��"); CurPos(1, 16);
		printf("��       �ڳװ� ������ ������ �ǹ��κ���     ��"); CurPos(1, 17);
		printf("��         ������ �ڿ��� ȹ���� �� �ֳ�      ��"); CurPos(1, 18);
		printf("��      �ʿ��� �ڿ��� ȿ�������� ��ƺ���    ��"); CurPos(1, 19);
		printf("��                                           ��"); CurPos(1, 20);
		printf("������������������������������������������������������������������������������������������"); CurPos(0, 23);
	}
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
	printf("%d", AvailResidence); CurPos(0, 23);
	if (!AvailResidence) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
}

void ResourceDisplayer(int EnergyState, int TechnologyState, int CapitalState, short ResourceType) {

	CurPos(19, 1);
	printf("%-16d", EnergyState); CurPos(37, 1);

	if (ResourceType == Power) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�� �� ��");
	}
	else {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("�� �� ��"); 
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(19, 3);
	printf("%-16d", TechnologyState); CurPos(37, 3);

	if (ResourceType == Factory) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�� �� ��");
	}
	else {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("�� �� ��"); 
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(19, 5);
	printf("%-16d", CapitalState); CurPos(37, 5);

	if (ResourceType == Residence) {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�� �� ��");
	}
	else {

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("�� �� ��"); CurPos(19, 3);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(0, 23);
}

void SystemMessage(char CityName[], short MessageType) {

	CurPos(12, 8);
	for (short i = 0; i < 33; ++i)putchar(' ');

	CurPos(12, 8);

	switch (MessageType) {
	
	case BuildingPhase:

		printf("�ǹ� �Ǽ��� �������ּ���.");
		break;

	case EnterProductionPhase:

		for (int i = 0; i < 5; ++i) {
			
			CurPos(12, 8);

			for (short i = 0; i < 33; ++i)putchar(' ');

			CurPos(12, 8);

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Cyan);

			if (i % 2) printf("���� �ܰ迡 �����մϴ�.");
			else printf("Please Wait...");

			Sleep(500);
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case ProductionPhase:

		printf("�ڿ� ������ �������ּ���.");
		break;

	case AlreadyOccupied:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("�̹� �ǹ��� ������ �����Դϴ�.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case NotingLeft:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("���� �ǹ��� �����ϴ�.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case Confirm:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);
		printf("�Ǽ��Ͻ÷��� �� �� �� �����ּ���.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case Canceled:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("��ҵǾ����ϴ�.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;
		
	default:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("Error, Someting Went Wrong");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;
	}

	CurPos(0, 23);
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

short BuildingConfirm(short BuildingType) {

	char UserInput;
	char DummyString[11] = { 0 };

	SystemMessage(DummyString, -3);

	UserInput = _getch();

	if ((BuildingType == Power && UserInput == 'e') ||
		(BuildingType == Factory && UserInput == 't') ||
		(BuildingType == Residence && UserInput == 'm')) {

		return True;
	}

	return False;
}

void BuildingBuilder(short OccupyState[]) {

	for (short i = 0; i < 12; ++i) {

		if (!OccupyState[i]) continue;
		if (OccupyState[i] == Power) MakePower(i, PowerHeight);
		else if (OccupyState[i] == Factory) MakeFactory(i, FactoryHeight);
		else if (OccupyState[i] == Residence) MakeResidence(i, ResidenceHeight);
	}
}

void MakePower(short UserPosition, short Health) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Yellow);

	for (short i = 20; i > 20 - Health; --i) {
	
		CurPos(52 + UserPosition, i);
		putchar('E');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(0, 23);
}

void MakeFactory(short UserPosition, short Health) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);

	for (short i = 20; i > 20 - Health; --i) {

		CurPos(52 + UserPosition, i);
		putchar('T');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(0, 23);
}

void MakeResidence(short UserPosition, short Health) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Green);

	for (short i = 20; i > 20 - Health; --i) {

		CurPos(52 + UserPosition, i);
		putchar('M');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);

	CurPos(0, 23);
}