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

	DialogDisplay("������ �����մϴ�... ���߿� �ٽ� �˰ڽ��ϴ� ��ɰ���.");
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

void UserInfo(void) {

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

	printf("SYSTEM : %s ��ɰ���, �Է��Ͻ� �̸��� �½��ϱ�? [Y/N]", U.UserName);

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

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? [Y/N]", U.CityName);

	UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void GameInitialize(void) {

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
	printf("��                <�ӽ� ����>              ��"); CurPos(1, 13);
	printf("��                                           ��"); CurPos(1, 14);
	printf("��  �� �޴��� �Ǽ�Ű�� ������ �ǹ��� ���´�. ��"); CurPos(1, 15);
	printf("��                                           ��"); CurPos(1, 16);
	printf("��      ���� ���� �ܰ� : �ǹ� �Ǽ� ����      ��"); CurPos(1, 17);
	printf("��                                           ��"); CurPos(1, 18);
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

		printf("�ǹ� �Ǽ��� �������ּ���.");
		break;

	case 1:

		printf("%s ���ø� ����϶�!", U.CityName);
		break;

	case -1:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("�̹� �ǹ��� ������ �����Դϴ�.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), White);
		break;

	case -2:

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Red);
		printf("���� �ǹ��� �����ϴ�.");
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