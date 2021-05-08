#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

void SplashScreen(void);
void StoryDescriptor(void);

void PAC(void);
void CurPos(short x, short y);
void K_Putchar(char toPrint[], short index);

void TypeAnimation(char toPrint[]);
void DialogDisplay(char toPrint[]);

void UserInfo(void);
void CityInfo(void);

void AvailableBuilding(void);

typedef struct {

	char UserName[21];
	char CityName[21];
}Info;

int main(void) {

	SplashScreen();
	
	StoryDescriptor();

	UserInfo();
	CityInfo();


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

	Info i;

	system("cls");

	printf("��������������������������������������������������������������������������������������������\n");
	printf("�� ����� �̸���? (�ִ� �ѱ� 10��, ���� 20��) ��\n");
	printf("��������������������������������������������������������������������������������������������\n");

	CurPos(47, 1);

	gets_s(i.UserName, sizeof(i.UserName));

	CurPos(1, 3);

	printf("SYSTEM : %s ��ɰ���, �Է��Ͻ� �̸��� �½��ϱ�? (Y/N)", i.UserName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo();
}
void CityInfo(void) {

	Info i;

	system("cls");

	printf("����������������������������������������������������������������������������������������������������������\n");
	printf("�� ����� ������ �̸���? (�ִ� �ѱ� 10��, ���� 20��) ��\n");
	printf("����������������������������������������������������������������������������������������������������������\n");

	CurPos(54, 1);

	gets_s(i.CityName, sizeof(i.CityName));

	CurPos(1, 3);

	printf("SYSTEM : ��ɰ���, �Է��Ͻ� ������ �̸��� %s �Դϱ�? (Y/N)", i.CityName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void AvailableBuilding(void) {


}