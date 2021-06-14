#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <memory.h>
#include <Windows.h>
#include "BaseSystem.h"
#include "MenuSystem.h"

void MainMenu(short CursorPosition) {

	for (short i = 0; i < 5; ++i) {

		CurPos(38, 17 + i);
		putchar(' ');
	}

	CurPos(38, 17 + CursorPosition); putchar('>');

	CurPos(40, 17); puts("����  ����");
	CurPos(40, 18); puts("����  ����");
	CurPos(42, 19); puts("��  ŷ");
	CurPos(42, 20); puts("ũ����");
	CurPos(42, 21); puts("��  ��");
}

void GameInfo(void) {

	system("cls");

	CurPos(23, 1); printf("����������������������������������������������������������������������������������������");
	CurPos(23, 2); printf("��             HARD RAIN IMPACT             ��");
	CurPos(23, 3); printf("����������������������������������������������������������������������������������������");
	CurPos(23, 4); printf("��  ���� 21XX��, AGENT�� ���� ��ü �Ҹ��� ��");
	CurPos(23, 5); printf("�� �������� ���� ���� 7�������� �ɰ�����... ��");
	CurPos(23, 6); printf("�� �̷��� �ɰ��� ���� ���� �� ���� �������� ��");
	CurPos(23, 7); printf("�� �������� �ᱹ �����������, �� ���ص���  ��");
	CurPos(23, 8); printf("�� ������ �ϴ��� �ڵ��� White Sky ������ �� ��");
	CurPos(23, 9); printf("�� � ������ �����Ǿ���. �ᱹ �� �������� ��");
	CurPos(23, 10); printf("�� �������� �������� Hard Rain ������ �Ͼ��");
	CurPos(23, 11); printf("�� ������ ����ȴ�. �̿� �η��� ������ ���� ��");
	CurPos(23, 12); printf("�� �ϰ� ���� ���ø� �Ǽ��� Cloud Ark��� �� ��");
	CurPos(23, 13); printf("�� ���� �����Ͽ� ������ Ż���� ��ȹ�� �����٦�");
	CurPos(23, 14); printf("�� �� ���ø� å���� ��ɰ����� ����� �������");
	CurPos(23, 15); printf("�� ������� Hard Rain �ӿ��� ���ø� ��Ű��  ��");
	CurPos(23, 16); printf("�� Cloud Ark ���������� �ð��� ��ƿ �� ���� ��");
	CurPos(23, 17); printf("�� ���ΰ�... �� �η��� ����� ��ſ��� �ִ�.��");
	CurPos(23, 18); printf("����������������������������������������������������������������������������������������");
	CurPos(23, 19); printf("����������������������������������������������������������������������������������������");
	CurPos(23, 20); printf("��         �ƹ� Ű�� ������ ���ư���        ��");
	CurPos(23, 21); printf("����������������������������������������������������������������������������������������");

	char Dummy = getchar();

	system("cls");

	return;
}

