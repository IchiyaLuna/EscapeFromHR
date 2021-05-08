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
void K_Putchar(char toPrint[], short index);

void TypeAnimation(char toPrint[]);
void DialogDisplay(char toPrint[]);

void UserInfo(void);
void CityInfo(void);

void GameInitialize(void);
void BuildingHeight(void);
void AvailableBuilding(int AvailPower, int AvailFactory, int AvailResidence);

void UserPrint(short UserPosition);

typedef struct {

	char UserName[21];
	char CityName[21];
}User;

typedef struct {

	int PowerLeft;
	int FactoryLeft;
	int ResidenceLeft;
}Buildings;

int main(void) {

	Buildings B = { .PowerLeft = 4,.FactoryLeft = 4,.ResidenceLeft = 4 };

	short UserPosition;

	SplashScreen();
	
	StoryDescriptor();

	UserInfo();
	CityInfo();

	GameInitialize();

	AvailableBuilding(B.PowerLeft, B.FactoryLeft, B.ResidenceLeft);


	return 0;
}

void SplashScreen(void) {

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

	CurPos(30, 17);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	puts("�� Press Any Key to Start ��");

	char Dummy = _getch();

	for (int i = 0; i < 5; ++i) {
		
		CurPos(30, 17);

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		puts("�� �ε���... ��ٷ��ּ��� �� ");

		Sleep(250);
	}


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

	puts("\n");
	puts("�� Press Any Key ��");
	char Dummy = _getch();
}

void CurPos(short x, short y) {

	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
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

	User U;

	system("cls");

	printf("��������������������������������������������������������������������������������������������\n");
	printf("�� ����� �̸���? (�ִ� �ѱ� 10��, ���� 20��) ��\n");
	printf("��������������������������������������������������������������������������������������������\n");

	CurPos(47, 1);

	gets_s(U.UserName, sizeof(U.UserName));

	CurPos(1, 3);

	printf("SYSTEM : %s ��ɰ���, �Է��Ͻ� �̸��� �½��ϱ�? (Y/N)", U.UserName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo();
}
void CityInfo(void) {

	User U;

	system("cls");

	printf("����������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� ������ �̸���? (�ִ� �ѱ� 10��, ���� 20��) ��\n");
	printf("����������������������������������������������������������������������������������������������������������\n");

	CurPos(54, 1);

	gets_s(U.CityName, sizeof(U.CityName));

	CurPos(1, 3);

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? (Y/N)", U.CityName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void GameInitialize(void) {

	system("cls");

	CurPos(1, 0);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 1);
	printf("�� �����Ҧ� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : e��"); CurPos(1, 2);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 3);
	printf("�� ��  �妭 ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : t��"); CurPos(1, 4);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 5);
	printf("�� �ְ����� ���� 0�� �Ǽ� ���� �� : 0�� �Ǽ� : m��"); CurPos(1, 6);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 7);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 8);
	printf("��                                           ��"); CurPos(1, 9);
	printf("��                                           ��"); CurPos(1, 10);
	printf("��                                           ��"); CurPos(1, 11);
	printf("��                                           ��"); CurPos(1, 12);
	printf("��           ���� ���� ����            ��"); CurPos(1, 13);
	printf("��                                           ��"); CurPos(1, 14);
	printf("��                                           ��"); CurPos(1, 15);
	printf("��                                           ��"); CurPos(1, 16);
	printf("��                                           ��"); CurPos(1, 17);
	printf("��                                           ��"); CurPos(1, 18);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 19);
	printf("������������������������������������������������������������������������������������������"); CurPos(1, 20);
	printf("�� ��  ���� ���� : a ������ : d�� ���� ���� : x��"); CurPos(1, 21);
	printf("������������������������������������������������������������������������������������������"); CurPos(50, 0);

	printf("������������������������������"); CurPos(50, 1);
	for (short i = 2; i < 22; ++i) {
		printf("�� aaaaaaaaaaaa��"); CurPos(50, i);
	}
	printf("������������������������������");

	BuildingHeight();
}

void BuildingHeight(void) {

	CurPos(16, 1);
	printf("%d", PowerHeight); CurPos(16, 3);
	printf("%d", FactoryHeight); CurPos(16, 5);
	printf("%d", ResidenceHeight);
}

void AvailableBuilding(int AvailPower, int AvailFactory, int AvailResidence) {

	CurPos(34, 1);
	printf("%d", AvailPower); CurPos(34, 3);
	printf("%d", AvailFactory); CurPos(34, 5);
	printf("%d", AvailResidence); CurPos(0, 23);
}