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
				DialogDisplay("Game Over... ��ɰ���, ���ð� ���� �ı��Ǿ����ϴ�...");

				break;
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
			DialogDisplay("����� ������� ��� ����� ���ô� Cloud Ark�� �ϼ��߽��ϴ�.");
			DialogDisplay("�Ŵ��� �Լ� Cloud Ark�� ��� �η��� �¿�� ���ַ� ���߽��ϴ�.");
			DialogDisplay("�η��� ���� �༱���� ����ϱ��?");
			DialogDisplay("����ϼ̽��ϴ� ��ɰ���.");
			
			break;
		}

		if (GameState != ProductionPhase && GameState != HardrainPhase) SystemMessage(GameState);

		if (MilliSecond == Tic) {

			if (GameState < 0) GameState = BuildingPhase;
		}

		MilliSecond = ClockGenerator(MilliSecond);
	}
	
	DialogDisplay("�ƹ� Ű�� ���� ��ɰ����� ����� �Ĵ뿡 ����ϴ�... (������ ���� 5���� ���� �ʾҴٸ� ��ϵ��� �ʽ��ϴ�.)");
	RankingRecorder(CityStr);
	DialogDisplay("��ŷ ������ �Ϸ�Ǿ����ϴ�!");

	DialogDisplay("������ �����մϴ�... ���߿� �ٽ� �˰ڽ��ϴ� ��ɰ���.");

	return 0;
}