#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include "MacroSet.h"
#include "StructSet.h"
#include "BaseSystem.h"

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

void StringColor(short color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CharBlink(char toBlink, short show, short color) {

	StringColor(color);
	if (show) putchar(toBlink);
	else putchar(' ');
	StringColor(White);
}

void K_Putchar(char toPrint[], short index) {

	putchar(toPrint[index]);
	if (toPrint[index + 1]) putchar(toPrint[index + 1]);
}

char GetKeyDown(void) {

	if (_kbhit()) return _getch();

	else return False;
}

short ClockGenerator(short MilliSecond) {

	if (MilliSecond == Tic) MilliSecond = 0;
	Sleep(50);
	MilliSecond += 50;

	return MilliSecond;
}

unsigned int _stdcall BeepPlayer(void* arg) {

	Beep((DWORD)Morse, 100);

	_endthreadex(0);

	return 0;
}

void TypeAnimation(char toPrint[]) {

	HANDLE hThread[1];
	DWORD dwThreadID;

	StringColor(Cyan);

	for (short i = 0; toPrint[i]; i += 2) {

		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, BeepPlayer, NULL, 0, (unsigned*)&dwThreadID);

		if (hThread[0]) CloseHandle(hThread[0]);

		if (toPrint[i] != ' ' && toPrint[i] != '.') {

			K_Putchar(toPrint, i);
			Sleep(25);
		}
		else {

			putchar(toPrint[i]);
			--i;
		}

		if (!toPrint[i + 1]) break;
	}

	StringColor(White);
}

char ParityMaker(int toTest) {

	char Result = 0;

	while (toTest > 0) {

		Result += toTest % 10;
		toTest /= 10;
	}

	return (Result % 26) + 'A';
}

void RankingRecorder(City CityStr) {

	FILE* RankingData;

	char FileLocation[] = "c:\\ProgramData\\AKKYU\\EscapeHR\\ranking.aku";
	char FileLineBuffer[50];
	char* FileSliceBuffer;
	char* FileSliceLeft = NULL;
	char NameList[5][11];
	char CityList[5][11];
	char ScoreList[5][16];
	char ScoreBuffer[16];
	char ParityList[5];
	short LinePosition = 0;
	short Separator = 0;

	memset(NameList, 0, sizeof(NameList));
	memset(CityList, 0, sizeof(CityList));
	memset(ScoreList, 0, sizeof(ScoreList));
	memset(ParityList, 0, sizeof(ParityList));

	fopen_s(&RankingData, FileLocation, "r");

	if (RankingData == NULL) {

		fopen_s(&RankingData, FileLocation, "w");

		if (RankingData == NULL) {

			system("cls");

			printf("알 수 없는 오류 발생!\n아무 키나 눌러 게임을 강제 종료합니다...");

			char Dummy = _getch();

			exit(-1);
		}

		fprintf_s(RankingData, "%s:%s:%d:%c\n", CityStr.Usr.UserName, CityStr.Usr.CityName, CityStr.Score, ParityMaker(CityStr.Score));

		fclose(RankingData);

		return;
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

						fopen_s(&RankingData, FileLocation, "w");

						if (RankingData == NULL) {

							system("cls");

							printf("알 수 없는 오류 발생!\n아무 키나 눌러 게임을 강제 종료합니다...");

							char Dummy = _getch();

							exit(-1);
						}

						fprintf_s(RankingData, "%s:%s:%d:%c\n", CityStr.Usr.UserName, CityStr.Usr.CityName, CityStr.Score, ParityMaker(CityStr.Score));

						fclose(RankingData);
					}
					break;
				}

				FileSliceBuffer = strtok_s(NULL, ":", &FileSliceLeft);
				++Separator;
			}

			++LinePosition;
		}

		if (LinePosition > 5) LinePosition = 5;

		fclose(RankingData);

		for (short i = 0; i < LinePosition; ++i) {

			if (atoi(ScoreList[i]) <= CityStr.Score) {

				for (short j = 4; j > i; --j) {

					strcpy_s(NameList[j], sizeof(NameList[j]), NameList[j - 1]);
					strcpy_s(CityList[j], sizeof(CityList[j]), CityList[j - 1]);
					strcpy_s(ScoreList[j], sizeof(ScoreList[j]), ScoreList[j - 1]);
					ParityList[j] = ParityList[j - 1];
				}

				strcpy_s(NameList[i], sizeof(NameList[i]), CityStr.Usr.UserName);
				strcpy_s(CityList[i], sizeof(CityList[i]), CityStr.Usr.CityName);
				sprintf_s(ScoreBuffer, sizeof(ScoreBuffer), "%d", CityStr.Score);
				strcpy_s(ScoreList[i], sizeof(ScoreList[i]), ScoreBuffer);
				ParityList[i] = ParityMaker(CityStr.Score);

				break;
			}
		}

		int RmResult = remove(FileLocation);

		if (RmResult == -1) {

			system("cls");

			printf("알 수 없는 오류 발생!\n아무 키나 눌러 게임을 강제 종료합니다...");

			char Dummy = _getch();

			exit(-1);
		}

		fopen_s(&RankingData, FileLocation, "w");

		if (RankingData == NULL) {

			system("cls");

			printf("알 수 없는 오류 발생!\n아무 키나 눌러 게임을 강제 종료합니다...");

			char Dummy = _getch();

			exit(-1);
		}

		for (short i = 0; i < LinePosition; ++i) {

			fprintf_s(RankingData, "%s:%s:%d:%c\n", NameList[i], CityList[i], atoi(ScoreList[i]), ParityList[i]);
		}

		fclose(RankingData);
	}
}