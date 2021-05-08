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
	puts("▶ Press Any Key to Start ◀");

	char Dummy = _getch();

	for (int i = 0; i < 5; ++i) {
		
		CurPos(30, 17);

		if (i % 2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		puts("▶ 로딩중... 기다려주세요 ◀ ");

		Sleep(250);
	}


}

void StoryDescriptor(void) {

	system("cls");

	DialogDisplay("SYSTEM : Incoming Message...");
	DialogDisplay("SYSTEM : 긴급 메시지입니다.");
	DialogDisplay("정체불명의 원인 에이전트(Agent)로 인해 달이 7조각으로 쪼개졌다네.");
	DialogDisplay("7조각의 달은 각자의 중력으로 한동안 궤도를 유지하였으나,");
	DialogDisplay("곧 서로 충돌하여 더 작은 조각으로 나뉘어지기 시작했네.");
	DialogDisplay("두브 박사의 시뮬레이션에 의하면 이러한 충돌 현상은 기하급수적으로 가속될 것이며...");
	DialogDisplay("곧 전 지구 궤도가 달의 암석 조각으로 뒤덮이는 화이트 스카이(White Sky) 현상이 발생할 것이라 한다네.");
	DialogDisplay("시뮬레이션 결과에서 더욱 암울한 것은 화이트 스카이 발생 후 몇 년 이내에...");
	DialogDisplay("수 조 개에 달하는 궤도 상의 달 암석 조각들이 지구 중력에 이끌려 동시다발적으로 지구로 쏟아져 내리는...");
	DialogDisplay("하드레인(Hard Rain) 현상이 시작되어 약 5,000년 간 지속된다는 것이네. ");
	DialogDisplay("우리 인류는 종말을 목전에 두고 있네...");
	DialogDisplay("자네는 이러한 절망적인 상황에서 도시를 건설하고 인류의 마지막 희망인 우주선...");
	DialogDisplay("클라우드아크(Cloud Ark)를 건조하여 발사할 때 까지 살아남는 미션을 지휘할 사령관으로 임명되었네.");
	DialogDisplay("인류의 미래가 그대의 어깨에 달려있네...");
	DialogDisplay("사령관...");
	DialogDisplay("건투를 비네.");
	DialogDisplay("SYSTEM : 통신이 종료되었습니다.");
}

void PAC(void) {

	puts("\n");
	puts("▶ Press Any Key ◀");
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

	printf("┏");

	for (short i = 0; toPrint[i]; ++i) printf("━");

	printf("━┓\n┃\n┗");

	for (short i = 0; toPrint[i]; ++i) printf("━");

	printf("━┛");

	CurPos(2, 1);
	TypeAnimation(toPrint);
	printf("┃");

	CurPos(0, 2);

	PAC();
}

void UserInfo(void) {

	Info i;

	system("cls");

	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ 당신의 이름은? (최대 한글 10자, 영문 20자) ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	CurPos(47, 1);

	gets_s(i.UserName, sizeof(i.UserName));

	CurPos(1, 3);

	printf("SYSTEM : %s 사령관님, 입력하신 이름이 맞습니까? (Y/N)", i.UserName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	UserInfo();
}
void CityInfo(void) {

	Info i;

	system("cls");

	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("┃ 방어할 도시의 이름은? (최대 한글 10자, 영문 20자) ┃\n");
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");

	CurPos(54, 1);

	gets_s(i.CityName, sizeof(i.CityName));

	CurPos(1, 3);

	printf("SYSTEM : 사령관님, 입력하신 도시의 이름이 %s 입니까? (Y/N)", i.CityName);

	char UserInput = _getch();

	if (UserInput == 'Y' || UserInput == 'y') return;

	CityInfo();
}

void AvailableBuilding(void) {


}