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

			puts("�� Press Any Key to Start ��");

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
		puts("�� Press Any Key ��");

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

	PAC();
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

void GameSetup(void) {

	char UserInput;

	system("cls");

	CurPos(16, 10); puts("����������������������������������������������������������������������������������������������������������������");
	CurPos(16, 11); puts("�� ���� ȭ�� ������ ����Ͻðڽ��ϱ�? (�ſ� ����!) [Y/N]��");
	CurPos(16, 12); puts("����������������������������������������������������������������������������������������������������������������");

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

	puts("����������������������������������������������������������������������");
	puts("�� ���丮�� ��û�Ͻðڽ��ϱ�? [Y/N]��");
	puts("����������������������������������������������������������������������");

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

	printf("������������������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� �̸���? (�ִ� ���� 10��, ���� �Ұ�)��           ��\n");
	printf("������������������������������������������������������������������������������������������������������������������\n");

	CurPos(46, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("���� ���� �� : %-24d", 56 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

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

	printf("��������������������������������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� ������ �̸���? (�ִ� ���� 10��, ���� �Ұ�)��           ��\n");
	printf("��������������������������������������������������������������������������������������������������������������������������������\n");

	CurPos(53, 1);

	while (True) {

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

		CursorView(0);
		CurPos(1, 3);
		printf("���� ���� �� : %-29d", 63 - curInfo.dwCursorPosition.X);

		CurPos(curInfo.dwCursorPosition.X, 1);
		CursorView(True);

		CharBuffer = _getche();
		if (CharBuffer > 32) StringBuffer[Index] = CharBuffer;
		++Index;

		if (curInfo.dwCursorPosition.X == 62 || CharBuffer == 13) {

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

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? [Y/N]", CityName);

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
		printf("�� �� ��");
	}
	else {

		StringColor(Red);
		printf("�� �� ��");
	}

	StringColor(White);

	CurPos(19, 3);

	printf("%-16d", City.Res.TechnologyState);

	CurPos(37, 3);

	if (City.OccupyState[City.UserPosition] == Factory) {

		StringColor(Green);
		printf("�� �� ��");
	}
	else {

		StringColor(Red);
		printf("�� �� ��");
	}

	StringColor(White);

	CurPos(19, 5);

	printf("%-16d", City.Res.CapitalState);

	CurPos(37, 5);

	if (City.OccupyState[City.UserPosition] == Residence) {

		StringColor(Green);
		printf("�� �� ��");
	}
	else {

		StringColor(Red);
		printf("�� �� ��"); CurPos(19, 3);
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

		CurPos(1, 0); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 1); printf("�� "); StringColor(Yellow);
		printf("������"); StringColor(White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : e��");
		CurPos(1, 2); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 3); printf("�� "); StringColor(Red);
		printf("��  ��"); StringColor(White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : t��");
		CurPos(1, 4); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 5); printf("�� "); StringColor(Green);
		printf("�ְ���"); StringColor(White);
		printf("�� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : m��");
		CurPos(1, 6); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 7); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 8); printf("�� SYSTEM :                                  ��");
		CurPos(1, 9); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 10); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 11); printf("��                                           ��");
		CurPos(1, 12); printf("��         <���� ��ɰ��� ���� �޸�>         ��");
		CurPos(1, 13); printf("��                                           ��");
		CurPos(1, 14); printf("��           ������ ȯ���ϳ� ��ɰ�          ��");
		CurPos(1, 15); printf("��  �� �޴��� �����Ͽ� ���� �Ǽ��� �����ϰ�  ��");
		CurPos(1, 16); printf("��     �� �ǹ��� ������ �ڿ��� �����Ѵٳ�    ��");
		CurPos(1, 17); printf("��        ���� ���� �ܰ迡���� �� ����       ��");
		CurPos(1, 18); printf("��      �� ������ �ڿ��� ������ �����ϳ�     ��");
		CurPos(1, 19); printf("��      �׷��� �����ϰ� �Ǽ��� �����ϰ�      ��");
		CurPos(1, 20); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 21); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 22); printf("�� ��  ���� ���� : a ������ : d�� ���� ���� : x��");
		CurPos(1, 23); printf("������������������������������������������������������������������������������������������");

		BuildingHeight();

		CurPos(50, 0); printf("������������������������������");
		for (short i = 1; i < 21; ++i) {
			CurPos(50, i);
			printf("��             ��");
		}
		CurPos(50, 21); printf("������������������������������");
		CurPos(50, 22); printf("��             ��");
		CurPos(50, 23); printf("������������������������������");

		UserPrint(0);

		CurPos(0, 23);
	}
	else if (GamePhase == ProductionPhase) {

		CurPos(1, 0); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 1); printf("�� "); StringColor(Yellow);
		printf("������"); StringColor(White);
		printf("�� "); StringColor(D_Yellow);
		printf("������"); StringColor(White);
		printf("�� EEEEEEEEEEEEEE16�� �� �� �Ӧ�");
		CurPos(1, 2); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 3); printf("�� "); StringColor(Red);
		printf("��  ��"); StringColor(White);
		printf("�� "); StringColor(D_Red);
		printf("��  ��"); StringColor(White);
		printf("�� EEEEEEEEEEEEEE16�� �� �� �Ӧ�");
		CurPos(1, 4); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 5); printf("�� "); StringColor(Green);
		printf("�ְ���"); StringColor(White);
		printf("�� "); StringColor(D_Green);
		printf("��  ��"); StringColor(White);
		printf("�� EEEEEEEEEEEEEE16�� �� �� �Ӧ�");
		CurPos(1, 6); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 10); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 11); printf("��                                           ��");
		CurPos(1, 12); printf("��         <���� ��ɰ��� ���� �޸�>         ��");
		CurPos(1, 13); printf("��                                           ��");
		CurPos(1, 14); printf("��    ��� �Ǽ��� �Ϸ�ƴٴ� �ҽ��� �����   ��");
		CurPos(1, 15); printf("��           �ڳװ� �¿�� �����̸�          ��");
		CurPos(1, 16); printf("��          ������ ������ �ǹ��κ���         ��");
		CurPos(1, 17); printf("��        ������ �ڿ��� ȹ���� �� �ֳ�       ��");
		CurPos(1, 18); printf("��     �ʿ��� �ڿ��� ȿ�������� ��ƺ���     ��");
		CurPos(1, 19); printf("��        �ϵ巹���� �� ���� �ʾҳ�...     ��");
		CurPos(1, 20); printf("������������������������������������������������������������������������������������������");

		CurPos(0, 23);
	}
	else if (GamePhase == HardrainPhase) {

		CurPos(1, 10); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 11); printf("�� ");
		StringColor(Cyan); printf("LASER"); StringColor(White);
		printf("�� ");
		StringColor(D_Yellow); printf("10 ������"); StringColor(White);
		printf("�� �� �� ���ݦ� �߻禭  Space��");
		CurPos(1, 12); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 13); printf("�� ");
		StringColor(Yellow); printf("PULSE"); StringColor(White);
		printf("�� ");
		StringColor(D_Green); printf("35 ��  ��"); StringColor(White);
		printf("�� ����� 3���� �߻禭    p  ��");
		CurPos(1, 14); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 15); printf("�� �� ���� 15 ��  ���� �� �� ������ ������    f  ��");
		CurPos(1, 16); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 17); printf("�� �� �æ� 0000000000   �� ��ɰ��� 0000000000  ��");
		CurPos(1, 18); printf("������������������������������������������������������������������������������������������");
		CurPos(1, 19); printf("�� �� ����                                    ��");
		CurPos(1, 20); printf("������������������������������������������������������������������������������������������");
	}
}

