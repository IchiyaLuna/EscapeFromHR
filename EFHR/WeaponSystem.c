#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <process.h>
#include "MacroSet.h"
#include "StructSet.h"
#include "WeaponSystem.h"
#include "BaseSystem.h"

void DisplayShield(short DamagePoint) {

	for (short i = 0; i < 12; ++i) {

		if (i == DamagePoint) {

			StringColor(Red);
			Beep((DWORD)_C, 100);
		}
		else StringColor(Cyan);

		CurPos(CityLeft + i, CityHeight - 4);

		printf("¦¬");

		StringColor(White);
	}

	CurPos(0, 23);
}

void MakeItRa1n(City* CityPtr, Rain* RainPtr) {

	short RandomPercent;
	short RandomPosition = -1;
	short IsBlankSpaceExist = False;
	short IsBuildingDestroyed = False;

	RandomPercent = rand() % 100;

	if (RandomPercent < 30) {

		for (short i = 0; i < 12; ++i) {

			if (!RainPtr->IsStarExist[i]) {

				IsBlankSpaceExist = True;
				break;
			}
		}

		if (IsBlankSpaceExist) {

			while (True) {

				RandomPosition = rand() % 12;
				if (!RainPtr->IsStarExist[RandomPosition]) break;
			}

			RainPtr->IsStarExist[RandomPosition] = True;
			RainPtr->StarHeight[RandomPosition] = 0;
		}
	}

	for (short i = 0; i < 12; ++i) {

		if (i == RandomPosition) continue;

		if (RainPtr->IsStarExist[i]) ++RainPtr->StarHeight[i];

		if (RainPtr->StarHeight[i] > 14) {

			RainPtr->StarHeight[i] = 0;
			RainPtr->IsStarExist[i] = False;

			if (CityPtr->OccupyState[i]) {

				--CityPtr->Health[i];

				if (!CityPtr->Health[i]) {

					CityPtr->OccupyState[i] = Blank;
					--CityPtr->BuildingLeft;
				}
			}

			IsBuildingDestroyed = True;

			CurPos(CityLeft + i, 15);
			putchar(' ');

			DisplayShield(i);
		}
	}
	if (!IsBuildingDestroyed) DisplayShield(-1);

	for (short i = 0; i < 12; ++i) {

		if (RainPtr->StarHeight[i]) {

			CurPos(CityLeft + i, RainPtr->StarHeight[i]);
			putchar(' ');
		}

		CurPos(CityLeft + i, CityTop + RainPtr->StarHeight[i]);

		StringColor(D_Red);
		if (RainPtr->IsStarExist[i]) putchar('*');
		StringColor(White);
	}

	CurPos(0, 23);
}

short RaserBeam(City* CityPtr, Rain* RainPtr) {

	short DestroyCount = 0;

	if (CityPtr->Res.EnergyState < 10) return 0;

	CityPtr->Res.EnergyState -= 10;

	for (short i = CityTop; i < 16; ++i) {

		CurPos(CityLeft + CityPtr->UserPosition, i);
		StringColor(Back_Cyan);
		putchar(' ');
	}

	Beep((DWORD)_E, 100);

	Sleep(100);

	for (short i = CityTop; i < 16; ++i) {

		CurPos(CityLeft + CityPtr->UserPosition, i);
		StringColor(White);
		putchar(' ');
	}

	if (RainPtr->IsStarExist[CityPtr->UserPosition]) ++DestroyCount;

	RainPtr->IsStarExist[CityPtr->UserPosition] = False;
	RainPtr->StarHeight[CityPtr->UserPosition] = 0;

	CurPos(0, 23);

	return DestroyCount;
}

short PulseLauncher(City* CityPtr, Rain* RainPtr) {

	HANDLE hThread[1];
	DWORD dwThreadID;

	short DestroyCount = 0;

	if (CityPtr->Res.CapitalState < 35) return -1;
	CityPtr->Res.CapitalState -= 35;

	for (short i = 0; i < 15; ++i) {

		for (short j = 0; j < 12; ++j) {

			CurPos(CityLeft + j, CityTop + (14 - i));
			StringColor(Back_Yellow);
			putchar(' ');

			if (!RainPtr->IsStarExist[j]) continue;

			if (RainPtr->StarHeight[j] == (14 - i)) {

				RainPtr->StarHeight[j] = 0;
				RainPtr->IsStarExist[j] = 0;
				++DestroyCount;
			}
		}

		hThread[0] = (HANDLE)_beginthreadex(NULL, 0, BeepPlayer, NULL, 0, (unsigned*)&dwThreadID);

		if (hThread[0]) CloseHandle(hThread[0]);

		Sleep(100);

		for (short j = 0; j < 12; ++j) {

			CurPos(CityLeft + j, CityTop + (14 - i));
			StringColor(White);
			putchar(' ');
		}

		if (DestroyCount == 3) break;
	}

	CurPos(0, 23);

	return DestroyCount;
}