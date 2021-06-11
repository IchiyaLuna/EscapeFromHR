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

	CurPos(40, 17); puts("啪歜  衛濛");
	CurPos(40, 18); puts("啪歜  薑爾");
	CurPos(42, 19); puts("楨  韁");
	CurPos(42, 20); puts("觼溯覃");
	CurPos(42, 21); puts("謙  猿");
}

void GameInfo(void) {

	system("cls");

	CurPos(23, 1); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	CurPos(23, 2); printf("早             HARD RAIN IMPACT             早");
	CurPos(23, 3); printf("曳收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收朽");
	CurPos(23, 4); printf("早  陽朝 21XX喇, AGENT塭 貲貲脹 薑羹 碳貲曖 早");
	CurPos(23, 5); printf("早 ⑷鼻戲煎 檣п 殖檜 7褻陝戲煎 薺偃螺棻... 早");
	CurPos(23, 6); printf("早 檜溢啪 薺偃霞 殖擎 薄薄 渦 濛擎 褻陝戲煎 早");
	CurPos(23, 7); printf("早 釭斯橫螳 唸措 骯骯褻陝陬堅, 斜 濤п菟檜  早");
	CurPos(23, 8); printf("早 雖掘曖 ж棺擊 菴竣朝 White Sky ⑷鼻檜 橾 早");
	CurPos(23, 9); printf("早 橫陳 匙戲煎 蕨難腎歷棻. 唸措 檜 褻陝菟檜 早");
	CurPos(23, 10); printf("早 雖鼻戲煎 雲橫雖朝 Hard Rain ⑷鼻檜 橾橫陳早");
	CurPos(23, 11); printf("早 匙戲煎 蕨鼻脹棻. 檜縑 檣盟朝 雖掘蒂 ん晦 早");
	CurPos(23, 12); printf("早 ж堅 婁з 紫衛蒂 勒撲п Cloud Ark塭朝 л 早");
	CurPos(23, 13); printf("早 摹擊 勒褻ж罹 雖掘蒂 驍轎й 啗�嘛� 撮錫棻早");
	CurPos(23, 14); printf("早 檜 紫衛蒂 疇歜韓 餌滄婦戲煎 摹轎脹 渡褐擎早");
	CurPos(23, 15); printf("早 踏嬴雖朝 Hard Rain 樓縑憮 紫衛蒂 雖酈堅  早");
	CurPos(23, 16); printf("早 Cloud Ark 勒褻梱雖曖 衛除擊 幗せ 熱 氈擊 早");
	CurPos(23, 17); printf("早 匙檣陛... 瞪 檣盟曖 遴貲檜 渡褐縑啪 氈棻.早");
	CurPos(23, 18); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
	CurPos(23, 19); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	CurPos(23, 20); printf("早         嬴鼠 酈釭 揚楝憮 給嬴陛晦        早");
	CurPos(23, 21); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	char Dummy = getchar();

	system("cls");

	return;
}

void Ranking(void) {

	FILE* RankingData;
	char FileLineBuffer[50];
	char NameList[5][11];
	char CityList[5][11];
	char ScoreList[5][16];
	short LinePosition = 0;
	short LastRanking = 0;
	short Separator = 0;
	short SepPosition;
	
	memset(NameList, 0, sizeof(NameList));
	memset(CityList, 0, sizeof(CityList));
	memset(ScoreList, 0, sizeof(ScoreList));

	fopen_s(&RankingData, "c:\\ProgramData\\AKKYU\\EscapeHR\\ranking.aku", "r");

	system("cls");

	if (RankingData == NULL) {

		CurPos(23, 1); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(23, 2); printf("早     嬴霜 盪濰脹 楨韁 晦煙檜 橈蝗棲棻.    早");
		CurPos(23, 3); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
		CurPos(23, 4); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(23, 5); printf("早         嬴鼠 酈釭 揚楝憮 給嬴陛晦        早");
		CurPos(23, 6); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

		char Dummy = getchar();
	}
	else {

		while (!feof(RankingData)) {

			memset(FileLineBuffer, 0, sizeof(FileLineBuffer));

			fgets(FileLineBuffer, sizeof(FileLineBuffer), RankingData);

			if (!FileLineBuffer[0])break;

			if (FileLineBuffer[strlen(FileLineBuffer) - 2] != 'a') {

				CurPos(23, 1); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
				CurPos(23, 2); printf("早       盪濰 等檜攪陛 槳鼻腎歷蝗棲棻...    早");
				CurPos(23, 3); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
				CurPos(23, 4); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
				CurPos(23, 5); printf("早         嬴鼠 酈釭 揚楝憮 給嬴陛晦        早");
				CurPos(23, 6); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

				fclose(RankingData);

				char Dummy = getchar();

				return;
			}
			else {

				for (short i = 0; FileLineBuffer[i] != '\n'; ++i) {

					if (isspace(FileLineBuffer[i])) {

						SepPosition = i + 1;
						++Separator;
						continue;
					}

					if (Separator == 2 && FileLineBuffer[i] == 'a') break;

					if (Separator == 0) NameList[LinePosition][i] = FileLineBuffer[i];
					else if (Separator == 1 && i >= SepPosition) CityList[LinePosition][i - SepPosition] = FileLineBuffer[i];
					else if (Separator == 2 && i >= SepPosition) ScoreList[LinePosition][i - SepPosition] = FileLineBuffer[i];
				}

				SepPosition = 0;
				Separator = 0;
				++LinePosition;
			}
		}

		CurPos(23, 1); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(23, 2); printf("早             鼻嬪 5嬪 Ranking             早");
		CurPos(23, 3); printf("曳收收收收收收收收收收收收有收收收收收收收收收收收收有收收收收收收收收收收收收收收收收朽");
		CurPos(23, 4); printf("早 餌滄婦 檜葷早  紫衛 檜葷 早       薄熱     早");

		for (short i = 0; i < LinePosition; ++i) {
			CurPos(23, 5 + 2 * i); printf("曳收收收收收收收收收收收收朱收收收收收收收收收收收收朱收收收收收收收收收收收收收收收收朽");
			CurPos(23, 6 + 2 * i); printf("早  %10s早  %10s早 %15s早", NameList[i], CityList[i], ScoreList[i]);
			LastRanking = 2 * i;
		}

		CurPos(23, 6 + LastRanking + 1); printf("曲收收收收收收收收收收收收朴收收收收收收收收收收收收朴收收收收收收收收收收收收收收收收旭");
		CurPos(23, 6 + LastRanking + 2); printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
		CurPos(23, 6 + LastRanking + 3); printf("早         嬴鼠 酈釭 揚楝憮 給嬴陛晦        早");
		CurPos(23, 6 + LastRanking + 4); printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

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