void SystemMessage(short MessageType) {

	CurPos(12, 8);

	for (short i = 0; i < 33; ++i) putchar(' ');

	CurPos(12, 8);

	switch (MessageType) {

	case BuildingPhase:

		printf("�ǹ� �Ǽ��� �������ּ���.");
		break;

	case EnterProductionPhase:

		for (int i = 0; i < 4; ++i) {

			CurPos(12, 8);

			for (short i = 0; i < 33; ++i) putchar(' ');

			CurPos(12, 8);

			StringColor(Cyan);

			if (i % 2) printf("���� �ܰ迡 �����մϴ�.");
			else printf("Please Wait...");

			Sleep(500);
		}

		StringColor(White);
		break;

	case ProductionPhase:

		printf("�ڿ� ������ �������ּ���.");
		break;

	case AlreadyOccupied:

		StringColor(Red);
		printf("�̹� �ǹ��� ������ �����Դϴ�.");
		StringColor(White);
		break;

	case NotingLeft:

		StringColor(Red);
		printf("���� �ǹ��� �����ϴ�.");
		StringColor(White);
		break;

	case Confirm:

		StringColor(Green);
		printf("�Ǽ��Ͻ÷��� �� �� �� �����ּ���.");
		StringColor(White);
		break;

	case Canceled:

		StringColor(Red);
		printf("��ҵǾ����ϴ�.");
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
		printf("HardRain ���� %2d�� ���ҽ��ϴ�.", Timer / 2);
	else
		printf("Hard Rain Impact");

	StringColor(White);

	CurPos(0, 23);
}