void Ranking(void) {

	FILE* RankingData;

	char FileLocation[] = "c:\\ProgramData\\AKKYU\\EscapeHR\\ranking.aku";
	char FileLineBuffer[50];
	char* FileSliceBuffer;
	char* FileSliceLeft = NULL;
	char NameList[5][11];
	char CityList[5][11];
	char ScoreList[5][16];
	char ParityList[5];
	short LinePosition = 0;
	short LastRanking = 0;
	short Separator = 0;
	
	memset(NameList, 0, sizeof(NameList));
	memset(CityList, 0, sizeof(CityList));
	memset(ScoreList, 0, sizeof(ScoreList));
	memset(ParityList, 0, sizeof(ParityList));

	fopen_s(&RankingData, FileLocation, "r");

	system("cls");

	if (RankingData == NULL) {

		CurPos(23, 1); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 2); printf("��     ���� ����� ��ŷ ����� �����ϴ�.    ��");
		CurPos(23, 3); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 4); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 5); printf("��         �ƹ� Ű�� ������ ���ư���        ��");
		CurPos(23, 6); printf("����������������������������������������������������������������������������������������");

		char Dummy = getchar();
	}
	else {

		while (!feof(RankingData)) {

			Separator = 0;

			memset(FileLineBuffer, 0, sizeof(FileLineBuffer));

			fgets(FileLineBuffer, sizeof(FileLineBuffer), RankingData);

			FileSliceBuffer = strtok_s(FileLineBuffer, ":", &FileSliceLeft);

			while (FileSliceBuffer) {

				switch (Separator) {

				case 0:

					strcpy_s(NameList[LinePosition], sizeof(NameList[LinePosition]), FileSliceBuffer);
					break;

				case 1:

					strcpy_s(CityList[LinePosition], sizeof(CityList[LinePosition]), FileSliceBuffer);
					break;

				case 2:

					strcpy_s(ScoreList[LinePosition], sizeof(CityList[LinePosition]), FileSliceBuffer);
					break;

				case 3:

					ParityList[LinePosition] = *FileSliceBuffer;

					if (ParityMaker(atoi(ScoreList[LinePosition])) != ParityList[LinePosition]) {

						system("cls");

						CurPos(23, 1); printf("����������������������������������������������������������������������������������������");
						CurPos(23, 2); printf("��       ���� �����Ͱ� �ջ�Ǿ����ϴ�...    ��");
						CurPos(23, 3); printf("����������������������������������������������������������������������������������������");
						CurPos(23, 4); printf("����������������������������������������������������������������������������������������");
						CurPos(23, 5); printf("��          �ƹ� Ű�� ������ �ʱ�ȭ         ��");
						CurPos(23, 6); printf("����������������������������������������������������������������������������������������");

						fclose(RankingData);

						char Dummy = getchar();

						int RmResult = remove(FileLocation);

						if (RmResult == -1) {

							system("cls");

							printf("�� �� ���� ���� �߻�!\n�ƹ� Ű�� ���� ������ ���� �����մϴ�...");

							char Dummy = _getch();

							exit(-1);
						}

						return;
					}

					break;
				}

				FileSliceBuffer = strtok_s(NULL, ":", &FileSliceLeft);
				++Separator;
			}

			++LinePosition;
		}

		--LinePosition;

		CurPos(23, 1); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 2); printf("��             ���� 5�� Ranking             ��");
		CurPos(23, 3); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 4); printf("�� ��ɰ� �̸���  ���� �̸� ��       ����     ��");

		for (short i = 0; i < LinePosition; ++i) {
			CurPos(23, 5 + 2 * i); printf("����������������������������������������������������������������������������������������");
			CurPos(23, 6 + 2 * i); printf("��  %10s��  %10s�� %15s��", NameList[i], CityList[i], ScoreList[i]);
			LastRanking = 2 * i;
		}

		CurPos(23, 6 + LastRanking + 1); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 6 + LastRanking + 2); printf("����������������������������������������������������������������������������������������");
		CurPos(23, 6 + LastRanking + 3); printf("��         �ƹ� Ű�� ������ ���ư���        ��");
		CurPos(23, 6 + LastRanking + 4); printf("����������������������������������������������������������������������������������������");

		fclose(RankingData);

		char Dummy = getchar();
	}
	system("cls");

	return;
}

void Credit(void) {

	system("cls");

	for (short i = 0; i < 42; ++i) {

		if (_kbhit()) if (_getch() != 13)break;

		system("cls");

		if (23 - i < 24 && 23 - i >= 0) {
			CurPos(35, 23 - i); puts("[HARD RAIN IMPACT]");
		}
		if (24 - i < 24 && 24 - i >= 0) {
			CurPos(0, 24 - i); puts("");
		}
		if (25 - i < 24 && 25 - i >= 0) {
			CurPos(28, 25 - i); puts("Proudly Present This Game To You");
		}
		if (26 - i < 24 && 26 - i >= 0) {
			CurPos(0, 26 - i); puts("");
		}
		if (27 - i < 24 && 27 - i >= 0) {
			CurPos(42, 27 - i); puts("B Y");
		}
		if (28 - i < 24 && 28 - i >= 0) {
			CurPos(0, 28 - i); puts("");
		}
		if (29 - i < 24 && 29 - i >= 0) {
			CurPos(38, 29 - i); puts("Sungha Choi");
		}
		if (30 - i < 24 && 30 - i >= 0) {
			CurPos(0, 30 - i); puts("");
		}
		if (31 - i < 24 && 31 - i >= 0) {
			CurPos(41, 31 - i); puts("<DEV>");
		}
		if (32 - i < 24 && 32 - i >= 0) {
			CurPos(0, 32 - i); puts("");
		}
		if (33 - i < 24 && 33 - i >= 0) {
			CurPos(38, 33 - i); puts("Sungha Choi");
		}
		if (34 - i < 24 && 34 - i >= 0) {
			CurPos(0, 34 - i); puts("");
		}
		if (35 - i < 24 && 35 - i >= 0) {
			CurPos(41, 35 - i); puts("<OST>");
		}
		if (36 - i < 24 && 36 - i >= 0) {
			CurPos(0, 36 - i); puts("");
		}
		if (37 - i < 24 && 37 - i >= 0) {
			CurPos(24, 37 - i); puts("Megadeth - Dystopia (8-Bit Edit by WERC85)");
		}
		if (38 - i < 24 && 38 - i >= 0) {
			CurPos(0, 38 - i); puts("");
		}
		if (39 - i < 24 && 39 - i >= 0) {
			CurPos(37, 39 - i); puts("<Main  Story>");
		}
		if (40 - i < 24 && 40 - i >= 0) {
			CurPos(0, 40 - i); puts("");
		}
		if (41 - i < 24 && 41 - i >= 0) {
			CurPos(34, 41 - i); puts("Prof. Hyo Sang Lim");
		}

		Sleep(300);
	}

	system("cls");

	return;
}