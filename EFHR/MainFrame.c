#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#define PowerHeight 3
#define FactoryHeight 3
#define ResidenceHeight 3

void SplashScreen(void);
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

struct User{

	char UserName[11];
	char CityName[11];
}U;

typedef struct {

	int PowerLeft;
	int FactoryLeft;
	int ResidenceLeft;
}Buildings;

int main(void) {

	Buildings B = { .PowerLeft = 4,.FactoryLeft = 4,.ResidenceLeft = 4 };

	short OccupyState[12] = { 0 };
	
	short GameState = 0;
	short UserPosition = 0;
	short IsBuildingError = 0;
	char UserInput;

	SplashScreen();
	
	//StoryDescriptor();

	//UserInfo();
	CityInfo();

	GameInitialize();

	AvailableBuilding(B.PowerLeft, B.FactoryLeft, B.ResidenceLeft);
	SystemMessage(GameState);

	while (1) {

		IsBuildingError = 0;

		UserPrint(UserPosition);

		UserInput = _getch();

		if (UserInput == 'x')return 0;

		if (UserInput == 'a') --UserPosition;
		if (UserInput == 'd') ++UserPosition;

		if (!GameState && UserInput == 'e') {

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
		if (!GameState && UserInput == 't') {

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
		if (!GameState && UserInput == 'm') {

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

		if (UserPosition < 0)UserPosition = 0;
		if (UserPosition > 11)UserPosition = 11;
	}
	return 0;
}

void SplashScreen(void) {

	CursorView(0);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

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

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

		CurPos(30, 17);
		puts("�� Press Any Key to Start ��");

		if (_kbhit())break;

		Sleep(500);
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void StoryDescriptor(void) {

	char Dummy = _getch();

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

	puts("\n");
	puts("�� Press Any Key ��");

	char Dummy = _getch();
}

void CurPos(short x, short y) {

	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void CursorView(short show){
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void DialogDisplay(char toPrint[]) {

	system("cls");

	printf("��");

	for (short i = 0; toPrint[i]; ++i) printf("��");

	printf("����\n��\n��");

	for (short i = 0; toPrint[i]; ++i) printf("��");

	printf("����");

	CurPos(2, 1);
	TypeAnimation(toPrint);
	printf("��");

	CurPos(0, 2);

	PAC();
}

void UserInfo(void) {

	system("cls");

	CursorView(1);

	printf("������������������������������������������������������������������������������������������\n");
	printf("�� ����� �̸���? (�ִ� �ѱ� 5��, ���� 10��) ��\n");
	printf("������������������������������������������������������������������������������������������\n");

	CurPos(46, 1);

	gets_s(U.UserName, sizeof(U.UserName));

	CurPos(1, 3);

	printf("SYSTEM : %s ��ɰ���, �Է��Ͻ� �̸��� �½��ϱ�? (Y/N)", U.UserName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo();
}
void CityInfo(void) {

	system("cls");

	CursorView(1);

	printf("��������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� ������ �̸���? (�ִ� �ѱ� 5��, ���� 10��) ��\n");
	printf("��������������������������������������������������������������������������������������������������������\n");

	CurPos(53, 1);

	gets_s(U.CityName, sizeof(U.CityName));

	CurPos(1, 3);

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? (Y/N)", U.CityName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void GameInitialize(void) {

	system("cls");

	CursorView(0);

	CurPos(1, 0);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 1);
	printf("�� �����Ҧ� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : e��"); CurPos(1, 2);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 3);
	printf("�� ��  �妭 ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : t��"); CurPos(1, 4);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 5);
	printf("�� �ְ����� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : m��"); CurPos(1, 6);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 7);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 8);
	printf("�� SYSTEM :                                  ��"); CurPos(1, 9);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 10);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 11);
	printf("��                                           ��"); CurPos(1, 12);
	printf("��           ���� ���� ����            ��"); CurPos(1, 13);
	printf("��                                           ��"); CurPos(1, 14);
	printf("��                                           ��"); CurPos(1, 15);
	printf("��                                           ��"); CurPos(1, 16);
	printf("��                                           ��"); CurPos(1, 17);
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

	if (!AvailPower) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("%d", AvailPower); CurPos(34, 3);
	if (!AvailPower) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (!AvailFactory) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("%d", AvailFactory); CurPos(34, 5);
	if (!AvailFactory) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	if (!AvailResidence) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("%d", AvailResidence);
	if (!AvailResidence) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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

		printf("�̹� �ǹ��� ������ �����Դϴ�.");
		break;

	case -2:

		printf("���� �ǹ��� �����ϴ�.");
		break;

	default:

		printf("Error, Someting Went Wrong");
		break;
	}
}

void UserPrint(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

	for (short i = 0; i < 12; ++i) {
		
		CurPos(52 + i, 22);

		if (i == UserPosition) putchar('*');
		else putchar(' ');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CurPos(0, 23);
}

void MakePower(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

	for (short i = 20; i > 20 - PowerHeight; --i) {
	
		CurPos(52 + UserPosition, i);
		putchar('e');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CurPos(0, 23);
}

void MakeFactory(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	for (short i = 20; i > 20 - FactoryHeight; --i) {

		CurPos(52 + UserPosition, i);
		putchar('t');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CurPos(0, 23);
}

void MakeResidence(short UserPosition) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

	for (short i = 20; i > 20 - ResidenceHeight; --i) {

		CurPos(52 + UserPosition, i);
		putchar('m');
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	CurPos(0, 23);
}