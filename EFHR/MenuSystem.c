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

	CurPos(40, 17); puts("게임  시작");
	CurPos(40, 18); puts("게임  정보");
	CurPos(42, 19); puts("랭  킹");
	CurPos(42, 20); puts("크레딧");
	CurPos(42, 21); puts("종  료");
}

void GameInfo(void) {

	system("cls");

	CurPos(23, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	CurPos(23, 2); printf("┃             HARD RAIN IMPACT             ┃");
	CurPos(23, 3); printf("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫");
	CurPos(23, 4); printf("┃  때는 21XX년, AGENT라 명명된 정체 불명의 ┃");
	CurPos(23, 5); printf("┃ 현상으로 인해 달이 7조각으로 쪼개졌다... ┃");
	CurPos(23, 6); printf("┃ 이렇게 쪼개진 달은 점점 더 작은 조각으로 ┃");
	CurPos(23, 7); printf("┃ 나뉘어져 결국 산산조각났고, 그 잔해들이  ┃");
	CurPos(23, 8); printf("┃ 지구의 하늘을 뒤덮는 White Sky 현상이 일 ┃");
	CurPos(23, 9); printf("┃ 어날 것으로 예측되었다. 결국 이 조각들이 ┃");
	CurPos(23, 10); printf("┃ 지상으로 떨어지는 Hard Rain 현상이 일어날┃");
	CurPos(23, 11); printf("┃ 것으로 예상된다. 이에 인류는 지구를 포기 ┃");
	CurPos(23, 12); printf("┃ 하고 과학 도시를 건설해 Cloud Ark라는 함 ┃");
	CurPos(23, 13); printf("┃ 선을 건조하여 지구를 탈출할 계획을 세웠다┃");
	CurPos(23, 14); printf("┃ 이 도시를 책임질 사령관으로 선출된 당신은┃");
	CurPos(23, 15); printf("┃ 쏟아지는 Hard Rain 속에서 도시를 지키고  ┃");
	CurPos(23, 16); printf("┃ Cloud Ark 건조까지의 시간을 버틸 수 있을 ┃");
	CurPos(23, 17); printf("┃ 것인가... 전 인류의 운명이 당신에게 있다.┃");
	CurPos(23, 18); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	CurPos(23, 19); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	CurPos(23, 20); printf("┃         아무 키나 눌러서 돌아가기        ┃");
	CurPos(23, 21); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

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

		CurPos(23, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		CurPos(23, 2); printf("┃     아직 저장된 랭킹 기록이 없습니다.    ┃");
		CurPos(23, 3); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
		CurPos(23, 4); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		CurPos(23, 5); printf("┃         아무 키나 눌러서 돌아가기        ┃");
		CurPos(23, 6); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

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

						CurPos(23, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
						CurPos(23, 2); printf("┃       저장 데이터가 손상되었습니다...    ┃");
						CurPos(23, 3); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
						CurPos(23, 4); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
						CurPos(23, 5); printf("┃          아무 키나 눌러서 초기화         ┃");
						CurPos(23, 6); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

						fclose(RankingData);

						char Dummy = getchar();

						int RmResult = remove(FileLocation);

						if (RmResult == -1) {

							system("cls");

							printf("알 수 없는 오류 발생!\n아무 키나 눌러 게임을 강제 종료합니다...");

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

		CurPos(23, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		CurPos(23, 2); printf("┃             상위 5위 Ranking             ┃");
		CurPos(23, 3); printf("┣━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┫");
		CurPos(23, 4); printf("┃ 사령관 이름┃  도시 이름 ┃       점수     ┃");

		for (short i = 0; i < LinePosition; ++i) {
			CurPos(23, 5 + 2 * i); printf("┣━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━┫");
			CurPos(23, 6 + 2 * i); printf("┃  %10s┃  %10s┃ %15s┃", NameList[i], CityList[i], ScoreList[i]);
			LastRanking = 2 * i;
		}

		CurPos(23, 6 + LastRanking + 1); printf("┗━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┛");
		CurPos(23, 6 + LastRanking + 2); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
		CurPos(23, 6 + LastRanking + 3); printf("┃         아무 키나 눌러서 돌아가기        ┃");
		CurPos(23, 6 + LastRanking + 4); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

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