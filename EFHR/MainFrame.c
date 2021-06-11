/*
2021 Yonsei Computer Programming Project (prof. Hyo Sang Lim)
[Game - Hard Rain Impact]

All code written by Sungha Choi

All rights reserved...
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "MacroSet.h"
#include "StructSet.h"
#include "BaseSystem.h"
#include "MenuSystem.h"
#include "DisplaySystem.h"
#include "BuildingSystem.h"
#include "WeaponSystem.h"

//void RankingRecorder(City* CityPtr); 구현 보류

int main(void) {

	City CityStr = { .UserPosition = 0,
		.Buil.PowerLeft = 4, .Buil.FactoryLeft = 4, .Buil.ResidenceLeft = 4,
		.OccupyState = { Blank }, .Health = { Blank }, .BuildingLeft = 0,
		.Res.EnergyState = 0, .Res.TechnologyState = 0, .Res.CapitalState = 0,
		.Score = 0 };

	City* CityPtr = &CityStr;

	Rain RainStr = { .IsStarExist = { Blank }, .StarHeight = { Blank } };

	Rain* RainPtr = &RainStr;

	short GameState = BuildingPhase;
	short MilliSecond = 0;
	short RainCounter = 0;
	short IsBuildingError;
	char UserInput;

	srand((unsigned int)time(NULL));

	system("title Hard Rain Impact v1.2");

	PlaySound(TEXT("Title.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);

	SplashScreen();

	GameSetup();

	UserInfo(CityStr.Usr.UserName);
	CityInfo(CityStr.Usr.CityName);

	GameInitialize(GameState);
	AvailableBuilding(CityStr.Buil);

	SystemMessage(BuildingPhase);

	while (True) {

		UserInput = GetKeyDown();

		if (UserInput == 'x') break;

		else if (UserInput == 'a') --CityStr.UserPosition;
		else if (UserInput == 'd') ++CityStr.UserPosition;

		if (CityStr.UserPosition < 0) {

			CityStr.UserPosition = 0;
			continue;
		}
		if (CityStr.UserPosition > 11) {

			CityStr.UserPosition = 11;
			continue;
		}

		UserPrint(CityStr.UserPosition);

		if (!(UserInput == False || UserInput == 'a' || UserInput == 'd') && GameState == BuildingPhase) {

			IsBuildingError = False;

			if (UserInput == 'e') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					GameState = AlreadyOccupied;
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.PowerLeft) {

					GameState = NotingLeft;
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Power)) {

						CityStr.OccupyState[CityStr.UserPosition] = Power;
						CityStr.Health[CityStr.UserPosition] = PowerHeight;
						--CityStr.Buil.PowerLeft;
						++CityStr.BuildingLeft;
					}
					else {

						GameState = Canceled;
						IsBuildingError = True;
					}
				}
			}
			else if (UserInput == 't') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					GameState = AlreadyOccupied;
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.FactoryLeft) {

					GameState = NotingLeft;
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Factory)) {

						CityStr.OccupyState[CityStr.UserPosition] = Factory;
						CityStr.Health[CityStr.UserPosition] = FactoryHeight;
						--CityStr.Buil.FactoryLeft;
						++CityStr.BuildingLeft;
					}
					else {

						GameState = Canceled;
						IsBuildingError = True;
					}
				}
			}
			else if (UserInput == 'm') {

				if (CityStr.OccupyState[CityStr.UserPosition]) {

					GameState = AlreadyOccupied;
					IsBuildingError = True;
				}
				else if (!CityStr.Buil.ResidenceLeft) {

					GameState = NotingLeft;
					IsBuildingError = True;
				}

				if (!IsBuildingError) {

					if (BuildingConfirm(Residence)) {

						CityStr.OccupyState[CityStr.UserPosition] = Residence;
						CityStr.Health[CityStr.UserPosition] = ResidenceHeight;
						--CityStr.Buil.ResidenceLeft;
						++CityStr.BuildingLeft;
					}
					else {

						GameState = Canceled;
						IsBuildingError = True;
					}
				}
			}

			AvailableBuilding(CityStr.Buil);

			BuildingBuilder(CityStr);

			if (!CityStr.Buil.PowerLeft && !CityStr.Buil.FactoryLeft && !CityStr.Buil.ResidenceLeft) {

				SystemMessage(EnterProductionPhase);
				GameInitialize(ProductionPhase);
				ResourceDisplayer(CityStr);
				GameState = ProductionPhase;
			}
		}
		else if (GameState == ProductionPhase) {

			if (!CityStr.BuildingLeft) {

				system("cls");
				DialogDisplay("Game Over... 사령관님, 도시가 전부 파괴되었습니다...");
				//DialogDisplay("점수가 랭킹에 기록되었습니다.");
				return 0;
			}
			if (CityStr.Res.TechnologyState >= 150) {

				GameState = EndingPhase;
				continue;
			}

			HardrainAlert(20 - RainCounter);

			if (UserInput == ' ') CityStr.Score += 50 * RaserBeam(CityPtr, RainPtr);
			else if (UserInput == 'p') CityStr.Score += 50 * PulseLauncher(CityPtr, RainPtr);
			else if (UserInput == 'f') BuildingRepair(CityPtr);

			if (MilliSecond == Tic) {

				if (CityStr.OccupyState[CityStr.UserPosition] == Power) CityStr.Res.EnergyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Factory) CityStr.Res.TechnologyState += CityStr.Health[CityStr.UserPosition];
				else if (CityStr.OccupyState[CityStr.UserPosition] == Residence) CityStr.Res.CapitalState += CityStr.Health[CityStr.UserPosition];

				if (RainCounter < 20) ++RainCounter;

				if (RainCounter == 20) {

					CityStr.Score += 10;

					MakeItRa1n(CityPtr, RainPtr);
					GameInitialize(HardrainPhase);
					UserInfoDisplayer(CityStr);
				}
			}

			ResourceDisplayer(CityStr);
			BuildingBuilder(CityStr);
		}
		else if (GameState == EndingPhase) {

			system("cls");
			DialogDisplay("충분한 기술력을 모아 당신의 도시는 Cloud Ark를 완성했습니다.");
			DialogDisplay("거대한 함선 Cloud Ark는 모든 인류를 태우고 우주로 향했습니다.");
			DialogDisplay("인류의 다음 행선지는 어디일까요?");
			DialogDisplay("고생하셨습니다 사령관님.");
			return 0;
		}

		if (GameState != ProductionPhase && GameState != HardrainPhase) SystemMessage(GameState);

		if (MilliSecond == Tic) {

			if (GameState < 0) GameState = BuildingPhase;
		}

		MilliSecond = ClockGenerator(MilliSecond);
	}
	
	DialogDisplay("게임을 종료합니다... 나중에 다시 뵙겠습니다 사령관님.");

	return 0;
}

/* 구현 보류 
void RankingRecorder(City* CityPtr) {

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

	if (RankingData == NULL) {

		fopen_s(&RankingData, "c:\\ProgramData\\AKKYU\\EscapeHR\\ranking.aku", "w");

		if (RankingData == NULL) {

			system("cls");
			printf("알 수 없는 오류 발생! 죄송합니다");
			return;
		}

		fprintf_s(RankingData, "%s %s %da\n", CityPtr->Usr.UserName, CityPtr->Usr.CityName, CityPtr->Score);

		fclose(RankingData);
	}
	else {

		while (!feof(RankingData)) {

			memset(FileLineBuffer, 0, sizeof(FileLineBuffer));

			fgets(FileLineBuffer, sizeof(FileLineBuffer), RankingData);

			if (!FileLineBuffer[0])break;

			if (FileLineBuffer[strlen(FileLineBuffer) - 2] != 'a') {

				system("cls");

				CurPos(23, 1); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
				CurPos(23, 2); printf("┃       저장 데이터가 손상되었습니다...    ┃");
				CurPos(23, 3); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
				CurPos(23, 4); printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
				CurPos(23, 5); printf("┃         아무 키나 눌러서 돌아가기        ┃");
				CurPos(23, 6); printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

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

		fclose(RankingData);

		fopen_s(&RankingData, "c:\\ProgramData\\AKKYU\\EscapeHR\\ranking.aku", "a");

		if (RankingData == NULL) {

			system("cls");
			printf("알 수 없는 오류 발생! 죄송합니다");
			return;
		}

		fprintf_s(RankingData, "%s %s %da\n", CityPtr->Usr.UserName, CityPtr->Usr.CityName, CityPtr->Score);

		fclose(RankingData);

	}
}
*/